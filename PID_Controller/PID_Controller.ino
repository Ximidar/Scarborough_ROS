#include <Wire.h>
#include <math.h>
#include "i2c_dealer.h"

i2c i2c1;

#define SLAVE 0x04 


int reference [4] = {0,0,0,0};
bool switcher;
bool positive;
double y = 0;
String sender = "";
int reg = 0;

void setup() {
  
  Wire.begin(SLAVE);
  Wire.onReceive(readROS);
  Wire.onRequest(writeROS);
   
   

}

void loop(){

}


void readROS(int byteC){
  int count = 0;
  for(int i = 0; i < 4 ; i++){
     reference[i] = 0;
  }


  while(Wire.available()){

      reference[count] = Wire.read();
      count++;

    }
  switcher = true;
  while(switcher == true){
    switch(reference[0]){

     //first number for yaw
      case 0:       
        i2c1.first_num(YAW, reference);
        switcher = false;
        break;
     //second number for yaw
      case 1:        
        i2c1.second_num(YAW, reference);
        switcher = false;
        break;
      //first number for pitch
      case 2:        
        i2c1.first_num(PITCH, reference);
        switcher = false;
        break;
      //second number for pitch
      case 3:        
        i2c1.second_num(PITCH, reference);
        switcher = false;
        break;
      //first number for roll
      case 4:        
        i2c1.first_num(ROLL, reference);
        switcher = false;
        break;
      //second number for roll
      case 5:        
        i2c1.second_num(ROLL, reference);
        switcher = false;
        break;
      //read request for yaw
      case 50:
        //writeROS();
        reg = 1;
        switcher = false;
        break;
      //read request for pitch
      case 51:
        //writeROS();
        reg = 2;
        switcher = false;
        break;
      //read request for roll
      case 52:
        //writeROS();
        reg = 3;
        switcher = false;
        break;
      default:
        Serial.print("Default hit error is number: ");
        Serial.println(reference[0]);
        switcher = false;
        break;
    }
  }
}

void writeROS(){
 
  sender = "";

  //depending on the value of reg different values will be sent
  if(reg == 1){
    sender = "M1:" + String(i2c1.get_y(),3) + ";";  
    Wire.write(sender.c_str());
  }
  if(reg == 2){
     sender = "M2:"+ String(i2c1.get_p(),3) + ";";
     Wire.write(sender.c_str());
  }
  if(reg == 3){
    sender = "M3:" + String(i2c1.get_r(),3) + ";";
    Wire.write(sender.c_str());
  }

    
}



