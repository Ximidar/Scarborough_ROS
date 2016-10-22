#include "accelerometer.h"

Accelerometer::Accelerometer(){
    cout << "Hllo Constructor" << endl;

}

Accelerometer::~Accelerometer(){
    cout << "hello de constructor" << endl;
}


void Accelerometer::accel_init(scarborough::YPR YPR){
    cout << YPR << endl;
}