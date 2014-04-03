/*
  WARNING: THIS FILE IS AUTO-GENERATED. DO NOT MODIFY.

  This file was generated from ShapeType.idl using "rtiddsgen".
  The rtiddsgen tool is part of the RTI Connext distribution.
  For more information, type 'rtiddsgen -help' at a command shell
  or consult the RTI Connext manual.
*/

#pragma once

#include "ShapeType.h"


    
/* ------------------------------------------------------------------------
 * Enum Type: ShapeFillKind
 * ------------------------------------------------------------------------ */

public ref class ShapeFillKindPlugin {
// --- (De)Serialization Methods: --------------------------------------------
public:
    System::Boolean serialize(
        TypePluginEndpointData^ endpoint_data,
        ShapeFillKind sample,
        CdrStream% stream,
        System::Boolean serialize_encapsulation,
        System::UInt16  encapsulation_id,
        System::Boolean serialize_sample,
        System::Object^ endpoint_plugin_qos);

    System::Boolean deserialize_sample(
        TypePluginEndpointData^ endpoint_data,
        ShapeFillKind% sample,
        CdrStream% stream,
        System::Boolean deserialize_encapsulation,
        System::Boolean deserialize_sample, 
        System::Object^ endpoint_plugin_qos);

    System::Boolean skip(
        TypePluginEndpointData^ endpoint_data,
        CdrStream% stream,
        System::Boolean skip_encapsulation,
        System::Boolean skip_sample, 
        System::Object^ endpoint_plugin_qos);

    System::UInt32 get_serialized_sample_max_size(
        TypePluginEndpointData^ endpoint_data,
        System::Boolean include_encapsulation,
        System::UInt16  encapsulation_id,
        System::UInt32 size);

    System::UInt32 get_serialized_sample_min_size(
        TypePluginEndpointData^ endpoint_data,
        System::Boolean include_encapsulation,
        System::UInt16  encapsulation_id,
        System::UInt32 size);

    System::UInt32 get_serialized_sample_size(
        TypePluginEndpointData^ endpoint_data,
        Boolean include_encapsulation,
        UInt16 encapsulation_id,
        UInt32 current_alignment,
        ShapeFillKind sample);

// --- Key Management functions: ---------------------------------------------
public:
    System::Boolean serialize_key(
        TypePluginEndpointData^ endpoint_data,
        ShapeFillKind key,
        CdrStream% stream,
        System::Boolean serialize_encapsulation,
        System::UInt16  encapsulation_id,
        System::Boolean serialize_sample,
        System::Object^ endpoint_plugin_qos);

    System::Boolean deserialize_key_sample(
        TypePluginEndpointData^ endpoint_data,
        ShapeFillKind% key,
        CdrStream% stream,
        System::Boolean deserialize_encapsulation,
        System::Boolean deserialize_sample,
        System::Object^ endpoint_plugin_qos);

    System::UInt32 get_serialized_key_max_size(
        TypePluginEndpointData^ endpoint_data,
        System::Boolean include_encapsulation,
        System::UInt16  encapsulation_id,
        System::UInt32 current_alignment);

    System::Boolean serialized_sample_to_key(
        TypePluginEndpointData^ endpoint_data,
        ShapeFillKind% sample,
        CdrStream% stream, 
        Boolean deserialize_encapsulation,  
        Boolean deserialize_key, 
        Object^ endpoint_plugin_qos);


// --- Support functions: ----------------------------------------------------
public:
    void print_data(
        ShapeFillKind sample,
        System::String^ desc,
        System::UInt32 indent_level);

    



// ---  Plug-in lifecycle management methods: --------------------------------
public:
    static ShapeFillKindPlugin^ get_instance();

    static void dispose();

private:
    ShapeFillKindPlugin() { /*empty*/ }

    static ShapeFillKindPlugin^ _singleton;
};  

/* ------------------------------------------------------------------------
 * Type: ShapeType
 * ------------------------------------------------------------------------ */

public ref class ShapeTypePlugin :
    DefaultTypePlugin<ShapeType^> {
// --- Support methods: ------------------------------------------------------
public:
    void print_data(
        ShapeType^ sample,
        System::String^ desc,
        System::UInt32 indent);


// --- (De)Serialize methods: ------------------------------------------------
public:
    virtual System::Boolean serialize(
        TypePluginDefaultEndpointData^ endpoint_data,
        ShapeType^ sample,
        CdrStream% stream,
        System::Boolean serialize_encapsulation,
        System::UInt16  encapsulation_id,
        System::Boolean serialize_sample,
        System::Object^ endpoint_plugin_qos) override;

    virtual System::Boolean deserialize_sample(
        TypePluginDefaultEndpointData^ endpoint_data,
        ShapeType^ sample,
        CdrStream% stream,
        System::Boolean deserialize_encapsulation,
        System::Boolean deserialize_sample, 
        System::Object^ endpoint_plugin_qos) override;

    System::Boolean skip(
        TypePluginDefaultEndpointData^ endpoint_data,
        CdrStream% stream,
        System::Boolean skip_encapsulation,  
        System::Boolean skip_sample, 
        System::Object^ endpoint_plugin_qos);

    virtual System::UInt32 get_serialized_sample_max_size(
        TypePluginDefaultEndpointData^ endpoint_data,
        System::Boolean include_encapsulation,
        System::UInt16  encapsulation_id,
        System::UInt32 size) override;

    virtual System::UInt32 get_serialized_sample_min_size(
        TypePluginDefaultEndpointData^ endpoint_data,
        System::Boolean include_encapsulation,
        System::UInt16  encapsulation_id,
        System::UInt32 size) override;

    virtual System::UInt32 get_serialized_sample_size(
        TypePluginDefaultEndpointData^ endpoint_data,
        Boolean include_encapsulation,
        UInt16 encapsulation_id,
        UInt32 current_alignment,
        ShapeType^ sample) override;

// ---  Key Management functions: --------------------------------------------
public:
    virtual System::UInt32 get_serialized_key_max_size(
        TypePluginDefaultEndpointData^ endpoint_data,
        System::Boolean include_encapsulation,
        System::UInt16  encapsulation_id,
        System::UInt32 current_alignment) override;

    virtual System::Boolean serialize_key(
        TypePluginDefaultEndpointData^ endpoint_data,
        ShapeType^ key,
        CdrStream% stream,
        System::Boolean serialize_encapsulation,
        System::UInt16  encapsulation_id,
        System::Boolean serialize_sample,
        System::Object^ endpoint_plugin_qos) override;

    virtual System::Boolean deserialize_key_sample(
        TypePluginDefaultEndpointData^ endpoint_data,
        ShapeType^ key,
        CdrStream% stream,
        System::Boolean deserialize_encapsulation,
        System::Boolean deserialize_sample,
        System::Object^ endpoint_plugin_qos) override;

    System::Boolean serialized_sample_to_key(
        TypePluginDefaultEndpointData^ endpoint_data,
        ShapeType^ sample,
        CdrStream% stream,
        System::Boolean deserialize_encapsulation,
        System::Boolean deserialize_key,
        System::Object^ endpoint_plugin_qos);

 

    virtual System::Boolean instance_to_key(
        TypePluginDefaultEndpointData^ endpoint_data,
        ShapeType^ key,
        ShapeType^ instance) override;

    virtual System::Boolean key_to_instance(
        TypePluginDefaultEndpointData^ endpoint_data,
        ShapeType^ instance,
        ShapeType^ key) override;

    virtual System::Boolean serialized_sample_to_key_hash(
        TypePluginDefaultEndpointData^ endpoint_data,
        CdrStream% stream,
        KeyHash_t% key_hash,
        System::Boolean deserialize_encapsulation,
        System::Object^ endpoint_plugin_qos) override;

 


// ---  Plug-in lifecycle management methods: --------------------------------
public:
    static ShapeTypePlugin^ get_instance();

    static void dispose();

private:
    ShapeTypePlugin()
            : DefaultTypePlugin(
                "ShapeType",

                true, // keyed
    
                false, // use RTPS-compliant alignment
                   ShapeType::get_typecode()) {
        // empty
    }

    static ShapeTypePlugin^ _singleton;
};

/* ------------------------------------------------------------------------
 * Type: ShapeTypeExtended
 * ------------------------------------------------------------------------ */

public ref class ShapeTypeExtendedPlugin :
    DefaultTypePlugin<ShapeTypeExtended^> {
// --- Support methods: ------------------------------------------------------
public:
    void print_data(
        ShapeTypeExtended^ sample,
        System::String^ desc,
        System::UInt32 indent);


// --- (De)Serialize methods: ------------------------------------------------
public:
    virtual System::Boolean serialize(
        TypePluginDefaultEndpointData^ endpoint_data,
        ShapeTypeExtended^ sample,
        CdrStream% stream,
        System::Boolean serialize_encapsulation,
        System::UInt16  encapsulation_id,
        System::Boolean serialize_sample,
        System::Object^ endpoint_plugin_qos) override;

    virtual System::Boolean deserialize_sample(
        TypePluginDefaultEndpointData^ endpoint_data,
        ShapeTypeExtended^ sample,
        CdrStream% stream,
        System::Boolean deserialize_encapsulation,
        System::Boolean deserialize_sample, 
        System::Object^ endpoint_plugin_qos) override;

    System::Boolean skip(
        TypePluginDefaultEndpointData^ endpoint_data,
        CdrStream% stream,
        System::Boolean skip_encapsulation,  
        System::Boolean skip_sample, 
        System::Object^ endpoint_plugin_qos);

    virtual System::UInt32 get_serialized_sample_max_size(
        TypePluginDefaultEndpointData^ endpoint_data,
        System::Boolean include_encapsulation,
        System::UInt16  encapsulation_id,
        System::UInt32 size) override;

    virtual System::UInt32 get_serialized_sample_min_size(
        TypePluginDefaultEndpointData^ endpoint_data,
        System::Boolean include_encapsulation,
        System::UInt16  encapsulation_id,
        System::UInt32 size) override;

    virtual System::UInt32 get_serialized_sample_size(
        TypePluginDefaultEndpointData^ endpoint_data,
        Boolean include_encapsulation,
        UInt16 encapsulation_id,
        UInt32 current_alignment,
        ShapeTypeExtended^ sample) override;

// ---  Key Management functions: --------------------------------------------
public:
    virtual System::UInt32 get_serialized_key_max_size(
        TypePluginDefaultEndpointData^ endpoint_data,
        System::Boolean include_encapsulation,
        System::UInt16  encapsulation_id,
        System::UInt32 current_alignment) override;

    virtual System::Boolean serialize_key(
        TypePluginDefaultEndpointData^ endpoint_data,
        ShapeTypeExtended^ key,
        CdrStream% stream,
        System::Boolean serialize_encapsulation,
        System::UInt16  encapsulation_id,
        System::Boolean serialize_sample,
        System::Object^ endpoint_plugin_qos) override;

    virtual System::Boolean deserialize_key_sample(
        TypePluginDefaultEndpointData^ endpoint_data,
        ShapeTypeExtended^ key,
        CdrStream% stream,
        System::Boolean deserialize_encapsulation,
        System::Boolean deserialize_sample,
        System::Object^ endpoint_plugin_qos) override;

    System::Boolean serialized_sample_to_key(
        TypePluginDefaultEndpointData^ endpoint_data,
        ShapeTypeExtended^ sample,
        CdrStream% stream,
        System::Boolean deserialize_encapsulation,
        System::Boolean deserialize_key,
        System::Object^ endpoint_plugin_qos);

 

    virtual System::Boolean instance_to_key(
        TypePluginDefaultEndpointData^ endpoint_data,
        ShapeTypeExtended^ key,
        ShapeTypeExtended^ instance) override;

    virtual System::Boolean key_to_instance(
        TypePluginDefaultEndpointData^ endpoint_data,
        ShapeTypeExtended^ instance,
        ShapeTypeExtended^ key) override;

    virtual System::Boolean serialized_sample_to_key_hash(
        TypePluginDefaultEndpointData^ endpoint_data,
        CdrStream% stream,
        KeyHash_t% key_hash,
        System::Boolean deserialize_encapsulation,
        System::Object^ endpoint_plugin_qos) override;

 


// ---  Plug-in lifecycle management methods: --------------------------------
public:
    static ShapeTypeExtendedPlugin^ get_instance();

    static void dispose();

private:
    ShapeTypeExtendedPlugin()
            : DefaultTypePlugin(
                "ShapeTypeExtended",

                true, // keyed
    
                false, // use RTPS-compliant alignment
                   ShapeTypeExtended::get_typecode()) {
        // empty
    }

    static ShapeTypeExtendedPlugin^ _singleton;
};
