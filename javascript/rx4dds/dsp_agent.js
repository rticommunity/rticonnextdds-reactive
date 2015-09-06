// make sure $NODE_PATH contains rti.js
var rti     = require("rti");
var http    = require("http");  
var fs      = require("fs");  
var Rx      = require("rx");
var filters = require("./filters.js");

function createObservableServer()
{
    var subject = new Rx.Subject();
    var errSubject = new Rx.Subject();

    var server = http.createServer(function (request, response)
    {
       subject.onNext(request);
       response.writeHeader(201, {"Content-Type": "text/plain"});  
       response.write("OK");  
       response.end();  
    });

    server.errObservable = errSubject.asObservable();

    server.observable = 
      subject
        .asObservable()
        .concatMap(function (request) 
        {
           return Rx.Node
                    .fromReadableStream(request)
                    .reduce(function (acc, data) 
                      {
                        return acc + data;
                      }, "")
                    .select(function(data) {
                      try {
                        return JSON.parse(data);
                      }
                      catch(err) {
                        errSubject.onNext(err);
                      }
                      return null;
                    })
                    .where(function (x) { return x != null; });
        });

    return server; 
};

function createObservableDataReader(library, profile, reader) 
{
  return Rx.Observable.create(function (observer) {
    //var subject = new Rx.Subject();

    var connector = new rti.Connector(library, profile);
    if (connector == null) {
      throw "Null connector";
    }
    
    var dds_input = connector.getInput(reader);
    if (dds_input == null) { 
      throw "Null dds_input";
    }

    connector.on('on_data_available',
       function() {
         try {
           dds_input.take();
           for (i=1; i <= dds_input.samples.getLength(); i++) 
           {
             if(dds_input.samples != null) 
             {
               var data = dds_input.samples.getString(i,"data");
               // console.log("Received @ DataReader: " + data);
               var json = JSON.parse(data);
               observer.onNext(json);
             } 
           }
         }
         catch(err) {
           console.log("Exception in on_data_available: " + err.message);
         }
       });
    
    //return subject.asObservable();
    return { dispose : function() {} };
 });
}

var runtimeInstance = {
  disposable   : null,
  server       : null,
  op_connector : null,
  dds_output   : null,
  errSubject   : null,
  in_streams   : { "AggregateFlow" : {} },
  out_streams  : { "console"   : {},
                   "alerts"    : {},
                   "snapshots" : {},
                   "dds"       : {} 
                 },
  port         : 8080,
  count        : 0,

  dispose : function() {
    if(this.disposable != null)
    {
      console.log("Now disposing...");
      this.disposable.dispose();
      this.disposable = null;
    }
  },

  writeToDDS : function(data) {
   try {
      var runtime = this;
      var str = JSON.stringify(data, null, 4);
      //console.log(str);
      runtime.dds_output.instance.setString("data", str);
      runtime.dds_output.write();
   }
   catch(err) {
      console.log("Exception in writeToDDS: " + err.message);
   }
  },

  probe_parser: function (filename) {
    'use strict'
    var runtime = this;
    if(filename != null) 
    {
      /* NOTE: return can't be on its own in a line. */
      return Rx.Node
          .fromReadableStream(fs.createReadStream(filename))
          .reduce(function (acc, data) 
          {
              return acc + data;
          }, "")
          .select(function (file) {
            return file.replace(/\n/g, "");
          })
          .selectMany(function(data) {
            try {
              var json = JSON.parse(data);
              if (json instanceof Array)
                return Rx.Observable.fromArray(json);
              else
                return Rx.Observable.just(json);
            }
            catch(err) {
              err.extra = "Probe JSON file parsing failed";
              runtime.errSubject.onNext(err);
            }
            return Rx.Observable.empty();
          });
    }
    throw new Error("Null filename");
  },

  launch_probes : function(probe_observable) {
    var runtime = this;

    var disposable = 
      probe_observable
        .do(function(probe) 
        { 
          runtime.composite_disposable.add(
            filters.install_probe(
                probe, 
                runtime, 
                function (err) {
                  runtime.errSubject.onNext(err);
               }).subscribe());
        })
        .subscribe();

    runtime.composite_disposable.add(disposable);
  },

  setup_error_streams : function() {
    var runtime = this;
    if(runtime.composite_disposable != null) 
    {
      var server_err_disposable = 
        runtime.server
               .errObservable
               .subscribe(
                 function (ex) {
                   console.log("Server Exception: " + ex.message); 
                 },
                 function (err) {},
                 function () {});
      
      runtime.composite_disposable.add(server_err_disposable);
   
      var runtime_err_disposable = 
        runtime.errSubject
               .asObservable()
               .subscribe(
                 function (err) {
                   var msg = "runtime Exception: " + err.message;

                   if(err.extra != null) 
                     msg += err.extra; 

                   console.log(msg);
                 },
                 function (err) {},
                 function () {});
      
      runtime.composite_disposable.add(runtime_err_disposable);
    }
    else {
      console.log("Missing composite disposable");
    }
  },

  setup_streams : function (source) {
    var runtime = this;
    runtime.setup_error_streams();

    if(runtime.composite_disposable != null)
    {
      runtime.out_streams["snapshots"] = new Rx.Subject();
      runtime.out_streams["console"]  = new Rx.Subject();
      runtime.out_streams["alerts"]   = new Rx.Subject();
      runtime.out_streams["dds"]      = new Rx.Subject();

      runtime.in_streams["alerts"] = 
        {
          observable : 
            runtime.out_streams["alerts"].asObservable() 
        };

      runtime.in_streams["snapshots"] = 
        {
          observable : 
            runtime.out_streams["snapshots"].asObservable() 
        };

      var seq_num = 0;
      runtime.in_streams["AggregateFlow"] = 
        {
          observable : source.select(function (x) {
                          x["seq_num"]   = seq_num++;
                          return x;
                       })
        };

      runtime.composite_disposable.add(
        runtime.out_streams["dds"]
               .asObservable()
               .subscribe(function(data) {
                 runtime.writeToDDS(data);
               }));

      runtime.composite_disposable.add(
        runtime.out_streams["console"]
               .asObservable()
               .subscribe(function(data) {
                 console.log(JSON.stringify(data, null, 4));
               }));
    }
    else
      console.log("Missing composite disposable");
  },

  setup_http_to_dds : function () {
    var runtime = this;
    runtime.op_connector 
      = new rti.Connector("AgentParticipantLibrary::Alert-Agent","rest2dds.xml");

    runtime.dds_output 
      = runtime.op_connector.getOutput("Publisher::FlatJSONWriter")

    runtime.server = createObservableServer();
    runtime.errSubject = new Rx.Subject();

    var source = 
      runtime.server
          .observable
          .flatMap(function(data) {
              if ("type" in data)
                return new Rx.Observable.just(data);
              else 
              {
                runtime.errSubject.onNext(new Error('No "type" in data'));
                return new Rx.Observable.empty();
              }
            })
          .publish()
          .refCount();

    
    runtime.server.listen(runtime.port);
    console.log("Runtime server listening on port: " + runtime.port);

    return source;
  },

  setup_dds_to_dds : function () {
    var runtime = this;
    
    var errSubject = new Rx.Subject();
    runtime.server = {};
    runtime.server.errObservable = errSubject.asObservable();

    runtime.op_connector 
      = new rti.Connector("AgentParticipantLibrary::Alert-Agent","rest2dds.xml");

    runtime.dds_output 
      = runtime.op_connector.getOutput("Publisher::FlatJSONWriter")

    var json_stream = createObservableDataReader(
      "AgentParticipantLibrary::Data-Collection-Agent",
      "rest2dds.xml",
      "Subscriber::FlatJSONReader");
   
    runtime.errSubject = new Rx.Subject();

    var source = 
        json_stream
          .flatMap(function(data) {
              if ("type" in data)
                return new Rx.Observable.just(data);
              else 
              {
                runtime.errSubject.onNext(new Error('No "type" in data'));
                return new Rx.Observable.empty();
              }
            })
          .publish()
          .refCount();

    console.log("Waiting for data over dds.");

    return source;
  },

  start : function(protocol, filename) {
    var runtime = this;

    runtime.composite_disposable = 
      new Rx.CompositeDisposable();

    var source_stream = null;
    if(protocol === "http")
      source_stream = runtime.setup_http_to_dds();
    else if(protocol === "dds") 
      source_stream = runtime.setup_dds_to_dds();
    else
    {
      console.log("Incorrect protocol. Must be 'http' or 'dds'.");
      return
    }

    runtime.setup_streams(source_stream);
    
    var probe_observable = runtime.probe_parser(filename);

    runtime.launch_probes(probe_observable);
   } // start
         
}; // runtimeInstance

function main(runtime, argv) {

  if(argv.length < 4)
  {
    console.log("Usage: node dsp_agent.js [http|dds] [filename]");
    return;
  }
  runtime.start(argv[2], argv[3]);  

  // exceptiopn
  /*process.on('uncaughtException', function (err)
  {
    runtime.dispose();
    console.log(['Caught exception:', err.message].join(" "));
  });*/

  process.on('exit', runtime.dispose);

}

main(runtimeInstance, process.argv);

