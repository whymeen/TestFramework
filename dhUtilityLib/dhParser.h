// dhParser.h: interface for the dhParser class.
//
//////////////////////////////////////////////////////////////////////

#ifndef DH_PARSER_H
#define DH_PARSER_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "dhTextFileIO.h"

#include "dhCommon.h"

#include <stdio.h>
#include <assert.h>
#include <fstream>
#include <ostream>
#include <cstdio>

#include "dhXMLParser.h"

#pragma warning(disable:4267)	// 64bit 이식성 문제(옵션을 Off 하면 없어짐)

class DHUTILITYLIB_API dhXMLParser ;

class dhParser 
{
public:
	dhParser( dhXMLParser *parser );
	virtual ~dhParser();

	bool			parseFile ( const std::string& fileName ) ;
	bool			parseFileFromBuffer ( const std::string& buffer ) ;
	void			saveFile  ( const std::string& fileName,  dhXMLParser::dhXMLReadElement *node ) ;

protected:
	void	saveNode ( std::ofstream& out, dhXMLParser::dhXMLReadElement *node, int indent ) ;

	bool	startTag ( const std::string& buffer, unsigned int& locator ) ;
	bool	getPreferences ( const std::string& buffer, unsigned int &locator ) ;
	bool	getComment ( const std::string& buffer, unsigned int &locator ) ;
	bool	getElement ( const std::string& buffer, unsigned int &locator ) ;
	
	dhTextFileIO					m_fileIO ;
	dhXMLParser						*m_parser ;

	std::ofstream					m_out;
	std::string						m_rootName ;
	std::string						m_indent ;
};

#endif // !defined(DH_PARSER_H)
