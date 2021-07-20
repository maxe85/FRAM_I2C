#include "FRAM_MULTI_I2C.h"

FRAM_I2C fram(8); // construct witch amount of devices (max 8), need to be addressed in order e.g. 0x50,0x51,0x52 ..

void setup(void) {
  Serial.begin(115200);
  char readBuffer[5];
  readBuffer[sizeof(readBuffer)-1] = 0;
  
  Serial.println("Fram Multi test:");

  // printing number of devices found
  Serial.println(fram.begin());
  delay(500);

  Serial.println("setting the answer to addr 0x0001\n");
  fram.write(0x0001,42);
  delay(500);

  char text[] = "Hello World";
  Serial.println("write 'Hello World!' to address 0x0100\n");
  fram.write(0x0100,text,sizeof(text));
  delay(500);

  Serial.println("writing '?' to last address\n");
  fram.write(fram.getAddrSpace()-1,'?');
  delay(500);
  
  
  Serial.println("print conten of all addresses containing anything:");
  for (uint16_t i=0; i<fram.getAddrSpace(); i++)
  {
    if (fram.read(i))
    {
      Serial.print(i);
      Serial.print("\taccessable byte: ");
      Serial.print(fram.read(i));
      Serial.print("\t all 4 bytes (as char array):\t");
      fram.read(i,readBuffer,sizeof(readBuffer)-1);
      Serial.println(readBuffer);
    }
  }
  Serial.println("done\n");
  delay(1000);
  
  Serial.println("clear all memory");
  fram.clear_all_memory();
  Serial.println("done\n");
  delay(500);

  Serial.println("again: print conten of all addresses containing anything:");
  for (uint16_t i=0; i<fram.getAddrSpace(); i++)
  {
    if (fram.read(i))
    {
      Serial.print(i);
      Serial.print("\taccessable byte: ");
      Serial.print(fram.read(i));
      Serial.print("\t all 4 bytes (as char array):\t");
      fram.read(i,readBuffer,sizeof(readBuffer)-1);
      Serial.println(readBuffer);
    }
  }
  Serial.println("done\n");
  delay(500);

  Serial.println("write single byte again to address 0x0100\n");
  fram.write(0x0100, 'h');
  delay(500);

  Serial.println("again: print conten of all addresses containing anything:");
  for (uint16_t i=0; i<fram.getAddrSpace(); i++)
  {
    if (fram.read(i))
    {
      Serial.print(i);
      Serial.print("\taccessable byte: ");
      Serial.print(fram.read(i));
      Serial.print("\t all 4 bytes (as char array):\t");
      fram.read(i,readBuffer,sizeof(readBuffer)-1);
      Serial.println(readBuffer);
    }
  }
  Serial.println("done\n");
  delay(500);

  Serial.println("clear all memory properly");
  fram.clear_all_memory(1);  //steps =1, default: 4
  Serial.println("done\n");
  delay(500);

  Serial.println("write single byte again to address 0x0100\n");
  fram.write(0x0100, 'h');
  delay(500);

  Serial.println("again: print conten of all addresses containing anything:");
  for (uint16_t i=0; i<fram.getAddrSpace(); i++)
  {
    if (fram.read(i))
    {
      Serial.print(i);
      Serial.print("\taccessable byte: ");
      Serial.print(fram.read(i));
      Serial.print("\t all 4 bytes (as char array):\t");
      fram.read(i,readBuffer,sizeof(readBuffer)-1);
      Serial.println(readBuffer);
    }
  }
  Serial.println("done\n");
  
  fram.write(0x0100,0); // clean up
}

void loop(void)
{
}
