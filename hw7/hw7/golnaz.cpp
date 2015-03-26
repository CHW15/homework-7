/****************************************************************************************************
* Programming Tools for  Engineers and Scientists - HW7
* by Golnaz Sarram
* March 23th, 2015

* Github Repoitory: https://github.com/Golnaz15/homework5/blob/master/Project2/Project2/golnaz.cpp

* Homework Description:
* This code will check a collection reports of earthquake event from sesmic stations
* using arrays, enumerators, and structures. It creats an output file and a log file.
****************************************************************************************************/

// Calling external libraries

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <ostream>
#include <cstdlib>
#include <sstream>
#include <istream>
#include <stdio.h>
#include <vector>
#include <stdlib.h>
#include <numeric>
#include <cstring>
#include <cctype>
#include "earthquake.h"
#include "station.h"
#include "earthquake.cpp"
#include "station.cpp"

using namespace std;

static const int MAXvalidentry = 300;

// Defining the main struct of event report propertires

string   inputfilename = "golnaz.in", outputiflename = "golnaz.out", logfilename = "golnaz.log";

//================================= Function Prototypes ==================================/

bool is_valid_magnitude_type(string);
bool is_valid_Network_code(string);
bool is_valid_Station_code(string);
bool is_valid_Type_of_band(string);
bool is_valid_Type_of_instrument(string, Inst_Type inst_type);
bool is_valid_Orientation(string);

bool read_input(string, string, int, int &, int);
bool check_input_header(ifstream &, ofstream &);
bool check_input_signals(ifstream &, station entry[MAXvalidentry], int, int, int);

void print_message(ofstream &, const string &);
void print_position(ofstream &, ostream &, int &);
void open_input(ifstream &, ofstream &, ostream &, string);
void open_file(ofstream &, ostream &, string);
void print_output(ofstream &, ofstream &, station, int, int, int);

//=========================================================================================/

int main() {

	string station_code;
	ifstream inputfile;
	ofstream outputfile,logfile;
	station entry[MAXvalidentry];
	string net_code;

	int valid_entries = 0, invalidEntries = 0, produced_signalnum = 0;

	// Generating the inputfile, outputifle and logfile

	open_input(inputfile, logfile, cout, inputfilename);

	open_file(logfile, cout, "golnaz.log");
	open_file(outputfile, cout, "golnaz.out");

	// Calling the read_input function

	check_input_header(inputfile, outputfile);
	print_message ( logfile, "header is read successfully!" );

	check_input_signals(inputfile, entry, valid_entries, invalidEntries, produced_signalnum);
	print_output(outputfile, logfile, entry[MAXvalidentry], valid_entries, invalidEntries, produced_signalnum);
	print_message ( logfile, "signals are read correctly!" );

	inputfile.close();
	outputfile.close();

	getchar();
	return 0;
}

//================================ Declare functions =====================================/

// Function for openning inputfile and logfile

void open_file(ofstream & file, ostream & stream, string filename) {

	file.open(filename.c_str());

	if (file.fail()) {
		print_message(file, "Error: cannot open the file. ");
		exit(EXIT_FAILURE);
	}
}

void open_input(ifstream &inputfile, ofstream & logfile, ostream & stream, string inputfilename) {

	// Prompt the user for an input file
	cout << "Enter input file name: ";
	cin >> inputfilename;

	inputfile.open(inputfilename.c_str());

	if (inputfile.fail()) {
		print_message(logfile, "Error: reading the file. ");
		exit(EXIT_FAILURE);
	}
}

// Function for printing the errors and results into the outputifle and terminal

void print_message(ofstream & logfile, const string & statement) {
	logfile << statement << "\n";
	cout << statement << "\n";
	return;
}

void print_position(ofstream & logfile, int & position) {
	logfile << (position) << "\n";
	cout << (position) << "\n";
	return;
}

//======================= check validity functions ==========================/

// Functions for input header inorder to check date and time validation 

bool is_valid_Network_code(string net_code) {

	if (net_code.compare("CE") == 0 ) return true;
	if (net_code.compare("CI") == 0 ) return true;
	if (net_code.compare("FA") == 0 ) return true;
	if (net_code.compare("NP") == 0 ) return true;
	if (net_code.compare("WR") == 0 ) return true;
	else return false;
}

bool is_valid_Station_code(string Stati_code) { 

	// 3 capital alphabetic character or 5 numeric characters

	if (Stati_code.length() == 5) {
		for (int i = 0; i < 4; i++) {
			if (isdigit(Stati_code[i])) {
				return true;
			}
		}
	}

	if (Stati_code.length() == 3) {
		for (int i = 0; i < 4; i++) {
			if (isalpha(Stati_code[i])) {
				if (isupper(Stati_code[i])) {
					return true;
				}
			}
		}
	}
	return false;
}

bool is_valid_Type_of_band(string Band_type) {

	string ss = uppercase(Band_type);
	if (ss == "LONG-PERIOD") {
		//band_type = LongPeriod;
		return true;
	}
	if (ss == "SHORT_PERIOD") {
		//band_type = ShortPeriod;
		return true;
	}
	if (ss == "BROADBAND") {
		//band_type = Broadband;
		return true;
	}
	return false;
}

bool is_valid_Type_of_instrument(string instrumenType) {

	string ss = uppercase(instrumenType);
	if (ss == "HIGH-GAIN") {
		//inst_type = HighGain;
		return true;
	}
	if (ss == "LOW-GAIN") {
		//inst_type = LowGain;
		return true;
	}
	if (ss == "ACCELEROMETER") {
		//inst_type = Accelerometer;
		return true;
	}
	return false;
}

bool is_valid_Orientation (string orientation) {

	// It is case insensitive so convert it to the uppercase and compare it

	string ss = uppercase(orientation);
	int length = ss.length();
	int length1 = abs (length);

	if (length1 < 4) {
		if (isdigit(ss[0])) {
			for (int i = 0; i < length1; i++) {
				if (!isdigit(ss[i])) {
					return false;
				}
			}

			return true;
		} else if (isalpha(ss[0])) {
			for (int i = 0; i < length1; i++) {
				if (ss[i] != 'N' && ss[i] != 'E' && ss[i] != 'Z') {
					return false;
				}
			}
			return true;
		}
	}
	return false;
} 

//=========================== set & get functions ================================/



