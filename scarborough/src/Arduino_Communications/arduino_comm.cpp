/*
 * arduino_comm.cpp
 *
 *  Created on: Jan 24, 2016
 *      Author: sdcr
 */
#include "arduino_comm.h"
#define DEBUG

//serial stream is used for opening and using comm ports
SerialStream port;

ArdComm::ArdComm(){
	handshake = false;
	message_count = 0;
	path = "/dev/ttyACM";
	delimiter = ";";
	parse = "";
	pos = 0;

}

void ArdComm::init(){

}

/*
 * This function takes the message from the arduino then parses the statement.
 * a standard statement is M0:123.235;M4:544.23523;M1:665; this will break apart this statement
 * into an array. the individual statements are broken up by the ";" delimiter
 */
void ArdComm::interperet_message(string message){

	string corrected = "";
	for(int j = 0 ; j < message.length() ; j++){

		if(message[j] != NULL){
			corrected += message[j];

		}
	}
	cout << corrected << endl;
	while( corrected != ""){
		pos = corrected.find(delimiter);
		parse = corrected.substr(0, pos +1);

		for(int i = 0 ; i < parse.length() ; i++){
			//cout << parse << " Parse  POS: " <<pos << " i" << i << " Parse[i] = " << parse[i];
			//cout << " message length" << corrected.length();

			switch(parse[i]){

			//reading in a K message looks like "K:1;" or "K:0;" which is the only two messages that should be!
			case 'K':
				//cout << "Case K Found";
				if(atoi(parse.substr(2,pos).c_str()) >1 || atoi(parse.substr(2,pos).c_str()) < 0){
					cout << "Invalid Code Must be a 0 or 1" << endl;
				}
				else{
					int _kill_switch = atoi(parse.substr(2,pos).c_str());

					switch(_kill_switch){
					case 1:
						kill_switch.killed = false;
						break;
					case 0:
						kill_switch.killed = true;
						break;
					default:
						break;
					}
				}
				//set cursor to next variable location.
				i = pos;
				//erase parsed values
				corrected.erase(0 , pos + delimiter.length());
				break;
				//A depth message should look like this "D:0.7;"
			case 'D':
				//cout << "Case D found" << endl;
				depth.depth = atof(parse.substr(2, pos).c_str());

				//set cursor to next variable location.
				i = pos;
				//erase parsed values
				corrected.erase(0 , pos + delimiter.length());
				break;

			default:

				cout << "default " << parse;
				i = pos;
				//erase parsed values
				corrected.erase(0 , pos + delimiter.length());
				break;
			}//end switch
		}//end for
	}//end while
}//end function


//This function checks whether a path exists or not. will return true or false
inline bool ArdComm::pathExists (const std::string& name) {
  struct stat buffer;
  return (stat (name.c_str(), &buffer) == 0);
}

string ArdComm::trim(string& str)
{
    size_t first = str.find_first_not_of(' ');
    size_t last = str.find_last_not_of(' ');
    return str.substr(first, (last-first+1));
}





