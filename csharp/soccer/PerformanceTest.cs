using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Diagnostics;
using System.IO;

namespace Utility
{
    class PerformanceTest
    {
                
        public static long NS_PER_TICK = (1000L * 1000L * 1000L) / Stopwatch.Frequency;
        
        //stores PerformanceTest object for each player stream/player. 
        public static PerformanceTest[] ptArray;
        
        //stopwatch for recording throughput.
        private static Stopwatch throughput_sw = new Stopwatch();
        
        //status variables for different queries. If set to true, then performance metrics will 
        //be calculated for that query
        public static bool AvgProcessorStatus { get; set; }
        public static bool CurrRunningStatus { get; set; }
        public static bool AggRunningStatus { get; set; }
        public static bool HeatMapStatus { get; set; }

        //used for keeping track of number of input samples received. 
        public long InputCount { get; set; }
        //used for keeping track of number of output samples produced. 
        public long OutputCount { get; private set; }     
        
        //used for storing sum of computation time. 
        public double SumComputationTime { get; private set; }
        //for keeping track of min computation time 
        public double MinComputationTime { get; private set; }
        //for keeping track of max computation time. 
        public double MaxComputationTime { get; private set; }
        //stopwatch for latency calculation 
        private Stopwatch sw;
        //stores time at which input sample is received. 
        private long prev_time;

        public PerformanceTest()
        {           
            InputCount = 0; OutputCount = 0;
            SumComputationTime = 0; MinComputationTime = Double.MaxValue; MaxComputationTime = Double.MinValue;
            prev_time = -1;            
            sw = Stopwatch.StartNew();
        }
        
        //creates ptArray used for storing PerformanceTest obj per Player/player stream 
        public static void  initializePtArr()
        {
            PerformanceTest[] arr = new PerformanceTest[MetaData.PLAYER_MAP.Count];
            for (var i = 0; i < MetaData.PLAYER_MAP.Count; i++)
                arr[i] = new PerformanceTest();
            ptArray = arr;
          
        }
        
        //records time at which input sample arrives. 
        public void recordTime()
        {
            prev_time = sw.ElapsedTicks;
        }

        //calculates latency value(computation time) and keeps track of sum of computation times,min/max 
        public double computeMetrics()
        {
            OutputCount++;            
            long curr_time = sw.ElapsedTicks;
            double computation_time_microSec = ((curr_time - prev_time)* NS_PER_TICK) / 1000.0;            
            
            SumComputationTime += computation_time_microSec;
            if (computation_time_microSec < MinComputationTime)
                MinComputationTime = computation_time_microSec;
            if (computation_time_microSec > MaxComputationTime)
                MaxComputationTime = computation_time_microSec;           
            
            return computation_time_microSec;          
          
        }
        //starts throughput stop watch
        public static void startThroughputSW()
        {
            throughput_sw.Start();
        }
        //stops throughput stop watch 
        public static void stopThroughputSW()
        {
            throughput_sw.Stop();
        }

        //computes throughput observed, average latency measurement from results of
        //PerformanceTest variables associated with each player/player stream.Outupt 
        //results are written to "file_name". 
        public static void postProcess(string file_name)
        {
            
            throughput_sw.Stop();
            long tot = 0; double sum_comp_time = 0;
            double min_time = Double.MaxValue, max_time = Double.MinValue;
            
            foreach (var ele in PerformanceTest.ptArray)
            {
                    if (ele.MinComputationTime < min_time)
                        min_time = ele.MinComputationTime;
                    if (ele.MaxComputationTime > max_time)
                        max_time = ele.MaxComputationTime;
                    tot += ele.OutputCount;
                    sum_comp_time += ele.SumComputationTime;
             }
            double throughput = (double)(tot * 1000 * 1000 * 1000) 
                / (double)(throughput_sw.ElapsedTicks * PerformanceTest.NS_PER_TICK);

            
            using (StreamWriter file = new StreamWriter("D:\\" + file_name + ".txt"))
            {
                file.WriteLine("total:{0}. Avg time:{1}", tot, sum_comp_time / tot);
                file.WriteLine("Min computation time in micro-sec: " + min_time);
                file.WriteLine("Max computation time in micro-sec: " + max_time);

                file.WriteLine("\nThroughput samples/sec: " + throughput);
                file.WriteLine("Total time taken in seconds: " + throughput_sw.ElapsedMilliseconds / 1000.0);  
               
            }
                  
        }

        
        

    }
}
