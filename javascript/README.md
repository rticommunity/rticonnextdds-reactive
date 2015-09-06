Rx4DDS
======
RxJS (Node.js) Adapter for RTI Connext DDS. Works with [Connext Node.js Connector](https://github.com/rticommunity/rticonnextdds-connector)

### StreamCoCo

- Stream Concatenation and Co-ordination Language for Reactive Stream Processing. See research [paper](https://community.rti.com/paper/streamcoco-dsl-processing-data-centric-streams-industrial-iot-edge-applications).
- StreamCoCo used in [remote log analytics](http://www.slideshare.net/SumantTambe/remote-log-data-analytics-using-dds-and-rxjs)

Here's a temperature monitoring and alerting program written in StreamCoCo.

```json
[
{
 "name"     : "AlertsStream",
 "filter"   : "source alerts |
               hastype Alert |
               insert jsonpath($.causedByData.sensor_id) as causedBySensor |
               insert jsonpath($..host_ip) as availabilityChangedHost |
               insert jsonpath($..stale) as hostStatus |
               output console |
               delete causedByData |
               output dds" 
},
{
 "name"     : "SnapshotStream",
 "filter"   : "source snapshots | 
               output dds"
},
{
 "name"     : "TemperatureDataSource",
 "filter"   : "source AggregateFlow            |
               hastype temperature_readings         |
               has sensor_id                        | 
               has celsius_x_1000                   | 
               insert eval(celsius_x_1000 / 1000) as celsius |
               match { \"host\" : \"sbir30ship\" }"
},
{ 
 "name"     : "TempAvgProbe",
 "filter"   : "source TemperatureDataSource |
               groupby sensor_id | 
               insert avg(celsius) over 30 sec as extra.degree_avg |
               snapshot timerange(-55 sec,+55 sec) |
               greater_than_equal extra.degree_avg 65 |
               interval 120 sec",
 "trigger"  : true,
 "tags"     : [ "cpu_overheat", "cpu_heat_warning" ]
}
```