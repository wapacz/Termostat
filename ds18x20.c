
#include "ds18x20.h"


uint8_t ds18x20_rom[8];
uint8_t ds18x20_sp[9];

void ds18x20_init()
{
	//only for DS18B20 (not for DS18S20)
	ow_command(COMMAND_WRITE_SP,NULL); // write 
	ow_byte_write(0x00); //Th
	ow_byte_write(0x00); //Tl
	ow_byte_write(0x7F); //config
}

uint8_t ds18x20_read_temp(int16_t *t, int8_t *e) 
{
	uint8_t i;

	if(ow_command(COMMAND_CONVERT_T,NULL) == RES_FAULT) return RES_FAULT;

	ow_strong_pullup_line();
	_delay_ms(1500); //
	ow_normal_line();

	if(ow_command(COMMAND_READ_SP,NULL) == RES_FAULT) return RES_FAULT;

	for (i=0; i<9; i++)	
		ds18x20_sp[i] = ow_byte_read();

	if(crc8(ds18x20_sp,9) == CRC_OK)
	{
		*t = ((ds18x20_sp[1] << 8) | (ds18x20_sp[0])) / 16;
		*e = ((ds18x20_sp[0] & M00001111) * 10) / 16;
		return RES_OK;
	}
	else
	{
		//*t = 127;
		//*e = 0;
		return RES_FAULT;
	}
}
