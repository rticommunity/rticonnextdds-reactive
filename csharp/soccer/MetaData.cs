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
using System.Collections.ObjectModel;
using System.Diagnostics;

namespace Utility
{
    public sealed class MetaData
    {
        
        private MetaData() { }
        //DomainID to be used for this application
        public static int mDomainId = 0;
        //variable to keep track if player info was initialized. 
        private static bool mInitialized = false;

        //GOAL AREAS of TEAMS
        public static double A_X_MIN = 22.5785;
        public static double A_X_MAX = 29.8985;
        public static double A_Y = 33.941;
        public static double A_Z = 2.440;

        public static double B_X_MIN = 22.560;
        public static double B_X_MAX = 29.880;
        public static double B_Y = -33.968;
        public static double B_Z = 2.440;           

        //Max Lengths on x and y axis
        public static int LEN_X = 52483;
        public static int LEN_Y = 67925;
        //GridDimensions
        public static int[] X_DIM={8,16,32,64};
        public static int[] Y_DIM={13,25,50,100};
        
        //Y_OFFSET
        public static int Y_OFFSET = 33960;
        //ball sensor ids
        public static List<int> BALL_SENSOR_IDS = new List<int> { 4, 8, 10, 12 };

        //GoalKeeper's sensor ids 
        public static List<int> GOAL_KEEPER_IDS = new List<int> { 61,62,99,100,13,14,97,98 };
        
        //list of player info
        public static List<PlayerInfo> PLAYER_DATA = new List<PlayerInfo>();
        
        //mapping of sensor_ids to player names
        public static ReadOnlyDictionary<int, string> SENSOR_MAP;
        
        //mapping of sensor_ids to player names
        public static ReadOnlyDictionary<string,List<int>> PLAYER_MAP;
        
        //mapping of player_name to team_id 
        public static ReadOnlyDictionary<string, string> PLAYER_TEAM_MAP;

        public static long NS_PER_TICK = (1000L * 1000L * 1000L) / Stopwatch.Frequency;
        public static int PICO_TO_MILI = 1000000000;
        public static long SECOND_TO_PICO = 1000000000000;
        public static long VEL_COMPONENT_FACTOR = 10000000000;
        public static double GRAVITY = 9.81;


        //field co-ordinates
        public static int MIN_FIELD_X_CORD = 0;
        public static int MAX_FIELD_X_CORD = 52483;
        public static int MIN_FIELD_Y_CORD = -33960;
        public static int MAX_FIELD_Y_CORD = 33965;
        
        //relevant game time-stamps
        public static Int64 START_TS = 10753295594424116;
        public static Int64 BREAK_START_TS = 12557295594424116;
        public static Int64 BREAK_END_TS = 13086639146403495;
        public static Int64 END_TS = 14879639146403495;

        public static bool isTsValid(Int64 ts)
        {
            if ((ts >= START_TS && ts <= BREAK_START_TS) || (ts >= BREAK_END_TS && ts <= END_TS))
                return true;

            else
                return false;
                
        }
        public static bool inRange(double val, double lower, double upper)
        {
            return (val >= lower && val <= upper);
        }
        //returns true if passed co-ordinates are within field co-ordinates
        public static bool inField(int x, int y)
        {
            return (x <= MAX_FIELD_X_CORD && x >= MIN_FIELD_X_CORD
                && y <= MAX_FIELD_Y_CORD && y >= MIN_FIELD_Y_CORD);
        }
        
        //this function calculates the distance between two position co-ordinates
        public static double returnDistance(double prev_x, double prev_y, double curr_x, double curr_y)
        {
            return Math.Sqrt(Math.Pow(curr_x - prev_x, 2) + Math.Pow(curr_y - prev_y, 2));
        }

        //This function maps the speed to its corresponding intensity.
        public static Intensity returnRunningIntensity(double speed)
        {
            if (speed <= 1)
                return Intensity.STOP;
            else if (speed > 1 && speed <= 11)
                return Intensity.TROT;
            else if (speed > 11 && speed <= 14)
                return Intensity.LOW;
            else if (speed > 14 && speed <= 17)
                return Intensity.MEDIUM;
            else if (speed > 17 && speed <= 24)
                return Intensity.HIGH;
            else
                return Intensity.SPRINT;
        }
        public static SensorData getDefaultSensorData()
        {
            return new SensorData
            {
                ts = -99999,
                sensor_id = -99999,
                pos_x = -99999,
                pos_y = -99999,
                pos_z = -99999,
                vel = -99999,
                accel = -99999,
                vel_x = -99999,
                vel_y = -99999,
                vel_z = -99999,
                accel_x = -99999,
                accel_y = -99999,
                accel_z = -99999
            };
        }
        public static SensorData getDefaultSensorDataWithSensorID(int id)
        {
            return new SensorData
            {
                ts = -99999,
                sensor_id = id,
                pos_x = -99999,
                pos_y = -99999,
                pos_z = -99999,
                vel = -99999,
                accel = -99999,
                vel_x = -99999,
                vel_y = -99999,
                vel_z = -99999,
                accel_x = -99999,
                accel_y = -99999,
                accel_z = -99999
            };
        }

        

        //initializes the player meta data stored in PLAYER_DATA list
        public static void initializePlayerData()
        {
            Console.WriteLine("Initializing Player Information");
            mInitialized = true;
            /* players for team A */
            PLAYER_DATA.Add(new PlayerInfo("A", "Nick Gertje", 13));
            PLAYER_DATA.Add(new PlayerInfo("A", "Nick Gertje", 14));
            PLAYER_DATA.Add(new PlayerInfo("A", "Nick Gertje", 97));
            PLAYER_DATA.Add(new PlayerInfo("A", "Nick Gertje", 98));

            PLAYER_DATA.Add(new PlayerInfo("A", "Dennis Dotterweich", 47));
            PLAYER_DATA.Add(new PlayerInfo("A", "Dennis Dotterweich", 16));

            PLAYER_DATA.Add(new PlayerInfo("A", "Niklas Waelzlein", 49));
            PLAYER_DATA.Add(new PlayerInfo("A", "Niklas Waelzlein", 88));

            PLAYER_DATA.Add(new PlayerInfo("A", "Wili Sommer", 19));
            PLAYER_DATA.Add(new PlayerInfo("A", "Wili Sommer", 52));

            PLAYER_DATA.Add(new PlayerInfo("A", "Philipp Harlass", 53));
            PLAYER_DATA.Add(new PlayerInfo("A", "Philipp Harlass", 54));

            PLAYER_DATA.Add(new PlayerInfo("A", "Roman Hartleb", 23));
            PLAYER_DATA.Add(new PlayerInfo("A", "Roman Hartleb", 24));

            PLAYER_DATA.Add(new PlayerInfo("A", "Erik Engelhardt", 57));
            PLAYER_DATA.Add(new PlayerInfo("A", "Erik Engelhardt", 58));

            PLAYER_DATA.Add(new PlayerInfo("A", "Sandro Schneider", 59));
            PLAYER_DATA.Add(new PlayerInfo("A", "Sandro Schneider", 28));

            /*players for team B */

            PLAYER_DATA.Add(new PlayerInfo("B", "Leon Krapf", 61));
            PLAYER_DATA.Add(new PlayerInfo("B", "Leon Krapf", 62));
            PLAYER_DATA.Add(new PlayerInfo("B", "Leon Krapf", 99));
            PLAYER_DATA.Add(new PlayerInfo("B", "Leon Krapf", 100));

            PLAYER_DATA.Add(new PlayerInfo("B", "Kevin Baer", 63));
            PLAYER_DATA.Add(new PlayerInfo("B", "Kevin Baer", 64));

            PLAYER_DATA.Add(new PlayerInfo("B", "Luca Ziegler", 65));
            PLAYER_DATA.Add(new PlayerInfo("B", "Luca Ziegler", 66));

            PLAYER_DATA.Add(new PlayerInfo("B", "Ben Mueller", 67));
            PLAYER_DATA.Add(new PlayerInfo("B", "Ben Mueller", 68));

            PLAYER_DATA.Add(new PlayerInfo("B", "Vale Reitstetter", 69));
            PLAYER_DATA.Add(new PlayerInfo("B", "Vale Reitstetter", 38));

            PLAYER_DATA.Add(new PlayerInfo("B", "Christopher Lee", 71));
            PLAYER_DATA.Add(new PlayerInfo("B", "Christopher Lee", 40));

            PLAYER_DATA.Add(new PlayerInfo("B", "Leon Heinze", 73));
            PLAYER_DATA.Add(new PlayerInfo("B", "Leon Heinze", 74));

            PLAYER_DATA.Add(new PlayerInfo("B", "Leo Langhans", 75));
            PLAYER_DATA.Add(new PlayerInfo("B", "Leo Langhans", 44));

            /* sensors for Refree */
            PLAYER_DATA.Add(new PlayerInfo("", "Referee", 105));
            PLAYER_DATA.Add(new PlayerInfo("", "Referee", 106));
        }
        public static void createTeamMap()
        {
            Console.WriteLine("Creating player_name to team_id map");
            if (mInitialized)
            {
                Dictionary<string,string> player_team=new Dictionary<string,string>();
                foreach (var element in PLAYER_DATA)
                {
                    if (!player_team.ContainsKey(element.mName))
                        player_team.Add(element.mName, element.mTeamId);                        
                }
                PLAYER_TEAM_MAP=new  ReadOnlyDictionary<string, string>(player_team);
               
            }
            else
                throw new ApplicationException("player information is not initialized");
        }

        public static void createSensorMap()
        {
            Console.WriteLine("Creating Sensor_id to Player_name map");
            if (mInitialized)
            {
                SENSOR_MAP = new ReadOnlyDictionary<int,string>(PLAYER_DATA
                    .ToDictionary(info => info.mSensorId, info => info.mName));
            }
            else
                throw new ApplicationException("player information is not initialized");
        }
        public static void createPlayerMap()
        {
            
            Console.WriteLine("Creating Player_name to sensor_ids map");
            if (mInitialized)
            {
                PLAYER_MAP = new ReadOnlyDictionary<string,List<int>>(
                    PLAYER_DATA.ToLookup(info => info.mName, info => info.mSensorId)
                    .ToDictionary(x => x.Key, x => x.ToList()));
               
            }
            else
                throw new ApplicationException("player information is not initialized");
        }

       
    
    }

    /**
     * Encapsulates information about a player. 
     */
    public sealed class PlayerInfo
    {
        public string mTeamId { get; set; }
        public string mName { get; set; }
        public int mSensorId { get; set; }

        public PlayerInfo(string teamId, string playerName, int sensorId)
        {
            mTeamId = teamId;
            mName = playerName;
            mSensorId = sensorId;
        }

    }

}
