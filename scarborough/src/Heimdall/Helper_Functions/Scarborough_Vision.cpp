//
//  bouydetection.cpp
//  openLOL
//
//  Created by Shubhankar Agarwal on 6/4/16.
//  Copyright © 2016 Shubhankar Agarwal. All rights reserved.
//

#include "Scarborough_Vision.hpp"


#define PI 3.14159265


int Scarborough_Vision::filter_image (  Mat detect, Mat src ,  int height , int width , vector<Point2i> cent_i , int red , int green , int blue)
{




    int r[height ][width], g[height ][width] ,b[height][width];




    cent_i[0].x= ( floor( width/2));
    cent_i[0].y = (floor( height/2));


    cout<<"Center of the picture: "<<cent_i[0]<<endl;

    //  cout<<s.width<<endl;
    // cout<<s.height<<endl;

    for(int col = 0; col < width ; col++){
        for(int row = 0; row < height ; row++){

            r[row][col] = 0;
            g[col][row] = 0;
            b[col][row] = 0;
        }
    }


    for(int col = 0; col < width ; col++){
        for(int row = 0; row < height ; row++){



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

    for(int col = 0; col < width ; col++){
        for(int row = 0; row < height ; row++){


            // WORKING PRETTY GOOD (120, 80, 140)
            // 120 , 100 , 150
            if( r[row][col] > red && g[row][col] > green && b[row][col] < blue)
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




    return 0;
}

//////////////	void path_marker( Mat final_image , double yawI , vector<Point2i> cent_i , vector<double> area1 ,  int thresh, int max_thresh , RNG rng , int g);
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int Scarborough_Vision::filterImageHSV (  Mat detect, Mat src ,  int height , int width , vector<Point2i> cent_i , int red , int green , int blue)
{
    int r[height ][width], g[height ][width] ,b[height][width];

    Mat hsv;     // = src.clone();
    cvtColor(src, hsv, CV_BGR2HSV);

    imshow("hsv", hsv);
    cent_i[0].x= ( floor( width/2));
    cent_i[0].y = (floor( height/2));


    cout<<"Center of the picture: "<<cent_i[0]<<endl;

    //  cout<<s.width<<endl;
    // cout<<s.height<<endl;

//    for(int col = 0; col < width ; col++){
//        for(int row = 0; row < height ; row++){
//
//            r[row][col] = 0;
//            g[col][row] = 0;
//            b[col][row] = 0;
//        }
//    }


    for(int col = 0; col < width ; col++){
        for(int row = 0; row < height ; row++){



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

    for(int col = 0; col < width ; col++){
        for(int row = 0; row < height ; row++){


            // WORKING PRETTY GOOD (120, 80, 140)
            // 120 , 100 , 150
            if( r[row][col] > red && g[row][col] > green && b[row][col] < blue)
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




    return 0;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int Scarborough_Vision::filter_image_green (  Mat detect, Mat src ,  int height , int width , vector<Point2i> cent_i , int red , int green , int blue)
{




    int r[height ][width], g[height ][width] ,b[height][width];




    cent_i[0].x= ( floor( width/2));
    cent_i[0].y = (floor( height/2));


    cout<<"Center of the picture: "<<cent_i[0]<<endl;

    //  cout<<s.width<<endl;
    // cout<<s.height<<endl;

    for(int col = 0; col < width ; col++){
        for(int row = 0; row < height ; row++){

            r[row][col] = 0;
            g[col][row] = 0;
            b[col][row] = 0;
        }
    }


    for(int col = 0; col < width ; col++){
        for(int row = 0; row < height ; row++){



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

    for(int col = 0; col < width ; col++){
        for(int row = 0; row < height ; row++){


            // WORKING PRETTY GOOD (120, 80, 140)
            // 120 , 100 , 150
            if( r[row][col] < red && g[row][col] > green && 250 > g[row][col] && b[row][col] < blue)
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




    return 0;
}


/** @function thresh_callback */
void Scarborough_Vision::thresh_callback( Mat final_image , double yawO , vector<Point2i> cent_i , vector<double> area1 ,  int thresh, int max_thresh , RNG rng , int g)
{
    Mat threshold_output;
    vector<vector<Point> > contours;

    vector<Vec4i> hierarchy;
    double largest_area = 0;
    int largest_contour_index = 0;
    double ang = 0;
    
    /// Detect edges using Threshold
    threshold( final_image, threshold_output, thresh, 255, THRESH_BINARY );
    cvtColor(threshold_output, threshold_output, CV_BGR2GRAY);
    /// Find contours
    findContours( threshold_output, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0) );
    
    if( contours.size() > 0  )  {  /// checking if any countour is detected

    /// Approximate contours to polygons + get bounding rects and circles
    vector<vector<Point> > contours_poly( contours.size() );
    // vector<Rect> boundRect( contours.size() );
    vector<Point2f>center( contours.size() );
    vector<float>radius( contours.size() );
    
    for( int i = 0; i < contours.size(); i++ )
    {   approxPolyDP( Mat(contours[i]), contours_poly[i], 3, true );
        // boundRect[i] = boundingRect( Mat(contours_poly[i]) );
        minEnclosingCircle( (Mat)contours_poly[i], center[i], radius[i] );
    }
    
 //   double b = contourArea( contours[0],false);





    for( int i = 0; i< contours.size(); i++ ) // iterate through each contour.
    {
        double a = contourArea( contours[i],false);  //  Find the area of contour
        if(a>largest_area){
            largest_area=a;
            largest_contour_index = i;                //Store the index of largest contour
        }
    }
    
   // minEnclosingCircle( (Mat)contours_poly[largest_contour_index], center[largest_contour_index], radius[largest_contour_index] );
    
    /// Draw polygonal contour + bonding rects + circles
    Mat drawing = Mat::zeros( threshold_output.size(), CV_8UC3 );


    for( int i = 0; i< contours.size(); i++ )
    {
        Scalar color = Scalar( rng.uniform(0, 255), rng.uniform(0,255), rng.uniform(0,255) );
        // drawContours( drawing, contours_poly, i, color, 1, 8, vector<Vec4i>(), 0, Point() );
        //rectangle( drawing, boundRect[i].tl(), boundRect[i].br(), color, 2, 8, 0 );
        circle( drawing, center[i], (int)radius[i], color, 2, 8, 0 );
        setLabel(drawing, "Target", contours[0]);    // Triangles
        
        
    }

    
    
    //////////////////////////////////////////////////////////////////////////////////
    /////////// FInding the angle ////////////////////////////////////////////////////

    int dist_x = center[0].x - cent_i[0].x;
    int dist_y = center[0].y - cent_i[0].y;

    
    



    cout<< " dist_x = " << dist_x << " dist_y =" << dist_y <<endl;
    
    //int ang = atan2 (dist_y,dist_x) * 180 / PI;
    
     ang = atan2 ( (dist_x) , (dist_y)) * 180 / PI;
    
  //cout<< "The target is "<< (  90  -  (ang - 90 ) ) << " degrees from x-axis"<<endl;
    
      //  if( dist_x > 0 && )
    
    
   // yawO = yawO  - (-ang);

        yawO =  -ang - 180   ;

    cout<< "The output yaw is "<<yawO<<endl;
    
          int area = (int)largest_area;

    cout<<"area = "<<area<<endl;
    cout<<endl;
    
    cout<< "frame no. = " << g << endl;
    
    area1.push_back(area);
    
    if( g > 3)
    {
        if( (area1[g-2] + area1[g-1] + area1[g])/3 > area )
            cout<<" wrong direction "<<endl;
        else
            cout<<" right direction "<<endl;
    }
    
    

    /////////////////////////////////////////////////////////////////////////////////////////
    
    /////////////////// putting the label //////////////////////////////////
    
    /////////////////////////////////////////////////////////////////////////////////////
    ///////  drawing the lines n the image //////////////////////////////////////////////
    
    vector<Point2i> cent_k(1);
    vector<Point2i> cent_j(1);
    
    cent_k[0] = cent_i[0];
    cent_k[0].x = cent_i[0].x - 20;
    
    cent_j[0] = cent_i[0];
    cent_j[0].x = cent_i[0].x + 20;
    
    
    // Scalar color = Scalar( rng.uniform(0, 255), rng.uniform(0,255), rng.uniform(0,255) );
    circle( drawing , cent_i[0] ,  5 , Scalar( 72, 209, 51 ) , 2, 8 , 0);
    //circle( drawing , cent_i[0] ,  2*5 , Scalar( 72, 209, 51 ) , 2, 8 , 0);
    //circle( drawing , cent_i[0] ,  4*5 , Scalar( 72, 209, 51 ) , 2, 8 , 0);
    MyLine(drawing , (cent_k[0] ), (cent_j[0]));
    
    cent_k[0] = cent_i[0];
    cent_k[0].y = cent_i[0].y - 20;
    
    cent_j[0] = cent_i[0];
    cent_j[0].y = cent_i[0].y + 20;
    
    MyLine(drawing , (cent_k[0] ), (cent_j[0]));
    ////////////////////////////////////////////////////////////////////////////////
    
    // string x = -ang;
    
    
    std::vector<cv::Point> c_print;
    
    Point temp;
    
    temp.x = 10;
    temp.y = 10;
    c_print.push_back(temp);
    
    temp.x = 100;
    temp.y = 10;
    c_print.push_back(temp);
    
    temp.x = 10;
    temp.y = 20;
    c_print.push_back(temp);
    temp.x = 100;
    temp.y = 20;
    c_print.push_back(temp);
    
    
    setLabel(drawing, "Property of Somi" , c_print);
    
    stringstream ang_s;
    ang_s<< -ang;
    string ang_s1 = ang_s.str();
    string s = "The angle of the target from x-axis is " + ang_s1;
    
    temp.x = 10;
    temp.y = 30;
    c_print.push_back(temp);
    
    temp.x = 100;
    temp.y = 30;
    c_print.push_back(temp);
    
    temp.x = 10;
    temp.y = 40;
    c_print.push_back(temp);
    temp.x = 100;
    temp.y = 40;
    c_print.push_back(temp);
    
    setLabel(drawing, s , c_print);
    /// Show in a window
    namedWindow( "Contours", CV_WINDOW_AUTOSIZE );
    imshow( "Contours", drawing );
      }
}

////////////////////////////////////////////////////////////////////////////////////////

void Scarborough_Vision::setLabel(cv::Mat& im, const std::string label, std::vector<cv::Point>& contour)
{
    int fontface = cv::FONT_HERSHEY_SIMPLEX;
    double scale = 0.4;
    int thickness = 1;
    int baseline = 0;
    
    
    cv::Size text = cv::getTextSize(label, fontface, scale, thickness, &baseline);
    cv::Rect r = cv::boundingRect(contour);
    
    cv::Point pt(r.x + ((r.width - text.width) / 2), r.y + ((r.height + text.height) / 2));
    cv::rectangle(im, pt + cv::Point(0, baseline), pt + cv::Point(text.width, -text.height), CV_RGB(0,0,0), CV_FILLED);
    cv::putText(im, label, pt, fontface, scale, CV_RGB(0, 100, 255), thickness, 8);
}


void Scarborough_Vision::MyLine( Mat img, Point start, Point end )
{
    int thickness = 2;
    int lineType = 8;
    line( img,
         start,
         end,
         Scalar( 72, 209, 51 ),
         thickness,
         lineType );
}

double hue(double r, double g, double b)
{
    double r_ = r / 255;
    double g_ = g / 255;
    double b_ = b / 255;

    double c_max = max(max(r_, g_), b_);
    double c_min = min(min(r_, g_), b_);

    double delta = c_max - c_min;

    if (delta == 0)
        return 0;
    else if (c_max == r_)
        return 60 * ((int)((g_ - b_) / delta) % 6);
    else if (c_max == g_)
        return 60 * (((b_ - r_) / delta) + 2);
    else
        return 60 * (((r_ - g_) / delta) + 4);
}

bool isRed(double hue)
{
    return hue < 30 || hue > 345;
}

bool isYellow(double hue)
{
    return hue > 30 && hue < 75;
}

bool isGreen(double hue)
{
    return hue > 75 && hue < 135;
}


vector<Point> Scarborough_Vision::all_bouy( Mat detect , Mat final_image , double yawI , vector<Point2i> cent_i , vector<double> area1 ,  int thresh, int max_thresh , RNG rng , int g , vector<vector<Point> > contours , int color)
{

    Mat threshold_output;
    vector<Vec4i> hierarchy;
    double l_area = 0;  // area of the largest contour
    int l_c_i = 0;   // largest contour index
 //   double ang = 0;

    /// Detect edges using Threshold
    threshold( detect, threshold_output, thresh, 255, THRESH_BINARY );
    cvtColor(threshold_output, threshold_output, CV_BGR2GRAY);
    /// Find contours
    findContours( threshold_output, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0) );
    if( contours.size() > 0  )  {  /// checking if any countour is detected

        /// Approximate contours to polygons + get bounding rects and circles
        vector<vector<Point> > contours_poly( contours.size() );
        vector<Rect> boundRect( contours.size() );
        vector<Point2f>center( contours.size() );
        vector<float>radius( contours.size() );




        for( int i = 0; i < contours.size(); i++ )
        {   approxPolyDP( Mat(contours[i]), contours_poly[i], 3, true );
            boundRect[i] = boundingRect( Mat(contours_poly[i]) );
            minEnclosingCircle( (Mat)contours_poly[i], center[i], radius[i] );


        }

        for( int i = 0; i< contours.size(); i++ ) // iterate through each contour.
        {
            double a = contourArea( contours_poly[i],false);  //  Find the area of contour
            if(a>l_area){
                l_area=a;
                l_c_i = i;                //Store the index of largest contour
            }

          //  cout<<"contour:" << contours[i]<<endl;
        }

        if( color == 0){

            circle( final_image, center[l_c_i], (int)radius[l_c_i], Scalar( 0 , 0, 255 ), 2, 8, 0 );
            setLabel(final_image, "Target Red", contours[l_c_i]); }// Triangle}
        else if( color == 1){
            circle( final_image, center[l_c_i], (int)radius[l_c_i], Scalar( 0, 255, 0 ), 2, 8, 0 );
            setLabel(final_image, "Target Green", contours[l_c_i]);
        }
        else if( color == 2)
        {
            circle( final_image, center[l_c_i], (int)radius[l_c_i],  Scalar( 0, 255, 255 ), 2, 8, 0 );
            setLabel(final_image, "Target Yellow", contours[l_c_i]);
        }


    }






//    for (int k = 0; k < contours.size(); k++) {
//        cout<<"contour everything:" << contours[k]<<"the size of the contour"<<contours.size()<<endl;
//    }
     return contours[l_c_i];
}


void Scarborough_Vision::pathmarker( Mat final_image , double yawI , vector<Point2i> cent_i , vector<double> area1 ,  int thresh, int max_thresh , RNG rng , int g)
{

    Mat threshold_output;
    vector<vector<Point> > contours;
    vector<Vec4i> hierarchy;
    double l_area = 0;
    int l_c_i = 0;
    double ang = 0;

    /// Detect edges using Threshold
    threshold( final_image, threshold_output, thresh, 255, THRESH_BINARY );
    cvtColor(threshold_output, threshold_output, CV_BGR2GRAY);
    /// Find contours
    findContours( threshold_output, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0) );

    if( contours.size() > 0  )  {  /// checking if any countour is detected

        /// Approximate contours to polygons + get bounding rects and circles
        vector<vector<Point> > contours_poly( contours.size() );
         vector<Rect> boundRect( contours.size() );

        for( int i = 0; i < contours.size(); i++ )
        {   approxPolyDP( Mat(contours[i]), contours_poly[i], 3, true );
            boundRect[i] = boundingRect( Mat(contours_poly[i]) );
          //  minEnclosingCircle( (Mat)contours_poly[i], center[i], radius[i] );
        }

        //   double b = contourArea( contours[0],false);





        for( int i = 0; i< contours.size(); i++ ) // iterate through each contour.
        {
            double a = contourArea( contours_poly[i],false);  //  Find the area of contour
            if(a>l_area){
                l_area=a;
                l_c_i = i;                //Store the index of largest contour
            }
        }


        /// Draw  bonding rects
        Mat drawing = Mat::zeros( threshold_output.size(), CV_8UC3 );



        Scalar color = Scalar( rng.uniform(0, 255), rng.uniform(0,255), rng.uniform(0,255) );

         //   rectangle( drawing, boundRect[l_c_i].tl(), boundRect[l_c_i].br(), color, 2, 8, 0 );


        //    setLabel(drawing, "Target", contours[0]);

       // Mat fit_line_image = drawing.clone();


////////////////////////// Making the line at the center of the rectangle ////////////////////////////
        int rec_top_w =  boundRect[l_c_i].tl().x + ( boundRect[l_c_i].br().x - boundRect[l_c_i].tl().x ) /2 ;
     //   int rec_bot_w = rec_top_w + (boundRect[l_c_i].br().y - boundRect[l_c_i].tl().y);

        {   std::vector<cv::Point> rect_center;
            Point temp;

            temp.x = rec_top_w;
            temp.y = boundRect[l_c_i].tl().y;
            rect_center.push_back(temp);

            temp.x = rec_top_w;
            temp.y = boundRect[l_c_i].br().y;
            rect_center.push_back(temp);

         //   MyLine(drawing , rect_center[0] , rect_center[1]);

         //   MyLine(drawing , boundRect[l_c_i].tl(), boundRect[l_c_i].br());


        }
        vector<float> fit_line(4);

        fitLine(contours_poly[l_c_i], fit_line, CV_DIST_L2, 0, 0.01, 0.01);

        Point fitline_start ;
        fitline_start.x = fit_line[2] - fit_line[0] * 200;
        fitline_start.y = fit_line[3] - fit_line[1] * 200;

        Point fitline_end ;

        fitline_end.x = fit_line[2] + fit_line[0] * 200;
        fitline_end.y = fit_line[3] + fit_line[1] * 200;



        line(final_image, fitline_start, fitline_end, color , 5 , 8 , 0  );

       // if( ang > 0 &&  ang ) {



        ///  fit_line[1] the y -axis angle and fit_line[0] x-axis. We make fit_line[0] -ve because in image processing the z values decrease as we go down
        ang = atan(-(fit_line[0]) /fit_line[1]) * 180 / PI;
            cout<<"The angle of the pathmarker is " << ang <<endl;
       // }

            path_marker.rotation[0] = ang;
            path_marker.rotation[1] = 0 ;
            path_marker.rotation[2] = 0 ;
            path_marker.in_sight = true ;
            path_marker.depth = 0 ;
            path_marker.object = "PATH_MARKER";
    }



}
void Scarborough_Vision::filterImageHSVRed(  Mat detect, Mat src ,  int height , int width , vector<Point2i> cent_i )
{
    int r[height ][width], g[height ][width] ,b[height][width];

    Mat hsv;     // = src.clone();
    cvtColor(src, hsv, CV_BGR2HSV);

    vector<Mat> channels;
    split(hsv, channels);

    imshow("Hue", channels[0]);
    imshow("Saturation", channels[1]);
    imshow("Value", channels[2]);

//    for(int col = 0; col < width ; col++){
//        for(int row = 0; row < height ; row++){
//
//            r[row][col] = 0;
//            g[col][row] = 0;
//            b[col][row] = 0;
//        }
//    }


    for(int col = 0; col < width ; col++){
        for(int row = 0; row < height ; row++){


            b[row][col] = src.template at<Vec3b>(row,col)[0];
            g[row][col] = src.template at<Vec3b>(row,col)[1];
            r[row][col] = src.template at<Vec3b>(row,col)[2];

            // cout<<g[row][col]<<endl;
        }
    }

    for(int col = 0; col < width ; col++){
        for(int row = 0; row < height ; row++){


            // WORKING PRETTY GOOD (120, 80, 140)
            // 120 , 100 , 150

            Vec3b hsv_vec = hsv.at<Vec3b>(row ,col);

            if( (hsv_vec.val[0] < 15 || hsv_vec.val[0] > 172) && hsv_vec.val[1] > 0  )
            {

                detect.template at<Vec3b>(row, col)[0] = 0;
                detect.template at<Vec3b>(row, col)[1] = 0;
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
//    imshow("after thresholding", detect);

}

void Scarborough_Vision::filterImageHSVGreen(  Mat detect, Mat src ,  int height , int width , vector<Point2i> cent_i )
{
    int r[height ][width], g[height ][width] ,b[height][width];

    Mat hsv;     // = src.clone();
    cvtColor(src, hsv, CV_BGR2HSV);


    for(int col = 0; col < width ; col++){
        for(int row = 0; row < height ; row++){


            b[row][col] = src.template at<Vec3b>(row,col)[0];
            g[row][col] = src.template at<Vec3b>(row,col)[1];
            r[row][col] = src.template at<Vec3b>(row,col)[2];

            // cout<<g[row][col]<<endl;
        }
    }

    for(int col = 0; col < width ; col++){
        for(int row = 0; row < height ; row++){


            // WORKING PRETTY GOOD (120, 80, 140)
            // 120 , 100 , 150

            Vec3b hsv_vec = hsv.at<Vec3b>(row ,col);

            if( hsv_vec.val[0] < 75 && hsv_vec.val[0] > 50   && hsv_vec.val[1] > 0 )
            {

                detect.template at<Vec3b>(row, col)[0] = 0;
                detect.template at<Vec3b>(row, col)[1] = 255;
                detect.template at<Vec3b>(row, col)[2] = 0;
            }
            else
            {
                detect.template at<Vec3b>(row, col)[0] = 0;
                detect.template at<Vec3b>(row, col)[1] = 0;
                detect.template at<Vec3b>(row, col)[2] = 0;


            }
        }
    }
    //    imshow("after thresholding", detect);

}

void Scarborough_Vision::filterImageHSVYellow(  Mat detect, Mat src ,  int height , int width , vector<Point2i> cent_i )
{
    int r[height ][width], g[height ][width] ,b[height][width];

    Mat hsv;     // = src.clone();
    cvtColor(src, hsv, CV_BGR2HSV);


    for(int col = 0; col < width ; col++){
        for(int row = 0; row < height ; row++){


            b[row][col] = src.template at<Vec3b>(row,col)[0];
            g[row][col] = src.template at<Vec3b>(row,col)[1];
            r[row][col] = src.template at<Vec3b>(row,col)[2];

            // cout<<g[row][col]<<endl;
        }
    }

    for(int col = 0; col < width ; col++){
        for(int row = 0; row < height ; row++){


            // WORKING PRETTY GOOD (120, 80, 140)
            // 120 , 100 , 150

            Vec3b hsv_vec = hsv.at<Vec3b>(row ,col);

            if( hsv_vec.val[0] <  38 && hsv_vec.val[0] > 27  && hsv_vec.val[1] > 0 )
            {

                detect.template at<Vec3b>(row, col)[0] = 0;
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
    //    imshow("after thresholding", detect);

}


void Scarborough_Vision::direction(vector<Point>  target ,  double yawO , vector<Point2i> cent_i  , int framecounter , vector<double> area1 , double curr_depth){

    double yaw_ang = 0;
    double pitch_ang = 0;

    double largest_area = contourArea( target , false);

    Point2f center;
    float   radius;
    //  vector<Point>  contours_poly( target.size() );

    // approxPolyDP( Mat(target), contours_poly , 3, true );
    minEnclosingCircle( target , center, radius);

    //////////////////////////////////////////////////////////////////////////////////
    /////////// FInding the angle ////////////////////////////////////////////////////

//    cout<<"Center of the image" << cent_i << endl;
//    cout<<"Center of the target" << center << endl;

    int dist_x = center.x - cent_i[0].x;
    int dist_y = center.y - cent_i[0].y;

    cout<< " dist_x = " << dist_x << " dist_y =" << dist_y <<endl;

     double camera_calib = 0.0005375 * min(2560/(cent_i[0].x * 2), 1440/(cent_i[0].y * 2));


 ////////////// Calculating the angle /////////////////////////////////////


    ////////// calculating the Yaw axis ///////////////

    yaw_ang = atan ( (dist_x) * camera_calib ) * 180 / PI;
    cout<< "The output yaw is "<<yaw_ang<<endl;


    ////////////////// calculating the PITCH ///////////////////////////////
    pitch_ang = - atan ( (dist_y) * camera_calib ) * 180 / PI;
    cout<< "The output pitch is "<<pitch_ang<<endl;


    int area = (int)largest_area;

    cout<<"area = "<<area<<endl;
    cout<<"frame no. = " << framecounter << endl;

    area1.push_back(area);

    double real_bouy_width = 0.1905 ; // in meters
    double dist = real_bouy_width/ (  camera_calib * (radius*2) );


    cout << "Distance to the bouy " << dist << endl;

    //////////////////////////////////////////////////////////////////////////////

    double depth , desired_depth;

    depth = dist * camera_calib * dist_y;

    desired_depth = curr_depth + depth;  /// the final desired depth


	red_bouy.object = "RED_BOUY";
	red_bouy.color = "RED";

	red_bouy.rotation[0] = yaw_ang;
	red_bouy.rotation[1] = 0;
	red_bouy.rotation[2] = 0;
	red_bouy.depth = desired_depth;
	red_bouy.in_sight = true;



    ///  vague description if we are going in correct direction
    /// comparing past 3 areas if the area has increased or not
    if( framecounter > 3)
    {
        if( (area1[framecounter-2] + area1[framecounter-1] + area1[framecounter])/3 > area )
            cout<<"Wrong direction "<<endl;
        else
            cout<<"Right direction "<<endl;
    }


    cout<<endl;

}
