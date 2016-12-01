// dhPrinter.h: interface for the dhPrinter class.
//
//////////////////////////////////////////////////////////////////////

#ifndef DH_PRINTER_H
#define DH_PRINTER_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "dhCommon.h"

//
//Shortcut Define
//
#define dhPrint		dhPrinter::print


class DHUTILITYLIB_API dhPrinter  
{
public:
	class DHUTILITYLIB_API BasePrinter 
	{
	public:
		BasePrinter () {} ;
		virtual ~BasePrinter () {} ;
		
		virtual void		print ( int msgType, const std::string& msg ) = 0 ;
	};

	class DHUTILITYLIB_API DefaultPrinter : public BasePrinter 
	{
	public:
		DefaultPrinter () {} ;
		virtual ~DefaultPrinter () {};

		virtual void		print ( int msgType, const std::string& msg ) ;
	};


public:
	dhPrinter();
	virtual ~dhPrinter();

	static void				addPrinter ( BasePrinter* printer ) ;
	static void				removePrinter ( BasePrinter* printer ) ;

	static void				print ( int msgType, const std::string& msg ) ;
	static void				print ( int msgType, const char *format, ... ) ;

	static void				print ( const std::string& msg ) ;
	static void				print ( const char *format, ... ) ;


	static void				setInstance ( dhPrinter* printer )
	{
		m_printer = printer ;
	}

	static dhPrinter*		getInstance ( void )
	{
		return m_printer ;
	}

protected:
	std::vector<BasePrinter*>		m_printers ;
	static dhPrinter*				m_printer ;
	bool							m_newLine ;

};

#endif // !defined(DH_PRINTER_H)
