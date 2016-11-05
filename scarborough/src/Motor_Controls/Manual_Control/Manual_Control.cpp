#include "Manual_Control.h"

Handler scarborough_handler;
Manual_Control man_control;

int main(int argc, char **argv){

    ros::init(argc, argv, scarborough_handler.MANUAL_CHATTER);
    ros::NodeHandle n;
    ros::Rate loop_rate(10);
    int current_motor = -1;
    int last_motor = -1;
    int speed = 1500;
    while(ros::ok()){
        int getc = man_control.getch();

        switch (char(getc)) {

            case 'k':
                current_motor = -1;
                break;
            case '1':
                current_motor = 0;
                break;

            case '2':
                current_motor = 1;
                break;

            case '3':
                current_motor = 2;
                break;

            case '4':
                current_motor = 3;
                break;

            case '5':
                current_motor = 4;
                break;

            case '6':
                current_motor = 5;
                break;

            case '+':
                speed += 50;
                if(speed > 1800){
                    speed = 1800;
                }
                
                
                break;

            case '-':
                speed -= 50;
                if(speed < 1200){
                    speed = 1200;
                }
                
                
                break;

            default:
                //do nothin
                break;

        }
        if(current_motor != last_motor){
            speed = 1500;
        }
        if(current_motor != -1){
            for(int i=0; i<6; i++){
                if(i == current_motor){
                    man_control.motor_speed.motor[i] = speed;
                }
                else{
                    man_control.motor_speed.motor[i] = 1500; //set to stop
                }
            }
        }
        else{
            for(int i=0; i<6; i++){
                man_control.motor_speed.motor[i] = 1500; //set to stop
            }
        }

        man_control.change_speed(man_control.motor_speed);
        cout << man_control.motor_speed << endl;
        last_motor = current_motor;
        ros::spinOnce();

        loop_rate.sleep();

    }



}

Manual_Control::Manual_Control(){

}

void Manual_Control::change_speed(Motor_Speed input){
    i2cdev.writeWord(0x04, (uint8_t)0, (uint16_t)input.motor[0]); //motor1
    i2cdev.writeWord(0x04, (uint8_t)1, (uint16_t)input.motor[1] ); // motor2
    i2cdev.writeWord(0x04, (uint8_t)2, (uint16_t)input.motor[2] ); // motor3
    i2cdev.writeWord(0x04, (uint8_t)3, (uint16_t)input.motor[3] ); // motor4
    i2cdev.writeWord(0x04, (uint8_t)4, (uint16_t)input.motor[4] ); //motor 5
    i2cdev.writeWord(0x04, (uint8_t)5, (uint16_t)input.motor[5] ); //motor 6
}

int Manual_Control::getch()
{
    static struct termios oldt, newt;
    tcgetattr( STDIN_FILENO, &oldt);           // save old settings
    newt = oldt;
    newt.c_lflag &= ~(ICANON);                 // disable buffering
    newt.c_cc[VMIN] = 0; newt.c_cc[VTIME] = 0;
    tcsetattr( STDIN_FILENO, TCSANOW, &newt);  // apply new settings

    int c = getchar();  // read character (non-blocking)

    tcsetattr( STDIN_FILENO, TCSANOW, &oldt);  // restore old settings
    return c;
}
