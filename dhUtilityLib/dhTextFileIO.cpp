/*
	dhTextFileIO.cpp : Text file access class
*/

#include "dhTextFileIO.h"

dhTextFileIO::dhTextFileIO ( void ) 
{
	m_currentLine = 0 ;
	m_fileName = "" ;
	m_fp = NULL ;
	
	m_commentIdf = "#" ;
	m_wordIdf = " " ;
	m_newLineIdf = "" ;
	m_newLineIdf += (char)'\n';		// new lines
	m_newLineIdf += (char)'\r';
	m_newLineIdf += (char)'\n\r';
	m_newLineIdf += (char)'\r\n';
}

dhTextFileIO::~dhTextFileIO ( void )
{

	closeFile() ;
}

dhTextFileIO::RESULT_TYPES dhTextFileIO::closeFile(  )

{
	if ( m_fp )
		fclose ( m_fp ) ;

	m_fp = NULL ;

	return SUCCESS ;
}

dhTextFileIO::RESULT_TYPES dhTextFileIO::openFile( const std::string& fileName, dhTextFileIO::ACCESS_TYPE type ) {
	m_fileName = fileName ;
	string accType ;
	
	switch ( type ) {
		case  ACCESS_R :
			accType = "r" ;
			break ;
		case  ACCESS_W :
			accType = "w" ;
			break ;
		case  ACCESS_RW :
			accType = "rw" ;
			break ;			
		default :
			break ;
	}

	m_fp = fopen ( m_fileName.c_str(), accType.c_str() ) ;
	if ( m_fp == NULL ) {
		return OPEN_ERROR ;
	}

	m_currentLine = 0 ;
	return SUCCESS ;
}

dhTextFileIO::RESULT_TYPES dhTextFileIO::getWholeLine ( string &buf, bool withEOL ) {

	buf = "" ;
	
	if ( m_skipCommentLines == false )
		return getWholeLineWithComment( buf, withEOL ) ;

	RESULT_TYPES result = getWholeLineWithComment( buf, withEOL ) ;
	if ( buf.size() == 0 )
		return result ;
	
	for ( unsigned int i = 0; i < m_commentIdf.size(); i++ ) {
		if ( buf[0] == m_commentIdf [i] ) {
			result = getWholeLine ( buf, withEOL ) ;
			break ;
		}
	}

	return result ;
}

dhTextFileIO::RESULT_TYPES dhTextFileIO::getWholeLineWithComment ( string &buf, bool withEOL ) {

	buf = "";
	if ( m_fp == NULL ) {
		return NOT_EXIST ;
	}

	int val  ;
	val = fgetc ( m_fp ) ;

	while ( val != EOF ) {
		switch ( val ) {
			case '\n':		// new lines
			case '\r':
			case '\n\r':
			case '\r\n':
				if ( withEOL )
					buf += (char) val ;
				m_currentLine ++ ;
				return SUCCESS ;
				break ;

			default :
				buf += (char) val ;
				break;
			
		}
		val = fgetc ( m_fp ) ;
	}

	m_currentLine ++ ;
	return EOF_REACHED ;
}

dhTextFileIO::RESULT_TYPES dhTextFileIO::getWholeFile ( string &buf ) {
	buf = "" ;

	if ( m_fp == NULL ) {
		return NOT_EXIST ;
	}

	
	int val  ;
	val = fgetc ( m_fp ) ;

	while ( val != EOF ) {
		buf += (char) val ;
			
		val = fgetc ( m_fp ) ;
	}

	return SUCCESS ;
}

std::string  dhTextFileIO::copyWholeFile ( ) {

	

	if ( m_fp == NULL ) {
		return NULL ;
	}

	std::string buf = "" ;

	int val = fgetc ( m_fp ) ;

	while ( val != EOF ) {
		buf += (char) val ;

		val = fgetc ( m_fp ) ;
	}

	return buf ;
	/*
	//const char* mybuf = buf.c_str() ;
//	buf.clear() ;
//	return mybuf ;



	//if ( m_fp == NULL )
	//	return NULL ;

	fpos_t pos = 0 ;
	fsetpos ( m_fp, &pos ) ;
	char *cbuf = new char [ m_fp->_bufsiz ] ;
	int len = fread ( cbuf, sizeof (char), m_fp->_bufsiz, m_fp ) ;
	cbuf [len] = 0 ;
	return cbuf ;
	  */

}

dhTextFileIO::RESULT_TYPES dhTextFileIO::getWord( string line, string &word, unsigned int &plcHolder ) {

	word = "";
	
	if ( plcHolder >= line.size() ) {
		return INDEX_OVERFLOW ;
	}

	// skip first word identifiers

	unsigned int i ;
	while ( plcHolder < line.size() ) {
		for ( i = 0; i < m_wordIdf.size(); i++ ) {
			if ( m_wordIdf[i] == line[plcHolder] ) {
				plcHolder ++ ;
				break ;
			}
		}
		if ( i == m_wordIdf.size() )
			break ;
	}

	while ( plcHolder < line.size() ) {
		for ( i = 0; i < m_wordIdf.size(); i++ ) {
			if ( m_wordIdf[i] == line[plcHolder] ) 
				return SUCCESS ;
		}

		word += line[plcHolder] ;
		plcHolder ++ ;
	}

	return INDEX_OVERFLOW ;
}

string dhTextFileIO::getErrorMsg ( dhTextFileIO::RESULT_TYPES result ) {
	string errMsg = "";

	switch ( result ) {
		case OPEN_ERROR :			// Could not open
			errMsg = "Could not open given file" ;
			break ;
		case NOT_EXIST :			// File not exist
			errMsg = "File Pointer not exist" ;
			break ;
		case EOF_REACHED:		// End Of File reached
			errMsg = "End of file reached" ;
			break ;
		case SUCCESS:			// No error
		default :
			errMsg = "" ;
			break ;
	}

	return errMsg ;
}

void dhTextFileIO::skipCommentLines ( bool val ) 
{
	m_skipCommentLines = val ; 
}

void dhTextFileIO::setNewLineIdf ( char *buf ) 
{
	m_newLineIdf = buf ;
} 

void dhTextFileIO::setCommentIdf ( char *buf ) 
{ 
	m_commentIdf = buf ; 
} 

void dhTextFileIO::setWordSeperator ( char *buf ) 
{
	m_wordIdf = buf ; 
}

