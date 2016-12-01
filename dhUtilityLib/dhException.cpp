#include "dhException.h"

#include "dhPrinter.h"

dhException::dhException( const std::string& from, const std::string& desc )
{
	m_from = from ;
	m_desc = desc ;
}

dhException::~dhException(void)
{
}

void dhException::print () 
{
	dhPrint ( "Handled Exception" ) ;
	dhPrint ( "   From: %s", m_from.c_str () ) ;
	dhPrint ( "   Desc: %s", m_desc.c_str () ) ;
}
