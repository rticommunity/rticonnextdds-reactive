/*
  WARNING: THIS FILE IS AUTO-GENERATED. DO NOT MODIFY.

  This file was generated from ShapeType.idl using "rtiddsgen".
  The rtiddsgen tool is part of the RTI Connext distribution.
  For more information, type 'rtiddsgen -help' at a command shell
  or consult the RTI Connext manual.
*/

#pragma once

#include "ShapeType.h"


class DDSDataWriter;
class DDSDataReader;
    
// ---------------------------------------------------------------------------
// ShapeTypeTypeSupport
// ---------------------------------------------------------------------------

ref class ShapeTypePlugin;

/* A collection of useful methods for dealing with objects of type
 * ShapeType.
 */
public ref class ShapeTypeTypeSupport
        : public DDS::TypedTypeSupport<ShapeType^> {
    // --- Type name: --------------------------------------------------------
  public:
    static System::String^ TYPENAME = "ShapeType";


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

    /* Create an instance of the ShapeType type.
     */
    static ShapeType^ create_data();

    /* If instances of the ShapeType type require any
     * explicit finalization, perform it now on the given sample.
     */
    static void delete_data(ShapeType^ data);

    /* Write the contents of the data sample to standard out.
     */
    static void print_data(ShapeType^ a_data);

    /* Perform a deep copy of the contents of one data sample over those of
     * another, overwriting it.
     */
    static void copy_data(
        ShapeType^ dst_data,
        ShapeType^ src_data);


    // --- Implementation: ---------------------------------------------------
    /* The following code is for the use of the middleware infrastructure.
     * Applications are not expected to call it directly.
     */
public:
    virtual DDS::DataReader^ create_datareaderI(
        System::IntPtr impl) override;
    virtual DDS::DataWriter^ create_datawriterI(
        System::IntPtr impl) override;
        
    virtual ShapeType^ create_data_untyped() override;
    
    virtual System::String^ get_type_name_untyped() override;
        

public:
    static ShapeTypeTypeSupport^ get_instance();

    ShapeTypeTypeSupport();

private:
    static ShapeTypeTypeSupport^ _singleton;
    ShapeTypePlugin^ _type_plugin;
};


// ---------------------------------------------------------------------------
// ShapeTypeDataReader
// ---------------------------------------------------------------------------

/**
 * A reader for the ShapeType type.
 */
public ref class ShapeTypeDataReader :
        public DDS::TypedDataReader<ShapeType^> {
    /* The following code is for the use of the middleware infrastructure.
     * Applications are not expected to call it directly.
     */
  internal:
    ShapeTypeDataReader(System::IntPtr impl);
};


// ---------------------------------------------------------------------------
// ShapeTypeDataWriter
// ---------------------------------------------------------------------------

/**
 * A writer for the ShapeType user type.
 */
public ref class ShapeTypeDataWriter :
        public DDS::TypedDataWriter<ShapeType^> {
    /* The following code is for the use of the middleware infrastructure.
     * Applications are not expected to call it directly.
     */
  internal:
    ShapeTypeDataWriter(System::IntPtr impl);
};

// ---------------------------------------------------------------------------
// ShapeTypeExtendedTypeSupport
// ---------------------------------------------------------------------------

ref class ShapeTypeExtendedPlugin;

/* A collection of useful methods for dealing with objects of type
 * ShapeTypeExtended.
 */
public ref class ShapeTypeExtendedTypeSupport
        : public DDS::TypedTypeSupport<ShapeTypeExtended^> {
    // --- Type name: --------------------------------------------------------
  public:
    static System::String^ TYPENAME = "ShapeTypeExtended";


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

    /* Create an instance of the ShapeTypeExtended type.
     */
    static ShapeTypeExtended^ create_data();

    /* If instances of the ShapeTypeExtended type require any
     * explicit finalization, perform it now on the given sample.
     */
    static void delete_data(ShapeTypeExtended^ data);

    /* Write the contents of the data sample to standard out.
     */
    static void print_data(ShapeTypeExtended^ a_data);

    /* Perform a deep copy of the contents of one data sample over those of
     * another, overwriting it.
     */
    static void copy_data(
        ShapeTypeExtended^ dst_data,
        ShapeTypeExtended^ src_data);


    // --- Implementation: ---------------------------------------------------
    /* The following code is for the use of the middleware infrastructure.
     * Applications are not expected to call it directly.
     */
public:
    virtual DDS::DataReader^ create_datareaderI(
        System::IntPtr impl) override;
    virtual DDS::DataWriter^ create_datawriterI(
        System::IntPtr impl) override;
        
    virtual ShapeTypeExtended^ create_data_untyped() override;
    
    virtual System::String^ get_type_name_untyped() override;
        

public:
    static ShapeTypeExtendedTypeSupport^ get_instance();

    ShapeTypeExtendedTypeSupport();

private:
    static ShapeTypeExtendedTypeSupport^ _singleton;
    ShapeTypeExtendedPlugin^ _type_plugin;
};


// ---------------------------------------------------------------------------
// ShapeTypeExtendedDataReader
// ---------------------------------------------------------------------------

/**
 * A reader for the ShapeTypeExtended type.
 */
public ref class ShapeTypeExtendedDataReader :
        public DDS::TypedDataReader<ShapeTypeExtended^> {
    /* The following code is for the use of the middleware infrastructure.
     * Applications are not expected to call it directly.
     */
  internal:
    ShapeTypeExtendedDataReader(System::IntPtr impl);
};


// ---------------------------------------------------------------------------
// ShapeTypeExtendedDataWriter
// ---------------------------------------------------------------------------

/**
 * A writer for the ShapeTypeExtended user type.
 */
public ref class ShapeTypeExtendedDataWriter :
        public DDS::TypedDataWriter<ShapeTypeExtended^> {
    /* The following code is for the use of the middleware infrastructure.
     * Applications are not expected to call it directly.
     */
  internal:
    ShapeTypeExtendedDataWriter(System::IntPtr impl);
};
