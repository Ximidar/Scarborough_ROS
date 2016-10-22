#include "Manual_Control.h"

Handler scarborough_handler;
Manual_Control man_control;

int main(int argc, char **argv){

    ros::init(argc, argv, scarborough_handler.MANUAL_CHATTER);

    while(ros::ok()){
        int getc = man_control.getch();

        switch (getc) {
            case 'q':
                cout << "this method works" << endl;
                // do something
                break;
            default:
                cout << "this method does not work" << endl; 
                // do something
        }
    }



}

Manual_Control::Manual_Control(){
    pub = n.advertise<Desired_Directions>(scarborough_handler.DESIRED, 200);
}

void Manual_Control::change_speed(Desired_Directions direction){
    pub.publish(direction);
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
