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
using SoccerExtesions;
using System.Diagnostics;
using System.IO;
using Utility;
using RTI.RxDDS;


namespace Query1
{
    
    public static class AggregateRunningAnalysis
    {
        //aggregateRunningFullGame Query as IEnumerable<IObservable<CurrentRunningData>> extension method
        public static IList<IObservable<AggregateRunningData>> aggregateRunningDataProcessorFullGame(this IList<IObservable<CurrentRunningData>> src)
        {
            return computeAggregateRunningDataFull(src);
        }
        
        ////aggregateRunningTimeSpan Query as IEnumerable<IObservable<CurrentRunningData>> extension method
        public static IList<IObservable<AggregateRunningData>> aggregateRunningDataProcessorTimeSpan(this IList<IObservable<CurrentRunningData>> src,int timeSpanInSec)
        {
            return computeAggregateRunningDataTS(src, timeSpanInSec);
        }
        
        public static IList<IObservable<AggregateRunningData>> computeAggregateRunningDataFull(IList<IObservable<CurrentRunningData>> src)
        {
            IList<IObservable<AggregateRunningData>> aggList=new List<IObservable<AggregateRunningData>>();
            
            //tracks PerformanceTest instance for a player stream in src. 
            int pt_index = 0;
            
            foreach(var playerStream in src)
            {
                //obtain PerformanceTest instance for this player stream from PerformanceTest.ptArray.
                var pt = PerformanceTest.ptArray[pt_index]; pt_index++;
                
                aggList.Add(
                    playerStream
                    .ObserveOn(Scheduler.Default)
                    //if AggRunningStatus==true, then compute performance metrics for AggregateRunning Processor
                    .DoIf(()=>PerformanceTest.AggRunningStatus,d=>pt.recordTime())
                    //for each player do a rolling aggregate on values. 
                    .Scan(new Composite
                        {
                            toPublish = true,
                            data = new AggregateRunningData()
                            {
                                ts = 0,
                                player_id = "",
                                standing_distance = 0,
                                standing_time = 0,
                                trot_distance = 0,
                                trot_time = 0,
                                low_distance = 0,
                                low_time = 0,
                                medium_distance = 0,
                                medium_time = 0,
                                high_distance = 0,
                                high_time = 0,
                                sprint_distance = 0,
                                sprint_time = 0
                            }
                        },
                        //aggregator function 
                        (seed, curValue) =>
                        {
                            List<CurrentRunningData> expList=new List<CurrentRunningData>();
                            return aggregatorFunction
                                (seed, curValue, expList,0);
                        })               
                        //only publish if 'toPublish' field is true 
                        .Where(data => data.toPublish == true)
                        .Select(val => val.data)
                        //computes time taken to process input CurrentRunning sample into a AggregateRunning output sample
                        .DoIf(()=>PerformanceTest.AggRunningStatus,d=>pt.computeMetrics()));
                
            }
            return aggList;
        }
        
        
        
        public static IList<IObservable<AggregateRunningData>> computeAggregateRunningDataTS(IList<IObservable<CurrentRunningData>> src, int timeSpanInSec)
        {
            var givenInterval = timeSpanInSec * MetaData.SECOND_TO_PICO;
            IList<IObservable<AggregateRunningData>> aggList = new List<IObservable<AggregateRunningData>>();
            
            //tracks PerformanceTest instance for a player stream in src. 
            int pt_index = 0;

            foreach (var playerStream in src)
            {
                //obtain PerformanceTest instance for this player stream from PerformanceTest.ptArray.
                var pt = PerformanceTest.ptArray[pt_index]; pt_index++;
               
                Composite seed = new Composite
                        {
                            toPublish = true,
                            lessThanSecDist=0,
                            lessThanSecTime=0,
                            data = new AggregateRunningData
                            {
                                ts = 0,
                                player_id ="",
                                standing_distance = 0,
                                standing_time = 0,
                                trot_distance = 0,
                                trot_time = 0,
                                low_distance = 0,
                                low_time = 0,
                                medium_distance = 0,
                                medium_time = 0,
                                high_distance = 0,
                                high_time = 0,
                                sprint_distance = 0,
                                sprint_time = 0
                            }
                        };
                aggList.Add(playerStream
                    //if AggRunningStatus==true, then compute performance metrics for AggregateRunning Processor
                    .DoIf(()=>PerformanceTest.AggRunningStatus,d => pt.recordTime())
                    .TimeWindowForTsDataAggregate(givenInterval, "ts_start", seed, aggregatorFunction)                    
                    .Where(d => d.toPublish == true)
                    .Select(d => d.data)
                    //computes time taken to process input CurrentRunning sample into a AggregateRunning output sample
                    .DoIf(()=>PerformanceTest.AggRunningStatus,d=> pt.computeMetrics()));
            }
            return aggList;

        }

        //This function adds CurrentRunningData element's time/distance
        //fields to aggregateValues based on this element's intensity
        public static void addToAggregateValues(CurrentRunningData element,
            ref double standing_time, ref double standing_dist,
            ref double trot_time, ref double trot_dist,
            ref double low_time, ref double low_dist,
            ref double medium_time, ref double medium_dist,
            ref double high_time, ref double high_dist,
            ref double sprint_time, ref double sprint_dist)
        {
            switch (element.intensity)
            {
                case Intensity.STOP:
                    standing_dist += element.distance;
                    standing_time +=
                        (element.ts_stop - element.ts_start) * MetaData.PICO_TO_MILI;
                    break;
                case Intensity.TROT:
                    trot_dist += element.distance;
                    trot_time +=
                        (element.ts_stop - element.ts_start) * MetaData.PICO_TO_MILI;
                    break;
                case Intensity.LOW:
                    low_dist += element.distance;
                    low_time +=
                        (element.ts_stop - element.ts_start) * MetaData.PICO_TO_MILI;
                    break;
                case Intensity.MEDIUM:
                    medium_dist += element.distance;
                    medium_time +=
                        (element.ts_stop - element.ts_start) * MetaData.PICO_TO_MILI;
                    break;
                case Intensity.HIGH:
                    high_dist += element.distance;
                    high_time +=
                        (element.ts_stop - element.ts_start) * MetaData.PICO_TO_MILI;
                    break;
                case Intensity.SPRINT:
                    sprint_dist += element.distance;
                    sprint_time +=
                        (element.ts_stop - element.ts_start) * MetaData.PICO_TO_MILI;
                    break;
                default:
                    throw new ApplicationException("Intensity value not recognized");
            }
        }


        //This function subtracts CurrentRunningData element's time/distance
        //fields from aggregateValues based on this element's intensity
        public static void subtractFromAggregateValues(CurrentRunningData element,
            ref double standing_time, ref double standing_dist,
            ref double trot_time, ref double trot_dist,
            ref double low_time, ref double low_dist,
            ref double medium_time, ref double medium_dist,
            ref double high_time, ref double high_dist,
            ref double sprint_time, ref double sprint_dist)
        {
            switch (element.intensity)
            {
                case Intensity.STOP:
                    standing_dist -= element.distance;
                    standing_time -=
                        (element.ts_stop - element.ts_start) * MetaData.PICO_TO_MILI;
                    break;
                case Intensity.TROT:
                    trot_dist -= element.distance;
                    trot_time -=
                        (element.ts_stop - element.ts_start) * MetaData.PICO_TO_MILI;
                    break;
                case Intensity.LOW:
                    low_dist -= element.distance;
                    low_time -=
                        (element.ts_stop - element.ts_start) * MetaData.PICO_TO_MILI;
                    break;
                case Intensity.MEDIUM:
                    medium_dist -= element.distance;
                    medium_time -=
                        (element.ts_stop - element.ts_start) * MetaData.PICO_TO_MILI;
                    break;
                case Intensity.HIGH:
                    high_dist -= element.distance;
                    high_time -=
                        (element.ts_stop - element.ts_start) * MetaData.PICO_TO_MILI;
                    break;
                case Intensity.SPRINT:
                    sprint_dist -= element.distance;
                    sprint_time -=
                        (element.ts_stop - element.ts_start) * MetaData.PICO_TO_MILI;
                    break;
                default:
                    throw new ApplicationException("Intensity value not recognized");
            }

        }

        //This function updates the seed value.
        private static Composite aggregatorFunction
            (Composite seed, CurrentRunningData curValue,
            IList<CurrentRunningData> expiredList, long count)
        {
            //stash away previous seed values since the seed can't be updated in place.
            double standing_time = seed.data.standing_time,
                standing_dist = seed.data.standing_distance,
                trot_time = seed.data.trot_time,
                trot_dist = seed.data.trot_distance,
                low_time = seed.data.low_time,
                low_dist = seed.data.low_distance,
                medium_time = seed.data.medium_time,
                medium_dist = seed.data.medium_distance,
                high_time = seed.data.high_time,
                high_dist = seed.data.high_distance,
                sprint_time = seed.data.sprint_time,
                sprint_dist = seed.data.sprint_distance,
                lessThanSecDist = seed.lessThanSecDist,
                lessThanSecTime = seed.lessThanSecTime;

            //for each expired element, remove its values from previous seed's values
            foreach (var element in expiredList)
            {
                Console.WriteLine("Subtracting expired element values");
                subtractFromAggregateValues(element, ref standing_time, ref standing_dist,
                    ref trot_time, ref trot_dist, ref low_time, ref low_dist, ref medium_time,
                    ref medium_dist, ref high_time, ref high_dist, ref sprint_time, ref sprint_dist);
            }
            
            //calculate timeInterval for which current intensity was observed.
            var timeInterval =
                (curValue.ts_stop - curValue.ts_start) * MetaData.PICO_TO_MILI;
            
            //if this time interval is less than a second (1000miliseconds)
            //then current intensity values - dist and time need to be added 
            //to next intensity that is observed for more than a second.             
            if (timeInterval < 1000)
            {
                Console.WriteLine("{0} intensity observed for less than 1 sec", curValue.intensity);               
                
                //values for currentRunningData must be added to lessThanSecDist and lessThanSecTime
                //so that when next intensity range for > 1sec is observed, these values can be added 
                //to that intensity range.
                lessThanSecDist += curValue.distance;
                lessThanSecTime += timeInterval;
                
                //return updated seed.
                return new Composite
                {
                    toPublish = false,
                    lessThanSecDist=lessThanSecDist,
                    lessThanSecTime=lessThanSecTime,
                    data = new AggregateRunningData
                    {
                        player_id = curValue.player_id,
                        ts = curValue.ts_stop,
                        standing_time = standing_time,
                        standing_distance = standing_dist,
                        trot_time = trot_time,
                        trot_distance = trot_dist,
                        low_time = low_time,
                        low_distance = low_dist,
                        medium_time = medium_time,
                        medium_distance = medium_dist,
                        high_time = high_time,
                        high_distance = high_dist,
                        sprint_time = sprint_time,
                        sprint_distance = sprint_dist
                    }
                };
            }
            else
            {
                //if lessThanSecDist and lessThanSecTime >0 then there were 
                //intensities which were observed for less than a second. 
                //Their values need to be added to the current intensity bracket.
                if (lessThanSecDist > 0 && lessThanSecTime > 0)
                {
                    curValue.distance += lessThanSecDist;
                    curValue.ts_stop += (long)(lessThanSecTime / MetaData.PICO_TO_MILI);
                    lessThanSecDist = 0; lessThanSecTime = 0;
                }

                //add current values to previous seed values
                addToAggregateValues(curValue, ref standing_time, ref standing_dist,
                    ref trot_time, ref trot_dist, ref low_time, ref low_dist, ref medium_time,
                    ref medium_dist, ref high_time, ref high_dist, ref sprint_time, ref sprint_dist);
                //return updated seed.
                return new Composite
                {
                    toPublish = true,
                    lessThanSecDist=lessThanSecDist,
                    lessThanSecTime=lessThanSecTime,
                    data = new AggregateRunningData
                    {
                        player_id = curValue.player_id,
                        ts = curValue.ts_stop,
                        standing_time = standing_time,
                        standing_distance = standing_dist,
                        trot_time = trot_time,
                        trot_distance = trot_dist,
                        low_time = low_time,
                        low_distance = low_dist,
                        medium_time = medium_time,
                        medium_distance = medium_dist,
                        high_time = high_time,
                        high_distance = high_dist,
                        sprint_time = sprint_time,
                        sprint_distance = sprint_dist
                    }
                };
            
            }//end of else block
        
        }//end of aggregatorFunction
       
        private struct Composite
        {
            public bool toPublish;
            public double lessThanSecTime;
            public double lessThanSecDist;            
            public AggregateRunningData data;
        };
  }

}



