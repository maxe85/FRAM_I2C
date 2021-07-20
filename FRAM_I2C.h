/*
*  Simple ibrary for accessing multiple FM24C256 devices adressed with their hardware pins A0 - A2 (pulled high)
*  	
*  the devices need to be adressed in order, since the library will iterate incrementing from first address 0x50 until 0x57
*
*  in order to use only 16bit addresses, only every 4th byte cann be accessed in single read/write methodes
*
*  to acess all data use the buffer read/write methodes
*  
*  Author: maxe85
*/
#ifndef FRAM_I2C_H_
#define FRAM_I2C_H_

#include <Arduino.h>
#include <Wire.h>

#define I2C_ADDR (0x50)    /* default */
#define MEM_SIZE 32768     // in bytes

#define TEST_DEVICES  // use this for device check, begin() will return number of used devices
#define TEST_DEVICES_SERIAL // use this for serial output from begin() methode if TEST_DEVICES is defined
#define DEV_MODE


class FRAM_I2C {
	public:
		FRAM_I2C(uint8_t no_devices); // construct the FRAM object with the numer of devices connected
			// will ignore higher numbers than no_devices found (exept there is any device using the I2C adress 0x58)
#ifdef TEST_DEVICES
		uint8_t begin(void);
#else
		void begin(void);
#endif
		void clear_all_memory(uint8_t steps = 4);
		uint16_t getAddrSpace(void);      		// will return 0 if eight devices can be used: use whole 16bit addresses
		void write (uint16_t framAddr, uint8_t value);	// write one adressable byte
		void write (uint16_t framAddr, uint8_t * array, uint8_t len);	// write a buffer beginning with adressable byte, use len == 4*x ! 
		uint8_t read  (uint16_t framAddr);				// read single adressable byte
		void read(uint16_t framAddr, uint8_t * array, uint8_t len);	// read buffer, beginning with adressable byte
	private:
		const uint8_t i2c_addr;
		uint8_t no_dev;
	
};

#endif
