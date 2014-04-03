/*
  WARNING: THIS FILE IS AUTO-GENERATED. DO NOT MODIFY.

  This file was generated from soccer.idl using "rtiddsgen".
  The rtiddsgen tool is part of the RTI Connext distribution.
  For more information, type 'rtiddsgen -help' at a command shell
  or consult the RTI Connext manual.
*/

#pragma once

#include "soccer.h"


    
/* ------------------------------------------------------------------------
 * Type: AggregateRunningData
 * ------------------------------------------------------------------------ */

public ref class AggregateRunningDataPlugin :
    DefaultTypePlugin<AggregateRunningData^> {
// --- Support methods: ------------------------------------------------------
public:
    void print_data(
        AggregateRunningData^ sample,
        System::String^ desc,
        System::UInt32 indent);


// --- (De)Serialize methods: ------------------------------------------------
public:
    virtual System::Boolean serialize(
        TypePluginDefaultEndpointData^ endpoint_data,
        AggregateRunningData^ sample,
        CdrStream% stream,
        System::Boolean serialize_encapsulation,
        System::UInt16  encapsulation_id,
        System::Boolean serialize_sample,
        System::Object^ endpoint_plugin_qos) override;

    virtual System::Boolean deserialize_sample(
        TypePluginDefaultEndpointData^ endpoint_data,
        AggregateRunningData^ sample,
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
        AggregateRunningData^ sample) override;

// ---  Key Management functions: --------------------------------------------
public:
    virtual System::UInt32 get_serialized_key_max_size(
        TypePluginDefaultEndpointData^ endpoint_data,
        System::Boolean include_encapsulation,
        System::UInt16  encapsulation_id,
        System::UInt32 current_alignment) override;

    virtual System::Boolean serialize_key(
        TypePluginDefaultEndpointData^ endpoint_data,
        AggregateRunningData^ key,
        CdrStream% stream,
        System::Boolean serialize_encapsulation,
        System::UInt16  encapsulation_id,
        System::Boolean serialize_sample,
        System::Object^ endpoint_plugin_qos) override;

    virtual System::Boolean deserialize_key_sample(
        TypePluginDefaultEndpointData^ endpoint_data,
        AggregateRunningData^ key,
        CdrStream% stream,
        System::Boolean deserialize_encapsulation,
        System::Boolean deserialize_sample,
        System::Object^ endpoint_plugin_qos) override;

    System::Boolean serialized_sample_to_key(
        TypePluginDefaultEndpointData^ endpoint_data,
        AggregateRunningData^ sample,
        CdrStream% stream,
        System::Boolean deserialize_encapsulation,
        System::Boolean deserialize_key,
        System::Object^ endpoint_plugin_qos);

 

    virtual System::Boolean instance_to_key(
        TypePluginDefaultEndpointData^ endpoint_data,
        AggregateRunningData^ key,
        AggregateRunningData^ instance) override;

    virtual System::Boolean key_to_instance(
        TypePluginDefaultEndpointData^ endpoint_data,
        AggregateRunningData^ instance,
        AggregateRunningData^ key) override;

    virtual System::Boolean serialized_sample_to_key_hash(
        TypePluginDefaultEndpointData^ endpoint_data,
        CdrStream% stream,
        KeyHash_t% key_hash,
        System::Boolean deserialize_encapsulation,
        System::Object^ endpoint_plugin_qos) override;

 


// ---  Plug-in lifecycle management methods: --------------------------------
public:
    static AggregateRunningDataPlugin^ get_instance();

    static void dispose();

private:
    AggregateRunningDataPlugin()
            : DefaultTypePlugin(
                "AggregateRunningData",

                true, // keyed
    
                false, // use RTPS-compliant alignment
                   AggregateRunningData::get_typecode()) {
        // empty
    }

    static AggregateRunningDataPlugin^ _singleton;
};

/* ------------------------------------------------------------------------
 * Enum Type: Intensity
 * ------------------------------------------------------------------------ */

public ref class IntensityPlugin {
// --- (De)Serialization Methods: --------------------------------------------
public:
    System::Boolean serialize(
        TypePluginEndpointData^ endpoint_data,
        Intensity sample,
        CdrStream% stream,
        System::Boolean serialize_encapsulation,
        System::UInt16  encapsulation_id,
        System::Boolean serialize_sample,
        System::Object^ endpoint_plugin_qos);

    System::Boolean deserialize_sample(
        TypePluginEndpointData^ endpoint_data,
        Intensity% sample,
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
        Intensity sample);

// --- Key Management functions: ---------------------------------------------
public:
    System::Boolean serialize_key(
        TypePluginEndpointData^ endpoint_data,
        Intensity key,
        CdrStream% stream,
        System::Boolean serialize_encapsulation,
        System::UInt16  encapsulation_id,
        System::Boolean serialize_sample,
        System::Object^ endpoint_plugin_qos);

    System::Boolean deserialize_key_sample(
        TypePluginEndpointData^ endpoint_data,
        Intensity% key,
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
        Intensity% sample,
        CdrStream% stream, 
        Boolean deserialize_encapsulation,  
        Boolean deserialize_key, 
        Object^ endpoint_plugin_qos);


// --- Support functions: ----------------------------------------------------
public:
    void print_data(
        Intensity sample,
        System::String^ desc,
        System::UInt32 indent_level);

    



// ---  Plug-in lifecycle management methods: --------------------------------
public:
    static IntensityPlugin^ get_instance();

    static void dispose();

private:
    IntensityPlugin() { /*empty*/ }

    static IntensityPlugin^ _singleton;
};  

/* ------------------------------------------------------------------------
 * Type: CurrentRunningData
 * ------------------------------------------------------------------------ */

public ref class CurrentRunningDataPlugin :
    DefaultTypePlugin<CurrentRunningData^> {
// --- Support methods: ------------------------------------------------------
public:
    void print_data(
        CurrentRunningData^ sample,
        System::String^ desc,
        System::UInt32 indent);


// --- (De)Serialize methods: ------------------------------------------------
public:
    virtual System::Boolean serialize(
        TypePluginDefaultEndpointData^ endpoint_data,
        CurrentRunningData^ sample,
        CdrStream% stream,
        System::Boolean serialize_encapsulation,
        System::UInt16  encapsulation_id,
        System::Boolean serialize_sample,
        System::Object^ endpoint_plugin_qos) override;

    virtual System::Boolean deserialize_sample(
        TypePluginDefaultEndpointData^ endpoint_data,
        CurrentRunningData^ sample,
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
        CurrentRunningData^ sample) override;

// ---  Key Management functions: --------------------------------------------
public:
    virtual System::UInt32 get_serialized_key_max_size(
        TypePluginDefaultEndpointData^ endpoint_data,
        System::Boolean include_encapsulation,
        System::UInt16  encapsulation_id,
        System::UInt32 current_alignment) override;

    virtual System::Boolean serialize_key(
        TypePluginDefaultEndpointData^ endpoint_data,
        CurrentRunningData^ key,
        CdrStream% stream,
        System::Boolean serialize_encapsulation,
        System::UInt16  encapsulation_id,
        System::Boolean serialize_sample,
        System::Object^ endpoint_plugin_qos) override;

    virtual System::Boolean deserialize_key_sample(
        TypePluginDefaultEndpointData^ endpoint_data,
        CurrentRunningData^ key,
        CdrStream% stream,
        System::Boolean deserialize_encapsulation,
        System::Boolean deserialize_sample,
        System::Object^ endpoint_plugin_qos) override;

    System::Boolean serialized_sample_to_key(
        TypePluginDefaultEndpointData^ endpoint_data,
        CurrentRunningData^ sample,
        CdrStream% stream,
        System::Boolean deserialize_encapsulation,
        System::Boolean deserialize_key,
        System::Object^ endpoint_plugin_qos);

 

    virtual System::Boolean instance_to_key(
        TypePluginDefaultEndpointData^ endpoint_data,
        CurrentRunningData^ key,
        CurrentRunningData^ instance) override;

    virtual System::Boolean key_to_instance(
        TypePluginDefaultEndpointData^ endpoint_data,
        CurrentRunningData^ instance,
        CurrentRunningData^ key) override;

    virtual System::Boolean serialized_sample_to_key_hash(
        TypePluginDefaultEndpointData^ endpoint_data,
        CdrStream% stream,
        KeyHash_t% key_hash,
        System::Boolean deserialize_encapsulation,
        System::Object^ endpoint_plugin_qos) override;

 


// ---  Plug-in lifecycle management methods: --------------------------------
public:
    static CurrentRunningDataPlugin^ get_instance();

    static void dispose();

private:
    CurrentRunningDataPlugin()
            : DefaultTypePlugin(
                "CurrentRunningData",

                true, // keyed
    
                false, // use RTPS-compliant alignment
                   CurrentRunningData::get_typecode()) {
        // empty
    }

    static CurrentRunningDataPlugin^ _singleton;
};

/* ------------------------------------------------------------------------
 * Type: PlayerBallPossession
 * ------------------------------------------------------------------------ */

public ref class PlayerBallPossessionPlugin :
    DefaultTypePlugin<PlayerBallPossession^> {
// --- Support methods: ------------------------------------------------------
public:
    void print_data(
        PlayerBallPossession^ sample,
        System::String^ desc,
        System::UInt32 indent);


// --- (De)Serialize methods: ------------------------------------------------
public:
    virtual System::Boolean serialize(
        TypePluginDefaultEndpointData^ endpoint_data,
        PlayerBallPossession^ sample,
        CdrStream% stream,
        System::Boolean serialize_encapsulation,
        System::UInt16  encapsulation_id,
        System::Boolean serialize_sample,
        System::Object^ endpoint_plugin_qos) override;

    virtual System::Boolean deserialize_sample(
        TypePluginDefaultEndpointData^ endpoint_data,
        PlayerBallPossession^ sample,
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
        PlayerBallPossession^ sample) override;

// ---  Key Management functions: --------------------------------------------
public:
    virtual System::UInt32 get_serialized_key_max_size(
        TypePluginDefaultEndpointData^ endpoint_data,
        System::Boolean include_encapsulation,
        System::UInt16  encapsulation_id,
        System::UInt32 current_alignment) override;

    virtual System::Boolean serialize_key(
        TypePluginDefaultEndpointData^ endpoint_data,
        PlayerBallPossession^ key,
        CdrStream% stream,
        System::Boolean serialize_encapsulation,
        System::UInt16  encapsulation_id,
        System::Boolean serialize_sample,
        System::Object^ endpoint_plugin_qos) override;

    virtual System::Boolean deserialize_key_sample(
        TypePluginDefaultEndpointData^ endpoint_data,
        PlayerBallPossession^ key,
        CdrStream% stream,
        System::Boolean deserialize_encapsulation,
        System::Boolean deserialize_sample,
        System::Object^ endpoint_plugin_qos) override;

    System::Boolean serialized_sample_to_key(
        TypePluginDefaultEndpointData^ endpoint_data,
        PlayerBallPossession^ sample,
        CdrStream% stream,
        System::Boolean deserialize_encapsulation,
        System::Boolean deserialize_key,
        System::Object^ endpoint_plugin_qos);

 

    virtual System::Boolean instance_to_key(
        TypePluginDefaultEndpointData^ endpoint_data,
        PlayerBallPossession^ key,
        PlayerBallPossession^ instance) override;

    virtual System::Boolean key_to_instance(
        TypePluginDefaultEndpointData^ endpoint_data,
        PlayerBallPossession^ instance,
        PlayerBallPossession^ key) override;

    virtual System::Boolean serialized_sample_to_key_hash(
        TypePluginDefaultEndpointData^ endpoint_data,
        CdrStream% stream,
        KeyHash_t% key_hash,
        System::Boolean deserialize_encapsulation,
        System::Object^ endpoint_plugin_qos) override;

 


// ---  Plug-in lifecycle management methods: --------------------------------
public:
    static PlayerBallPossessionPlugin^ get_instance();

    static void dispose();

private:
    PlayerBallPossessionPlugin()
            : DefaultTypePlugin(
                "PlayerBallPossession",

                true, // keyed
    
                false, // use RTPS-compliant alignment
                   PlayerBallPossession::get_typecode()) {
        // empty
    }

    static PlayerBallPossessionPlugin^ _singleton;
};

/* ------------------------------------------------------------------------
 * Type: PlayerData
 * ------------------------------------------------------------------------ */

public ref class PlayerDataPlugin :
    DefaultTypePlugin<PlayerData^> {
// --- Support methods: ------------------------------------------------------
public:
    void print_data(
        PlayerData^ sample,
        System::String^ desc,
        System::UInt32 indent);


// --- (De)Serialize methods: ------------------------------------------------
public:
    virtual System::Boolean serialize(
        TypePluginDefaultEndpointData^ endpoint_data,
        PlayerData^ sample,
        CdrStream% stream,
        System::Boolean serialize_encapsulation,
        System::UInt16  encapsulation_id,
        System::Boolean serialize_sample,
        System::Object^ endpoint_plugin_qos) override;

    virtual System::Boolean deserialize_sample(
        TypePluginDefaultEndpointData^ endpoint_data,
        PlayerData^ sample,
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
        PlayerData^ sample) override;

// ---  Key Management functions: --------------------------------------------
public:
    virtual System::UInt32 get_serialized_key_max_size(
        TypePluginDefaultEndpointData^ endpoint_data,
        System::Boolean include_encapsulation,
        System::UInt16  encapsulation_id,
        System::UInt32 current_alignment) override;

    virtual System::Boolean serialize_key(
        TypePluginDefaultEndpointData^ endpoint_data,
        PlayerData^ key,
        CdrStream% stream,
        System::Boolean serialize_encapsulation,
        System::UInt16  encapsulation_id,
        System::Boolean serialize_sample,
        System::Object^ endpoint_plugin_qos) override;

    virtual System::Boolean deserialize_key_sample(
        TypePluginDefaultEndpointData^ endpoint_data,
        PlayerData^ key,
        CdrStream% stream,
        System::Boolean deserialize_encapsulation,
        System::Boolean deserialize_sample,
        System::Object^ endpoint_plugin_qos) override;

    System::Boolean serialized_sample_to_key(
        TypePluginDefaultEndpointData^ endpoint_data,
        PlayerData^ sample,
        CdrStream% stream,
        System::Boolean deserialize_encapsulation,
        System::Boolean deserialize_key,
        System::Object^ endpoint_plugin_qos);

 

    virtual System::Boolean instance_to_key(
        TypePluginDefaultEndpointData^ endpoint_data,
        PlayerData^ key,
        PlayerData^ instance) override;

    virtual System::Boolean key_to_instance(
        TypePluginDefaultEndpointData^ endpoint_data,
        PlayerData^ instance,
        PlayerData^ key) override;

    virtual System::Boolean serialized_sample_to_key_hash(
        TypePluginDefaultEndpointData^ endpoint_data,
        CdrStream% stream,
        KeyHash_t% key_hash,
        System::Boolean deserialize_encapsulation,
        System::Object^ endpoint_plugin_qos) override;

 


// ---  Plug-in lifecycle management methods: --------------------------------
public:
    static PlayerDataPlugin^ get_instance();

    static void dispose();

private:
    PlayerDataPlugin()
            : DefaultTypePlugin(
                "PlayerData",

                true, // keyed
    
                false, // use RTPS-compliant alignment
                   PlayerData::get_typecode()) {
        // empty
    }

    static PlayerDataPlugin^ _singleton;
};

/* ------------------------------------------------------------------------
 * Type: SensorData
 * ------------------------------------------------------------------------ */

public ref class SensorDataPlugin :
    DefaultTypePlugin<SensorData^> {
// --- Support methods: ------------------------------------------------------
public:
    void print_data(
        SensorData^ sample,
        System::String^ desc,
        System::UInt32 indent);


// --- (De)Serialize methods: ------------------------------------------------
public:
    virtual System::Boolean serialize(
        TypePluginDefaultEndpointData^ endpoint_data,
        SensorData^ sample,
        CdrStream% stream,
        System::Boolean serialize_encapsulation,
        System::UInt16  encapsulation_id,
        System::Boolean serialize_sample,
        System::Object^ endpoint_plugin_qos) override;

    virtual System::Boolean deserialize_sample(
        TypePluginDefaultEndpointData^ endpoint_data,
        SensorData^ sample,
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
        SensorData^ sample) override;

// ---  Key Management functions: --------------------------------------------
public:
    virtual System::UInt32 get_serialized_key_max_size(
        TypePluginDefaultEndpointData^ endpoint_data,
        System::Boolean include_encapsulation,
        System::UInt16  encapsulation_id,
        System::UInt32 current_alignment) override;

    virtual System::Boolean serialize_key(
        TypePluginDefaultEndpointData^ endpoint_data,
        SensorData^ key,
        CdrStream% stream,
        System::Boolean serialize_encapsulation,
        System::UInt16  encapsulation_id,
        System::Boolean serialize_sample,
        System::Object^ endpoint_plugin_qos) override;

    virtual System::Boolean deserialize_key_sample(
        TypePluginDefaultEndpointData^ endpoint_data,
        SensorData^ key,
        CdrStream% stream,
        System::Boolean deserialize_encapsulation,
        System::Boolean deserialize_sample,
        System::Object^ endpoint_plugin_qos) override;

    System::Boolean serialized_sample_to_key(
        TypePluginDefaultEndpointData^ endpoint_data,
        SensorData^ sample,
        CdrStream% stream,
        System::Boolean deserialize_encapsulation,
        System::Boolean deserialize_key,
        System::Object^ endpoint_plugin_qos);

 

    virtual System::Boolean instance_to_key(
        TypePluginDefaultEndpointData^ endpoint_data,
        SensorData^ key,
        SensorData^ instance) override;

    virtual System::Boolean key_to_instance(
        TypePluginDefaultEndpointData^ endpoint_data,
        SensorData^ instance,
        SensorData^ key) override;

    virtual System::Boolean serialized_sample_to_key_hash(
        TypePluginDefaultEndpointData^ endpoint_data,
        CdrStream% stream,
        KeyHash_t% key_hash,
        System::Boolean deserialize_encapsulation,
        System::Object^ endpoint_plugin_qos) override;

 


// ---  Plug-in lifecycle management methods: --------------------------------
public:
    static SensorDataPlugin^ get_instance();

    static void dispose();

private:
    SensorDataPlugin()
            : DefaultTypePlugin(
                "SensorData",

                true, // keyed
    
                false, // use RTPS-compliant alignment
                   SensorData::get_typecode()) {
        // empty
    }

    static SensorDataPlugin^ _singleton;
};

/* ------------------------------------------------------------------------
 * Type: ShotOnGoalData
 * ------------------------------------------------------------------------ */

public ref class ShotOnGoalDataPlugin :
    DefaultTypePlugin<ShotOnGoalData^> {
// --- Support methods: ------------------------------------------------------
public:
    void print_data(
        ShotOnGoalData^ sample,
        System::String^ desc,
        System::UInt32 indent);


// --- (De)Serialize methods: ------------------------------------------------
public:
    virtual System::Boolean serialize(
        TypePluginDefaultEndpointData^ endpoint_data,
        ShotOnGoalData^ sample,
        CdrStream% stream,
        System::Boolean serialize_encapsulation,
        System::UInt16  encapsulation_id,
        System::Boolean serialize_sample,
        System::Object^ endpoint_plugin_qos) override;

    virtual System::Boolean deserialize_sample(
        TypePluginDefaultEndpointData^ endpoint_data,
        ShotOnGoalData^ sample,
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
        ShotOnGoalData^ sample) override;

// ---  Key Management functions: --------------------------------------------
public:
    virtual System::UInt32 get_serialized_key_max_size(
        TypePluginDefaultEndpointData^ endpoint_data,
        System::Boolean include_encapsulation,
        System::UInt16  encapsulation_id,
        System::UInt32 current_alignment) override;

    virtual System::Boolean serialize_key(
        TypePluginDefaultEndpointData^ endpoint_data,
        ShotOnGoalData^ key,
        CdrStream% stream,
        System::Boolean serialize_encapsulation,
        System::UInt16  encapsulation_id,
        System::Boolean serialize_sample,
        System::Object^ endpoint_plugin_qos) override;

    virtual System::Boolean deserialize_key_sample(
        TypePluginDefaultEndpointData^ endpoint_data,
        ShotOnGoalData^ key,
        CdrStream% stream,
        System::Boolean deserialize_encapsulation,
        System::Boolean deserialize_sample,
        System::Object^ endpoint_plugin_qos) override;

    System::Boolean serialized_sample_to_key(
        TypePluginDefaultEndpointData^ endpoint_data,
        ShotOnGoalData^ sample,
        CdrStream% stream,
        System::Boolean deserialize_encapsulation,
        System::Boolean deserialize_key,
        System::Object^ endpoint_plugin_qos);

 


// ---  Plug-in lifecycle management methods: --------------------------------
public:
    static ShotOnGoalDataPlugin^ get_instance();

    static void dispose();

private:
    ShotOnGoalDataPlugin()
            : DefaultTypePlugin(
                "ShotOnGoalData",

                false, // not keyed
    
                false, // use RTPS-compliant alignment
                   ShotOnGoalData::get_typecode()) {
        // empty
    }

    static ShotOnGoalDataPlugin^ _singleton;
};

/* ------------------------------------------------------------------------
 * Type: TeamBallPossession
 * ------------------------------------------------------------------------ */

public ref class TeamBallPossessionPlugin :
    DefaultTypePlugin<TeamBallPossession^> {
// --- Support methods: ------------------------------------------------------
public:
    void print_data(
        TeamBallPossession^ sample,
        System::String^ desc,
        System::UInt32 indent);


// --- (De)Serialize methods: ------------------------------------------------
public:
    virtual System::Boolean serialize(
        TypePluginDefaultEndpointData^ endpoint_data,
        TeamBallPossession^ sample,
        CdrStream% stream,
        System::Boolean serialize_encapsulation,
        System::UInt16  encapsulation_id,
        System::Boolean serialize_sample,
        System::Object^ endpoint_plugin_qos) override;

    virtual System::Boolean deserialize_sample(
        TypePluginDefaultEndpointData^ endpoint_data,
        TeamBallPossession^ sample,
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
        TeamBallPossession^ sample) override;

// ---  Key Management functions: --------------------------------------------
public:
    virtual System::UInt32 get_serialized_key_max_size(
        TypePluginDefaultEndpointData^ endpoint_data,
        System::Boolean include_encapsulation,
        System::UInt16  encapsulation_id,
        System::UInt32 current_alignment) override;

    virtual System::Boolean serialize_key(
        TypePluginDefaultEndpointData^ endpoint_data,
        TeamBallPossession^ key,
        CdrStream% stream,
        System::Boolean serialize_encapsulation,
        System::UInt16  encapsulation_id,
        System::Boolean serialize_sample,
        System::Object^ endpoint_plugin_qos) override;

    virtual System::Boolean deserialize_key_sample(
        TypePluginDefaultEndpointData^ endpoint_data,
        TeamBallPossession^ key,
        CdrStream% stream,
        System::Boolean deserialize_encapsulation,
        System::Boolean deserialize_sample,
        System::Object^ endpoint_plugin_qos) override;

    System::Boolean serialized_sample_to_key(
        TypePluginDefaultEndpointData^ endpoint_data,
        TeamBallPossession^ sample,
        CdrStream% stream,
        System::Boolean deserialize_encapsulation,
        System::Boolean deserialize_key,
        System::Object^ endpoint_plugin_qos);

 


// ---  Plug-in lifecycle management methods: --------------------------------
public:
    static TeamBallPossessionPlugin^ get_instance();

    static void dispose();

private:
    TeamBallPossessionPlugin()
            : DefaultTypePlugin(
                "TeamBallPossession",

                false, // not keyed
    
                false, // use RTPS-compliant alignment
                   TeamBallPossession::get_typecode()) {
        // empty
    }

    static TeamBallPossessionPlugin^ _singleton;
};
