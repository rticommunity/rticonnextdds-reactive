/*
  WARNING: THIS FILE IS AUTO-GENERATED. DO NOT MODIFY.

  This file was generated from ShapeType.idl using "rtiddsgen".
  The rtiddsgen tool is part of the RTI Connext distribution.
  For more information, type 'rtiddsgen -help' at a command shell
  or consult the RTI Connext manual.
*/

#include "ShapeTypeSupport.h"
#include "ShapeTypePlugin.h"


using namespace System;
using namespace DDS;
    
/* ========================================================================= */

// ---------------------------------------------------------------------------
// ShapeTypeDataWriter
// ---------------------------------------------------------------------------

ShapeTypeDataWriter::ShapeTypeDataWriter(
        System::IntPtr impl) : DDS::TypedDataWriter<ShapeType^>(impl) {
    // empty
}


// ---------------------------------------------------------------------------
// ShapeTypeDataReader
// ---------------------------------------------------------------------------

ShapeTypeDataReader::ShapeTypeDataReader(
        System::IntPtr impl) : DDS::TypedDataReader<ShapeType^>(impl) {
    // empty
}


// ---------------------------------------------------------------------------
// ShapeTypeTypeSupport
// ---------------------------------------------------------------------------

ShapeTypeTypeSupport::ShapeTypeTypeSupport()
        : DDS::TypedTypeSupport<ShapeType^>(
            ShapeTypePlugin::get_instance()) {

    _type_plugin = ShapeTypePlugin::get_instance();
}

void ShapeTypeTypeSupport::register_type(
        DDS::DomainParticipant^ participant,
        System::String^ type_name) {

    get_instance()->register_type_untyped(participant, type_name);
}

void ShapeTypeTypeSupport::unregister_type(
        DDS::DomainParticipant^ participant,
        System::String^ type_name) {

    get_instance()->unregister_type_untyped(participant, type_name);
}

ShapeType^ ShapeTypeTypeSupport::create_data() {
    return gcnew ShapeType();
}

ShapeType^ ShapeTypeTypeSupport::create_data_untyped() {
    return create_data();
}

void ShapeTypeTypeSupport::delete_data(
        ShapeType^ a_data) {
    /* If the generated type does not implement IDisposable (the default),
     * the following will no a no-op.
     */
    delete a_data;
}

void ShapeTypeTypeSupport::print_data(ShapeType^ a_data) {
     get_instance()->_type_plugin->print_data(a_data, nullptr, 0);
}

void ShapeTypeTypeSupport::copy_data(
        ShapeType^ dst, ShapeType^ src) {

    get_instance()->copy_data_untyped(dst, src);
}

System::String^ ShapeTypeTypeSupport::get_type_name() {
    return TYPENAME;
}

System::String^ ShapeTypeTypeSupport::get_type_name_untyped() {
    return TYPENAME;
}

DDS::DataReader^ ShapeTypeTypeSupport::create_datareaderI(
        System::IntPtr impl) {

    return gcnew ShapeTypeDataReader(impl);
}

DDS::DataWriter^ ShapeTypeTypeSupport::create_datawriterI(
        System::IntPtr impl) {

    return gcnew ShapeTypeDataWriter(impl);
}

ShapeTypeTypeSupport^
ShapeTypeTypeSupport::get_instance() {
    if (_singleton == nullptr) {
        _singleton = gcnew ShapeTypeTypeSupport();
    }
    return _singleton;
}
    
/* ========================================================================= */

// ---------------------------------------------------------------------------
// ShapeTypeExtendedDataWriter
// ---------------------------------------------------------------------------

ShapeTypeExtendedDataWriter::ShapeTypeExtendedDataWriter(
        System::IntPtr impl) : DDS::TypedDataWriter<ShapeTypeExtended^>(impl) {
    // empty
}


// ---------------------------------------------------------------------------
// ShapeTypeExtendedDataReader
// ---------------------------------------------------------------------------

ShapeTypeExtendedDataReader::ShapeTypeExtendedDataReader(
        System::IntPtr impl) : DDS::TypedDataReader<ShapeTypeExtended^>(impl) {
    // empty
}


// ---------------------------------------------------------------------------
// ShapeTypeExtendedTypeSupport
// ---------------------------------------------------------------------------

ShapeTypeExtendedTypeSupport::ShapeTypeExtendedTypeSupport()
        : DDS::TypedTypeSupport<ShapeTypeExtended^>(
            ShapeTypeExtendedPlugin::get_instance()) {

    _type_plugin = ShapeTypeExtendedPlugin::get_instance();
}

void ShapeTypeExtendedTypeSupport::register_type(
        DDS::DomainParticipant^ participant,
        System::String^ type_name) {

    get_instance()->register_type_untyped(participant, type_name);
}

void ShapeTypeExtendedTypeSupport::unregister_type(
        DDS::DomainParticipant^ participant,
        System::String^ type_name) {

    get_instance()->unregister_type_untyped(participant, type_name);
}

ShapeTypeExtended^ ShapeTypeExtendedTypeSupport::create_data() {
    return gcnew ShapeTypeExtended();
}

ShapeTypeExtended^ ShapeTypeExtendedTypeSupport::create_data_untyped() {
    return create_data();
}

void ShapeTypeExtendedTypeSupport::delete_data(
        ShapeTypeExtended^ a_data) {
    /* If the generated type does not implement IDisposable (the default),
     * the following will no a no-op.
     */
    delete a_data;
}

void ShapeTypeExtendedTypeSupport::print_data(ShapeTypeExtended^ a_data) {
     get_instance()->_type_plugin->print_data(a_data, nullptr, 0);
}

void ShapeTypeExtendedTypeSupport::copy_data(
        ShapeTypeExtended^ dst, ShapeTypeExtended^ src) {

    get_instance()->copy_data_untyped(dst, src);
}

System::String^ ShapeTypeExtendedTypeSupport::get_type_name() {
    return TYPENAME;
}

System::String^ ShapeTypeExtendedTypeSupport::get_type_name_untyped() {
    return TYPENAME;
}

DDS::DataReader^ ShapeTypeExtendedTypeSupport::create_datareaderI(
        System::IntPtr impl) {

    return gcnew ShapeTypeExtendedDataReader(impl);
}

DDS::DataWriter^ ShapeTypeExtendedTypeSupport::create_datawriterI(
        System::IntPtr impl) {

    return gcnew ShapeTypeExtendedDataWriter(impl);
}

ShapeTypeExtendedTypeSupport^
ShapeTypeExtendedTypeSupport::get_instance() {
    if (_singleton == nullptr) {
        _singleton = gcnew ShapeTypeExtendedTypeSupport();
    }
    return _singleton;
}
    