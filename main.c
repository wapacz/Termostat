
#include "ds18x20.h"
#include "basic_types.h"
#include "return_codes.h"
#include "led_display.h"
#include "relay.h"

#define REQUIRED_TEMPERATURE 40
#define AVERAGE_LENGTH 5

int main(void) {
	int16_t aT, temperature, temperatures[AVERAGE_LENGTH];
	int8_t e;
	uint8_t measurementCntr, errorCntr;
	uint8_t loopCntr;

	aT=0;
	measurementCntr=0;
	errorCntr=0;
	for(loopCntr=0; loopCntr<AVERAGE_LENGTH; loopCntr++) {
		temperatures[loopCntr] = 0;
	}

	ds18x20_init();

	DisplayDashes();

	//TurnOn();

	/*
	loopCntr =0;
	while(TRUE) {
		loopCntr++;
		loopCntr%=99;
		DisplayDigit(loopCntr);
		_delay_ms(500);
	}
	*/
	while(TRUE) {
		if(ds18x20_read_temp(&temperature,&e) == RES_OK) {
			/*** temperature is correct, you can do something with it ***/
			temperatures[measurementCntr] = temperature;
			measurementCntr += 1;
			measurementCntr %= AVERAGE_LENGTH;

			/*** count average temperature ***/
			aT = 0;
			for(loopCntr=0; loopCntr<AVERAGE_LENGTH; loopCntr++)
				aT += temperatures[loopCntr];
			aT = aT / AVERAGE_LENGTH;	

			/*** update LED display ***/
			DisplayDigit(aT);

			/*** check and turn on/off relay ***/
			if(aT > (REQUIRED_TEMPERATURE)) {
				TurnOff();
			}
			if(aT < (REQUIRED_TEMPERATURE)) {
				TurnOn();
			}


			/*** clear error counter ***/
			errorCntr =0;
		}
		else {
			errorCntr++;
			//if(errorCntr == 10) {
				// display fault
				DisplayDashes();
			//}
		}
	}
}
