#include <Wire.h>

#include "i2c_dealer.h"
#include "PID_v1.h"

i2c i2c1;


#define SLAVE 0x04 

//variables for the i2c exchange
int reference [4] = {0,0,0,0};
bool switcher;
bool positive;
String sender = "";
int reg = 0;

//variables for the PID

double m1_desired,  m2_desired,  m3_desired,  m4_desired,  m5_desired,  m6_desired,
       m1_in,       m2_in,       m3_in,       m4_in,       m5_in,       m6_in,
       m1_out,      m2_out,      m3_out,      m4_out,      m5_out,      m6_out;

double kp = 1, ki = 0.05, kd = 0.25; //we can set this for each motor if nessesary. for right now we will only set one setting for all motors


//left / right
PID m1(&m1_in, &m1_out, &m1_desired, kp, ki, kd, DIRECT);
PID m2(&m2_in, &m2_out, &m2_desired, kp, ki, kd, DIRECT);

//dive motors
PID m3(&m3_in, &m3_out, &m3_desired, kp, ki, kd, DIRECT);
PID m4(&m4_in, &m4_out, &m4_desired, kp, ki, kd, DIRECT);
PID m5(&m5_in, &m5_out, &m5_desired, kp, ki, kd, DIRECT);
PID m6(&m6_in, &m6_out, &m6_desired, kp, ki, kd, DIRECT);


void setup() {
  
  Wire.begin(SLAVE);
  Wire.onReceive(readROS);
  Wire.onRequest(writeROS);


  //initial desireds for all motors
  m1_desired = 0;
  m2_desired = 0;
  m3_desired = 0;
  m4_desired = 0;
  m5_desired = 0;
  m6_desired = 0;

  //make desireds for all objects. 
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

    
}

// read ROS is used to write to the registers that are in the switch statement.
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
      ///////////////////////////////////Write Requests//////////////////////////////
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
      //update kp
      case 6:        
        kp = (double)(reference[1] * 256) + reference[2];
        switcher = false;
        break;
      //update ki
      case 7:        
        ki = (double)(reference[1] * 256) + reference[2];
        switcher = false;
        break;
      //update kd
      case 8:        
        kd = (double)(reference[1] * 256) + reference[2];
        switcher = false;
        break;
      //update desired yaw
      case 9:
        m1_desired = (double)(reference[1] * 256) + reference[2];
        m2_desired = (double)(reference[1] * 256) + reference[2];
        switcher = false;
        break;
      

      ////////////////////////////Read Requests///////////////////////////  
      //motor1
      case 51:
        //writeROS();
        reg = 1;
        switcher = false;
        break;
      //motor1
      case 52:
        //writeROS();
        reg = 2;
        switcher = false;
        break;
      //motor2
      case 53:
        //writeROS();
        reg = 3;
        switcher = false;
        break;
      //motor3
      case 54:
        //writeROS();
        reg = 4;
        switcher = false;
        break;
      //motor 4
      case 55:
        //writeROS();
        reg = 5;
        switcher = false;
        break;
      //motor 5
      case 56:
        //writeROS();
        reg = 6;
        switcher = false;
        break;
      //in case something messes up heres a default value that will be hit
      default:       
        switcher = false;
        break;
    }
  }
}

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



