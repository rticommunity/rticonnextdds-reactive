/*
  WARNING: THIS FILE IS AUTO-GENERATED. DO NOT MODIFY.

  This file was generated from soccer.idl using "rtiddsgen".
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
    

#include "soccer.h"
    
/* ========================================================================= */
AggregateRunningData::AggregateRunningData() {

    ts = 0;
            
    player_id = "";
            
    standing_time = 0;
            
    standing_distance = 0;
            
    trot_time = 0;
            
    trot_distance = 0;
            
    low_time = 0;
            
    low_distance = 0;
            
    medium_time = 0;
            
    medium_distance = 0;
            
    high_time = 0;
            
    high_distance = 0;
            
    sprint_time = 0;
            
    sprint_distance = 0;
            
}

void AggregateRunningData::clear() {
  
    ts = 0;
          
    player_id = "";
          
    standing_time = 0;
          
    standing_distance = 0;
          
    trot_time = 0;
          
    trot_distance = 0;
          
    low_time = 0;
          
    low_distance = 0;
          
    medium_time = 0;
          
    medium_distance = 0;
          
    high_time = 0;
          
    high_distance = 0;
          
    sprint_time = 0;
          
    sprint_distance = 0;
          
}

  

System::Boolean AggregateRunningData::copy_from(AggregateRunningData^ src) {
    AggregateRunningData^ dst = this;

    dst->ts = src->ts;
    dst->player_id = src->player_id;
    dst->standing_time = src->standing_time;
    dst->standing_distance = src->standing_distance;
    dst->trot_time = src->trot_time;
    dst->trot_distance = src->trot_distance;
    dst->low_time = src->low_time;
    dst->low_distance = src->low_distance;
    dst->medium_time = src->medium_time;
    dst->medium_distance = src->medium_distance;
    dst->high_time = src->high_time;
    dst->high_distance = src->high_distance;
    dst->sprint_time = src->sprint_time;
    dst->sprint_distance = src->sprint_distance;

    return true;
}

Boolean AggregateRunningData::Equals(Object^ other) {
    if (other == nullptr) {
        return false;
    }        
    if (this == other) {
        return true;
    }

    AggregateRunningData^ otherObj =
        dynamic_cast<AggregateRunningData^>(other);
    if (otherObj == nullptr) {
        return false;
    }


    if (ts != otherObj->ts) {
        return false;
    }
            
    if (!player_id->Equals(otherObj->player_id)) {
        return false;
    }
            
    if (standing_time != otherObj->standing_time) {
        return false;
    }
            
    if (standing_distance != otherObj->standing_distance) {
        return false;
    }
            
    if (trot_time != otherObj->trot_time) {
        return false;
    }
            
    if (trot_distance != otherObj->trot_distance) {
        return false;
    }
            
    if (low_time != otherObj->low_time) {
        return false;
    }
            
    if (low_distance != otherObj->low_distance) {
        return false;
    }
            
    if (medium_time != otherObj->medium_time) {
        return false;
    }
            
    if (medium_distance != otherObj->medium_distance) {
        return false;
    }
            
    if (high_time != otherObj->high_time) {
        return false;
    }
            
    if (high_distance != otherObj->high_distance) {
        return false;
    }
            
    if (sprint_time != otherObj->sprint_time) {
        return false;
    }
            
    if (sprint_distance != otherObj->sprint_distance) {
        return false;
    }
            
    return true;
}



DDS::TypeCode^ AggregateRunningData::get_typecode() {
    if (_typecode == nullptr) {
        _typecode = gcnew DDS::TypeCode(AggregateRunningData_get_typecode());
    }
    return _typecode;
}


DDS_TypeCode* AggregateRunningData_get_typecode()
{
    static RTIBool is_initialized = RTI_FALSE;

    static DDS_TypeCode AggregateRunningData_g_tc_player_id_string = DDS_INITIALIZE_STRING_TYPECODE(255);

    static DDS_TypeCode_Member AggregateRunningData_g_tc_members[14]=
    {
        {
            (char *)"ts",/* Member name */
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
            RTI_CDR_REQUIRED_MEMBER, /* Member flags */
            DDS_PRIVATE_MEMBER,/* Ignored */
            1,
            NULL/* Ignored */
        },
        {
            (char *)"player_id",/* Member name */
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
            RTI_CDR_KEY_MEMBER, /* Member flags */
            DDS_PRIVATE_MEMBER,/* Ignored */
            1,
            NULL/* Ignored */
        },
        {
            (char *)"standing_time",/* Member name */
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
            (char *)"standing_distance",/* Member name */
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
        },
        {
            (char *)"trot_time",/* Member name */
            {
                4,/* Representation ID */
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
            (char *)"trot_distance",/* Member name */
            {
                5,/* Representation ID */
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
            (char *)"low_time",/* Member name */
            {
                6,/* Representation ID */
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
            (char *)"low_distance",/* Member name */
            {
                7,/* Representation ID */
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
            (char *)"medium_time",/* Member name */
            {
                8,/* Representation ID */
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
            (char *)"medium_distance",/* Member name */
            {
                9,/* Representation ID */
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
            (char *)"high_time",/* Member name */
            {
                10,/* Representation ID */
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
            (char *)"high_distance",/* Member name */
            {
                11,/* Representation ID */
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
            (char *)"sprint_time",/* Member name */
            {
                12,/* Representation ID */
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
            (char *)"sprint_distance",/* Member name */
            {
                13,/* Representation ID */
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

    static DDS_TypeCode AggregateRunningData_g_tc =
    {{
        DDS_TK_STRUCT,/* Kind */
        DDS_BOOLEAN_FALSE, /* Ignored */
        -1,/* Ignored */
        (char *)"AggregateRunningData", /* Name */
        NULL, /* Ignored */
        0, /* Ignored */
        0, /* Ignored */
        NULL, /* Ignored */
        14, /* Number of members */
        AggregateRunningData_g_tc_members, /* Members */
        DDS_VM_NONE /* Ignored */
    }}; /* Type code for AggregateRunningData*/

    if (is_initialized) {
        return &AggregateRunningData_g_tc;
    }


    AggregateRunningData_g_tc_members[0]._representation._typeCode = (RTICdrTypeCode *)&DDS_g_tc_longlong;
    AggregateRunningData_g_tc_members[1]._representation._typeCode = (RTICdrTypeCode *)&AggregateRunningData_g_tc_player_id_string;
    AggregateRunningData_g_tc_members[2]._representation._typeCode = (RTICdrTypeCode *)&DDS_g_tc_double;
    AggregateRunningData_g_tc_members[3]._representation._typeCode = (RTICdrTypeCode *)&DDS_g_tc_double;
    AggregateRunningData_g_tc_members[4]._representation._typeCode = (RTICdrTypeCode *)&DDS_g_tc_double;
    AggregateRunningData_g_tc_members[5]._representation._typeCode = (RTICdrTypeCode *)&DDS_g_tc_double;
    AggregateRunningData_g_tc_members[6]._representation._typeCode = (RTICdrTypeCode *)&DDS_g_tc_double;
    AggregateRunningData_g_tc_members[7]._representation._typeCode = (RTICdrTypeCode *)&DDS_g_tc_double;
    AggregateRunningData_g_tc_members[8]._representation._typeCode = (RTICdrTypeCode *)&DDS_g_tc_double;
    AggregateRunningData_g_tc_members[9]._representation._typeCode = (RTICdrTypeCode *)&DDS_g_tc_double;
    AggregateRunningData_g_tc_members[10]._representation._typeCode = (RTICdrTypeCode *)&DDS_g_tc_double;
    AggregateRunningData_g_tc_members[11]._representation._typeCode = (RTICdrTypeCode *)&DDS_g_tc_double;
    AggregateRunningData_g_tc_members[12]._representation._typeCode = (RTICdrTypeCode *)&DDS_g_tc_double;
    AggregateRunningData_g_tc_members[13]._representation._typeCode = (RTICdrTypeCode *)&DDS_g_tc_double;

    is_initialized = RTI_TRUE;

    return &AggregateRunningData_g_tc;
}

/* ========================================================================= */

DDS_TypeCode* Intensity_get_typecode()
{
    static RTIBool is_initialized = RTI_FALSE;

    static DDS_TypeCode_Member Intensity_g_tc_members[6] =
    {
        {
            (char *)"STOP",/* Member name */
            {
                0,/* Ignored */
                DDS_BOOLEAN_FALSE, /* Ignored */
                -1, /* Ignored */
                NULL /* Ignored */
            },
            (RTICdrLong) Intensity::STOP, /* Enumerator ordinal */
            0, /* Ignored */
            0, /* Ignored */
            NULL, /* Ignored */
            RTI_CDR_REQUIRED_MEMBER, /* Ignored */
            DDS_PRIVATE_MEMBER,/* Ignored */
            1,
            NULL/* Ignored */
        },
        {
            (char *)"TROT",/* Member name */
            {
                0,/* Ignored */
                DDS_BOOLEAN_FALSE, /* Ignored */
                -1, /* Ignored */
                NULL /* Ignored */
            },
            (RTICdrLong) Intensity::TROT, /* Enumerator ordinal */
            0, /* Ignored */
            0, /* Ignored */
            NULL, /* Ignored */
            RTI_CDR_REQUIRED_MEMBER, /* Ignored */
            DDS_PRIVATE_MEMBER,/* Ignored */
            1,
            NULL/* Ignored */
        },
        {
            (char *)"LOW",/* Member name */
            {
                0,/* Ignored */
                DDS_BOOLEAN_FALSE, /* Ignored */
                -1, /* Ignored */
                NULL /* Ignored */
            },
            (RTICdrLong) Intensity::LOW, /* Enumerator ordinal */
            0, /* Ignored */
            0, /* Ignored */
            NULL, /* Ignored */
            RTI_CDR_REQUIRED_MEMBER, /* Ignored */
            DDS_PRIVATE_MEMBER,/* Ignored */
            1,
            NULL/* Ignored */
        },
        {
            (char *)"MEDIUM",/* Member name */
            {
                0,/* Ignored */
                DDS_BOOLEAN_FALSE, /* Ignored */
                -1, /* Ignored */
                NULL /* Ignored */
            },
            (RTICdrLong) Intensity::MEDIUM, /* Enumerator ordinal */
            0, /* Ignored */
            0, /* Ignored */
            NULL, /* Ignored */
            RTI_CDR_REQUIRED_MEMBER, /* Ignored */
            DDS_PRIVATE_MEMBER,/* Ignored */
            1,
            NULL/* Ignored */
        },
        {
            (char *)"HIGH",/* Member name */
            {
                0,/* Ignored */
                DDS_BOOLEAN_FALSE, /* Ignored */
                -1, /* Ignored */
                NULL /* Ignored */
            },
            (RTICdrLong) Intensity::HIGH, /* Enumerator ordinal */
            0, /* Ignored */
            0, /* Ignored */
            NULL, /* Ignored */
            RTI_CDR_REQUIRED_MEMBER, /* Ignored */
            DDS_PRIVATE_MEMBER,/* Ignored */
            1,
            NULL/* Ignored */
        },
        {
            (char *)"SPRINT",/* Member name */
            {
                0,/* Ignored */
                DDS_BOOLEAN_FALSE, /* Ignored */
                -1, /* Ignored */
                NULL /* Ignored */
            },
            (RTICdrLong) Intensity::SPRINT, /* Enumerator ordinal */
            0, /* Ignored */
            0, /* Ignored */
            NULL, /* Ignored */
            RTI_CDR_REQUIRED_MEMBER, /* Ignored */
            DDS_PRIVATE_MEMBER,/* Ignored */
            1,
            NULL/* Ignored */
        }
    };

    static DDS_TypeCode Intensity_g_tc = 
    {{
        DDS_TK_ENUM, /* Kind */
        DDS_BOOLEAN_FALSE, /* Ignored */
        -1, /* Ignored */
        (char *)"Intensity", /* Name */
        NULL, /* Ignored */
        0, /* Ignored */
        0, /* Ignored */
        NULL, /* Ignored */
        6, /* Number of enumerators */
        Intensity_g_tc_members, /* Enumerators */
        DDS_VM_NONE /* Ignored */
}    };

    if (is_initialized) {
        return &Intensity_g_tc;
    }

    is_initialized = RTI_TRUE;
    return &Intensity_g_tc;
}
Intensity Intensity_get_default_value() {
    return Intensity::STOP;
}


/* ========================================================================= */
CurrentRunningData::CurrentRunningData() {

    ts_start = 0;
            
    ts_stop = 0;
            
    player_id = "";
            
    intensity = Intensity_get_default_value();
            
    distance = 0;
            
    speed = 0;
            
}

void CurrentRunningData::clear() {
  
    ts_start = 0;
          
    ts_stop = 0;
          
    player_id = "";
          
    intensity = Intensity_get_default_value();
          
    distance = 0;
          
    speed = 0;
          
}

  

System::Boolean CurrentRunningData::copy_from(CurrentRunningData^ src) {
    CurrentRunningData^ dst = this;

    dst->ts_start = src->ts_start;
    dst->ts_stop = src->ts_stop;
    dst->player_id = src->player_id;
    dst->intensity = src->intensity;
            
    dst->distance = src->distance;
    dst->speed = src->speed;

    return true;
}

Boolean CurrentRunningData::Equals(Object^ other) {
    if (other == nullptr) {
        return false;
    }        
    if (this == other) {
        return true;
    }

    CurrentRunningData^ otherObj =
        dynamic_cast<CurrentRunningData^>(other);
    if (otherObj == nullptr) {
        return false;
    }


    if (ts_start != otherObj->ts_start) {
        return false;
    }
            
    if (ts_stop != otherObj->ts_stop) {
        return false;
    }
            
    if (!player_id->Equals(otherObj->player_id)) {
        return false;
    }
            
    if (intensity != otherObj->intensity) {
        return false;
    }
            
    if (distance != otherObj->distance) {
        return false;
    }
            
    if (speed != otherObj->speed) {
        return false;
    }
            
    return true;
}



DDS::TypeCode^ CurrentRunningData::get_typecode() {
    if (_typecode == nullptr) {
        _typecode = gcnew DDS::TypeCode(CurrentRunningData_get_typecode());
    }
    return _typecode;
}


DDS_TypeCode* CurrentRunningData_get_typecode()
{
    static RTIBool is_initialized = RTI_FALSE;

    static DDS_TypeCode CurrentRunningData_g_tc_player_id_string = DDS_INITIALIZE_STRING_TYPECODE(255);

    static DDS_TypeCode_Member CurrentRunningData_g_tc_members[6]=
    {
        {
            (char *)"ts_start",/* Member name */
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
            RTI_CDR_REQUIRED_MEMBER, /* Member flags */
            DDS_PRIVATE_MEMBER,/* Ignored */
            1,
            NULL/* Ignored */
        },
        {
            (char *)"ts_stop",/* Member name */
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
            (char *)"player_id",/* Member name */
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
            RTI_CDR_KEY_MEMBER, /* Member flags */
            DDS_PRIVATE_MEMBER,/* Ignored */
            1,
            NULL/* Ignored */
        },
        {
            (char *)"intensity",/* Member name */
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
        },
        {
            (char *)"distance",/* Member name */
            {
                4,/* Representation ID */
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
            (char *)"speed",/* Member name */
            {
                5,/* Representation ID */
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

    static DDS_TypeCode CurrentRunningData_g_tc =
    {{
        DDS_TK_STRUCT,/* Kind */
        DDS_BOOLEAN_FALSE, /* Ignored */
        -1,/* Ignored */
        (char *)"CurrentRunningData", /* Name */
        NULL, /* Ignored */
        0, /* Ignored */
        0, /* Ignored */
        NULL, /* Ignored */
        6, /* Number of members */
        CurrentRunningData_g_tc_members, /* Members */
        DDS_VM_NONE /* Ignored */
    }}; /* Type code for CurrentRunningData*/

    if (is_initialized) {
        return &CurrentRunningData_g_tc;
    }


    CurrentRunningData_g_tc_members[0]._representation._typeCode = (RTICdrTypeCode *)&DDS_g_tc_longlong;
    CurrentRunningData_g_tc_members[1]._representation._typeCode = (RTICdrTypeCode *)&DDS_g_tc_longlong;
    CurrentRunningData_g_tc_members[2]._representation._typeCode = (RTICdrTypeCode *)&CurrentRunningData_g_tc_player_id_string;
    CurrentRunningData_g_tc_members[3]._representation._typeCode = (RTICdrTypeCode *)Intensity_get_typecode();
    CurrentRunningData_g_tc_members[4]._representation._typeCode = (RTICdrTypeCode *)&DDS_g_tc_double;
    CurrentRunningData_g_tc_members[5]._representation._typeCode = (RTICdrTypeCode *)&DDS_g_tc_double;

    is_initialized = RTI_TRUE;

    return &CurrentRunningData_g_tc;
}

/* ========================================================================= */
PlayerBallPossession::PlayerBallPossession() {

    ts = 0;
            
    player_id = "";
            
    time = 0;
            
    hits = 0;
            
}

void PlayerBallPossession::clear() {
  
    ts = 0;
          
    player_id = "";
          
    time = 0;
          
    hits = 0;
          
}

  

System::Boolean PlayerBallPossession::copy_from(PlayerBallPossession^ src) {
    PlayerBallPossession^ dst = this;

    dst->ts = src->ts;
    dst->player_id = src->player_id;
    dst->time = src->time;
    dst->hits = src->hits;

    return true;
}

Boolean PlayerBallPossession::Equals(Object^ other) {
    if (other == nullptr) {
        return false;
    }        
    if (this == other) {
        return true;
    }

    PlayerBallPossession^ otherObj =
        dynamic_cast<PlayerBallPossession^>(other);
    if (otherObj == nullptr) {
        return false;
    }


    if (ts != otherObj->ts) {
        return false;
    }
            
    if (!player_id->Equals(otherObj->player_id)) {
        return false;
    }
            
    if (time != otherObj->time) {
        return false;
    }
            
    if (hits != otherObj->hits) {
        return false;
    }
            
    return true;
}



DDS::TypeCode^ PlayerBallPossession::get_typecode() {
    if (_typecode == nullptr) {
        _typecode = gcnew DDS::TypeCode(PlayerBallPossession_get_typecode());
    }
    return _typecode;
}


DDS_TypeCode* PlayerBallPossession_get_typecode()
{
    static RTIBool is_initialized = RTI_FALSE;

    static DDS_TypeCode PlayerBallPossession_g_tc_player_id_string = DDS_INITIALIZE_STRING_TYPECODE(255);

    static DDS_TypeCode_Member PlayerBallPossession_g_tc_members[4]=
    {
        {
            (char *)"ts",/* Member name */
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
            RTI_CDR_REQUIRED_MEMBER, /* Member flags */
            DDS_PRIVATE_MEMBER,/* Ignored */
            1,
            NULL/* Ignored */
        },
        {
            (char *)"player_id",/* Member name */
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
            RTI_CDR_KEY_MEMBER, /* Member flags */
            DDS_PRIVATE_MEMBER,/* Ignored */
            1,
            NULL/* Ignored */
        },
        {
            (char *)"time",/* Member name */
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
            (char *)"hits",/* Member name */
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

    static DDS_TypeCode PlayerBallPossession_g_tc =
    {{
        DDS_TK_STRUCT,/* Kind */
        DDS_BOOLEAN_FALSE, /* Ignored */
        -1,/* Ignored */
        (char *)"PlayerBallPossession", /* Name */
        NULL, /* Ignored */
        0, /* Ignored */
        0, /* Ignored */
        NULL, /* Ignored */
        4, /* Number of members */
        PlayerBallPossession_g_tc_members, /* Members */
        DDS_VM_NONE /* Ignored */
    }}; /* Type code for PlayerBallPossession*/

    if (is_initialized) {
        return &PlayerBallPossession_g_tc;
    }


    PlayerBallPossession_g_tc_members[0]._representation._typeCode = (RTICdrTypeCode *)&DDS_g_tc_longlong;
    PlayerBallPossession_g_tc_members[1]._representation._typeCode = (RTICdrTypeCode *)&PlayerBallPossession_g_tc_player_id_string;
    PlayerBallPossession_g_tc_members[2]._representation._typeCode = (RTICdrTypeCode *)&DDS_g_tc_double;
    PlayerBallPossession_g_tc_members[3]._representation._typeCode = (RTICdrTypeCode *)&DDS_g_tc_long;

    is_initialized = RTI_TRUE;

    return &PlayerBallPossession_g_tc;
}

/* ========================================================================= */
PlayerData::PlayerData() {

    player_name = "";
            
    ts = 0;
            
    pos_x = 0;
            
    pos_y = 0;
            
    pos_z = 0;
            
    vel = 0;
            
    accel = 0;
            
    vel_x = 0;
            
    vel_y = 0;
            
    vel_z = 0;
            
    accel_x = 0;
            
    accel_y = 0;
            
    accel_z = 0;
            
}

void PlayerData::clear() {
  
    player_name = "";
          
    ts = 0;
          
    pos_x = 0;
          
    pos_y = 0;
          
    pos_z = 0;
          
    vel = 0;
          
    accel = 0;
          
    vel_x = 0;
          
    vel_y = 0;
          
    vel_z = 0;
          
    accel_x = 0;
          
    accel_y = 0;
          
    accel_z = 0;
          
}

  

System::Boolean PlayerData::copy_from(PlayerData^ src) {
    PlayerData^ dst = this;

    dst->player_name = src->player_name;
    dst->ts = src->ts;
    dst->pos_x = src->pos_x;
    dst->pos_y = src->pos_y;
    dst->pos_z = src->pos_z;
    dst->vel = src->vel;
    dst->accel = src->accel;
    dst->vel_x = src->vel_x;
    dst->vel_y = src->vel_y;
    dst->vel_z = src->vel_z;
    dst->accel_x = src->accel_x;
    dst->accel_y = src->accel_y;
    dst->accel_z = src->accel_z;

    return true;
}

Boolean PlayerData::Equals(Object^ other) {
    if (other == nullptr) {
        return false;
    }        
    if (this == other) {
        return true;
    }

    PlayerData^ otherObj =
        dynamic_cast<PlayerData^>(other);
    if (otherObj == nullptr) {
        return false;
    }


    if (!player_name->Equals(otherObj->player_name)) {
        return false;
    }
            
    if (ts != otherObj->ts) {
        return false;
    }
            
    if (pos_x != otherObj->pos_x) {
        return false;
    }
            
    if (pos_y != otherObj->pos_y) {
        return false;
    }
            
    if (pos_z != otherObj->pos_z) {
        return false;
    }
            
    if (vel != otherObj->vel) {
        return false;
    }
            
    if (accel != otherObj->accel) {
        return false;
    }
            
    if (vel_x != otherObj->vel_x) {
        return false;
    }
            
    if (vel_y != otherObj->vel_y) {
        return false;
    }
            
    if (vel_z != otherObj->vel_z) {
        return false;
    }
            
    if (accel_x != otherObj->accel_x) {
        return false;
    }
            
    if (accel_y != otherObj->accel_y) {
        return false;
    }
            
    if (accel_z != otherObj->accel_z) {
        return false;
    }
            
    return true;
}



DDS::TypeCode^ PlayerData::get_typecode() {
    if (_typecode == nullptr) {
        _typecode = gcnew DDS::TypeCode(PlayerData_get_typecode());
    }
    return _typecode;
}


DDS_TypeCode* PlayerData_get_typecode()
{
    static RTIBool is_initialized = RTI_FALSE;

    static DDS_TypeCode PlayerData_g_tc_player_name_string = DDS_INITIALIZE_STRING_TYPECODE(255);

    static DDS_TypeCode_Member PlayerData_g_tc_members[13]=
    {
        {
            (char *)"player_name",/* Member name */
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
            (char *)"ts",/* Member name */
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
            (char *)"pos_x",/* Member name */
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
            (char *)"pos_y",/* Member name */
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
        },
        {
            (char *)"pos_z",/* Member name */
            {
                4,/* Representation ID */
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
            (char *)"vel",/* Member name */
            {
                5,/* Representation ID */
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
            (char *)"accel",/* Member name */
            {
                6,/* Representation ID */
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
            (char *)"vel_x",/* Member name */
            {
                7,/* Representation ID */
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
            (char *)"vel_y",/* Member name */
            {
                8,/* Representation ID */
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
            (char *)"vel_z",/* Member name */
            {
                9,/* Representation ID */
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
            (char *)"accel_x",/* Member name */
            {
                10,/* Representation ID */
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
            (char *)"accel_y",/* Member name */
            {
                11,/* Representation ID */
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
            (char *)"accel_z",/* Member name */
            {
                12,/* Representation ID */
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

    static DDS_TypeCode PlayerData_g_tc =
    {{
        DDS_TK_STRUCT,/* Kind */
        DDS_BOOLEAN_FALSE, /* Ignored */
        -1,/* Ignored */
        (char *)"PlayerData", /* Name */
        NULL, /* Ignored */
        0, /* Ignored */
        0, /* Ignored */
        NULL, /* Ignored */
        13, /* Number of members */
        PlayerData_g_tc_members, /* Members */
        DDS_VM_NONE /* Ignored */
    }}; /* Type code for PlayerData*/

    if (is_initialized) {
        return &PlayerData_g_tc;
    }


    PlayerData_g_tc_members[0]._representation._typeCode = (RTICdrTypeCode *)&PlayerData_g_tc_player_name_string;
    PlayerData_g_tc_members[1]._representation._typeCode = (RTICdrTypeCode *)&DDS_g_tc_longlong;
    PlayerData_g_tc_members[2]._representation._typeCode = (RTICdrTypeCode *)&DDS_g_tc_double;
    PlayerData_g_tc_members[3]._representation._typeCode = (RTICdrTypeCode *)&DDS_g_tc_double;
    PlayerData_g_tc_members[4]._representation._typeCode = (RTICdrTypeCode *)&DDS_g_tc_double;
    PlayerData_g_tc_members[5]._representation._typeCode = (RTICdrTypeCode *)&DDS_g_tc_double;
    PlayerData_g_tc_members[6]._representation._typeCode = (RTICdrTypeCode *)&DDS_g_tc_double;
    PlayerData_g_tc_members[7]._representation._typeCode = (RTICdrTypeCode *)&DDS_g_tc_double;
    PlayerData_g_tc_members[8]._representation._typeCode = (RTICdrTypeCode *)&DDS_g_tc_double;
    PlayerData_g_tc_members[9]._representation._typeCode = (RTICdrTypeCode *)&DDS_g_tc_double;
    PlayerData_g_tc_members[10]._representation._typeCode = (RTICdrTypeCode *)&DDS_g_tc_double;
    PlayerData_g_tc_members[11]._representation._typeCode = (RTICdrTypeCode *)&DDS_g_tc_double;
    PlayerData_g_tc_members[12]._representation._typeCode = (RTICdrTypeCode *)&DDS_g_tc_double;

    is_initialized = RTI_TRUE;

    return &PlayerData_g_tc;
}

/* ========================================================================= */
SensorData::SensorData() {

    sensor_id = 0;
            
    ts = 0;
            
    pos_x = 0;
            
    pos_y = 0;
            
    pos_z = 0;
            
    vel = 0;
            
    accel = 0;
            
    vel_x = 0;
            
    vel_y = 0;
            
    vel_z = 0;
            
    accel_x = 0;
            
    accel_y = 0;
            
    accel_z = 0;
            
}

void SensorData::clear() {
  
    sensor_id = 0;
          
    ts = 0;
          
    pos_x = 0;
          
    pos_y = 0;
          
    pos_z = 0;
          
    vel = 0;
          
    accel = 0;
          
    vel_x = 0;
          
    vel_y = 0;
          
    vel_z = 0;
          
    accel_x = 0;
          
    accel_y = 0;
          
    accel_z = 0;
          
}

  

System::Boolean SensorData::copy_from(SensorData^ src) {
    SensorData^ dst = this;

    dst->sensor_id = src->sensor_id;
    dst->ts = src->ts;
    dst->pos_x = src->pos_x;
    dst->pos_y = src->pos_y;
    dst->pos_z = src->pos_z;
    dst->vel = src->vel;
    dst->accel = src->accel;
    dst->vel_x = src->vel_x;
    dst->vel_y = src->vel_y;
    dst->vel_z = src->vel_z;
    dst->accel_x = src->accel_x;
    dst->accel_y = src->accel_y;
    dst->accel_z = src->accel_z;

    return true;
}

Boolean SensorData::Equals(Object^ other) {
    if (other == nullptr) {
        return false;
    }        
    if (this == other) {
        return true;
    }

    SensorData^ otherObj =
        dynamic_cast<SensorData^>(other);
    if (otherObj == nullptr) {
        return false;
    }


    if (sensor_id != otherObj->sensor_id) {
        return false;
    }
            
    if (ts != otherObj->ts) {
        return false;
    }
            
    if (pos_x != otherObj->pos_x) {
        return false;
    }
            
    if (pos_y != otherObj->pos_y) {
        return false;
    }
            
    if (pos_z != otherObj->pos_z) {
        return false;
    }
            
    if (vel != otherObj->vel) {
        return false;
    }
            
    if (accel != otherObj->accel) {
        return false;
    }
            
    if (vel_x != otherObj->vel_x) {
        return false;
    }
            
    if (vel_y != otherObj->vel_y) {
        return false;
    }
            
    if (vel_z != otherObj->vel_z) {
        return false;
    }
            
    if (accel_x != otherObj->accel_x) {
        return false;
    }
            
    if (accel_y != otherObj->accel_y) {
        return false;
    }
            
    if (accel_z != otherObj->accel_z) {
        return false;
    }
            
    return true;
}



DDS::TypeCode^ SensorData::get_typecode() {
    if (_typecode == nullptr) {
        _typecode = gcnew DDS::TypeCode(SensorData_get_typecode());
    }
    return _typecode;
}


DDS_TypeCode* SensorData_get_typecode()
{
    static RTIBool is_initialized = RTI_FALSE;


    static DDS_TypeCode_Member SensorData_g_tc_members[13]=
    {
        {
            (char *)"sensor_id",/* Member name */
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
            (char *)"ts",/* Member name */
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
            (char *)"pos_x",/* Member name */
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
            (char *)"pos_y",/* Member name */
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
        },
        {
            (char *)"pos_z",/* Member name */
            {
                4,/* Representation ID */
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
            (char *)"vel",/* Member name */
            {
                5,/* Representation ID */
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
            (char *)"accel",/* Member name */
            {
                6,/* Representation ID */
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
            (char *)"vel_x",/* Member name */
            {
                7,/* Representation ID */
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
            (char *)"vel_y",/* Member name */
            {
                8,/* Representation ID */
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
            (char *)"vel_z",/* Member name */
            {
                9,/* Representation ID */
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
            (char *)"accel_x",/* Member name */
            {
                10,/* Representation ID */
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
            (char *)"accel_y",/* Member name */
            {
                11,/* Representation ID */
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
            (char *)"accel_z",/* Member name */
            {
                12,/* Representation ID */
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

    static DDS_TypeCode SensorData_g_tc =
    {{
        DDS_TK_STRUCT,/* Kind */
        DDS_BOOLEAN_FALSE, /* Ignored */
        -1,/* Ignored */
        (char *)"SensorData", /* Name */
        NULL, /* Ignored */
        0, /* Ignored */
        0, /* Ignored */
        NULL, /* Ignored */
        13, /* Number of members */
        SensorData_g_tc_members, /* Members */
        DDS_VM_NONE /* Ignored */
    }}; /* Type code for SensorData*/

    if (is_initialized) {
        return &SensorData_g_tc;
    }


    SensorData_g_tc_members[0]._representation._typeCode = (RTICdrTypeCode *)&DDS_g_tc_long;
    SensorData_g_tc_members[1]._representation._typeCode = (RTICdrTypeCode *)&DDS_g_tc_longlong;
    SensorData_g_tc_members[2]._representation._typeCode = (RTICdrTypeCode *)&DDS_g_tc_long;
    SensorData_g_tc_members[3]._representation._typeCode = (RTICdrTypeCode *)&DDS_g_tc_long;
    SensorData_g_tc_members[4]._representation._typeCode = (RTICdrTypeCode *)&DDS_g_tc_long;
    SensorData_g_tc_members[5]._representation._typeCode = (RTICdrTypeCode *)&DDS_g_tc_long;
    SensorData_g_tc_members[6]._representation._typeCode = (RTICdrTypeCode *)&DDS_g_tc_long;
    SensorData_g_tc_members[7]._representation._typeCode = (RTICdrTypeCode *)&DDS_g_tc_long;
    SensorData_g_tc_members[8]._representation._typeCode = (RTICdrTypeCode *)&DDS_g_tc_long;
    SensorData_g_tc_members[9]._representation._typeCode = (RTICdrTypeCode *)&DDS_g_tc_long;
    SensorData_g_tc_members[10]._representation._typeCode = (RTICdrTypeCode *)&DDS_g_tc_long;
    SensorData_g_tc_members[11]._representation._typeCode = (RTICdrTypeCode *)&DDS_g_tc_long;
    SensorData_g_tc_members[12]._representation._typeCode = (RTICdrTypeCode *)&DDS_g_tc_long;

    is_initialized = RTI_TRUE;

    return &SensorData_g_tc;
}

/* ========================================================================= */
ShotOnGoalData::ShotOnGoalData() {

    ts = 0;
            
    player_id = "";
            
    pos_x = 0;
            
    pos_y = 0;
            
    pos_z = 0;
            
    vel = 0;
            
    vel_x = 0;
            
    vel_y = 0;
            
    vel_z = 0;
            
    accel = 0;
            
    accel_x = 0;
            
    accel_y = 0;
            
    accel_z = 0;
            
}

void ShotOnGoalData::clear() {
  
    ts = 0;
          
    player_id = "";
          
    pos_x = 0;
          
    pos_y = 0;
          
    pos_z = 0;
          
    vel = 0;
          
    vel_x = 0;
          
    vel_y = 0;
          
    vel_z = 0;
          
    accel = 0;
          
    accel_x = 0;
          
    accel_y = 0;
          
    accel_z = 0;
          
}

  

System::Boolean ShotOnGoalData::copy_from(ShotOnGoalData^ src) {
    ShotOnGoalData^ dst = this;

    dst->ts = src->ts;
    dst->player_id = src->player_id;
    dst->pos_x = src->pos_x;
    dst->pos_y = src->pos_y;
    dst->pos_z = src->pos_z;
    dst->vel = src->vel;
    dst->vel_x = src->vel_x;
    dst->vel_y = src->vel_y;
    dst->vel_z = src->vel_z;
    dst->accel = src->accel;
    dst->accel_x = src->accel_x;
    dst->accel_y = src->accel_y;
    dst->accel_z = src->accel_z;

    return true;
}

Boolean ShotOnGoalData::Equals(Object^ other) {
    if (other == nullptr) {
        return false;
    }        
    if (this == other) {
        return true;
    }

    ShotOnGoalData^ otherObj =
        dynamic_cast<ShotOnGoalData^>(other);
    if (otherObj == nullptr) {
        return false;
    }


    if (ts != otherObj->ts) {
        return false;
    }
            
    if (!player_id->Equals(otherObj->player_id)) {
        return false;
    }
            
    if (pos_x != otherObj->pos_x) {
        return false;
    }
            
    if (pos_y != otherObj->pos_y) {
        return false;
    }
            
    if (pos_z != otherObj->pos_z) {
        return false;
    }
            
    if (vel != otherObj->vel) {
        return false;
    }
            
    if (vel_x != otherObj->vel_x) {
        return false;
    }
            
    if (vel_y != otherObj->vel_y) {
        return false;
    }
            
    if (vel_z != otherObj->vel_z) {
        return false;
    }
            
    if (accel != otherObj->accel) {
        return false;
    }
            
    if (accel_x != otherObj->accel_x) {
        return false;
    }
            
    if (accel_y != otherObj->accel_y) {
        return false;
    }
            
    if (accel_z != otherObj->accel_z) {
        return false;
    }
            
    return true;
}



DDS::TypeCode^ ShotOnGoalData::get_typecode() {
    if (_typecode == nullptr) {
        _typecode = gcnew DDS::TypeCode(ShotOnGoalData_get_typecode());
    }
    return _typecode;
}


DDS_TypeCode* ShotOnGoalData_get_typecode()
{
    static RTIBool is_initialized = RTI_FALSE;

    static DDS_TypeCode ShotOnGoalData_g_tc_player_id_string = DDS_INITIALIZE_STRING_TYPECODE(255);

    static DDS_TypeCode_Member ShotOnGoalData_g_tc_members[13]=
    {
        {
            (char *)"ts",/* Member name */
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
            RTI_CDR_REQUIRED_MEMBER, /* Member flags */
            DDS_PRIVATE_MEMBER,/* Ignored */
            1,
            NULL/* Ignored */
        },
        {
            (char *)"player_id",/* Member name */
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
            (char *)"pos_x",/* Member name */
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
            (char *)"pos_y",/* Member name */
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
        },
        {
            (char *)"pos_z",/* Member name */
            {
                4,/* Representation ID */
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
            (char *)"vel",/* Member name */
            {
                5,/* Representation ID */
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
            (char *)"vel_x",/* Member name */
            {
                6,/* Representation ID */
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
            (char *)"vel_y",/* Member name */
            {
                7,/* Representation ID */
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
            (char *)"vel_z",/* Member name */
            {
                8,/* Representation ID */
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
            (char *)"accel",/* Member name */
            {
                9,/* Representation ID */
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
            (char *)"accel_x",/* Member name */
            {
                10,/* Representation ID */
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
            (char *)"accel_y",/* Member name */
            {
                11,/* Representation ID */
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
            (char *)"accel_z",/* Member name */
            {
                12,/* Representation ID */
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

    static DDS_TypeCode ShotOnGoalData_g_tc =
    {{
        DDS_TK_STRUCT,/* Kind */
        DDS_BOOLEAN_FALSE, /* Ignored */
        -1,/* Ignored */
        (char *)"ShotOnGoalData", /* Name */
        NULL, /* Ignored */
        0, /* Ignored */
        0, /* Ignored */
        NULL, /* Ignored */
        13, /* Number of members */
        ShotOnGoalData_g_tc_members, /* Members */
        DDS_VM_NONE /* Ignored */
    }}; /* Type code for ShotOnGoalData*/

    if (is_initialized) {
        return &ShotOnGoalData_g_tc;
    }


    ShotOnGoalData_g_tc_members[0]._representation._typeCode = (RTICdrTypeCode *)&DDS_g_tc_longlong;
    ShotOnGoalData_g_tc_members[1]._representation._typeCode = (RTICdrTypeCode *)&ShotOnGoalData_g_tc_player_id_string;
    ShotOnGoalData_g_tc_members[2]._representation._typeCode = (RTICdrTypeCode *)&DDS_g_tc_long;
    ShotOnGoalData_g_tc_members[3]._representation._typeCode = (RTICdrTypeCode *)&DDS_g_tc_long;
    ShotOnGoalData_g_tc_members[4]._representation._typeCode = (RTICdrTypeCode *)&DDS_g_tc_long;
    ShotOnGoalData_g_tc_members[5]._representation._typeCode = (RTICdrTypeCode *)&DDS_g_tc_long;
    ShotOnGoalData_g_tc_members[6]._representation._typeCode = (RTICdrTypeCode *)&DDS_g_tc_long;
    ShotOnGoalData_g_tc_members[7]._representation._typeCode = (RTICdrTypeCode *)&DDS_g_tc_long;
    ShotOnGoalData_g_tc_members[8]._representation._typeCode = (RTICdrTypeCode *)&DDS_g_tc_long;
    ShotOnGoalData_g_tc_members[9]._representation._typeCode = (RTICdrTypeCode *)&DDS_g_tc_long;
    ShotOnGoalData_g_tc_members[10]._representation._typeCode = (RTICdrTypeCode *)&DDS_g_tc_long;
    ShotOnGoalData_g_tc_members[11]._representation._typeCode = (RTICdrTypeCode *)&DDS_g_tc_long;
    ShotOnGoalData_g_tc_members[12]._representation._typeCode = (RTICdrTypeCode *)&DDS_g_tc_long;

    is_initialized = RTI_TRUE;

    return &ShotOnGoalData_g_tc;
}

/* ========================================================================= */
TeamBallPossession::TeamBallPossession() {

    ts = 0;
            
    team_id = "";
            
    time = 0;
            
    time_percent = 0;
            
}

void TeamBallPossession::clear() {
  
    ts = 0;
          
    team_id = "";
          
    time = 0;
          
    time_percent = 0;
          
}

  

System::Boolean TeamBallPossession::copy_from(TeamBallPossession^ src) {
    TeamBallPossession^ dst = this;

    dst->ts = src->ts;
    dst->team_id = src->team_id;
    dst->time = src->time;
    dst->time_percent = src->time_percent;

    return true;
}

Boolean TeamBallPossession::Equals(Object^ other) {
    if (other == nullptr) {
        return false;
    }        
    if (this == other) {
        return true;
    }

    TeamBallPossession^ otherObj =
        dynamic_cast<TeamBallPossession^>(other);
    if (otherObj == nullptr) {
        return false;
    }


    if (ts != otherObj->ts) {
        return false;
    }
            
    if (!team_id->Equals(otherObj->team_id)) {
        return false;
    }
            
    if (time != otherObj->time) {
        return false;
    }
            
    if (time_percent != otherObj->time_percent) {
        return false;
    }
            
    return true;
}



DDS::TypeCode^ TeamBallPossession::get_typecode() {
    if (_typecode == nullptr) {
        _typecode = gcnew DDS::TypeCode(TeamBallPossession_get_typecode());
    }
    return _typecode;
}


DDS_TypeCode* TeamBallPossession_get_typecode()
{
    static RTIBool is_initialized = RTI_FALSE;

    static DDS_TypeCode TeamBallPossession_g_tc_team_id_string = DDS_INITIALIZE_STRING_TYPECODE(255);

    static DDS_TypeCode_Member TeamBallPossession_g_tc_members[4]=
    {
        {
            (char *)"ts",/* Member name */
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
            RTI_CDR_REQUIRED_MEMBER, /* Member flags */
            DDS_PRIVATE_MEMBER,/* Ignored */
            1,
            NULL/* Ignored */
        },
        {
            (char *)"team_id",/* Member name */
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
            (char *)"time",/* Member name */
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
            (char *)"time_percent",/* Member name */
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

    static DDS_TypeCode TeamBallPossession_g_tc =
    {{
        DDS_TK_STRUCT,/* Kind */
        DDS_BOOLEAN_FALSE, /* Ignored */
        -1,/* Ignored */
        (char *)"TeamBallPossession", /* Name */
        NULL, /* Ignored */
        0, /* Ignored */
        0, /* Ignored */
        NULL, /* Ignored */
        4, /* Number of members */
        TeamBallPossession_g_tc_members, /* Members */
        DDS_VM_NONE /* Ignored */
    }}; /* Type code for TeamBallPossession*/

    if (is_initialized) {
        return &TeamBallPossession_g_tc;
    }


    TeamBallPossession_g_tc_members[0]._representation._typeCode = (RTICdrTypeCode *)&DDS_g_tc_longlong;
    TeamBallPossession_g_tc_members[1]._representation._typeCode = (RTICdrTypeCode *)&TeamBallPossession_g_tc_team_id_string;
    TeamBallPossession_g_tc_members[2]._representation._typeCode = (RTICdrTypeCode *)&DDS_g_tc_double;
    TeamBallPossession_g_tc_members[3]._representation._typeCode = (RTICdrTypeCode *)&DDS_g_tc_double;

    is_initialized = RTI_TRUE;

    return &TeamBallPossession_g_tc;
}
