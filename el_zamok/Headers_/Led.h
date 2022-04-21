/*
 * Led.h
 *
 * Created: 4/19/2022 10:59:42 AM
 *  Author: Simona
 */ 


#ifndef __LED_H__
#define __LED_H__

#include "Board.h"

class Led
{
	//variables
	public:

	protected:
	private:
	//Led( const Led &c );
	//Led& operator=( const Led &c );

	public:
	Led();
	~Led();
	void set(bool r, bool g, bool b);
	protected:
}; //Led

#endif //__LED_H__