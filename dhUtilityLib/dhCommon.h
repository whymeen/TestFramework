// dhCommon.h: Common Declerations for Utility Library
//
//////////////////////////////////////////////////////////////////////



#ifndef DHUTILITYLIB_COMMON_H
#define DHUTILITYLIB_COMMON_H


#ifdef DHUTILITYLIB_EXPORTS
#define DHUTILITYLIB_API __declspec(dllexport)
#else
#define DHUTILITYLIB_API __declspec(dllimport)
#endif

#pragma warning ( disable : 4786 )		// name length
#pragma warning ( disable : 4251 )		// member does not have dll interface 

#include <list>
#include <vector>
#include <map>
#include <string>
#include <deque>

#endif
