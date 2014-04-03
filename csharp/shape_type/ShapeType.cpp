/*
  WARNING: THIS FILE IS AUTO-GENERATED. DO NOT MODIFY.

  This file was generated from ShapeType.idl using "rtiddsgen".
  The rtiddsgen tool is part of the RTI Connext distribution.
  For more information, type 'rtiddsgen -help' at a command shell
  or consult the RTI Connext manual.
*/

    
#pragma unmanaged
#include "ndds/ndds_cpp.h"
#pragma managed

using namespace System;
using namespace System::Collections;
using namespace DDS;
    

#include "ShapeType.h"
    
/* ========================================================================= */

DDS_TypeCode* ShapeFillKind_get_typecode()
{
    static RTIBool is_initialized = RTI_FALSE;

    static DDS_TypeCode_Member ShapeFillKind_g_tc_members[4] =
    {
        {
            (char *)"SOLID_FILL",/* Member name */
            {
                0,/* Ignored */
                DDS_BOOLEAN_FALSE, /* Ignored */
                -1, /* Ignored */
                NULL /* Ignored */
            },
            (RTICdrLong) ShapeFillKind::SOLID_FILL, /* Enumerator ordinal */
            0, /* Ignored */
            0, /* Ignored */
            NULL, /* Ignored */
            RTI_CDR_REQUIRED_MEMBER, /* Ignored */
            DDS_PRIVATE_MEMBER,/* Ignored */
            1,
            NULL/* Ignored */
        },
        {
            (char *)"TRANSPARENT_FILL",/* Member name */
            {
                0,/* Ignored */
                DDS_BOOLEAN_FALSE, /* Ignored */
                -1, /* Ignored */
                NULL /* Ignored */
            },
            (RTICdrLong) ShapeFillKind::TRANSPARENT_FILL, /* Enumerator ordinal */
            0, /* Ignored */
            0, /* Ignored */
            NULL, /* Ignored */
            RTI_CDR_REQUIRED_MEMBER, /* Ignored */
            DDS_PRIVATE_MEMBER,/* Ignored */
            1,
            NULL/* Ignored */
        },
        {
            (char *)"HORIZONTAL_HATCH_FILL",/* Member name */
            {
                0,/* Ignored */
                DDS_BOOLEAN_FALSE, /* Ignored */
                -1, /* Ignored */
                NULL /* Ignored */
            },
            (RTICdrLong) ShapeFillKind::HORIZONTAL_HATCH_FILL, /* Enumerator ordinal */
            0, /* Ignored */
            0, /* Ignored */
            NULL, /* Ignored */
            RTI_CDR_REQUIRED_MEMBER, /* Ignored */
            DDS_PRIVATE_MEMBER,/* Ignored */
            1,
            NULL/* Ignored */
        },
        {
            (char *)"VERTICAL_HATCH_FILL",/* Member name */
            {
                0,/* Ignored */
                DDS_BOOLEAN_FALSE, /* Ignored */
                -1, /* Ignored */
                NULL /* Ignored */
            },
            (RTICdrLong) ShapeFillKind::VERTICAL_HATCH_FILL, /* Enumerator ordinal */
            0, /* Ignored */
            0, /* Ignored */
            NULL, /* Ignored */
            RTI_CDR_REQUIRED_MEMBER, /* Ignored */
            DDS_PRIVATE_MEMBER,/* Ignored */
            1,
            NULL/* Ignored */
        }
    };

    static DDS_TypeCode ShapeFillKind_g_tc = 
    {{
        DDS_TK_ENUM, /* Kind */
        DDS_BOOLEAN_FALSE, /* Ignored */
        -1, /* Ignored */
        (char *)"ShapeFillKind", /* Name */
        NULL, /* Ignored */
        0, /* Ignored */
        0, /* Ignored */
        NULL, /* Ignored */
        4, /* Number of enumerators */
        ShapeFillKind_g_tc_members, /* Enumerators */
        DDS_VM_NONE /* Ignored */
}    };

    if (is_initialized) {
        return &ShapeFillKind_g_tc;
    }

    is_initialized = RTI_TRUE;
    return &ShapeFillKind_g_tc;
}
ShapeFillKind ShapeFillKind_get_default_value() {
    return ShapeFillKind::SOLID_FILL;
}


/* ========================================================================= */
ShapeType::ShapeType() {

    color = "";
            
    x = 0;
            
    y = 0;
            
    shapesize = 0;
            
}

void ShapeType::clear() {
  
    color = "";
          
    x = 0;
          
    y = 0;
          
    shapesize = 0;
          
}

  

System::Boolean ShapeType::copy_from(ShapeType^ src) {
    ShapeType^ dst = this;

    dst->color = src->color;
    dst->x = src->x;
    dst->y = src->y;
    dst->shapesize = src->shapesize;

    return true;
}

Boolean ShapeType::Equals(Object^ other) {
    if (other == nullptr) {
        return false;
    }        
    if (this == other) {
        return true;
    }

    ShapeType^ otherObj =
        dynamic_cast<ShapeType^>(other);
    if (otherObj == nullptr) {
        return false;
    }


    if (!color->Equals(otherObj->color)) {
        return false;
    }
            
    if (x != otherObj->x) {
        return false;
    }
            
    if (y != otherObj->y) {
        return false;
    }
            
    if (shapesize != otherObj->shapesize) {
        return false;
    }
            
    return true;
}



DDS::TypeCode^ ShapeType::get_typecode() {
    if (_typecode == nullptr) {
        _typecode = gcnew DDS::TypeCode(ShapeType_get_typecode());
    }
    return _typecode;
}


DDS_TypeCode* ShapeType_get_typecode()
{
    static RTIBool is_initialized = RTI_FALSE;

    static DDS_TypeCode ShapeType_g_tc_color_string = DDS_INITIALIZE_STRING_TYPECODE(128);

    static DDS_TypeCode_Member ShapeType_g_tc_members[4]=
    {
        {
            (char *)"color",/* Member name */
            {
                0,/* Representation ID */
                DDS_BOOLEAN_FALSE,/* Is a pointer? */
                -1, /* Bitfield bits */
                NULL/* Member type code is assigned later */
            },
            0, /* Ignored */
            0, /* Ignored */
            0, /* Ignored */
            NULL, /* Ignored */
            RTI_CDR_KEY_MEMBER, /* Member flags */
            DDS_PRIVATE_MEMBER,/* Ignored */
            1,
            NULL/* Ignored */
        },
        {
            (char *)"x",/* Member name */
            {
                1,/* Representation ID */
                DDS_BOOLEAN_FALSE,/* Is a pointer? */
                -1, /* Bitfield bits */
                NULL/* Member type code is assigned later */
            },
            0, /* Ignored */
            0, /* Ignored */
            0, /* Ignored */
            NULL, /* Ignored */
            RTI_CDR_REQUIRED_MEMBER, /* Member flags */
            DDS_PRIVATE_MEMBER,/* Ignored */
            1,
            NULL/* Ignored */
        },
        {
            (char *)"y",/* Member name */
            {
                2,/* Representation ID */
                DDS_BOOLEAN_FALSE,/* Is a pointer? */
                -1, /* Bitfield bits */
                NULL/* Member type code is assigned later */
            },
            0, /* Ignored */
            0, /* Ignored */
            0, /* Ignored */
            NULL, /* Ignored */
            RTI_CDR_REQUIRED_MEMBER, /* Member flags */
            DDS_PRIVATE_MEMBER,/* Ignored */
            1,
            NULL/* Ignored */
        },
        {
            (char *)"shapesize",/* Member name */
            {
                3,/* Representation ID */
                DDS_BOOLEAN_FALSE,/* Is a pointer? */
                -1, /* Bitfield bits */
                NULL/* Member type code is assigned later */
            },
            0, /* Ignored */
            0, /* Ignored */
            0, /* Ignored */
            NULL, /* Ignored */
            RTI_CDR_REQUIRED_MEMBER, /* Member flags */
            DDS_PRIVATE_MEMBER,/* Ignored */
            1,
            NULL/* Ignored */
        }
    };

    static DDS_TypeCode ShapeType_g_tc =
    {{
        DDS_TK_STRUCT,/* Kind */
        DDS_BOOLEAN_FALSE, /* Ignored */
        -1,/* Ignored */
        (char *)"ShapeType", /* Name */
        NULL, /* Ignored */
        0, /* Ignored */
        0, /* Ignored */
        NULL, /* Ignored */
        4, /* Number of members */
        ShapeType_g_tc_members, /* Members */
        DDS_VM_NONE /* Ignored */
    }}; /* Type code for ShapeType*/

    if (is_initialized) {
        return &ShapeType_g_tc;
    }


    ShapeType_g_tc_members[0]._representation._typeCode = (RTICdrTypeCode *)&ShapeType_g_tc_color_string;
    ShapeType_g_tc_members[1]._representation._typeCode = (RTICdrTypeCode *)&DDS_g_tc_long;
    ShapeType_g_tc_members[2]._representation._typeCode = (RTICdrTypeCode *)&DDS_g_tc_long;
    ShapeType_g_tc_members[3]._representation._typeCode = (RTICdrTypeCode *)&DDS_g_tc_long;

    is_initialized = RTI_TRUE;

    return &ShapeType_g_tc;
}

/* ========================================================================= */
ShapeTypeExtended::ShapeTypeExtended() {

    fillKind = ShapeFillKind_get_default_value();
            
    angle = 0;
            
}

void ShapeTypeExtended::clear() {
  ShapeType::clear();
  
    fillKind = ShapeFillKind_get_default_value();
          
    angle = 0;
          
}

  

System::Boolean ShapeTypeExtended::copy_from(ShapeTypeExtended^ src) {
    if(!ShapeType::copy_from((ShapeType^) src)) {
        return false;
    }
    ShapeTypeExtended^ dst = this;

    dst->fillKind = src->fillKind;
            
    dst->angle = src->angle;

    return true;
}

Boolean ShapeTypeExtended::Equals(Object^ other) {
    if (other == nullptr) {
        return false;
    }        
    if (this == other) {
        return true;
    }


    if (!ShapeType::Equals(other)) {
        return false;
    }
    ShapeTypeExtended^ otherObj =
        dynamic_cast<ShapeTypeExtended^>(other);
    if (otherObj == nullptr) {
        return false;
    }


    if (fillKind != otherObj->fillKind) {
        return false;
    }
            
    if (angle != otherObj->angle) {
        return false;
    }
            
    return true;
}



DDS::TypeCode^ ShapeTypeExtended::get_typecode() {
    if (_typecode == nullptr) {
        _typecode = gcnew DDS::TypeCode(ShapeTypeExtended_get_typecode());
    }
    return _typecode;
}


DDS_TypeCode* ShapeTypeExtended_get_typecode()
{
    static RTIBool is_initialized = RTI_FALSE;


    static DDS_TypeCode_Member ShapeTypeExtended_g_tc_members[2]=
    {
        {
            (char *)"fillKind",/* Member name */
            {
                (ShapeType_LAST_MEMBER_ID + 1),/* Representation ID */
                DDS_BOOLEAN_FALSE,/* Is a pointer? */
                -1, /* Bitfield bits */
                NULL/* Member type code is assigned later */
            },
            0, /* Ignored */
            0, /* Ignored */
            0, /* Ignored */
            NULL, /* Ignored */
            RTI_CDR_REQUIRED_MEMBER, /* Member flags */
            DDS_PUBLIC_MEMBER,/* Member visibility */
            1,
            NULL/* Ignored */
        },
        {
            (char *)"angle",/* Member name */
            {
                (ShapeType_LAST_MEMBER_ID + 2),/* Representation ID */
                DDS_BOOLEAN_FALSE,/* Is a pointer? */
                -1, /* Bitfield bits */
                NULL/* Member type code is assigned later */
            },
            0, /* Ignored */
            0, /* Ignored */
            0, /* Ignored */
            NULL, /* Ignored */
            RTI_CDR_REQUIRED_MEMBER, /* Member flags */
            DDS_PUBLIC_MEMBER,/* Member visibility */
            1,
            NULL/* Ignored */
        }
    };

    static DDS_TypeCode ShapeTypeExtended_g_tc =
    {{
        DDS_TK_VALUE,/* Kind */
        DDS_BOOLEAN_FALSE, /* Ignored */
        -1,/* Ignored */
        (char *)"ShapeTypeExtended", /* Name */
        NULL, /* Base class type code is assigned later */
        0, /* Ignored */
        0, /* Ignored */
        NULL, /* Ignored */
        2, /* Number of members */
        ShapeTypeExtended_g_tc_members, /* Members */
        DDS_VM_NONE /* Ignored */
    }}; /* Type code for ShapeTypeExtended*/

    if (is_initialized) {
        return &ShapeTypeExtended_g_tc;
    }


    ShapeTypeExtended_g_tc_members[0]._representation._typeCode = (RTICdrTypeCode *)ShapeFillKind_get_typecode();
    ShapeTypeExtended_g_tc_members[1]._representation._typeCode = (RTICdrTypeCode *)&DDS_g_tc_float;

    ShapeTypeExtended_g_tc._data._typeCode = (RTICdrTypeCode *)ShapeType_get_typecode(); /* Base class */

    is_initialized = RTI_TRUE;

    return &ShapeTypeExtended_g_tc;
}
