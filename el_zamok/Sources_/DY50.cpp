/*
 * DY50.cpp
 *
 * Created: 4/21/2022 12:08:41 PM
 *  Author: Simona
 */ 

#include "../Headers_/DY50.h"


DY50::DY50()
{

}

DY50::~DY50()
{

}


int DY50::nacitaj()
{
	uint8_t getImmagemessage[] = {0xEF, 0x01, 0xFF, 0xFF, 0xFF, 0xFF, 0x01, 0x00, 0x03, 0x01, 0x00, 0x05};
	uint8_t getImageResponse[12];
	memset(getImageResponse,0,12);
	for (int j =0 ; j< 12; j++)
	{
		u.sendChar(getImmagemessage[j]);
	}
	while(u.recieveChar() != 0xef){
	}
	getImageResponse[0] = 0xef;
		for(int i=1; i < 12; i++)
		{
			getImageResponse[i] = u.recieveChar();
		}
return getImageResponse[9];
}

int DY50::uploadImage()
{
	uint8_t upImageMesage[] = {0xEF, 0x01, 0xFF, 0xFF, 0xFF, 0xFF, 0x01, 0x00, 0x03, 0x0A, 0x00, 0x0E};
	uint8_t upImageResponse[12];
	memset(upImageResponse,0,12);

	for (int j =0 ; j< 12; j++)
	{
		u.sendChar(upImageMesage[j]);
	}
	while(u.recieveChar() != 0xef){
	}
	upImageResponse[0] = 0xef;
	for(int i=1; i < 12; i++)
	{
		upImageResponse[i] = u.recieveChar();
	}
return upImageResponse[9];
}

int DY50::downloadImage()
{
	uint8_t downImageMesage[] = {0xEF, 0x01, 0xFF, 0xFF, 0xFF, 0xFF, 0x01, 0x00, 0x03, 0x0b, 0x00, 0x0F};
	uint8_t downImageResponse[12];
	memset(downImageResponse,0,12);

	for (int j =0 ; j< 12; j++)
	{
		u.sendChar(downImageMesage[j]);
	}
	while(u.recieveChar() != 0xef){
	}
	downImageResponse[0] = 0xef;
	for(int i=1; i < 12; i++){
		downImageResponse[i] = u.recieveChar();
	}

	return downImageResponse[9];

}

int DY50::Image2Tz()
{
	uint16_t checksum;
	
	uint8_t image2TzMessage[] = {0xEF, 0x01, 0xFF, 0xFF, 0xFF, 0xFF, 0x01,0x00, 0x04, 0x02, 0x01};// charbuffer1 = 0x01
	uint8_t image2TzResponse[12];
	memset(image2TzResponse,0,12);
	checksum = image2TzMessage[6] + image2TzMessage[7]+ image2TzMessage [8] +  image2TzMessage[9]+ image2TzMessage[10];
	for (int j =0 ; j< 11; j++)
	{
		u.sendChar(image2TzMessage[j]);
	}
	u.sendChar(checksum << 8 );
	u.sendChar(checksum&0xff);
	
	while(u.recieveChar() != 0xef){
	}
	image2TzResponse[0] = 0xef;
	for(int i=1; i < 12; i++){
		image2TzResponse[i] = u.recieveChar();
	}
return image2TzResponse[9];	
}
/*
int DY50::loadTemplate(int pageId1, int pageId2) 
{
uint8_t image2TzMessage[] = {0xEF, 0x01, 0xFF, 0xFF, 0xFF, 0xFF, 0x01, 0x00, 0x06, 0x07, 0x02, pageId1, pageId2, CHECKSUM 2B}; //checksum? charbuffer2 = 0x02
uint8_t image2TzResponse[12];
memset(image2TzResponse,0,12);

for (int j =0 ; j< 15; j++)
{
	u.sendChar(image2TzMessage[j]);
}
while(u.recieveChar() != 0xef){
}
image2TzResponse[0] = 0xef;
for(int i=1; i < 12; i++){
	image2TzResponse[i] = u.recieveChar();
}

return image2TzResponse[9];
}
*/

int DY50::fastSearch()
{
	uint16_t packagelength; 
	uint16_t checksum;
	//0x1b - fingerprint_hispeedsearch 
	packagelength =	8;
	//comand packets + data packets + checksum(2B)
	uint8_t paket[] = {0xef,0x01, 0xFF, 0xFF, 0xFF, 0xFF, 0x01, packagelength << 8, packagelength&0xff, 0x1b, 0x01, 0x00, 0x00,0x00,0xA3 }; 
		//instruction code - 0x1b, 0x01, 0x00, 0x00,0x00,0xA3
		//package identifier for search - 0x01
	checksum = paket[6] + paket[7]+ paket[8] +paket[9]+paket[10]+paket[11] +paket[12]+paket[13]+paket[14];
		// sum of package identifier, package length + package contens
	uint8_t respond[16]; 
	for (int j =0 ; j< 15; j++)
	{
		u.sendChar(paket[j]);
	}
	u.sendChar(checksum << 8);
	u.sendChar(checksum&0xff );

	while(u.recieveChar() != 0xef){
	}
	respond[0] = 0xef;
	for(int i=1; i < 16; i++){
		respond[i] = u.recieveChar();
	}
	
	//na 9 confirmation
	return respond[9];

}
