// dhCommon.h: Common Declerations for TCP/IP Library
//
//////////////////////////////////////////////////////////////////////



#ifndef DHTCPLIB_COMMON_H
#define DHTCPLIB_COMMON_H


#ifdef DHTCPLIB_EXPORTS
#define DHTCPLIB_API __declspec(dllexport)
#else
#define DHTCPLIB_API __declspec(dllimport)
#endif


#pragma warning ( disable : 4786 )		// name length
#pragma warning ( disable : 4251 )		// member does not have dll interface 

#define MAX_RECEIVE_DATA_SIZE 40000

#endif
