#include "FRAM_I2C.h"

FRAM_I2C::FRAM_I2C(uint8_t no_devices)  :
	i2c_addr(I2C_ADDR),
	no_dev(no_devices)
{}

#ifdef TEST_DEVICES
uint8_t FRAM_I2C::begin(void) 
{
	Wire.begin();
	uint8_t devices=0;
	for ( ; devices < no_dev; devices++)
	{
		Wire.beginTransmission(i2c_addr+devices);
		#ifdef TEST_DEVICES_SERIAL
		Serial.print("0x");Serial.print(i2c_addr+devices,HEX);Serial.print("\t");
		#endif
		if (!Wire.endTransmission())
		{
			#ifdef TEST_DEVICES_SERIAL
			Serial.println("exists");
			#endif
		}
		else
		{
			#ifdef TEST_DEVICES_SERIAL
			Serial.println("not found");
			#endif
			break;
		}
	}
	#ifdef TEST_DEVICES_SERIAL
	if (devices != no_dev)
	{
		Serial.print ("not ");
		Serial.print(no_dev);
		Serial.print(" but ");
	}	
	Serial.print(devices);
	Serial.print(" devices used");
	no_dev = devices;
	Serial.print("\taddress space: ");
	Serial.print(getAddrSpace());
	Serial.print("\t in HEX: 0x");
	Serial.println(getAddrSpace(),HEX);
	#else
	no_dev = devices;
	#endif
	return no_dev;
#else
void FRAM_I2C::begin(void) 
{
	Wire.begin();
#endif
}

void FRAM_I2C::clear_all_memory(uint8_t steps)
{
    for (uint8_t a = i2c_addr; a < i2c_addr+no_dev; a++)
	for (uint16_t addr = 0; addr < MEM_SIZE; addr+=steps)
	{
		Wire.beginTransmission(a);
		Wire.write(addr >> 8);
		Wire.write(addr & 0xFF);
		Wire.write( 0x00 );
		Wire.endTransmission();
	}
	
	
}

uint16_t FRAM_I2C::getAddrSpace(void)
{
	return (MEM_SIZE>>2)*no_dev;
}

void FRAM_I2C::write (uint16_t framAddr, uint8_t value) // only every 4th byte is accessabile in this mode
{
	Wire.beginTransmission(i2c_addr|uint8_t(framAddr>>13));
	Wire.write(framAddr >> 6);
	Wire.write(framAddr << 2);
	Wire.write(value);
	Wire.endTransmission();
}

void FRAM_I2C::write(uint16_t framAddr, uint8_t * array, uint8_t len)
{
	Wire.beginTransmission(i2c_addr|uint8_t(framAddr>>13));
	Wire.write(framAddr >> 6);
	Wire.write(framAddr << 2);
	while (len--)
	{
		Wire.write(*(array++));
	}
	Wire.endTransmission();
}

uint8_t FRAM_I2C::read (uint16_t framAddr) // only every 4th byte is accessabile in this mode
{
	Wire.beginTransmission(i2c_addr|uint8_t(framAddr>>13));
	Wire.write(framAddr >> 6);
	Wire.write(framAddr << 2);
	Wire.endTransmission();
	Wire.requestFrom(i2c_addr|uint8_t(framAddr>>13), 1);
	return Wire.read();
}
void FRAM_I2C::read(uint16_t framAddr, uint8_t * array, uint8_t len)
{
	Wire.beginTransmission(i2c_addr|uint8_t(framAddr>>13));
	Wire.write(framAddr >> 6);
	Wire.write(framAddr << 2);
	Wire.endTransmission();
	while (len--)
	{
		Wire.requestFrom(i2c_addr|uint8_t(framAddr>>13), 1);
		*(array++) = Wire.read();
	}
}
