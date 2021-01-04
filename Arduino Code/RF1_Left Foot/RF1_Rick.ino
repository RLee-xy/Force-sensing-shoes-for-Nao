#include <RF24.h>
#include <RF24Network.h>
#include <SPI.h>
#include "HX711.h"

// Communication part
RF24 radio(10, 9);               // nRF24L01 (CE,CSN)
RF24Network network(radio);      // Include the radio in the network
const uint16_t this_node = 01;   // Address of this node in Octal format ( 04,031, etc)
const uint16_t node01 = 00;  

// Force sensor part
HX711 cell1(5, 4);
HX711 cell2(17, 16);
HX711 cell3(15,14);
HX711 cell4(7, 6);

float val1 = 0; 
float val2 = 0; 
float val3 = 0; 
float val4 = 0; 

float val_adjust1 = 0; 
float val_adjust2 = 0; 
float val_adjust3 = 0; 
float val_adjust4 = 0; 

    
void setup() {
  Serial.begin(115200);
  SPI.begin();
  radio.begin();
  network.begin(90, this_node);  //(channel, node address)
}

void loop() {
  
  val1 = cell1.read(); 
  val2 = cell2.read();
  val3 = cell3.read();
  val4 = cell4.read();
  
//  val_adjust1 = (val1 - 8427784)/(-171433.0f/204); // Individual Calibration Result
//  val_adjust2 = (val2 - 8217875)/(+170117.0f/204); // Individual Calibration Result
//  val_adjust3 = (val3 - 8217545)/(-175206.0f/204); // Individual Calibration Result
//  val_adjust4 = (val4 - 8294472)/(+176251.0f/204); // Individual Calibration Result

//  Serial.print(val1);
//  Serial.print("  ");
//  Serial.print(val2);
//  Serial.print("  ");
//  Serial.print(val3);
//  Serial.print("  ");
//  Serial.println(val4);

//  Serial.print(val_adjust1);
//  Serial.print("  ");
//  Serial.print(val_adjust2);
//  Serial.print("  ");
//  Serial.print(val_adjust3);
//  Serial.print("  ");
//  Serial.println(val_adjust4);

  network.update();
  float datasend[] = {val1,val2,val3,val4};
  RF24NetworkHeader header(node01);     // (Address where the data is going)
  network.write(header, &datasend, sizeof(datasend)); // Send the data

//  delay(20);
}
