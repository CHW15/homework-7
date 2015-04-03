/*
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
*/
//#include "earthquake.h"
//#include "station.h"

#include "mutualfunctions.h"
#include "LNK2005errorpass.h"

//using namespace std;

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

// Function for printing the errors and results into the outputfile and terminal

void print_message(ofstream & logfile, const string & statement) {
	logfile << statement;
	cout << statement;
	return;
}

void print_position(ofstream & logfile, int & position) {
	logfile << (position);
	cout << (position);
	return;
}

string uppercase(string & s) {
	string result = s;
	for (int i = 0; i < (int)result.size(); i++)
		result[i] = toupper(result[i]);
	return result;
}

//**********************************************************/