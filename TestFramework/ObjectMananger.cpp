#include "StdAfx.h"
#include "ObjectMananger.h"

CObjectMananger::CObjectMananger(void)
{
	resetObjectList();
}

CObjectMananger::~CObjectMananger(void)
{
	resetObjectList();
}

void CObjectMananger::resetObjectList()
{
	m_ObjectList.clear();

	//dhPrint("객체 리스트를 초기화 합니다. 객체리스트 사이즈[%d]..!!!\n", GetSize());
}

void CObjectMananger::addObject(CObjectBase object)
{
	int i, count = GetSize();
	for( i=0 ; i<count ; i++ )
	{
		if(object.getObjectID() == m_ObjectList[i].getObjectID())
		{
			//dhPrint("객체 리스트에 이미 존재하는 ID[%d]로 객체 생성 메시지가 수신되었다..!!!\n", object.getObjectID());
			return;
		}			
	}

	m_ObjectList.push_back(object);
	//dhPrint("객체 리스트에 ID[%d] 인 객체정보를 추가하였다...!!!\n", object.getObjectID());

	return;
	
}


void CObjectMananger::delObject(int objectID)
{
	std::vector<CObjectBase>::iterator itor;
	for( itor=m_ObjectList.begin();itor !=m_ObjectList.end() ;itor++)
	{
		CObjectBase objectData = *itor;
		if( objectID == objectData.getObjectID() )
		{
			m_ObjectList.erase(itor);
			//dhPrint("해당하는 객체정보[%d]를 객체리스트에서 삭제합니다. !!\n",objectID);

			return;
		}
	}

	//dhPrint("해당하는 ID[%d]와 일치하는 객체정보가 없습니다. !!\n",objectID);
}

void CObjectMananger::updateObject(CObjectBase object)
{
	int i, count = GetSize();
	for( i=0 ; i<count ; i++ )
	{
		if(object.getObjectID() == m_ObjectList[i].getObjectID())
		{
			m_ObjectList[i].setObjectType(object.getObjectType());

			m_ObjectList[i].setTimeStamp(object.getTimeStamp());
			m_ObjectList[i].setIFF(object.getIFF());
			m_ObjectList[i].setObjectStatus(object.getObjectStatus());

			double x, y, z;
			double h, p, r;

			object.getInitPosition(x, y, z);
			object.getInitDirection(h, p, r);

			m_ObjectList[i].setInitPosition(x, y, z);
			m_ObjectList[i].setInitDirection(h, p, r);

			object.getTranslate(x, y, z);
			object.getRotate(h, p, r);

			m_ObjectList[i].setTranslate(x, y, z);
			m_ObjectList[i].setRotate(h, p, r);
			
			return;
		}			
	}
	//dhPrint("객체 리스트에 갱신할 ID[%d]인 객체정보가 없다....!!!\n", object.getObjectID());
}

void CObjectMananger::updateObject(int objectID, double x, double y, double z)
{
	int i, count = GetSize();
	for( i=0 ; i<count ; i++ )
	{
		if(objectID == m_ObjectList[i].getObjectID())
		{
			m_ObjectList[i].setTranslate(x, y, z);

			return;
		}			
	}
	//dhPrint("객체 리스트에 갱신할 ID[%d]인 객체정보가 없다....!!!\n", objectID);
}

void CObjectMananger::updateObject(int objectID, double x, double y, double z, double h, double p, double r)
{
	int i, count = GetSize();
	for( i=0 ; i<count ; i++ )
	{
		if(objectID == m_ObjectList[i].getObjectID())
		{
			m_ObjectList[i].setTranslate(x, y, z);
			m_ObjectList[i].setRotate(h, p, r);

			return;
		}			
	}
	//dhPrint("객체 리스트에 갱신할 ID[%d]인 객체정보가 없다....!!!\n", objectID);
}

void CObjectMananger::updateObject(int objectID, double dIncreaseHeading, double dVelocity)
{
	int i, count = GetSize();
	for( i=0 ; i<count ; i++ )
	{
		if(objectID == m_ObjectList[i].getObjectID())
		{
			m_ObjectList[i].setIncreaseH(dIncreaseHeading);
			m_ObjectList[i].setIncreaseVel(dVelocity);

			return;
		}			
	}
	//dhPrint("객체 리스트에 갱신할 ID[%d]인 객체정보가 없다....!!!\n", objectID);
}

void CObjectMananger::updateObjectVel(int objectID, double dVelocity)
{
	int i, count = GetSize();
	for( i=0 ; i<count ; i++ )
	{
		if(objectID == m_ObjectList[i].getObjectID())
		{
			m_ObjectList[i].setIncreaseVel(dVelocity);

			return;
		}			
	}
	//dhPrint("객체 리스트에 갱신할 ID[%d]인 객체정보가 없다....!!!\n", objectID);
}

void CObjectMananger::updateObjectAVel(int objectID, double dIncreaseHeading)
{
	int i, count = GetSize();
	for( i=0 ; i<count ; i++ )
	{
		if(objectID == m_ObjectList[i].getObjectID())
		{
			m_ObjectList[i].setIncreaseH(dIncreaseHeading);

			return;
		}			
	}
	//dhPrint("객체 리스트에 갱신할 ID[%d]인 객체정보가 없다....!!!\n", objectID);
}

void CObjectMananger::updateObjectDVel(int objectID, double dIncreaseDepth)
{
	int i, count = GetSize();
	for( i=0 ; i<count ; i++ )
	{
		if(objectID == m_ObjectList[i].getObjectID())
		{
			m_ObjectList[i].setIncreaseDepth(dIncreaseDepth);

			return;
		}			
	}
	//dhPrint("객체 리스트에 갱신할 ID[%d]인 객체정보가 없다....!!!\n", objectID);
}

CObjectBase* CObjectMananger::GetObjectPointer(int objectID)
{
	int i, count = GetSize();
	for( i=0 ; i<count ; i++ )
	{
		if(objectID == m_ObjectList[i].getObjectID())
		{
			return &(CObjectBase)m_ObjectList[i];
		}			
	}
	//dhPrint("객체 리스트에 갱신할 ID[%d]인 객체정보가 없다....!!!\n", objectID);

	return NULL;
}

CObjectBase* CObjectMananger::GetObjectPointerIdx(int index)
{
	int count = GetSize();

	if(index >= count)
	{
		//dhPrint("객체 리스트에 갱신할 index[%d]인 객체정보가 없다....!!!\n", index);
		return NULL;
	}

	return &(CObjectBase)m_ObjectList[index];
}

bool CObjectMananger::checkObjectID(int objectID)
{
	int i, count = GetSize();
	for( i=0 ; i<count ; i++ )
	{
		if(objectID == m_ObjectList[i].getObjectID())
		{
			return true;
		}			
	}
	return false;

}