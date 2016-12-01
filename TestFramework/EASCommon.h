
//#include "common.h"

#pragma warning (disable: 4996)
#pragma warning (disable: 4267)	//'인수' : 'size_t'에서 'DWORD'(으)로 변환하면서 데이터가 손실될 수 있습니다.
#pragma warning (disable: 4800)	// 'BOOL' : 'true' 또는 'false'로 bool 값을 강제하고 있습니다(성능 경고).

#include <string>

//#include "dhutil/dhTextFileIO.h"
//#include "dhutil/dhXMLParser.h"
//#include "dhutil/dhException.h"
//#include "dhutil/dhPrinter.h"

//#include "EASPrinter.h"
//#include "EASDefBase.h"

#define NETWORK_MAXSIZE		3000

#define THE_NUMBER_OF_TIMES_ABOUT_SENDING_MESSAGE	5

#define CONFIGFILE_NAME		"../data/config.xml"

#define FRAME_3_75HZ			266
#define FRAME_7_5HZ				133
#define FRAME_15HZ				66
#define FRAME_30HZ				33
#define FRAME_60HZ				16
#define FRAME_120HZ				8
#define FRAME_240HZ				4

#define SURFACESHIP_ID			1000
#define SUBMARINE_ID			2000
#define TORPEDO_ID				3000
#define DECOY_ID				4000


enum SIMSPEED_MODE
{
	SPMODE_0_8,
	SPMODE_0_4,
	SPMODE_0_2,
	SPMODE_1,
	SPMODE_2,
	SPMODE_4,
	SPMODE_8,

	SPMODE_NUM
};

enum SIMCTRL_MODE
{
	SIMCTRL_STANDBY,
	SIMCTRL_START,
	SIMCTRL_PAUSE,
	SIMCTRL_STOP,
	SIMCTRL_MODE_SIMSPEED,

	SIMCTRL_NUM
};

enum OBJECT_STATUS_MODE
{
	OBJECT_STATUS_STANDBY,
	OBJECT_STATUS_ENABLE,
	OBJECT_STATUS_DISABLE,

	OBJECT_STATUS_NUM
};

enum OBJECT_CTRL_MODE
{
	OBJECT_CTRL_CREATE,
	OBJECT_CTRL_UPDATE,
	OBJECT_CTRL_DELETE,

	OBJECT_CTRL_NUM
};


enum OBJECT_TYPE
{
	OBJECT_TYPE_INIT,
	OBJECT_TYPE_SURFACESHIP,
	OBJECT_TYPE_SUBMARINE,
	OBJECT_TYPE_TORPEDO,
	OBJECT_TYPE_DECOY,

	OBJECT_TYPE_NUM
};

enum EQUIP_CODE
{
	EQUIP_CODE_ALL,
	EQUIP_CODE_OPERATION_CONTROL,
	EQUIP_CODE_BATTLEFIELD_DISPLAY,
	EQUIP_CODE_OWNSHIP,
	EQUIP_CODE_NEW_HEAVY_TORPEDO,
	EQUIP_CODE_TARGETSHIP,
	EQUIP_CODE_TACTICAL_OBJECT,

	EQUIP_CODE_NUM
};

enum IFF_CODE
{
	IFF_FRIEND,
	IFF_ENEMY,

	IFF__CODE
};



class Common
{
public:
	Common(void);
	~Common(void);

	// 문자열 변환 함수 [3/31/2007 boxface]
//	static CString		stdToCString(std::string s)	{return s.c_str();}
//	static std::string		CStringTostd(CString c)	{return (LPCTSTR)c;}

//	static char*		CStringTochar(CString c)	{return (LPSTR)(LPCSTR)c;}
//	static char*		stdTochar(std::string s)	{CString cst = s.c_str();		return (LPSTR)(LPCSTR)cst;}

	static int			sizeOfCString(CString c)		{return c.GetLength();}
	static int			sizeOfstdString(std::string s)		{return (int)s.size();}

	// 색상 변환 [8/20/2007 boxface]
	static CString		SetNamedColor(COLORREF col);
	static char*		SetNamedColorToChar(COLORREF col);		
	static COLORREF		GetColorCSName(const CString &csCol);
	static COLORREF		GetColorStdName(const std::string &sCol);

	static CString	GetSystemName(int systemCode)
	{
		CString SystemName;
		switch(systemCode)
		{
		case EQUIP_CODE_OPERATION_CONTROL:			SystemName="운용통제기";			break;
		case EQUIP_CODE_BATTLEFIELD_DISPLAY:		SystemName="전장가시화";			break;
		case EQUIP_CODE_OWNSHIP:					SystemName="운용함 모의기";			break;
		case EQUIP_CODE_NEW_HEAVY_TORPEDO:		    SystemName="차기중어뢰 모의기";		break;
		case EQUIP_CODE_TARGETSHIP:					SystemName="표적함 모의기";			break;
		case EQUIP_CODE_TACTICAL_OBJECT:			SystemName="전술객체 모의기";		break;
		default:								    SystemName="unknown system Code";	break;
		}
		return SystemName;
	}

	static double DegreetoDMS(double Degree, double Minute, double Second)
	{
		double tempMin;
		double tempDegree;
		
		if (Second != 0)		tempMin = Minute + (Second / 60);
		else					tempMin = Minute;

		if (tempMin != 0)		tempDegree = Degree + (tempMin / 60);
		else					tempDegree = Degree;

		return tempDegree;
	}

	static double CutDegreet(char *temp)
	{
		double de, mi, se;
		char *p;
		p = strtok(temp, "-");
		de = atof(p);
		p = strtok(NULL, "-");
		mi = atof(p);
		p = strtok(NULL, "-");
		se = atof(p);

		return DegreetoDMS(de, mi, se);
	}

	static void DegreetoDMS(double dDegree, int &iDeg, int &iMin, int &iSec)
	{
		double dMin;

		iDeg = (int)dDegree;
		dMin = (dDegree - iDeg)*60.0;
		iMin = (int)dMin;
		iSec = (int)((dMin - iMin)*60.0);
	}
};
