/*
  WARNING: THIS FILE IS AUTO-GENERATED. DO NOT MODIFY.

  This file was generated from soccer.idl using "rtiddsgen".
  The rtiddsgen tool is part of the RTI Connext distribution.
  For more information, type 'rtiddsgen -help' at a command shell
  or consult the RTI Connext manual.
*/

#pragma once

#include "soccer.h"


class DDSDataWriter;
class DDSDataReader;
    
// ---------------------------------------------------------------------------
// AggregateRunningDataTypeSupport
// ---------------------------------------------------------------------------

ref class AggregateRunningDataPlugin;

/* A collection of useful methods for dealing with objects of type
 * AggregateRunningData.
 */
public ref class AggregateRunningDataTypeSupport
        : public DDS::TypedTypeSupport<AggregateRunningData^> {
    // --- Type name: --------------------------------------------------------
  public:
    static System::String^ TYPENAME = "AggregateRunningData";


    // --- Public Methods: ---------------------------------------------------
  public:
    /* Get the default name of this type.
     *
     * An application can choose to register a type under any name, so
     * calling this method is strictly optional.
     */
    static System::String^ get_type_name();

    /* Register this type with the given participant under the given logical
     * name. This type must be registered before a Topic can be created that
     * uses it.
     */
    static void register_type(
            DDS::DomainParticipant^ participant,
            System::String^ type_name);

    /* Unregister this type from the given participant, where it was
     * previously registered under the given name. No further Topic creation
     * using this type will be possible.
     *
     * Unregistration allows some middleware resources to be reclaimed.
     */
    static void unregister_type(
            DDS::DomainParticipant^ participant,
            System::String^ type_name);

    /* Create an instance of the AggregateRunningData type.
     */
    static AggregateRunningData^ create_data();

    /* If instances of the AggregateRunningData type require any
     * explicit finalization, perform it now on the given sample.
     */
    static void delete_data(AggregateRunningData^ data);

    /* Write the contents of the data sample to standard out.
     */
    static void print_data(AggregateRunningData^ a_data);

    /* Perform a deep copy of the contents of one data sample over those of
     * another, overwriting it.
     */
    static void copy_data(
        AggregateRunningData^ dst_data,
        AggregateRunningData^ src_data);


    // --- Implementation: ---------------------------------------------------
    /* The following code is for the use of the middleware infrastructure.
     * Applications are not expected to call it directly.
     */
public:
    virtual DDS::DataReader^ create_datareaderI(
        System::IntPtr impl) override;
    virtual DDS::DataWriter^ create_datawriterI(
        System::IntPtr impl) override;
        
    virtual AggregateRunningData^ create_data_untyped() override;
    
    virtual System::String^ get_type_name_untyped() override;
        

public:
    static AggregateRunningDataTypeSupport^ get_instance();

    AggregateRunningDataTypeSupport();

private:
    static AggregateRunningDataTypeSupport^ _singleton;
    AggregateRunningDataPlugin^ _type_plugin;
};


// ---------------------------------------------------------------------------
// AggregateRunningDataDataReader
// ---------------------------------------------------------------------------

/**
 * A reader for the AggregateRunningData type.
 */
public ref class AggregateRunningDataDataReader :
        public DDS::TypedDataReader<AggregateRunningData^> {
    /* The following code is for the use of the middleware infrastructure.
     * Applications are not expected to call it directly.
     */
  internal:
    AggregateRunningDataDataReader(System::IntPtr impl);
};


// ---------------------------------------------------------------------------
// AggregateRunningDataDataWriter
// ---------------------------------------------------------------------------

/**
 * A writer for the AggregateRunningData user type.
 */
public ref class AggregateRunningDataDataWriter :
        public DDS::TypedDataWriter<AggregateRunningData^> {
    /* The following code is for the use of the middleware infrastructure.
     * Applications are not expected to call it directly.
     */
  internal:
    AggregateRunningDataDataWriter(System::IntPtr impl);
};

// ---------------------------------------------------------------------------
// CurrentRunningDataTypeSupport
// ---------------------------------------------------------------------------

ref class CurrentRunningDataPlugin;

/* A collection of useful methods for dealing with objects of type
 * CurrentRunningData.
 */
public ref class CurrentRunningDataTypeSupport
        : public DDS::TypedTypeSupport<CurrentRunningData^> {
    // --- Type name: --------------------------------------------------------
  public:
    static System::String^ TYPENAME = "CurrentRunningData";


    // --- Public Methods: ---------------------------------------------------
  public:
    /* Get the default name of this type.
     *
     * An application can choose to register a type under any name, so
     * calling this method is strictly optional.
     */
    static System::String^ get_type_name();

    /* Register this type with the given participant under the given logical
     * name. This type must be registered before a Topic can be created that
     * uses it.
     */
    static void register_type(
            DDS::DomainParticipant^ participant,
            System::String^ type_name);

    /* Unregister this type from the given participant, where it was
     * previously registered under the given name. No further Topic creation
     * using this type will be possible.
     *
     * Unregistration allows some middleware resources to be reclaimed.
     */
    static void unregister_type(
            DDS::DomainParticipant^ participant,
            System::String^ type_name);

    /* Create an instance of the CurrentRunningData type.
     */
    static CurrentRunningData^ create_data();

    /* If instances of the CurrentRunningData type require any
     * explicit finalization, perform it now on the given sample.
     */
    static void delete_data(CurrentRunningData^ data);

    /* Write the contents of the data sample to standard out.
     */
    static void print_data(CurrentRunningData^ a_data);

    /* Perform a deep copy of the contents of one data sample over those of
     * another, overwriting it.
     */
    static void copy_data(
        CurrentRunningData^ dst_data,
        CurrentRunningData^ src_data);


    // --- Implementation: ---------------------------------------------------
    /* The following code is for the use of the middleware infrastructure.
     * Applications are not expected to call it directly.
     */
public:
    virtual DDS::DataReader^ create_datareaderI(
        System::IntPtr impl) override;
    virtual DDS::DataWriter^ create_datawriterI(
        System::IntPtr impl) override;
        
    virtual CurrentRunningData^ create_data_untyped() override;
    
    virtual System::String^ get_type_name_untyped() override;
        

public:
    static CurrentRunningDataTypeSupport^ get_instance();

    CurrentRunningDataTypeSupport();

private:
    static CurrentRunningDataTypeSupport^ _singleton;
    CurrentRunningDataPlugin^ _type_plugin;
};


// ---------------------------------------------------------------------------
// CurrentRunningDataDataReader
// ---------------------------------------------------------------------------

/**
 * A reader for the CurrentRunningData type.
 */
public ref class CurrentRunningDataDataReader :
        public DDS::TypedDataReader<CurrentRunningData^> {
    /* The following code is for the use of the middleware infrastructure.
     * Applications are not expected to call it directly.
     */
  internal:
    CurrentRunningDataDataReader(System::IntPtr impl);
};


// ---------------------------------------------------------------------------
// CurrentRunningDataDataWriter
// ---------------------------------------------------------------------------

/**
 * A writer for the CurrentRunningData user type.
 */
public ref class CurrentRunningDataDataWriter :
        public DDS::TypedDataWriter<CurrentRunningData^> {
    /* The following code is for the use of the middleware infrastructure.
     * Applications are not expected to call it directly.
     */
  internal:
    CurrentRunningDataDataWriter(System::IntPtr impl);
};

// ---------------------------------------------------------------------------
// PlayerBallPossessionTypeSupport
// ---------------------------------------------------------------------------

ref class PlayerBallPossessionPlugin;

/* A collection of useful methods for dealing with objects of type
 * PlayerBallPossession.
 */
public ref class PlayerBallPossessionTypeSupport
        : public DDS::TypedTypeSupport<PlayerBallPossession^> {
    // --- Type name: --------------------------------------------------------
  public:
    static System::String^ TYPENAME = "PlayerBallPossession";


    // --- Public Methods: ---------------------------------------------------
  public:
    /* Get the default name of this type.
     *
     * An application can choose to register a type under any name, so
     * calling this method is strictly optional.
     */
    static System::String^ get_type_name();

    /* Register this type with the given participant under the given logical
     * name. This type must be registered before a Topic can be created that
     * uses it.
     */
    static void register_type(
            DDS::DomainParticipant^ participant,
            System::String^ type_name);

    /* Unregister this type from the given participant, where it was
     * previously registered under the given name. No further Topic creation
     * using this type will be possible.
     *
     * Unregistration allows some middleware resources to be reclaimed.
     */
    static void unregister_type(
            DDS::DomainParticipant^ participant,
            System::String^ type_name);

    /* Create an instance of the PlayerBallPossession type.
     */
    static PlayerBallPossession^ create_data();

    /* If instances of the PlayerBallPossession type require any
     * explicit finalization, perform it now on the given sample.
     */
    static void delete_data(PlayerBallPossession^ data);

    /* Write the contents of the data sample to standard out.
     */
    static void print_data(PlayerBallPossession^ a_data);

    /* Perform a deep copy of the contents of one data sample over those of
     * another, overwriting it.
     */
    static void copy_data(
        PlayerBallPossession^ dst_data,
        PlayerBallPossession^ src_data);


    // --- Implementation: ---------------------------------------------------
    /* The following code is for the use of the middleware infrastructure.
     * Applications are not expected to call it directly.
     */
public:
    virtual DDS::DataReader^ create_datareaderI(
        System::IntPtr impl) override;
    virtual DDS::DataWriter^ create_datawriterI(
        System::IntPtr impl) override;
        
    virtual PlayerBallPossession^ create_data_untyped() override;
    
    virtual System::String^ get_type_name_untyped() override;
        

public:
    static PlayerBallPossessionTypeSupport^ get_instance();

    PlayerBallPossessionTypeSupport();

private:
    static PlayerBallPossessionTypeSupport^ _singleton;
    PlayerBallPossessionPlugin^ _type_plugin;
};


// ---------------------------------------------------------------------------
// PlayerBallPossessionDataReader
// ---------------------------------------------------------------------------

/**
 * A reader for the PlayerBallPossession type.
 */
public ref class PlayerBallPossessionDataReader :
        public DDS::TypedDataReader<PlayerBallPossession^> {
    /* The following code is for the use of the middleware infrastructure.
     * Applications are not expected to call it directly.
     */
  internal:
    PlayerBallPossessionDataReader(System::IntPtr impl);
};


// ---------------------------------------------------------------------------
// PlayerBallPossessionDataWriter
// ---------------------------------------------------------------------------

/**
 * A writer for the PlayerBallPossession user type.
 */
public ref class PlayerBallPossessionDataWriter :
        public DDS::TypedDataWriter<PlayerBallPossession^> {
    /* The following code is for the use of the middleware infrastructure.
     * Applications are not expected to call it directly.
     */
  internal:
    PlayerBallPossessionDataWriter(System::IntPtr impl);
};

// ---------------------------------------------------------------------------
// PlayerDataTypeSupport
// ---------------------------------------------------------------------------

ref class PlayerDataPlugin;

/* A collection of useful methods for dealing with objects of type
 * PlayerData.
 */
public ref class PlayerDataTypeSupport
        : public DDS::TypedTypeSupport<PlayerData^> {
    // --- Type name: --------------------------------------------------------
  public:
    static System::String^ TYPENAME = "PlayerData";


    // --- Public Methods: ---------------------------------------------------
  public:
    /* Get the default name of this type.
     *
     * An application can choose to register a type under any name, so
     * calling this method is strictly optional.
     */
    static System::String^ get_type_name();

    /* Register this type with the given participant under the given logical
     * name. This type must be registered before a Topic can be created that
     * uses it.
     */
    static void register_type(
            DDS::DomainParticipant^ participant,
            System::String^ type_name);

    /* Unregister this type from the given participant, where it was
     * previously registered under the given name. No further Topic creation
     * using this type will be possible.
     *
     * Unregistration allows some middleware resources to be reclaimed.
     */
    static void unregister_type(
            DDS::DomainParticipant^ participant,
            System::String^ type_name);

    /* Create an instance of the PlayerData type.
     */
    static PlayerData^ create_data();

    /* If instances of the PlayerData type require any
     * explicit finalization, perform it now on the given sample.
     */
    static void delete_data(PlayerData^ data);

    /* Write the contents of the data sample to standard out.
     */
    static void print_data(PlayerData^ a_data);

    /* Perform a deep copy of the contents of one data sample over those of
     * another, overwriting it.
     */
    static void copy_data(
        PlayerData^ dst_data,
        PlayerData^ src_data);


    // --- Implementation: ---------------------------------------------------
    /* The following code is for the use of the middleware infrastructure.
     * Applications are not expected to call it directly.
     */
public:
    virtual DDS::DataReader^ create_datareaderI(
        System::IntPtr impl) override;
    virtual DDS::DataWriter^ create_datawriterI(
        System::IntPtr impl) override;
        
    virtual PlayerData^ create_data_untyped() override;
    
    virtual System::String^ get_type_name_untyped() override;
        

public:
    static PlayerDataTypeSupport^ get_instance();

    PlayerDataTypeSupport();

private:
    static PlayerDataTypeSupport^ _singleton;
    PlayerDataPlugin^ _type_plugin;
};


// ---------------------------------------------------------------------------
// PlayerDataDataReader
// ---------------------------------------------------------------------------

/**
 * A reader for the PlayerData type.
 */
public ref class PlayerDataDataReader :
        public DDS::TypedDataReader<PlayerData^> {
    /* The following code is for the use of the middleware infrastructure.
     * Applications are not expected to call it directly.
     */
  internal:
    PlayerDataDataReader(System::IntPtr impl);
};


// ---------------------------------------------------------------------------
// PlayerDataDataWriter
// ---------------------------------------------------------------------------

/**
 * A writer for the PlayerData user type.
 */
public ref class PlayerDataDataWriter :
        public DDS::TypedDataWriter<PlayerData^> {
    /* The following code is for the use of the middleware infrastructure.
     * Applications are not expected to call it directly.
     */
  internal:
    PlayerDataDataWriter(System::IntPtr impl);
};

// ---------------------------------------------------------------------------
// SensorDataTypeSupport
// ---------------------------------------------------------------------------

ref class SensorDataPlugin;

/* A collection of useful methods for dealing with objects of type
 * SensorData.
 */
public ref class SensorDataTypeSupport
        : public DDS::TypedTypeSupport<SensorData^> {
    // --- Type name: --------------------------------------------------------
  public:
    static System::String^ TYPENAME = "SensorData";


    // --- Public Methods: ---------------------------------------------------
  public:
    /* Get the default name of this type.
     *
     * An application can choose to register a type under any name, so
     * calling this method is strictly optional.
     */
    static System::String^ get_type_name();

    /* Register this type with the given participant under the given logical
     * name. This type must be registered before a Topic can be created that
     * uses it.
     */
    static void register_type(
            DDS::DomainParticipant^ participant,
            System::String^ type_name);

    /* Unregister this type from the given participant, where it was
     * previously registered under the given name. No further Topic creation
     * using this type will be possible.
     *
     * Unregistration allows some middleware resources to be reclaimed.
     */
    static void unregister_type(
            DDS::DomainParticipant^ participant,
            System::String^ type_name);

    /* Create an instance of the SensorData type.
     */
    static SensorData^ create_data();

    /* If instances of the SensorData type require any
     * explicit finalization, perform it now on the given sample.
     */
    static void delete_data(SensorData^ data);

    /* Write the contents of the data sample to standard out.
     */
    static void print_data(SensorData^ a_data);

    /* Perform a deep copy of the contents of one data sample over those of
     * another, overwriting it.
     */
    static void copy_data(
        SensorData^ dst_data,
        SensorData^ src_data);


    // --- Implementation: ---------------------------------------------------
    /* The following code is for the use of the middleware infrastructure.
     * Applications are not expected to call it directly.
     */
public:
    virtual DDS::DataReader^ create_datareaderI(
        System::IntPtr impl) override;
    virtual DDS::DataWriter^ create_datawriterI(
        System::IntPtr impl) override;
        
    virtual SensorData^ create_data_untyped() override;
    
    virtual System::String^ get_type_name_untyped() override;
        

public:
    static SensorDataTypeSupport^ get_instance();

    SensorDataTypeSupport();

private:
    static SensorDataTypeSupport^ _singleton;
    SensorDataPlugin^ _type_plugin;
};


// ---------------------------------------------------------------------------
// SensorDataDataReader
// ---------------------------------------------------------------------------

/**
 * A reader for the SensorData type.
 */
public ref class SensorDataDataReader :
        public DDS::TypedDataReader<SensorData^> {
    /* The following code is for the use of the middleware infrastructure.
     * Applications are not expected to call it directly.
     */
  internal:
    SensorDataDataReader(System::IntPtr impl);
};


// ---------------------------------------------------------------------------
// SensorDataDataWriter
// ---------------------------------------------------------------------------

/**
 * A writer for the SensorData user type.
 */
public ref class SensorDataDataWriter :
        public DDS::TypedDataWriter<SensorData^> {
    /* The following code is for the use of the middleware infrastructure.
     * Applications are not expected to call it directly.
     */
  internal:
    SensorDataDataWriter(System::IntPtr impl);
};

// ---------------------------------------------------------------------------
// ShotOnGoalDataTypeSupport
// ---------------------------------------------------------------------------

ref class ShotOnGoalDataPlugin;

/* A collection of useful methods for dealing with objects of type
 * ShotOnGoalData.
 */
public ref class ShotOnGoalDataTypeSupport
        : public DDS::TypedTypeSupport<ShotOnGoalData^> {
    // --- Type name: --------------------------------------------------------
  public:
    static System::String^ TYPENAME = "ShotOnGoalData";


    // --- Public Methods: ---------------------------------------------------
  public:
    /* Get the default name of this type.
     *
     * An application can choose to register a type under any name, so
     * calling this method is strictly optional.
     */
    static System::String^ get_type_name();

    /* Register this type with the given participant under the given logical
     * name. This type must be registered before a Topic can be created that
     * uses it.
     */
    static void register_type(
            DDS::DomainParticipant^ participant,
            System::String^ type_name);

    /* Unregister this type from the given participant, where it was
     * previously registered under the given name. No further Topic creation
     * using this type will be possible.
     *
     * Unregistration allows some middleware resources to be reclaimed.
     */
    static void unregister_type(
            DDS::DomainParticipant^ participant,
            System::String^ type_name);

    /* Create an instance of the ShotOnGoalData type.
     */
    static ShotOnGoalData^ create_data();

    /* If instances of the ShotOnGoalData type require any
     * explicit finalization, perform it now on the given sample.
     */
    static void delete_data(ShotOnGoalData^ data);

    /* Write the contents of the data sample to standard out.
     */
    static void print_data(ShotOnGoalData^ a_data);

    /* Perform a deep copy of the contents of one data sample over those of
     * another, overwriting it.
     */
    static void copy_data(
        ShotOnGoalData^ dst_data,
        ShotOnGoalData^ src_data);


    // --- Implementation: ---------------------------------------------------
    /* The following code is for the use of the middleware infrastructure.
     * Applications are not expected to call it directly.
     */
public:
    virtual DDS::DataReader^ create_datareaderI(
        System::IntPtr impl) override;
    virtual DDS::DataWriter^ create_datawriterI(
        System::IntPtr impl) override;
        
    virtual ShotOnGoalData^ create_data_untyped() override;
    
    virtual System::String^ get_type_name_untyped() override;
        

public:
    static ShotOnGoalDataTypeSupport^ get_instance();

    ShotOnGoalDataTypeSupport();

private:
    static ShotOnGoalDataTypeSupport^ _singleton;
    ShotOnGoalDataPlugin^ _type_plugin;
};


// ---------------------------------------------------------------------------
// ShotOnGoalDataDataReader
// ---------------------------------------------------------------------------

/**
 * A reader for the ShotOnGoalData type.
 */
public ref class ShotOnGoalDataDataReader :
        public DDS::TypedDataReader<ShotOnGoalData^> {
    /* The following code is for the use of the middleware infrastructure.
     * Applications are not expected to call it directly.
     */
  internal:
    ShotOnGoalDataDataReader(System::IntPtr impl);
};


// ---------------------------------------------------------------------------
// ShotOnGoalDataDataWriter
// ---------------------------------------------------------------------------

/**
 * A writer for the ShotOnGoalData user type.
 */
public ref class ShotOnGoalDataDataWriter :
        public DDS::TypedDataWriter<ShotOnGoalData^> {
    /* The following code is for the use of the middleware infrastructure.
     * Applications are not expected to call it directly.
     */
  internal:
    ShotOnGoalDataDataWriter(System::IntPtr impl);
};

// ---------------------------------------------------------------------------
// TeamBallPossessionTypeSupport
// ---------------------------------------------------------------------------

ref class TeamBallPossessionPlugin;

/* A collection of useful methods for dealing with objects of type
 * TeamBallPossession.
 */
public ref class TeamBallPossessionTypeSupport
        : public DDS::TypedTypeSupport<TeamBallPossession^> {
    // --- Type name: --------------------------------------------------------
  public:
    static System::String^ TYPENAME = "TeamBallPossession";


    // --- Public Methods: ---------------------------------------------------
  public:
    /* Get the default name of this type.
     *
     * An application can choose to register a type under any name, so
     * calling this method is strictly optional.
     */
    static System::String^ get_type_name();

    /* Register this type with the given participant under the given logical
     * name. This type must be registered before a Topic can be created that
     * uses it.
     */
    static void register_type(
            DDS::DomainParticipant^ participant,
            System::String^ type_name);

    /* Unregister this type from the given participant, where it was
     * previously registered under the given name. No further Topic creation
     * using this type will be possible.
     *
     * Unregistration allows some middleware resources to be reclaimed.
     */
    static void unregister_type(
            DDS::DomainParticipant^ participant,
            System::String^ type_name);

    /* Create an instance of the TeamBallPossession type.
     */
    static TeamBallPossession^ create_data();

    /* If instances of the TeamBallPossession type require any
     * explicit finalization, perform it now on the given sample.
     */
    static void delete_data(TeamBallPossession^ data);

    /* Write the contents of the data sample to standard out.
     */
    static void print_data(TeamBallPossession^ a_data);

    /* Perform a deep copy of the contents of one data sample over those of
     * another, overwriting it.
     */
    static void copy_data(
        TeamBallPossession^ dst_data,
        TeamBallPossession^ src_data);


    // --- Implementation: ---------------------------------------------------
    /* The following code is for the use of the middleware infrastructure.
     * Applications are not expected to call it directly.
     */
public:
    virtual DDS::DataReader^ create_datareaderI(
        System::IntPtr impl) override;
    virtual DDS::DataWriter^ create_datawriterI(
        System::IntPtr impl) override;
        
    virtual TeamBallPossession^ create_data_untyped() override;
    
    virtual System::String^ get_type_name_untyped() override;
        

public:
    static TeamBallPossessionTypeSupport^ get_instance();

    TeamBallPossessionTypeSupport();

private:
    static TeamBallPossessionTypeSupport^ _singleton;
    TeamBallPossessionPlugin^ _type_plugin;
};


// ---------------------------------------------------------------------------
// TeamBallPossessionDataReader
// ---------------------------------------------------------------------------

/**
 * A reader for the TeamBallPossession type.
 */
public ref class TeamBallPossessionDataReader :
        public DDS::TypedDataReader<TeamBallPossession^> {
    /* The following code is for the use of the middleware infrastructure.
     * Applications are not expected to call it directly.
     */
  internal:
    TeamBallPossessionDataReader(System::IntPtr impl);
};


// ---------------------------------------------------------------------------
// TeamBallPossessionDataWriter
// ---------------------------------------------------------------------------

/**
 * A writer for the TeamBallPossession user type.
 */
public ref class TeamBallPossessionDataWriter :
        public DDS::TypedDataWriter<TeamBallPossession^> {
    /* The following code is for the use of the middleware infrastructure.
     * Applications are not expected to call it directly.
     */
  internal:
    TeamBallPossessionDataWriter(System::IntPtr impl);
};
