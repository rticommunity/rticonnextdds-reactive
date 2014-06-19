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
using SoccerExtesions;
using System.Diagnostics;
using System.IO;
using Utility;

namespace Query2
{
    public static class TeamBallPossessionQuery
    {
        public static IObservable<TeamBallPossession> teamBallPossessionProcessorFullGame(this IObservable<PlayerBallPossession> src)
        {
            return computeTeamBallPossessionFullGame(src);

        }
        public static IObservable<TeamBallPossession> teamBallPossessionProcessorTimeWindow(this IObservable<PlayerBallPossession> src, int timeWindowInSec)
        {
            return computeTeamBallPossessionTW(src, timeWindowInSec);
        }
        //this function computes the TeamBall Possession data for the entire game
        public static  IObservable<TeamBallPossession> computeTeamBallPossessionFullGame(IObservable<PlayerBallPossession> src)
        {
            
            List<PlayerBallPossession> expList = new List<PlayerBallPossession>();

            return src
            .Scan(new Aggregate { currTeam = "", pTimeA = 0.0, pTimeB = 0.0, ts = 0 }, (seed, val) =>
            {
                seed = aggregatorFunction(seed, val, expList, 0);
                return seed;
            })
            .Select(b => getTeamPossessionData(b));
           
            
        }

        //this function computes the TeamBall Possession data for a specified time duration timeWindowInSec
        public static IObservable<TeamBallPossession> computeTeamBallPossessionTW(IObservable<PlayerBallPossession> src,int timeWindowInSec)            
        {
            
            var timeWindowInPico = timeWindowInSec * MetaData.SECOND_TO_PICO;
           // List<PlayerBallPossession> list_of_values = new List<PlayerBallPossession>();
            Aggregate seed= new Aggregate { currTeam = "", pTimeA = 0.0, pTimeB = 0.0, ts = 0 };


            return src
            .TimeWindowForTsDataAggregate(timeWindowInPico, "ts", seed, aggregatorFunction)
            .Select(b => getTeamPossessionData(b));
            
                        

        }


        //calculates the team ball possession data from player ball possession 
        private static Aggregate aggregatorFunction(Aggregate seed, PlayerBallPossession curr,
            IList<PlayerBallPossession> expList, long count)
        {
            double pTimeA = seed.pTimeA, pTimeB = seed.pTimeB;
            //remove expired possession time from the aggregate team possession time information
            foreach (var ele in expList)
            {
                if (MetaData.PLAYER_TEAM_MAP[ele.player_id].Equals("A"))
                    pTimeA -= ele.time;
                else
                    pTimeB -= ele.time;
            }
            string team_name = MetaData.PLAYER_TEAM_MAP[curr.player_id];
            //if the player for which this PlayerBallPossession information(curr) belongs to Team A
            //then add possession time of this player to pTimeA else to pTimeB
            if (team_name.Equals("A"))
                pTimeA = seed.pTimeA + curr.time;
            else
                pTimeB = seed.pTimeB + curr.time;
            //return updated team possession time information
            return new Aggregate { currTeam = team_name, pTimeA = pTimeA, pTimeB = pTimeB, ts = curr.ts };
            
        }
        
        //getTeamPossessionData calculates TeamBallPossession information. 
        private static TeamBallPossession getTeamPossessionData(Aggregate b)
        {
            double time = 0.0, percentTime = 0.0;
            if (b.currTeam.Equals("A"))
            {
                time = b.pTimeA;
                if (b.pTimeA + b.pTimeB != 0)
                    percentTime = (b.pTimeA / (b.pTimeA + b.pTimeB)) * 100;
                else
                    percentTime = 0.0;
            }
            else
            {
                time = b.pTimeB;
                if (b.pTimeA + b.pTimeB != 0)
                    percentTime = (b.pTimeB / (b.pTimeA + b.pTimeB)) * 100;
                else
                    percentTime = 0.0;
            }

            return new TeamBallPossession
            {
                ts = b.ts,
                team_id = b.currTeam,
                time = time,
                time_percent = percentTime
            };


        }

        //This structure is used for storing aggregate possession time information 
        //both teams A and B
        private struct Aggregate
        {
            //currTeam represents the team_id of the player whose 
            //ball possession information updated this aggregate team possession data.
            public string currTeam;
            //possession time of Team A
            public double pTimeA;
            //possession time of Team B
            public double pTimeB;
            //ts of update
            public Int64 ts;

        };
    }
}

