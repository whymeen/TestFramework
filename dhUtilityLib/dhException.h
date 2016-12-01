#ifndef dh_EXCEPTION_H
#define dh_EXCEPTION_H

#include "dhCommon.h"

class DHUTILITYLIB_API dhException
{
public:
	dhException( const std::string& from = "", const std::string& desc = "" );
	virtual ~dhException(void);

	virtual void print () ;

	std::string		m_from ;
	std::string		m_desc ;
};


#define	DH_TRY			try 
#define	DH_CATCH		catch ( dhException &exception)
#define	DH_CATCH_ALL	catch (...) 
#define DH_EXP_PRINT	exception.print () ;

#endif //DH_EXCEPTION