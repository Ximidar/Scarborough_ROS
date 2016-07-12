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
//listen listens to the comm port and returns the message when the end character
//is hit. '\'
string ArdComm::listen(){
	char next_char;
	string message;
	 message_count = 0;
	cout << "Reading Message" << endl;
	//while the end line character isn't hit record the message.
	while(next_char != '\\'){

		port >> next_char; //get the next char
		message += next_char; //add char to message

		//check if a message is too long. If it is then throw away the message and break.
		/*
		 * This is nice for checking if there's waaay to many characters, but we need a better way to
		 * detect a long message. Maybe we should detect if it has changed the same variable in the same
		 * line. TODO
		 */
		 message_count++;
		 //cout << message << endl;
		if ( message_count > 1000){
			cout << "ERROR MESSAGE OVER 1000 CHARACTERS!!!";
			message = "";
			break;
		}
	}
	return message;
}

void ArdComm::init(){

	//find an open comm port. 0 - 10 is just because I've never seen more than 3 comm ports
	//TODO do a handshake with the arduino so we can determine if it is the correct comm port even further
	for(int i = 0 ; i < 10 ; i++){
		//bool equals true or false depending on whether a path exists. path is defined in the constructor.
		handshake = pathExists(path + boost::lexical_cast<std::string>(i) );
		//if it returns true then construct the full path and break the loop.
		if(handshake == true){
			path += boost::lexical_cast<std::string>(i);
			break;
		}
	}

	//output a statement that tells which comm port the program connected to
	cout << "connected on Comm Port: "
			<< path
			<< endl;

	//open comm port
	port.Open(path);
	//set baud rate. This also needs to be set on the arduino
	port.SetBaudRate(SerialStreamBuf::BAUD_115200);
	//set char size.
	port.SetCharSize( SerialStreamBuf::CHAR_SIZE_8 );
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

			case 'M':
				//cout << "Case M Found! " << parse;
				//check if the addressed variable is within the appropriate array bounds
				if(atoi(parse.substr(1,2).c_str()) >= 0 && atoi(parse.substr(1,2).c_str()) <=6 ){

					//populate the correct motor with the correct value
					motor.motor[atoi(parse.substr(1,2).c_str()) - 1] = atoi(message.substr(3,pos).c_str());

					//set cursor to next variable location.
					i = pos;
					//erase parsed values
					corrected.erase(0 , pos + delimiter.length());
				}//end if
				else{
					//reading next char will destroy the bad data by causing a default to occur.
					cout << "number is not within the bounds of the array" << endl;
				}

				break;

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
						kill_switch.killed = true;
						break;
					case 0:
						kill_switch.killed = false;
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





