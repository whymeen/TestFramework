

#ifndef DH_FLOATING_H
#define DH_FLOATING_H

/*******************************************************************************
During performance testing I noticed that almost %8 of my game's time was spent
in the _ftol function converting floating point numbers to integers. While my
game does an extreme amount of such conversions, this may effect other games
to a lesser degree. The inline ASM functions below are designed to speed up
various types of floating point to integral conversions.
When a floating point number is cast to an integer, ANSI C requires that the
integer be truncated. In MS VC this is done by the _ftol library function.
In order to truncate, the _ftol function is forced to change the Intel FPU
from the default rounding mode of "round to nearest" (RC field of 00B) to
the "round toward zero" mode (RC field of 11B) then back again. This FPU
mode switching is very slow.
The helper functions below use rounding conversions for specific purposes
instead of truncating conversions. This is much faster since the FPU's mode
does not need to be changed. Since these funcitons are inlined the
conversions are even faster because _ftol is a libary function call.
IMPORTANT NOTES:
1) These functions do not have the same behavior as standard arithmetic
rounding. 'fist' uses the default FPU rounding mode which rounds to the
nearest even number. So 0.5 rounds to 0.0 while 1.5 rounds to 2.0. This
may not always be desirable! The FPU could be set to "round up" mode
and back, but that would kill performance. Just add 0.5 and cast instead.
2) Even if "round to the nearest" is OK, rounding in general is not
always an acceptable float to integer conversion. Know your code before
using these functions.
3) This code has been compiled and tested using VC6. The ASSERT calls
are place holders and will not compile by default.
*******************************************************************************/

#include "DHCommon.h"

#include "limits.h"

class DHUTILITYLIB_API dhFloating {
protected:
	dhFloating () {};
	~dhFloating () {};

	//static const double m_maxBool ;
	
public:
	/*******************************************************************************
	Rounding from a float to the nearest integer can be done several ways.
	Calling the ANSI C floor() routine then casting to an int is very slow.
	Manually adding 0.5 then casting to an int is also somewhat slow because
	truncation of the float is slow on Intel FPUs. The fastest choice is to
	use the FPU 'fistp' instruction which does the round and conversion
	in one instruction (not sure how many clocks). This function is almost
	10x faster than adding and casting.
	Caller is expected to range check 'v' before attempting to round.
	Valid range is INT_MIN to INT_MAX inclusive.
	*******************************************************************************/
	static int DHUTILITYLIB_API Round ( double v ) ;
	
	
	/*******************************************************************************
	Same behavior as Round, except that PRound returns and unsigned value
	(and checks 'v' for being positive in debug mode). This method can
	be used for better type safety if 'v' is known to be positive.
	Caller is expected to range check 'v' before attempting to round.
	Valid range is 0 to UINT_MAX inclusive.
	*******************************************************************************/
	static  unsigned DHUTILITYLIB_API PRound( double v ) ;

	/*******************************************************************************
	To check if a double is actually an integral value you could
	cast the double to an int (which used the slow ANSI C _ftol function)
	then subtracted the int from the original double and tested for zero. This
	is fairly slow. The code below produces the same result but it faster
	because a rounding float to int conversion is used. I'm actually not
	sure if the code below is optimal but I profiled several variations and
	this was the fastest...
	Returns true if 'v' is a valid integer in the range of INT_MIN to INT_MAX
	inclusive and fills 'i' with the integer
	Returns false if 'v' is not an integer.
	There is no need to range check 'v' before calling IsInteger
	*******************************************************************************/
	static bool DHUTILITYLIB_API IsInteger( double v, int *i ) ;

	
	/*******************************************************************************
	Identical to IsInteger but checks 'v' for a more restrictive range.
	Returns true if 'v' is an intergal value and between 0 and USHRT_MAX inclusive.
	Unlike Round this method can be called with a negative value.
	Returns true if 'v' is a valid integer in the range of 0 to USHRT_MAX
	inclusive and fills 'i' with the integer
	Returns false if 'v' is not an index.
	There is no need to range check 'v' before calling IsIndex
	*******************************************************************************/
	static bool DHUTILITYLIB_API IsIndex( double v, int *i ) ;

	/*******************************************************************************
	Used to avoid errors from precision limitations when converting a double to
	a boolean. Converts the argument to a positive then compares the
	result to a small double that is the maximum allowed value that is considered
	false. This technique is about 8 times faster than using the C runtime
	fabs() function because like _ftol fabs() changes FPU control flags.
	Returns true if 'v' is within or at +- 1.0e-10 of zero
	Returns false if 'v' is outside +- 1.0e-10 of zero
	There is no need to range check 'v' before calling IsIndex
	*******************************************************************************/
	static bool DHUTILITYLIB_API ToBool( double v ) ;


} ;



__forceinline int dhFloating::Round( double v )
{
	//@todo: ASSERT not defined ...
	//ASSERT( v >= INT_MIN && v <= INT_MAX );
	int result;
	__asm
	{
		fld v ; Push 'v' into st(0) of FPU stack
			fistp result ; Convert and store st(0) to integer and pop
	}
	return result;
}


__forceinline unsigned dhFloating::PRound( double v )
{
	//@todo: ASSERT not defined ...
	//ASSERT( v >= 0 && v <= UINT_MAX );
	unsigned result;
	__asm
	{
		fld v ; Push 'v' into st(0) of FPU stack
			fistp result ; Convert and store st(0) to integer and pop
	}
	
	return result;
}


// Ignore warning about not returning a value
#pragma warning( disable: 4035 )

__forceinline bool dhFloating::IsInteger( double v, int *i )
{
	if( v < (double)INT_MIN || v > (double)INT_MAX )
		return false;
	// Using a local int to store conversions then reloading
	// it is faster than doing multiple conversions.
	int local;
	__asm
	{
		fld v ; Push 'v' into st(0) of FPU stack
			fist local ; Convert and store st(0) to integer
			fild local ; Push integer to st(0)
			fcompp ; Compare st(0) and st(1) then pop twice
			fnstsw ax ; Moves FPU code flags to AX (AH) register
			test ah,40h ; Test if AH is 40h (meaning st(0) == st(1) )
			je SetF ; Jump to SetF if test was false
			mov edx,i ; Move local to *i
			mov eax,local
			mov [edx],eax
			mov al,1 ; Set return value to true
			jmp Bye ; Jump to exit
	SetF:
		xor al,al ; Set return value to false
	Bye:
	}
}

__forceinline bool dhFloating::IsIndex( double v, int *i )
{
	// Change the max value to suite your needs.
	if( v < 0.0 || v > (double)USHRT_MAX )
		return false;
	// Using a local int to store conversions then reloading
	// it is faster than doing multiple conversions.
	int local;
	__asm
	{
		fld v ; Push 'v' into st(0) of FPU stack
			fist local ; Convert and store st(0) to integer
			fild local ; Push integer to st(0)
			fcompp ; Compare st(0) and st(1) then pop twice
			fnstsw ax ; Moves FPU code flags to AX (AH) register
			test ah,40h ; Test if AH is 40h (meaning st(0) == st(1) )
			je SetF ; Jump to SetF if test was false
			mov edx,i ; Move local to *i
			mov eax,local
			mov [edx],eax
			mov al,1 ; Set return value to true
			jmp Bye ; Jump to exit
	SetF:
		xor al,al ; Set return value to false
	Bye:
	}
}

const double __m_maxBool = 1.0e-10;
__forceinline bool dhFloating::ToBool( double v )
{
	__asm
	{
		fld v ; Push 'v' into st(0) of FPU stack
			fabs ; Drop the sign of st(0)
			fcomp __m_maxBool; Compare st(0) to __m_maxBool
			fnstsw ax ; Moves FPU code flags to AX (AH) register
			test ah,41h ; Test if AH is 40h or 1h (meaning st(0) <= __m_maxBool)
			je SetF ; Jump to SetF if test was false
			xor al,al ; Set return value to false (since 'v' is 0 or very small)
			jmp Bye ; Jump to exit
	SetF:
		mov al,1 ; Set return value to true
	Bye:
	}
}

#pragma warning( default: 4035 )


#endif // DH_FLOATING_H