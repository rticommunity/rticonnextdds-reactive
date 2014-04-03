/*
  WARNING: THIS FILE IS AUTO-GENERATED. DO NOT MODIFY.

  This file was generated from ShapeType.idl using "rtiddsgen".
  The rtiddsgen tool is part of the RTI Connext distribution.
  For more information, type 'rtiddsgen -help' at a command shell
  or consult the RTI Connext manual.
*/

#include "ShapeTypePlugin.h"


#pragma unmanaged
#include "ndds/ndds_cpp.h"
#include "osapi/osapi_utility.h"
#pragma managed

using namespace System::Runtime::InteropServices;
    

/* ------------------------------------------------------------------------
  Enum Type: ShapeFillKind
 * ------------------------------------------------------------------------ */

/* ------------------------------------------------------------------------
 * (De)Serialization Methods
 * ------------------------------------------------------------------------ */


Boolean
ShapeFillKindPlugin::serialize(
    TypePluginEndpointData^ endpoint_data,
    ShapeFillKind sample,
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
ShapeFillKindPlugin::deserialize_sample(
    TypePluginEndpointData^ endpoint_data,
    ShapeFillKind% sample,
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


        sample = stream.deserialize_enum<ShapeFillKind>();

        switch (sample) {

            case ShapeFillKind::SOLID_FILL:

            case ShapeFillKind::TRANSPARENT_FILL:

            case ShapeFillKind::HORIZONTAL_HATCH_FILL:

            case ShapeFillKind::VERTICAL_HATCH_FILL:

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
ShapeFillKindPlugin::skip(
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
ShapeFillKindPlugin::get_serialized_sample_max_size(
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
ShapeFillKindPlugin::get_serialized_sample_min_size(
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
ShapeFillKindPlugin::get_serialized_sample_size(
    TypePluginEndpointData^ endpoint_data,
    Boolean include_encapsulation,
    UInt16 encapsulation_id,
    UInt32 current_alignment,
    ShapeFillKind sample) 
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
ShapeFillKindPlugin::serialize_key(
    TypePluginEndpointData^ endpoint_data,
    ShapeFillKind sample,
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
ShapeFillKindPlugin::deserialize_key_sample(
    TypePluginEndpointData^ endpoint_data,
    ShapeFillKind% sample,
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
ShapeFillKindPlugin::get_serialized_key_max_size(
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
ShapeFillKindPlugin::serialized_sample_to_key(
    TypePluginEndpointData^ endpoint_data,
    ShapeFillKind% sample,
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
ShapeFillKindPlugin::print_data(
    ShapeFillKind sample,
    String^ description,
    UInt32 indent_level)
{
    if (description != nullptr) {
        for (UInt32 i = 0; i < indent_level; ++i) { Console::Write("   "); }
        Console::WriteLine("{0}:", description);
    }

    RTICdrType_printEnum((RTICdrEnum*) &sample,
                         "ShapeFillKind", indent_level + 1);
}


/* ------------------------------------------------------------------------
 * Plug-in Lifecycle Methods
 * ------------------------------------------------------------------------ */

ShapeFillKindPlugin^
ShapeFillKindPlugin::get_instance() {
    if (_singleton == nullptr) {
        _singleton = gcnew ShapeFillKindPlugin();
    }
    return _singleton;
}


void
ShapeFillKindPlugin::dispose() {
    delete _singleton;
    _singleton = nullptr;
}


/* ------------------------------------------------------------------------
 *  Type ShapeType
 * ------------------------------------------------------------------------ */

/* ------------------------------------------------------------------------
    Support functions:
 * ------------------------------------------------------------------------ */

void 
ShapeTypePlugin::print_data(
        ShapeType^ sample,
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
        sample->color, "color", indent_level);
            
    DataPrintUtility::print_object(
        sample->x, "x", indent_level);
            
    DataPrintUtility::print_object(
        sample->y, "y", indent_level);
            
    DataPrintUtility::print_object(
        sample->shapesize, "shapesize", indent_level);
            
}


/* ------------------------------------------------------------------------
    (De)Serialize functions:
 * ------------------------------------------------------------------------ */

Boolean 
ShapeTypePlugin::serialize(
    TypePluginDefaultEndpointData^ endpoint_data,
    ShapeType^ sample,
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

    if (!stream.serialize_string(sample->color, (128))) {
        return false;
    }
            
    if (!stream.serialize_long(sample->x)) {
        return false;
    }
            
    if (!stream.serialize_long(sample->y)) {
        return false;
    }
            
    if (!stream.serialize_long(sample->shapesize)) {
        return false;
    }
            
    }


    if(serialize_encapsulation) {
        stream.restore_alignment(position);
    }


    return true;
}


Boolean 
ShapeTypePlugin::deserialize_sample(
    TypePluginDefaultEndpointData^ endpoint_data,
    ShapeType^ sample,
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
  
    sample->color = stream.deserialize_string((128)); 
    if (sample->color == nullptr) {
        return false;
    }
            
    sample->x = stream.deserialize_long();
            
    sample->y = stream.deserialize_long();
            
    sample->shapesize = stream.deserialize_long();
            
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
ShapeTypePlugin::skip(
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

    if (!stream.skip_string((128) + 1)) {
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
ShapeTypePlugin::get_serialized_sample_max_size(
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
        current_alignment, (128) + 1);
            
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
ShapeTypePlugin::get_serialized_sample_min_size(
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
ShapeTypePlugin::get_serialized_sample_size(
    TypePluginDefaultEndpointData^ endpoint_data,
    Boolean include_encapsulation,
    UInt16 encapsulation_id,
    UInt32 current_alignment,
    ShapeType^ sample)
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


    current_alignment += CdrSizes::STRING->serialized_size(current_alignment, sample->color);
            
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
ShapeTypePlugin::get_serialized_key_max_size(
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
        current_alignment, (128) + 1);
            
    if (include_encapsulation) {
        current_alignment += encapsulation_size;
    }

    return current_alignment - initial_alignment;
}

/* ------------------------------------------------------------------------
    Key Management functions:
 * ------------------------------------------------------------------------ */

Boolean 
ShapeTypePlugin::serialize_key(
    TypePluginDefaultEndpointData^ endpoint_data,
    ShapeType^ sample,
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

    if (!stream.serialize_string(sample->color, (128))) {
        return false;
    }
            
    }


    if(serialize_encapsulation) {
        stream.restore_alignment(position);
    }


    return true;
}


Boolean ShapeTypePlugin::deserialize_key_sample(
    TypePluginDefaultEndpointData^ endpoint_data,
    ShapeType^ sample,
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

    sample->color = stream.deserialize_string((128)); 
    if (sample->color == nullptr) {
        return false;
    }
            
    }


    if(deserialize_encapsulation) {
        stream.restore_alignment(position);
    }


    return true;
}


Boolean
ShapeTypePlugin::serialized_sample_to_key(
    TypePluginDefaultEndpointData^ endpoint_data,
    ShapeType^ sample,
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

    sample->color = stream.deserialize_string((128)); 
    if (sample->color == nullptr) {
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
ShapeTypePlugin::instance_to_key(
    TypePluginDefaultEndpointData^ endpoint_data,
    ShapeType^ dst, 
    ShapeType^ src)
{

    dst->color = src->color;
    return true;
}

Boolean 
ShapeTypePlugin::key_to_instance(
    TypePluginDefaultEndpointData^ endpoint_data,
    ShapeType^ dst,
    ShapeType^ src)
{

    dst->color = src->color;
    return true;
}


Boolean 
ShapeTypePlugin::serialized_sample_to_key_hash(
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
    ShapeType^ sample = static_cast<ShapeType^>(sample_handle.Target);
    if (sample == nullptr) {
        return false;
    }


    sample->color = stream.deserialize_string((128)); 
    if (sample->color == nullptr) {
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

ShapeTypePlugin^
ShapeTypePlugin::get_instance() {
    if (_singleton == nullptr) {
        _singleton = gcnew ShapeTypePlugin();
    }
    return _singleton;
}


void
ShapeTypePlugin::dispose() {
    delete _singleton;
    _singleton = nullptr;
}

/* ------------------------------------------------------------------------
 *  Type ShapeTypeExtended
 * ------------------------------------------------------------------------ */

/* ------------------------------------------------------------------------
    Support functions:
 * ------------------------------------------------------------------------ */

void 
ShapeTypeExtendedPlugin::print_data(
        ShapeTypeExtended^ sample,
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

    ShapeTypePlugin::get_instance()->print_data(sample, "", indent_level);

    DataPrintUtility::print_object(
        sample->fillKind, "fillKind", indent_level);
            
    DataPrintUtility::print_object(
        sample->angle, "angle", indent_level);
            
}


/* ------------------------------------------------------------------------
    (De)Serialize functions:
 * ------------------------------------------------------------------------ */

Boolean 
ShapeTypeExtendedPlugin::serialize(
    TypePluginDefaultEndpointData^ endpoint_data,
    ShapeTypeExtended^ sample,
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
    if (!ShapeTypePlugin::get_instance()->serialize(endpoint_data,sample, stream, false, encapsulation_id, true, endpoint_plugin_qos)) {
        return false;
    }
    if (!ShapeFillKindPlugin::get_instance()->serialize(
            endpoint_data,
            sample->fillKind,
            stream,
            false, // serialize encapsulation
            encapsulation_id,
            true,  // serialize data 
            endpoint_plugin_qos)) {
        return false;
    }
            
    if (!stream.serialize_float(sample->angle)) {
        return false;
    }
            
    }


    if(serialize_encapsulation) {
        stream.restore_alignment(position);
    }


    return true;
}


Boolean 
ShapeTypeExtendedPlugin::deserialize_sample(
    TypePluginDefaultEndpointData^ endpoint_data,
    ShapeTypeExtended^ sample,
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
        if (!ShapeTypePlugin::get_instance()->deserialize_sample(endpoint_data,sample, stream, false, true, endpoint_plugin_qos)) {
            return false;
        }
    try {
  
    if (!ShapeFillKindPlugin::get_instance()->deserialize_sample(
            endpoint_data,
            sample->fillKind,
            stream,
            false, // deserialize encapsulation
            true,  // deserialize data
            endpoint_plugin_qos)) {
        return false;
    }
            
    sample->angle = stream.deserialize_float();
            
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
ShapeTypeExtendedPlugin::skip(
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
    if (!ShapeTypePlugin::get_instance()->skip(endpoint_data, stream,false, true, endpoint_plugin_qos)) {
        return false;
    }
    if (!ShapeFillKindPlugin::get_instance()->skip(
            endpoint_data,
            stream, 
            false, true, 
            endpoint_plugin_qos)) {
        return false;
    }
            
    if (!stream.skip_float()) {
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
ShapeTypeExtendedPlugin::get_serialized_sample_max_size(
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

    current_alignment += ShapeTypePlugin::get_instance()->get_serialized_sample_max_size(endpoint_data,false,encapsulation_id,current_alignment);

    current_alignment +=  ShapeFillKindPlugin::get_instance()->get_serialized_sample_max_size(
        endpoint_data, false, encapsulation_id, current_alignment);
            
    current_alignment +=  CdrSizes::FLOAT->serialized_size(
        current_alignment);
            
    if (include_encapsulation) {
        current_alignment += encapsulation_size;
    }

    return current_alignment - initial_alignment;
}


UInt32
ShapeTypeExtendedPlugin::get_serialized_sample_min_size(
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

    current_alignment += ShapeTypePlugin::get_instance()->get_serialized_sample_min_size(endpoint_data,false,encapsulation_id,current_alignment);

    current_alignment +=  ShapeFillKindPlugin::get_instance()->get_serialized_sample_min_size(
        endpoint_data, false, encapsulation_id, current_alignment);
            
    current_alignment +=  CdrSizes::FLOAT->serialized_size(
        current_alignment);
            
    if (include_encapsulation) {
        current_alignment += encapsulation_size;
    }

    return current_alignment - initial_alignment;
}


UInt32 
ShapeTypeExtendedPlugin::get_serialized_sample_size(
    TypePluginDefaultEndpointData^ endpoint_data,
    Boolean include_encapsulation,
    UInt16 encapsulation_id,
    UInt32 current_alignment,
    ShapeTypeExtended^ sample)
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

    current_alignment += ShapeTypePlugin::get_instance()->get_serialized_sample_size(endpoint_data,false,encapsulation_id,current_alignment,sample);

    current_alignment += ShapeFillKindPlugin::get_instance()->get_serialized_sample_size(
        endpoint_data, false, encapsulation_id, current_alignment, sample->fillKind);
            
    current_alignment += CdrSizes::FLOAT->serialized_size(
        current_alignment);
            
    if (include_encapsulation) {
        current_alignment += encapsulation_size;
    }

    return current_alignment - initial_alignment;
}


UInt32
ShapeTypeExtendedPlugin::get_serialized_key_max_size(
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
        
    current_alignment += ShapeTypePlugin::get_instance()->get_serialized_key_max_size(
        endpoint_data,
        false, encapsulation_id, 
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
ShapeTypeExtendedPlugin::serialize_key(
    TypePluginDefaultEndpointData^ endpoint_data,
    ShapeTypeExtended^ sample,
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
        if (!ShapeTypePlugin::get_instance()->serialize_key(
            endpoint_data,sample, stream, false, encapsulation_id, true, endpoint_plugin_qos)) {
            return false;
        }
    }


    if(serialize_encapsulation) {
        stream.restore_alignment(position);
    }


    return true;
}


Boolean ShapeTypeExtendedPlugin::deserialize_key_sample(
    TypePluginDefaultEndpointData^ endpoint_data,
    ShapeTypeExtended^ sample,
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

        if (!ShapeTypePlugin::get_instance()->deserialize_key_sample(
                endpoint_data, sample, stream, deserialize_encapsulation, deserialize_key, endpoint_plugin_qos)) {
            return false;
        }
       
    }


    if(deserialize_encapsulation) {
        stream.restore_alignment(position);
    }


    return true;
}


Boolean
ShapeTypeExtendedPlugin::serialized_sample_to_key(
    TypePluginDefaultEndpointData^ endpoint_data,
    ShapeTypeExtended^ sample,
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
    if (!ShapeTypePlugin::get_instance()->serialized_sample_to_key(
                        endpoint_data,
                        sample,
                        stream,
                        false, 
                        true,
                        endpoint_plugin_qos)) {
                    return false;

                }
                
    if (!ShapeFillKindPlugin::get_instance()->skip(
            endpoint_data,
            stream, 
            false, true, 
            endpoint_plugin_qos)) {
        return false;
    }
            
    if (!stream.skip_float()) {
        return false;
    }
            
    }


    if(deserialize_encapsulation) {
        stream.restore_alignment(position);
    }


    return true;
}



Boolean 
ShapeTypeExtendedPlugin::instance_to_key(
    TypePluginDefaultEndpointData^ endpoint_data,
    ShapeTypeExtended^ dst, 
    ShapeTypeExtended^ src)
{
    if (!ShapeTypePlugin::get_instance()->instance_to_key(endpoint_data,dst,src)) {
        return false;
    }
    return true;
}

Boolean 
ShapeTypeExtendedPlugin::key_to_instance(
    TypePluginDefaultEndpointData^ endpoint_data,
    ShapeTypeExtended^ dst,
    ShapeTypeExtended^ src)
{
    if (!ShapeTypePlugin::get_instance()->key_to_instance(endpoint_data,dst,src)) {
        return false;
    }
    return true;
}


Boolean 
ShapeTypeExtendedPlugin::serialized_sample_to_key_hash(
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
    ShapeTypeExtended^ sample = static_cast<ShapeTypeExtended^>(sample_handle.Target);
    if (sample == nullptr) {
        return false;
    }


    if (!ShapeTypePlugin::get_instance()->serialized_sample_to_key(
            endpoint_data, sample, stream, false, true, endpoint_plugin_qos)) {
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

ShapeTypeExtendedPlugin^
ShapeTypeExtendedPlugin::get_instance() {
    if (_singleton == nullptr) {
        _singleton = gcnew ShapeTypeExtendedPlugin();
    }
    return _singleton;
}


void
ShapeTypeExtendedPlugin::dispose() {
    delete _singleton;
    _singleton = nullptr;
}
