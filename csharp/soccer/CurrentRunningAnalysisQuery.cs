/*********************************************************************************************
(c) 2005-2014 Copyright, Real-Time Innovations, Inc.  All rights reserved.                                  
RTI grants Licensee a license to use, modify, compile, and create derivative works 
of the Software.  Licensee has the right to distribute object form only for use with RTI 
products.  The Software is provided “as is”, with no warranty of any type, including 
any warranty for fitness for any purpose. RTI is under no obligation to maintain or 
support the Software.  RTI shall not be liable for any incidental or consequential 
damages arising out of the use or inability to use the software.
**********************************************************************************************/

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Reactive.Subjects;
using System.Reactive.Linq;
using System.Reactive.Concurrency;
using System.Threading;
using System.Reactive.PlatformServices;

namespace Queries
{
    class CurrentRunningAnalysisQuery
    {
        /*
         *This function emits currentRunnningData for a player by observing the current
         *and previous PlayerData values. The emitted currentRunningData comprises of 
         *ts_start and ts_end, averageSpeed over this time-interval,running intensity 
         *observed for this time-interval and distance travelled.
         */
        public static void currentRunningDataProcessor(ref Subject<PlayerData> sub,
            ref Subject<CurrentRunningData> output)
        {            
            
            sub.
                GroupBy(data => data.player_name)
                //.ObserveOn(Scheduler.Default)
                .SelectMany(player_stream =>
                    {
                        return player_stream                            
                            .Scan(
                            new Aggregate
                            {
                                ts_start = -1,
                                ts_end = -1,
                                pos_x = -1,
                                pos_y = -1,
                                dist = -1,
                                speed = -1
                            },
                            (seed, currData) =>
                            {
                                
                                double distance = -1, avgSpeed = -1;
                                var prev_ts = seed.ts_end;
                                var curr_ts = currData.ts;
                                if (prev_ts != -1 && curr_ts != -1)
                                {
                                    //Get Distance travelled in mm
                                    distance = MetaData.returnDistance(seed.pos_x, seed.pos_y,
                                        currData.pos_x, currData.pos_y);
                                    Int64 timeSpan = curr_ts - prev_ts;
                                    //avgSpeed in km/hr
                                    if (timeSpan != 0)
                                        avgSpeed = (distance / timeSpan) * 3.6 * 1000000000;

                                }
                                return new Aggregate
                                {
                                    ts_start = seed.ts_end,
                                    ts_end = currData.ts,
                                    pos_x = currData.pos_x,
                                    pos_y = currData.pos_y,
                                    dist = distance,
                                    speed = avgSpeed

                                };
                            })
                            .Where(data => (data.ts_end != -1 && data.ts_start != -1))
                            .Select(agg =>
                                    {
                                        
                                        return new CurrentRunningData
                                        {
                                            ts_start = agg.ts_start,
                                            ts_stop = agg.ts_end,
                                            player_id = player_stream.Key,
                                            distance = agg.dist / 1000000,//dist in Km
                                            speed = agg.speed,
                                            intensity = MetaData.returnRunningIntensity(agg.speed)

                                        };
                                    });
                    }).Subscribe(output);
        }

        private struct Aggregate
        {
            public Int64 ts_start;
            public Int64 ts_end;
            public double pos_x;
            public double pos_y;
            public double dist;
            public double speed;
        };       
        
    }
}










    