/*
 * Heimdall.cpp
 *
 *  Created on: Jul 16, 2016
 *      Author: ximidar
 */
#include "Heimdall.h"

Heimdall::Heimdall(){
	yawI = 0;
	thresh = 100;
	max_thresh = 255;
	rng(12345);
	forward.open(1);
	downward.open(2);
}

bool Heimdall::init(){
	 cout<<"Time at starting is 0 sec"<<endl;

	    string filename = "/Users/Somi/Desktop/_Recordings_/underwatertest.mp4";

	    if(!forward.isOpened() || !downward.isOpened()){
	    	cout << "Connect the freaking cameras BITCH -Shubhankar Agarwal 2016 SDCR" << endl;
	    	return false;
	    }

	    forward >> src;


	    if(! src.data )                              // Check for invalid input
	    {
	        cout <<  "Could not open or find the image" << std::endl ;
	        return false;
	    }
	    return true;
}


void Heimdall::heimdall_bouy(gui interface){
	vector<Point2i> cent_i(1);
	//initialize time variables
	 struct timeval tv0,tv1;
	 gettimeofday(&tv0 , 0);

	 //clone src
	 detect_r = src.clone();
	 detect_g = src.clone();
	 detect_y = src.clone();

	 if(interface == Heimdall::SHOW_VIDEO){
		 imshow("w", src);
	 }

	 //get size of the src image
	 Size s = src.size();

	 //initialize contours
	 vector<vector<Point> > contours;


	 //time checking how long it took to clone
	 gettimeofday(&tv1,0);
	 long elap = (tv1.tv_sec - tv0.tv_sec ) * 100000  + tv1.tv_usec - tv0.tv_usec;

	 cout<<"Time after initial thresholding : " << elap/1000.0f <<"millisec"<<endl;

	    // red 150 , 100 , 150
	    // green <  140 , 160 , 160

	 //get FPS
	 int framecounter = 0 ;

	 Mat final_image = Mat::zeros( src.size(), CV_8UC3 );


	 Scarborough_Vision vision;

	 //detect red
	 int red_bouy = vision.filter_image (detect_r ,src, s.height, s.width, cent_i , 150  , 100 , 150 );

	 fastNlMeansDenoising(detect_r , detect_r , 100, 3, 31);
	  //  imshow( "Display red", detect_r );

	 bouy.color = Heimdall::YELLOW;
	 bouy.rotation = {10,10,10};
	 bouy.object = Heimdall::GATE;


	 vector<Point> red_vec = vision.all_bouy(detect_r , final_image,   yawI ,  cent_i , area1 ,  thresh , max_thresh , rng ,  framecounter   , contours , red_bouy);
	 cout<<"red completed"<<endl;
	 imshow( "after red completed" , final_image);


	 //detect green
	 int green_bouy = vision.filter_image_green(detect_g ,src, s.height, s.width, cent_i , 140  , 150 , 150 );

	 fastNlMeansDenoising(detect_g,detect_g , 100, 3, 31);


	 vector<Point> green_vec = vision.all_bouy(detect_g ,final_image,  yawI ,  cent_i , area1 ,  thresh , max_thresh , rng ,  framecounter   , contours , green_bouy);
	 cout<<"green completed"<<endl;
	 imshow( "after green completed" , final_image);




	 //detect yellow
	 int yellow_bouy = vision.filter_image(detect_y ,src, s.height, s.width, cent_i , 150  , 180 , 150 );



	 fastNlMeansDenoising(detect_y,detect_y , 100, 3, 31);
	 imshow( "Display yellow", detect_y );

	 vector<Point> yellow_vec = vision.all_bouy(detect_y , final_image,   yawI ,  cent_i , area1 ,  thresh , max_thresh , rng ,  framecounter   , contours , yellow_bouy);
	 cout<<"yellow completed"<<endl;
	 imshow( "after yellow completed" , final_image);

	 ///////////////////////////////////////////////////////////////////////////////////////////////////////


	 waitKey();

}


