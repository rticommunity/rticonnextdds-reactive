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
using System.Reactive;
using System.Reactive.Linq;
using System.Reactive.Subjects;
using System.Reactive.Concurrency;
using System.Reactive.PlatformServices;
using RTI.RxDDS;
using System.Diagnostics;
using System.IO;
using Utility;




namespace Temp
{
    
    public static class AverageProcessor
    {
        public static IObservable<PlayerData> computePlayerData(IObservable<SensorData> src)
        {                  
            var res=MetaData.PLAYER_MAP.Values.ToObservable().Select(lst =>
            {               
                IList<IObservable<SensorData>> ret = new List<IObservable<SensorData>>();
                foreach (var val in lst)
                    ret.Add(src.Where(d=>d.sensor_id==val).Once(MetaData.getDefaultSensorDataWithSensorID(val)));
                return ret;
            });

            return res.SelectMany(d =>
            {
                return Observable
                    .CombineLatest(d)
                    .Select(lst =>
                    {
                        var r = returnPlayerData(lst);
                        Console.WriteLine(r.player_name);
                        return r;
                    });
            });      
      
        }

        public static PlayerData returnPlayerData(IList<SensorData> values)
        {
            double pos_x = 0, pos_y = 0, pos_z = 0, vel = 0, accel = 0,
                vel_x = 0, vel_y = 0, vel_z = 0, accel_x = 0,
                accel_y = 0, accel_z = 0;
            Int64 ts_max = 0;

            string player_name = MetaData.SENSOR_MAP[values.ElementAt(0).sensor_id];
            var count = values.Count;

            foreach (var value in values)
            {
                if (value.ts == -99999)
                {
                    count--;
                    continue;
                }

                if (value.ts >= ts_max)
                    ts_max = value.ts;
                pos_x += value.pos_x;
                pos_y += value.pos_y;
                pos_z += value.pos_z;
                vel += value.vel;
                accel += value.accel;
                vel_x += value.vel_x;
                vel_y += value.vel_y;
                vel_z += value.vel_z;
                accel_x += value.accel_x;
                accel_y += value.accel_y;
                accel_z += value.accel_z;
            }
            if (count != 0)
            {

                return new PlayerData
                {
                    player_name = player_name,
                    ts = ts_max,
                    pos_x = (pos_x / count),
                    pos_y = (pos_y / count),
                    pos_z = (pos_z / count),
                    vel = (vel / count),
                    accel = (accel / count),
                    vel_x = (vel_x / count),
                    vel_y = (vel_y / count),
                    vel_z = (vel_z / count),
                    accel_x = (accel_x / count),
                    accel_y = (accel_y / count),
                    accel_z = (accel_z / count)
                };
            }
            else
                return new PlayerData
                {
                    player_name = "",
                    ts = ts_max,
                    pos_x = (pos_x),
                    pos_y = (pos_y),
                    pos_z = (pos_z),
                    vel = (vel),
                    accel = (accel),
                    vel_x = (vel_x),
                    vel_y = (vel_y),
                    vel_z = (vel_z),
                    accel_x = (accel_x),
                    accel_y = (accel_y),
                    accel_z = (accel_z)
                };


        }//end of function: returnPlayerData
    }
}


namespace Average
{
    
    public static class AverageProcessor
    {       
        
        public static IList<IObservable<PlayerData>> computePlayerData(IObservable<SensorData> src)
        {           
            List<IObservable<PlayerData>> playerStreamList = new List<IObservable<PlayerData>>();
            
            //tracks PerformanceTest instance for a player stream. 
            int pt_index=0;
            
            foreach (var keypair in MetaData.PLAYER_MAP)
            {
                //obtain PerformanceTest instance for this player from PerformanceTest.ptArray.
                var pt = PerformanceTest.ptArray[pt_index]; pt_index++;
                
                string player_name = keypair.Key;
                //Extract the list of sensors attached to this player               
                var sensorList = keypair.Value;

                //Create a list of SensorData streams associated with each sensor in sensorList
                List<IObservable<SensorData>> sensorStreamList = new
                    List<IObservable<SensorData>>();

                //for each sensor in sensorList
                foreach (var val in sensorList)
                {                    
                    //Add stream associated with this sensor's sensor_id
                    sensorStreamList
                        .Add(src
                        .Where(ss =>ss.sensor_id==val)                            
                        //Emit one default value at the beginning of this 
                        //sensor stream to be able to get PlayerData 
                        //for each player even if one of his sensor's 
                        //data doesn't show up until later in the game.
                        .Once(MetaData.getDefaultSensorDataWithSensorID(val)));
                }

                //emit PlayerData for each player.         

                playerStreamList.Add(
                    Observable                                        
                    .Zip(sensorStreamList)
                    //If AvgProcessorStatus==true, then compute performance metrics for AverageProcessor. 
                    .DoIf(()=> PerformanceTest.AvgProcessorStatus,d=> pt.recordTime())                        
                    .Select(lst =>
                    {
                        return returnPlayerData(lst);
                    })
                    .Where(data => !String.IsNullOrEmpty(data.player_name))
                    //compute time taken to produce a PlayerData sample from list of updated sensor values. 
                    .DoIf(()=>PerformanceTest.AvgProcessorStatus, d=>pt.computeMetrics()));
                                       
            }
            
            return playerStreamList;
        }

        //This function averages out the fields in SensorData structures 
        //containted in the list.The result is returned as a PlayerData type. 
        public static PlayerData returnPlayerData(IList<SensorData> values)
        {
            double pos_x = 0, pos_y = 0, pos_z = 0, vel = 0, accel = 0,
                vel_x = 0, vel_y = 0, vel_z = 0, accel_x = 0,
                accel_y = 0, accel_z = 0;
            Int64 ts_max = 0;

            string player_name = MetaData.SENSOR_MAP[values.ElementAt(0).sensor_id];
            var count = values.Count;

            foreach (var value in values)
            {
                if (value.ts == -99999)
                {
                    count--;
                    continue;
                }

                if (value.ts >= ts_max)
                    ts_max = value.ts;
                pos_x += value.pos_x;
                pos_y += value.pos_y;
                pos_z += value.pos_z;
                vel += value.vel;
                accel += value.accel;
                vel_x += value.vel_x;
                vel_y += value.vel_y;
                vel_z += value.vel_z;
                accel_x += value.accel_x;
                accel_y += value.accel_y;
                accel_z += value.accel_z;
            }
            if (count != 0)
            {
                
                return new PlayerData
                {
                    player_name = player_name,
                    ts = ts_max,
                    pos_x = (pos_x / count),
                    pos_y = (pos_y / count),
                    pos_z = (pos_z / count),
                    vel = (vel / count),
                    accel = (accel / count),
                    vel_x = (vel_x / count),
                    vel_y = (vel_y / count),
                    vel_z = (vel_z / count),
                    accel_x = (accel_x / count),
                    accel_y = (accel_y / count),
                    accel_z = (accel_z / count)
                };
            }
            else
                return new PlayerData
                {
                    player_name = "",
                    ts = ts_max,
                    pos_x = (pos_x),
                    pos_y = (pos_y),
                    pos_z = (pos_z),
                    vel = (vel),
                    accel = (accel),
                    vel_x = (vel_x),
                    vel_y = (vel_y),
                    vel_z = (vel_z),
                    accel_x = (accel_x),
                    accel_y = (accel_y),
                    accel_z = (accel_z)
                };


        }//end of function: returnPlayerData

        //averageProcessor Query as an IObservable<SensorData> Extension method 
        public static IList<IObservable<PlayerData>> averageProcessor(this IObservable<SensorData> src)
        {
            return computePlayerData(src);
        }

    }   

}


