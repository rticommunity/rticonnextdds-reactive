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
using System.Diagnostics;
using System.IO;
using Utility;
using RTI.RxDDS;

namespace Query1
{
  
    public static class CurrentRunningAnalysisQuery
    {        
        
        public static IList<IObservable<CurrentRunningData>> computeCurrentRunningData(IList<IObservable<PlayerData>> inp)
        {
            List<IObservable<CurrentRunningData>> currentRunningList = new List<IObservable<CurrentRunningData>>();

            //tracks PerformanceTest instance for a player stream.
            int pt_index = 0;
            
            foreach(var playerStrm in inp)
            {
                //obtain PerformanceTest instance for this player stream from PerformanceTest.ptArray.
                var pt = PerformanceTest.ptArray[pt_index]; pt_index++;

                string player_name="";

                currentRunningList.Add(
                    playerStrm
                        .ObserveOn(Scheduler.Default)
                        //if CurrRunningStatus==true, then compute performace metrics for CurrentRunningAnalyzer.
                        .DoIf(() => PerformanceTest.CurrRunningStatus, d => pt.recordTime())
                        .Scan(new Aggregate
                                {
                                    ts_start = -1,
                                    ts_end = -1,
                                    pos_x = -1,
                                    pos_y = -1,
                                    dist = -1,
                                    speed = -1
                                }, (seed, currData) =>
                                {
                                    player_name = currData.player_name;
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
                                            player_id = player_name,
                                            distance = agg.dist / 1000000,//dist in Km
                                            speed = agg.speed,
                                            intensity = MetaData.returnRunningIntensity(agg.speed)
                                        };
                                    })
                             //compute time to produce a CurrentRunningData sample from input PlayerData sample 
                            .DoIf(() => PerformanceTest.CurrRunningStatus, d => pt.computeMetrics()));
                                    
            }
            return currentRunningList;

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

        //CurrentRunningAnalysisQuery as IEnumerable<IObservable<PlayerData>> extension method. 
        public static IList<IObservable<CurrentRunningData>> currentRunningProcessor(this IList<IObservable<PlayerData>> src)
        {
            return computeCurrentRunningData(src);
        }


    }

}












    