// dhParser.cpp: implementation of the dhParser class.
//
//////////////////////////////////////////////////////////////////////

#include "dhParser.h"
#include "dhPrinter.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

dhParser::dhParser( dhXMLParser *parser)
{
	m_parser = parser ;
	m_rootName = "" ;
	m_indent = "" ;
}

dhParser::~dhParser()
{

}

void dhParser::saveFile ( const std::string& fileName, dhXMLParser::dhXMLReadElement *node )
{
	try {
		std::ofstream out;
		out.open( fileName.c_str(), std::ios::out ) ;
		//out << "<?xml version='1.0' encoding='ISO-8859-1' ?>\n\n";
		out << "<?xml version='1.0' encoding='UTF-8' ?>\n\n";

		// Bug here:  we need to find a way to get the encoding name
		//   for the default code page on the system where the
		//   program is running, and plug that in for the encoding
		//   name.
		saveNode ( out, node, 0 ) ;
		out.close () ;
	}
	catch (...){
		printf ("Erron in file save\n" ) ;
	}
}

void dhParser::saveNode ( std::ofstream& out, dhXMLParser::dhXMLReadElement *node, int indent )
{
	//
	unsigned int i = 0 ;
	std::string indentstring = "" ;
	std::string myindent = "	" ;
	for ( i = 0; i < (unsigned int)indent; i++ )
	{
		indentstring +=  myindent ;
	}

	//
	//Open Element tag
	//
	out << indentstring.c_str() << "<" << node->m_name.c_str() ;

	dhXMLParser::dhXMLReadElement::AttributeMap::iterator iMap = node->m_attList.begin() ;

	std::string name = "" ;
	std::string value = "" ;
	while ( iMap != node->m_attList.end() )
	{
		name = iMap->first ;
		value = iMap->second ;

		out << std::endl << indentstring.c_str() << myindent.c_str() ;
		//email = "chieff@foo.com"
		out << iMap->first.c_str () << " = \"" << iMap->second.c_str() << "\""  ;
		iMap ++ ;
	}

	//
	//Close Element tag
	//
	if ( node->m_elementList.size() == 0 )
	{
		out << std::endl << indentstring.c_str() << "/" << ">" << std::endl ;
	}
	else
	{
		//
		//Close element name
		//
		out << std::endl << indentstring.c_str() << ">" << std::endl ;

		for ( i = 0; i < node->m_elementList.size(); i++ )
		{
			saveNode ( out, node->m_elementList[i], indent+1) ;
		}

		out << indentstring.c_str() << "</" << node->m_name.c_str() << ">" << std::endl ;
	}
}

bool dhParser::parseFileFromBuffer ( const std::string &buffer )
{
	std::string wholebuf = buffer  ;

	unsigned int locator = 0 ;
	while ( locator < wholebuf.size() )
	{
		switch ( wholebuf [locator ] )
		{
		case '<' :		// Starting a tag
			{
				locator++ ;
				if ( startTag ( wholebuf, locator ) == false )
				{
					dhPrint ("dhParser::parseFileFromBuffer(): Start tag returned false...") ;
					return false ;
				}

			}	break ;

		case '>' :		// Ending a tag
			{
				locator++ ;
			}	break ;

		default:
			locator ++ ;
			break ;
		}
	}

	return true ;
}



bool dhParser::parseFile( const std::string &fileName )
{
	if ( m_fileIO.openFile ( fileName, dhTextFileIO::ACCESS_R ) != dhTextFileIO::SUCCESS )
	{
		dhPrint ( "dhParser::parseFile() : File could not be opened " + fileName ) ;
		return false ;
	}

	std::string wholebuf = "" ;
	m_fileIO.getWholeFile( wholebuf ) ;

	bool result = parseFileFromBuffer ( wholebuf ) ;

	m_fileIO.closeFile() ;

	return result ;
}

bool dhParser::startTag( const std::string& buffer, unsigned int& locator)
{
	//
	// RULES
	//
	// Tag Name ends with ">" or " "
	//
	//
	//

	//Get Tag Name First:
	//
	std::string tagName = "" ;
	m_fileIO.setWordSeperator( "	 >\n\r" ) ;
	m_fileIO.getWord( buffer, tagName, locator ) ;
	printf ( "Start Tag Name : [%s]\n", tagName.c_str () ) ;

	if ( tagName == "?xml" )
	{
		printf ( " Starting PREFERENCES tag : [%s]\n", tagName.c_str() ) ;
		if ( getPreferences ( buffer, locator ) == false )
			return false ;
	}
	else if ( tagName == "!--" )
	{
		printf  ( " Starting COMMENT tag : [%s]\n", tagName.c_str() ) ;
		if ( getComment ( buffer, locator ) == false )
			return false ;
	}
	else if ( tagName[0] == '/' )
	{
		std::string name = tagName.substr( 1, tagName.size() - 1 ) ;
		printf  ( " ENDING ELEMENT tag : [%s]\n", name.c_str() ) ;

		m_parser->readEndElement ( name ) ;
	}
	else
	{
		std::string name ;
		if ( tagName[tagName.size() - 1] == '/' )
		{
			name = tagName.substr( 0, tagName.size() - 1) ;
			printf  ( " Starting ELEMENT tag : [%s]\n", name.c_str() ) ;
			m_parser->readStartElement ( name ) ;
			m_parser->readEndElement ( name ) ;
		}
		else
		{
			name = tagName ;
			//printf  ( " Starting ELEMENT tag : [%s]\n", name.c_str() ) ;
			m_parser->readStartElement ( name ) ;
			if ( getElement ( buffer, locator ) == false )
				return false ;
		}
	}

	return true ;
}

bool dhParser::getElement ( const std::string& buffer, unsigned int& locator)
{
	//
	//Element name ">"
	//It may have attributes or not...
	//
	int endPos = buffer.find (">", locator ) ;
	if ( endPos == buffer.npos )			// buffer.find ÇÑ °á°ú°¡ ¾øÀ»°æ¿ì buffer.npos [6/2/2009 boxface]
		return false ;

	std::string buf = buffer.substr( locator, endPos - locator ) ;

	m_fileIO.setWordSeperator( "	 =>\n\r" ) ;
	std::string name = "" ;
	std::string value = "" ;

	int valStart = 0 ;
	int valEnd = 0 ;

	unsigned int i = 0 ;
	while ( i < buf.size() )
	{
		m_fileIO.getWord( buf, name , i ) ;
		if ( i >= buf.size() || name.size() == 0 )
			break ;

		//
		//@todo: make checks here....!!!!
		//
		valStart = buf.find( '"', i ) ;
		valEnd = buf.find ( '"', valStart + 1 ) ;
		value = buf.substr( valStart+1, valEnd - valStart - 1 ) ;

		//if ( value.size() == 0 )
		//	return false ;

		//printf  ( "  Attribute [%s] = [%s]\n", name.c_str(), value.c_str() ) ;

		m_parser->readAttribute( name, value ) ;

		i = valEnd + 1;
	}

	locator = endPos + 1 ;

	//
	//
	//
	int bufSize = buf.size()-1;
	if(bufSize < 1)
		return true;

	if ( buf[buf.size()-1] == '/' )
	{
		m_parser->readEndElement ( "" ) ;
	}

	return true ;

}

bool dhParser::getPreferences( const std::string& buffer, unsigned int& locator)
{
	//
	//Preferences node should end with "?>"
	//
	int endPos = buffer.find ("?>", locator ) ;
	if ( endPos == buffer.npos )
		return false ;

	std::string buf = buffer.substr( locator, endPos - locator ) ;

	m_fileIO.setWordSeperator( "	 =\n\r" ) ;
	std::string name = "" ;
	std::string value = "" ;

	unsigned int i = 0 ;
	while ( i < buf.size() )
	{
		m_fileIO.getWord( buf, name , i ) ;
		if ( i >= buf.size() || name.size() == 0 )
			break ;

		m_fileIO.getWord ( buf, value, i ) ;

		if ( value.size() < 3 )							// value should be like "value"
			return false ;								// or					'value'
		value = value.substr( 1, value.size() - 2 ) ;	// remove endings

		//printf  ( "  Preferences [%s] = [%s]\n", name.c_str(), value.c_str() ) ;
	}

	locator = endPos + 2 ;
	return true ;

}

bool dhParser::getComment ( const std::string& buffer, unsigned int& locator)
{
	//
	//Comment node should end with "-->"
	//
	int endPos = buffer.find ("-->", locator ) ;
	if ( endPos == buffer.npos )
		return false ;

	std::string buf = buffer.substr( locator, endPos - locator ) ;

	//printf  ( "  Comment [%s]\n", buf.c_str() ) ;

	locator = endPos + 3 ;
	return true ;
}
