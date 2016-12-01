// dhPrinter.cpp: implementation of the dhPrinter class.
//
//////////////////////////////////////////////////////////////////////

#include "dhPrinter.h"

#include <stdarg.h>

dhPrinter* dhPrinter::m_printer = NULL ;


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
void dhPrinter::DefaultPrinter::print( int msgType, const std::string& msg )
{
	printf ( "DefaultPrinter MsgType [%i]: %s\n", msgType, msg.c_str() ) ;
}

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

dhPrinter::dhPrinter()
{
}

dhPrinter::~dhPrinter()
{
	m_printers.clear() ;
}

void dhPrinter::addPrinter( dhPrinter::BasePrinter* printer )
{
	dhPrinter *p = dhPrinter::getInstance() ;
	if ( p == NULL )
		return ;

	p->m_printers.push_back( printer ) ;
}

void dhPrinter::removePrinter( dhPrinter::BasePrinter* printer )
{
	dhPrinter *p = dhPrinter::getInstance() ;
 	if ( p == NULL )
		return ;

	std::vector<BasePrinter*>::iterator iVec = p->m_printers.begin() ;
	while ( iVec != p->m_printers.end() )
	{
		if ( *iVec == printer )
		{
			*iVec = NULL ;
			p->m_printers.erase( iVec ) ;
			break ;
		}
		iVec ++ ;
	}
}

void dhPrinter::print( int msgType, const std::string& msg )
{
	dhPrinter *p = dhPrinter::getInstance() ;
	if ( p == NULL )
		return ;

	for ( unsigned int i = 0; i < p->m_printers.size(); i++ )
	{
		p->m_printers[i]->print ( msgType, msg ) ;
	}
}

void dhPrinter::print( const std::string& msg )
{
	print ( -1, msg ) ;
}

void dhPrinter::print( int msgType, const char *format, ... )
{
	char msgbuff[ 16384 ];
	va_list argp;
	
	char* msgptr = msgbuff;
	
	va_start( argp, format );
	vsprintf( msgptr, format, argp );
	va_end( argp );
	
	print( msgType, std::string(msgbuff) ) ;
}

void dhPrinter::print( const char *format, ... )
{
	char msgbuff[ 16384 ];
	va_list argp;
	
	char* msgptr = msgbuff;
	
	va_start( argp, format );
	vsprintf( msgptr, format, argp );
	va_end( argp );
	
	print( -1, std::string(msgbuff) ) ;
}