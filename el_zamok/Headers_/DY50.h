/*
 * DY50.h
 *
 * Created: 4/20/2022 9:13:09 PM
 *  Author: Simona
 */ 


#ifndef DY50_H_
#define DY50_H_

#include "Board.h"
#include "UART.h"
#include <string.h>


class DY50
{
	//variables
	public:
	
	protected:
	private:
		UART u;
		

	public:
	DY50();
	~DY50();
	int nacitaj();
	int uploadImage();
	int downloadImage();
	int Image2Tz();
	int loadTemplate(int pageId1, int pageId2);
	int searchForTemplate();
	int fastSearch();
	protected:
}; //Led



#endif /* DY50_H_ */