#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "soccer.h"
#include "soccerSupport.h"
#include "ndds/ndds_cpp.h"

#if defined(_MSC_VER) || defined(_MSC_EXTENSIONS)
  #define DELTA_EPOCH_IN_MICROSECS  11644473600000000Ui64
#else
  #define DELTA_EPOCH_IN_MICROSECS  11644473600000000ULL
#endif
 
struct timezone 
{
  int  tz_minuteswest; /* minutes W of Greenwich */
  int  tz_dsttime;     /* type of dst correction */
};
 
int gettimeofday(struct timeval *tv, struct timezone *tz)
{
  FILETIME ft;
  unsigned __int64 tmpres = 0;
  static int tzflag;
 
  if (NULL != tv)
  {
    GetSystemTimeAsFileTime(&ft);
 
    tmpres |= ft.dwHighDateTime;
    tmpres <<= 32;
    tmpres |= ft.dwLowDateTime;
 
    /*converting file time to unix epoch*/
    tmpres -= DELTA_EPOCH_IN_MICROSECS; 
    tmpres /= 10;  /*convert into microseconds*/
    tv->tv_sec = (long)(tmpres / 1000000UL);
    tv->tv_usec = (long)(tmpres % 1000000UL);
  }
 
  if (NULL != tz)
  {
    if (!tzflag)
    {
      _tzset();
      tzflag++;
    }
    tz->tz_minuteswest = _timezone / 60;
    tz->tz_dsttime = _daylight;
  }
 
  return 0;
}

long operator - (const timeval & t1, const timeval & t2) 
{
    long start_milli = t1.tv_sec*1000 + t1.tv_usec/1000;
    long end_milli = t2.tv_sec*1000 + t2.tv_usec/1000;
    return start_milli-end_milli;
}


/* Delete all entities */
static int publisher_shutdown(
    DDSDomainParticipant *participant)
{
    DDS_ReturnCode_t retcode;
    int status = 0;

    if (participant != NULL) {
        retcode = participant->delete_contained_entities();
        if (retcode != DDS_RETCODE_OK) {
            printf("delete_contained_entities error %d\n", retcode);
            status = -1;
        }

        retcode = DDSTheParticipantFactory->delete_participant(participant);
        if (retcode != DDS_RETCODE_OK) {
            printf("delete_participant error %d\n", retcode);
            status = -1;
        }
    }

    /* RTI Connext provides finalize_instance() method on
       domain participant factory for people who want to release memory used
       by the participant factory. Uncomment the following block of code for
       clean destruction of the singleton. */
/*
    retcode = DDSDomainParticipantFactory::finalize_instance();
    if (retcode != DDS_RETCODE_OK) {
        printf("finalize_instance error %d\n", retcode);
        status = -1;
    }
*/

    return status;
}

bool wait_for_readers(DDSDataWriter * writer,
                      int howmany_dr)
{
  DDS_InstanceHandleSeq sub_handle_seq;   
  DDS_Duration_t wait_period = {0, 1000*1000*100}; // 100 msec
    
  printf("Waiting for discovery....\n"); 
  for(int count = 0; count <= 200; ++count) 
  {
    writer->get_matched_subscriptions(sub_handle_seq);
      
    if(sub_handle_seq.length() >= howmany_dr) 
      return true;
      
    NDDSUtility::sleep(wait_period);
  }
  printf("Discovery did not finish\n");
  return false;
}


extern "C" int publisher_main(int domainId, char * filename, int sample_count, int target_rate)
{
    DDSDomainParticipant *participant = NULL;
    DDSPublisher *publisher = NULL;
    DDSTopic *topic = NULL;
    DDSDataWriter *writer = NULL;
    SensorDataDataWriter * SensorData_writer = NULL;
    SensorData *sensor_data = NULL;
    DDS_ReturnCode_t retcode;
    DDS_InstanceHandle_t instance_handle = DDS_HANDLE_NIL;
    const char *type_name = NULL;
    int count = 0;  
    DDS_Duration_t send_period = {4,0};

    /* To customize participant QoS, use 
       the configuration file USER_QOS_PROFILES.xml */
    participant = DDSTheParticipantFactory->create_participant(
        domainId, DDS_PARTICIPANT_QOS_DEFAULT, 
        NULL /* listener */, DDS_STATUS_MASK_NONE);
    if (participant == NULL) {
        printf("create_participant error\n");
        publisher_shutdown(participant);
        return -1;
    }

    /* To customize publisher QoS, use 
       the configuration file USER_QOS_PROFILES.xml */
    publisher = participant->create_publisher(
        DDS_PUBLISHER_QOS_DEFAULT, NULL /* listener */, DDS_STATUS_MASK_NONE);
    if (publisher == NULL) {
        printf("create_publisher error\n");
        publisher_shutdown(participant);
        return -1;
    }

    /* Register type before creating topic */
    type_name = SensorDataTypeSupport::get_type_name();
    retcode = SensorDataTypeSupport::register_type(
        participant, type_name);
    if (retcode != DDS_RETCODE_OK) {
        printf("register_type error %d\n", retcode);
        publisher_shutdown(participant);
        return -1;
    }

    /* To customize topic QoS, use 
       the configuration file USER_QOS_PROFILES.xml */
    topic = participant->create_topic(
        "Raw SensorData",
        type_name, DDS_TOPIC_QOS_DEFAULT, NULL /* listener */,
        DDS_STATUS_MASK_NONE);
    if (topic == NULL) {
        printf("create_topic error\n");
        publisher_shutdown(participant);
        return -1;
    }

    /* To customize data writer QoS, use 
       the configuration file USER_QOS_PROFILES.xml */
    writer = publisher->create_datawriter(
        topic, DDS_DATAWRITER_QOS_DEFAULT, NULL /* listener */,
        DDS_STATUS_MASK_NONE);
    if (writer == NULL) {
        printf("create_datawriter error\n");
        publisher_shutdown(participant);
        return -1;
    }
    SensorData_writer = SensorDataDataWriter::narrow(writer);
    if (SensorData_writer == NULL) {
        printf("DataWriter narrow error\n");
        publisher_shutdown(participant);
        return -1;
    }

    /* Create data sample for writing */

    sensor_data = SensorDataTypeSupport::create_data();
    
    if (sensor_data == NULL) {
        printf("SensorDataTypeSupport::create_data error\n");
        publisher_shutdown(participant);
        return -1;
    }
    
    if(wait_for_readers(SensorData_writer, 1) != true)
      return -1;
	
	FILE *fin = NULL;
	fin = fopen (filename, "r");

	if (fin == NULL) {
		printf("Unable to open file: %s\n", filename);
		perror("Error");
		publisher_shutdown(participant);
		return -1;
	}

	//fseek (fin, 131435030, SEEK_SET);
	int lines_read = 0;
	int calc_point = 100000;

  timeval start, current, prev, end;
  gettimeofday(&start, NULL);
  prev = start;

	for (count=0; (sample_count == 0) || (count < sample_count);) 
	{
		if(EOF==fscanf(fin, "%hu,%llu,%d,%d,%d,%u,%d,%d,%d,%d,%d,%d,%d",
						&sensor_data->sensor_id,
						&sensor_data->ts,
						&sensor_data->pos_x,
						&sensor_data->pos_y,
						&sensor_data->pos_z,
						&sensor_data->vel,
						&sensor_data->accel,
						&sensor_data->vel_x,
						&sensor_data->vel_y,
						&sensor_data->vel_z,
						&sensor_data->accel_x,
						&sensor_data->accel_y,
						&sensor_data->accel_z))
		{
			break;
		}

		lines_read++;
		if((sensor_data->sensor_id == 4)  || /* ball sensors */
		   (sensor_data->sensor_id == 8)  ||
		   (sensor_data->sensor_id == 10) ||
		   (sensor_data->sensor_id == 12))
		   continue;

		retcode = SensorData_writer->write(*sensor_data, DDS_HANDLE_NIL);
		if (retcode != DDS_RETCODE_OK) {
			printf("write error %d\n", retcode);
			publisher_shutdown(participant);
			return -1; 
		}
		count++;
    if (count % calc_point == 0)
    {                       
        gettimeofday(&current, NULL);
        long lapse_msec = current - prev;
        prev = current;
                        
        printf("Took %ld millisec to send next %d samples: %d\n",
            lapse_msec, calc_point, count);
                        
        double rate = (double)(calc_point*1000L) / (double)(lapse_msec);
        printf("publishing rate: %lf samples/sec\n", rate);
    }

		//if((target_rate != 0) && (count % 100==0))
    //  NDDSUtility::sleep(DDS_Duration_t::from_micros(1000*1000*100/target_rate*98/100));
	}

  gettimeofday(&end, NULL);
  long total_msec = end - start;
  printf("lines read = %d, count = %d\n", lines_read, count);
  printf("Total sec = %lf and cumulative rate = %lf\n", (double) total_msec/1000, (double)count/total_msec*1000);

  /* Delete data sample */
  retcode = SensorDataTypeSupport::delete_data(sensor_data);
  if (retcode != DDS_RETCODE_OK) {
      printf("SensorDataTypeSupport::delete_data error %d\n", retcode);
  }
  NDDSUtility::sleep(DDS_Duration_t::from_seconds(2));
  /* Delete all entities */
  return publisher_shutdown(participant);
}

int main(int argc, char *argv[])
{
  int domainId = 0;
  int sample_count = 0; /* infinite loop */
	char * filename = 0;
	int target_rate = 0;

	if (argc < 4) {
		printf("Usage: soccer-publisher <domain-id> <sensor-data-filename> <max-samples> [target-rate]");
		return 1;
	}
  domainId = atoi(argv[1]);
  filename = argv[2];
	sample_count = atoi(argv[3]);
	if (argc == 5)
	  target_rate = atoi(argv[4]);
    
    return publisher_main(domainId, filename, sample_count, target_rate);
}
