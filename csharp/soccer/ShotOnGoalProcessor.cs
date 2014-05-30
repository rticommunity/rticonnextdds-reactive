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
using System.Diagnostics;
using System.IO;
using Utility;
using Query2;

namespace Query4
{
    public static class ShotOnGoalProcessor
    {

        //ShotonGoal Query as IObservable<SensorData> extension 
        public static IObservable<ShotOnGoalData> shotOnGoalProcessor(this IObservable<SensorData> src,
            ref Subject<BallPossessionQuery.EventInfo> eventInfoStream)
        {
            return computeShotOnGoal(src, ref eventInfoStream);
        }


        public static IObservable<ShotOnGoalData> computeShotOnGoal(IObservable<SensorData> src,
            ref Subject<BallPossessionQuery.EventInfo> eventInfoStream)            
        {
            return eventInfoStream
                .Select(data =>
                    {
                        if (data.state.Equals("hit"))
                        {
                            //Console.WriteLine(data.player_id);
                            //calculate the component velocities along x, y and z axis. 
                            double x_vel = (data.ballData.vel * data.ballData.vel_x)
                                / MetaData.VEL_COMPONENT_FACTOR;
                            double y_vel = (data.ballData.vel * data.ballData.vel_y)
                                / MetaData.VEL_COMPONENT_FACTOR;
                            double z_vel = (data.ballData.vel * data.ballData.vel_z)
                                / MetaData.VEL_COMPONENT_FACTOR;

                            //calculate projected ball position after 1.5 seconds 
                            double x_projection = data.ballData.pos_x / 1000.0 + x_vel * 1.5;
                            double y_projection = data.ballData.pos_y / 1000.0 + y_vel * 1.5
                                - (0.5 * MetaData.GRAVITY * 1.5 * 1.5);
                            double z_projection = data.ballData.pos_z / 1000.0 + z_vel * 1.5;

                            //check if the ball's projected position will fall within goal-post areas
                            if (checkProjection(x_projection, y_projection, z_projection))
                                //if so there is a shot-on-goal
                                return new
                                {
                                    shot_on_goal = true,
                                    player_id = data.player_id,
                                    ball_id = data.ball_sensor_id,
                                    ball_ts = data.ballData.ts
                                };
                            else
                                //if projected ball position does not lie in goal post areas then shot_on_goal=false
                                return new
                                {
                                    shot_on_goal = false,
                                    player_id = data.player_id,
                                    ball_id = data.ball_sensor_id,
                                    ball_ts = data.ballData.ts
                                };
                        }
                        else
                        {
                            //in case the EventInfo state is ballOutofFieldOrEnded, then shot_on_goal=false
                            return new
                            {
                                shot_on_goal = false,
                                player_id = data.player_id,
                                ball_id = data.ball_sensor_id,
                                ball_ts = data.ballData.ts
                            };
                        }

                    })
                    .CombineLatest(src.Where(d => MetaData.BALL_SENSOR_IDS.Contains(d.sensor_id)),
                    (a, b) =>
                    {
                        //only publish ball data when shot_on_goal=true 
                        //and the ball's ts >= when shot on goal was detected for the ball on field. 
                        if (a.shot_on_goal && (a.ball_id == b.sensor_id) && (b.ts >= a.ball_ts))
                        {
                            return new { to_publish = true, player_id = a.player_id, ballData = b };
                        }
                        else
                            return new { to_publish = false, player_id = a.player_id, ballData = b };

                    })
                    .Where(d => d.to_publish == true)
                    .Select(d =>
                        {
                            //publish ball information while shot_on_goal state is active.                             
                            return new ShotOnGoalData
                            {
                                ts = d.ballData.ts,
                                player_id = d.player_id,
                                pos_x = d.ballData.pos_x,
                                pos_y = d.ballData.pos_y,
                                pos_z = d.ballData.pos_z,
                                vel = d.ballData.vel,
                                vel_x = d.ballData.vel_x,
                                vel_y = d.ballData.vel_y,
                                vel_z = d.ballData.vel_z,
                                accel = d.ballData.accel,
                                accel_x = d.ballData.accel_x,
                                accel_y = d.ballData.accel_y,
                                accel_z = d.ballData.accel_z
                            };
                        });
      
        }        
        
        //this function checks whether the projected ball position will fall within defined goal-post areas. 
        private static bool checkProjection(double x_projection, double y_projection, double z_projection)
        {
            bool towardsA = x_projection >= MetaData.A_X_MIN && x_projection <= MetaData.A_X_MAX &&
                                    y_projection <= MetaData.A_Y && z_projection < MetaData.A_Z;
            bool towardsB = x_projection >= MetaData.B_X_MIN && x_projection <= MetaData.B_X_MAX &&
                                    y_projection >= MetaData.B_Y && z_projection < MetaData.B_Z;
            return (towardsA || towardsB);
        }
    }
}
