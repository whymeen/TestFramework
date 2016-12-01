
// v.10 [8/24/2010 boxface]
// v.10.1 [8/31/2010 boxface]
// v.10.2 [9/1/2010 boxface]
// v.10.3 [9/5/2010 boxface]
//  - 명칭변경
//   

#pragma once

typedef unsigned char Uint8;
typedef char Sint8;
typedef unsigned short Uint16;
typedef short Sint16;
typedef unsigned int Uint32;
typedef int Sint32;
typedef float Sflt32;
typedef double Sdbl64;


typedef struct _STRUCT_WAYPOINT
{
	Sflt32 lat;
	Sflt32 lon;

} STRUCT_WAYPOINT;

typedef struct _STRUCT_TARGET_STRENGTH
{
	Sflt32 azimuth;
	Sflt32 elevation;
	Sflt32 db;

} STRUCT_TARGET_STRENGTH;



typedef struct _ICD_HEADER
{
	Sdbl64	H_Timestamp;
	Uint16	H_Length;
	Uint8	H_Sender_Equip_Code;	//메시지 송신장비 0:All 1:운용통제, 2:전장가시화, 3:운용함, 4:차기중어뢰, 5:표적함, 6:전술객체
	Uint8	H_Receiver_Equip_Code;	//메시지 수신장비 0:All 1:운용통제, 2:전장가시화, 3:운용함, 4:차기중어뢰, 5:표적함, 6:전술객체

} ICD_HEADER;


typedef struct _CODE_HEADER
{
	Uint8	C_Code;
	Uint8	C_Length;

} CODE_HEADER;


typedef struct _EVENT_SIMULATION_CONTROL_0x11
{
	Uint8 type;
	Uint8 length;

	Uint8 control_code;
	Uint8 simspeed;

} EVENT_SIMULATION_CONTROL;


typedef struct _EVENT_SCENARIO_SETUP_0x12
{
	Uint8 type;
	Uint8 length;

	Uint8 ownship_Num;
	Uint8 targetship_Num;
	Uint8 torpedo_Num;
	Uint8 decoy_Num;
	Uint8 sensor_Num;
	Uint8 reserved0;
	Uint16 reserved1;

} EVENT_SCENARIO_SETUP;


typedef struct _EVENT_OBJECT_CONTROL_0x13
{
	Uint8 type;
	Uint8 length;

	Uint16 objectID;

	Uint8 objectType;
	Uint8 mode : 2;		// 0:create, 1:update, 2:delete [6/15/2010 boxface]
	Uint8 IFF : 1;		// 0:아군, 1:적군
	Uint8 status : 2;
	Uint8 unused13_15;

	Uint8 imageType;
	Uint8 targetID;

	Sdbl64 latitude;
	Sdbl64 longitude;
	Sdbl64 depth;

	Sdbl64 speed;
	Sdbl64 course;

	Sdbl64 x;
	Sdbl64 y;
	Sdbl64 z;

	Sdbl64 h;
	Sdbl64 p;
	Sdbl64 r;

} EVENT_OBJECT_CONTROL;


typedef struct _EVENT_TORPEDO_SETUP_0x14
{
	Uint8 type;
	Uint8 length;

	Uint16 objectID;

	Uint8 torpedoType;	
	Uint8 imageType;
	Uint16 parentID;

	Sflt32 torpedoLength;
	Sflt32 diameter;
	Sflt32 weight;
	Sflt32 maxspeed;
	Sflt32 dB;
	Sflt32 maxTime;
	Sflt32 maxRange;

	Uint8 searchPattenMode;	
	Uint8 ACCMAbility : 3;
	Uint8 guidanceMode : 3;	
	Uint8 strightSearchMode : 2;
	Uint8 tube_Number : 5;	
	Uint8 torpedo_Mode : 3;
	Uint8 reserved;
	

} EVENT_TORPEDO_SETUP;


typedef struct _EVENT_DECOY_SETUP_0x15
{
	Uint8 type;
	Uint8 length;

	Uint16 objectID;

	Uint8 decoyType;	
	Uint8 imageType;
	Uint16 parentID;

	Sflt32 decoyLength;
	Sflt32 diameter;
	Sflt32 weight;
	Sflt32 maxspeed;
	Sflt32 sounddB;
	Sflt32 workingTime;
	Sflt32 reactionDelayTime;
	Sflt32 workingDelayTime;

	Uint8 operationMode;	
	Uint8 reserved0;
	Uint16 reserved1;

} EVENT_DECOY_SETUP;


typedef struct _EVENT_SENSOR_SETUP_0x16
{
	Uint8 type;
	Uint8 length;

	Uint16 parentID;

	Uint8 sensorID;	
	Uint8 reserved0;
	Uint16 reserved1;

	Sflt32 maxDetectDist;
	Sflt32 HozMinDetectDeg;
	Sflt32 HozMaxDetectDeg;
	Sflt32 VrtMinDetectDeg;
	Sflt32 HrtMaxDetectDeg;
	Sflt32 frequence;

} EVENT_SENSOR_SETUP;

// 미정 [8/12/2010 boxface]
typedef struct _EVENT_EVN_SETUP_0x17
{
	Uint8 type;
	Uint8 length;



} EVENT_ENV_SETUP;


typedef struct _EVENT_LOGIN_0x18
{
	Uint8 type;
	Uint8 length;

	Uint16 ownship_Display_login : 1;
	Uint16 targetship_Display_login : 1;
	Uint16 display_login : 1;
	Uint16 ownship_Model_login : 1;
	Uint16 targetship_Model_login : 1;
	Uint16 new_torpedo_login : 1;
	Uint16 tactical_object_login : 1;
	Uint16 reserved : 9;

} EVENT_LOGIN;


typedef struct _UPDATE_BIT_0x21
{
	Uint8 type : 8;
	Uint8 length : 8;

	Uint8 status_Code : 8;
	Uint8 equip_code : 8;	// 1:운용통제, 2:전장가시화, 3:운용함, 4:차기중어뢰, 5:표적함, 6:전술객체

} UPDATE_BIT;


typedef struct _EVENT_SCENARIO_SETUP_REPLY_0x22
{
	Uint8 type : 8;
	Uint8 length : 8;

	Uint8 setup_reply;	// 0:설정에 문제있음 1:문제없음
	Uint8 reserved;	 

} EVENT_SCENARIO_SETUP_REPLY;


typedef struct _UPDATE_OBJECT_CONTROL_0x23
{
	Uint8 type;
	Uint8 length;

	Uint16 ObjectID;

	Uint8 ObjectType;
	Uint8 IFF : 1;		// 0:아군, 1:적군
	Uint8 status : 2;
	Uint8 unused11_15;

	Uint16 parentID;

	Sdbl64 x;
	Sdbl64 y;
	Sdbl64 z;
	Sdbl64 u;
	Sdbl64 v;
	Sdbl64 w;

	Sflt32 h;
	Sflt32 p;
	Sflt32 r;

	Sdbl64 latitude;
	Sdbl64 longitude;
	Sdbl64 depth;

	Sdbl64 range;
	Sdbl64 elevation;
	Sdbl64 bearing;
	Sdbl64 course;
	Sdbl64 pathAngle;
	Sdbl64 speed;


} UPDATE_OBJECT_CONTROL;


typedef struct _EVENT_LOGIN_REPLY_0x24
{
	Uint8 type;
	Uint8 length;
	Uint16 status:1;
	Uint16 reserved : 15;

} EVENT_LOGIN_REPLY;


typedef struct _EVENT_ACK_0x2F
{
	Uint8 type;
	Uint8 length;
	Uint16 reserved;

	Sdbl64 timestamp;

} EVENT_ACK;


typedef struct _EVENT_TORPEDO_IMPACT_0x31
{
	Uint8 type;
	Uint8 length;

	Uint16 objectID;

	Uint16 impact_objectID;
	Uint16 reserved;

} EVENT_TORPEDO_IMPACT;


typedef struct _EVENT_TORPEDO_PRESET_0x51
{
	Uint8 type;
	Uint8 length;
	Uint16 objectID;

	Uint8 torpedoState :4;
	Uint8 guidanceMode : 2;
	Uint8 guidanceMethod : 2;
	Uint8 speedStep : 2;
	Uint8 targetMode : 2;
	Uint8 targetDetectionState : 4;
	Uint8 TOSOMode : 2;
	Uint8 tansducerControlMode : 4;
	Uint8 tansducerPursuitMode : 2;
	Uint8 targetSupport : 2;
	Uint8 floorStatus : 1;
	Uint8 reserved0 : 5;

	Uint8 linked_Launch ;
	Uint8 reserved1 ;
	Uint16 reserved2 ;

	Sflt32 lateral_Offset;
	Sflt32 mainDirection;
	Sflt32 searchSector;
	Sdbl64 fireTime;
	Sflt32 own_course;
	Sflt32 own_speed;
	Sflt32 torpedo_course;
	Sflt32 torpedo_program_course;
	Sflt32 hDepth;
	Sflt32 mDepth;
	Sflt32 lDepth;

} EVENT_TORPEDO_PRESET;

// 해당패킷은 2010. 09. 13일부로 삭제되고 기능은 0x95 패킷으로 이관
typedef struct _EVENT_TORPEDO_FIRE_0x52
{
	Uint8 type;
	Uint8 length;
	Uint16 objectID;

	Uint16 firing_objectID;
	Uint16 target_objectID;

} EVENT_TORPEDO_FIRE;

typedef struct _EVENT_TORPEDO_PRESET_REPLY_0x61
{
	Uint8 type;
	Uint8 length;
	Uint16 objectID;

	Uint8 torpedoState :4;
	Uint8 guidanceMode : 2;
	Uint8 guidanceMethod : 2;
	Uint8 speedStep : 2;
	Uint8 targetMode : 2;
	Uint8 targetDetectionState : 4;
	Uint8 TOSOMode : 2;
	Uint8 tansducerControlMode : 4;
	Uint8 tansducerPursuitMode : 2;
	Uint8 targetSupport : 2;
	Uint8 floorStatus : 1;
	Uint8 reserved0 : 5;

	Uint8 linked_Launch ;
	Uint8 reserved1 ;
	Uint16 reserved2 ;

	Sflt32 lateral_Offset;
	Sflt32 mainDirection;
	Sflt32 searchSector;
	Sdbl64 fireTime;
	Sflt32 own_course;
	Sflt32 own_speed;
	Sflt32 torpedo_course;
	Sflt32 torpedo_program_course;
	Sflt32 hDepth;
	Sflt32 mDepth;
	Sflt32 lDepth;

} EVENT_TORPEDO_PRESET_REPLY;


typedef struct _UPDATE_TORPEDO_STATUS_0x62
{
	Uint8 type;
	Uint8 length;
	Uint16 objectID;

	Uint8 torpedoState :4;
	Uint8 guidanceMode : 2;
	Uint8 guidanceMethod : 2;

	Uint8 speedStep : 2;
	Uint8 targetMode : 2;
	Uint8 targetDetectionState : 4;

	Uint8 TOSOMode : 2;
	Uint8 tansducerControlMode : 4;
	Uint8 tansducerPursuitMode : 2;

	Uint8 depthLimit_Ceiling : 1;
	Uint8 depthLimit_Floor : 1;
	Uint8 floorStatus : 1;
	Uint8 reserved0 : 5;

	Sflt32 latitiude;
	Sflt32 longitude;
	Sflt32 depth;
	Sflt32 range;
	Sflt32 elevation;
	Sflt32 bearing;
	Sflt32 course;
	Sflt32 pathAngle;
	Sflt32 speed;
	Sflt32 hitTime;
	Sflt32 timeToHit;
	Sflt32 hitRunDistance;
	Uint16 acquisitionProbability;
	Uint16 reattack;
	Sflt32 batteryCapacityTime;

	Uint16 batteryCapacity;
	Uint16 targetSupport : 2;
	Uint16 reserved1 : 14;
	Sflt32 wireLenght;
	Sflt32 wireTime;
	Sflt32 remainderTime;



} UPDATE_TORPEDO_STATUS;

typedef struct _UPDATE_TORPEDO_TACTICAL_DISPLAY_0x63
{
	Uint8 type;
	Uint8 length;
	Uint16 objectID;

	STRUCT_WAYPOINT trj[60];
	STRUCT_WAYPOINT HP;
	STRUCT_WAYPOINT AQ;
	STRUCT_WAYPOINT TEXA[4];
	STRUCT_WAYPOINT WireEnd;
	STRUCT_WAYPOINT BatteryEnd;

} UPDATE_TORPEDO_TACTICAL_DISPLAY;

typedef struct _UPDATE_TORPEDO_TACTICAL_WPA_DISPLAY_0x64
{
	Uint8 type;
	Uint8 length;
	Uint16 objectID;

	Sflt32 torpedoPosition;
	Sflt32 AQPosition;
	Sflt32 TexaPosition0;
	Sflt32 TexaPosition1;
	Sflt32 hitPosition;
	Sflt32 wireEnd;
	Sflt32 batteryEnd;

} UPDATE_TORPEDO_TACTICAL_WPA_DISPLAY;


typedef struct _EVENT_DECOY_PRESET_0x71
{
	Uint8 type;
	Uint8 length;
	Uint16 objectID;

	Uint8 oprationMode;
	Uint8 sendingMode : 3;
	Uint8 reserved0 : 5;
	Uint16 reserved1;

	Sflt32 frequence;
	Sflt32 soundPressure;
	Sflt32 beamWidth;
	Sflt32 decoyDoppler;
	Sflt32 throwingDistance;
	Sflt32 throwingDirection;
	Sflt32 workingTime;
	Sflt32 speed1;
	Sflt32 speed2;
	Sflt32 speed3;
	Sflt32 H1;
	Sflt32 P1;
	Sflt32 R1;
	Sflt32 H2;
	Sflt32 P2;
	Sflt32 R2;
	Sflt32 H3;
	Sflt32 P3;
	Sflt32 R3;
	Sflt32 depth1;
	Sflt32 depth2;
	Sflt32 depth3;
	Sflt32 delayTime;

} EVENT_DECOY_PRESET;


typedef struct _EVENT_DECOY_FIRE_0x72
{
	Uint8 type;
	Uint8 length;
	Uint16 objectID;

	Uint16 firing_objectID;
	Uint16 target_objectID;

} EVENT_DECOY_FIRE;

typedef struct _EVENT_TARGETSHIP_CONTROL_0x73
{
	Uint8 type;
	Uint8 length;
	Uint16 objectID;

	Sflt32 speed;			
	Sflt32 rudderAngle;
	Sflt32 elevatorAngle;

} EVENT_TARGETSHIP_CONTROL;


typedef struct _EVENT_DECOY_PRESET_REPLY_0x81
{
	Uint8 type;
	Uint8 length;
	Uint16 objectID;

	Uint8 status;			// 0:비정상, 1:정상
	Uint8 reserved0;
	Uint16 reserved1;

} EVENT_DECOY_PRESET_REPLY;


typedef struct _EVENT_TARGETSHIP_CONTROL_REPLY_0x82
{
	Uint8 type;
	Uint8 length;
	Uint16 objectID;

	Sflt32 speed;			
	Sflt32 rudderAngle;
	Sflt32 elevatorAngle;

} EVENT_TARGETSHIP_CONTROL_REPLY;


typedef struct _EVENT_TUBE_ASSIGNMENT_0x91
{
	Uint8 type;
	Uint8 length;
	Uint16 objectID;

	Uint8 tube_Number;
	Uint16 targetID;
	Uint8 room_Number;

} EVENT_TUBE_ASSIGNMENT;

typedef struct _EVENT_TORPEDO_SIM_PRESET_0x92
{
	Uint8 type;
	Uint8 length;
	Uint16 objectID;

	Uint8 torpedoState :4;
	Uint8 guidanceMode : 2;
	Uint8 guidanceMethod : 2;
	Uint8 speedStep : 2;
	Uint8 targetMode : 2;
	Uint8 targetDetectionState : 4;
	Uint8 TOSOMode : 2;
	Uint8 tansducerControlMode : 4;
	Uint8 tansducerPursuitMode : 2;
	Uint8 targetSupport : 2;
	Uint8 floorStatus : 1;
	Uint8 attackPlanning : 1;
	Uint8 displayOn : 1;
	Uint8 attackPlanningCopy : 1;
	Uint8 reserved0 : 2;

	Uint8 linked_Launch ;
	Uint8 reserved1 ;
	Uint16 reserved2 ;

	Sflt32 lateral_Offset;
	Sflt32 mainDirection;
	Sflt32 searchSector;
	Sdbl64 fireTime;
	Sflt32 own_course;
	Sflt32 own_speed;
	Sflt32 torpedo_course;
	Sflt32 torpedo_program_course;
	Sflt32 hDepth;
	Sflt32 mDepth;
	Sflt32 lDepth;

} EVENT_TORPEDO_SIM_PRESET;


typedef struct _EVENT_SIM_CONTROL_0x93
{
	Uint8 type;
	Uint8 length;
	Uint8 simMode: 2;		//0 = "-", 1 = "ON"
	Uint8 attackPlanningMode: 2;	//0 = "-", 1 = "ON"
	Uint8 displayMode: 2;		//0 = "-", 1 = "ON"
	Uint8 copyMode: 2;		//0 = "COPY", 1 = " ",  2 = " "
	Uint8 reserved;

} EVENT_SIM_CONTROL;


typedef struct _EVENT_OWNSHIP_CONTROL_0x94
{
	Uint8 type;
	Uint8 length;
	Uint16 objectID;

	Sflt32 speed;			
	Sflt32 rudderAngle;
	Sflt32 elevatorAngle;

} EVENT_OWNSHIP_CONTROL;


typedef struct _EVENT_TOUCH_PANEL_CONTROL_0x95
{
	Uint8 type;
	Uint8 length;
	Uint16 objectID;
	
	Uint16 Firing_objectID;
	Uint16 Target_objectID;

	Uint8 abort_fire: 1;
	Uint8 fire: 1;
	Uint8 internal_Guidance: 1;
	Uint8 manual_Guidance: 1;
	Uint8 toso_boso: 2;
	Uint8 override: 1;
	Uint8 stopWatch: 1;
	
	Uint8 reserved0;
	Uint16 reserved1;		

} EVENT_TOUCH_PANEL_CONTROL;


typedef struct _EVENT_TUBE_ASSIGNMENT_REPLY_0xA1
{
	Uint8 type;
	Uint8 length;
	Uint16 objectID;

	Uint8 assigned_tube_Number;
	Uint16 targetID;
	Uint8 room_Number;

} EVENT_TUBE_ASSIGNMENT_REPLY;

typedef struct _UPDATE_TUBE_STATUS_0xA2
{
	Uint8 type;
	Uint8 length;
	Uint16 objectID;

	Uint8 tube_Number;
	Uint16 target_ObjectID;
	Uint8 torpedoState :4;
	Uint8 check_TWS :4;

	Uint8 tube_status : 4;
	Uint8 weaponType : 2;
	Uint8 weaponCharacter : 2;
	Uint8 emergencyMode : 2;
	Uint8 firingStatus : 2;
	Uint8 reserved1 : 4;
	Uint16 reserved2;

	Sflt32 wireLength;
	Sdbl64 wireTime;

} UPDATE_TUBE_STATUS;


typedef struct _EVENT_TORPEDO_SIM_PRESET_REPLY_0xA3
{
	Uint8 type;
	Uint8 length;
	Uint16 objectID;

	Uint8 torpedoState :4;
	Uint8 guidanceMode : 2;
	Uint8 guidanceMethod : 2;
	Uint8 speedStep : 2;
	Uint8 targetMode : 2;
	Uint8 targetDetectionState : 4;
	Uint8 TOSOMode : 2;
	Uint8 tansducerControlMode : 4;
	Uint8 tansducerPursuitMode : 2;
	Uint8 targetSupport : 2;
	Uint8 floorStatus : 1;
	Uint8 attackPlanning : 1;
	Uint8 displayOn : 1;
	Uint8 attackPlanningCopy : 1;
	Uint8 reserved0 : 2;

	Uint8 linked_Launch ;
	Uint8 reserved1 ;
	Uint16 reserved2 ;

	Sflt32 lateral_Offset;
	Sflt32 mainDirection;
	Sflt32 searchSector;
	Sdbl64 fireTime;
	Sflt32 own_course;
	Sflt32 own_speed;
	Sflt32 torpedo_course;
	Sflt32 torpedo_program_course;
	Sflt32 hDepth;
	Sflt32 mDepth;
	Sflt32 lDepth;

} EVENT_TORPEDO_SIM_PRESET_REPLY;


typedef struct _UPDATE_TORPEDO_SIM_STATUS_0xA4
{
	Uint8 type;
	Uint8 length;
	Uint16 objectID;

	Uint8 torpedoState :4;
	Uint8 guidanceMode : 2;
	Uint8 guidanceMethod : 2;

	Uint8 speedStep : 2;
	Uint8 targetMode : 2;
	Uint8 targetDetectionState : 4;

	Uint8 TOSOMode : 2;
	Uint8 tansducerControlMode : 4;
	Uint8 tansducerPursuitMode : 2;

	Uint8 depthLimit_Ceiling : 1;
	Uint8 depthLimit_Floor : 1;
	Uint8 floorStatus : 1;
	Uint8 reserved0 : 5;

	Sflt32 latitiude;
	Sflt32 longitude;
	Sflt32 depth;
	Sflt32 range;
	Sflt32 elevation;
	Sflt32 bearing;
	Sflt32 course;
	Sflt32 pathAngle;
	Sflt32 speed;
	Sflt32 hitTime;
	Sflt32 timeToHit;
	Sflt32 hitRunDistance;
	Uint16 acquisitionProbability;
	Uint16 reattack;
	Sflt32 batteryCapacityTime;

	Uint16 batteryCapacity;
	Uint16 targetSupport : 2;
	Uint16 attackPlanning : 1;
	Uint16 displayOn : 1;
	Uint16 reserved1 : 12;

	Sflt32 wireLenght;
	Sflt32 wireTime;
	Sflt32 remainderTime;

} UPDATE_TORPEDO_SIM_STATUS;


typedef struct _UPDATE_OWNSHIP_STATUS_0xA5
{
	Uint8 type;
	Uint8 length;
	Uint16 objectID;

	Uint8 objectType ;
	Uint8 reserved0;
	Uint16 reserved1;

	Sdbl64 course;
	Sdbl64 speed;
	Sdbl64 RPM;
	Sdbl64 depth;
	Sdbl64 latitiude;
	Sdbl64 longitude;

} UPDATE_OWNSHIP_STATUS;


typedef struct _UPDATE_TARGETSHIP_STATUS_0xA6
{
	Uint8 type;
	Uint8 length;
	Uint16 objectID;

	Uint8 objectType ;
	Uint16 targetID;
	Uint8 IFF: 2;
	Uint8 targetClass: 2;
	Uint8 PT : 1;
	Uint8 SC : 1;
	Uint8 RC : 1;
	Uint8 reserved;

	Sdbl64 bearing;
	Sdbl64 BR;
	Sdbl64 range;
	Sdbl64 course;
	Sdbl64 AOB;
	Sdbl64 AOBS;
	Sdbl64 latitiude;
	Sdbl64 longitude;
	Sdbl64 CPAB;
	Sdbl64 CPAR;
	Sdbl64 SR;
	Sdbl64 WR;
	Sdbl64 Time;

} UPDATE_TARGETSHIP_STATUS;

typedef struct _EVENT_SIM_CONTROL_REPLY_0xA7
{
	Uint8 type;
	Uint8 length;
	Uint8 simMode: 2;		//0 = "-", 1 = "ON"
	Uint8 attackPlanningMode: 2;	//0 = "-", 1 = "ON"
	Uint8 displayMode: 2;		//0 = "-", 1 = "ON"
	Uint8 copyMode: 3;		//0 = "COPY", 1 = " ",  2 = " "
	Uint8 reserved;	

} EVENT_SIM_CONTROL_REPLY;


typedef struct _EVENT_OWNSHIP_CONTROL_REPLY_0xA8
{
	Uint8 type;
	Uint8 length;
	Uint16 objectID;

	Sflt32 speed;			
	Sflt32 rudderAngle;
	Sflt32 elevatorAngle;

} EVENT_OWNSHIP_CONTROL_REPLY;


typedef struct _EVENT_TORPEDO_TARGET_STRENGTH_0xA9
{
	Uint8 type;
	Uint8 length;
	Uint16 objectID;

	Uint16 targetNum;
	Uint16 reserved0;
	
	// STRUCT_TARGET_STRENGTH data[targetNum];

} EVENT_TORPEDO_TARGET_STRENGTH;


typedef struct _UPDATE_TORPEDO_SONAR_0xAA
{
	Uint8 type;
	Uint8 length;
	Uint16 objectID;

	Sflt32 min_frequence;
	Sflt32 max_frequence;
	Uint32 resolution;
	
	// db[resolution];

} EVENT_TORPEDO_SONAR;


typedef struct _UPDATE_OWNSHIP_SONAR_0xAB
{
	Uint8 type;
	Uint8 length;
	Uint16 objectID;

	Sflt32 min_frequence;
	Sflt32 max_frequence;
	Uint32 resolution;
	
	// db[resolution];

} UPDATE_OWNSHIP_SONAR;


typedef struct _UPDATE_TORPEDO_TACTICAL_SIM_DISPLAY_0xAC
{
	Uint8 type;
	Uint8 length;
	Uint16 objectID;

	STRUCT_WAYPOINT trj[10];
	STRUCT_WAYPOINT HP;
	STRUCT_WAYPOINT AQ;
	STRUCT_WAYPOINT TEXA[4];
	STRUCT_WAYPOINT WireEnd;
	STRUCT_WAYPOINT BatteryEnd;

} UPDATE_TORPEDO_TACTICAL_SIM_DISPLAY;


typedef struct _UPDATE_TORPEDO_TACTICAL_WPA_SIM_DISPLAY_0xAD
{
	Uint8 type;
	Uint8 length;
	Uint16 objectID;

	Sflt32 torpedoPosition;
	Sflt32 AQPosition;
	Sflt32 TexaPosition0;
	Sflt32 TexaPosition1;
	Sflt32 hitPosition;
	Sflt32 wireEnd;
	Sflt32 batteryEnd;

} UPDATE_TORPEDO_TACTICAL_WPA_SIM_DISPLAY;


typedef struct _SUB_OBJECT_INFO
{
	Uint16 objectID;
	Uint8 objectType;
	Uint8 imageType;

} SUB_OBJECT_INFO;


typedef struct _STRUCT_TORPEDO_INFO
{
	int iObjectID;
	int iObjectType;
	int iImageType;
	bool bFired;

} STRUCT_TORPEDO_INFO;


typedef struct _STRUCT_DECOY_INFO
{
	int iObjectID;
	int iObjectType;
	int iImageType;
	bool bFired;

} STRUCT_DECOY_INFO;



typedef struct _UPDATE_TORPEDO_STATUS_0x63
{
	Uint8 type;
	Uint8 length; 
	Uint16 objectID;

	Uint8 torpedoState :4;
	Uint8 guidanceMode : 2;
	Uint8 guidanceMethod : 2;
	Sflt32 depth;

}UPDATE_TORPEDO_STATUS_63;
