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
using System.Reactive;
using System.Diagnostics;
using System.Threading;
using System.IO;


using Utility;
using Average;
using Query1;
using Query2;
using Query3;
using Query4;


namespace Queries
{
    
    class Soccer
    {
        //data-writers for different typed outputs. 
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
            Console.WriteLine("Running QueryProcessor. Press Enter to exit...");            
           
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

                //get an instance of default domain participant
                participant =DefaultParticipant.Instance;                

                //Register types that will be used in application 
                registerTypes();

                
                Soccer prog = new Soccer();   
                //initialize dataWriters  
                prog.initializeDataWriters();
               
                IDisposable disposable = null;               
                Console.WriteLine("******************Initialization is Complete**************");

                //eventInfoStream subject is used to convey intermediate output from query-2 to query-4             
                var eventInfoStream = new Subject<BallPossessionQuery.EventInfo>();
                //heatMapSub subject is used to integrate HeatMap data for 17*4=68 streams. (17 players * 4 grid types)
                var heatMapSub = new Subject<HeatMapProcessor.HeatMapData>();
                
                //create rawSensorStream from data received on DDS topic "Raw SensorData"
                IObservable<SensorData> rawSensorStream =DDSObservable
                    .FromTopic<SensorData>(participant, "Raw SensorData");            
                
                //used to keep track of number of output samples produced from a query. 
                int output_count = 0;

                //initialize PerformanceTest.ptArray that stores a PerformanceTest obj for each player stream 
                PerformanceTest.initializePtArr();
                //set AvgProcessorStatus equal to true to compute performance metrics for AverageProcessor. 
                PerformanceTest.AvgProcessorStatus = true;
                

                //start throughput timer before query 
                PerformanceTest.startThroughputSW();               
               
                //AverageProcessor               
                disposable= rawSensorStream
                     .ObserveOn(Scheduler.Default)
                     .averageProcessor()
                     .Merge()
                     //if PerformanceTest.AvgProcessorStatus is true, then perform Do side-effect. 
                     .DoIf(() => PerformanceTest.AvgProcessorStatus,
                         d => output_count++,
                         () =>
                         {
                             PerformanceTest.postProcess("averageProcessor_stats.txt");
                             Console.WriteLine("check on output count: " + output_count);
                         })
                     .Subscribe(prog.mPlayerDataWriter);       
                
                //Query-1 CurrentRunningProcessor
                //disposable= rawSensorStream.averageProcessor().currentRunningProcessor().Merge().Subscribe(prog.mCurrentRunningDataWriter);
                
                //Query-1 AggregateRunningProcessor
                //disposable= rawSensorStream.averageProcessor().currentRunningProcessor().aggregateRunningDataProcessorFullGame().Merge().Subscribe(prog.mAggregateRunningDataWriter);

                //Query2
                //disposable= rawSensorStream.ballPossessionProcessor(ref eventInfoStream).Subscribe(prog.mPlayerBallPossessionDataWriter);
                
                /*//Query3
                rawSensorStream.averageProcessor().heatMapProcessor(heatMapSub);
                disposable= heatMapSub.Subscribe();*/                 
                 
                //Query4
                //disposable= rawSensorStream.shotOnGoalProcessor(ref eventInfoStream).Subscribe(prog.mshotOnGoalDataWriter);
               
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

        }

        //function to register data-types used in the application 
        public static void registerTypes()
        {
            DefaultParticipant.RegisterType<SensorData, SensorDataTypeSupport>();
            DefaultParticipant.RegisterType<PlayerData, PlayerDataTypeSupport>();
            DefaultParticipant.RegisterType<CurrentRunningData, CurrentRunningDataTypeSupport>();
            DefaultParticipant.RegisterType<AggregateRunningData, AggregateRunningDataTypeSupport>();
            DefaultParticipant.RegisterType<PlayerBallPossession, PlayerBallPossessionTypeSupport>();
            DefaultParticipant.RegisterType<TeamBallPossession, TeamBallPossessionTypeSupport>();
            DefaultParticipant.RegisterType<ShotOnGoalData, ShotOnGoalDataTypeSupport>();

        }
        //initializes typed datawriters for this object. 
        public void initializeDataWriters()
        {
            mSensorDataWriter =
                  DefaultParticipant.CreateDataWriter<SensorData>("QueryOutput", typeof(SensorData).ToString());
            mPlayerDataWriter =
              DefaultParticipant.CreateDataWriter<PlayerData>("PlayerOutput", typeof(PlayerData).ToString());
            mCurrentRunningDataWriter =
              DefaultParticipant.CreateDataWriter<CurrentRunningData>("CurrentRunningDataTopic", typeof(CurrentRunningData).ToString());
            mAggregateRunningDataWriter =
              DefaultParticipant.CreateDataWriter<AggregateRunningData>("AggregateRunningDataTopic", typeof(AggregateRunningData).ToString());
            mPlayerBallPossessionDataWriter =
              DefaultParticipant.CreateDataWriter<PlayerBallPossession>("PlayerBallPossessionTopic", typeof(PlayerBallPossession).ToString());
            mTeamBallPossessionDataWriter =
              DefaultParticipant.CreateDataWriter<TeamBallPossession>("TeamBallPossessionTopic", typeof(TeamBallPossession).ToString());
            mshotOnGoalDataWriter =
              DefaultParticipant.CreateDataWriter<ShotOnGoalData>("ShotOnGoalDataTopic", typeof(ShotOnGoalData).ToString());

        }

        
    }
}
