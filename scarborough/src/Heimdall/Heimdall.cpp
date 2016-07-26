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
	forward.open(0);
	downward.open(1);
	vector<Point2i> cent_i(1);
	Scarborough_Vision scarborough;
	depth = 0;
}
//TODO read Webcams not files
bool Heimdall::init(){
	 cout<<"Time at starting is 0 sec"<<endl;

	 //   string filename = "/Users/Somi/Desktop/_Recordings_/underwatertest.mp4";

	    if(!forward.isOpened() || !downward.isOpened()){
	    	cout << "Connect the freaking cameras BITCH -Shubhankar Agarwal 2016 SDCR" << endl;
	    	return false;
	    }

//	    forward >> src;
//	    downward >> down;

//
//	    if(! src.data || !down.data )         // Check for invalid input
//	    {
//	        cout <<  "Could not open or find the image" << std::endl ;
//	        return false;
//	    }

	    cout << "FINISHED INIT"<<endl;
	    return true;
}


void Heimdall::heimdall_bouy(gui interface){
	 int framecounter = 0;

	 imshow("front", src);

	Size s = src.size();
	cent_i[0].x=  (floor( s.width/2));
	cent_i[0].y = (floor( s.height/2));

	cout<< cent_i << endl;

	///////////////////////////////////////////////////ALL BOUY DETECTION //////////////////////////////////////////////////////

	detect_r = src.clone();
	detect_g = src.clone();
	detect_y = src.clone();

	//imshow("Source Front", src);



	vector<vector<Point> > contours;
	Mat surc;

	forward >> surc;


	Mat final_image = Mat::zeros( src.size(), CV_8UC3 );

	scarborough.filterImageHSVRed(detect_r ,src, s.height, s.width, cent_i  );
	fastNlMeansDenoising(detect_r , detect_r , 100, 3, 31);
	imshow("After Hue red", detect_r);
	vector<Point> red_vec = scarborough.all_bouy(detect_r , final_image,   yawI ,  cent_i , area1 ,  thresh , max_thresh , rng , framecounter   , contours , 0);

	// get current depth from ROS



	if(red_vec.size() > 0){
			scarborough.direction(red_vec ,yawI ,  cent_i ,framecounter ,  area1 , depth);
			red_bouy = scarborough.red_bouy;
	}


//    scarborough.filterImageHSVGreen(detect_g ,src, s.height, s.width, cent_i  );
//	fastNlMeansDenoising(detect_g , detect_g , 100, 3, 31);
//	//   imshow("After Hue Green", detect_g);
//	vector<Point> green_vec = scarborough.all_bouy(detect_g ,final_image,  yawI ,  cent_i , area1 ,  thresh , max_thresh , rng , framecounter   , contours , 1);
//
//
//	scarborough.filterImageHSVYellow(detect_y ,src, s.height, s.width, cent_i  );
//	fastNlMeansDenoising(detect_y , detect_y , 100, 3, 31);
//	// imshow("After Hue Yellow", detect_y);
//	vector<Point> yellow_vec = scarborough.all_bouy(detect_y , final_image,   yawI ,  cent_i , area1 ,  thresh , max_thresh , rng ,framecounter, contours , 2);
//

}



void Heimdall::heimdall_pathmarker(gui interface ){

				imshow("Down" , down);
	            Size s = down.size();
	            Mat pathmark = down.clone();
	           // cout << "width "  << s.width  << "height " << s.height << endl;

	            int framecounter = 0;

	            scarborough.filter_image( pathmark , down, s.height, s.width, cent_i , 160  , 150 , 150 );
	            scarborough.filterImageHSVRed(pathmark, down,  s.height, s.width, cent_i  );

	            fastNlMeansDenoising(pathmark , pathmark , 100, 3, 31);
	            //imshow( "Display red", detect_r );
	            scarborough.pathmarker(  pathmark,  yawI , cent_i ,  area1 ,  thresh,  max_thresh ,  rng ,  framecounter);
}

void Heimdall::get_depth(double _depth){
	depth = _depth;
}

void Heimdall::get_state(string _state){
	state = _state;
}

void Heimdall::test_camera( ){
	forward >> src;

	cout << "Can Open Image" << endl;

	if(!src.data ){
		cout <<  "Could not open or find the image" << std::endl ;
	}else{
	imshow("yusssss", src);
	imwrite("~/Desktop/testimg.png", src );

	}
	//imshow("Front" , src );
	//imshow("Down" , down );


}



