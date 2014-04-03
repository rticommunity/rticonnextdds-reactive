/*
  WARNING: THIS FILE IS AUTO-GENERATED. DO NOT MODIFY.

  This file was generated from soccer.idl using "rtiddsgen".
  The rtiddsgen tool is part of the RTI Connext distribution.
  For more information, type 'rtiddsgen -help' at a command shell
  or consult the RTI Connext manual.
*/

#include "soccerSupport.h"
#include "soccerPlugin.h"


using namespace System;
using namespace DDS;
    
/* ========================================================================= */

// ---------------------------------------------------------------------------
// AggregateRunningDataDataWriter
// ---------------------------------------------------------------------------

AggregateRunningDataDataWriter::AggregateRunningDataDataWriter(
        System::IntPtr impl) : DDS::TypedDataWriter<AggregateRunningData^>(impl) {
    // empty
}


// ---------------------------------------------------------------------------
// AggregateRunningDataDataReader
// ---------------------------------------------------------------------------

AggregateRunningDataDataReader::AggregateRunningDataDataReader(
        System::IntPtr impl) : DDS::TypedDataReader<AggregateRunningData^>(impl) {
    // empty
}


// ---------------------------------------------------------------------------
// AggregateRunningDataTypeSupport
// ---------------------------------------------------------------------------

AggregateRunningDataTypeSupport::AggregateRunningDataTypeSupport()
        : DDS::TypedTypeSupport<AggregateRunningData^>(
            AggregateRunningDataPlugin::get_instance()) {

    _type_plugin = AggregateRunningDataPlugin::get_instance();
}

void AggregateRunningDataTypeSupport::register_type(
        DDS::DomainParticipant^ participant,
        System::String^ type_name) {

    get_instance()->register_type_untyped(participant, type_name);
}

void AggregateRunningDataTypeSupport::unregister_type(
        DDS::DomainParticipant^ participant,
        System::String^ type_name) {

    get_instance()->unregister_type_untyped(participant, type_name);
}

AggregateRunningData^ AggregateRunningDataTypeSupport::create_data() {
    return gcnew AggregateRunningData();
}

AggregateRunningData^ AggregateRunningDataTypeSupport::create_data_untyped() {
    return create_data();
}

void AggregateRunningDataTypeSupport::delete_data(
        AggregateRunningData^ a_data) {
    /* If the generated type does not implement IDisposable (the default),
     * the following will no a no-op.
     */
    delete a_data;
}

void AggregateRunningDataTypeSupport::print_data(AggregateRunningData^ a_data) {
     get_instance()->_type_plugin->print_data(a_data, nullptr, 0);
}

void AggregateRunningDataTypeSupport::copy_data(
        AggregateRunningData^ dst, AggregateRunningData^ src) {

    get_instance()->copy_data_untyped(dst, src);
}

System::String^ AggregateRunningDataTypeSupport::get_type_name() {
    return TYPENAME;
}

System::String^ AggregateRunningDataTypeSupport::get_type_name_untyped() {
    return TYPENAME;
}

DDS::DataReader^ AggregateRunningDataTypeSupport::create_datareaderI(
        System::IntPtr impl) {

    return gcnew AggregateRunningDataDataReader(impl);
}

DDS::DataWriter^ AggregateRunningDataTypeSupport::create_datawriterI(
        System::IntPtr impl) {

    return gcnew AggregateRunningDataDataWriter(impl);
}

AggregateRunningDataTypeSupport^
AggregateRunningDataTypeSupport::get_instance() {
    if (_singleton == nullptr) {
        _singleton = gcnew AggregateRunningDataTypeSupport();
    }
    return _singleton;
}
    
/* ========================================================================= */

// ---------------------------------------------------------------------------
// CurrentRunningDataDataWriter
// ---------------------------------------------------------------------------

CurrentRunningDataDataWriter::CurrentRunningDataDataWriter(
        System::IntPtr impl) : DDS::TypedDataWriter<CurrentRunningData^>(impl) {
    // empty
}


// ---------------------------------------------------------------------------
// CurrentRunningDataDataReader
// ---------------------------------------------------------------------------

CurrentRunningDataDataReader::CurrentRunningDataDataReader(
        System::IntPtr impl) : DDS::TypedDataReader<CurrentRunningData^>(impl) {
    // empty
}


// ---------------------------------------------------------------------------
// CurrentRunningDataTypeSupport
// ---------------------------------------------------------------------------

CurrentRunningDataTypeSupport::CurrentRunningDataTypeSupport()
        : DDS::TypedTypeSupport<CurrentRunningData^>(
            CurrentRunningDataPlugin::get_instance()) {

    _type_plugin = CurrentRunningDataPlugin::get_instance();
}

void CurrentRunningDataTypeSupport::register_type(
        DDS::DomainParticipant^ participant,
        System::String^ type_name) {

    get_instance()->register_type_untyped(participant, type_name);
}

void CurrentRunningDataTypeSupport::unregister_type(
        DDS::DomainParticipant^ participant,
        System::String^ type_name) {

    get_instance()->unregister_type_untyped(participant, type_name);
}

CurrentRunningData^ CurrentRunningDataTypeSupport::create_data() {
    return gcnew CurrentRunningData();
}

CurrentRunningData^ CurrentRunningDataTypeSupport::create_data_untyped() {
    return create_data();
}

void CurrentRunningDataTypeSupport::delete_data(
        CurrentRunningData^ a_data) {
    /* If the generated type does not implement IDisposable (the default),
     * the following will no a no-op.
     */
    delete a_data;
}

void CurrentRunningDataTypeSupport::print_data(CurrentRunningData^ a_data) {
     get_instance()->_type_plugin->print_data(a_data, nullptr, 0);
}

void CurrentRunningDataTypeSupport::copy_data(
        CurrentRunningData^ dst, CurrentRunningData^ src) {

    get_instance()->copy_data_untyped(dst, src);
}

System::String^ CurrentRunningDataTypeSupport::get_type_name() {
    return TYPENAME;
}

System::String^ CurrentRunningDataTypeSupport::get_type_name_untyped() {
    return TYPENAME;
}

DDS::DataReader^ CurrentRunningDataTypeSupport::create_datareaderI(
        System::IntPtr impl) {

    return gcnew CurrentRunningDataDataReader(impl);
}

DDS::DataWriter^ CurrentRunningDataTypeSupport::create_datawriterI(
        System::IntPtr impl) {

    return gcnew CurrentRunningDataDataWriter(impl);
}

CurrentRunningDataTypeSupport^
CurrentRunningDataTypeSupport::get_instance() {
    if (_singleton == nullptr) {
        _singleton = gcnew CurrentRunningDataTypeSupport();
    }
    return _singleton;
}
    
/* ========================================================================= */

// ---------------------------------------------------------------------------
// PlayerBallPossessionDataWriter
// ---------------------------------------------------------------------------

PlayerBallPossessionDataWriter::PlayerBallPossessionDataWriter(
        System::IntPtr impl) : DDS::TypedDataWriter<PlayerBallPossession^>(impl) {
    // empty
}


// ---------------------------------------------------------------------------
// PlayerBallPossessionDataReader
// ---------------------------------------------------------------------------

PlayerBallPossessionDataReader::PlayerBallPossessionDataReader(
        System::IntPtr impl) : DDS::TypedDataReader<PlayerBallPossession^>(impl) {
    // empty
}


// ---------------------------------------------------------------------------
// PlayerBallPossessionTypeSupport
// ---------------------------------------------------------------------------

PlayerBallPossessionTypeSupport::PlayerBallPossessionTypeSupport()
        : DDS::TypedTypeSupport<PlayerBallPossession^>(
            PlayerBallPossessionPlugin::get_instance()) {

    _type_plugin = PlayerBallPossessionPlugin::get_instance();
}

void PlayerBallPossessionTypeSupport::register_type(
        DDS::DomainParticipant^ participant,
        System::String^ type_name) {

    get_instance()->register_type_untyped(participant, type_name);
}

void PlayerBallPossessionTypeSupport::unregister_type(
        DDS::DomainParticipant^ participant,
        System::String^ type_name) {

    get_instance()->unregister_type_untyped(participant, type_name);
}

PlayerBallPossession^ PlayerBallPossessionTypeSupport::create_data() {
    return gcnew PlayerBallPossession();
}

PlayerBallPossession^ PlayerBallPossessionTypeSupport::create_data_untyped() {
    return create_data();
}

void PlayerBallPossessionTypeSupport::delete_data(
        PlayerBallPossession^ a_data) {
    /* If the generated type does not implement IDisposable (the default),
     * the following will no a no-op.
     */
    delete a_data;
}

void PlayerBallPossessionTypeSupport::print_data(PlayerBallPossession^ a_data) {
     get_instance()->_type_plugin->print_data(a_data, nullptr, 0);
}

void PlayerBallPossessionTypeSupport::copy_data(
        PlayerBallPossession^ dst, PlayerBallPossession^ src) {

    get_instance()->copy_data_untyped(dst, src);
}

System::String^ PlayerBallPossessionTypeSupport::get_type_name() {
    return TYPENAME;
}

System::String^ PlayerBallPossessionTypeSupport::get_type_name_untyped() {
    return TYPENAME;
}

DDS::DataReader^ PlayerBallPossessionTypeSupport::create_datareaderI(
        System::IntPtr impl) {

    return gcnew PlayerBallPossessionDataReader(impl);
}

DDS::DataWriter^ PlayerBallPossessionTypeSupport::create_datawriterI(
        System::IntPtr impl) {

    return gcnew PlayerBallPossessionDataWriter(impl);
}

PlayerBallPossessionTypeSupport^
PlayerBallPossessionTypeSupport::get_instance() {
    if (_singleton == nullptr) {
        _singleton = gcnew PlayerBallPossessionTypeSupport();
    }
    return _singleton;
}
    
/* ========================================================================= */

// ---------------------------------------------------------------------------
// PlayerDataDataWriter
// ---------------------------------------------------------------------------

PlayerDataDataWriter::PlayerDataDataWriter(
        System::IntPtr impl) : DDS::TypedDataWriter<PlayerData^>(impl) {
    // empty
}


// ---------------------------------------------------------------------------
// PlayerDataDataReader
// ---------------------------------------------------------------------------

PlayerDataDataReader::PlayerDataDataReader(
        System::IntPtr impl) : DDS::TypedDataReader<PlayerData^>(impl) {
    // empty
}


// ---------------------------------------------------------------------------
// PlayerDataTypeSupport
// ---------------------------------------------------------------------------

PlayerDataTypeSupport::PlayerDataTypeSupport()
        : DDS::TypedTypeSupport<PlayerData^>(
            PlayerDataPlugin::get_instance()) {

    _type_plugin = PlayerDataPlugin::get_instance();
}

void PlayerDataTypeSupport::register_type(
        DDS::DomainParticipant^ participant,
        System::String^ type_name) {

    get_instance()->register_type_untyped(participant, type_name);
}

void PlayerDataTypeSupport::unregister_type(
        DDS::DomainParticipant^ participant,
        System::String^ type_name) {

    get_instance()->unregister_type_untyped(participant, type_name);
}

PlayerData^ PlayerDataTypeSupport::create_data() {
    return gcnew PlayerData();
}

PlayerData^ PlayerDataTypeSupport::create_data_untyped() {
    return create_data();
}

void PlayerDataTypeSupport::delete_data(
        PlayerData^ a_data) {
    /* If the generated type does not implement IDisposable (the default),
     * the following will no a no-op.
     */
    delete a_data;
}

void PlayerDataTypeSupport::print_data(PlayerData^ a_data) {
     get_instance()->_type_plugin->print_data(a_data, nullptr, 0);
}

void PlayerDataTypeSupport::copy_data(
        PlayerData^ dst, PlayerData^ src) {

    get_instance()->copy_data_untyped(dst, src);
}

System::String^ PlayerDataTypeSupport::get_type_name() {
    return TYPENAME;
}

System::String^ PlayerDataTypeSupport::get_type_name_untyped() {
    return TYPENAME;
}

DDS::DataReader^ PlayerDataTypeSupport::create_datareaderI(
        System::IntPtr impl) {

    return gcnew PlayerDataDataReader(impl);
}

DDS::DataWriter^ PlayerDataTypeSupport::create_datawriterI(
        System::IntPtr impl) {

    return gcnew PlayerDataDataWriter(impl);
}

PlayerDataTypeSupport^
PlayerDataTypeSupport::get_instance() {
    if (_singleton == nullptr) {
        _singleton = gcnew PlayerDataTypeSupport();
    }
    return _singleton;
}
    
/* ========================================================================= */

// ---------------------------------------------------------------------------
// SensorDataDataWriter
// ---------------------------------------------------------------------------

SensorDataDataWriter::SensorDataDataWriter(
        System::IntPtr impl) : DDS::TypedDataWriter<SensorData^>(impl) {
    // empty
}


// ---------------------------------------------------------------------------
// SensorDataDataReader
// ---------------------------------------------------------------------------

SensorDataDataReader::SensorDataDataReader(
        System::IntPtr impl) : DDS::TypedDataReader<SensorData^>(impl) {
    // empty
}


// ---------------------------------------------------------------------------
// SensorDataTypeSupport
// ---------------------------------------------------------------------------

SensorDataTypeSupport::SensorDataTypeSupport()
        : DDS::TypedTypeSupport<SensorData^>(
            SensorDataPlugin::get_instance()) {

    _type_plugin = SensorDataPlugin::get_instance();
}

void SensorDataTypeSupport::register_type(
        DDS::DomainParticipant^ participant,
        System::String^ type_name) {

    get_instance()->register_type_untyped(participant, type_name);
}

void SensorDataTypeSupport::unregister_type(
        DDS::DomainParticipant^ participant,
        System::String^ type_name) {

    get_instance()->unregister_type_untyped(participant, type_name);
}

SensorData^ SensorDataTypeSupport::create_data() {
    return gcnew SensorData();
}

SensorData^ SensorDataTypeSupport::create_data_untyped() {
    return create_data();
}

void SensorDataTypeSupport::delete_data(
        SensorData^ a_data) {
    /* If the generated type does not implement IDisposable (the default),
     * the following will no a no-op.
     */
    delete a_data;
}

void SensorDataTypeSupport::print_data(SensorData^ a_data) {
     get_instance()->_type_plugin->print_data(a_data, nullptr, 0);
}

void SensorDataTypeSupport::copy_data(
        SensorData^ dst, SensorData^ src) {

    get_instance()->copy_data_untyped(dst, src);
}

System::String^ SensorDataTypeSupport::get_type_name() {
    return TYPENAME;
}

System::String^ SensorDataTypeSupport::get_type_name_untyped() {
    return TYPENAME;
}

DDS::DataReader^ SensorDataTypeSupport::create_datareaderI(
        System::IntPtr impl) {

    return gcnew SensorDataDataReader(impl);
}

DDS::DataWriter^ SensorDataTypeSupport::create_datawriterI(
        System::IntPtr impl) {

    return gcnew SensorDataDataWriter(impl);
}

SensorDataTypeSupport^
SensorDataTypeSupport::get_instance() {
    if (_singleton == nullptr) {
        _singleton = gcnew SensorDataTypeSupport();
    }
    return _singleton;
}
    
/* ========================================================================= */

// ---------------------------------------------------------------------------
// ShotOnGoalDataDataWriter
// ---------------------------------------------------------------------------

ShotOnGoalDataDataWriter::ShotOnGoalDataDataWriter(
        System::IntPtr impl) : DDS::TypedDataWriter<ShotOnGoalData^>(impl) {
    // empty
}


// ---------------------------------------------------------------------------
// ShotOnGoalDataDataReader
// ---------------------------------------------------------------------------

ShotOnGoalDataDataReader::ShotOnGoalDataDataReader(
        System::IntPtr impl) : DDS::TypedDataReader<ShotOnGoalData^>(impl) {
    // empty
}


// ---------------------------------------------------------------------------
// ShotOnGoalDataTypeSupport
// ---------------------------------------------------------------------------

ShotOnGoalDataTypeSupport::ShotOnGoalDataTypeSupport()
        : DDS::TypedTypeSupport<ShotOnGoalData^>(
            ShotOnGoalDataPlugin::get_instance()) {

    _type_plugin = ShotOnGoalDataPlugin::get_instance();
}

void ShotOnGoalDataTypeSupport::register_type(
        DDS::DomainParticipant^ participant,
        System::String^ type_name) {

    get_instance()->register_type_untyped(participant, type_name);
}

void ShotOnGoalDataTypeSupport::unregister_type(
        DDS::DomainParticipant^ participant,
        System::String^ type_name) {

    get_instance()->unregister_type_untyped(participant, type_name);
}

ShotOnGoalData^ ShotOnGoalDataTypeSupport::create_data() {
    return gcnew ShotOnGoalData();
}

ShotOnGoalData^ ShotOnGoalDataTypeSupport::create_data_untyped() {
    return create_data();
}

void ShotOnGoalDataTypeSupport::delete_data(
        ShotOnGoalData^ a_data) {
    /* If the generated type does not implement IDisposable (the default),
     * the following will no a no-op.
     */
    delete a_data;
}

void ShotOnGoalDataTypeSupport::print_data(ShotOnGoalData^ a_data) {
     get_instance()->_type_plugin->print_data(a_data, nullptr, 0);
}

void ShotOnGoalDataTypeSupport::copy_data(
        ShotOnGoalData^ dst, ShotOnGoalData^ src) {

    get_instance()->copy_data_untyped(dst, src);
}

System::String^ ShotOnGoalDataTypeSupport::get_type_name() {
    return TYPENAME;
}

System::String^ ShotOnGoalDataTypeSupport::get_type_name_untyped() {
    return TYPENAME;
}

DDS::DataReader^ ShotOnGoalDataTypeSupport::create_datareaderI(
        System::IntPtr impl) {

    return gcnew ShotOnGoalDataDataReader(impl);
}

DDS::DataWriter^ ShotOnGoalDataTypeSupport::create_datawriterI(
        System::IntPtr impl) {

    return gcnew ShotOnGoalDataDataWriter(impl);
}

ShotOnGoalDataTypeSupport^
ShotOnGoalDataTypeSupport::get_instance() {
    if (_singleton == nullptr) {
        _singleton = gcnew ShotOnGoalDataTypeSupport();
    }
    return _singleton;
}
    
/* ========================================================================= */

// ---------------------------------------------------------------------------
// TeamBallPossessionDataWriter
// ---------------------------------------------------------------------------

TeamBallPossessionDataWriter::TeamBallPossessionDataWriter(
        System::IntPtr impl) : DDS::TypedDataWriter<TeamBallPossession^>(impl) {
    // empty
}


// ---------------------------------------------------------------------------
// TeamBallPossessionDataReader
// ---------------------------------------------------------------------------

TeamBallPossessionDataReader::TeamBallPossessionDataReader(
        System::IntPtr impl) : DDS::TypedDataReader<TeamBallPossession^>(impl) {
    // empty
}


// ---------------------------------------------------------------------------
// TeamBallPossessionTypeSupport
// ---------------------------------------------------------------------------

TeamBallPossessionTypeSupport::TeamBallPossessionTypeSupport()
        : DDS::TypedTypeSupport<TeamBallPossession^>(
            TeamBallPossessionPlugin::get_instance()) {

    _type_plugin = TeamBallPossessionPlugin::get_instance();
}

void TeamBallPossessionTypeSupport::register_type(
        DDS::DomainParticipant^ participant,
        System::String^ type_name) {

    get_instance()->register_type_untyped(participant, type_name);
}

void TeamBallPossessionTypeSupport::unregister_type(
        DDS::DomainParticipant^ participant,
        System::String^ type_name) {

    get_instance()->unregister_type_untyped(participant, type_name);
}

TeamBallPossession^ TeamBallPossessionTypeSupport::create_data() {
    return gcnew TeamBallPossession();
}

TeamBallPossession^ TeamBallPossessionTypeSupport::create_data_untyped() {
    return create_data();
}

void TeamBallPossessionTypeSupport::delete_data(
        TeamBallPossession^ a_data) {
    /* If the generated type does not implement IDisposable (the default),
     * the following will no a no-op.
     */
    delete a_data;
}

void TeamBallPossessionTypeSupport::print_data(TeamBallPossession^ a_data) {
     get_instance()->_type_plugin->print_data(a_data, nullptr, 0);
}

void TeamBallPossessionTypeSupport::copy_data(
        TeamBallPossession^ dst, TeamBallPossession^ src) {

    get_instance()->copy_data_untyped(dst, src);
}

System::String^ TeamBallPossessionTypeSupport::get_type_name() {
    return TYPENAME;
}

System::String^ TeamBallPossessionTypeSupport::get_type_name_untyped() {
    return TYPENAME;
}

DDS::DataReader^ TeamBallPossessionTypeSupport::create_datareaderI(
        System::IntPtr impl) {

    return gcnew TeamBallPossessionDataReader(impl);
}

DDS::DataWriter^ TeamBallPossessionTypeSupport::create_datawriterI(
        System::IntPtr impl) {

    return gcnew TeamBallPossessionDataWriter(impl);
}

TeamBallPossessionTypeSupport^
TeamBallPossessionTypeSupport::get_instance() {
    if (_singleton == nullptr) {
        _singleton = gcnew TeamBallPossessionTypeSupport();
    }
    return _singleton;
}
    