using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;
using System.Reactive.Linq;
using System.Collections.Concurrent;
using System.Diagnostics;

namespace soccer_publisher
{
  public class SensorDataPublisher
  {
    public static void Main(string[] args) 
    {
        if (args.Length < 3) {
          Console.WriteLine("Usage: soccer-publisher <domain-id> <sensor-data-filename> <max-samples> [target-rate]");
          return;
        }
        int domain_id = Int32.Parse(args[0]);
        String file_name = args[1];
        max_samples = Int32.Parse(args[2]);

        if (args.Length == 4) {
          target_rate = Int32.Parse(args[3]);
        }

        try
        {
            SensorDataPublisher.publish(domain_id, file_name);
        }
        catch(DDS.Exception)
        {
            Console.WriteLine("error in publisher");
        }
    }
    static bool wait_for_readers(DDS.DataWriter writer, int howmany_dr)
    {
        SensorDataDataWriter sensor_data_writer = (SensorDataDataWriter)writer;
        DDS.InstanceHandleSeq sub_handle_seq=new DDS.InstanceHandleSeq();
        int interval_milisec = 100;

        Console.WriteLine("waiting for discovery");

        for (var i = 0; i <= 200; i++)
        {
            sensor_data_writer.get_matched_subscriptions(sub_handle_seq);
            
            if (sub_handle_seq.length >= howmany_dr)
                return true;

            System.Threading.Thread.Sleep(interval_milisec);
        }
        Console.WriteLine("Discovery not complete");
        return false;
   }


    static void publish(int domain_id, String file_name)
    {
        // --- Create participant --- //

        /* To customize participant QoS, use 
           the configuration file USER_QOS_PROFILES.xml */
        DDS.DomainParticipant participant =                       
            DDS.DomainParticipantFactory.get_instance().create_participant(
                domain_id,
                DDS.DomainParticipantFactory.PARTICIPANT_QOS_DEFAULT, 
                null,
                DDS.StatusMask.STATUS_MASK_NONE);
        if (participant == null) {
            shutdown(participant);
            throw new ApplicationException("create_participant error");
        }

        // --- Create publisher --- //

        /* To customize publisher QoS, use 
           the configuration file USER_QOS_PROFILES.xml */
        DDS.Publisher publisher = participant.create_publisher(
        DDS.DomainParticipant.PUBLISHER_QOS_DEFAULT,
        null /* listener */,
        DDS.StatusMask.STATUS_MASK_NONE);
        if (publisher == null) {
            shutdown(participant);
            throw new ApplicationException("create_publisher error");
        }

        // --- Create topic --- //

        /* Register type before creating topic */
        System.String type_name = SensorDataTypeSupport.get_type_name();
        try {
            SensorDataTypeSupport.register_type(
                participant, type_name);
        }
        catch(DDS.Exception e) {
            Console.WriteLine("register_type error {0}", e);
            shutdown(participant);
            throw e;
        }

        /* To customize topic QoS, use 
           the configuration file USER_QOS_PROFILES.xml */
        DDS.Topic topic = participant.create_topic(
            "Raw SensorData",
            type_name,
            DDS.DomainParticipant.TOPIC_QOS_DEFAULT,
            null /* listener */,
            DDS.StatusMask.STATUS_MASK_NONE);
        if (topic == null) {
            shutdown(participant);
            throw new ApplicationException("create_topic error");
        }

        // --- Create writer --- //
        
        /* To customize data writer QoS, use 
           the configuration file USER_QOS_PROFILES.xml */
        DDS.DataWriter writer = publisher.create_datawriter(
            topic,
            DDS.Publisher.DATAWRITER_QOS_DEFAULT,
            null /* listener */,
            DDS.StatusMask.STATUS_MASK_NONE);
        if (writer == null) {
            shutdown(participant);
            throw new ApplicationException("create_datawriter error");
        }
        SensorDataDataWriter SensorData_writer =
            (SensorDataDataWriter)writer;

        // --- Write --- //

        /* Create data sample for writing */
        SensorData instance = SensorDataTypeSupport.create_data();
        if (instance == null) {
            shutdown(participant);
            throw new ApplicationException(
                "SensorDataTypeSupport.create_data error");
        }

        /* For a data type that has a key, if the same instance is going to be
           written multiple times, initialize the key here
           and register the keyed instance prior to writing */
        DDS.InstanceHandle_t instance_handle = DDS.InstanceHandle_t.HANDLE_NIL;

        //wait for all data-readers to join before publishing: 
        while (!wait_for_readers(writer, no_dr))
        { }
        System.Threading.Thread.Sleep(1000);
        Console.WriteLine("datareaders have connected. starting to publish");

        /* Main loop */
        using (StreamReader sReader = new StreamReader(file_name))                
        {          
            String line; 
            publication_sw.Start();
            start_ticks = publication_sw.ElapsedTicks;
            prev_ticks = start_ticks;
            int[] ballSensors = { 4, 8, 10, 12 };

            while ((line = sReader.ReadLine())!= null && count < max_samples)
            {
              try
              {
                linesRead++;
                String[] fields = line.Split(',');            
                
                instance.sensor_id = Int32.Parse(fields[0]);
                if(ballSensors.Contains(instance.sensor_id))
                  continue;

                instance.ts        = Int64.Parse(fields[1]);
                instance.pos_x     = Int32.Parse(fields[2]);
                instance.pos_y     = Int32.Parse(fields[3]);
                instance.pos_z     = Int32.Parse(fields[4]);
                instance.vel       = Int32.Parse(fields[5]);
                instance.accel     = Int32.Parse(fields[6]);
                instance.vel_x     = Int32.Parse(fields[7]);
                instance.vel_y     = Int32.Parse(fields[8]);
                instance.vel_z     = Int32.Parse(fields[9]);
                instance.accel_x   = Int32.Parse(fields[10]);
                instance.accel_y   = Int32.Parse(fields[11]);
                instance.accel_z   = Int32.Parse(fields[12]);

                count++;
                SensorData_writer.write(instance, ref instance_handle);
                if (count % calculation_point == 0)
                {                       
                    long curr_ticks = publication_sw.ElapsedTicks;
                    ncalcs++;
                    long lapse_ticks = curr_ticks - prev_ticks;
                        
                    double lapse_msec = (double) lapse_ticks * ns_per_tick/(1000.0*1000.0);
                    sum_lapse_msec += lapse_msec;
                    if (lapse_msec < min_lapse)
                        min_lapse = lapse_msec;
                    if (lapse_msec > max_lapse)
                        max_lapse = lapse_msec;                        
                    prev_ticks = curr_ticks;
                        
                    Console.WriteLine("Took {0} millisec to send next {1} samples: {2}",
                        lapse_msec, calculation_point, count);
                        
                    double rate = (double)(calculation_point*1000L*1000L*1000L) / (double)(lapse_ticks * ns_per_tick);
                    if (rate < min_rate)
                        min_rate = rate;
                    if (rate > max_rate)
                        max_rate = rate;
                    Console.WriteLine("publishing rate:{0} samples/sec", rate);
                }
              }
              catch (DDS.Exception e)
              {
                  Console.WriteLine("write error {0}", e);
              }

              if((target_rate != 0) && (count % 100==0))
                  System.Threading.Thread.Sleep(1000*100/target_rate*90/100);
            }
            end_ticks = publication_sw.ElapsedTicks;
            publication_sw.Stop();
        }

        Console.WriteLine("Playback finished.. "+ count);
        // --- Shutdown --- //
        double total_time_ms = (end_ticks - start_ticks) * ns_per_tick / 1000 / 1000;
        double rate_pub = (double)count / total_time_ms;
        Console.WriteLine("Target rate = {0} samples/sec.", target_rate);
        Console.WriteLine("Overall Publication Rate Observed: {0} per sec", rate_pub*1000);
        Console.WriteLine("total time for playback in seconds: {0}", total_time_ms/1000);
        Console.WriteLine("lines read = {0}, samples written = {1}", linesRead, count);
        
        /* Delete data sample */
        try {
            SensorData_writer.dispose(instance, ref instance_handle);
            System.Threading.Thread.Sleep(10000);
            SensorDataTypeSupport.delete_data(instance);          
        } 
        catch(DDS.Exception e) {
            Console.WriteLine(
                "SensorDataTypeSupport.delete_data error: {0}", e);
        }
        
        Console.WriteLine("Press enter to exit");
        Console.ReadLine();
        using (StreamWriter file = new StreamWriter("publisher_output.txt"))
        {
            file.WriteLine("Publisher summary statistics:\n");
            file.WriteLine("Sent {0} samples in {1} seconds", count, total_time_ms/1000);
            file.WriteLine("\nAverage rate of publishing: {0} samples/sec", count/total_time_ms/1000);
            file.WriteLine("Max publishing rate:{0} samples/sec.",max_rate);
            file.WriteLine("Min publishing rate:{0} samples/sec.", min_rate);
            
            file.WriteLine("\nAverage time taken to publish 10000 samples: {0} sec", (sum_lapse_msec) /(double)ncalcs);
            file.WriteLine("Max time to publish 10000 samples:{0} sec.",max_lapse);
            file.WriteLine("Min time to publish 10000 samples:{0} sec.", min_lapse);
        }

        /* Delete all entities */
        shutdown(participant);
    }

    static void shutdown(
        DDS.DomainParticipant participant) {

        /* Delete all entities */

        if (participant != null) {
            participant.delete_contained_entities();
            DDS.DomainParticipantFactory.get_instance().delete_participant(
                ref participant);
        }
    }
    private static Stopwatch publication_sw=new Stopwatch();
    private static double ns_per_tick = (1000L * 1000L * 1000L) / Stopwatch.Frequency;
    private static long prev_ticks = 0;
    private static long start_ticks = 0;
    private static long end_ticks = 0;
    private static long ncalcs = 0;
    private static long count = 0;
    private static long linesRead = 0;
    private static double sum_lapse_msec = 0;
    private static double min_rate = Double.MaxValue, max_rate = Double.MinValue;
    private static double min_lapse = Double.MaxValue, max_lapse = Double.MinValue;
    private static int no_dr = 1;
    private static long calculation_point = 100000;
    private static int target_rate = 2000; // samples/sec
    private static int max_samples = 100000;
}

}
