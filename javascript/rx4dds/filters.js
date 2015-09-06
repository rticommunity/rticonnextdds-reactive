var flatMap  = require("flatmap");
var jsonPath = require("JSONPath");
var Rx       = require("rx");
var _        = require("underscore");

var MAX_INT = 9007199254740992;

var time_scale = {
  "msec" : 1,
  "sec"  : 1000,
  "min"  : 60000,
  "hr"   : 3600000,
};

function add_expr(a, b) { return a+b; } 
function sub_expr(a, b) { return a-b; } 
function div_expr(a, b) { return a/b; } 
function mul_expr(a, b) { return a*b; } 

var expr = {
  "+" : add_expr,
  "-" : sub_expr,
  "/" : div_expr,
  "*" : mul_expr
};

function clone(x) {
  return JSON.parse(JSON.stringify(x));
}

function getArrayMin(array){
  return Math.min.apply(Math,array);
}

function getArrayMax(array){
  return Math.max.apply(Math,array);
}

function set_property(obj, path, val) {
  var nested = obj;
  var i = 0;
  for(i = 0;i < path.length - 1; ++i)
  {
    if(!(path[i] in nested)) {
      nested[path[i]] = {};
    }
    nested = nested[path[i]];
  }
  nested[path[i]] = val;
}

function has_property(obj, path) {
  var nested = obj;
  var i = 0;
  for(i = 0;i < path.length; ++i)
  {
    if(!(path[i] in nested)) {
      return false;
    }
    else
      nested = nested[path[i]];
  }
  return true;
}

function get_property(path, obj) {
  var nested = obj;
  var i = 0;
  for(i = 0;i < path.length - 1; ++i)
  {
    if(!(path[i] in nested)) {
      return undefined;
    }
    else
      nested = nested[path[i]];
  }
  return nested[path[i]];
}

function has(arr) {
   var path = arr[2].split(".");   
   return function (x) {
     return has_property(x, path);
   };
}

function match(arg) {
  return function (x) {
    var result = false;
    for(var key in arg) {
      if ((key in x) && (x[key] === arg[key]))
        result = true;
      else {
        result = false;
        break;
      }
    }
    return result;
  };
}

function hastype(arr) {
  return match({ "type" : arr[2] });
}

function contains(arr) {
  var path = arr[2].split(".");
  var substr = arr[3];
  return function (x) {
    return get_property(path, x).toString().indexOf(substr) >= 0;
  };
}

function notcontains(arr) {
  var path = arr[2].split(".");
  var substr = arr[3];
  return function (x) {
    return !(get_property(path, x).toString().indexOf(substr) >= 0);
  };
}

function block(unused) {
  return function (x) { return false; }
}

function pass (unused) {
  return function (x) { return true; }
}

function comparer(comp) {
  return function (arr) {
    var path = arr[2].split(".");
    return function (x) {
      var nested = x;
      var i = 0;
      for(i = 0;i < path.length - 1; ++i)
      {
        if(!(path[i] in nested)) {
          return false;
        }
        else
          nested = nested[path[i]];
      }
      if(path[i] in nested) 
        return comp(nested[path[i]], arr[3]);
      else
        return false;
    };
  };
}

function gte(a, b)       { return a >= b;  }
function gt(a, b)        { return a > b;   }
function lte(a, b)       { return a <= b;  }
function lt(a, b)        { return a < b;   }
function not_equal(a, b) { return a != b;  }
function equal(a, b)     { return a == b;  }

function Operator(inprop, outprop) {
 this.inpath = inprop.split(".");
 this.outpath = outprop.split(".");
}

function AverageOp(inprop, outprop) {
 Operator.call(this, inprop, outprop);
 this.count = 0; 
 this.avg = 0;
}

AverageOp.prototype.scan = function (acc, x) 
{
   var newsum = acc.avg * acc.count + get_property(acc.inpath, x);
   acc.count = acc.count + 1;
   acc.avg = newsum/acc.count;
   set_property(x, acc.outpath, acc.avg);
   return acc;
};

AverageOp.prototype.win_scan = function(acc,
                                        x, 
                                        expired_list, 
                                        current_list)
{
  var total 
    = acc.avg * (current_list.length + expired_list.length - 1);
  total += get_property(acc.inpath, x);
  for(var i = 0;i < expired_list.length; ++i)
  {
    total -= get_property(acc.inpath, expired_list[i].data);
  }
  acc.avg = total/current_list.length;
  set_property(x, acc.outpath, acc.avg);
  return acc;
}

function MinOp(inprop, outprop) {
 Operator.call(this, inprop, outprop);
 this.min = MAX_INT; 
}

MinOp.prototype.scan = function (acc, x) {
   acc.min = Math.min(acc.min, get_property(acc.inpath, x));
   set_property(x, acc.outpath, acc.min);
   return acc;
};

MinOp.prototype.win_scan = function(acc,
                                    x, 
                                    expired_list, 
                                    current_list)
{
  var min = MAX_INT;
  for(var i = 0;i < current_list.length; ++i)
  {
    var val = get_property(acc.inpath, current_list[i].data);
    if(val < min)
      min = val;
  }
  acc.min = min;
  set_property(x, acc.outpath, min);
  return acc;
}

function MaxOp(inprop, outprop) {
 Operator.call(this, inprop, outprop);
 this.max = MAX_INT * -1; 
}

MaxOp.prototype.scan = function (acc, x) {
   acc.max = Math.max(acc.max, get_property(acc.inpath, x));
   set_property(x, acc.outpath, acc.max);
   return acc;
};

MaxOp.prototype.win_scan = function(acc,
                                    x, 
                                    expired_list, 
                                    current_list)
{
  var max = MAX_INT * -1;
  for(var i = 0;i < current_list.length; ++i)
  {
    var val = get_property(acc.inpath, current_list[i].data);
    if(val > max)
      max = val;
  }
  acc.max = max;
  set_property(x, acc.outpath, max);
  return acc;
}

function SnapshotOp(minus, plus, trigger_stream, in_stream, out_subject) {
  var self = this;
  self.history = [];

  var history_stream = 
    trigger_stream.select(function (x) {
        
        var history = self.history.slice(0); // make copy
        prune_history(history, new Date(), minus);
        var history_stream = 
              Rx.Observable
                .fromArray(history)
                .select(function (x) {
                   return x.data;
                });
        return history_stream; 
    });

  var future_stream =
    in_stream
      .window(trigger_stream,
              function () { 
                return Rx.Observable.timer(plus);
              });

  var snapshot_stream = 
    Rx.Observable.zip(history_stream, 
                      future_stream,
                      function (hs, fs) {
                        return Rx.Observable.concat(hs, fs);
                      });

  this.disposable = 
    snapshot_stream
      .selectMany(function (stream) {
          return stream;
      })
      .subscribe(out_subject);
}

SnapshotOp.prototype.scan = function (acc, x) {
   return acc;
};

SnapshotOp.prototype.win_scan = function(acc,
                                         x, 
                                         expired_list, 
                                         current_list)
{
  this.history = current_list;
  return acc;
}

function scan_insert(op, in_observable) {
  return in_observable.scan(
    { 
      data  : null,
      state : op
    },
    function (acc, x) {
      acc.data = x;
      acc.state = acc.state.scan(acc.state, x);
      return acc;
  })
  .select(function (x) { return x.data; });
}

function average_insert(inprop, outprop, in_observable) {
 return scan_insert(new AverageOp(inprop, outprop), in_observable);
}

function minimum_insert(inprop, outprop, in_observable) {
 return scan_insert(new MinOp(inprop, outprop), in_observable);
}

function maximum_insert(inprop, outprop, in_observable) {
 return scan_insert(new MaxOp(inprop, outprop), in_observable);
}

function count_insert(inprop, outprop, in_observable) {
 return scan_insert(new CountOp(inprop, outprop), in_observable);
}

function jsonpath_insert(inprop, outprop, in_observable) {
  var outpath = outprop.split(".");
  return in_observable.select(function (x) {
      var result = jsonPath.eval(x, inprop);
      if(result.length > 0)
        set_property(x, outpath, result);
      return x;
  });
}

function eval_insert(inprop, outprop, in_observable, callback) {
  var outpath = outprop.split(".");
  var inexpr = inprop.match(/\s*([\w\.]+)\s+([\/\-\+\*]?)\s+([\d\.]+)\s*$/i);
  if(inexpr != null)
  {
    var inpath = inexpr[1].split(".");
    var mathfunc = inexpr[2];
    var operand = inexpr[3];
    return in_observable.select(function (x) {
        var orig = get_property(inpath, x);
        var result = expr[mathfunc](orig, operand);
        set_property(x, outpath, result);
        return x;
    });
  }
  else {
    callback(new Error("Invalid expression = '" + inprop + "'"));
    return in_observable.where(block);
  }
}

function average_win_insert(inprop, winlen, wintype, outprop, in_observable, callback) {
 return time_window_aggregate(
          in_observable, 
          winlen * time_scale[wintype],
          new AverageOp(inprop, outprop), 
          null, // timekeeper
          function (err) {
            err.extra = "Error in average_win_insert.";
            callback(err);
          });
}

function minimum_win_insert(inprop, winlen, wintype, outprop, in_observable, callback) {
 return time_window_aggregate(
          in_observable, 
          winlen * time_scale[wintype],
          new MinOp(inprop, outprop), 
          null, // timekeeper
          function (err) {
            err.extra = "Error in minimum_win_insert.";
            callback(err);
          });
}

function maximum_win_insert(inprop, winlen, wintype, outprop, in_observable, callback) {
 return time_window_aggregate(
          in_observable, 
          winlen * time_scale[wintype],
          new MaxOp(inprop, outprop), 
          null, // timekeeper
          function (err) {
            err.extra = "Error in maximum_win_insert.";
            callback(err);
          });
}

function snapshot_window(minus, plus, trigger_stream, in_observable, out_subject, callback) {
 return time_window_aggregate(
          in_observable, 
          minus,
          new SnapshotOp(minus, plus, trigger_stream, in_observable, out_subject), 
          null, // timekeeper
          function (err) {
            err.extra = "Error in snapshot_window.";
            callback(err);
          });
}

function TimestampedData(data, now) 
{
  this.data = data;
  this.ts = now;
}


function prune_history(history_list, now, timespan) {
  var ex_count = 0;

  for(var i = 0;i < history_list.length; ++i)
  {
    if ((now - history_list[i].ts) > timespan)
      ex_count++;
    else
      break;
  }
  var expired_list = history_list.splice(0, ex_count);
  return expired_list;
}

function time_window_aggregate(
  in_observable, timespan, op, timekeeper, callback)
{
  if(timekeeper == null)
    timekeeper = function (x) { return new Date(x["@timestamp"]); };

  return in_observable.scan(
    { data         : null,
      history_list : [],
      state        : op,
      now          : new Date(1) 
    },
    function(acc, x) {
      try
      {
        acc.data = x;
        acc.now = Math.max(acc.now, timekeeper(x));
        var expired_list =
          prune_history(acc.history_list, acc.now, timespan);
        acc.history_list.push(new TimestampedData(x, acc.now));
        acc.state = acc.state.win_scan(acc.state,
                                       x, 
                                       expired_list, 
                                       acc.history_list);
        return acc;
      }
      catch (err)
      {
        callback(err);
      }
    })
    .select(function(x) { return x.data; });
}

function detectStale(source, period, callback)
{
    return Rx.Observable.create(function (observer) {
        var timerSubscription = new Rx.SerialDisposable();
        var last_seen = null;

        var scheduleStale = function() 
        {
            timerSubscription.setDisposable(
                  Rx.Observable
                    .timer(period)
                    .subscribe(function() 
                    {
                       observer.onNext({ "last_seen" : last_seen,
                                         "stale" : "Unavailable" });
                    }));
        };

        var sourceSubscription = source.subscribe(
            function (x) 
            {
                // cancel any scheduled stale update
                var disposable = timerSubscription.getDisposable();
                if (disposable != null)
                    disposable.dispose();

                last_seen = x;
                observer.onNext({ "last_seen" : x,
                                  "stale" : "Available" } );
                scheduleStale();
            },
            function (err) { callback(err); },
            function () { });

        scheduleStale();

        return new Rx.CompositeDisposable(sourceSubscription, timerSubscription);
    });
}

var where_regex = {
  "has"     : { 
                regex: /^\s*(has)\s+([\w\.]+)\s*$/i,
                func : has
              },
  "hastype" : {
                regex : /^\s*(hastype)\s+(\w+)\s*$/i,
                func  : hastype
              },
  "contains" : {
                regex : /^\s*(contains)\s+([\w\.]+)\s+'(.*)'\s*$/i,
                func  : contains 
              },
  "notcontains" : {
                regex : /^\s*(notcontains)\s+([\w\.]+)\s+'(.*)'\s*$/i,
                func  : notcontains 
              },
  "pass"    : {
                regex : /^\s*(pass)\s*$/i,
                func  : pass
              },
  "block"   : {
                regex : /^\s*(block)\s*$/i,
                func  : block
              },
  "greater_than_equal" : {
      regex : /^\s*(greater_than_equal)\s+([\w\.]+)\s+([\w\.]+)\s*$/i,
      func  : comparer(gte) 
  },
  "greater_than" : {
      regex : /^\s*(greater_than)\s+([\w\.]+)\s+([\w\.]+)\s*$/i,
      func  : comparer(gt) 
  },
  "less_than_equal" : {
      regex : /^\s*(less_than_equal)\s+([\w\.]+)\s+([\w\.]+)\s*$/i,
      func  : comparer(lte) 
  },
  "less_than" : {
      regex : /^\s*(less_than)\s+([\w\.]+)\s+([\w\.]+)\s*$/i,
      func  : comparer(lt) 
  },
  "not_equal" : {
      regex : /^\s*(not_equal)\s+([\w\.]+)\s+([\w\.]+)\s*$/i,
      func  : comparer(not_equal) 
  },
  "equal" : {
      regex : /^\s*(equal)\s+([\w\.]+)\s+([\w\.]+)\s*$/i,
      func  : comparer(equal) 
  }

};

var regex = {
  "output"     : /^\s*(output)\s+(\w+)\s*([@\w\.]+)?\s*$/i,
  "match"      : /\s*(match)\s+({.*})\s*$/i,
  "source"     : /\s*(source)\s+(\w+)\s*$/i,
  "groupby"    : /\s*(groupby)\s+([\w\.]+)\s*$/i,
  "pluck"      : /\s*(pluck)\s+([@\w\.]+)\s*$/i,
  "delete"     : /\s*(delete)\s+([\w@\.]+)\s*$/i,
  "sample"     : /\s*(sample)\s+([\w]+)\s*$/i,
  "interval"   : /\s*(interval)\s+([\d\.]+)\s+(\w+)\s*$/i,
  "maxage"     : /\s*(maxage)\s+([\d\.]+)\s+(\w+)\s*$/i,
  "jsonpath"   : /\s*(jsonpath)\s+(\$\.{1,2}[^\s]*)\s*$/i,
  "liveliness" : /\s*(liveliness)\s+([\d\.]+)\s+(\w+)\s*$/i,
  "snapshot"   : /\s*(snapshot)\s+(timerange)\((-?[\d\.]+)\s+(\w+)\s*,\s*(\+?[\d\.]+)\s+(\w+)\)\s*([\w,]+)?\s*$/i,
  "insert"     : /\s*(insert)\s+(.+)\((.+)\)\s+(as)\s+([\w.]+)\s*$/i,
  "insertover" : 
    /\s*(insert)\s+(\w+)\((.+)\)\s+(over)\s+([\d\.]+)\s+(\w+)\s+(as)\s+([\w.]+)\s*$/i
};

var projection_op = {
  "avg"      : { always : average_insert, 
                 window : average_win_insert },

  "min"      : { always : minimum_insert,
                 window : minimum_win_insert },

  "max"      : { always : maximum_insert,
                 window : maximum_win_insert },

  "jsonpath" : { always : jsonpath_insert },

  "eval"     : { always : eval_insert }
};

function compile_filter(stages, runtime, source, callback)
{
  var result = 
    stages.reduce(function (acc, f, index) {
      if(acc.ignore) {
        return acc;
      }

      if(source == null)
      {
        var arr = f.match(regex["source"]);
        if(arr != null) 
        {
          if(acc.observable == null)
          {
            if(arr[2] in runtime.in_streams)
              acc.observable = 
                runtime.in_streams[arr[2]]
                       .observable
                       .select(clone);
            else
              callback(new Error("Non-existant source '" + arr[2] + "'"));
          }
          else
            callback(new Error("Ignoring extra source '" + arr[2] + "'"));
            
          return acc;
        }

        if(acc.observable == null)
        {
          callback(new Error("Missing source..."));
          return acc;
        }
      }

      if((source != null) && (acc.observable == null))
      { 
        acc.observable = source;
      }

      arr = f.match(regex["groupby"]);
      if(arr != null)
      {
        var rhs_stages = stages.slice(index+1); 
        var path = arr[2].split(".");
        var key_selector = _.partial(get_property, path);
        var pre_groupby_ob = acc.observable;

        acc.observable = 
          Rx.Observable.create(function (observer) {
            return pre_groupby_ob
                      .groupBy(key_selector)
                      .selectMany(function (keyed_stream) {
                        //console.log("rhs_stages = " + 
                        //            JSON.stringify(rhs_stages, null, 4));
                        return compile_filter(
                                 rhs_stages, 
                                 runtime, 
                                 keyed_stream.select(clone),
                                 callback);
                      })
                      .subscribe(observer);
          })
          .publish()
          .refCount();

        acc.ignore = true;
        return acc;
      }

      for(var key in where_regex) 
      {
        var arr = f.match(where_regex[key].regex);
        if(arr != null) 
        {
          acc.observable = 
            acc.observable.where(where_regex[key].func(arr)); 
          return acc;
        }
      }

      arr = f.match(regex["snapshot"]);
      if(arr != null)
      {
        var trigger_names = [ "alerts" ];

        if(arr[7] != null)
          trigger_names = arr[7].split(",");

        var trigger_stream = 
          runtime.in_streams[trigger_names[0]].observable;
        for(var i = 1;i < trigger_names.length; ++i)
        {
          trigger_stream = 
            trigger_stream.merge(
              runtime.in_streams[trigger_names[i]].observable);
        }
        acc.observable = 
          snapshot_window(Math.abs(arr[3] * time_scale[arr[4]]), 
                          Math.abs(arr[5] * time_scale[arr[6]]), 
                          trigger_stream, 
                          acc.observable, 
                          runtime.out_streams["snapshots"],
                          callback);

        return acc;
      }

      var arr = f.match(regex["pluck"])
      if(arr != null)
      {
        var path = arr[2].split(".");
        acc.observable = acc.observable
                            .select(_.partial(get_property, path));
        return acc;
      }

      var arr = f.match(regex["match"]);
      if(arr != null)
      {
        try {
          var json = JSON.parse(arr[2]);
          acc.observable = acc.observable.where(match(json)); 
        }
        catch (err) {
          err.extra = "Parsing 'match JSON' failed. filter = '" + f + "'";
          callback(err);
          acc.observable = acc.observable.where(block); 
        }
        return acc;
      }

      arr = f.match(regex["insert"]);
      if(arr != null)
      {
        if(arr[2] in projection_op)
          acc.observable = 
            projection_op[arr[2]].always(arr[3], 
                                         arr[5], 
                                         acc.observable,
                                         callback);
        else 
          callback(new Error("Projection operator '" + arr[2] + "' is not defined."));
      
        return acc;
      }

      arr = f.match(regex["insertover"]);
      if(arr != null)
      {
        if(arr[2] in projection_op)
          acc.observable = 
            projection_op[arr[2]].window(arr[3], 
                                         arr[5], 
                                         arr[6], 
                                         arr[8], 
                                         acc.observable,
                                         callback);
        else 
          callback(new Error("Projection window operator '" + arr[2] + "' is not defined."));
      
        return acc;
      }
     
      arr = f.match(regex["interval"]);
      if(arr != null)
      {
        if(arr[3] in time_scale) {
          acc.observable =
            acc.observable.throttleFirst(time_scale[arr[3]] * arr[2]);
        }
        else
        {
          callback(new Error("Unknown time scale '" + arr[3] + "'"));
        }
        return acc;
      }

      arr = f.match(regex["sample"]);
      if(arr != null)
      {
        if(arr[2] in runtime.in_streams)  
        {
          acc.observable =
            acc.observable.sample(runtime.in_streams[arr[2]].observable);
        }
        else {
          callback(new Error("Stream '" + arr[2] + "' is not defined"));
        }
        
        return acc;
      }

      arr = f.match(regex["maxage"]);
      if(arr != null)
      {
        if(arr[3] in time_scale) 
        {
          var delta = time_scale[arr[3]] * arr[2];  
          acc.observable = 
            acc.observable.where(function (x) {
                  var data_ts = Date.parse(x["@timestamp"]); 
                  var now = new Date().getTime();
                  return Math.abs(now - data_ts) <= delta;
                });
        }
        else {
          callback(new Error("maxage unit " + arr[3] + "is illegal."));
        }
        return acc;
      }
      
      arr = f.match(regex["delete"]);
      if(arr != null)
      {
        var path = arr[2].split(".");
        acc.observable = 
          acc.observable.select(function (x) {
            var i = 0;
            nested = x;
            for(;i < path.length - 1; ++i) {
              nested = nested[path[i]]; 
            }
            delete nested[path[i]];
            return x;
          });
        return acc;
      }

      arr = f.match(regex["jsonpath"]);
      if(arr != null)
      {
        acc.observable = 
          acc.observable.selectMany(function (x) {
            var json_result = jsonPath.eval(x, arr[2]);
            if (json_result instanceof Array)
            {
              if(json_result.length > 0)
                return Rx.Observable.fromArray(json_result);
              else
                return Rx.Observable.empty();
            }
            else
              return Rx.Observable.empty();
          });
        return acc;
      }

      arr = f.match(regex["liveliness"]);
      if(arr != null)
      {
        if(arr[3] in time_scale) 
        {
          acc.observable = 
            detectStale(acc.observable, 
                        time_scale[arr[3]] * arr[2], 
                        callback)
                    .distinctUntilChanged(function (x) {
                       return x.stale;
                    });
        }
        else
          callback(new Error("Illegal time scale: " + arr[3]));

        return acc;
      }

      arr = f.match(regex["output"]);
      if(arr != null)
      {
        if(arr[2] in runtime.out_streams) 
        {
          var prop = arr[3];
          if(prop != null) {
            var path = arr[3].split(".");
            acc.observable = 
              acc.observable
                 .select(function (x) {
                    console.log(prop + " = " + 
                                JSON.stringify(get_property(path, x), null, 4));
                    return x;
                 });
          }
          acc.observable = 
            acc.observable
               .do(runtime.out_streams[arr[2]]);
        }
        else
          callback(new Error("Unknown output stream '" + 
                             arr[2] + 
                             "'. Ignoring..."));
        
        return acc;
      }

      callback(new Error("Unknown/Invalid filter: '" + f + "'"));
      acc.observable = acc.observable.where(block("unused"));
      return acc;
    }, 
    { observable : null,
      ignore     : false} );

    return result.observable;
}

function install_probe(probe, runtime, callback) {
  var result =
    compile_filter(probe.filter.split("|"),
                   runtime, 
                   null, // source
                   callback);
 
  result = result.publish().refCount();

  if(probe.trigger) 
  {
      result = 
        result.do(function (x) {
              var alrt = 
                { 
                  "type"           : "Alert",
                  "causedByProbe"  : probe.name,
                  "causedByData"   : x,
                  "@timestamp"     : new Date(), 
                  "tags"           : [],
                };
       
              if("tags" in probe)
                alrt.tags = probe.tags;

              runtime.out_streams["alerts"].onNext(alrt);
          });
  }

  runtime.in_streams[probe.name] = 
    { observable : result };

  return result;
}

module.exports = {
 "install_probe" : install_probe 
};
