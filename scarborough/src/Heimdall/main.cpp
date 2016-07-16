#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <ctime>
#include <sys/time.h>
#include <math.h>
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/photo/photo.hpp"

#include "Helper_Functions/Scarborough_Vision.hpp"




using namespace std;
using namespace cv;

double yawI = 0; 
int thresh = 100;
int max_thresh = 255;
RNG rng(12345);


/// Global variables
Mat src, detect , final_image;
vector<Point2i> cent_i(1);
vector<double> area1;


int main( int argc, char** argv )

{
    
   
    
    cout<<"Time at starting is 0 sec"<<endl;
    
    string filename = "/Users/Somi/Desktop/_Recordings_/Bouy_Ramming.mp4";
    VideoCapture capture(filename);
    Mat frame;
    
    if( !capture.isOpened() )
        cout<< "Error when reading steam_avi"<<endl;
    
    int framecounter = 0;
    
 
    for( ; ; )
    {
        struct timeval tv0,tv1;
        gettimeofday(&tv0 , 0);
        
        capture >> src;
        capture >> detect;
        if(src.empty())
            break;
        imshow("w", src);
        waitKey(20); // waits to display frame
    
    
//
//    char imageName[48];
//    //char imageDest[57];
//    namedWindow( "Display window", WINDOW_AUTOSIZE );// Create a window for display.
//
//    int i = 0;
//    
//    //while(1){
//        cout<<"again"<<endl;
//        sprintf(imageName,"/Users/Somi/Desktop/_Recordings_/Front/Image299.png",i);
//        
//        src= imread(imageName,1);
//    detect = imread(imageName,1);
//       // double j =0;
//     //   while ( j < 1000000) {
//        //    j++;
//        //}
//       
//        if(!src.data ){
//            cout<<"NO image found!"<<endl;
//            return 0;
//      //      break;
//        }
//    
//        //sprintf(imageDest,"/Users/Somi/Desktop/_Recordings_/convertimage/image_g%d.png",i);
//        //imwrite(imageDest, gray);
//    
//       cout<<imageName<<endl;
//    
//    
//    
/////////////////////////////////////////////////////////////////////////
      Size s = src.size();
    

    int r[s.height ][s.width], g[s.height ][s.width] ,b[s.height][s.width];
        
        
        
        
        cent_i[0].x= ( floor( s.width/2));
        cent_i[0].y = (floor( s.height/2));
        
        
        cout<<"Center of the picture: "<<cent_i[0]<<endl;
   
      //  cout<<s.width<<endl;
      // cout<<s.height<<endl;
    
    for(int col = 0; col < s.width ; col++){
        for(int row = 0; row < s.height ; row++){
            
            r[row][col] = 0;
            g[col][row] = 0;
            b[col][row] = 0;
        }
    }
    
    
    for(int col = 0; col < s.width ; col++){
        for(int row = 0; row < s.height ; row++){
            
            
            
            b[row][col] = src.template at<Vec3b>(row,col)[0];
            g[row][col] = src.template at<Vec3b>(row,col)[1];
            r[row][col] = src.template at<Vec3b>(row,col)[2];
            
            
            
            
           // cout<<g[row][col]<<endl;
        }
    }
    
   // cout<<"copy done"<<endl;
    
  //  double alpha = 1.0;
  //  int beta = 1;
    
   // Mat detect(s.height,s.width, CV_8UC3,Scalar(0,255,255));

    for(int col = 0; col < s.width ; col++){
        for(int row = 0; row < s.height ; row++){
        
            
            // WORKING PRETTY GOOD (120, 80, 140)
            if( r[row][col] > 120 && g[row][col] > 100 && b[row][col] < 130)
            {
            
                detect.template at<Vec3b>(row, col)[0] = 255;
                detect.template at<Vec3b>(row, col)[1] = 255;
                detect.template at<Vec3b>(row, col)[2] = 255;
            }
            else
            {
                detect.template at<Vec3b>(row, col)[0] = 0;
                detect.template at<Vec3b>(row, col)[1] = 0;
                detect.template at<Vec3b>(row, col)[2] = 0;
                
            
            }
    }
}
        gettimeofday(&tv1,0);
        long elap = (tv1.tv_sec - tv0.tv_sec ) * 100000  + tv1.tv_usec - tv0.tv_usec;
        
        cout<<"Time after initial thresholding : " << elap/1000.0f <<"millisec"<<endl;
        
      //  imshow( "Display window", detect );
         fastNlMeansDenoising(detect,final_image , 100, 3, 31);

  
        //thresh_callback( 0, 0 , framecounter);
        
        imshow("asdasd", final_image);
        
      //  thresh_callback( final_image ,  yawI ,  cent_i , area1 ,  thresh , max_thresh , rng ,  framecounter);
 
        waitKey(1);
 
        framecounter++;
        
             //  cout<<"Time after denoising and finding the target:"<<"sec"<<endl;
    
        
    }
       waitKey();
    
       return 0;
}

////////////////////////////////////////////////////////////////////////////






