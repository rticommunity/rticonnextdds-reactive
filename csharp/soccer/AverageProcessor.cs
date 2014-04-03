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


namespace Queries
{
    class AverageProcessor
    {
        /**
         * This function averages the sensor values of sensors attached to a player and returns 
         * it as a stream of PlayerData in 'sub' which is Subject<PlayerData> passed by reference.
         */
        public static void sensorToPlayerAverageProcessor(ref Subject<SensorData> src, 
            ref Subject<PlayerData> sub)
        {

           
            //for each player in MetaData.PLAYER_MAP
            foreach (var keypair in MetaData.PLAYER_MAP)
            {
                //Extract the list of sensors attached to this player               
                var sensorList = keypair.Value;
                
                //Create a list of SensorData streams associated with each sensor in sensorList
                List<IObservable<SensorData>> sensorStreamList = new 
                    List<IObservable<SensorData>>();

                //for each sensor in sensorList
                foreach (var val in sensorList)
                    //Add stream associated with this sensor's sensor_id
                    sensorStreamList
                        .Add(src
                        .Where(ss => ss.sensor_id == val)
                        //Emit one default value at the beginning of this 
                        //sensor stream to be able to get PlayerData 
                        //for each player even if one of his sensor's 
                        //data doesn't show up until later in the game.
                        .Once(new SensorData{
                            ts= -99999,
                            sensor_id=val,
                            pos_x= -99999,
                            pos_y= -99999,
                            pos_z = -99999,
                            vel = -99999,
                            accel = -99999,
                            vel_x = -99999,
                            vel_y = -99999,
                            vel_z = -99999,
                            accel_x = -99999,
                            accel_y = -99999,
                            accel_z = -99999
                        }));
                Console.WriteLine("Emitting data for {0}", keypair.Key);
                //emit PlayerData for each player. 
                
                Observable                      
                    .CombineLatest(sensorStreamList)                     
                    .Select(lst => returnPlayerData(lst))
                    .Where(data=> !String.IsNullOrEmpty(data.player_name))
                    .Subscribe(sub);
            }
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
            if (count !=0)
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
            else
                return new PlayerData
                {
                    player_name ="",
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

    
    
    
    }//end of class: AverageProcessor


}//end of namespace: Queries
