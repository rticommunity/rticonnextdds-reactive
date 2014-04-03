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
using RTI.RxDDS;
using System.Reactive.Subjects;
using System.Reactive.Linq;
using System.Reactive.Concurrency;
using System.Reactive.Disposables;

namespace QueryExtensions
{

}

namespace Queries
{
    class Soccer
    {
        //Private DataMemebers of class
        private DDS.TypedDataWriter<SensorData> mSensorDataWriter;
        private DDS.TypedDataWriter<PlayerData> mPlayerDataWriter;
        private DDS.TypedDataWriter<CurrentRunningData> mCurrentRunningDataWriter;
        private DDS.TypedDataWriter<AggregateRunningData> mAggregateRunningDataWriter;
        private DDS.TypedDataWriter<PlayerBallPossession> mPlayerBallPossessionDataWriter;
        private DDS.TypedDataWriter<TeamBallPossession> mTeamBallPossessionDataWriter;
        private DDS.TypedDataWriter<ShotOnGoalData> mshotOnGoalDataWriter;

        private DDS.InstanceHandle_t mInstanceHandle = DDS.InstanceHandle_t.HANDLE_NIL;

        /**
         * Entry point of program
         */
        public static void Main(string[] args)
        {
            Console.WriteLine("Running SensorToPlayer Average Processor. Press Enter to exit...");

            //DDS domain participant
            DDS.DomainParticipant participant = null;

            try
            {
                //initialize player information
                MetaData.initializePlayerData();

                //create Sensor mapping to player name
                MetaData.createSensorMap();

                //create Player mapping to sensor_ids 
                MetaData.createPlayerMap();

                //create Player mapping to team_ids
                MetaData.createTeamMap();

                participant = DefaultParticipant.Instance;

                //Register SensorData type with the domain participant
                SensorDataTypeSupport.register_type(participant, typeof(SensorData).ToString());
                PlayerDataTypeSupport.register_type(participant, typeof(PlayerData).ToString());
                CurrentRunningDataTypeSupport.register_type(participant, typeof(CurrentRunningData).ToString());
                AggregateRunningDataTypeSupport.register_type(participant, typeof(AggregateRunningData).ToString());
                PlayerBallPossessionTypeSupport.register_type(participant, typeof(PlayerBallPossession).ToString());
                TeamBallPossessionTypeSupport.register_type(participant, typeof(TeamBallPossession).ToString());
                ShotOnGoalDataTypeSupport.register_type(participant, typeof(ShotOnGoalData).ToString());


                Soccer prog = new Soccer();
                
               prog.mSensorDataWriter = 
                  DefaultParticipant.CreateDataWriter<SensorData>("QueryOutput", typeof(SensorData).ToString());
                prog.mPlayerDataWriter =
                  DefaultParticipant.CreateDataWriter<PlayerData>("PlayerOutput", typeof(PlayerData).ToString());
                prog.mCurrentRunningDataWriter =
                  DefaultParticipant.CreateDataWriter<CurrentRunningData>("CurrentRunningDataTopic", typeof(CurrentRunningData).ToString());
                prog.mAggregateRunningDataWriter =
                  DefaultParticipant.CreateDataWriter<AggregateRunningData>("AggregateRunningDataTopic", typeof(AggregateRunningData).ToString());
                prog.mPlayerBallPossessionDataWriter =
                  DefaultParticipant.CreateDataWriter<PlayerBallPossession>("PlayerBallPossessionTopic", typeof(PlayerBallPossession).ToString());
                prog.mTeamBallPossessionDataWriter = 
                  DefaultParticipant.CreateDataWriter<TeamBallPossession>("TeamBallPossessionTopic", typeof(TeamBallPossession).ToString());
                prog.mshotOnGoalDataWriter = 
                  DefaultParticipant.CreateDataWriter<ShotOnGoalData>("ShotOnGoalDataTopic", typeof(ShotOnGoalData).ToString());

                IDisposable disposable = null;
                Console.WriteLine("**********************************************************************");
                Console.WriteLine("**********************************************************************");
                Console.WriteLine("******************************Initialization is Complete**************");


                var sensorDataStream = new Subject<SensorData>();
                var averagePlayerDataStream = new Subject<PlayerData>();
                var currentRunningDataStream = new Subject<CurrentRunningData>();
                var aggregateRunningDataStream = new Subject<AggregateRunningData>();
                var playerBallPossessionDataStream = new Subject<PlayerBallPossession>();
                var teamBallPossessionDataStream = new Subject<TeamBallPossession>();
                var eventInfoStream = new Subject<BallPossessionQuery.EventInfo>();
                var shotOnGoalStream = new Subject<ShotOnGoalData>();

                IObservable<SensorData> rawSensorStream =
                DDSObservable.FromTopic<SensorData>(participant, "Raw SensorData");

                rawSensorStream.Subscribe(sensorDataStream);

                AverageProcessor.sensorToPlayerAverageProcessor(ref sensorDataStream, ref averagePlayerDataStream);
                averagePlayerDataStream.Subscribe(prog.mPlayerDataWriter);              
              
               CurrentRunningAnalysisQuery
                    .currentRunningDataProcessor(ref averagePlayerDataStream,ref currentRunningDataStream);
                currentRunningDataStream.Subscribe(prog.mCurrentRunningDataWriter);     

               AggregateRunningAnalysis
                    .aggregateRunningDataProcessorTimeSpan(ref currentRunningDataStream,
                    ref aggregateRunningDataStream,300);               
               aggregateRunningDataStream.Subscribe(prog.mAggregateRunningDataWriter);

               BallPossessionQuery.ballPossessionProcessor(ref sensorDataStream,
                   ref playerBallPossessionDataStream,
                   ref eventInfoStream
                   );
               playerBallPossessionDataStream.Subscribe(prog.mPlayerBallPossessionDataWriter);

               TeamBallPossessionQuery.teamBallPossessionTimeWindow(300,ref playerBallPossessionDataStream,
                   ref teamBallPossessionDataStream);
               teamBallPossessionDataStream.Subscribe(prog.mTeamBallPossessionDataWriter);

               HeatMapProcessor.heatMap(ref averagePlayerDataStream);

               ShotOnGoalProcessor.shotProcessor(ref sensorDataStream, ref eventInfoStream, ref shotOnGoalStream);
               shotOnGoalStream.Subscribe(prog.mshotOnGoalDataWriter);
                 

                Console.ReadLine();
                while (disposable != null)
                {
                    ConsoleKeyInfo info = Console.ReadKey(true);
                    if (info.Key == ConsoleKey.Enter)
                    {
                        disposable.Dispose();
                        break;
                    }
                }

            }
            catch (DDS.Exception e)
            {
                Console.WriteLine("Error: {0}", e);
            }
            Console.WriteLine("Quitting...");
            DefaultParticipant.Shutdown();

        }//End of function: main        

        
    }
}
