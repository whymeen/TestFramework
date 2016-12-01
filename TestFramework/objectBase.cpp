/*
 * CObjectBase.cpp
 *
 *  Created on: 2010. 6. 15
 *      Author: boxface
 */

#include "stdafx.h"

#include "objectBase.h"


CObjectBase::CObjectBase()
{
	// TODO Auto-generated constructor stub
	init();

}

CObjectBase::~CObjectBase()
{
	// TODO Auto-generated destructor stub
}

void CObjectBase::init()
{
	m_objectID = -99;
	m_objectType = -1 ;
	m_objectImageType = 0;
//	m_objectStatus = OBJECT_STATUS_STANDBY;  林籍 秒家
	m_iParentID = 0;

	// position variable
	m_posX = 0.0;
	m_posY = 0.0;
	m_posZ = 0.0;

	// direction variable
	m_directH = 0.0;
	m_directP = 0.0;
	m_directR = 0.0;

	// init position variable
	m_initPosX = 0.0;
	m_initPosY = 0.0;
	m_initPosZ = 0.0;

	// init direction variable
	m_initDirectH = 0.0;
	m_initDirectP = 0.0;
	m_initDirectR = 0.0;

	// init velocity and heading [7/6/2010 boxface]
	m_dIncreaseH = 0.0;
	m_dIncreaseVel = 0.0;
	m_dIncreaseDepth = 0.0;

	// init lat/lon/depth [8/22/2010 boxface]
	m_dInitLatitude = 0.0;
	m_dInitLongitude = 0.0;
	m_dInitDepth = 0.0;
	m_dLatitude = 0.0;
	m_dLongitude = 0.0;
	m_dDepth = 0.0;

//	m_vTorpedoList.clear();       林籍 秒家
}

/*
CObjectBase& CObjectBase::operator =(CObjectBase &Data)
{
	init();

	m_iTimeStamp = Data.m_iTimeStamp;
	m_objectID = Data.m_objectID;
	m_objectType = Data.m_objectType;

	m_objectStatus = Data.m_objectStatus;
	m_IFF = Data.m_IFF;
	m_action = Data.m_action;
	m_terrainMode = Data.m_terrainMode;
	m_eventCtrlMode = Data.m_eventCtrlMode;

	m_initPosX = Data.m_initPosX;
	m_initPosY = Data.m_initPosY;
	m_initPosZ = Data.m_initPosZ;
	
	m_initDirectH = Data.m_initDirectH;
	m_initDirectP = Data.m_initDirectP;
	m_initDirectR = Data.m_initDirectR;

	m_posX = Data.m_posX;
	m_posY = Data.m_posY;
	m_posZ = Data.m_posZ;
	
	m_directH = Data.m_directH;
	m_directP = Data.m_directP;
	m_directR = Data.m_directR;

	return (*this);

}
*/