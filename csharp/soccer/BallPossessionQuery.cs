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
using RTI.RxDDS;

namespace Queries
{
    class BallPossessionQuery
    {
       
        public static void ballPossessionProcessor(ref Subject<SensorData> src,
            ref Subject<PlayerBallPossession>output, ref Subject<EventInfo> eventInfoStream)            
        {

            Console.WriteLine("inside ballPossessionProcessor");
                      
            //for keeping track of active ball sensor_id
            int ballSensorId = -1;
            //for keeping track of player who is in possession of ball currently
            string playerWithBallPossession = "";
            //for keeping track of number of hits for each player
            Dictionary<string, int> playerHitsMap = initializeHitsDictionary();
            //for keeping track of last ts of ball hit for each player
            Dictionary<string, Int64> playerTsMap = initializeTsDictionary();
            //for keeping track of possession time of ball for each player 
            Dictionary<string, double> playerPossessionTimeMap = initializePossessionTimeDictionary();           
            

            //for publishing possession state changes. 
            //Subject<EventInfo> stateInfoSub = new Subject<EventInfo>();
            
            //This list will hold references to sensor streams for all the sensors that 
            //are attached to a player
            List<IObservable<SensorData>> playerStreamList = getPlayerStreamList(ref src);

                      

            //reference to ball sensor data stream 
            var ball = src
            .Where(data => MetaData.BALL_SENSOR_IDS.Contains(data.sensor_id))
            .Once(MetaData.getDefaultSensorData())
            .Select(ballData =>
            {            
                return new
                {
                    isTsValid=MetaData.isTsValid(ballData.ts),
                    inField = MetaData.inField(ballData.pos_x, ballData.pos_y),
                    ballData = ballData
                };
            });

            Observable
                //obtain latest data sample for all player sensors 
                .CombineLatest(playerStreamList)
                //obtain latest ball sensor data 
                .CombineLatest(ball.Where(d => (d.ballData.ts != -99999) ),                                            
                    (a, b) =>                   
                    {                       
                        //initialize min_distance to ball
                        double min_distance = double.MaxValue;
                        //initialize sensor_id of sensor that is at min_distance to ball
                        int min_dist_sensor_id = -1;
                        //initialize sensor data for the min_dist_sensor 
                        SensorData min_dist_Player = MetaData.getDefaultSensorData();                      
                        

                        min_dist_Player=a
                            .Where(val=>val.ts !=-99999)
                            .Aggregate((x, y) =>
                            {
                                double dist1 = MetaData
                               .returnDistance(b.ballData.pos_x, b.ballData.pos_y, x.pos_x, x.pos_y);
                                double dist2 = MetaData
                                .returnDistance(b.ballData.pos_x, b.ballData.pos_y, y.pos_x, y.pos_y);
                                if (dist1 < dist2)
                                {
                                    min_distance = dist1;
                                    return x;
                                }
                                else
                                {
                                    min_distance = dist2;
                                    return y;
                                }
                            });
                        if (min_dist_Player.ts == -99999)
                        {
                            //no valid player sensor data was observed yet
                            return new EventInfo
                            {
                                state = "invalid",
                                player_id ="",
                                ts = min_dist_Player.ts,
                                ball_sensor_id =b.ballData.sensor_id,
                                ballData=b.ballData
                            };
                        }
                                                
                        min_dist_sensor_id = min_dist_Player.sensor_id;                        
                       
                        //find out if the present state is valid. i.e. the current ball sensor is in field 
                        //and the ts of ball sensor and min_dist player sensor are within correct bounds 
                                               
                        var isValid = b.isTsValid && b.inField && MetaData.isTsValid(min_dist_Player.ts);
                                                
                        //if the game state is valid- find out if there was a hit on the ball 
                        if (isValid)
                        {
                            //hit state 
                            if (min_distance < 1000 && ((b.ballData.accel / 1000000) >= 55.0))
                            {
                                return new EventInfo
                                {
                                    state = "hit",
                                    player_id = MetaData.SENSOR_MAP[min_dist_sensor_id],
                                    ts = min_dist_Player.ts,
                                    ball_sensor_id=b.ballData.sensor_id,
                                    ballData=b.ballData
                                };
                            }
                            //empty state 
                            else 
                            {
                                return new EventInfo
                                {
                                    state = "empty",
                                    player_id = MetaData.SENSOR_MAP[min_dist_sensor_id],
                                    ts = min_dist_Player.ts,
                                    ball_sensor_id=b.ballData.sensor_id,
                                    ballData=b.ballData
                                };

                            }
                        }
                        //game state is invalid either due to current ball is not in field or ts of
                        //ball and/or player sensors are out of bounds 
                        else
                            return new EventInfo
                            {
                                state = "outOfFieldOrEnded",
                                player_id = MetaData.SENSOR_MAP[min_dist_sensor_id],
                                ts = min_dist_Player.ts,
                                ball_sensor_id=b.ballData.sensor_id,
                                ballData=b.ballData
                            };

                    }).Where(data =>
                    {   
                        //possession state changes only occur on a hit or if game ends/ball out of field
                        return !(data.state.Equals("empty") || data.state.Equals("invalid"));
                    }).Subscribe(eventInfoStream);
                                   

            
            eventInfoStream.SelectMany(data =>
                  {
                      if (data.state.Equals("outOfFieldOrEnded"))
                      {
                          //the player who possesses the ball hits it out of the field and 
                          //the outOfFieldOrEnded state is for the active ball.
                          if (data.player_id.Equals(playerWithBallPossession)
                              && data.ball_sensor_id == ballSensorId)
                          {
                              //increment this players hit count
                              playerHitsMap[data.player_id] += 1;
                              //increment this player's possession time.
                              playerPossessionTimeMap[data.player_id] = data.ts - playerTsMap[data.player_id];
                              //No player is currently in possession of the ball
                              playerWithBallPossession = "";
                              //the ball is no longer active in field
                              ballSensorId = -1;

                              //publish state change 
                              return new List<Update>
                                {
                                    new Update{
                                    toPublish = true,
                                    possessionData = new PlayerBallPossession
                                        {
                                            player_id = data.player_id,
                                            time = playerPossessionTimeMap[data.player_id],
                                            hits = playerHitsMap[data.player_id],
                                            ts = data.ts
                                        }
                                    }
                                };
                          }
                      }
                      else//data.state=="hit"
                      {
                          //If the same player who had the ball before hits active ball again.
                          if (data.player_id.Equals(playerWithBallPossession) && ballSensorId == data.ball_sensor_id)
                          {
                              //increment hit count 
                              playerHitsMap[data.player_id] += 1;
                              //update possession time
                              playerPossessionTimeMap[data.player_id] += data.ts - playerTsMap[data.player_id];
                              //update last hit timeStamp 
                              playerTsMap[data.player_id] = data.ts;

                          }
                          //if this player hits the ball and acquires its possession, 
                          //when previously no other player possessed the ball
                          else if (playerWithBallPossession.Equals(""))
                          {
                              //update Player who has ball
                              playerWithBallPossession = data.player_id;
                              //increment hit count for this player
                              playerHitsMap[data.player_id] += 1;
                              //update time of hit 
                              playerTsMap[data.player_id] = data.ts;
                              //keep track of active ball in field
                              ballSensorId = data.ball_sensor_id;

                              //publish state change
                              return new List<Update>{
                                    new Update{
                                        toPublish = true,
                                        possessionData = new PlayerBallPossession
                                        {
                                            player_id=data.player_id,
                                            ts=data.ts,
                                            hits=playerHitsMap[data.player_id],
                                            time=playerPossessionTimeMap[data.player_id]
                                        }
                                    }
                                };
                          }//pervious player was intercepted by a new player for the active ball
                          else if (!playerWithBallPossession.Equals(data.player_id)
                              && ballSensorId == data.ball_sensor_id)
                          {
                              List<Update> updates = new List<Update>();
                              //update previous player's possession time 
                              //pervious player has lost possession and this state change must be published
                              playerPossessionTimeMap[playerWithBallPossession] = data.ts - playerTsMap[playerWithBallPossession];
                              updates.Add(
                                  new Update
                                  {
                                      toPublish = true,
                                      possessionData = new PlayerBallPossession
                                      {
                                          player_id = playerWithBallPossession,
                                          time = playerPossessionTimeMap[playerWithBallPossession],
                                          hits = playerHitsMap[playerWithBallPossession],
                                          ts = data.ts
                                      }
                                  });

                              //set player with ball possession to this player
                              playerWithBallPossession = data.player_id;
                              //increment this player's no of hits
                              playerHitsMap[data.player_id] += 1;
                              //update this player's last hit time
                              playerTsMap[data.player_id] = data.ts;

                              //publish update for new player
                              updates.Add(new Update
                              {
                                  toPublish = true,
                                  possessionData = new PlayerBallPossession
                                  {
                                      player_id = data.player_id,
                                      hits = playerHitsMap[data.player_id],
                                      time = playerPossessionTimeMap[data.player_id],
                                      ts = data.ts
                                  }
                              });
                              return updates;
                          }
                      }
                      //for all don't care state transitions...
                      return new List<Update> { new Update { toPublish = false, possessionData = new PlayerBallPossession { } } };
                  })
                //only select state changes that need to be published
                  .Where(update => update.toPublish)
                //publish playerball possession data 
                  .Select(result => result.possessionData)
                  .Subscribe(output);               
  
        }
       
        public static List<IObservable<SensorData>> getPlayerStreamList(ref Subject<SensorData> src)
        {
            List<IObservable<SensorData>> playerStreamList =
                new List<IObservable<SensorData>>();
            foreach (var sensor_id in MetaData.SENSOR_MAP.Keys)
            {
                if (!MetaData.BALL_SENSOR_IDS.Contains(sensor_id))
                    playerStreamList
                        .Add(src
                        .Where(data => data.sensor_id == sensor_id)
                        .Once(MetaData.getDefaultSensorData()));
                        
            }
            return playerStreamList;
        }


        public static Dictionary<string, int> initializeHitsDictionary()
        {
            Dictionary<string,int> hits =new Dictionary<string,int>();
            foreach (var key in MetaData.PLAYER_MAP.Keys)
                hits.Add(key, 0);
            return hits;
        }
        public static Dictionary<string, double> initializePossessionTimeDictionary()
        {
            Dictionary<string, double> possessionTime = new Dictionary<string, double>();
            foreach (var key in MetaData.PLAYER_MAP.Keys)
                possessionTime.Add(key, 0);
            return possessionTime;
        }
        public static Dictionary<string, Int64> initializeTsDictionary()
        {
            Dictionary<string, Int64> ts = new Dictionary<string, Int64>();
            foreach (var key in MetaData.PLAYER_MAP.Keys)
                ts.Add(key, 0);
            return ts;
        }        

        public struct EventInfo
        {            
            //The state in which the player is in- empty,hit or outOfFieldEnded
            public string state;
            //player id
            public string player_id;
            //time at which this state happened.
            public Int64 ts;
            //sensor_id of ball
            public int ball_sensor_id;
            //ball Data
            public SensorData ballData;
            
        };
        private struct Update
        {
            public bool toPublish;
            public PlayerBallPossession possessionData;
        };      
    
    }//End of class: BallPossessionQuery

}//End of Namespace: Queries
