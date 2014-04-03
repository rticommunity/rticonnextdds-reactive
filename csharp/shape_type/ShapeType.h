/*
  WARNING: THIS FILE IS AUTO-GENERATED. DO NOT MODIFY.

  This file was generated from ShapeType.idl using "rtiddsgen".
  The rtiddsgen tool is part of the RTI Connext distribution.
  For more information, type 'rtiddsgen -help' at a command shell
  or consult the RTI Connext manual.
*/

#pragma once


struct DDS_TypeCode;
    

using namespace System;
using namespace DDS;

    

public enum class ShapeFillKind : System::Int32 {
    
    SOLID_FILL, 
    TRANSPARENT_FILL, 
    HORIZONTAL_HATCH_FILL, 
    VERTICAL_HATCH_FILL
};

ShapeFillKind ShapeFillKind_get_default_value();

public ref class ShapeFillKindSeq
        : public DDS::UserValueSequence<ShapeFillKind> {
public:
    ShapeFillKindSeq() :
            DDS::UserValueSequence<ShapeFillKind>() {
        // empty
    }
    ShapeFillKindSeq(System::Int32 max) :
            DDS::UserValueSequence<ShapeFillKind>(max) {
        // empty
    }
    ShapeFillKindSeq(ShapeFillKindSeq^ src) :
            DDS::UserValueSequence<ShapeFillKind>(src) {
        // empty
    }
};


  #define NDDSUSERDllExport
NDDSUSERDllExport DDS_TypeCode* ShapeFillKind_get_typecode();


public ref struct ShapeType
        : public DDS::ICopyable<ShapeType^> {
    // --- Declared members: -------------------------------------------------
  public:            
    
    System::String^ color; // maximum length = (128)
    System::Int32 x;
    System::Int32 y;
    System::Int32 shapesize;

    // --- Static constants: -------------------------------------    
public:
    


#define ShapeType_LAST_MEMBER_ID 3

    // --- Constructors and destructors: -------------------------------------
  public:
    ShapeType();

  // --- Utility methods: --------------------------------------------------
  public:
  virtual void clear();

  virtual System::Boolean copy_from(ShapeType^ src);

    virtual System::Boolean Equals(System::Object^ other) override;

    
    static DDS::TypeCode^ get_typecode();

  private:
    static DDS::TypeCode^ _typecode;

}; // class ShapeType




public ref class ShapeTypeSeq sealed
        : public DDS::UserRefSequence<ShapeType^> {
public:
    ShapeTypeSeq() :
            DDS::UserRefSequence<ShapeType^>() {
        // empty
    }
    ShapeTypeSeq(System::Int32 max) :
            DDS::UserRefSequence<ShapeType^>(max) {
        // empty
    }
    ShapeTypeSeq(ShapeTypeSeq^ src) :
            DDS::UserRefSequence<ShapeType^>(src) {
        // empty
    }
};


  #define NDDSUSERDllExport

NDDSUSERDllExport DDS_TypeCode* ShapeType_get_typecode();


public ref struct ShapeTypeExtended
        :  public ShapeType, public DDS::ICopyable<ShapeTypeExtended^> {
    // --- Declared members: -------------------------------------------------
  public:            
    
    ShapeFillKind fillKind;
    System::Single angle;

    // --- Static constants: -------------------------------------    
public:
    


#define ShapeTypeExtended_LAST_MEMBER_ID (ShapeType_LAST_MEMBER_ID + 2)

    // --- Constructors and destructors: -------------------------------------
  public:
    ShapeTypeExtended();

  // --- Utility methods: --------------------------------------------------
  public:
  virtual void clear() override;

  virtual System::Boolean copy_from(ShapeTypeExtended^ src);

    virtual System::Boolean Equals(System::Object^ other) override;

    
    static DDS::TypeCode^ get_typecode();

  private:
    static DDS::TypeCode^ _typecode;

}; // class ShapeTypeExtended




public ref class ShapeTypeExtendedSeq sealed
        : public DDS::UserRefSequence<ShapeTypeExtended^> {
public:
    ShapeTypeExtendedSeq() :
            DDS::UserRefSequence<ShapeTypeExtended^>() {
        // empty
    }
    ShapeTypeExtendedSeq(System::Int32 max) :
            DDS::UserRefSequence<ShapeTypeExtended^>(max) {
        // empty
    }
    ShapeTypeExtendedSeq(ShapeTypeExtendedSeq^ src) :
            DDS::UserRefSequence<ShapeTypeExtended^>(src) {
        // empty
    }
};


  #define NDDSUSERDllExport

NDDSUSERDllExport DDS_TypeCode* ShapeTypeExtended_get_typecode();
