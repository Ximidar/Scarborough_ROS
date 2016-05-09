#include <Wire.h>

#include "i2c_dealer.h"
#include "PID_v1.h"

i2c i2c1;


#define SLAVE 0x04 

//variables for the i2c exchange
int reference [4] = {0,0,0,0};
bool positive;
String sender = "";
int reg = 0;

//variables for the PID

double m1_desired,  m2_desired,  m3_desired,  m4_desired,  m5_desired,  m6_desired,
       m1_in,       m2_in,       m3_in,       m4_in,       m5_in,       m6_in,
       m1_out,      m2_out,      m3_out,      m4_out,      m5_out,      m6_out;

 //we can set this for each motor if nessesary. for right now we will only set one setting for all motors
double kp = 1, ki = 0.05, kd = 0.25;


//left / right
PID m1(&m1_in, &m1_out, &m1_desired, kp, ki, kd, DIRECT);
PID m2(&m2_in, &m2_out, &m2_desired, kp, ki, kd, DIRECT);

//dive motors
PID m3(&m3_in, &m3_out, &m3_desired, kp, ki, kd, DIRECT);
PID m4(&m4_in, &m4_out, &m4_desired, kp, ki, kd, DIRECT);
PID m5(&m5_in, &m5_out, &m5_desired, kp, ki, kd, DIRECT);
PID m6(&m6_in, &m6_out, &m6_desired, kp, ki, kd, DIRECT);


void setup() {
  
  Wire.begin(SLAVE); //set up the arduino as a slave
  Wire.onReceive(readROS); //function for handling receiving instructions
  Wire.onRequest(writeROS); //function for handling writing to ROS


  //initial desireds for all motors
  m1_desired = 0;
  m2_desired = 0;
  m3_desired = 0;
  m4_desired = 0;
  m5_desired = 0;
  m6_desired = 0;

  //set limits for all motors 
  m1.SetOutputLimits(-32000, 32000);
  m2.SetOutputLimits(-32000, 32000);
  m3.SetOutputLimits(-32000, 32000);
  m4.SetOutputLimits(-32000, 32000);
  m5.SetOutputLimits(-32000, 32000);
  m6.SetOutputLimits(-32000, 32000);

  //turn on all PID calcutrons
  m1.SetMode(AUTOMATIC);
  m2.SetMode(AUTOMATIC);
  m3.SetMode(AUTOMATIC);
  m4.SetMode(AUTOMATIC);
  m5.SetMode(AUTOMATIC);
  m6.SetMode(AUTOMATIC);

}

void loop(){

  //get reference for left / right motors
  m1_in = i2c1.get_y();
  m2_in = i2c1.get_y();

  //get reference for dive motors 
  m3_in = i2c1.get_r();
  m4_in = i2c1.get_r();
  m5_in = i2c1.get_r();
  m6_in = i2c1.get_r();

  m1.Compute();
  m2.Compute();
  m3.Compute();
  m4.Compute();
  m5.Compute();
  m6.Compute();

  m1.SetTunings(kp, ki, kd);
  m2.SetTunings(kp, ki, kd);
  m3.SetTunings(kp, ki, kd);
  m4.SetTunings(kp, ki, kd);
  m5.SetTunings(kp, ki, kd);
  m6.SetTunings(kp, ki, kd);

    
}

// read ROS is used to write to the registers that are in the switch statement.
void readROS(int byteC){
  int count = 0;
  for(int i = 0; i < 4 ; i++){
     reference[i] = 0;
  }

  //This while loop reads all available bytes over the i2c bus then stores them into reference[]
  //reference is composed of three values, reference[0] is the addressed register, then reference[1] and reference[2] are the numbers for the register
  //look further on to see how to extract the number out of reference.
  while(Wire.available()){

      reference[count] = Wire.read();
      count++;

  }

  
    switch(reference[0]){
      ///////////////////////////////////Write Requests//////////////////////////////


      ///////////////////////////////////YPR WRITES/////////////////////////////////
     //first number for yaw
      case 0:       
        i2c1.first_num(YAW, reference);        
        break;
        
     //second number for yaw
      case 1:        
        i2c1.second_num(YAW, reference);        
        break;
        
      //first number for pitch
      case 2:        
        i2c1.first_num(PITCH, reference);        
        break;
        
      //second number for pitch
      case 3:        
        i2c1.second_num(PITCH, reference);        
        break;
        
      //first number for roll
      case 4:        
        i2c1.first_num(ROLL, reference);        
        break;
        
      //second number for roll
      case 5:        
        i2c1.second_num(ROLL, reference);        
        break;


      ///////////////////////////////////////////PID WRITES///////////////////////////////
      //update kp
      case 6:        
        kp = (double)(reference[1] * 256) + reference[2];        
        break;
        
      //update ki
      case 7:        
        ki = (double)(reference[1] * 256) + reference[2];        
        break;
        
      //update kd
      case 8:        
        kd = (double)(reference[1] * 256) + reference[2];        
        break;


      /////////////////////////////////DESIRED WRITES///////////////////////////////
      //update desired yaw
      case 9:        
        m1_desired = (double)(reference[1] * 256) + reference[2];
        m2_desired = (double)(reference[1] * 256) + reference[2];
        break;

      //update desired depth
      case 10:        
        m3_desired = (double)(reference[1] * 256) + reference[2];
        m4_desired = (double)(reference[1] * 256) + reference[2];
        m5_desired = (double)(reference[1] * 256) + reference[2];
        m6_desired = (double)(reference[1] * 256) + reference[2];

      ////////////////////////////Read Requests///////////////////////////  
      //motor1
      case 51:
        reg = 1;        
        break;
      //motor2
      case 52:
        reg = 2;        
        break;
      //motor3
      case 53:
        reg = 3;        
        break;
      //motor4
      case 54:
        reg = 4;        
        break;
      //motor5
      case 55:
        reg = 5;        
        break;
      //motor 6
      case 56:
        reg = 6;        
        break;


      //////////////////////////////////////////DEFAULT///////////////////////////////////////////////////// 
      //in case something messes up heres a default value that will be hit
      default:          
        break;
    }
  
}

//This function writes motor values to ROS with strings
void writeROS(){
 
  sender = "";

  //depending on the value of reg different values will be sent
  if(reg == 1){
    sender = "M1:" + String(m1_out,0) + ";";  
    Wire.write(sender.c_str());
  }
  if(reg == 2){
     sender = "M2:"+ String(m2_out,0) + ";";
     Wire.write(sender.c_str());
  }
  if(reg == 3){
    sender = "M3:" + String(m3_out,0) + ";";
    Wire.write(sender.c_str());
  }
  if(reg == 4){
    sender = "M4:" + String(m4_out,0) + ";";
    Wire.write(sender.c_str());
  }
  if(reg == 5){
    sender = "M5:" + String(m5_out,0) + ";";
    Wire.write(sender.c_str());
  }
  if(reg == 6){
    sender = "M6:" + String(m6_out,0) + ";";
    Wire.write(sender.c_str());
  }

    
}



