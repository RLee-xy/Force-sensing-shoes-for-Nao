#include <RF24.h>
#include <RF24Network.h>
#include <SPI.h>
#include<ros.h> 
#include<nao_shoe/SensorL.h>
#include<nao_shoe/SensorR.h>

// Define wireless parameters
RF24 radio(10, 9);               // nRF24L01 (CE,CSN)
RF24Network network(radio);      // Include the radio in the network
const uint16_t this_node = 00;   // Address of our node in Octal format ( 04,031, etc)
const uint16_t node01 = 01; 
const uint16_t node02 = 02; 

// Define Ros message
ros::NodeHandle nh;  
nao_shoe::SensorL SensorL_msg;
nao_shoe::SensorR SensorR_msg;
ros::Publisher pub1("SensorL", &SensorL_msg);
ros::Publisher pub2("SensorR", &SensorR_msg);

void setup() {
  Serial.begin(57600);

  //setup wireless
  SPI.begin();
  radio.begin();
  network.begin(90, this_node); //(channel, node address)

  // set up publisher for ros
  nh.initNode();  
  nh.advertise(pub1);
  nh.advertise(pub2);
}

void loop() {
  network.update();
  while ( network.available() ) {     // Is there any incoming data?
    RF24NetworkHeader header;
    
    float incomingData[4];
    
    network.read(header, &incomingData, sizeof(incomingData));
    
    if(header.from_node == 01){
      
      SensorL_msg.force1 = incomingData[0];
      SensorL_msg.force2 = incomingData[1];
      SensorL_msg.force3 = incomingData[2];
      SensorL_msg.force4 = incomingData[3];

      Serial.print("ForceL: ");
      Serial.print(SensorL_msg.force1);
      Serial.print(", ");
      Serial.print(SensorL_msg.force2);
      Serial.print(", ");
      Serial.print(SensorL_msg.force3);
      Serial.print(", ");
      Serial.println(SensorL_msg.force4);

      pub1.publish(&SensorL_msg);
  
    }


    if(header.from_node == 02){
      
      SensorR_msg.force1 = incomingData[0];
      SensorR_msg.force2 = incomingData[1];
      SensorR_msg.force3 = incomingData[2];
      SensorR_msg.force4 = incomingData[3];

      Serial.print("ForceR: ");
      Serial.print(SensorR_msg.force1);
      Serial.print(", ");
      Serial.print(SensorR_msg.force2);
      Serial.print(", ");
      Serial.print(SensorR_msg.force3);
      Serial.print(", ");
      Serial.println(SensorR_msg.force4);

      pub2.publish(&SensorR_msg);
  
    }
    nh.spinOnce();
//    delay(100);
  }
}
