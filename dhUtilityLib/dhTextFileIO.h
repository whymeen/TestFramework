#ifndef DH_TEXTFILE_IO_H
#define DH_TEXTFILE_IO_H

/*
Include Files
*/
#include <stdio.h>

#include "dhCommon.h"
using namespace std;

/*
Description:
Access class for text format files.

Remarks:
Actually I am not working on this class anymore. 
I prefer to use XML files instead of text format files. 
So currently I stopped the development on it. 
Currently it can just read text files. Save functions are not implemented.
*/

class DHUTILITYLIB_API dhTextFileIO 
{
public :
	enum RESULT_TYPES {
		OPEN_ERROR,			// Could not open
		NOT_EXIST,			// File not exist
		EOF_REACHED,		// End Of File reached
		INDEX_OVERFLOW,



		SUCCESS,			// No error
	}  ;

	enum ACCESS_TYPE{
		ACCESS_R,
		ACCESS_W,
		ACCESS_RW
	}  ;

public :
	dhTextFileIO  ( void ) ;
	~dhTextFileIO ( void ) ;



	RESULT_TYPES openFile ( const std::string& fileName, ACCESS_TYPE ) ;
	RESULT_TYPES closeFile (  ) ;
	RESULT_TYPES getWholeLine ( string &buf, bool withEOL = false ) ;
	RESULT_TYPES getWholeFile ( string &buf	) ;
	std::string		copyWholeFile ( ) ;
	RESULT_TYPES getWord ( string line,	string &word, unsigned int& plcHolder ) ;	
	void skipCommentLines ( bool val ) ;
	string getErrorMsg ( RESULT_TYPES result ) ; 
	void setNewLineIdf ( char *buf ) ;
	void setCommentIdf ( char *buf ) ;
	void setWordSeperator ( char *buf ) ;
	int	currentLine ( void ) { return m_currentLine ; };

private :
	
	FILE	*m_fp ;
	string	m_fileName ;

	string	m_commentIdf ;		// comment identifiers default :   '#'
	string	m_wordIdf ;			// word identifier default : " "
	string  m_newLineIdf ;		// new line identifier default : "" 

	bool	m_skipCommentLines ; // default true 

	int		m_currentLine ;

	RESULT_TYPES  getWholeLineWithComment ( string &buf, bool withEOL ) ;
} ;

#endif // DH_TEXTFILE_IO_H
