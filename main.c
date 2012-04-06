
#include "ds18x20.h"
#include "basic_types.h"
#include "return_codes.h"

#define REQUIRED_TEMPERATURE 40
#define AVERAGE_LENGTH 10

int main(void) {
	int16_t aT, temperature, temperatures[AVERAGE_LENGTH];
	int8_t e;
	uint8_t measurementCntr, errorCntr;
	uint8_t loopCntr;

	measurementCntr=0;
	errorCntr=0;

	while(TRUE) {
		if(ds18x20_read_temp(&temperature,&e) == RES_OK) {
			/*** temperature is correct, you can do something with it ***/
			temperatures[measurementCntr] = temperature;
			measurementCntr += 1;
			measurementCntr %= AVERAGE_LENGTH;

			/*** count average temperature ***/
			loopCntr = AVERAGE_LENGTH;
			while(loopCntr) {
				aT += temperatures[loopCntr];
				loopCntr--;
			}
			aT = aT / AVERAGE_LENGTH;	

			/*** update LED display ***/
			

			/*** check and turn on/off relay ***/
			if(aT > (REQUIRED_TEMPERATURE + 1)) {
				// turn off
			}
			if(aT < (REQUIRED_TEMPERATURE - 1)) {
				// turn on
			}


			/*** clear error counter ***/
			errorCntr =0;
		}
		else {
			errorCntr++;
			if(errorCntr == 10) {
				// display fault
				// - -
			}
		}
	}
}
