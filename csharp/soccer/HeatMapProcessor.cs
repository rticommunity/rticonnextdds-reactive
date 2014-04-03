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
using System.Reactive.Linq;
using System.Reactive.Subjects;
using SoccerExtesions;

namespace Queries
{
    class HeatMapProcessor
    {
        public static void heatMap(ref Subject<PlayerData> src)
        {        
           
            src
                .SelectMany(pData =>
                {
                    //correct x and y co-ordinates of playerdata. 
                    double x = pData.pos_x < 0 ? 0 : pData.pos_x;
                    double y = pData.pos_y + MetaData.Y_OFFSET;
                    if (y < 0)
                        y = y * -1;

                    //for each player's position find out the grid_cell index that the 
                    //player is in for each of the 4 grid_dimensions. 
                    List<GridInfo> output = new List<GridInfo>();
                    for (int i = 0; i < 4; i++)
                    {
                        int x_row = (int)Math.Ceiling(x / (MetaData.LEN_X / MetaData.X_DIM[i]));
                        int y_col = (int)Math.Ceiling(y / (MetaData.LEN_Y / MetaData.Y_DIM[i]));

                        output.Add(new GridInfo
                        {
                            gridType = i,
                            player_name = pData.player_name,
                            ts = pData.ts,
                            index = (x_row - 1) + (y_col - 1) * MetaData.X_DIM[i],

                        });
                    }
                    return output;
                })
                //groupby on both gridType and player_name fields
                .GroupBy(d => d.gridType + d.player_name)
                .Subscribe(player_grid_stream =>
                    {
                        player_grid_stream
                            .Scan(new TimeInCell
                                {
                                    ts = -1,
                                    player_name = "",
                                    gridType = -1,
                                    prev_index = -1,
                                    time_in_cell = -999,
                                    curr_index = -1,
                                },
                               (seed, curr) =>
                               {
                                   //This function calculates the time for which the player was in gird_cell prev_index 
                                   //as observed at timestamp ts when player is in grid_cell curr_index                                   
                                   TimeInCell new_seed = new TimeInCell
                                   {
                                       ts = curr.ts,
                                       player_name = curr.player_name,
                                       gridType = curr.gridType,
                                       prev_index = seed.curr_index,
                                       curr_index = curr.index,
                                       time_in_cell = -999
                                   };
                                   if (new_seed.prev_index == -1)
                                       new_seed.prev_index = curr.index;
                                   else
                                   {
                                       new_seed.time_in_cell = (curr.ts - seed.ts)
                                           / MetaData.PICO_TO_MILI;

                                   }
                                   return new_seed;
                               })
                               //computes heatMapData for the timeframe of 5 seconds. 
                               .TimeWindowForTsDataAggregate(5 * MetaData.SECOND_TO_PICO, "ts",
                                new HeatMapData
                                {
                                    ts = -1,
                                    player_name = "",
                                    gridType = -1,
                                    heatmap = new Dictionary<int, double>()
                                },
                                aggregatorFunction)
                                .Subscribe(data => printInfo(data));
                                        
                    });          
          
        }

        //aggregatorFunction used in TimeWindow based aggregation 
        private static HeatMapData aggregatorFunction(HeatMapData seed, TimeInCell curr,
           IList<TimeInCell> expList, long count)
        {
            HeatMapData new_seed = new HeatMapData { ts = curr.ts, player_name = curr.player_name,
                gridType=curr.gridType, heatmap = seed.heatmap};            
            
            foreach(var item in expList)
            {                
                if (item.time_in_cell != -999)
                {
                    
                    if (new_seed.heatmap.ContainsKey(item.prev_index))
                    {
                        new_seed.heatmap[item.prev_index] -= item.time_in_cell;
                        if (new_seed.heatmap[item.prev_index] <= 0)
                            new_seed.heatmap.Remove(item.prev_index);
                    }
                    else
                    {
                        Console.WriteLine("attempt to access non-existent key");
                    }
                    
                }                
                
            }
            if (curr.time_in_cell != -999)
            {
                if (new_seed.heatmap.ContainsKey(curr.prev_index))                
                    new_seed.heatmap[curr.prev_index] += curr.time_in_cell;       
                else
                    new_seed.heatmap.Add(curr.prev_index, curr.time_in_cell);                            
                
            }
            return new_seed;
        }  

        //function for printing out HeatMap structure data 
        public static void printInfo(HeatMapData data)
        {
           double total_time = 0;
           Console.WriteLine("\nts: " + data.ts);
           
           Console.WriteLine("player_name: " + data.player_name);
           
            Console.WriteLine("gridType: " + data.gridType);
           foreach (var item in data.heatmap)
                total_time += item.Value;
           foreach (var item in data.heatmap)
                Console.WriteLine("index: " + item.Key + "  time % : " + (item.Value / total_time) * 100);                                                                     
        }
    
        //This structure stores the final HeatMap data. 
        public struct HeatMapData
        {
            public Int64 ts;
            public string player_name;
            //gridType is 0 for 8*13, 1 for 16*25, 2 for 32*50 and 3 for 64*100
            public int gridType;
            //this stores map of occupancy time to grid_cell index 
            public Dictionary<int,double> heatmap;            
        };
        
        //This structure stores the time for which the player was in gird_cell prev_index 
        //as observed at timestamp ts when player is in grid_cell curr_index
        public struct TimeInCell
        {
            public Int64 ts;
            //gridType is 0 for 8*13, 1 for 16*25, 2 for 32*50 and 3 for 64*100
            public int gridType;
            public string player_name;
            public int prev_index;
            //length of time for which player was in prev_index
            public double time_in_cell;
            //grid_cell in which the player is in currently at timestamp ts. 
            public int curr_index;
        };
        
        //This structure stores at which grid_cell index a player is in
        public struct GridInfo
        {
            public Int64 ts;
            //gridType is 0 for 8*13, 1 for 16*25, 2 for 32*50 and 3 for 64*100
            public int gridType;
            public string player_name;
            //index of grid_cell in which the player is in.
            public int index;                        
        }
       
    
    }
}



