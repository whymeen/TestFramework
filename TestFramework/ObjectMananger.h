#pragma once

#include "objectBase.h"		// ref. CObjectBase class

#include <vector>

class CObjectMananger
{
public:
	CObjectMananger(void);
	~CObjectMananger(void);


public:
	const int GetSize()			{return m_ObjectList.size();}

	bool checkObjectID(int ObjectID);

	void resetObjectList();

	void addObject(CObjectBase object);
	void delObject(int objectID);
	void updateObject(CObjectBase object);
	void updateObject(int objectID, double x, double y, double z);
	void updateObject(int objectID, double x, double y, double z, double h, double p, double r);
	void updateObject(int objectID, double dIncreaseHeading, double dVelocity);
	void updateObjectVel(int objectID, double dVelocity);
	void updateObjectAVel(int objectID, double dIncreaseHeading);
	void updateObjectDVel(int objectID, double dIncreaseDepth);

	CObjectBase* GetObjectPointer(int objectID);
	CObjectBase* GetObjectPointerIdx(int index);

//protected:
	std::vector<CObjectBase>	m_ObjectList;


};
