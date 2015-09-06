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
 "name"     : "Win32LoginAlertStream",
 "filter"   : "source AlertsStream | 
               contains tags 'win32_login'"
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
},
{ 
 "name"     : "TempMaxProbe",
 "filter"   : "source TemperatureDataSource |
               groupby sensor_id | 
               insert max(celsius) over 30 sec as extra.degree_max |
               snapshot timerange(-55 sec,+55 sec) |
               greater_than_equal extra.degree_max 85 |
               interval 120 sec",
 "trigger"  : true,
 "tags"     : [ "cpu_overheat", "cpu_heat_critical" ]
},
{
  "name"    : "Win32EventLogSource",
  "filter"  : "source AggregateFlow |
               hastype win32_eventlogs   |  
               snapshot timerange(-120 sec,+60 sec)",
  "trigger" : false
},
{
  "name"    : "Win32LoginEventProbe",
  "filter"  : "source Win32EventLogSource |
               contains Logfile 'Security' |
               contains Message 'Special privileges assigned to new logon'",
  "trigger" : true,
  "tags"    : [ "login_attempt", "win32_login" ]
},
{ 
 "name"     : "LinuxSecurityLogsProbe",
 "filter"   : "source AggregateFlow  | 
               hastype linux_securitylogs | 
               snapshot timerange(-120 sec,+60 sec) |
               contains message 'session opened'",
 "trigger"  : true,
 "tags"     : [ "login_attempt", "linux_login" ]
},
{
  "name"    : "AvailabilityProbe",
  "filter"  : "source AggregateFlow |
               hastype host_availability_readings |
               groupby host_ip |
               liveliness 30 sec",
  "trigger" : false,
  "tags"    : [ "host_availability_change" ]
},
{ 
 "name"     : "LinuxSystemLogsProbe",
 "filter"   : "source AggregateFlow | 
               hastype linux_syslogs" 
},
{ 
 "name"     : "LinuxLogsProbe",
 "filter"   : "source AggregateFlow | 
               hastype linux_logs"
},
{ 
 "name"     : "SNMPTrapsProbe",
 "filter"   : "source AggregateFlow | 
               hastype snmptraps"
},
{ 
 "name"     : "WinEventLogProbe",
 "filter"   : "source AggregateFlow | 
               hastype win32_eventlogs"
}
]
