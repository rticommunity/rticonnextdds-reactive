/*
  WARNING: THIS FILE IS AUTO-GENERATED. DO NOT MODIFY.

  This file was generated from soccer.idl using "rtiddsgen".
  The rtiddsgen tool is part of the RTI Connext distribution.
  For more information, type 'rtiddsgen -help' at a command shell
  or consult the RTI Connext manual.
*/

#include "soccerPlugin.h"


#pragma unmanaged
#include "ndds/ndds_cpp.h"
#include "osapi/osapi_utility.h"
#pragma managed

using namespace System::Runtime::InteropServices;
    
/* ------------------------------------------------------------------------
 *  Type AggregateRunningData
 * ------------------------------------------------------------------------ */

/* ------------------------------------------------------------------------
    Support functions:
 * ------------------------------------------------------------------------ */

void 
AggregateRunningDataPlugin::print_data(
        AggregateRunningData^ sample,
        String^ desc,
        UInt32 indent_level) {

    for (UInt32 i = 0; i < indent_level; ++i) { Console::Write("   "); }

    if (desc != nullptr) {
        Console::WriteLine("{0}:", desc);
    } else {
        Console::WriteLine();
    }

    if (sample == nullptr) {
        Console::WriteLine("null");
        return;
    }


    DataPrintUtility::print_object(
        sample->ts, "ts", indent_level);
            
    DataPrintUtility::print_object(
        sample->player_id, "player_id", indent_level);
            
    DataPrintUtility::print_object(
        sample->standing_time, "standing_time", indent_level);
            
    DataPrintUtility::print_object(
        sample->standing_distance, "standing_distance", indent_level);
            
    DataPrintUtility::print_object(
        sample->trot_time, "trot_time", indent_level);
            
    DataPrintUtility::print_object(
        sample->trot_distance, "trot_distance", indent_level);
            
    DataPrintUtility::print_object(
        sample->low_time, "low_time", indent_level);
            
    DataPrintUtility::print_object(
        sample->low_distance, "low_distance", indent_level);
            
    DataPrintUtility::print_object(
        sample->medium_time, "medium_time", indent_level);
            
    DataPrintUtility::print_object(
        sample->medium_distance, "medium_distance", indent_level);
            
    DataPrintUtility::print_object(
        sample->high_time, "high_time", indent_level);
            
    DataPrintUtility::print_object(
        sample->high_distance, "high_distance", indent_level);
            
    DataPrintUtility::print_object(
        sample->sprint_time, "sprint_time", indent_level);
            
    DataPrintUtility::print_object(
        sample->sprint_distance, "sprint_distance", indent_level);
            
}


/* ------------------------------------------------------------------------
    (De)Serialize functions:
 * ------------------------------------------------------------------------ */

Boolean 
AggregateRunningDataPlugin::serialize(
    TypePluginDefaultEndpointData^ endpoint_data,
    AggregateRunningData^ sample,
    CdrStream% stream,    
    Boolean serialize_encapsulation,
    UInt16 encapsulation_id,
    Boolean serialize_sample, 
    Object^ endpoint_plugin_qos)
{
    CdrStreamPosition position;

    

    if (serialize_encapsulation) {
        /* Encapsulate sample */
        
        if (!stream.serialize_and_set_cdr_encapsulation(encapsulation_id)) {
            return false;
        }


        position = stream.reset_alignment();

    }

    if (serialize_sample) {

    if (!stream.serialize_long_long(sample->ts)) {
        return false;
    }
            
    if (!stream.serialize_string(sample->player_id, (255))) {
        return false;
    }
            
    if (!stream.serialize_double(sample->standing_time)) {
        return false;
    }
            
    if (!stream.serialize_double(sample->standing_distance)) {
        return false;
    }
            
    if (!stream.serialize_double(sample->trot_time)) {
        return false;
    }
            
    if (!stream.serialize_double(sample->trot_distance)) {
        return false;
    }
            
    if (!stream.serialize_double(sample->low_time)) {
        return false;
    }
            
    if (!stream.serialize_double(sample->low_distance)) {
        return false;
    }
            
    if (!stream.serialize_double(sample->medium_time)) {
        return false;
    }
            
    if (!stream.serialize_double(sample->medium_distance)) {
        return false;
    }
            
    if (!stream.serialize_double(sample->high_time)) {
        return false;
    }
            
    if (!stream.serialize_double(sample->high_distance)) {
        return false;
    }
            
    if (!stream.serialize_double(sample->sprint_time)) {
        return false;
    }
            
    if (!stream.serialize_double(sample->sprint_distance)) {
        return false;
    }
            
    }


    if(serialize_encapsulation) {
        stream.restore_alignment(position);
    }


    return true;
}


Boolean 
AggregateRunningDataPlugin::deserialize_sample(
    TypePluginDefaultEndpointData^ endpoint_data,
    AggregateRunningData^ sample,
    CdrStream% stream,   
    Boolean deserialize_encapsulation,
    Boolean deserialize_data, 
    Object^ endpoint_plugin_qos)
{
    CdrStreamPosition position;

    if(deserialize_encapsulation) {
        /* Deserialize encapsulation */
        if (!stream.deserialize_and_set_cdr_encapsulation()) {
            return false;
        }


        position = stream.reset_alignment();

    }

    if (deserialize_data) {
        sample->clear();

    try {
  
    sample->ts = stream.deserialize_long_long();
            
    sample->player_id = stream.deserialize_string((255)); 
    if (sample->player_id == nullptr) {
        return false;
    }
            
    sample->standing_time = stream.deserialize_double();
            
    sample->standing_distance = stream.deserialize_double();
            
    sample->trot_time = stream.deserialize_double();
            
    sample->trot_distance = stream.deserialize_double();
            
    sample->low_time = stream.deserialize_double();
            
    sample->low_distance = stream.deserialize_double();
            
    sample->medium_time = stream.deserialize_double();
            
    sample->medium_distance = stream.deserialize_double();
            
    sample->high_time = stream.deserialize_double();
            
    sample->high_distance = stream.deserialize_double();
            
    sample->sprint_time = stream.deserialize_double();
            
    sample->sprint_distance = stream.deserialize_double();
            
    } catch (System::ApplicationException^  e) {
        if (stream.get_remainder() >= RTI_CDR_PARAMETER_HEADER_ALIGNMENT) {
            throw gcnew System::ApplicationException("Error deserializing sample! Remainder: " + stream.get_remainder() + "\n" +
                                                              "Exception caused by: " + e->Message);
        }
    }

    }


    if(deserialize_encapsulation) {
        stream.restore_alignment(position);
    }


    return true;
}


Boolean
AggregateRunningDataPlugin::skip(
    TypePluginDefaultEndpointData^ endpoint_data,
    CdrStream% stream,   
    Boolean skip_encapsulation,
    Boolean skip_sample, 
    Object^ endpoint_plugin_qos)
{
    CdrStreamPosition position;


    if (skip_encapsulation) {
        if (!stream.skip_encapsulation()) {
            return false;
        }

        position = stream.reset_alignment();

    }

    if (skip_sample) {

    if (!stream.skip_long_long()) {
        return false;
    }
            
    if (!stream.skip_string((255) + 1)) {
        return false;
    }
            
    if (!stream.skip_double()) {
        return false;
    }
            
    if (!stream.skip_double()) {
        return false;
    }
            
    if (!stream.skip_double()) {
        return false;
    }
            
    if (!stream.skip_double()) {
        return false;
    }
            
    if (!stream.skip_double()) {
        return false;
    }
            
    if (!stream.skip_double()) {
        return false;
    }
            
    if (!stream.skip_double()) {
        return false;
    }
            
    if (!stream.skip_double()) {
        return false;
    }
            
    if (!stream.skip_double()) {
        return false;
    }
            
    if (!stream.skip_double()) {
        return false;
    }
            
    if (!stream.skip_double()) {
        return false;
    }
            
    if (!stream.skip_double()) {
        return false;
    }
            
    }


    if(skip_encapsulation) {
        stream.restore_alignment(position);
    }


    return true;
}

/*
  size is the offset from the point where we have do a logical reset
  Return difference in size, not the final offset.
*/
UInt32 
AggregateRunningDataPlugin::get_serialized_sample_max_size(
    TypePluginDefaultEndpointData^ endpoint_data,
    Boolean include_encapsulation,
    UInt16 encapsulation_id,
    UInt32 current_alignment)
{

    UInt32 initial_alignment = current_alignment;

    UInt32 encapsulation_size = current_alignment;


    if (include_encapsulation) {
        if (!CdrStream::valid_encapsulation_id(encapsulation_id)) {
            return 1;
        }


        encapsulation_size = CdrSizes::ENCAPSULATION->serialized_size(
            current_alignment);
        encapsulation_size -= current_alignment;
        current_alignment = 0;
        initial_alignment = 0;

    }


    current_alignment +=  CdrSizes::LONG_LONG->serialized_size(
        current_alignment);
            
    current_alignment +=  CdrSizes::STRING->serialized_size(
        current_alignment, (255) + 1);
            
    current_alignment +=  CdrSizes::DOUBLE->serialized_size(
        current_alignment);
            
    current_alignment +=  CdrSizes::DOUBLE->serialized_size(
        current_alignment);
            
    current_alignment +=  CdrSizes::DOUBLE->serialized_size(
        current_alignment);
            
    current_alignment +=  CdrSizes::DOUBLE->serialized_size(
        current_alignment);
            
    current_alignment +=  CdrSizes::DOUBLE->serialized_size(
        current_alignment);
            
    current_alignment +=  CdrSizes::DOUBLE->serialized_size(
        current_alignment);
            
    current_alignment +=  CdrSizes::DOUBLE->serialized_size(
        current_alignment);
            
    current_alignment +=  CdrSizes::DOUBLE->serialized_size(
        current_alignment);
            
    current_alignment +=  CdrSizes::DOUBLE->serialized_size(
        current_alignment);
            
    current_alignment +=  CdrSizes::DOUBLE->serialized_size(
        current_alignment);
            
    current_alignment +=  CdrSizes::DOUBLE->serialized_size(
        current_alignment);
            
    current_alignment +=  CdrSizes::DOUBLE->serialized_size(
        current_alignment);
            
    if (include_encapsulation) {
        current_alignment += encapsulation_size;
    }

    return current_alignment - initial_alignment;
}


UInt32
AggregateRunningDataPlugin::get_serialized_sample_min_size(
    TypePluginDefaultEndpointData^ endpoint_data,
    Boolean include_encapsulation,
    UInt16 encapsulation_id,
    UInt32 current_alignment)
{

    UInt32 initial_alignment = current_alignment;

    UInt32 encapsulation_size = current_alignment;


    if (include_encapsulation) {
        if (!CdrStream::valid_encapsulation_id(encapsulation_id)) {
            return 1;
        }


        encapsulation_size = CdrSizes::ENCAPSULATION->serialized_size(
            encapsulation_size);
        current_alignment = 0;
        initial_alignment = 0;

    }


    current_alignment +=  CdrSizes::LONG_LONG->serialized_size(
        current_alignment);
            
    current_alignment +=  CdrSizes::STRING->serialized_size(
        current_alignment, 1);
            
    current_alignment +=  CdrSizes::DOUBLE->serialized_size(
        current_alignment);
            
    current_alignment +=  CdrSizes::DOUBLE->serialized_size(
        current_alignment);
            
    current_alignment +=  CdrSizes::DOUBLE->serialized_size(
        current_alignment);
            
    current_alignment +=  CdrSizes::DOUBLE->serialized_size(
        current_alignment);
            
    current_alignment +=  CdrSizes::DOUBLE->serialized_size(
        current_alignment);
            
    current_alignment +=  CdrSizes::DOUBLE->serialized_size(
        current_alignment);
            
    current_alignment +=  CdrSizes::DOUBLE->serialized_size(
        current_alignment);
            
    current_alignment +=  CdrSizes::DOUBLE->serialized_size(
        current_alignment);
            
    current_alignment +=  CdrSizes::DOUBLE->serialized_size(
        current_alignment);
            
    current_alignment +=  CdrSizes::DOUBLE->serialized_size(
        current_alignment);
            
    current_alignment +=  CdrSizes::DOUBLE->serialized_size(
        current_alignment);
            
    current_alignment +=  CdrSizes::DOUBLE->serialized_size(
        current_alignment);
            
    if (include_encapsulation) {
        current_alignment += encapsulation_size;
    }

    return current_alignment - initial_alignment;
}


UInt32 
AggregateRunningDataPlugin::get_serialized_sample_size(
    TypePluginDefaultEndpointData^ endpoint_data,
    Boolean include_encapsulation,
    UInt16 encapsulation_id,
    UInt32 current_alignment,
    AggregateRunningData^ sample)
{

    UInt32 initial_alignment = current_alignment;

    UInt32 encapsulation_size = current_alignment;


    if (include_encapsulation) {
        if (!CdrStream::valid_encapsulation_id(encapsulation_id)) {
            return 1;
        }


        encapsulation_size = CdrSizes::ENCAPSULATION->serialized_size(
            current_alignment);
        encapsulation_size -= current_alignment;
        current_alignment = 0;
        initial_alignment = 0;

    }


    current_alignment += CdrSizes::LONG_LONG->serialized_size(
        current_alignment);
            
    current_alignment += CdrSizes::STRING->serialized_size(current_alignment, sample->player_id);
            
    current_alignment += CdrSizes::DOUBLE->serialized_size(
        current_alignment);
            
    current_alignment += CdrSizes::DOUBLE->serialized_size(
        current_alignment);
            
    current_alignment += CdrSizes::DOUBLE->serialized_size(
        current_alignment);
            
    current_alignment += CdrSizes::DOUBLE->serialized_size(
        current_alignment);
            
    current_alignment += CdrSizes::DOUBLE->serialized_size(
        current_alignment);
            
    current_alignment += CdrSizes::DOUBLE->serialized_size(
        current_alignment);
            
    current_alignment += CdrSizes::DOUBLE->serialized_size(
        current_alignment);
            
    current_alignment += CdrSizes::DOUBLE->serialized_size(
        current_alignment);
            
    current_alignment += CdrSizes::DOUBLE->serialized_size(
        current_alignment);
            
    current_alignment += CdrSizes::DOUBLE->serialized_size(
        current_alignment);
            
    current_alignment += CdrSizes::DOUBLE->serialized_size(
        current_alignment);
            
    current_alignment += CdrSizes::DOUBLE->serialized_size(
        current_alignment);
            
    if (include_encapsulation) {
        current_alignment += encapsulation_size;
    }

    return current_alignment - initial_alignment;
}


UInt32
AggregateRunningDataPlugin::get_serialized_key_max_size(
    TypePluginDefaultEndpointData^ endpoint_data,
    Boolean include_encapsulation,
    UInt16 encapsulation_id,
    UInt32 current_alignment)
{

    UInt32 encapsulation_size = current_alignment;


    UInt32 initial_alignment = current_alignment;

    if (include_encapsulation) {
        if (!CdrStream::valid_encapsulation_id(encapsulation_id)) {
            return 1;
        }


        encapsulation_size = CdrSizes::ENCAPSULATION->serialized_size(
            current_alignment);
        current_alignment = 0;
        initial_alignment = 0;

    }
        

    current_alignment +=  CdrSizes::STRING->serialized_size(
        current_alignment, (255) + 1);
            
    if (include_encapsulation) {
        current_alignment += encapsulation_size;
    }

    return current_alignment - initial_alignment;
}

/* ------------------------------------------------------------------------
    Key Management functions:
 * ------------------------------------------------------------------------ */

Boolean 
AggregateRunningDataPlugin::serialize_key(
    TypePluginDefaultEndpointData^ endpoint_data,
    AggregateRunningData^ sample,
    CdrStream% stream,    
    Boolean serialize_encapsulation,
    UInt16 encapsulation_id,
    Boolean serialize_key,
    Object^ endpoint_plugin_qos)
{
    CdrStreamPosition position;

    if (serialize_encapsulation) {
        /* Encapsulate sample */

        if (!stream.serialize_and_set_cdr_encapsulation(encapsulation_id)) {
            return false;
        }


        position = stream.reset_alignment();

    }

    if (serialize_key) {

    if (!stream.serialize_string(sample->player_id, (255))) {
        return false;
    }
            
    }


    if(serialize_encapsulation) {
        stream.restore_alignment(position);
    }


    return true;
}


Boolean AggregateRunningDataPlugin::deserialize_key_sample(
    TypePluginDefaultEndpointData^ endpoint_data,
    AggregateRunningData^ sample,
    CdrStream% stream, 
    Boolean deserialize_encapsulation,
    Boolean deserialize_key,
    Object^ endpoint_plugin_qos)
{
    CdrStreamPosition position;

    if (deserialize_encapsulation) {
        /* Deserialize encapsulation */
        if (!stream.deserialize_and_set_cdr_encapsulation()) {
            return false;  
        }


        position = stream.reset_alignment();

    }

    if (deserialize_key) {

    sample->player_id = stream.deserialize_string((255)); 
    if (sample->player_id == nullptr) {
        return false;
    }
            
    }


    if(deserialize_encapsulation) {
        stream.restore_alignment(position);
    }


    return true;
}


Boolean
AggregateRunningDataPlugin::serialized_sample_to_key(
    TypePluginDefaultEndpointData^ endpoint_data,
    AggregateRunningData^ sample,
    CdrStream% stream, 
    Boolean deserialize_encapsulation,  
    Boolean deserialize_key, 
    Object^ endpoint_plugin_qos)
{
    CdrStreamPosition position;

    if(deserialize_encapsulation) {
        if (!stream.deserialize_and_set_cdr_encapsulation()) {
            return false;
        }

        position = stream.reset_alignment();

    }

    if (deserialize_key) {

    if (!stream.skip_long_long()) {
        return false;
    }
            
    sample->player_id = stream.deserialize_string((255)); 
    if (sample->player_id == nullptr) {
        return false;
    }
            
    if (!stream.skip_double()) {
        return false;
    }
            
    if (!stream.skip_double()) {
        return false;
    }
            
    if (!stream.skip_double()) {
        return false;
    }
            
    if (!stream.skip_double()) {
        return false;
    }
            
    if (!stream.skip_double()) {
        return false;
    }
            
    if (!stream.skip_double()) {
        return false;
    }
            
    if (!stream.skip_double()) {
        return false;
    }
            
    if (!stream.skip_double()) {
        return false;
    }
            
    if (!stream.skip_double()) {
        return false;
    }
            
    if (!stream.skip_double()) {
        return false;
    }
            
    if (!stream.skip_double()) {
        return false;
    }
            
    if (!stream.skip_double()) {
        return false;
    }
            
    }


    if(deserialize_encapsulation) {
        stream.restore_alignment(position);
    }


    return true;
}



Boolean 
AggregateRunningDataPlugin::instance_to_key(
    TypePluginDefaultEndpointData^ endpoint_data,
    AggregateRunningData^ dst, 
    AggregateRunningData^ src)
{

    dst->player_id = src->player_id;
    return true;
}

Boolean 
AggregateRunningDataPlugin::key_to_instance(
    TypePluginDefaultEndpointData^ endpoint_data,
    AggregateRunningData^ dst,
    AggregateRunningData^ src)
{

    dst->player_id = src->player_id;
    return true;
}


Boolean 
AggregateRunningDataPlugin::serialized_sample_to_key_hash(
    TypePluginDefaultEndpointData^ endpoint_data,
    CdrStream% stream, 
    KeyHash_t% key_hash,
    Boolean deserialize_encapsulation,
    Object^ endpoint_plugin_qos) 
{   
    CdrStreamPosition position;


    if(deserialize_encapsulation) {
        if (!stream.deserialize_and_set_cdr_encapsulation()) {
            return false;
        }

        position = stream.reset_alignment();
    }

    
    GCHandle sample_handle = GCHandle::FromIntPtr(IntPtr(const_cast<void*>(endpoint_data->get_temp_sample())));
    AggregateRunningData^ sample = static_cast<AggregateRunningData^>(sample_handle.Target);
    if (sample == nullptr) {
        return false;
    }


    if (!stream.skip_long_long()) {
        return false;
    }
            
    sample->player_id = stream.deserialize_string((255)); 
    if (sample->player_id == nullptr) {
        return false;
    }
            
    if(deserialize_encapsulation) {
        stream.restore_alignment(position);
    }


    if (!instance_to_key_hash(
            endpoint_data, key_hash, sample)) {
        return false;
    }

    return true;
}



/* ------------------------------------------------------------------------
 * Plug-in Lifecycle Methods
 * ------------------------------------------------------------------------ */

AggregateRunningDataPlugin^
AggregateRunningDataPlugin::get_instance() {
    if (_singleton == nullptr) {
        _singleton = gcnew AggregateRunningDataPlugin();
    }
    return _singleton;
}


void
AggregateRunningDataPlugin::dispose() {
    delete _singleton;
    _singleton = nullptr;
}


/* ------------------------------------------------------------------------
  Enum Type: Intensity
 * ------------------------------------------------------------------------ */

/* ------------------------------------------------------------------------
 * (De)Serialization Methods
 * ------------------------------------------------------------------------ */


Boolean
IntensityPlugin::serialize(
    TypePluginEndpointData^ endpoint_data,
    Intensity sample,
    CdrStream% stream, 
    Boolean serialize_encapsulation,
    UInt16 encapsulation_id,
    Boolean serialize_sample,
    Object^ endpoint_plugin_qos)
{
    CdrStreamPosition position;

    if (serialize_encapsulation) {
        if (!stream.serialize_and_set_cdr_encapsulation(encapsulation_id)) {
            return false;
        }

        position = stream.reset_alignment();

    }

    if (serialize_sample) {

        if (!stream.serialize_enum(sample)) {
            return false;
        }

    }


    if (serialize_encapsulation) {
        stream.restore_alignment(position);

    }

    return true;
}


Boolean 
IntensityPlugin::deserialize_sample(
    TypePluginEndpointData^ endpoint_data,
    Intensity% sample,
    CdrStream% stream, 
    Boolean deserialize_encapsulation,  
    Boolean deserialize_data, 
    Object^ endpoint_plugin_qos)
{
    CdrStreamPosition position;

    if (deserialize_encapsulation) {
        if (!stream.deserialize_and_set_cdr_encapsulation()) {
            return false;
        }


        position = stream.reset_alignment();

    }

    if (deserialize_data) {


        sample = stream.deserialize_enum<Intensity>();

        switch (sample) {

            case Intensity::STOP:

            case Intensity::TROT:

            case Intensity::LOW:

            case Intensity::MEDIUM:

            case Intensity::HIGH:

            case Intensity::SPRINT:

            {
            } break;
            default:
            {
                throw gcnew Unassignable("invalid enumerator " + sample.ToString());
            } break;
        }

    }

    if(deserialize_encapsulation) {
        stream.restore_alignment(position);
    }


    return true;
}


Boolean
IntensityPlugin::skip(
    TypePluginEndpointData^ endpoint_data,
    CdrStream% stream, 
    Boolean skip_encapsulation,  
    Boolean skip_sample, 
    Object^ endpoint_plugin_qos)
{
    CdrStreamPosition position;

    if (skip_encapsulation) {
        if (!stream.skip_encapsulation()) {
            return false;
        }

        position = stream.reset_alignment();

    }
    if (skip_sample) {

        if (!stream.skip_enum()) {
            return false;
        }


    }


    if(skip_encapsulation) {
        stream.restore_alignment(position);
    }


    return true;
}


UInt32
IntensityPlugin::get_serialized_sample_max_size(
    TypePluginEndpointData^ endpoint_data,
    Boolean include_encapsulation,
    UInt16 encapsulation_id,
    UInt32 current_alignment)
{
    UInt32 initial_alignment = current_alignment;

    UInt32 encapsulation_size = current_alignment;


    if (include_encapsulation) {
        if (!CdrStream::valid_encapsulation_id(encapsulation_id)) {
            return 1;
        }


        encapsulation_size = CdrSizes::ENCAPSULATION->serialized_size(
            current_alignment);
        current_alignment = 0;
        initial_alignment = 0;

    }

    current_alignment += RTICdrType_getEnumMaxSizeSerialized(current_alignment);


    if (include_encapsulation) {
        current_alignment += encapsulation_size;
    }


    return current_alignment - initial_alignment;
}


UInt32
IntensityPlugin::get_serialized_sample_min_size(
    TypePluginEndpointData^ endpoint_data,
    Boolean include_encapsulation,
    UInt16 encapsulation_id,
    UInt32 current_alignment)
{
    UInt32 initial_alignment = current_alignment;

    UInt32 encapsulation_size = current_alignment;


    if (include_encapsulation) {
        if (!CdrStream::valid_encapsulation_id(encapsulation_id)) {
            return 1;
        }


        encapsulation_size = CdrSizes::ENCAPSULATION->serialized_size(
            current_alignment);
        current_alignment = 0;
        initial_alignment = 0;

    }

    current_alignment += RTICdrType_getEnumMaxSizeSerialized(current_alignment);


    if (include_encapsulation) {
        current_alignment += encapsulation_size;
    }


    return current_alignment - initial_alignment;
}


UInt32
IntensityPlugin::get_serialized_sample_size(
    TypePluginEndpointData^ endpoint_data,
    Boolean include_encapsulation,
    UInt16 encapsulation_id,
    UInt32 current_alignment,
    Intensity sample) 
{
    UInt32 initial_alignment = current_alignment;

    UInt32 encapsulation_size = current_alignment;


    if (include_encapsulation) {
        if (!CdrStream::valid_encapsulation_id(encapsulation_id)) {
            return 1;
        }


        encapsulation_size = CdrSizes::ENCAPSULATION->serialized_size(
            current_alignment);
        current_alignment = 0;
        initial_alignment = 0;

    }

    current_alignment += RTICdrType_getEnumMaxSizeSerialized(current_alignment);


    if (include_encapsulation) {
        current_alignment += encapsulation_size;
    }


    return current_alignment - initial_alignment;
}

/* ------------------------------------------------------------------------
    Key Management functions:
 * ------------------------------------------------------------------------ */


Boolean
IntensityPlugin::serialize_key(
    TypePluginEndpointData^ endpoint_data,
    Intensity sample,
    CdrStream% stream,
    Boolean serialize_encapsulation,
    UInt16 encapsulation_id,
    Boolean serialize_key,
    Object^ endpoint_plugin_qos)
{
    return serialize(
            endpoint_data, sample, stream, serialize_encapsulation, 
            encapsulation_id, 
            serialize_key, endpoint_plugin_qos);
}


Boolean
IntensityPlugin::deserialize_key_sample(
    TypePluginEndpointData^ endpoint_data,
    Intensity% sample,
    CdrStream% stream,
    Boolean deserialize_encapsulation,
    Boolean deserialize_key,
    Object^ endpoint_plugin_qos)
{
    return deserialize_sample(
            endpoint_data, sample, stream, deserialize_encapsulation, 
            deserialize_key, endpoint_plugin_qos);
}


UInt32
IntensityPlugin::get_serialized_key_max_size(
    TypePluginEndpointData^ endpoint_data,
    Boolean include_encapsulation,
    UInt16 encapsulation_id,
    UInt32 current_alignment)
{
    UInt32 initial_alignment = current_alignment;

    current_alignment += get_serialized_sample_max_size(
        endpoint_data,include_encapsulation,
        encapsulation_id,current_alignment);

    return current_alignment - initial_alignment;
}


Boolean
IntensityPlugin::serialized_sample_to_key(
    TypePluginEndpointData^ endpoint_data,
    Intensity% sample,
    CdrStream% stream, 
    Boolean deserialize_encapsulation,  
    Boolean deserialize_key, 
    Object^ endpoint_plugin_qos)
{    
    return deserialize_sample(
            endpoint_data,
            sample,
            stream,
            deserialize_encapsulation, 
            deserialize_key,
            endpoint_plugin_qos);
}


/* ------------------------------------------------------------------------
   Support functions:
 * ------------------------------------------------------------------------ */


void
IntensityPlugin::print_data(
    Intensity sample,
    String^ description,
    UInt32 indent_level)
{
    if (description != nullptr) {
        for (UInt32 i = 0; i < indent_level; ++i) { Console::Write("   "); }
        Console::WriteLine("{0}:", description);
    }

    RTICdrType_printEnum((RTICdrEnum*) &sample,
                         "Intensity", indent_level + 1);
}


/* ------------------------------------------------------------------------
 * Plug-in Lifecycle Methods
 * ------------------------------------------------------------------------ */

IntensityPlugin^
IntensityPlugin::get_instance() {
    if (_singleton == nullptr) {
        _singleton = gcnew IntensityPlugin();
    }
    return _singleton;
}


void
IntensityPlugin::dispose() {
    delete _singleton;
    _singleton = nullptr;
}


/* ------------------------------------------------------------------------
 *  Type CurrentRunningData
 * ------------------------------------------------------------------------ */

/* ------------------------------------------------------------------------
    Support functions:
 * ------------------------------------------------------------------------ */

void 
CurrentRunningDataPlugin::print_data(
        CurrentRunningData^ sample,
        String^ desc,
        UInt32 indent_level) {

    for (UInt32 i = 0; i < indent_level; ++i) { Console::Write("   "); }

    if (desc != nullptr) {
        Console::WriteLine("{0}:", desc);
    } else {
        Console::WriteLine();
    }

    if (sample == nullptr) {
        Console::WriteLine("null");
        return;
    }


    DataPrintUtility::print_object(
        sample->ts_start, "ts_start", indent_level);
            
    DataPrintUtility::print_object(
        sample->ts_stop, "ts_stop", indent_level);
            
    DataPrintUtility::print_object(
        sample->player_id, "player_id", indent_level);
            
    DataPrintUtility::print_object(
        sample->intensity, "intensity", indent_level);
            
    DataPrintUtility::print_object(
        sample->distance, "distance", indent_level);
            
    DataPrintUtility::print_object(
        sample->speed, "speed", indent_level);
            
}


/* ------------------------------------------------------------------------
    (De)Serialize functions:
 * ------------------------------------------------------------------------ */

Boolean 
CurrentRunningDataPlugin::serialize(
    TypePluginDefaultEndpointData^ endpoint_data,
    CurrentRunningData^ sample,
    CdrStream% stream,    
    Boolean serialize_encapsulation,
    UInt16 encapsulation_id,
    Boolean serialize_sample, 
    Object^ endpoint_plugin_qos)
{
    CdrStreamPosition position;

    

    if (serialize_encapsulation) {
        /* Encapsulate sample */
        
        if (!stream.serialize_and_set_cdr_encapsulation(encapsulation_id)) {
            return false;
        }


        position = stream.reset_alignment();

    }

    if (serialize_sample) {

    if (!stream.serialize_long_long(sample->ts_start)) {
        return false;
    }
            
    if (!stream.serialize_long_long(sample->ts_stop)) {
        return false;
    }
            
    if (!stream.serialize_string(sample->player_id, (255))) {
        return false;
    }
            
    if (!IntensityPlugin::get_instance()->serialize(
            endpoint_data,
            sample->intensity,
            stream,
            false, // serialize encapsulation
            encapsulation_id,
            true,  // serialize data 
            endpoint_plugin_qos)) {
        return false;
    }
            
    if (!stream.serialize_double(sample->distance)) {
        return false;
    }
            
    if (!stream.serialize_double(sample->speed)) {
        return false;
    }
            
    }


    if(serialize_encapsulation) {
        stream.restore_alignment(position);
    }


    return true;
}


Boolean 
CurrentRunningDataPlugin::deserialize_sample(
    TypePluginDefaultEndpointData^ endpoint_data,
    CurrentRunningData^ sample,
    CdrStream% stream,   
    Boolean deserialize_encapsulation,
    Boolean deserialize_data, 
    Object^ endpoint_plugin_qos)
{
    CdrStreamPosition position;

    if(deserialize_encapsulation) {
        /* Deserialize encapsulation */
        if (!stream.deserialize_and_set_cdr_encapsulation()) {
            return false;
        }


        position = stream.reset_alignment();

    }

    if (deserialize_data) {
        sample->clear();

    try {
  
    sample->ts_start = stream.deserialize_long_long();
            
    sample->ts_stop = stream.deserialize_long_long();
            
    sample->player_id = stream.deserialize_string((255)); 
    if (sample->player_id == nullptr) {
        return false;
    }
            
    if (!IntensityPlugin::get_instance()->deserialize_sample(
            endpoint_data,
            sample->intensity,
            stream,
            false, // deserialize encapsulation
            true,  // deserialize data
            endpoint_plugin_qos)) {
        return false;
    }
            
    sample->distance = stream.deserialize_double();
            
    sample->speed = stream.deserialize_double();
            
    } catch (System::ApplicationException^  e) {
        if (stream.get_remainder() >= RTI_CDR_PARAMETER_HEADER_ALIGNMENT) {
            throw gcnew System::ApplicationException("Error deserializing sample! Remainder: " + stream.get_remainder() + "\n" +
                                                              "Exception caused by: " + e->Message);
        }
    }

    }


    if(deserialize_encapsulation) {
        stream.restore_alignment(position);
    }


    return true;
}


Boolean
CurrentRunningDataPlugin::skip(
    TypePluginDefaultEndpointData^ endpoint_data,
    CdrStream% stream,   
    Boolean skip_encapsulation,
    Boolean skip_sample, 
    Object^ endpoint_plugin_qos)
{
    CdrStreamPosition position;


    if (skip_encapsulation) {
        if (!stream.skip_encapsulation()) {
            return false;
        }

        position = stream.reset_alignment();

    }

    if (skip_sample) {

    if (!stream.skip_long_long()) {
        return false;
    }
            
    if (!stream.skip_long_long()) {
        return false;
    }
            
    if (!stream.skip_string((255) + 1)) {
        return false;
    }
            
    if (!IntensityPlugin::get_instance()->skip(
            endpoint_data,
            stream, 
            false, true, 
            endpoint_plugin_qos)) {
        return false;
    }
            
    if (!stream.skip_double()) {
        return false;
    }
            
    if (!stream.skip_double()) {
        return false;
    }
            
    }


    if(skip_encapsulation) {
        stream.restore_alignment(position);
    }


    return true;
}

/*
  size is the offset from the point where we have do a logical reset
  Return difference in size, not the final offset.
*/
UInt32 
CurrentRunningDataPlugin::get_serialized_sample_max_size(
    TypePluginDefaultEndpointData^ endpoint_data,
    Boolean include_encapsulation,
    UInt16 encapsulation_id,
    UInt32 current_alignment)
{

    UInt32 initial_alignment = current_alignment;

    UInt32 encapsulation_size = current_alignment;


    if (include_encapsulation) {
        if (!CdrStream::valid_encapsulation_id(encapsulation_id)) {
            return 1;
        }


        encapsulation_size = CdrSizes::ENCAPSULATION->serialized_size(
            current_alignment);
        encapsulation_size -= current_alignment;
        current_alignment = 0;
        initial_alignment = 0;

    }


    current_alignment +=  CdrSizes::LONG_LONG->serialized_size(
        current_alignment);
            
    current_alignment +=  CdrSizes::LONG_LONG->serialized_size(
        current_alignment);
            
    current_alignment +=  CdrSizes::STRING->serialized_size(
        current_alignment, (255) + 1);
            
    current_alignment +=  IntensityPlugin::get_instance()->get_serialized_sample_max_size(
        endpoint_data, false, encapsulation_id, current_alignment);
            
    current_alignment +=  CdrSizes::DOUBLE->serialized_size(
        current_alignment);
            
    current_alignment +=  CdrSizes::DOUBLE->serialized_size(
        current_alignment);
            
    if (include_encapsulation) {
        current_alignment += encapsulation_size;
    }

    return current_alignment - initial_alignment;
}


UInt32
CurrentRunningDataPlugin::get_serialized_sample_min_size(
    TypePluginDefaultEndpointData^ endpoint_data,
    Boolean include_encapsulation,
    UInt16 encapsulation_id,
    UInt32 current_alignment)
{

    UInt32 initial_alignment = current_alignment;

    UInt32 encapsulation_size = current_alignment;


    if (include_encapsulation) {
        if (!CdrStream::valid_encapsulation_id(encapsulation_id)) {
            return 1;
        }


        encapsulation_size = CdrSizes::ENCAPSULATION->serialized_size(
            encapsulation_size);
        current_alignment = 0;
        initial_alignment = 0;

    }


    current_alignment +=  CdrSizes::LONG_LONG->serialized_size(
        current_alignment);
            
    current_alignment +=  CdrSizes::LONG_LONG->serialized_size(
        current_alignment);
            
    current_alignment +=  CdrSizes::STRING->serialized_size(
        current_alignment, 1);
            
    current_alignment +=  IntensityPlugin::get_instance()->get_serialized_sample_min_size(
        endpoint_data, false, encapsulation_id, current_alignment);
            
    current_alignment +=  CdrSizes::DOUBLE->serialized_size(
        current_alignment);
            
    current_alignment +=  CdrSizes::DOUBLE->serialized_size(
        current_alignment);
            
    if (include_encapsulation) {
        current_alignment += encapsulation_size;
    }

    return current_alignment - initial_alignment;
}


UInt32 
CurrentRunningDataPlugin::get_serialized_sample_size(
    TypePluginDefaultEndpointData^ endpoint_data,
    Boolean include_encapsulation,
    UInt16 encapsulation_id,
    UInt32 current_alignment,
    CurrentRunningData^ sample)
{

    UInt32 initial_alignment = current_alignment;

    UInt32 encapsulation_size = current_alignment;


    if (include_encapsulation) {
        if (!CdrStream::valid_encapsulation_id(encapsulation_id)) {
            return 1;
        }


        encapsulation_size = CdrSizes::ENCAPSULATION->serialized_size(
            current_alignment);
        encapsulation_size -= current_alignment;
        current_alignment = 0;
        initial_alignment = 0;

    }


    current_alignment += CdrSizes::LONG_LONG->serialized_size(
        current_alignment);
            
    current_alignment += CdrSizes::LONG_LONG->serialized_size(
        current_alignment);
            
    current_alignment += CdrSizes::STRING->serialized_size(current_alignment, sample->player_id);
            
    current_alignment += IntensityPlugin::get_instance()->get_serialized_sample_size(
        endpoint_data, false, encapsulation_id, current_alignment, sample->intensity);
            
    current_alignment += CdrSizes::DOUBLE->serialized_size(
        current_alignment);
            
    current_alignment += CdrSizes::DOUBLE->serialized_size(
        current_alignment);
            
    if (include_encapsulation) {
        current_alignment += encapsulation_size;
    }

    return current_alignment - initial_alignment;
}


UInt32
CurrentRunningDataPlugin::get_serialized_key_max_size(
    TypePluginDefaultEndpointData^ endpoint_data,
    Boolean include_encapsulation,
    UInt16 encapsulation_id,
    UInt32 current_alignment)
{

    UInt32 encapsulation_size = current_alignment;


    UInt32 initial_alignment = current_alignment;

    if (include_encapsulation) {
        if (!CdrStream::valid_encapsulation_id(encapsulation_id)) {
            return 1;
        }


        encapsulation_size = CdrSizes::ENCAPSULATION->serialized_size(
            current_alignment);
        current_alignment = 0;
        initial_alignment = 0;

    }
        

    current_alignment +=  CdrSizes::STRING->serialized_size(
        current_alignment, (255) + 1);
            
    if (include_encapsulation) {
        current_alignment += encapsulation_size;
    }

    return current_alignment - initial_alignment;
}

/* ------------------------------------------------------------------------
    Key Management functions:
 * ------------------------------------------------------------------------ */

Boolean 
CurrentRunningDataPlugin::serialize_key(
    TypePluginDefaultEndpointData^ endpoint_data,
    CurrentRunningData^ sample,
    CdrStream% stream,    
    Boolean serialize_encapsulation,
    UInt16 encapsulation_id,
    Boolean serialize_key,
    Object^ endpoint_plugin_qos)
{
    CdrStreamPosition position;

    if (serialize_encapsulation) {
        /* Encapsulate sample */

        if (!stream.serialize_and_set_cdr_encapsulation(encapsulation_id)) {
            return false;
        }


        position = stream.reset_alignment();

    }

    if (serialize_key) {

    if (!stream.serialize_string(sample->player_id, (255))) {
        return false;
    }
            
    }


    if(serialize_encapsulation) {
        stream.restore_alignment(position);
    }


    return true;
}


Boolean CurrentRunningDataPlugin::deserialize_key_sample(
    TypePluginDefaultEndpointData^ endpoint_data,
    CurrentRunningData^ sample,
    CdrStream% stream, 
    Boolean deserialize_encapsulation,
    Boolean deserialize_key,
    Object^ endpoint_plugin_qos)
{
    CdrStreamPosition position;

    if (deserialize_encapsulation) {
        /* Deserialize encapsulation */
        if (!stream.deserialize_and_set_cdr_encapsulation()) {
            return false;  
        }


        position = stream.reset_alignment();

    }

    if (deserialize_key) {

    sample->player_id = stream.deserialize_string((255)); 
    if (sample->player_id == nullptr) {
        return false;
    }
            
    }


    if(deserialize_encapsulation) {
        stream.restore_alignment(position);
    }


    return true;
}


Boolean
CurrentRunningDataPlugin::serialized_sample_to_key(
    TypePluginDefaultEndpointData^ endpoint_data,
    CurrentRunningData^ sample,
    CdrStream% stream, 
    Boolean deserialize_encapsulation,  
    Boolean deserialize_key, 
    Object^ endpoint_plugin_qos)
{
    CdrStreamPosition position;

    if(deserialize_encapsulation) {
        if (!stream.deserialize_and_set_cdr_encapsulation()) {
            return false;
        }

        position = stream.reset_alignment();

    }

    if (deserialize_key) {

    if (!stream.skip_long_long()) {
        return false;
    }
            
    if (!stream.skip_long_long()) {
        return false;
    }
            
    sample->player_id = stream.deserialize_string((255)); 
    if (sample->player_id == nullptr) {
        return false;
    }
            
    if (!IntensityPlugin::get_instance()->skip(
            endpoint_data,
            stream, 
            false, true, 
            endpoint_plugin_qos)) {
        return false;
    }
            
    if (!stream.skip_double()) {
        return false;
    }
            
    if (!stream.skip_double()) {
        return false;
    }
            
    }


    if(deserialize_encapsulation) {
        stream.restore_alignment(position);
    }


    return true;
}



Boolean 
CurrentRunningDataPlugin::instance_to_key(
    TypePluginDefaultEndpointData^ endpoint_data,
    CurrentRunningData^ dst, 
    CurrentRunningData^ src)
{

    dst->player_id = src->player_id;
    return true;
}

Boolean 
CurrentRunningDataPlugin::key_to_instance(
    TypePluginDefaultEndpointData^ endpoint_data,
    CurrentRunningData^ dst,
    CurrentRunningData^ src)
{

    dst->player_id = src->player_id;
    return true;
}


Boolean 
CurrentRunningDataPlugin::serialized_sample_to_key_hash(
    TypePluginDefaultEndpointData^ endpoint_data,
    CdrStream% stream, 
    KeyHash_t% key_hash,
    Boolean deserialize_encapsulation,
    Object^ endpoint_plugin_qos) 
{   
    CdrStreamPosition position;


    if(deserialize_encapsulation) {
        if (!stream.deserialize_and_set_cdr_encapsulation()) {
            return false;
        }

        position = stream.reset_alignment();
    }

    
    GCHandle sample_handle = GCHandle::FromIntPtr(IntPtr(const_cast<void*>(endpoint_data->get_temp_sample())));
    CurrentRunningData^ sample = static_cast<CurrentRunningData^>(sample_handle.Target);
    if (sample == nullptr) {
        return false;
    }


    if (!stream.skip_long_long()) {
        return false;
    }
            
    if (!stream.skip_long_long()) {
        return false;
    }
            
    sample->player_id = stream.deserialize_string((255)); 
    if (sample->player_id == nullptr) {
        return false;
    }
            
    if(deserialize_encapsulation) {
        stream.restore_alignment(position);
    }


    if (!instance_to_key_hash(
            endpoint_data, key_hash, sample)) {
        return false;
    }

    return true;
}



/* ------------------------------------------------------------------------
 * Plug-in Lifecycle Methods
 * ------------------------------------------------------------------------ */

CurrentRunningDataPlugin^
CurrentRunningDataPlugin::get_instance() {
    if (_singleton == nullptr) {
        _singleton = gcnew CurrentRunningDataPlugin();
    }
    return _singleton;
}


void
CurrentRunningDataPlugin::dispose() {
    delete _singleton;
    _singleton = nullptr;
}

/* ------------------------------------------------------------------------
 *  Type PlayerBallPossession
 * ------------------------------------------------------------------------ */

/* ------------------------------------------------------------------------
    Support functions:
 * ------------------------------------------------------------------------ */

void 
PlayerBallPossessionPlugin::print_data(
        PlayerBallPossession^ sample,
        String^ desc,
        UInt32 indent_level) {

    for (UInt32 i = 0; i < indent_level; ++i) { Console::Write("   "); }

    if (desc != nullptr) {
        Console::WriteLine("{0}:", desc);
    } else {
        Console::WriteLine();
    }

    if (sample == nullptr) {
        Console::WriteLine("null");
        return;
    }


    DataPrintUtility::print_object(
        sample->ts, "ts", indent_level);
            
    DataPrintUtility::print_object(
        sample->player_id, "player_id", indent_level);
            
    DataPrintUtility::print_object(
        sample->time, "time", indent_level);
            
    DataPrintUtility::print_object(
        sample->hits, "hits", indent_level);
            
}


/* ------------------------------------------------------------------------
    (De)Serialize functions:
 * ------------------------------------------------------------------------ */

Boolean 
PlayerBallPossessionPlugin::serialize(
    TypePluginDefaultEndpointData^ endpoint_data,
    PlayerBallPossession^ sample,
    CdrStream% stream,    
    Boolean serialize_encapsulation,
    UInt16 encapsulation_id,
    Boolean serialize_sample, 
    Object^ endpoint_plugin_qos)
{
    CdrStreamPosition position;

    

    if (serialize_encapsulation) {
        /* Encapsulate sample */
        
        if (!stream.serialize_and_set_cdr_encapsulation(encapsulation_id)) {
            return false;
        }


        position = stream.reset_alignment();

    }

    if (serialize_sample) {

    if (!stream.serialize_long_long(sample->ts)) {
        return false;
    }
            
    if (!stream.serialize_string(sample->player_id, (255))) {
        return false;
    }
            
    if (!stream.serialize_double(sample->time)) {
        return false;
    }
            
    if (!stream.serialize_long(sample->hits)) {
        return false;
    }
            
    }


    if(serialize_encapsulation) {
        stream.restore_alignment(position);
    }


    return true;
}


Boolean 
PlayerBallPossessionPlugin::deserialize_sample(
    TypePluginDefaultEndpointData^ endpoint_data,
    PlayerBallPossession^ sample,
    CdrStream% stream,   
    Boolean deserialize_encapsulation,
    Boolean deserialize_data, 
    Object^ endpoint_plugin_qos)
{
    CdrStreamPosition position;

    if(deserialize_encapsulation) {
        /* Deserialize encapsulation */
        if (!stream.deserialize_and_set_cdr_encapsulation()) {
            return false;
        }


        position = stream.reset_alignment();

    }

    if (deserialize_data) {
        sample->clear();

    try {
  
    sample->ts = stream.deserialize_long_long();
            
    sample->player_id = stream.deserialize_string((255)); 
    if (sample->player_id == nullptr) {
        return false;
    }
            
    sample->time = stream.deserialize_double();
            
    sample->hits = stream.deserialize_long();
            
    } catch (System::ApplicationException^  e) {
        if (stream.get_remainder() >= RTI_CDR_PARAMETER_HEADER_ALIGNMENT) {
            throw gcnew System::ApplicationException("Error deserializing sample! Remainder: " + stream.get_remainder() + "\n" +
                                                              "Exception caused by: " + e->Message);
        }
    }

    }


    if(deserialize_encapsulation) {
        stream.restore_alignment(position);
    }


    return true;
}


Boolean
PlayerBallPossessionPlugin::skip(
    TypePluginDefaultEndpointData^ endpoint_data,
    CdrStream% stream,   
    Boolean skip_encapsulation,
    Boolean skip_sample, 
    Object^ endpoint_plugin_qos)
{
    CdrStreamPosition position;


    if (skip_encapsulation) {
        if (!stream.skip_encapsulation()) {
            return false;
        }

        position = stream.reset_alignment();

    }

    if (skip_sample) {

    if (!stream.skip_long_long()) {
        return false;
    }
            
    if (!stream.skip_string((255) + 1)) {
        return false;
    }
            
    if (!stream.skip_double()) {
        return false;
    }
            
    if (!stream.skip_long()) {
        return false;
    }
            
    }


    if(skip_encapsulation) {
        stream.restore_alignment(position);
    }


    return true;
}

/*
  size is the offset from the point where we have do a logical reset
  Return difference in size, not the final offset.
*/
UInt32 
PlayerBallPossessionPlugin::get_serialized_sample_max_size(
    TypePluginDefaultEndpointData^ endpoint_data,
    Boolean include_encapsulation,
    UInt16 encapsulation_id,
    UInt32 current_alignment)
{

    UInt32 initial_alignment = current_alignment;

    UInt32 encapsulation_size = current_alignment;


    if (include_encapsulation) {
        if (!CdrStream::valid_encapsulation_id(encapsulation_id)) {
            return 1;
        }


        encapsulation_size = CdrSizes::ENCAPSULATION->serialized_size(
            current_alignment);
        encapsulation_size -= current_alignment;
        current_alignment = 0;
        initial_alignment = 0;

    }


    current_alignment +=  CdrSizes::LONG_LONG->serialized_size(
        current_alignment);
            
    current_alignment +=  CdrSizes::STRING->serialized_size(
        current_alignment, (255) + 1);
            
    current_alignment +=  CdrSizes::DOUBLE->serialized_size(
        current_alignment);
            
    current_alignment +=  CdrSizes::LONG->serialized_size(
        current_alignment);
            
    if (include_encapsulation) {
        current_alignment += encapsulation_size;
    }

    return current_alignment - initial_alignment;
}


UInt32
PlayerBallPossessionPlugin::get_serialized_sample_min_size(
    TypePluginDefaultEndpointData^ endpoint_data,
    Boolean include_encapsulation,
    UInt16 encapsulation_id,
    UInt32 current_alignment)
{

    UInt32 initial_alignment = current_alignment;

    UInt32 encapsulation_size = current_alignment;


    if (include_encapsulation) {
        if (!CdrStream::valid_encapsulation_id(encapsulation_id)) {
            return 1;
        }


        encapsulation_size = CdrSizes::ENCAPSULATION->serialized_size(
            encapsulation_size);
        current_alignment = 0;
        initial_alignment = 0;

    }


    current_alignment +=  CdrSizes::LONG_LONG->serialized_size(
        current_alignment);
            
    current_alignment +=  CdrSizes::STRING->serialized_size(
        current_alignment, 1);
            
    current_alignment +=  CdrSizes::DOUBLE->serialized_size(
        current_alignment);
            
    current_alignment +=  CdrSizes::LONG->serialized_size(
        current_alignment);
            
    if (include_encapsulation) {
        current_alignment += encapsulation_size;
    }

    return current_alignment - initial_alignment;
}


UInt32 
PlayerBallPossessionPlugin::get_serialized_sample_size(
    TypePluginDefaultEndpointData^ endpoint_data,
    Boolean include_encapsulation,
    UInt16 encapsulation_id,
    UInt32 current_alignment,
    PlayerBallPossession^ sample)
{

    UInt32 initial_alignment = current_alignment;

    UInt32 encapsulation_size = current_alignment;


    if (include_encapsulation) {
        if (!CdrStream::valid_encapsulation_id(encapsulation_id)) {
            return 1;
        }


        encapsulation_size = CdrSizes::ENCAPSULATION->serialized_size(
            current_alignment);
        encapsulation_size -= current_alignment;
        current_alignment = 0;
        initial_alignment = 0;

    }


    current_alignment += CdrSizes::LONG_LONG->serialized_size(
        current_alignment);
            
    current_alignment += CdrSizes::STRING->serialized_size(current_alignment, sample->player_id);
            
    current_alignment += CdrSizes::DOUBLE->serialized_size(
        current_alignment);
            
    current_alignment += CdrSizes::LONG->serialized_size(
        current_alignment);
            
    if (include_encapsulation) {
        current_alignment += encapsulation_size;
    }

    return current_alignment - initial_alignment;
}


UInt32
PlayerBallPossessionPlugin::get_serialized_key_max_size(
    TypePluginDefaultEndpointData^ endpoint_data,
    Boolean include_encapsulation,
    UInt16 encapsulation_id,
    UInt32 current_alignment)
{

    UInt32 encapsulation_size = current_alignment;


    UInt32 initial_alignment = current_alignment;

    if (include_encapsulation) {
        if (!CdrStream::valid_encapsulation_id(encapsulation_id)) {
            return 1;
        }


        encapsulation_size = CdrSizes::ENCAPSULATION->serialized_size(
            current_alignment);
        current_alignment = 0;
        initial_alignment = 0;

    }
        

    current_alignment +=  CdrSizes::STRING->serialized_size(
        current_alignment, (255) + 1);
            
    if (include_encapsulation) {
        current_alignment += encapsulation_size;
    }

    return current_alignment - initial_alignment;
}

/* ------------------------------------------------------------------------
    Key Management functions:
 * ------------------------------------------------------------------------ */

Boolean 
PlayerBallPossessionPlugin::serialize_key(
    TypePluginDefaultEndpointData^ endpoint_data,
    PlayerBallPossession^ sample,
    CdrStream% stream,    
    Boolean serialize_encapsulation,
    UInt16 encapsulation_id,
    Boolean serialize_key,
    Object^ endpoint_plugin_qos)
{
    CdrStreamPosition position;

    if (serialize_encapsulation) {
        /* Encapsulate sample */

        if (!stream.serialize_and_set_cdr_encapsulation(encapsulation_id)) {
            return false;
        }


        position = stream.reset_alignment();

    }

    if (serialize_key) {

    if (!stream.serialize_string(sample->player_id, (255))) {
        return false;
    }
            
    }


    if(serialize_encapsulation) {
        stream.restore_alignment(position);
    }


    return true;
}


Boolean PlayerBallPossessionPlugin::deserialize_key_sample(
    TypePluginDefaultEndpointData^ endpoint_data,
    PlayerBallPossession^ sample,
    CdrStream% stream, 
    Boolean deserialize_encapsulation,
    Boolean deserialize_key,
    Object^ endpoint_plugin_qos)
{
    CdrStreamPosition position;

    if (deserialize_encapsulation) {
        /* Deserialize encapsulation */
        if (!stream.deserialize_and_set_cdr_encapsulation()) {
            return false;  
        }


        position = stream.reset_alignment();

    }

    if (deserialize_key) {

    sample->player_id = stream.deserialize_string((255)); 
    if (sample->player_id == nullptr) {
        return false;
    }
            
    }


    if(deserialize_encapsulation) {
        stream.restore_alignment(position);
    }


    return true;
}


Boolean
PlayerBallPossessionPlugin::serialized_sample_to_key(
    TypePluginDefaultEndpointData^ endpoint_data,
    PlayerBallPossession^ sample,
    CdrStream% stream, 
    Boolean deserialize_encapsulation,  
    Boolean deserialize_key, 
    Object^ endpoint_plugin_qos)
{
    CdrStreamPosition position;

    if(deserialize_encapsulation) {
        if (!stream.deserialize_and_set_cdr_encapsulation()) {
            return false;
        }

        position = stream.reset_alignment();

    }

    if (deserialize_key) {

    if (!stream.skip_long_long()) {
        return false;
    }
            
    sample->player_id = stream.deserialize_string((255)); 
    if (sample->player_id == nullptr) {
        return false;
    }
            
    if (!stream.skip_double()) {
        return false;
    }
            
    if (!stream.skip_long()) {
        return false;
    }
            
    }


    if(deserialize_encapsulation) {
        stream.restore_alignment(position);
    }


    return true;
}



Boolean 
PlayerBallPossessionPlugin::instance_to_key(
    TypePluginDefaultEndpointData^ endpoint_data,
    PlayerBallPossession^ dst, 
    PlayerBallPossession^ src)
{

    dst->player_id = src->player_id;
    return true;
}

Boolean 
PlayerBallPossessionPlugin::key_to_instance(
    TypePluginDefaultEndpointData^ endpoint_data,
    PlayerBallPossession^ dst,
    PlayerBallPossession^ src)
{

    dst->player_id = src->player_id;
    return true;
}


Boolean 
PlayerBallPossessionPlugin::serialized_sample_to_key_hash(
    TypePluginDefaultEndpointData^ endpoint_data,
    CdrStream% stream, 
    KeyHash_t% key_hash,
    Boolean deserialize_encapsulation,
    Object^ endpoint_plugin_qos) 
{   
    CdrStreamPosition position;


    if(deserialize_encapsulation) {
        if (!stream.deserialize_and_set_cdr_encapsulation()) {
            return false;
        }

        position = stream.reset_alignment();
    }

    
    GCHandle sample_handle = GCHandle::FromIntPtr(IntPtr(const_cast<void*>(endpoint_data->get_temp_sample())));
    PlayerBallPossession^ sample = static_cast<PlayerBallPossession^>(sample_handle.Target);
    if (sample == nullptr) {
        return false;
    }


    if (!stream.skip_long_long()) {
        return false;
    }
            
    sample->player_id = stream.deserialize_string((255)); 
    if (sample->player_id == nullptr) {
        return false;
    }
            
    if(deserialize_encapsulation) {
        stream.restore_alignment(position);
    }


    if (!instance_to_key_hash(
            endpoint_data, key_hash, sample)) {
        return false;
    }

    return true;
}



/* ------------------------------------------------------------------------
 * Plug-in Lifecycle Methods
 * ------------------------------------------------------------------------ */

PlayerBallPossessionPlugin^
PlayerBallPossessionPlugin::get_instance() {
    if (_singleton == nullptr) {
        _singleton = gcnew PlayerBallPossessionPlugin();
    }
    return _singleton;
}


void
PlayerBallPossessionPlugin::dispose() {
    delete _singleton;
    _singleton = nullptr;
}

/* ------------------------------------------------------------------------
 *  Type PlayerData
 * ------------------------------------------------------------------------ */

/* ------------------------------------------------------------------------
    Support functions:
 * ------------------------------------------------------------------------ */

void 
PlayerDataPlugin::print_data(
        PlayerData^ sample,
        String^ desc,
        UInt32 indent_level) {

    for (UInt32 i = 0; i < indent_level; ++i) { Console::Write("   "); }

    if (desc != nullptr) {
        Console::WriteLine("{0}:", desc);
    } else {
        Console::WriteLine();
    }

    if (sample == nullptr) {
        Console::WriteLine("null");
        return;
    }


    DataPrintUtility::print_object(
        sample->player_name, "player_name", indent_level);
            
    DataPrintUtility::print_object(
        sample->ts, "ts", indent_level);
            
    DataPrintUtility::print_object(
        sample->pos_x, "pos_x", indent_level);
            
    DataPrintUtility::print_object(
        sample->pos_y, "pos_y", indent_level);
            
    DataPrintUtility::print_object(
        sample->pos_z, "pos_z", indent_level);
            
    DataPrintUtility::print_object(
        sample->vel, "vel", indent_level);
            
    DataPrintUtility::print_object(
        sample->accel, "accel", indent_level);
            
    DataPrintUtility::print_object(
        sample->vel_x, "vel_x", indent_level);
            
    DataPrintUtility::print_object(
        sample->vel_y, "vel_y", indent_level);
            
    DataPrintUtility::print_object(
        sample->vel_z, "vel_z", indent_level);
            
    DataPrintUtility::print_object(
        sample->accel_x, "accel_x", indent_level);
            
    DataPrintUtility::print_object(
        sample->accel_y, "accel_y", indent_level);
            
    DataPrintUtility::print_object(
        sample->accel_z, "accel_z", indent_level);
            
}


/* ------------------------------------------------------------------------
    (De)Serialize functions:
 * ------------------------------------------------------------------------ */

Boolean 
PlayerDataPlugin::serialize(
    TypePluginDefaultEndpointData^ endpoint_data,
    PlayerData^ sample,
    CdrStream% stream,    
    Boolean serialize_encapsulation,
    UInt16 encapsulation_id,
    Boolean serialize_sample, 
    Object^ endpoint_plugin_qos)
{
    CdrStreamPosition position;

    

    if (serialize_encapsulation) {
        /* Encapsulate sample */
        
        if (!stream.serialize_and_set_cdr_encapsulation(encapsulation_id)) {
            return false;
        }


        position = stream.reset_alignment();

    }

    if (serialize_sample) {

    if (!stream.serialize_string(sample->player_name, (255))) {
        return false;
    }
            
    if (!stream.serialize_long_long(sample->ts)) {
        return false;
    }
            
    if (!stream.serialize_double(sample->pos_x)) {
        return false;
    }
            
    if (!stream.serialize_double(sample->pos_y)) {
        return false;
    }
            
    if (!stream.serialize_double(sample->pos_z)) {
        return false;
    }
            
    if (!stream.serialize_double(sample->vel)) {
        return false;
    }
            
    if (!stream.serialize_double(sample->accel)) {
        return false;
    }
            
    if (!stream.serialize_double(sample->vel_x)) {
        return false;
    }
            
    if (!stream.serialize_double(sample->vel_y)) {
        return false;
    }
            
    if (!stream.serialize_double(sample->vel_z)) {
        return false;
    }
            
    if (!stream.serialize_double(sample->accel_x)) {
        return false;
    }
            
    if (!stream.serialize_double(sample->accel_y)) {
        return false;
    }
            
    if (!stream.serialize_double(sample->accel_z)) {
        return false;
    }
            
    }


    if(serialize_encapsulation) {
        stream.restore_alignment(position);
    }


    return true;
}


Boolean 
PlayerDataPlugin::deserialize_sample(
    TypePluginDefaultEndpointData^ endpoint_data,
    PlayerData^ sample,
    CdrStream% stream,   
    Boolean deserialize_encapsulation,
    Boolean deserialize_data, 
    Object^ endpoint_plugin_qos)
{
    CdrStreamPosition position;

    if(deserialize_encapsulation) {
        /* Deserialize encapsulation */
        if (!stream.deserialize_and_set_cdr_encapsulation()) {
            return false;
        }


        position = stream.reset_alignment();

    }

    if (deserialize_data) {
        sample->clear();

    try {
  
    sample->player_name = stream.deserialize_string((255)); 
    if (sample->player_name == nullptr) {
        return false;
    }
            
    sample->ts = stream.deserialize_long_long();
            
    sample->pos_x = stream.deserialize_double();
            
    sample->pos_y = stream.deserialize_double();
            
    sample->pos_z = stream.deserialize_double();
            
    sample->vel = stream.deserialize_double();
            
    sample->accel = stream.deserialize_double();
            
    sample->vel_x = stream.deserialize_double();
            
    sample->vel_y = stream.deserialize_double();
            
    sample->vel_z = stream.deserialize_double();
            
    sample->accel_x = stream.deserialize_double();
            
    sample->accel_y = stream.deserialize_double();
            
    sample->accel_z = stream.deserialize_double();
            
    } catch (System::ApplicationException^  e) {
        if (stream.get_remainder() >= RTI_CDR_PARAMETER_HEADER_ALIGNMENT) {
            throw gcnew System::ApplicationException("Error deserializing sample! Remainder: " + stream.get_remainder() + "\n" +
                                                              "Exception caused by: " + e->Message);
        }
    }

    }


    if(deserialize_encapsulation) {
        stream.restore_alignment(position);
    }


    return true;
}


Boolean
PlayerDataPlugin::skip(
    TypePluginDefaultEndpointData^ endpoint_data,
    CdrStream% stream,   
    Boolean skip_encapsulation,
    Boolean skip_sample, 
    Object^ endpoint_plugin_qos)
{
    CdrStreamPosition position;


    if (skip_encapsulation) {
        if (!stream.skip_encapsulation()) {
            return false;
        }

        position = stream.reset_alignment();

    }

    if (skip_sample) {

    if (!stream.skip_string((255) + 1)) {
        return false;
    }
            
    if (!stream.skip_long_long()) {
        return false;
    }
            
    if (!stream.skip_double()) {
        return false;
    }
            
    if (!stream.skip_double()) {
        return false;
    }
            
    if (!stream.skip_double()) {
        return false;
    }
            
    if (!stream.skip_double()) {
        return false;
    }
            
    if (!stream.skip_double()) {
        return false;
    }
            
    if (!stream.skip_double()) {
        return false;
    }
            
    if (!stream.skip_double()) {
        return false;
    }
            
    if (!stream.skip_double()) {
        return false;
    }
            
    if (!stream.skip_double()) {
        return false;
    }
            
    if (!stream.skip_double()) {
        return false;
    }
            
    if (!stream.skip_double()) {
        return false;
    }
            
    }


    if(skip_encapsulation) {
        stream.restore_alignment(position);
    }


    return true;
}

/*
  size is the offset from the point where we have do a logical reset
  Return difference in size, not the final offset.
*/
UInt32 
PlayerDataPlugin::get_serialized_sample_max_size(
    TypePluginDefaultEndpointData^ endpoint_data,
    Boolean include_encapsulation,
    UInt16 encapsulation_id,
    UInt32 current_alignment)
{

    UInt32 initial_alignment = current_alignment;

    UInt32 encapsulation_size = current_alignment;


    if (include_encapsulation) {
        if (!CdrStream::valid_encapsulation_id(encapsulation_id)) {
            return 1;
        }


        encapsulation_size = CdrSizes::ENCAPSULATION->serialized_size(
            current_alignment);
        encapsulation_size -= current_alignment;
        current_alignment = 0;
        initial_alignment = 0;

    }


    current_alignment +=  CdrSizes::STRING->serialized_size(
        current_alignment, (255) + 1);
            
    current_alignment +=  CdrSizes::LONG_LONG->serialized_size(
        current_alignment);
            
    current_alignment +=  CdrSizes::DOUBLE->serialized_size(
        current_alignment);
            
    current_alignment +=  CdrSizes::DOUBLE->serialized_size(
        current_alignment);
            
    current_alignment +=  CdrSizes::DOUBLE->serialized_size(
        current_alignment);
            
    current_alignment +=  CdrSizes::DOUBLE->serialized_size(
        current_alignment);
            
    current_alignment +=  CdrSizes::DOUBLE->serialized_size(
        current_alignment);
            
    current_alignment +=  CdrSizes::DOUBLE->serialized_size(
        current_alignment);
            
    current_alignment +=  CdrSizes::DOUBLE->serialized_size(
        current_alignment);
            
    current_alignment +=  CdrSizes::DOUBLE->serialized_size(
        current_alignment);
            
    current_alignment +=  CdrSizes::DOUBLE->serialized_size(
        current_alignment);
            
    current_alignment +=  CdrSizes::DOUBLE->serialized_size(
        current_alignment);
            
    current_alignment +=  CdrSizes::DOUBLE->serialized_size(
        current_alignment);
            
    if (include_encapsulation) {
        current_alignment += encapsulation_size;
    }

    return current_alignment - initial_alignment;
}


UInt32
PlayerDataPlugin::get_serialized_sample_min_size(
    TypePluginDefaultEndpointData^ endpoint_data,
    Boolean include_encapsulation,
    UInt16 encapsulation_id,
    UInt32 current_alignment)
{

    UInt32 initial_alignment = current_alignment;

    UInt32 encapsulation_size = current_alignment;


    if (include_encapsulation) {
        if (!CdrStream::valid_encapsulation_id(encapsulation_id)) {
            return 1;
        }


        encapsulation_size = CdrSizes::ENCAPSULATION->serialized_size(
            encapsulation_size);
        current_alignment = 0;
        initial_alignment = 0;

    }


    current_alignment +=  CdrSizes::STRING->serialized_size(
        current_alignment, 1);
            
    current_alignment +=  CdrSizes::LONG_LONG->serialized_size(
        current_alignment);
            
    current_alignment +=  CdrSizes::DOUBLE->serialized_size(
        current_alignment);
            
    current_alignment +=  CdrSizes::DOUBLE->serialized_size(
        current_alignment);
            
    current_alignment +=  CdrSizes::DOUBLE->serialized_size(
        current_alignment);
            
    current_alignment +=  CdrSizes::DOUBLE->serialized_size(
        current_alignment);
            
    current_alignment +=  CdrSizes::DOUBLE->serialized_size(
        current_alignment);
            
    current_alignment +=  CdrSizes::DOUBLE->serialized_size(
        current_alignment);
            
    current_alignment +=  CdrSizes::DOUBLE->serialized_size(
        current_alignment);
            
    current_alignment +=  CdrSizes::DOUBLE->serialized_size(
        current_alignment);
            
    current_alignment +=  CdrSizes::DOUBLE->serialized_size(
        current_alignment);
            
    current_alignment +=  CdrSizes::DOUBLE->serialized_size(
        current_alignment);
            
    current_alignment +=  CdrSizes::DOUBLE->serialized_size(
        current_alignment);
            
    if (include_encapsulation) {
        current_alignment += encapsulation_size;
    }

    return current_alignment - initial_alignment;
}


UInt32 
PlayerDataPlugin::get_serialized_sample_size(
    TypePluginDefaultEndpointData^ endpoint_data,
    Boolean include_encapsulation,
    UInt16 encapsulation_id,
    UInt32 current_alignment,
    PlayerData^ sample)
{

    UInt32 initial_alignment = current_alignment;

    UInt32 encapsulation_size = current_alignment;


    if (include_encapsulation) {
        if (!CdrStream::valid_encapsulation_id(encapsulation_id)) {
            return 1;
        }


        encapsulation_size = CdrSizes::ENCAPSULATION->serialized_size(
            current_alignment);
        encapsulation_size -= current_alignment;
        current_alignment = 0;
        initial_alignment = 0;

    }


    current_alignment += CdrSizes::STRING->serialized_size(current_alignment, sample->player_name);
            
    current_alignment += CdrSizes::LONG_LONG->serialized_size(
        current_alignment);
            
    current_alignment += CdrSizes::DOUBLE->serialized_size(
        current_alignment);
            
    current_alignment += CdrSizes::DOUBLE->serialized_size(
        current_alignment);
            
    current_alignment += CdrSizes::DOUBLE->serialized_size(
        current_alignment);
            
    current_alignment += CdrSizes::DOUBLE->serialized_size(
        current_alignment);
            
    current_alignment += CdrSizes::DOUBLE->serialized_size(
        current_alignment);
            
    current_alignment += CdrSizes::DOUBLE->serialized_size(
        current_alignment);
            
    current_alignment += CdrSizes::DOUBLE->serialized_size(
        current_alignment);
            
    current_alignment += CdrSizes::DOUBLE->serialized_size(
        current_alignment);
            
    current_alignment += CdrSizes::DOUBLE->serialized_size(
        current_alignment);
            
    current_alignment += CdrSizes::DOUBLE->serialized_size(
        current_alignment);
            
    current_alignment += CdrSizes::DOUBLE->serialized_size(
        current_alignment);
            
    if (include_encapsulation) {
        current_alignment += encapsulation_size;
    }

    return current_alignment - initial_alignment;
}


UInt32
PlayerDataPlugin::get_serialized_key_max_size(
    TypePluginDefaultEndpointData^ endpoint_data,
    Boolean include_encapsulation,
    UInt16 encapsulation_id,
    UInt32 current_alignment)
{

    UInt32 encapsulation_size = current_alignment;


    UInt32 initial_alignment = current_alignment;

    if (include_encapsulation) {
        if (!CdrStream::valid_encapsulation_id(encapsulation_id)) {
            return 1;
        }


        encapsulation_size = CdrSizes::ENCAPSULATION->serialized_size(
            current_alignment);
        current_alignment = 0;
        initial_alignment = 0;

    }
        

    current_alignment +=  CdrSizes::STRING->serialized_size(
        current_alignment, (255) + 1);
            
    if (include_encapsulation) {
        current_alignment += encapsulation_size;
    }

    return current_alignment - initial_alignment;
}

/* ------------------------------------------------------------------------
    Key Management functions:
 * ------------------------------------------------------------------------ */

Boolean 
PlayerDataPlugin::serialize_key(
    TypePluginDefaultEndpointData^ endpoint_data,
    PlayerData^ sample,
    CdrStream% stream,    
    Boolean serialize_encapsulation,
    UInt16 encapsulation_id,
    Boolean serialize_key,
    Object^ endpoint_plugin_qos)
{
    CdrStreamPosition position;

    if (serialize_encapsulation) {
        /* Encapsulate sample */

        if (!stream.serialize_and_set_cdr_encapsulation(encapsulation_id)) {
            return false;
        }


        position = stream.reset_alignment();

    }

    if (serialize_key) {

    if (!stream.serialize_string(sample->player_name, (255))) {
        return false;
    }
            
    }


    if(serialize_encapsulation) {
        stream.restore_alignment(position);
    }


    return true;
}


Boolean PlayerDataPlugin::deserialize_key_sample(
    TypePluginDefaultEndpointData^ endpoint_data,
    PlayerData^ sample,
    CdrStream% stream, 
    Boolean deserialize_encapsulation,
    Boolean deserialize_key,
    Object^ endpoint_plugin_qos)
{
    CdrStreamPosition position;

    if (deserialize_encapsulation) {
        /* Deserialize encapsulation */
        if (!stream.deserialize_and_set_cdr_encapsulation()) {
            return false;  
        }


        position = stream.reset_alignment();

    }

    if (deserialize_key) {

    sample->player_name = stream.deserialize_string((255)); 
    if (sample->player_name == nullptr) {
        return false;
    }
            
    }


    if(deserialize_encapsulation) {
        stream.restore_alignment(position);
    }


    return true;
}


Boolean
PlayerDataPlugin::serialized_sample_to_key(
    TypePluginDefaultEndpointData^ endpoint_data,
    PlayerData^ sample,
    CdrStream% stream, 
    Boolean deserialize_encapsulation,  
    Boolean deserialize_key, 
    Object^ endpoint_plugin_qos)
{
    CdrStreamPosition position;

    if(deserialize_encapsulation) {
        if (!stream.deserialize_and_set_cdr_encapsulation()) {
            return false;
        }

        position = stream.reset_alignment();

    }

    if (deserialize_key) {

    sample->player_name = stream.deserialize_string((255)); 
    if (sample->player_name == nullptr) {
        return false;
    }
            
    if (!stream.skip_long_long()) {
        return false;
    }
            
    if (!stream.skip_double()) {
        return false;
    }
            
    if (!stream.skip_double()) {
        return false;
    }
            
    if (!stream.skip_double()) {
        return false;
    }
            
    if (!stream.skip_double()) {
        return false;
    }
            
    if (!stream.skip_double()) {
        return false;
    }
            
    if (!stream.skip_double()) {
        return false;
    }
            
    if (!stream.skip_double()) {
        return false;
    }
            
    if (!stream.skip_double()) {
        return false;
    }
            
    if (!stream.skip_double()) {
        return false;
    }
            
    if (!stream.skip_double()) {
        return false;
    }
            
    if (!stream.skip_double()) {
        return false;
    }
            
    }


    if(deserialize_encapsulation) {
        stream.restore_alignment(position);
    }


    return true;
}



Boolean 
PlayerDataPlugin::instance_to_key(
    TypePluginDefaultEndpointData^ endpoint_data,
    PlayerData^ dst, 
    PlayerData^ src)
{

    dst->player_name = src->player_name;
    return true;
}

Boolean 
PlayerDataPlugin::key_to_instance(
    TypePluginDefaultEndpointData^ endpoint_data,
    PlayerData^ dst,
    PlayerData^ src)
{

    dst->player_name = src->player_name;
    return true;
}


Boolean 
PlayerDataPlugin::serialized_sample_to_key_hash(
    TypePluginDefaultEndpointData^ endpoint_data,
    CdrStream% stream, 
    KeyHash_t% key_hash,
    Boolean deserialize_encapsulation,
    Object^ endpoint_plugin_qos) 
{   
    CdrStreamPosition position;


    if(deserialize_encapsulation) {
        if (!stream.deserialize_and_set_cdr_encapsulation()) {
            return false;
        }

        position = stream.reset_alignment();
    }

    
    GCHandle sample_handle = GCHandle::FromIntPtr(IntPtr(const_cast<void*>(endpoint_data->get_temp_sample())));
    PlayerData^ sample = static_cast<PlayerData^>(sample_handle.Target);
    if (sample == nullptr) {
        return false;
    }


    sample->player_name = stream.deserialize_string((255)); 
    if (sample->player_name == nullptr) {
        return false;
    }
            
    if(deserialize_encapsulation) {
        stream.restore_alignment(position);
    }


    if (!instance_to_key_hash(
            endpoint_data, key_hash, sample)) {
        return false;
    }

    return true;
}



/* ------------------------------------------------------------------------
 * Plug-in Lifecycle Methods
 * ------------------------------------------------------------------------ */

PlayerDataPlugin^
PlayerDataPlugin::get_instance() {
    if (_singleton == nullptr) {
        _singleton = gcnew PlayerDataPlugin();
    }
    return _singleton;
}


void
PlayerDataPlugin::dispose() {
    delete _singleton;
    _singleton = nullptr;
}

/* ------------------------------------------------------------------------
 *  Type SensorData
 * ------------------------------------------------------------------------ */

/* ------------------------------------------------------------------------
    Support functions:
 * ------------------------------------------------------------------------ */

void 
SensorDataPlugin::print_data(
        SensorData^ sample,
        String^ desc,
        UInt32 indent_level) {

    for (UInt32 i = 0; i < indent_level; ++i) { Console::Write("   "); }

    if (desc != nullptr) {
        Console::WriteLine("{0}:", desc);
    } else {
        Console::WriteLine();
    }

    if (sample == nullptr) {
        Console::WriteLine("null");
        return;
    }


    DataPrintUtility::print_object(
        sample->sensor_id, "sensor_id", indent_level);
            
    DataPrintUtility::print_object(
        sample->ts, "ts", indent_level);
            
    DataPrintUtility::print_object(
        sample->pos_x, "pos_x", indent_level);
            
    DataPrintUtility::print_object(
        sample->pos_y, "pos_y", indent_level);
            
    DataPrintUtility::print_object(
        sample->pos_z, "pos_z", indent_level);
            
    DataPrintUtility::print_object(
        sample->vel, "vel", indent_level);
            
    DataPrintUtility::print_object(
        sample->accel, "accel", indent_level);
            
    DataPrintUtility::print_object(
        sample->vel_x, "vel_x", indent_level);
            
    DataPrintUtility::print_object(
        sample->vel_y, "vel_y", indent_level);
            
    DataPrintUtility::print_object(
        sample->vel_z, "vel_z", indent_level);
            
    DataPrintUtility::print_object(
        sample->accel_x, "accel_x", indent_level);
            
    DataPrintUtility::print_object(
        sample->accel_y, "accel_y", indent_level);
            
    DataPrintUtility::print_object(
        sample->accel_z, "accel_z", indent_level);
            
}


/* ------------------------------------------------------------------------
    (De)Serialize functions:
 * ------------------------------------------------------------------------ */

Boolean 
SensorDataPlugin::serialize(
    TypePluginDefaultEndpointData^ endpoint_data,
    SensorData^ sample,
    CdrStream% stream,    
    Boolean serialize_encapsulation,
    UInt16 encapsulation_id,
    Boolean serialize_sample, 
    Object^ endpoint_plugin_qos)
{
    CdrStreamPosition position;

    

    if (serialize_encapsulation) {
        /* Encapsulate sample */
        
        if (!stream.serialize_and_set_cdr_encapsulation(encapsulation_id)) {
            return false;
        }


        position = stream.reset_alignment();

    }

    if (serialize_sample) {

    if (!stream.serialize_long(sample->sensor_id)) {
        return false;
    }
            
    if (!stream.serialize_long_long(sample->ts)) {
        return false;
    }
            
    if (!stream.serialize_long(sample->pos_x)) {
        return false;
    }
            
    if (!stream.serialize_long(sample->pos_y)) {
        return false;
    }
            
    if (!stream.serialize_long(sample->pos_z)) {
        return false;
    }
            
    if (!stream.serialize_long(sample->vel)) {
        return false;
    }
            
    if (!stream.serialize_long(sample->accel)) {
        return false;
    }
            
    if (!stream.serialize_long(sample->vel_x)) {
        return false;
    }
            
    if (!stream.serialize_long(sample->vel_y)) {
        return false;
    }
            
    if (!stream.serialize_long(sample->vel_z)) {
        return false;
    }
            
    if (!stream.serialize_long(sample->accel_x)) {
        return false;
    }
            
    if (!stream.serialize_long(sample->accel_y)) {
        return false;
    }
            
    if (!stream.serialize_long(sample->accel_z)) {
        return false;
    }
            
    }


    if(serialize_encapsulation) {
        stream.restore_alignment(position);
    }


    return true;
}


Boolean 
SensorDataPlugin::deserialize_sample(
    TypePluginDefaultEndpointData^ endpoint_data,
    SensorData^ sample,
    CdrStream% stream,   
    Boolean deserialize_encapsulation,
    Boolean deserialize_data, 
    Object^ endpoint_plugin_qos)
{
    CdrStreamPosition position;

    if(deserialize_encapsulation) {
        /* Deserialize encapsulation */
        if (!stream.deserialize_and_set_cdr_encapsulation()) {
            return false;
        }


        position = stream.reset_alignment();

    }

    if (deserialize_data) {
        sample->clear();

    try {
  
    sample->sensor_id = stream.deserialize_long();
            
    sample->ts = stream.deserialize_long_long();
            
    sample->pos_x = stream.deserialize_long();
            
    sample->pos_y = stream.deserialize_long();
            
    sample->pos_z = stream.deserialize_long();
            
    sample->vel = stream.deserialize_long();
            
    sample->accel = stream.deserialize_long();
            
    sample->vel_x = stream.deserialize_long();
            
    sample->vel_y = stream.deserialize_long();
            
    sample->vel_z = stream.deserialize_long();
            
    sample->accel_x = stream.deserialize_long();
            
    sample->accel_y = stream.deserialize_long();
            
    sample->accel_z = stream.deserialize_long();
            
    } catch (System::ApplicationException^  e) {
        if (stream.get_remainder() >= RTI_CDR_PARAMETER_HEADER_ALIGNMENT) {
            throw gcnew System::ApplicationException("Error deserializing sample! Remainder: " + stream.get_remainder() + "\n" +
                                                              "Exception caused by: " + e->Message);
        }
    }

    }


    if(deserialize_encapsulation) {
        stream.restore_alignment(position);
    }


    return true;
}


Boolean
SensorDataPlugin::skip(
    TypePluginDefaultEndpointData^ endpoint_data,
    CdrStream% stream,   
    Boolean skip_encapsulation,
    Boolean skip_sample, 
    Object^ endpoint_plugin_qos)
{
    CdrStreamPosition position;


    if (skip_encapsulation) {
        if (!stream.skip_encapsulation()) {
            return false;
        }

        position = stream.reset_alignment();

    }

    if (skip_sample) {

    if (!stream.skip_long()) {
        return false;
    }
            
    if (!stream.skip_long_long()) {
        return false;
    }
            
    if (!stream.skip_long()) {
        return false;
    }
            
    if (!stream.skip_long()) {
        return false;
    }
            
    if (!stream.skip_long()) {
        return false;
    }
            
    if (!stream.skip_long()) {
        return false;
    }
            
    if (!stream.skip_long()) {
        return false;
    }
            
    if (!stream.skip_long()) {
        return false;
    }
            
    if (!stream.skip_long()) {
        return false;
    }
            
    if (!stream.skip_long()) {
        return false;
    }
            
    if (!stream.skip_long()) {
        return false;
    }
            
    if (!stream.skip_long()) {
        return false;
    }
            
    if (!stream.skip_long()) {
        return false;
    }
            
    }


    if(skip_encapsulation) {
        stream.restore_alignment(position);
    }


    return true;
}

/*
  size is the offset from the point where we have do a logical reset
  Return difference in size, not the final offset.
*/
UInt32 
SensorDataPlugin::get_serialized_sample_max_size(
    TypePluginDefaultEndpointData^ endpoint_data,
    Boolean include_encapsulation,
    UInt16 encapsulation_id,
    UInt32 current_alignment)
{

    UInt32 initial_alignment = current_alignment;

    UInt32 encapsulation_size = current_alignment;


    if (include_encapsulation) {
        if (!CdrStream::valid_encapsulation_id(encapsulation_id)) {
            return 1;
        }


        encapsulation_size = CdrSizes::ENCAPSULATION->serialized_size(
            current_alignment);
        encapsulation_size -= current_alignment;
        current_alignment = 0;
        initial_alignment = 0;

    }


    current_alignment +=  CdrSizes::LONG->serialized_size(
        current_alignment);
            
    current_alignment +=  CdrSizes::LONG_LONG->serialized_size(
        current_alignment);
            
    current_alignment +=  CdrSizes::LONG->serialized_size(
        current_alignment);
            
    current_alignment +=  CdrSizes::LONG->serialized_size(
        current_alignment);
            
    current_alignment +=  CdrSizes::LONG->serialized_size(
        current_alignment);
            
    current_alignment +=  CdrSizes::LONG->serialized_size(
        current_alignment);
            
    current_alignment +=  CdrSizes::LONG->serialized_size(
        current_alignment);
            
    current_alignment +=  CdrSizes::LONG->serialized_size(
        current_alignment);
            
    current_alignment +=  CdrSizes::LONG->serialized_size(
        current_alignment);
            
    current_alignment +=  CdrSizes::LONG->serialized_size(
        current_alignment);
            
    current_alignment +=  CdrSizes::LONG->serialized_size(
        current_alignment);
            
    current_alignment +=  CdrSizes::LONG->serialized_size(
        current_alignment);
            
    current_alignment +=  CdrSizes::LONG->serialized_size(
        current_alignment);
            
    if (include_encapsulation) {
        current_alignment += encapsulation_size;
    }

    return current_alignment - initial_alignment;
}


UInt32
SensorDataPlugin::get_serialized_sample_min_size(
    TypePluginDefaultEndpointData^ endpoint_data,
    Boolean include_encapsulation,
    UInt16 encapsulation_id,
    UInt32 current_alignment)
{

    UInt32 initial_alignment = current_alignment;

    UInt32 encapsulation_size = current_alignment;


    if (include_encapsulation) {
        if (!CdrStream::valid_encapsulation_id(encapsulation_id)) {
            return 1;
        }


        encapsulation_size = CdrSizes::ENCAPSULATION->serialized_size(
            encapsulation_size);
        current_alignment = 0;
        initial_alignment = 0;

    }


    current_alignment +=  CdrSizes::LONG->serialized_size(
        current_alignment);
            
    current_alignment +=  CdrSizes::LONG_LONG->serialized_size(
        current_alignment);
            
    current_alignment +=  CdrSizes::LONG->serialized_size(
        current_alignment);
            
    current_alignment +=  CdrSizes::LONG->serialized_size(
        current_alignment);
            
    current_alignment +=  CdrSizes::LONG->serialized_size(
        current_alignment);
            
    current_alignment +=  CdrSizes::LONG->serialized_size(
        current_alignment);
            
    current_alignment +=  CdrSizes::LONG->serialized_size(
        current_alignment);
            
    current_alignment +=  CdrSizes::LONG->serialized_size(
        current_alignment);
            
    current_alignment +=  CdrSizes::LONG->serialized_size(
        current_alignment);
            
    current_alignment +=  CdrSizes::LONG->serialized_size(
        current_alignment);
            
    current_alignment +=  CdrSizes::LONG->serialized_size(
        current_alignment);
            
    current_alignment +=  CdrSizes::LONG->serialized_size(
        current_alignment);
            
    current_alignment +=  CdrSizes::LONG->serialized_size(
        current_alignment);
            
    if (include_encapsulation) {
        current_alignment += encapsulation_size;
    }

    return current_alignment - initial_alignment;
}


UInt32 
SensorDataPlugin::get_serialized_sample_size(
    TypePluginDefaultEndpointData^ endpoint_data,
    Boolean include_encapsulation,
    UInt16 encapsulation_id,
    UInt32 current_alignment,
    SensorData^ sample)
{

    UInt32 initial_alignment = current_alignment;

    UInt32 encapsulation_size = current_alignment;


    if (include_encapsulation) {
        if (!CdrStream::valid_encapsulation_id(encapsulation_id)) {
            return 1;
        }


        encapsulation_size = CdrSizes::ENCAPSULATION->serialized_size(
            current_alignment);
        encapsulation_size -= current_alignment;
        current_alignment = 0;
        initial_alignment = 0;

    }


    current_alignment += CdrSizes::LONG->serialized_size(
        current_alignment);
            
    current_alignment += CdrSizes::LONG_LONG->serialized_size(
        current_alignment);
            
    current_alignment += CdrSizes::LONG->serialized_size(
        current_alignment);
            
    current_alignment += CdrSizes::LONG->serialized_size(
        current_alignment);
            
    current_alignment += CdrSizes::LONG->serialized_size(
        current_alignment);
            
    current_alignment += CdrSizes::LONG->serialized_size(
        current_alignment);
            
    current_alignment += CdrSizes::LONG->serialized_size(
        current_alignment);
            
    current_alignment += CdrSizes::LONG->serialized_size(
        current_alignment);
            
    current_alignment += CdrSizes::LONG->serialized_size(
        current_alignment);
            
    current_alignment += CdrSizes::LONG->serialized_size(
        current_alignment);
            
    current_alignment += CdrSizes::LONG->serialized_size(
        current_alignment);
            
    current_alignment += CdrSizes::LONG->serialized_size(
        current_alignment);
            
    current_alignment += CdrSizes::LONG->serialized_size(
        current_alignment);
            
    if (include_encapsulation) {
        current_alignment += encapsulation_size;
    }

    return current_alignment - initial_alignment;
}


UInt32
SensorDataPlugin::get_serialized_key_max_size(
    TypePluginDefaultEndpointData^ endpoint_data,
    Boolean include_encapsulation,
    UInt16 encapsulation_id,
    UInt32 current_alignment)
{

    UInt32 encapsulation_size = current_alignment;


    UInt32 initial_alignment = current_alignment;

    if (include_encapsulation) {
        if (!CdrStream::valid_encapsulation_id(encapsulation_id)) {
            return 1;
        }


        encapsulation_size = CdrSizes::ENCAPSULATION->serialized_size(
            current_alignment);
        current_alignment = 0;
        initial_alignment = 0;

    }
        

    current_alignment +=  CdrSizes::LONG->serialized_size(
        current_alignment);
            
    if (include_encapsulation) {
        current_alignment += encapsulation_size;
    }

    return current_alignment - initial_alignment;
}

/* ------------------------------------------------------------------------
    Key Management functions:
 * ------------------------------------------------------------------------ */

Boolean 
SensorDataPlugin::serialize_key(
    TypePluginDefaultEndpointData^ endpoint_data,
    SensorData^ sample,
    CdrStream% stream,    
    Boolean serialize_encapsulation,
    UInt16 encapsulation_id,
    Boolean serialize_key,
    Object^ endpoint_plugin_qos)
{
    CdrStreamPosition position;

    if (serialize_encapsulation) {
        /* Encapsulate sample */

        if (!stream.serialize_and_set_cdr_encapsulation(encapsulation_id)) {
            return false;
        }


        position = stream.reset_alignment();

    }

    if (serialize_key) {

    if (!stream.serialize_long(sample->sensor_id)) {
        return false;
    }
            
    }


    if(serialize_encapsulation) {
        stream.restore_alignment(position);
    }


    return true;
}


Boolean SensorDataPlugin::deserialize_key_sample(
    TypePluginDefaultEndpointData^ endpoint_data,
    SensorData^ sample,
    CdrStream% stream, 
    Boolean deserialize_encapsulation,
    Boolean deserialize_key,
    Object^ endpoint_plugin_qos)
{
    CdrStreamPosition position;

    if (deserialize_encapsulation) {
        /* Deserialize encapsulation */
        if (!stream.deserialize_and_set_cdr_encapsulation()) {
            return false;  
        }


        position = stream.reset_alignment();

    }

    if (deserialize_key) {

    sample->sensor_id = stream.deserialize_long();
            
    }


    if(deserialize_encapsulation) {
        stream.restore_alignment(position);
    }


    return true;
}


Boolean
SensorDataPlugin::serialized_sample_to_key(
    TypePluginDefaultEndpointData^ endpoint_data,
    SensorData^ sample,
    CdrStream% stream, 
    Boolean deserialize_encapsulation,  
    Boolean deserialize_key, 
    Object^ endpoint_plugin_qos)
{
    CdrStreamPosition position;

    if(deserialize_encapsulation) {
        if (!stream.deserialize_and_set_cdr_encapsulation()) {
            return false;
        }

        position = stream.reset_alignment();

    }

    if (deserialize_key) {

    sample->sensor_id = stream.deserialize_long();
            
    if (!stream.skip_long_long()) {
        return false;
    }
            
    if (!stream.skip_long()) {
        return false;
    }
            
    if (!stream.skip_long()) {
        return false;
    }
            
    if (!stream.skip_long()) {
        return false;
    }
            
    if (!stream.skip_long()) {
        return false;
    }
            
    if (!stream.skip_long()) {
        return false;
    }
            
    if (!stream.skip_long()) {
        return false;
    }
            
    if (!stream.skip_long()) {
        return false;
    }
            
    if (!stream.skip_long()) {
        return false;
    }
            
    if (!stream.skip_long()) {
        return false;
    }
            
    if (!stream.skip_long()) {
        return false;
    }
            
    if (!stream.skip_long()) {
        return false;
    }
            
    }


    if(deserialize_encapsulation) {
        stream.restore_alignment(position);
    }


    return true;
}



Boolean 
SensorDataPlugin::instance_to_key(
    TypePluginDefaultEndpointData^ endpoint_data,
    SensorData^ dst, 
    SensorData^ src)
{

    dst->sensor_id = src->sensor_id;
    return true;
}

Boolean 
SensorDataPlugin::key_to_instance(
    TypePluginDefaultEndpointData^ endpoint_data,
    SensorData^ dst,
    SensorData^ src)
{

    dst->sensor_id = src->sensor_id;
    return true;
}


Boolean 
SensorDataPlugin::serialized_sample_to_key_hash(
    TypePluginDefaultEndpointData^ endpoint_data,
    CdrStream% stream, 
    KeyHash_t% key_hash,
    Boolean deserialize_encapsulation,
    Object^ endpoint_plugin_qos) 
{   
    CdrStreamPosition position;


    if(deserialize_encapsulation) {
        if (!stream.deserialize_and_set_cdr_encapsulation()) {
            return false;
        }

        position = stream.reset_alignment();
    }

    
    GCHandle sample_handle = GCHandle::FromIntPtr(IntPtr(const_cast<void*>(endpoint_data->get_temp_sample())));
    SensorData^ sample = static_cast<SensorData^>(sample_handle.Target);
    if (sample == nullptr) {
        return false;
    }


    sample->sensor_id = stream.deserialize_long();
            
    if(deserialize_encapsulation) {
        stream.restore_alignment(position);
    }


    if (!instance_to_key_hash(
            endpoint_data, key_hash, sample)) {
        return false;
    }

    return true;
}



/* ------------------------------------------------------------------------
 * Plug-in Lifecycle Methods
 * ------------------------------------------------------------------------ */

SensorDataPlugin^
SensorDataPlugin::get_instance() {
    if (_singleton == nullptr) {
        _singleton = gcnew SensorDataPlugin();
    }
    return _singleton;
}


void
SensorDataPlugin::dispose() {
    delete _singleton;
    _singleton = nullptr;
}

/* ------------------------------------------------------------------------
 *  Type ShotOnGoalData
 * ------------------------------------------------------------------------ */

/* ------------------------------------------------------------------------
    Support functions:
 * ------------------------------------------------------------------------ */

void 
ShotOnGoalDataPlugin::print_data(
        ShotOnGoalData^ sample,
        String^ desc,
        UInt32 indent_level) {

    for (UInt32 i = 0; i < indent_level; ++i) { Console::Write("   "); }

    if (desc != nullptr) {
        Console::WriteLine("{0}:", desc);
    } else {
        Console::WriteLine();
    }

    if (sample == nullptr) {
        Console::WriteLine("null");
        return;
    }


    DataPrintUtility::print_object(
        sample->ts, "ts", indent_level);
            
    DataPrintUtility::print_object(
        sample->player_id, "player_id", indent_level);
            
    DataPrintUtility::print_object(
        sample->pos_x, "pos_x", indent_level);
            
    DataPrintUtility::print_object(
        sample->pos_y, "pos_y", indent_level);
            
    DataPrintUtility::print_object(
        sample->pos_z, "pos_z", indent_level);
            
    DataPrintUtility::print_object(
        sample->vel, "vel", indent_level);
            
    DataPrintUtility::print_object(
        sample->vel_x, "vel_x", indent_level);
            
    DataPrintUtility::print_object(
        sample->vel_y, "vel_y", indent_level);
            
    DataPrintUtility::print_object(
        sample->vel_z, "vel_z", indent_level);
            
    DataPrintUtility::print_object(
        sample->accel, "accel", indent_level);
            
    DataPrintUtility::print_object(
        sample->accel_x, "accel_x", indent_level);
            
    DataPrintUtility::print_object(
        sample->accel_y, "accel_y", indent_level);
            
    DataPrintUtility::print_object(
        sample->accel_z, "accel_z", indent_level);
            
}


/* ------------------------------------------------------------------------
    (De)Serialize functions:
 * ------------------------------------------------------------------------ */

Boolean 
ShotOnGoalDataPlugin::serialize(
    TypePluginDefaultEndpointData^ endpoint_data,
    ShotOnGoalData^ sample,
    CdrStream% stream,    
    Boolean serialize_encapsulation,
    UInt16 encapsulation_id,
    Boolean serialize_sample, 
    Object^ endpoint_plugin_qos)
{
    CdrStreamPosition position;

    

    if (serialize_encapsulation) {
        /* Encapsulate sample */
        
        if (!stream.serialize_and_set_cdr_encapsulation(encapsulation_id)) {
            return false;
        }


        position = stream.reset_alignment();

    }

    if (serialize_sample) {

    if (!stream.serialize_long_long(sample->ts)) {
        return false;
    }
            
    if (!stream.serialize_string(sample->player_id, (255))) {
        return false;
    }
            
    if (!stream.serialize_long(sample->pos_x)) {
        return false;
    }
            
    if (!stream.serialize_long(sample->pos_y)) {
        return false;
    }
            
    if (!stream.serialize_long(sample->pos_z)) {
        return false;
    }
            
    if (!stream.serialize_long(sample->vel)) {
        return false;
    }
            
    if (!stream.serialize_long(sample->vel_x)) {
        return false;
    }
            
    if (!stream.serialize_long(sample->vel_y)) {
        return false;
    }
            
    if (!stream.serialize_long(sample->vel_z)) {
        return false;
    }
            
    if (!stream.serialize_long(sample->accel)) {
        return false;
    }
            
    if (!stream.serialize_long(sample->accel_x)) {
        return false;
    }
            
    if (!stream.serialize_long(sample->accel_y)) {
        return false;
    }
            
    if (!stream.serialize_long(sample->accel_z)) {
        return false;
    }
            
    }


    if(serialize_encapsulation) {
        stream.restore_alignment(position);
    }


    return true;
}


Boolean 
ShotOnGoalDataPlugin::deserialize_sample(
    TypePluginDefaultEndpointData^ endpoint_data,
    ShotOnGoalData^ sample,
    CdrStream% stream,   
    Boolean deserialize_encapsulation,
    Boolean deserialize_data, 
    Object^ endpoint_plugin_qos)
{
    CdrStreamPosition position;

    if(deserialize_encapsulation) {
        /* Deserialize encapsulation */
        if (!stream.deserialize_and_set_cdr_encapsulation()) {
            return false;
        }


        position = stream.reset_alignment();

    }

    if (deserialize_data) {
        sample->clear();

    try {
  
    sample->ts = stream.deserialize_long_long();
            
    sample->player_id = stream.deserialize_string((255)); 
    if (sample->player_id == nullptr) {
        return false;
    }
            
    sample->pos_x = stream.deserialize_long();
            
    sample->pos_y = stream.deserialize_long();
            
    sample->pos_z = stream.deserialize_long();
            
    sample->vel = stream.deserialize_long();
            
    sample->vel_x = stream.deserialize_long();
            
    sample->vel_y = stream.deserialize_long();
            
    sample->vel_z = stream.deserialize_long();
            
    sample->accel = stream.deserialize_long();
            
    sample->accel_x = stream.deserialize_long();
            
    sample->accel_y = stream.deserialize_long();
            
    sample->accel_z = stream.deserialize_long();
            
    } catch (System::ApplicationException^  e) {
        if (stream.get_remainder() >= RTI_CDR_PARAMETER_HEADER_ALIGNMENT) {
            throw gcnew System::ApplicationException("Error deserializing sample! Remainder: " + stream.get_remainder() + "\n" +
                                                              "Exception caused by: " + e->Message);
        }
    }

    }


    if(deserialize_encapsulation) {
        stream.restore_alignment(position);
    }


    return true;
}


Boolean
ShotOnGoalDataPlugin::skip(
    TypePluginDefaultEndpointData^ endpoint_data,
    CdrStream% stream,   
    Boolean skip_encapsulation,
    Boolean skip_sample, 
    Object^ endpoint_plugin_qos)
{
    CdrStreamPosition position;


    if (skip_encapsulation) {
        if (!stream.skip_encapsulation()) {
            return false;
        }

        position = stream.reset_alignment();

    }

    if (skip_sample) {

    if (!stream.skip_long_long()) {
        return false;
    }
            
    if (!stream.skip_string((255) + 1)) {
        return false;
    }
            
    if (!stream.skip_long()) {
        return false;
    }
            
    if (!stream.skip_long()) {
        return false;
    }
            
    if (!stream.skip_long()) {
        return false;
    }
            
    if (!stream.skip_long()) {
        return false;
    }
            
    if (!stream.skip_long()) {
        return false;
    }
            
    if (!stream.skip_long()) {
        return false;
    }
            
    if (!stream.skip_long()) {
        return false;
    }
            
    if (!stream.skip_long()) {
        return false;
    }
            
    if (!stream.skip_long()) {
        return false;
    }
            
    if (!stream.skip_long()) {
        return false;
    }
            
    if (!stream.skip_long()) {
        return false;
    }
            
    }


    if(skip_encapsulation) {
        stream.restore_alignment(position);
    }


    return true;
}

/*
  size is the offset from the point where we have do a logical reset
  Return difference in size, not the final offset.
*/
UInt32 
ShotOnGoalDataPlugin::get_serialized_sample_max_size(
    TypePluginDefaultEndpointData^ endpoint_data,
    Boolean include_encapsulation,
    UInt16 encapsulation_id,
    UInt32 current_alignment)
{

    UInt32 initial_alignment = current_alignment;

    UInt32 encapsulation_size = current_alignment;


    if (include_encapsulation) {
        if (!CdrStream::valid_encapsulation_id(encapsulation_id)) {
            return 1;
        }


        encapsulation_size = CdrSizes::ENCAPSULATION->serialized_size(
            current_alignment);
        encapsulation_size -= current_alignment;
        current_alignment = 0;
        initial_alignment = 0;

    }


    current_alignment +=  CdrSizes::LONG_LONG->serialized_size(
        current_alignment);
            
    current_alignment +=  CdrSizes::STRING->serialized_size(
        current_alignment, (255) + 1);
            
    current_alignment +=  CdrSizes::LONG->serialized_size(
        current_alignment);
            
    current_alignment +=  CdrSizes::LONG->serialized_size(
        current_alignment);
            
    current_alignment +=  CdrSizes::LONG->serialized_size(
        current_alignment);
            
    current_alignment +=  CdrSizes::LONG->serialized_size(
        current_alignment);
            
    current_alignment +=  CdrSizes::LONG->serialized_size(
        current_alignment);
            
    current_alignment +=  CdrSizes::LONG->serialized_size(
        current_alignment);
            
    current_alignment +=  CdrSizes::LONG->serialized_size(
        current_alignment);
            
    current_alignment +=  CdrSizes::LONG->serialized_size(
        current_alignment);
            
    current_alignment +=  CdrSizes::LONG->serialized_size(
        current_alignment);
            
    current_alignment +=  CdrSizes::LONG->serialized_size(
        current_alignment);
            
    current_alignment +=  CdrSizes::LONG->serialized_size(
        current_alignment);
            
    if (include_encapsulation) {
        current_alignment += encapsulation_size;
    }

    return current_alignment - initial_alignment;
}


UInt32
ShotOnGoalDataPlugin::get_serialized_sample_min_size(
    TypePluginDefaultEndpointData^ endpoint_data,
    Boolean include_encapsulation,
    UInt16 encapsulation_id,
    UInt32 current_alignment)
{

    UInt32 initial_alignment = current_alignment;

    UInt32 encapsulation_size = current_alignment;


    if (include_encapsulation) {
        if (!CdrStream::valid_encapsulation_id(encapsulation_id)) {
            return 1;
        }


        encapsulation_size = CdrSizes::ENCAPSULATION->serialized_size(
            encapsulation_size);
        current_alignment = 0;
        initial_alignment = 0;

    }


    current_alignment +=  CdrSizes::LONG_LONG->serialized_size(
        current_alignment);
            
    current_alignment +=  CdrSizes::STRING->serialized_size(
        current_alignment, 1);
            
    current_alignment +=  CdrSizes::LONG->serialized_size(
        current_alignment);
            
    current_alignment +=  CdrSizes::LONG->serialized_size(
        current_alignment);
            
    current_alignment +=  CdrSizes::LONG->serialized_size(
        current_alignment);
            
    current_alignment +=  CdrSizes::LONG->serialized_size(
        current_alignment);
            
    current_alignment +=  CdrSizes::LONG->serialized_size(
        current_alignment);
            
    current_alignment +=  CdrSizes::LONG->serialized_size(
        current_alignment);
            
    current_alignment +=  CdrSizes::LONG->serialized_size(
        current_alignment);
            
    current_alignment +=  CdrSizes::LONG->serialized_size(
        current_alignment);
            
    current_alignment +=  CdrSizes::LONG->serialized_size(
        current_alignment);
            
    current_alignment +=  CdrSizes::LONG->serialized_size(
        current_alignment);
            
    current_alignment +=  CdrSizes::LONG->serialized_size(
        current_alignment);
            
    if (include_encapsulation) {
        current_alignment += encapsulation_size;
    }

    return current_alignment - initial_alignment;
}


UInt32 
ShotOnGoalDataPlugin::get_serialized_sample_size(
    TypePluginDefaultEndpointData^ endpoint_data,
    Boolean include_encapsulation,
    UInt16 encapsulation_id,
    UInt32 current_alignment,
    ShotOnGoalData^ sample)
{

    UInt32 initial_alignment = current_alignment;

    UInt32 encapsulation_size = current_alignment;


    if (include_encapsulation) {
        if (!CdrStream::valid_encapsulation_id(encapsulation_id)) {
            return 1;
        }


        encapsulation_size = CdrSizes::ENCAPSULATION->serialized_size(
            current_alignment);
        encapsulation_size -= current_alignment;
        current_alignment = 0;
        initial_alignment = 0;

    }


    current_alignment += CdrSizes::LONG_LONG->serialized_size(
        current_alignment);
            
    current_alignment += CdrSizes::STRING->serialized_size(current_alignment, sample->player_id);
            
    current_alignment += CdrSizes::LONG->serialized_size(
        current_alignment);
            
    current_alignment += CdrSizes::LONG->serialized_size(
        current_alignment);
            
    current_alignment += CdrSizes::LONG->serialized_size(
        current_alignment);
            
    current_alignment += CdrSizes::LONG->serialized_size(
        current_alignment);
            
    current_alignment += CdrSizes::LONG->serialized_size(
        current_alignment);
            
    current_alignment += CdrSizes::LONG->serialized_size(
        current_alignment);
            
    current_alignment += CdrSizes::LONG->serialized_size(
        current_alignment);
            
    current_alignment += CdrSizes::LONG->serialized_size(
        current_alignment);
            
    current_alignment += CdrSizes::LONG->serialized_size(
        current_alignment);
            
    current_alignment += CdrSizes::LONG->serialized_size(
        current_alignment);
            
    current_alignment += CdrSizes::LONG->serialized_size(
        current_alignment);
            
    if (include_encapsulation) {
        current_alignment += encapsulation_size;
    }

    return current_alignment - initial_alignment;
}


UInt32
ShotOnGoalDataPlugin::get_serialized_key_max_size(
    TypePluginDefaultEndpointData^ endpoint_data,
    Boolean include_encapsulation,
    UInt16 encapsulation_id,
    UInt32 current_alignment)
{

    UInt32 encapsulation_size = current_alignment;


    UInt32 initial_alignment = current_alignment;

    if (include_encapsulation) {
        if (!CdrStream::valid_encapsulation_id(encapsulation_id)) {
            return 1;
        }


        encapsulation_size = CdrSizes::ENCAPSULATION->serialized_size(
            current_alignment);
        current_alignment = 0;
        initial_alignment = 0;

    }
        

    current_alignment += get_serialized_sample_max_size(
        endpoint_data,false,encapsulation_id,current_alignment);
    
    if (include_encapsulation) {
        current_alignment += encapsulation_size;
    }

    return current_alignment - initial_alignment;
}

/* ------------------------------------------------------------------------
    Key Management functions:
 * ------------------------------------------------------------------------ */

Boolean 
ShotOnGoalDataPlugin::serialize_key(
    TypePluginDefaultEndpointData^ endpoint_data,
    ShotOnGoalData^ sample,
    CdrStream% stream,    
    Boolean serialize_encapsulation,
    UInt16 encapsulation_id,
    Boolean serialize_key,
    Object^ endpoint_plugin_qos)
{
    CdrStreamPosition position;

    if (serialize_encapsulation) {
        /* Encapsulate sample */

        if (!stream.serialize_and_set_cdr_encapsulation(encapsulation_id)) {
            return false;
        }


        position = stream.reset_alignment();

    }

    if (serialize_key) {

        if (!serialize(
                endpoint_data,
                sample,
                stream,
                serialize_encapsulation,
                encapsulation_id, 
                serialize_key,
                endpoint_plugin_qos)) {
            return false;
        }
    
    }


    if(serialize_encapsulation) {
        stream.restore_alignment(position);
    }


    return true;
}


Boolean ShotOnGoalDataPlugin::deserialize_key_sample(
    TypePluginDefaultEndpointData^ endpoint_data,
    ShotOnGoalData^ sample,
    CdrStream% stream, 
    Boolean deserialize_encapsulation,
    Boolean deserialize_key,
    Object^ endpoint_plugin_qos)
{
    CdrStreamPosition position;

    if (deserialize_encapsulation) {
        /* Deserialize encapsulation */
        if (!stream.deserialize_and_set_cdr_encapsulation()) {
            return false;  
        }


        position = stream.reset_alignment();

    }

    if (deserialize_key) {

        if (!deserialize_sample(
                endpoint_data, sample, stream,
                deserialize_encapsulation,
                deserialize_key,
                endpoint_plugin_qos)) {
            return false;
        }
    
    }


    if(deserialize_encapsulation) {
        stream.restore_alignment(position);
    }


    return true;
}


Boolean
ShotOnGoalDataPlugin::serialized_sample_to_key(
    TypePluginDefaultEndpointData^ endpoint_data,
    ShotOnGoalData^ sample,
    CdrStream% stream, 
    Boolean deserialize_encapsulation,  
    Boolean deserialize_key, 
    Object^ endpoint_plugin_qos)
{
    CdrStreamPosition position;

    if(deserialize_encapsulation) {
        if (!stream.deserialize_and_set_cdr_encapsulation()) {
            return false;
        }

        position = stream.reset_alignment();

    }

    if (deserialize_key) {

        if (!deserialize_sample(
                endpoint_data,
                sample,
                stream,
                deserialize_encapsulation,
                deserialize_key,
                endpoint_plugin_qos)) {
            return false;
        }

    }


    if(deserialize_encapsulation) {
        stream.restore_alignment(position);
    }


    return true;
}




/* ------------------------------------------------------------------------
 * Plug-in Lifecycle Methods
 * ------------------------------------------------------------------------ */

ShotOnGoalDataPlugin^
ShotOnGoalDataPlugin::get_instance() {
    if (_singleton == nullptr) {
        _singleton = gcnew ShotOnGoalDataPlugin();
    }
    return _singleton;
}


void
ShotOnGoalDataPlugin::dispose() {
    delete _singleton;
    _singleton = nullptr;
}

/* ------------------------------------------------------------------------
 *  Type TeamBallPossession
 * ------------------------------------------------------------------------ */

/* ------------------------------------------------------------------------
    Support functions:
 * ------------------------------------------------------------------------ */

void 
TeamBallPossessionPlugin::print_data(
        TeamBallPossession^ sample,
        String^ desc,
        UInt32 indent_level) {

    for (UInt32 i = 0; i < indent_level; ++i) { Console::Write("   "); }

    if (desc != nullptr) {
        Console::WriteLine("{0}:", desc);
    } else {
        Console::WriteLine();
    }

    if (sample == nullptr) {
        Console::WriteLine("null");
        return;
    }


    DataPrintUtility::print_object(
        sample->ts, "ts", indent_level);
            
    DataPrintUtility::print_object(
        sample->team_id, "team_id", indent_level);
            
    DataPrintUtility::print_object(
        sample->time, "time", indent_level);
            
    DataPrintUtility::print_object(
        sample->time_percent, "time_percent", indent_level);
            
}


/* ------------------------------------------------------------------------
    (De)Serialize functions:
 * ------------------------------------------------------------------------ */

Boolean 
TeamBallPossessionPlugin::serialize(
    TypePluginDefaultEndpointData^ endpoint_data,
    TeamBallPossession^ sample,
    CdrStream% stream,    
    Boolean serialize_encapsulation,
    UInt16 encapsulation_id,
    Boolean serialize_sample, 
    Object^ endpoint_plugin_qos)
{
    CdrStreamPosition position;

    

    if (serialize_encapsulation) {
        /* Encapsulate sample */
        
        if (!stream.serialize_and_set_cdr_encapsulation(encapsulation_id)) {
            return false;
        }


        position = stream.reset_alignment();

    }

    if (serialize_sample) {

    if (!stream.serialize_long_long(sample->ts)) {
        return false;
    }
            
    if (!stream.serialize_string(sample->team_id, (255))) {
        return false;
    }
            
    if (!stream.serialize_double(sample->time)) {
        return false;
    }
            
    if (!stream.serialize_double(sample->time_percent)) {
        return false;
    }
            
    }


    if(serialize_encapsulation) {
        stream.restore_alignment(position);
    }


    return true;
}


Boolean 
TeamBallPossessionPlugin::deserialize_sample(
    TypePluginDefaultEndpointData^ endpoint_data,
    TeamBallPossession^ sample,
    CdrStream% stream,   
    Boolean deserialize_encapsulation,
    Boolean deserialize_data, 
    Object^ endpoint_plugin_qos)
{
    CdrStreamPosition position;

    if(deserialize_encapsulation) {
        /* Deserialize encapsulation */
        if (!stream.deserialize_and_set_cdr_encapsulation()) {
            return false;
        }


        position = stream.reset_alignment();

    }

    if (deserialize_data) {
        sample->clear();

    try {
  
    sample->ts = stream.deserialize_long_long();
            
    sample->team_id = stream.deserialize_string((255)); 
    if (sample->team_id == nullptr) {
        return false;
    }
            
    sample->time = stream.deserialize_double();
            
    sample->time_percent = stream.deserialize_double();
            
    } catch (System::ApplicationException^  e) {
        if (stream.get_remainder() >= RTI_CDR_PARAMETER_HEADER_ALIGNMENT) {
            throw gcnew System::ApplicationException("Error deserializing sample! Remainder: " + stream.get_remainder() + "\n" +
                                                              "Exception caused by: " + e->Message);
        }
    }

    }


    if(deserialize_encapsulation) {
        stream.restore_alignment(position);
    }


    return true;
}


Boolean
TeamBallPossessionPlugin::skip(
    TypePluginDefaultEndpointData^ endpoint_data,
    CdrStream% stream,   
    Boolean skip_encapsulation,
    Boolean skip_sample, 
    Object^ endpoint_plugin_qos)
{
    CdrStreamPosition position;


    if (skip_encapsulation) {
        if (!stream.skip_encapsulation()) {
            return false;
        }

        position = stream.reset_alignment();

    }

    if (skip_sample) {

    if (!stream.skip_long_long()) {
        return false;
    }
            
    if (!stream.skip_string((255) + 1)) {
        return false;
    }
            
    if (!stream.skip_double()) {
        return false;
    }
            
    if (!stream.skip_double()) {
        return false;
    }
            
    }


    if(skip_encapsulation) {
        stream.restore_alignment(position);
    }


    return true;
}

/*
  size is the offset from the point where we have do a logical reset
  Return difference in size, not the final offset.
*/
UInt32 
TeamBallPossessionPlugin::get_serialized_sample_max_size(
    TypePluginDefaultEndpointData^ endpoint_data,
    Boolean include_encapsulation,
    UInt16 encapsulation_id,
    UInt32 current_alignment)
{

    UInt32 initial_alignment = current_alignment;

    UInt32 encapsulation_size = current_alignment;


    if (include_encapsulation) {
        if (!CdrStream::valid_encapsulation_id(encapsulation_id)) {
            return 1;
        }


        encapsulation_size = CdrSizes::ENCAPSULATION->serialized_size(
            current_alignment);
        encapsulation_size -= current_alignment;
        current_alignment = 0;
        initial_alignment = 0;

    }


    current_alignment +=  CdrSizes::LONG_LONG->serialized_size(
        current_alignment);
            
    current_alignment +=  CdrSizes::STRING->serialized_size(
        current_alignment, (255) + 1);
            
    current_alignment +=  CdrSizes::DOUBLE->serialized_size(
        current_alignment);
            
    current_alignment +=  CdrSizes::DOUBLE->serialized_size(
        current_alignment);
            
    if (include_encapsulation) {
        current_alignment += encapsulation_size;
    }

    return current_alignment - initial_alignment;
}


UInt32
TeamBallPossessionPlugin::get_serialized_sample_min_size(
    TypePluginDefaultEndpointData^ endpoint_data,
    Boolean include_encapsulation,
    UInt16 encapsulation_id,
    UInt32 current_alignment)
{

    UInt32 initial_alignment = current_alignment;

    UInt32 encapsulation_size = current_alignment;


    if (include_encapsulation) {
        if (!CdrStream::valid_encapsulation_id(encapsulation_id)) {
            return 1;
        }


        encapsulation_size = CdrSizes::ENCAPSULATION->serialized_size(
            encapsulation_size);
        current_alignment = 0;
        initial_alignment = 0;

    }


    current_alignment +=  CdrSizes::LONG_LONG->serialized_size(
        current_alignment);
            
    current_alignment +=  CdrSizes::STRING->serialized_size(
        current_alignment, 1);
            
    current_alignment +=  CdrSizes::DOUBLE->serialized_size(
        current_alignment);
            
    current_alignment +=  CdrSizes::DOUBLE->serialized_size(
        current_alignment);
            
    if (include_encapsulation) {
        current_alignment += encapsulation_size;
    }

    return current_alignment - initial_alignment;
}


UInt32 
TeamBallPossessionPlugin::get_serialized_sample_size(
    TypePluginDefaultEndpointData^ endpoint_data,
    Boolean include_encapsulation,
    UInt16 encapsulation_id,
    UInt32 current_alignment,
    TeamBallPossession^ sample)
{

    UInt32 initial_alignment = current_alignment;

    UInt32 encapsulation_size = current_alignment;


    if (include_encapsulation) {
        if (!CdrStream::valid_encapsulation_id(encapsulation_id)) {
            return 1;
        }


        encapsulation_size = CdrSizes::ENCAPSULATION->serialized_size(
            current_alignment);
        encapsulation_size -= current_alignment;
        current_alignment = 0;
        initial_alignment = 0;

    }


    current_alignment += CdrSizes::LONG_LONG->serialized_size(
        current_alignment);
            
    current_alignment += CdrSizes::STRING->serialized_size(current_alignment, sample->team_id);
            
    current_alignment += CdrSizes::DOUBLE->serialized_size(
        current_alignment);
            
    current_alignment += CdrSizes::DOUBLE->serialized_size(
        current_alignment);
            
    if (include_encapsulation) {
        current_alignment += encapsulation_size;
    }

    return current_alignment - initial_alignment;
}


UInt32
TeamBallPossessionPlugin::get_serialized_key_max_size(
    TypePluginDefaultEndpointData^ endpoint_data,
    Boolean include_encapsulation,
    UInt16 encapsulation_id,
    UInt32 current_alignment)
{

    UInt32 encapsulation_size = current_alignment;


    UInt32 initial_alignment = current_alignment;

    if (include_encapsulation) {
        if (!CdrStream::valid_encapsulation_id(encapsulation_id)) {
            return 1;
        }


        encapsulation_size = CdrSizes::ENCAPSULATION->serialized_size(
            current_alignment);
        current_alignment = 0;
        initial_alignment = 0;

    }
        

    current_alignment += get_serialized_sample_max_size(
        endpoint_data,false,encapsulation_id,current_alignment);
    
    if (include_encapsulation) {
        current_alignment += encapsulation_size;
    }

    return current_alignment - initial_alignment;
}

/* ------------------------------------------------------------------------
    Key Management functions:
 * ------------------------------------------------------------------------ */

Boolean 
TeamBallPossessionPlugin::serialize_key(
    TypePluginDefaultEndpointData^ endpoint_data,
    TeamBallPossession^ sample,
    CdrStream% stream,    
    Boolean serialize_encapsulation,
    UInt16 encapsulation_id,
    Boolean serialize_key,
    Object^ endpoint_plugin_qos)
{
    CdrStreamPosition position;

    if (serialize_encapsulation) {
        /* Encapsulate sample */

        if (!stream.serialize_and_set_cdr_encapsulation(encapsulation_id)) {
            return false;
        }


        position = stream.reset_alignment();

    }

    if (serialize_key) {

        if (!serialize(
                endpoint_data,
                sample,
                stream,
                serialize_encapsulation,
                encapsulation_id, 
                serialize_key,
                endpoint_plugin_qos)) {
            return false;
        }
    
    }


    if(serialize_encapsulation) {
        stream.restore_alignment(position);
    }


    return true;
}


Boolean TeamBallPossessionPlugin::deserialize_key_sample(
    TypePluginDefaultEndpointData^ endpoint_data,
    TeamBallPossession^ sample,
    CdrStream% stream, 
    Boolean deserialize_encapsulation,
    Boolean deserialize_key,
    Object^ endpoint_plugin_qos)
{
    CdrStreamPosition position;

    if (deserialize_encapsulation) {
        /* Deserialize encapsulation */
        if (!stream.deserialize_and_set_cdr_encapsulation()) {
            return false;  
        }


        position = stream.reset_alignment();

    }

    if (deserialize_key) {

        if (!deserialize_sample(
                endpoint_data, sample, stream,
                deserialize_encapsulation,
                deserialize_key,
                endpoint_plugin_qos)) {
            return false;
        }
    
    }


    if(deserialize_encapsulation) {
        stream.restore_alignment(position);
    }


    return true;
}


Boolean
TeamBallPossessionPlugin::serialized_sample_to_key(
    TypePluginDefaultEndpointData^ endpoint_data,
    TeamBallPossession^ sample,
    CdrStream% stream, 
    Boolean deserialize_encapsulation,  
    Boolean deserialize_key, 
    Object^ endpoint_plugin_qos)
{
    CdrStreamPosition position;

    if(deserialize_encapsulation) {
        if (!stream.deserialize_and_set_cdr_encapsulation()) {
            return false;
        }

        position = stream.reset_alignment();

    }

    if (deserialize_key) {

        if (!deserialize_sample(
                endpoint_data,
                sample,
                stream,
                deserialize_encapsulation,
                deserialize_key,
                endpoint_plugin_qos)) {
            return false;
        }

    }


    if(deserialize_encapsulation) {
        stream.restore_alignment(position);
    }


    return true;
}




/* ------------------------------------------------------------------------
 * Plug-in Lifecycle Methods
 * ------------------------------------------------------------------------ */

TeamBallPossessionPlugin^
TeamBallPossessionPlugin::get_instance() {
    if (_singleton == nullptr) {
        _singleton = gcnew TeamBallPossessionPlugin();
    }
    return _singleton;
}


void
TeamBallPossessionPlugin::dispose() {
    delete _singleton;
    _singleton = nullptr;
}
