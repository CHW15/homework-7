
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
#include "station.h"
#include "LNK2005errorpass.h"
//#include "mutualfunctions.h"

//using namespace std;

//**************************************************/

bool station::set_valid_Network_code(string Net_code) {          // mashkukam be in?!

	if (Net_code.compare("CE") == 0) {
		net_code = CE;
		return true;
	}

	if (Net_code.compare("CI") == 0) {
		net_code = CI;
		return true;
	}

	if (Net_code.compare("FA") == 0) {
		net_code = FA;
		return true;
	}

	if (Net_code.compare("NP") == 0) {
		net_code = NP;
		return true;
	}

	if (Net_code.compare("WR") == 0) {
		net_code = WR;
		return true;
	}

	else return false;
}

string station::get_Net_code2namestr() {
	switch (net_code) {
	case CE:   return "CE";
	case CI:   return "CI";
	case FA:   return "FA";
	case NP:   return "NP";
	case WR:   return "WR";
	}
	// It should never get here!!
	exit(EXIT_FAILURE);
}

Net_code station::str2Net_code(string nt){

	string ss = uppercase(nt);                                         // bayad case sensitive bashad ke pas !?

	if (ss == "CE")  return CE;
	if (ss == "CI")  return CI;
	if (ss == "FA")  return FA;
	if (ss == "NP")  return NP;
	if (ss == "WR")  return WR;

	// It should never get here!!
	exit(EXIT_FAILURE);
}

//**************************************************/

bool station::set_valid_Station_code(string Stati_code) {

	// 3 capital alphabetic character or 5 numeric characters

	if (Stati_code.length() == 5) {
		for (int i = 0; i < 4; i++) {
			if (isdigit(Stati_code[i])) {
				Station_Name = Stati_code;
				return true;
			}
		}
	}

	if (Stati_code.length() == 3) {
		for (int i = 0; i < 4; i++) {
			if (isalpha(Stati_code[i])) {
				if (isupper(Stati_code[i])) {
					Station_Name = Stati_code;
					return true;
				}
			}
		}
	}	

	return false;
}

string station::get_Station_code() {
	return Station_Name;
}

//**************************************************/

bool station::set_valid_Type_of_band(string Band_type) {

	string ss = uppercase(Band_type);
	if (ss == "LONG-PERIOD") {
		band_type = LongPeriod;
		return true;
	}
	if (ss == "SHORT-PERIOD") {
		band_type = ShortPeriod;
		return true;
	}
	if (ss == "BROADBAND") {
		band_type = Broadband;
		return true;
	}
	return false;
}

string station::get_Type_of_band2str() {
	switch (band_type) {
	case LongPeriod:   return "L";
	case ShortPeriod:  return "B";
	case Broadband:    return "H";
	}
	// It should never get here!!
	exit(EXIT_FAILURE);
}

Band_Type station::str2Band_Type(string d) {

	string ss = uppercase(d);

	if (ss == "LONG-PERIOD")  
		return LongPeriod;
	else if (ss == "SHORT_PERIOD")  
		return ShortPeriod;
	else 
		return Broadband;

	// It should never get here!!
	//exit(EXIT_FAILURE);
}

//**************************************************/

bool station::set_valid_Type_of_instrument(string instrumenType) {

	string ss = uppercase(instrumenType);
	if (ss == "HIGH-GAIN") {
		inst_type = HighGain;
		return true;
	}
	if (ss == "LOW-GAIN") {
		inst_type = LowGain;
		return true;
	}
	if (ss == "ACCELEROMETER") {
		inst_type = Accelerometer;
		return true;
	}
	return false;
}

string station::get_Inst_Type2str() {
	switch (inst_type) {
	case HighGain:       return "H";
	case LowGain:        return "L";
	case Accelerometer:  return "N";
	}
	// It should never get here!!
	exit(EXIT_FAILURE);
}



Inst_Type station::Inst_Type_str2enum(string e){

	string ss = uppercase(e);

	if (ss == "HIGH-GAIN")  return HighGain;
	else if (ss == "LOW-GAIN")  return LowGain;
	else return Accelerometer;

}

//**************************************************/

bool station::set_valid_Orientation(string orientation) {

	// It is case insensitive so convert it to the uppercase and compare it

	string ss = uppercase(orientation);
	int length = ss.length();
	int length1 = abs(length);

	if (length1 < 4) {
		if (isdigit(ss[0])) {
			for (int i = 0; i < length1; i++) {
				if (!isdigit(ss[i])) {
					return false;
				}
			}

			orientation = ss;

			return true;
		}
		else if (isalpha(ss[0])) {
			for (int i = 0; i < length1; i++) {
				if (ss[i] != 'N' && ss[i] != 'E' && ss[i] != 'Z') {
					return false;
				}
			}

			orientation = ss;

			return true;
		}
	}
	return false;
}

string station::get_Orientation() {
	return orientation;
}

// Check the table of reports from input file and return the signals output
void read_input_signals(ifstream & inputfile, ofstream& outputfile, station (&entry)[MAXvalidentry], int  & valid_entries, int & invalidEntries, int & produced_signalnum) {

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
		if (!entry[i].set_valid_Network_code(Net_code)) {
			print_message(logfile, "Error: Entry # ");
			print_position(logfile, entry_pos);
			print_message(logfile, " ignored. Invalid_Network_code");
			print_message(logfile, "\n");
			m++;
		} else {
			entry[i].set_valid_Network_code(Net_code);

			inputfile >> Station_Name;
			if (!entry[i].set_valid_Station_code(Station_Name)) {
				print_message(logfile, "Error: Entry # ");
				print_position(logfile, entry_pos);
				print_message(logfile, " ignored. Invalid_Station_code");
				print_message(logfile, "\n");
				m++;

			} else {
				entry[i].set_valid_Station_code(Station_Name);
			}

			inputfile >> band_Type;
			if (!entry[i].set_valid_Type_of_band(band_Type)) {
				print_message(logfile, "Error: Entry # ");
				print_position(logfile, entry_pos);
				print_message(logfile, " ignored. Invalid Type_of_band");
				print_message(logfile, "\n");
				m++;

			} else {
				entry[i].set_valid_Type_of_band(band_Type);     
			}

			inputfile >> inst_type;
			if (!entry[i].set_valid_Type_of_instrument(inst_type)) {
				print_message(logfile, "Error: Entry # ");
				print_position(logfile, entry_pos);
				print_message(logfile, " ignored. Invalid Type_of_band");
				print_message(logfile, "\n");
				m++;

			} else { 

				entry[i].set_valid_Type_of_instrument(inst_type);
			}

			inputfile >> orientation;
			if (!entry[i].set_valid_Orientation(orientation)) {
				print_message(logfile, "Error: Entry # ");
				print_position(logfile, entry_pos);
				print_message(logfile, " ignored. as an invalid Orientation");
				print_message(logfile, "\n");
				m++;

			} else {
				entry[i].set_valid_Orientation(orientation);
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
}

	void print_output(ofstream & outputfile, ofstream & logfile, station entry[MAXvalidentry], int & valid_entries, int & invalidEntries, int & produced_signalnum) {

		// print all the signals to the output file

		string orientation;

		for (int i = 0; i < valid_entries; i++) {
			orientation = entry[i].get_Orientation();

			for (int j = 0; j < (int) orientation.length(); j++) {
				stringstream records;
				records << entry[i].get_Net_code2namestr() << "." ;
				records << entry[i].get_Type_of_band2str() << ".";
				records << entry[i].get_Station_code();
				records << entry[i].get_Inst_Type2str();
				//records << entry[i].get_Orientation() << "\n";
				records << orientation[j] << "\n";

				outputfile << records.str();
			}
		}
	}