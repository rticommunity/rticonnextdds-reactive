/*
  WARNING: THIS FILE IS AUTO-GENERATED. DO NOT MODIFY.

  This file was generated from soccer.idl using "rtiddsgen".
  The rtiddsgen tool is part of the RTI Connext distribution.
  For more information, type 'rtiddsgen -help' at a command shell
  or consult the RTI Connext manual.
*/

#pragma once


struct DDS_TypeCode;
    

using namespace System;
using namespace DDS;

    

public ref struct AggregateRunningData
        : public DDS::ICopyable<AggregateRunningData^> {
    // --- Declared members: -------------------------------------------------
  public:            
    
    System::Int64 ts;
    System::String^ player_id; // maximum length = (255)
    System::Double standing_time;
    System::Double standing_distance;
    System::Double trot_time;
    System::Double trot_distance;
    System::Double low_time;
    System::Double low_distance;
    System::Double medium_time;
    System::Double medium_distance;
    System::Double high_time;
    System::Double high_distance;
    System::Double sprint_time;
    System::Double sprint_distance;

    // --- Static constants: -------------------------------------    
public:
    


#define AggregateRunningData_LAST_MEMBER_ID 13

    // --- Constructors and destructors: -------------------------------------
  public:
    AggregateRunningData();

  // --- Utility methods: --------------------------------------------------
  public:
  virtual void clear();

  virtual System::Boolean copy_from(AggregateRunningData^ src);

    virtual System::Boolean Equals(System::Object^ other) override;

    
    static DDS::TypeCode^ get_typecode();

  private:
    static DDS::TypeCode^ _typecode;

}; // class AggregateRunningData




public ref class AggregateRunningDataSeq sealed
        : public DDS::UserRefSequence<AggregateRunningData^> {
public:
    AggregateRunningDataSeq() :
            DDS::UserRefSequence<AggregateRunningData^>() {
        // empty
    }
    AggregateRunningDataSeq(System::Int32 max) :
            DDS::UserRefSequence<AggregateRunningData^>(max) {
        // empty
    }
    AggregateRunningDataSeq(AggregateRunningDataSeq^ src) :
            DDS::UserRefSequence<AggregateRunningData^>(src) {
        // empty
    }
};


  #define NDDSUSERDllExport

NDDSUSERDllExport DDS_TypeCode* AggregateRunningData_get_typecode();


public enum class Intensity : System::Int32 {
    
    STOP, 
    TROT, 
    LOW, 
    MEDIUM, 
    HIGH, 
    SPRINT
};

Intensity Intensity_get_default_value();

public ref class IntensitySeq
        : public DDS::UserValueSequence<Intensity> {
public:
    IntensitySeq() :
            DDS::UserValueSequence<Intensity>() {
        // empty
    }
    IntensitySeq(System::Int32 max) :
            DDS::UserValueSequence<Intensity>(max) {
        // empty
    }
    IntensitySeq(IntensitySeq^ src) :
            DDS::UserValueSequence<Intensity>(src) {
        // empty
    }
};


  #define NDDSUSERDllExport
NDDSUSERDllExport DDS_TypeCode* Intensity_get_typecode();


public ref struct CurrentRunningData
        : public DDS::ICopyable<CurrentRunningData^> {
    // --- Declared members: -------------------------------------------------
  public:            
    
    System::Int64 ts_start;
    System::Int64 ts_stop;
    System::String^ player_id; // maximum length = (255)
    Intensity intensity;
    System::Double distance;
    System::Double speed;

    // --- Static constants: -------------------------------------    
public:
    


#define CurrentRunningData_LAST_MEMBER_ID 5

    // --- Constructors and destructors: -------------------------------------
  public:
    CurrentRunningData();

  // --- Utility methods: --------------------------------------------------
  public:
  virtual void clear();

  virtual System::Boolean copy_from(CurrentRunningData^ src);

    virtual System::Boolean Equals(System::Object^ other) override;

    
    static DDS::TypeCode^ get_typecode();

  private:
    static DDS::TypeCode^ _typecode;

}; // class CurrentRunningData




public ref class CurrentRunningDataSeq sealed
        : public DDS::UserRefSequence<CurrentRunningData^> {
public:
    CurrentRunningDataSeq() :
            DDS::UserRefSequence<CurrentRunningData^>() {
        // empty
    }
    CurrentRunningDataSeq(System::Int32 max) :
            DDS::UserRefSequence<CurrentRunningData^>(max) {
        // empty
    }
    CurrentRunningDataSeq(CurrentRunningDataSeq^ src) :
            DDS::UserRefSequence<CurrentRunningData^>(src) {
        // empty
    }
};


  #define NDDSUSERDllExport

NDDSUSERDllExport DDS_TypeCode* CurrentRunningData_get_typecode();


public ref struct PlayerBallPossession
        : public DDS::ICopyable<PlayerBallPossession^> {
    // --- Declared members: -------------------------------------------------
  public:            
    
    System::Int64 ts;
    System::String^ player_id; // maximum length = (255)
    System::Double time;
    System::Int32 hits;

    // --- Static constants: -------------------------------------    
public:
    


#define PlayerBallPossession_LAST_MEMBER_ID 3

    // --- Constructors and destructors: -------------------------------------
  public:
    PlayerBallPossession();

  // --- Utility methods: --------------------------------------------------
  public:
  virtual void clear();

  virtual System::Boolean copy_from(PlayerBallPossession^ src);

    virtual System::Boolean Equals(System::Object^ other) override;

    
    static DDS::TypeCode^ get_typecode();

  private:
    static DDS::TypeCode^ _typecode;

}; // class PlayerBallPossession




public ref class PlayerBallPossessionSeq sealed
        : public DDS::UserRefSequence<PlayerBallPossession^> {
public:
    PlayerBallPossessionSeq() :
            DDS::UserRefSequence<PlayerBallPossession^>() {
        // empty
    }
    PlayerBallPossessionSeq(System::Int32 max) :
            DDS::UserRefSequence<PlayerBallPossession^>(max) {
        // empty
    }
    PlayerBallPossessionSeq(PlayerBallPossessionSeq^ src) :
            DDS::UserRefSequence<PlayerBallPossession^>(src) {
        // empty
    }
};


  #define NDDSUSERDllExport

NDDSUSERDllExport DDS_TypeCode* PlayerBallPossession_get_typecode();


public ref struct PlayerData
        : public DDS::ICopyable<PlayerData^> {
    // --- Declared members: -------------------------------------------------
  public:            
    
    System::String^ player_name; // maximum length = (255)
    System::Int64 ts;
    System::Double pos_x;
    System::Double pos_y;
    System::Double pos_z;
    System::Double vel;
    System::Double accel;
    System::Double vel_x;
    System::Double vel_y;
    System::Double vel_z;
    System::Double accel_x;
    System::Double accel_y;
    System::Double accel_z;

    // --- Static constants: -------------------------------------    
public:
    


#define PlayerData_LAST_MEMBER_ID 12

    // --- Constructors and destructors: -------------------------------------
  public:
    PlayerData();

  // --- Utility methods: --------------------------------------------------
  public:
  virtual void clear();

  virtual System::Boolean copy_from(PlayerData^ src);

    virtual System::Boolean Equals(System::Object^ other) override;

    
    static DDS::TypeCode^ get_typecode();

  private:
    static DDS::TypeCode^ _typecode;

}; // class PlayerData




public ref class PlayerDataSeq sealed
        : public DDS::UserRefSequence<PlayerData^> {
public:
    PlayerDataSeq() :
            DDS::UserRefSequence<PlayerData^>() {
        // empty
    }
    PlayerDataSeq(System::Int32 max) :
            DDS::UserRefSequence<PlayerData^>(max) {
        // empty
    }
    PlayerDataSeq(PlayerDataSeq^ src) :
            DDS::UserRefSequence<PlayerData^>(src) {
        // empty
    }
};


  #define NDDSUSERDllExport

NDDSUSERDllExport DDS_TypeCode* PlayerData_get_typecode();


public ref struct SensorData
        : public DDS::ICopyable<SensorData^> {
    // --- Declared members: -------------------------------------------------
  public:            
    
    System::Int32 sensor_id;
    System::Int64 ts;
    System::Int32 pos_x;
    System::Int32 pos_y;
    System::Int32 pos_z;
    System::Int32 vel;
    System::Int32 accel;
    System::Int32 vel_x;
    System::Int32 vel_y;
    System::Int32 vel_z;
    System::Int32 accel_x;
    System::Int32 accel_y;
    System::Int32 accel_z;

    // --- Static constants: -------------------------------------    
public:
    


#define SensorData_LAST_MEMBER_ID 12

    // --- Constructors and destructors: -------------------------------------
  public:
    SensorData();

  // --- Utility methods: --------------------------------------------------
  public:
  virtual void clear();

  virtual System::Boolean copy_from(SensorData^ src);

    virtual System::Boolean Equals(System::Object^ other) override;

    
    static DDS::TypeCode^ get_typecode();

  private:
    static DDS::TypeCode^ _typecode;

}; // class SensorData




public ref class SensorDataSeq sealed
        : public DDS::UserRefSequence<SensorData^> {
public:
    SensorDataSeq() :
            DDS::UserRefSequence<SensorData^>() {
        // empty
    }
    SensorDataSeq(System::Int32 max) :
            DDS::UserRefSequence<SensorData^>(max) {
        // empty
    }
    SensorDataSeq(SensorDataSeq^ src) :
            DDS::UserRefSequence<SensorData^>(src) {
        // empty
    }
};


  #define NDDSUSERDllExport

NDDSUSERDllExport DDS_TypeCode* SensorData_get_typecode();


public ref struct ShotOnGoalData
        : public DDS::ICopyable<ShotOnGoalData^> {
    // --- Declared members: -------------------------------------------------
  public:            
    
    System::Int64 ts;
    System::String^ player_id; // maximum length = (255)
    System::Int32 pos_x;
    System::Int32 pos_y;
    System::Int32 pos_z;
    System::Int32 vel;
    System::Int32 vel_x;
    System::Int32 vel_y;
    System::Int32 vel_z;
    System::Int32 accel;
    System::Int32 accel_x;
    System::Int32 accel_y;
    System::Int32 accel_z;

    // --- Static constants: -------------------------------------    
public:
    


#define ShotOnGoalData_LAST_MEMBER_ID 12

    // --- Constructors and destructors: -------------------------------------
  public:
    ShotOnGoalData();

  // --- Utility methods: --------------------------------------------------
  public:
  virtual void clear();

  virtual System::Boolean copy_from(ShotOnGoalData^ src);

    virtual System::Boolean Equals(System::Object^ other) override;

    
    static DDS::TypeCode^ get_typecode();

  private:
    static DDS::TypeCode^ _typecode;

}; // class ShotOnGoalData




public ref class ShotOnGoalDataSeq sealed
        : public DDS::UserRefSequence<ShotOnGoalData^> {
public:
    ShotOnGoalDataSeq() :
            DDS::UserRefSequence<ShotOnGoalData^>() {
        // empty
    }
    ShotOnGoalDataSeq(System::Int32 max) :
            DDS::UserRefSequence<ShotOnGoalData^>(max) {
        // empty
    }
    ShotOnGoalDataSeq(ShotOnGoalDataSeq^ src) :
            DDS::UserRefSequence<ShotOnGoalData^>(src) {
        // empty
    }
};


  #define NDDSUSERDllExport

NDDSUSERDllExport DDS_TypeCode* ShotOnGoalData_get_typecode();


public ref struct TeamBallPossession
        : public DDS::ICopyable<TeamBallPossession^> {
    // --- Declared members: -------------------------------------------------
  public:            
    
    System::Int64 ts;
    System::String^ team_id; // maximum length = (255)
    System::Double time;
    System::Double time_percent;

    // --- Static constants: -------------------------------------    
public:
    


#define TeamBallPossession_LAST_MEMBER_ID 3

    // --- Constructors and destructors: -------------------------------------
  public:
    TeamBallPossession();

  // --- Utility methods: --------------------------------------------------
  public:
  virtual void clear();

  virtual System::Boolean copy_from(TeamBallPossession^ src);

    virtual System::Boolean Equals(System::Object^ other) override;

    
    static DDS::TypeCode^ get_typecode();

  private:
    static DDS::TypeCode^ _typecode;

}; // class TeamBallPossession




public ref class TeamBallPossessionSeq sealed
        : public DDS::UserRefSequence<TeamBallPossession^> {
public:
    TeamBallPossessionSeq() :
            DDS::UserRefSequence<TeamBallPossession^>() {
        // empty
    }
    TeamBallPossessionSeq(System::Int32 max) :
            DDS::UserRefSequence<TeamBallPossession^>(max) {
        // empty
    }
    TeamBallPossessionSeq(TeamBallPossessionSeq^ src) :
            DDS::UserRefSequence<TeamBallPossession^>(src) {
        // empty
    }
};


  #define NDDSUSERDllExport

NDDSUSERDllExport DDS_TypeCode* TeamBallPossession_get_typecode();
