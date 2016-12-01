/*
 * objectBase.h
 *
 *  Created on: 2010. 6. 15
 *      Author: boxface
 */
#include "vector"

#ifndef OBJECTBASE_H_
#define OBJECTBASE_H_


class CObjectBase
{
public:
	CObjectBase();
	virtual ~CObjectBase();

	void init();

	//CObjectBase& operator = (CObjectBase &Data);

	void setTimeStamp(unsigned int timestamp )	{ m_iTimeStamp = timestamp;}
	void setObjectID(int id)					{m_objectID = id;}
	void setObjectType(int type)				{m_objectType = type;}
	void setObjectImageType(int Imgtype)		{m_objectImageType = Imgtype;}
	void setParentID(int ID)					{m_iParentID = ID;}

	void setObjectStatus(unsigned int status)	{m_objectStatus = status;}
	void setIFF(unsigned short iff)				{m_IFF = iff;}

	void setInitPosition(double x, double y, double z)	{m_initPosX=x; m_initPosY=y; m_initPosZ=z;}
	void setTranslate(double x, double y, double z)		{m_posX=x; m_posY=y; m_posZ=z;}
	void setTranslateX(double x)						{m_posX = x;}
	void setTranslateY(double y)						{m_posY = y;}
	void setTranslateZ(double z)						{m_posZ = z;}
	void setInitLLD(double lat, double lon, double depth)	{m_dLatitude = lat;m_dLongitude = lon;m_dDepth = depth;}
	void setLLD(double lat, double lon, double depth)	{m_dInitLatitude = lat;m_dInitLongitude = lon;m_dInitDepth = depth;}
	void setLatitude(double lat)						{m_dLatitude = lat;}
	void setLongitude(double lon)						{m_dLongitude = lon;}
	void setDepth(double depth)							{m_dDepth = depth;}

	void setInitDirection(double h, double p, double r)	{m_initDirectH=h; m_initDirectP=p; m_initDirectR=r;}
	void setRotate(double h, double p, double r)		{m_directH = h; m_directP = p; m_directR = r;}
	void setRotateH(double h)							{m_directH = h;}
	void setRotateP(double p)							{m_directP = p;}
	void setRotateR(double r)							{m_directR = r;}

	void setIncreaseH(double heading)					{m_dIncreaseH = heading;}
	void setIncreaseVel(double velocity)				{m_dIncreaseVel = velocity;}
	void setIncreaseDepth(double depth)					{m_dIncreaseDepth = depth;}


	const unsigned int getTimeStamp()	{return m_iTimeStamp;}
	const int getObjectID()				{return m_objectID;}
	const int getObjectType()			{return m_objectType;}
	const int getObjectImageType()		{return m_objectImageType;}
	const int getParentID()				{return m_iParentID;}

	const unsigned int getObjectStatus()	{return m_objectStatus;}
	const unsigned short getIFF()			{return m_IFF;}

	void getInitPosition(double &x, double &y, double &z)	{x=m_initPosX; y=m_initPosY; z=m_initPosZ;}
	void getTranslate(double &x, double &y, double &z)		{x=m_posX; y=m_posY; z=m_posZ;}
	const double getTranslateX()							{return m_posX;}
	const double getTranslateY()							{return m_posY;}
	const double getTranslateZ()							{return m_posZ;}
	void getInitLLD(double &lat, double &lon, double &depth)	{lat=m_dInitLatitude;lon=m_dInitLongitude;depth=m_dInitDepth;}
	void getLLD(double &lat, double &lon, double &depth)		{lat=m_dLatitude;lon=m_dLongitude;depth=m_dDepth;}
	const double getLatitude(double lat)						{m_dLatitude = lat;}
	const double getLongitude(double lon)						{m_dLongitude = lon;}
	const double getDepth(double depth)							{m_dDepth = depth;}

	void getInitDirection(double &h, double &p, double &r)	{h=m_initDirectH; p=m_initDirectP;  r=m_initDirectR;}
	void getRotate(double &h, double &p, double &r)			{h=m_directH; p=m_directP; r=m_directR;}
	const double getRotateH()								{return m_directH;}
	const double getRotateP()								{return m_directP;}
	const double getRotateR()								{return m_directR;}

	const double getIncreaseH()								{return m_dIncreaseH;}
	const double getIncreaseVel()							{return m_dIncreaseVel;}
	const double getIncreaseDepth()							{return m_dIncreaseDepth;}


protected:

	unsigned int m_iTimeStamp;
	int m_objectID;
	int m_objectType;
	int m_objectImageType;
	int m_iParentID;

	unsigned int m_objectStatus;  //  [7/19/2010 boxface]
	unsigned short m_IFF;
    
	double m_initPosX, m_initPosY, m_initPosZ;
	double m_initDirectH, m_initDirectP, m_initDirectR;
	double m_posX, m_posY, m_posZ;
	double m_directH, m_directP, m_directR;

	double m_dIncreaseH;
	double m_dIncreaseVel;
	double m_dIncreaseDepth;

	double m_dInitLatitude;
	double m_dInitLongitude;
	double m_dInitDepth;
	double m_dLatitude;
	double m_dLongitude;
	double m_dDepth;



public:

	std::vector<STRUCT_TORPEDO_INFO>	m_vTorpedoList;
	std::vector<STRUCT_DECOY_INFO>	m_vDecoyList;

	

};

#endif /* OBJECTBASE_H_ */
