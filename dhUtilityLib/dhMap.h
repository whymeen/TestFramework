// ozMap.h: interface for the ozMap class.
//
//////////////////////////////////////////////////////////////////////

#ifndef DH_MAP_H
#define DH_MAP_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "dhCommon.h"

#if 1 // USE STANDARD MAP
#define dhMap std::map

#else // USE DHMAP

template <class TypeObjFirst, class TypeObjSecond >
class DHUTILITYLIB_API dhMap 
{
public:
	class value_type 
	{
	public:
		value_type ( TypeObjFirst f, TypeObjSecond s ) 
		{
			first = f ;
			second = s ;
		}
		~value_type ()
		{
		}
		bool operator == ( const TypeObjFirst& obj )
		{
			return first == obj ;
		}
		TypeObjFirst first ;
		TypeObjSecond second ;
	};
  
	typedef typename std::vector<value_type>::iterator iterator ;
  
	public:
		dhMap()
		{
		}
		virtual ~dhMap()
		{
		}
		void clear () 
		{
			m_list.clear() ;
		}
		iterator begin ( void )
		{
			return m_list.begin() ;
		}
		iterator end () 
		{ 
			return m_list.end() ; 
		}
		iterator insert ( const value_type& val )
		{
			m_list.push_back( val ) ;
			iterator ret = m_list.end() ;
			ret -- ;
			return ( ret ) ;
			
		}
		iterator find ( const TypeObjFirst& key )
		{
			iterator iVec = m_list.begin() ;
			while ( iVec != m_list.end() )
			{
				if ( iVec->first == key )
					break ;
				iVec ++ ;
			}
			return iVec ;
		}
	protected:
		std::vector<value_type> m_list ;
};

#endif

#endif // !defined(DH_MAP_H)
