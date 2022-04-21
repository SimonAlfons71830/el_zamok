/*
 * el_zamok.cpp
 *
 * Created: 4/20/2022 8:31:35 PM
 * Author : Simona
 */ 

#include <avr/io.h>
#include "Headers_/UART.h"
#include "Headers_/Led.h"
#include <string.h>
#include "Headers_/DY50.h"
#include "Headers_/Zamok.h"


int main(void)
{
	Zamok el_lock;
	Led rgb;
	
	//zopnutie tranzistoru na snimaci
	sbi(DDRC, SNIMAC);
	sbi(DDRD,R_LED);
	sbi(DDRD,B_LED);
	sbi(DDRD,G_LED);
	sbi(DDRD, ZAMOK);
	cbi(PORTC,SNIMAC);
	_delay_ms(500);
 
	DY50 snimac;
	
	
	while(true){
		_delay_ms(500);
		rgb.set(0,0,0);
		int s1 = snimac.nacitaj();	
		if (s1 == 0x00)
		{
			//fingerprint detected - green
			//rgb.set(1,1,0);
			//_delay_ms(500);
					
					int s4 = snimac.Image2Tz();
					if (s4 == 0x00)
					{
						//generate character file complete
						int s5 = snimac.fastSearch();
						if (s5 == 0x00)
						{
							//naslo match 
							rgb.set(0,1,0);
							_delay_ms(500);
							el_lock.odomkni();
						}else{
							rgb.set(1,1,1);
							_delay_ms(500);
						}
				
			} else			 
			{
				//fail to convert data
				rgb.set(1,0,1);
				_delay_ms(500);
				if (s4 == 0x01)
				{
					rgb.set(1,1,1);
					_delay_ms(500);
				}else if (s4 == 0x06)
				{
					rgb.set(0,1,1);
					_delay_ms(500);
				}else if (s4 == 0x07)
				{
					rgb.set(0,1,0);
				} else{
					rgb.set(0,0,0);
				}
				
			}
		} else if (s1 == 0x02)
		{
			//fingerprint not detected - blue
			rgb.set(0,0,1);
			_delay_ms(500);
		}else{
			//else - red - error reading
			rgb.set(1,0,0);
			_delay_ms(500);
		}
		
	}

}

