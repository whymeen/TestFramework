/*
 *       "This product includes software developed by the
 *        Apache Software Foundation (http://www.apache.org/)."
 */

	 
#ifndef DH_XML_PARSER
#define DH_XML_PARSER

#pragma warning(disable : 4786)

#include <stdio.h>
#include <assert.h>
#include <fstream>
#include <ostream>
#include <cstdio>

#include "dhCommon.h"

#include "dhMap.h"

class DHUTILITYLIB_API dhXMLParser 
{

public:
	class DHUTILITYLIB_API dhXMLReadElement {
	public :
		friend class dhXMLParser ;
		friend class dhParser ;

	public:
		typedef dhMap<std::string, std::string> AttributeMap ;
		
		dhXMLReadElement ( const std::string& name ) ;
		virtual ~dhXMLReadElement () ;

		void	setAttributeStr ( const std::string& name, const std::string& value, bool checkWhiteSpace = false ) ;
		void	setAttributeDbl ( const std::string& name, double value ) ;
		void	setAttributeInt ( const std::string& name, int value ) ;
		void	setAttributeBool ( const std::string& name, bool value ) ;
		
		const std::string	getAttributeStr ( const std::string& name, bool checkWhiteSpace = false ) ;
		int		getAttributeInt ( const std::string& name, int defaultVal = 0 ) ;
		bool	getAttributeBool ( const std::string& name, bool defaultVal = false ) ;
		double	getAttributeDbl ( const std::string& name, double defaultVal = 0.0f ) ;
		dhXMLReadElement* element ( const std::string& name, bool lookSubNodes = false );
		dhXMLReadElement* element ( unsigned int idx ) ;

		dhXMLReadElement*	push ( dhXMLReadElement *elem	);
		dhXMLReadElement*	pop ( void ) ;

		void				removeElement ( int idx ) ;

		const std::string&		name ( void ) { return m_name; } ;

		int						numElements ( void ) { return (int)m_elementList.size() ; } ;

		void					clearAttributes () { m_attList.clear() ; }
		void					clearElements ()
		{
			for ( size_t i = 0; i < m_elementList.size(); i++ )
			{
				delete m_elementList[i] ;
				m_elementList[i] = NULL ;
			}
			m_elementList.clear() ;
		}

	protected :

		std::string						m_name ;		// Name of the node
		std::vector<dhXMLReadElement*>	m_elementList ;	// Child node list
		dhXMLReadElement				*m_parent ;		//
		AttributeMap					m_attList ;		//
	} ;

	
public :
	dhXMLParser		( ) ;
	~dhXMLParser	( void ) ;

	bool parseFile			( const std::string& fileName ) ;
	bool parseFileFromBuffer( const std::string& buffer ) ;
	void saveFile			( const std::string& fileName ) ;
	std::string	saveFileToBuffer ( ) ;

	void printFile			( ) ;

	dhXMLReadElement*		rootElement ( void ) ;
	void					rootElement ( dhXMLReadElement *root ) ;
	dhXMLReadElement*		currentElement ( void ) ;

	virtual void readStartDocument	( ) {};
	virtual void readEndDocument	( ) {};
	virtual void readStartElement	( const std::string& name ) ;
	virtual void readEndElement		( const std::string& name ) ;
	virtual void readAttribute		( const std::string& name, const std::string& value ) ;
	
	void printNode			( dhXMLReadElement *node ) ;

protected:
	dhXMLReadElement		*m_currentPreReadElement ;
	dhXMLReadElement		*m_preReadElement ;
	
	dhParser				*m_handler ;
} ;

std::string DHUTILITYLIB_API dhToString ( int val ) ;
std::string DHUTILITYLIB_API dhToString ( double val ) ;

#endif // DH_XML_PARSER

