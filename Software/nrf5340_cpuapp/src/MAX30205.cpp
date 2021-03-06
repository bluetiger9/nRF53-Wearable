//////////////////////////////////////////////////////////////////////////////////////////
//
//    Arduino library for the MAX30205 body temperature sensor breakout board
//
//    Author: Ashwin Whitchurch
//    Copyright (c) 2018 ProtoCentral
//
//    This software is licensed under the MIT License(http://opensource.org/licenses/MIT).
//
//   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT
//   NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
//   IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
//   WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
//   SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
//
//   For information on how to use, visit https://github.com/protocentral/ProtoCentral_MAX30205
/////////////////////////////////////////////////////////////////////////////////////////

#include "drivers/i2c.h"
#include "MAX30205.h"
#include <stdint.h>

MAX30205::MAX30205(const device *i2c_dev) {
  this->i2c_dev = i2c_dev;
}

float MAX30205::getTemperature(void){
	uint8_t readRaw[2] = {0};
    I2CreadBytes(sensorAddress,MAX30205_TEMPERATURE, &readRaw[0] ,2); // read two bytes
	int16_t raw = readRaw[0] << 8 | readRaw[1];  //combine two bytes
    temperature = raw  * 0.00390625;     // convert to temperature
	return  temperature;
}

bool MAX30205::scanAvailableSensors(void){
  bool sensorFound = false;

  uint8_t cmd = 1;
  int error = i2c_write(i2c_dev, &cmd, 1, MAX30205_ADDRESS1);
  if (error == 0){
    sensorAddress = MAX30205_ADDRESS1;
    sensorFound = true;
  }
  
  error = i2c_write(i2c_dev, &cmd, 1, MAX30205_ADDRESS2);
  if(error == 0){
    sensorAddress = MAX30205_ADDRESS2;
    sensorFound = true;
  }

  return sensorFound;
}

void MAX30205::shutdown(void){
  uint8_t reg = I2CreadByte(sensorAddress, MAX30205_CONFIGURATION);  // Get the current register
  I2CwriteByte(sensorAddress, MAX30205_CONFIGURATION, reg | 0x80);
}

void MAX30205::begin(void){
  I2CwriteByte(sensorAddress, MAX30205_CONFIGURATION, 0x00); //mode config
  I2CwriteByte(sensorAddress, MAX30205_THYST , 		 0x00); // set threshold
  I2CwriteByte(sensorAddress, MAX30205_TOS, 			 0x00); //
}

void MAX30205::printRegisters(void){
  printk("TEMP: 0x%2X\n", I2CreadByte(sensorAddress, MAX30205_TEMPERATURE));
  printk("CONF: 0x%2X\n", I2CreadByte(sensorAddress, MAX30205_CONFIGURATION));
  printk("THYST: 0x%2X\n", I2CreadByte(sensorAddress, MAX30205_THYST));
  printk("TOS: 0x%2X\n", I2CreadByte(sensorAddress, MAX30205_TOS));

}

// Wire.h read and write protocols
void MAX30205::I2CwriteByte(uint8_t address, uint8_t subAddress, uint8_t data){
  int res = i2c_reg_write_byte(i2c_dev, sensorAddress, subAddress, data);
  if (0 != res) {
    printk("MAX30205 I2C error: %d", res);
  }
	//Wire.beginTransmission(address);  // Initialize the Tx buffer
//	Wire.write(subAddress);           // Put slave register address in Tx buffer
//	Wire.write(data);                 // Put data in Tx buffer
//	Wire.endTransmission();           // Send the Tx buffer
}

uint8_t MAX30205::I2CreadByte(uint8_t address, uint8_t subAddress){
    uint8_t data;
    int res = i2c_reg_read_byte(i2c_dev, sensorAddress, subAddress, &data);
    if (0 != res) {
      printk("MAX30205 I2C error: %d", res);
    }
    return data;
	//uint8_t data; // `data` will store the register data
	//Wire.beginTransmission(address);
	//Wire.write(subAddress);
	//Wire.endTransmission(false);
	//Wire.requestFrom(address, (uint8_t) 1);
	//data = Wire.read();
	//return data;
}

void MAX30205::I2CreadBytes(uint8_t address, uint8_t subAddress, uint8_t * dest, uint8_t count) 
{    
    int res = i2c_write_read(i2c_dev, sensorAddress, &subAddress, 1, dest, count);
    //int res = i2c_read(i2c_dev, dest, count, sensorAddress);
    if (0 != res) {
      printk("MAX30205 I2C error: %d", res);
    }
	//Wire.beginTransmission(address);   // Initialize the Tx buffer
	// Next send the register to be read. OR with 0x80 to indicate multi-read.
	//Wire.write(subAddress);
	//Wire.endTransmission(false);
	//uint8_t i = 0;
	//Wire.requestFrom(address, count);  // Read bytes from slave register address
	//while (Wire.available())
	//{
	//	dest[i++] = Wire.read();
	//}
}
