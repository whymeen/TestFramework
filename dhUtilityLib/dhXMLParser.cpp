// ---------------------------------------------------------------------------
//  Includes
// ---------------------------------------------------------------------------

#include "dhXMLParser.h"

#include "dhParser.h"
#include "dhPrinter.h"


#include <string>
#include <sstream>


std::string dhToString ( int val ) 
{
	std::ostringstream os;
	os << val ;
	return os.str();
}

std::string dhToString ( double val ) 
{
	char valstr [1024] ;
	sprintf ( valstr, "%e", val ) ;
	return valstr ;
}

/*************************************
*
*
*
************************************/

dhXMLParser::dhXMLReadElement::dhXMLReadElement ( const std::string& name ) 
{
	m_name = name ;
	m_parent = NULL ;
}

dhXMLParser::dhXMLReadElement::~dhXMLReadElement () 
{
	m_attList.clear() ;

	for ( unsigned int i = 0; i < m_elementList.size(); i++ ) {
		delete m_elementList[i] ;
		m_elementList[i] = NULL ;
	}
	m_elementList.clear() ;

	//delete m_parent;
}


void dhXMLParser::dhXMLReadElement::setAttributeStr ( const std::string& name, const std::string& value, bool checkWhiteSpace ) {
	if ( checkWhiteSpace == true ) 
	{
		std::string val = value ;
		for ( unsigned int i = 0; i < val.size(); i++ ) {
			if ( val[i] == '\r' )
				val[i] = char (194) ;
			else if ( val[i] == '\n' )
				val[i] = char (195) ;
		}
		m_attList[name] = val ;
	}
	else
	{
		m_attList[name] = value ;
	}
}

void dhXMLParser::dhXMLReadElement::setAttributeDbl ( const std::string& name, double value ) {
	setAttributeStr ( name, dhToString (value) ) ;
}

void dhXMLParser::dhXMLReadElement::setAttributeInt ( const std::string& name, int value ) {
	setAttributeStr ( name, dhToString( value ) ) ;
}

void dhXMLParser::dhXMLReadElement::setAttributeBool ( const std::string& name, bool value ) {
	setAttributeStr ( name, dhToString( value ) ) ;
}

const std::string dhXMLParser::dhXMLReadElement::getAttributeStr ( const std::string& name, bool checkWhiteSpace ) {
	
	AttributeMap::iterator imap = m_attList.find( name ) ;
	std::string value ;

	if ( imap == m_attList.end() )
		value = "" ;
	else
		value = imap->second ;

	if ( checkWhiteSpace == true ) {
		for ( unsigned int i = 0; i < value.size(); i++ ) {
			if ( value[i] == char(194) )
				value[i] = '\r' ;
			else if ( value[i] == char(195) )
				value[i] = '\n' ;
		}
	}

	return value ;
	
}

bool dhXMLParser::dhXMLReadElement::getAttributeBool ( const std::string& name, bool defaultVal ) {
	const std::string& val = getAttributeStr (name) ;
	if ( val.empty() )
		return defaultVal ;
	if ( atoi ( val.c_str() ) > 0 )
		return true ;
	else
		return false ;
}


int dhXMLParser::dhXMLReadElement::getAttributeInt ( const std::string& name, int defaultVal ) {
	const std::string& val = getAttributeStr (name) ;
	if ( ! val.empty() )
		return atoi ( val.c_str() ) ;
	return defaultVal ;	
}

double dhXMLParser::dhXMLReadElement::getAttributeDbl ( const std::string& name, double defaultVal ) {
	const std::string& val = getAttributeStr (name) ;
	if ( ! val.empty() )
		return atof ( val.c_str() ) ;
	return defaultVal ;	
}

dhXMLParser::dhXMLReadElement* dhXMLParser::dhXMLReadElement::push ( dhXMLReadElement *elem ) {
	elem->m_parent = this ;
	m_elementList.push_back( elem ) ;
	return elem ;
}

dhXMLParser::dhXMLReadElement* dhXMLParser::dhXMLReadElement::pop ( void ) {
	// not actually pop back from list
	// just return parent node
	return m_parent ;
}

void dhXMLParser::dhXMLReadElement::removeElement ( int idx ) 
{
	if ( idx > (int) m_elementList.size() )
		return ;

	std::vector<dhXMLReadElement*>::iterator iVec = m_elementList.begin () ;
	for ( size_t i = 0; i < (size_t)idx; i++ )
		iVec ++ ;
	delete *iVec ;
	*iVec = NULL ;
	m_elementList.erase ( iVec ) ;
}


dhXMLParser::dhXMLReadElement* dhXMLParser::dhXMLReadElement::element ( const std::string& name, bool lookSubNodes ) {
	unsigned int i ;
	for ( i = 0; i < m_elementList.size(); i++ ) {
		if ( m_elementList[i]->m_name == name )
			return m_elementList[i] ;
	}

	if ( lookSubNodes == true ) {
		for ( unsigned i = 0; i < m_elementList.size(); i++ ) {
			dhXMLReadElement *node = m_elementList[i]->element ( name, lookSubNodes ) ;
			if ( node )
				return node ;
		}
	}

	return NULL ;
}

dhXMLParser::dhXMLReadElement* dhXMLParser::dhXMLReadElement::element ( unsigned int idx ) {
	if ( idx < m_elementList.size() )
		return m_elementList[idx] ;

	return NULL ;
}

/*************************************
*
*
*
************************************/

dhXMLParser::dhXMLParser( ) 
{
	m_preReadElement = NULL ;
	m_currentPreReadElement = NULL ;

	m_handler = new dhParser ( this ) ;

}

dhXMLParser::~dhXMLParser() 
{
	if ( m_preReadElement )
		delete m_preReadElement;
	m_preReadElement = NULL;

	if( m_currentPreReadElement )
		delete m_currentPreReadElement;
	m_currentPreReadElement = NULL;

	if( m_handler )
		delete m_handler;
	m_handler = NULL;
}

bool dhXMLParser::parseFile ( const std::string& fileName ) 
{
	if (  m_handler->parseFile( fileName ) == false )
		return false ;

	return ( rootElement() != NULL ) ;
}

bool dhXMLParser::parseFileFromBuffer ( const std::string& buffer ) 
{
	if ( m_handler->parseFileFromBuffer ( buffer ) == false )
		return false ;

	return ( rootElement() != NULL ) ;
}


void dhXMLParser::saveFile ( const std::string& fileName ) 
{
	// Save to file
	if ( rootElement() == NULL )
		return ;
	m_handler->saveFile ( fileName, rootElement() ) ;

}

std::string dhXMLParser::saveFileToBuffer (  )
{
	saveFile( "temp_file_buffer.xml" ) ;

	dhTextFileIO file ;
	file.openFile ( "temp_file_buffer.xml", dhTextFileIO::ACCESS_R ) ;
	std::string buffer = "" ;
	file.getWholeFile ( buffer ) ;
	file.closeFile () ;
	return buffer ;
}

void dhXMLParser::printFile ( ) 
{
	assert ( m_preReadElement ) ;
	dhPrint ( "Printing Contents of the file:") ;
	printNode ( m_preReadElement ) ;
}

void dhXMLParser::printNode ( dhXMLReadElement *node ) 
{
	dhPrint ("   Contents of the node[%s]", node->name().c_str() ) ;
	
	dhXMLReadElement::AttributeMap::iterator iMap = node->m_attList.begin() ;
	while ( iMap != node->m_attList.end () ) {
		std::string name = iMap->first ;
		std::string val = iMap->second ;

		dhPrint ("      [%s] [%s]", name.c_str(), val.c_str()   ) ;
/**
#if 1
		dhPrint (name.c_str()  ) ;
		dhPrint ("  " ) ;
		dhPrint (val.c_str()   ) ;
		dhPrint ("\n"  ) ;
#else
		wprintf ((wchar_t*)name.c_str()  ) ;
		wprintf ((wchar_t*)"  " ) ;
		wprintf ((wchar_t*)val.c_str()   ) ;
		wprintf ((wchar_t*)"\n"  ) ;
#endif
*/
		iMap ++ ;
	}

	for ( unsigned int i = 0 ; i < node->m_elementList.size(); i++ ) {
		dhXMLReadElement *cNode = node->m_elementList[i] ;
		printNode ( cNode ) ;
	}
}

void dhXMLParser::readStartElement ( const std::string& name ) {
	if ( m_currentPreReadElement == NULL ) {
		assert ( m_preReadElement == NULL ) ;
		m_currentPreReadElement = new dhXMLReadElement ( name ) ;
		m_preReadElement = m_currentPreReadElement ;
	}
	else {
		dhXMLReadElement *elem = new dhXMLReadElement ( name ) ;
		m_currentPreReadElement = m_currentPreReadElement->push ( elem ) ;
	}
}

void dhXMLParser::readEndElement ( const std::string& name ) {
	assert ( m_currentPreReadElement ) ;
	m_currentPreReadElement = m_currentPreReadElement->pop (  ) ;
}

void dhXMLParser::readAttribute ( const std::string& name, const std::string& value ) {
	assert ( m_currentPreReadElement ) ;
	m_currentPreReadElement->setAttributeStr ( name, value ) ;		
}

dhXMLParser::dhXMLReadElement* dhXMLParser::rootElement ( void ) 
{
	return m_preReadElement ;
}

void dhXMLParser::rootElement ( dhXMLParser::dhXMLReadElement*root ) 
{
	if ( m_preReadElement )
		delete m_preReadElement ;
	m_preReadElement = root;
}

dhXMLParser::dhXMLReadElement* dhXMLParser::currentElement ( void ) 
{
	return m_currentPreReadElement ;
}
