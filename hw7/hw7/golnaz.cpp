/****************************************************************************************************
* Programming Tools for  Engineers and Scientists - HW7
* by Golnaz Sarram
* March 20th, 2015

* Github Repoitory: https://github.com/Golnaz15

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

using namespace std;

static const int MAXvalidentry = 300;

string   inputfilename = "golnaz.in", outputfilename = "golnaz.out", logfilename = "golnaz.log";

//================================= Function Prototypes ==================================/

bool read_input(string, string, int, int &, int);
bool check_input_header(ifstream &, ofstream &);
bool set_valid_Network_code(station &, string);
bool set_valid_Station_code(station &, string);
bool set_valid_Type_of_band(station &, string);
bool set_valid_Type_of_instrument(station &, string);
bool set_valid_Orientation(station &, string);

void read_input_signals(ifstream &, ofstream &, station entry[MAXvalidentry], int&, int&, int&);
void print_message(ofstream &, const string &);
void print_position(ofstream &, int &);
void open_input(ifstream &, ofstream &, ostream &, string);
void open_file(ofstream &, ostream &, string);
void print_output(ofstream &, ofstream &, station entry[MAXvalidentry], int &, int &, int&);
void set_eventid(earthquake&, ifstream &, string);
void set_date(earthquake &, ofstream &, string &, string &, string &, string &, int &);
void set_time(earthquake &, ofstream &, string, string &, string &, string &);
void set_time_zone(earthquake &, ofstream &, string);
void set_magnitude_size(earthquake &, ofstream &, string);
void set_magnitude_type(earthquake &, ofstream &, string);

string get_Month_Num2namestr(Months);
string get_mag_type2str(Mag_type);
string uppercase(string &);
string get_eventid();
string get_date();
string get_time();
string get_time_zone() {
string get_magnitude_size();
string get_mag_type2str(string);
string get_Net_code2namestr(station &);
string get_Type_of_band2str(station &);
string get_Station_code(station &);
string get_Inst_Type2str(station &);
string get_Orientation(station &);

Months month_num2enum(int);
Mag_type str2Mag_type(string);
Net_code str2Net_code(string);
Band_Type str2Band_Type(string);
Inst_Type Inst_Type_str2enum(string);

//=========================================================================================/

int main() {

	string station_code;
	ifstream inputfile;
	ofstream outputfile, logfile;
	station entry[MAXvalidentry];
	string net_code;

	int valid_entries = 0, invalidEntries = 0, produced_signalnum = 0;

	// Generating the inputfile, outputfile and logfile

	print_message(logfile, "opening file: the input.in ");
	print_message(logfile, "\n");
	open_input(inputfile, logfile, cout, inputfilename);
	open_file(logfile, cout, "golnaz.log");
	open_file(outputfile, cout, "golnaz.out");

	// Calling the read_input function

	print_message(logfile, "processing input...");
	print_message(logfile, "\n");
	check_input_header(inputfile, outputfile);
	print_message(logfile, "header is read successfully!");
	print_message(logfile, "\n");
	
	read_input_signals(inputfile, outputfile, entry, valid_entries, invalidEntries, produced_signalnum);
	//print_output(outputfile, logfile, entry, valid_entries, invalidEntries, produced_signalnum);
	print_message(logfile, "signals are read correctly!");

	inputfile.close();
	outputfile.close();

	//getchar();
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

//**********************************************************/

// Check the header of the input file
bool check_input_header(ifstream & inputfile, ofstream & outputfile) {

	// Declare variable types:
	// Date & Time variables ("mm/dd/yyyy or mm-dd-yyyy hh:mm:ss.fff time_zone"):

	int mm;

	string date, day, month, year, time, hour, minute, second;
	string line, time_zone, magnitude_type, magnitude_size;
	string longitude1, latitude1, depth1;
	stringstream longt, lat, dep;
	ofstream logfile;

	earthquake eq_info;

	// Check data validation and storing them
	// First line for event ID

	getline(inputfile, line);

	set_eventid(eq_info, inputfile, line);

	// Second line for date

	inputfile >> date >> time >> time_zone;
	set_date(eq_info, logfile, date, month, day, year, mm);

	set_time(eq_info, logfile, time, hour, minute, second);
	get_time (eq_info);

	set_time_zone(eq_info, logfile, time_zone);

	// Third line for earthquake name

	inputfile.ignore();
	getline(inputfile, line);
	eq_info.earthquake_name(line);

	// Fourth line for epicenter info

	inputfile >> eq_info.latitude;
	inputfile >> eq_info.longitude;
	inputfile >> eq_info.depth;

	inputfile >> magnitude_type;

	set_magnitude_type(eq_info, logfile, magnitude_type);
	//get_mag_type2str(eq_info, magnitude_type);

	inputfile >> magnitude_size;
	set_magnitude_size(eq_info, logfile, magnitude_size);

	// Print the header in the outputfile:

	outputfile << "# " << " " << get_Month_Num2namestr(month_num2enum(mm)) << " " << day << " " << year << " "
		<< eq_info.get_time << " " << eq_info.get_time_zone << " " << eq_info.get_mag_type2str << " " << eq_info.get_magnitude_size
		<< " " << eq_info.get_earthquake_name << " " << "[" << eq_info.id << "]" << "("
		<< eq_info.longitude << "," << " " << eq_info.latitude << "," << " " << eq_info.depth << ")" << "\n";

	return 0;
}

// Check the table of reports from input file and return the signals output
void read_input_signals(ifstream & inputfile, ofstream& outputfile, station entry[MAXvalidentry], int  & valid_entries, int & invalidEntries, int & produced_signalnum) {

	int entry_pos = 0;

	ofstream logfile;
	string Net_code, Station_Name, band_Type, inst_type, orientation;
	string string, temp_holder;
	int i = 0;
	// check the stored data validation

	//inputfile >> temp_holder;

	//for (int i = 0; inputfile. != NULL && valid_entries < MAXvalidentry; i++) {             // or wile inputfile.eof()
	while ((inputfile >> Net_code) && valid_entries < MAXvalidentry) {
		int m = -1;

		entry_pos++;
		if (!set_valid_Network_code(entry[i], Net_code)) {
			print_message(logfile, "Error: Entry # ");
			print_position(logfile, entry_pos);
			print_message(logfile, " ignored. Invalid_Network_code");
			print_message(logfile, "\n");
			m++;
		}

		inputfile >> Station_Name;
		if (!set_valid_Station_code(entry[i], Station_Name)) {
			print_message(logfile, "Error: Entry # ");
			print_position(logfile, entry_pos);
			print_message(logfile, " ignored. Invalid_Station_code");
			print_message(logfile, "\n");
			m++;

		} else {
			entry[i].Station_Name = Station_Name;
		}

		inputfile >> band_Type;
		if (!set_valid_Type_of_band(entry[i], band_Type)) {
			print_message(logfile, "Error: Entry # ");
			print_position(logfile, entry_pos);
			print_message(logfile, " ignored. Invalid Type_of_band");
			print_message(logfile, "\n");
			m++;

		} else {
			entry[i].band_type = str2Band_Type(band_Type);     
		}

		inputfile >> inst_type;
		if (!set_valid_Type_of_instrument(entry[i], inst_type)) {
			print_message(logfile, "Error: Entry # ");
			print_position(logfile, entry_pos);
			print_message(logfile, " ignored. Invalid Type_of_band");
			print_message(logfile, "\n");
			m++;

		} else { 
			entry[i].inst_type = Inst_Type_str2enum(inst_type);
		}

		inputfile >> orientation;
		if (!set_valid_Orientation(entry[i], orientation)) {
			print_message(logfile, "Error: Entry # ");
			print_position(logfile, entry_pos);
			print_message(logfile, " ignored. as an invalid Orientation");
			print_message(logfile, "\n");
			m++;

		} else {
			entry[i].orientation = orientation;
		}

		if (m == -1) {

			valid_entries++;
			produced_signalnum = produced_signalnum + orientation.size();

			print_output(outputfile, logfile, entry, valid_entries, invalidEntries, produced_signalnum);

		} else {
			invalidEntries++;
		}
		i++;
	}

	outputfile << valid_entries << "\n";
	print_message(logfile, "invalid entries ignored:");
	print_position(logfile, invalidEntries);
	print_message(logfile, "\n");
	print_message(logfile, "valid entries read:");
	print_position(logfile, valid_entries);
	print_message(logfile, "\n");
	print_message(logfile, "signal name produced:");
	print_position(logfile, produced_signalnum);
	print_message(logfile, "\n");
	print_message(logfile, "Finished!");
	print_message(logfile, "\n");

}

void print_output(ofstream & outputfile, ofstream & logfile, station entry[MAXvalidentry], int & valid_entries, int & invalidEntries, int & produced_signalnum) {

	// print all the signals to the output file

	string orientation;

	for (int i = 0; i < valid_entries; i++) {
		orientation = get_Orientation(entry[i]);

		for (int j = 0; j < (int) orientation.length(); j++) {
			stringstream records;
			records << get_Net_code2namestr(entry[i]) << "." ;
			records << get_Type_of_band2str(entry[i]) << ".";
			records << get_Station_code(entry[i]);
			records << get_Inst_Type2str(entry[i]);
			records << orientation[j] << "\n";

			outputfile << records.str();
		}
	}
}