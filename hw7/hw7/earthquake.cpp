/*
#include <iostream>
#include <fstream>
#include <iomanip>
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

#include "earthquake.h"
#include "station.h"
#include <string>

using namespace std;

string earthquake::get_Month_Num2namestr(Months aa) {
	switch (aa) {
	case January:   return "January";
	case February:  return "February";
	case March:     return "March";
	case April:     return "April";
	case May:       return "May";
	case June:      return "June";
	case July:      return "July";
	case August:    return "August";
	case September: return "September";
	case October:   return "October";
	case November:  return "November";
	case December:  return "December";
	}
	exit(EXIT_FAILURE);
}

Months month_num2enum(int a){

	if (a == 1)  return January;
	if (a == 2)  return February;
	if (a == 3)  return March;
	if (a == 4)  return April;
	if (a == 5)  return May;
	if (a == 6)  return June;
	if (a == 7)  return July;
	if (a == 8)  return August;
	if (a == 9)  return September;
	if (a == 10) return October;
	if (a == 11) return November;
	if (a == 12) return December;
	// It should never get here!!
	exit(EXIT_FAILURE);
}

//**************************************************/

void earthquake::set_eventid(string line) {

	//stringstream eventID (line);
	id = line;
	//eq_info.id = line;
}

string earthquake::get_eventid() {
	return id;
}

//**************************************************/

void earthquake::set_earthquake_name(string line) {

	//stringstream eventID (line);
	earthquake_name = line;
	//eq_info.id = line;
}

string earthquake::get_earthquake_name() {
	return earthquake_name;
}

//**************************************************/

void earthquake::set_latitude(string Lat) {

	this->latitude = atof(Lat.c_str());
}

double earthquake::get_latitude() {
	return this->latitude;
}

//**************************************************/

void earthquake::set_longitude(string Long) {

	longitude = atof(Long.c_str());
}

double earthquake::get_longitude() {
	return longitude;
}

//**************************************************/

void earthquake::set_depth(string Depth) {

	depth = atof(Depth.c_str());
	//eq_info.id = line;
}

double earthquake::get_depth() {
	return depth;
}

//**************************************************/

void earthquake::set_date(ofstream & logfile, string & date, string & month, string & day, string & year, int & mm) {

	int dd, yyyy;
	stringstream month1, day1, year1;

	// Check for the date format (it must be mm/dd/year or mm-dd-year and 10 digits)

	if (date.length() == 10) {

		month = date.substr(0, 2);
		month1 << month;
		month1 >> mm;

		day = date.substr(3, 2);
		day1 << day;
		day1 >> dd;

		year = date.substr(6, 4);
		year1 << year;
		year1 >> yyyy;

		//cout << "m : " << mm << "d :" << dd << "y : " << yyyy <<"\n";
		// Meanwhile month, day and year should be valid numbers

		if (!isdigit(date[0]) || !isdigit(date[1]) || !isdigit(date[3]) || !isdigit(date[4])) {
			print_message(logfile, "Error: Date of earthquake is not valid. ");
			//exit (EXIT_FAILURE);
		}

		if (!isdigit(date[6]) || !isdigit(date[7]) || !isdigit(date[8]) || !isdigit(date[9])) {
			print_message(logfile, "Error: Date of earthquake is not valid. ");
			//exit (EXIT_FAILURE);
		} else {
			if (mm < 0 || mm > 13 || dd < 0 || dd > 32 || yyyy < 1850 || yyyy > 2016) {
				print_message(logfile, "Error: Date digits are not valid. ");
				exit(EXIT_FAILURE);
			}
		}

		if ((date[2] != '/' || date[5] != '/') && (date[2] != '-' || date[5] != '-')) {
			print_message(logfile, "Error: Date format is not valid. ");
			//exit (EXIT_FAILURE);
		}

		this->date = date;

		/*
		Date.year = year;
		Date.month = month;
		Date.day = day;
		*/

	} else {
		print_message(logfile, "Error: Date of earthquake is not valid. ");
		//exit (EXIT_FAILURE);
	}
}

string earthquake::get_date() {
	return date;
}

//**************************************************/

void earthquake::set_time(ofstream & logfile, string time, string & hour, string & minute, string & second) {

	int hr, min;
	float  sec = 0;
	stringstream hr1, min1, sec1;
	//earthquake eq_info;

	// Check for the time format (must be hh:mm:ss.fff and 12 digits)

	if (time.length() == 12) {

		hour = time.substr(0, 2);
		hr1 << hour;

		hr1 >> hr;
		minute = time.substr(3, 2);
		min1 << minute;
		min1 >> min;
		second = time.substr(6, 2);
		sec1 << second;
		sec1 >> sec;

		//cout << "hr : " << hr << "min :" << min << "sec : " << sec <<"\n";
		//  Meanwhile the hour, minute, second should be valid numbers

		if (!isdigit(time[0]) || !isdigit(time[1]) || !isdigit(time[3]) || !isdigit(time[4])) {
			print_message(logfile, "Error: time of earthquake is not valid. ");
			exit(EXIT_FAILURE);
		}

		if (!isdigit(time[6]) || !isdigit(time[7]) || !isdigit(time[9]) || !isdigit(time[10]) || !isdigit(time[11])) {
			print_message(logfile, "Error: time of earthquake is not valid. ");
			exit(EXIT_FAILURE);
		}

		if (hr < 0 || hr > 24 || min < 0 || min > 60 || sec < 0.0009 || sec > 59.9999) {
			print_message(logfile, "Error: time digits are not valid. ");
			//exit (EXIT_FAILURE);
		}
		if (time[2] != ':' || time[5] != ':' || time[8] != '.') {
			print_message(logfile, "Error: time format is not valid.");
			//exit (EXIT_FAILURE);
		}

		this->time = time;

		// (Or I could add another struct for time and use atoi(.c_str) command to convert the string into integer
		// and but it needs more set and get functions which I prefered to learn compile and run completely

		/*
		Time.hr = hr';
		Time.min = min;
		Time.sec = sec;
		*/

	} else {
		print_message(logfile, "Error: time of earthquake is not valid.");
		//exit (EXIT_FAILURE);
	}
}

string earthquake::get_time() {
	return time;
}

//**************************************************/

void earthquake::set_time_zone(ofstream & logfile, string time_zone) {

	int tzl = 0;
	string str = time_zone;
	const char *cstr = str.c_str();
	tzl = strlen(cstr);
	if ((tzl != 3) || (!isalpha(time_zone[0])) || (!isalpha(time_zone[1])) || (!isalpha(time_zone[2]))) {
		print_message(logfile, "Error: Time_zone is not valid");
		//exit (EXIT_FAILURE);
	} else {
		timeZone = time_zone;
	}
}

string earthquake::get_time_zone() {
	return timeZone;
}

//**************************************************/

void earthquake::set_magnitude_size(ofstream & logfile, string magnitude_size) {

	int mag_size;
	stringstream mg;
	mg << magnitude_size;
	mg >> mag_size;

	if (mag_size < 0) {
		print_message(logfile, "Error: The magnitude_size is not valid");
		//exit (EXIT_FAILURE);
	} else {
		this->magnitude_size = magnitude_size;
	}
}

string earthquake::get_magnitude_size() {
	return magnitude_size;
}

//**************************************************/

void earthquake::set_magnitude_type(ofstream & logfile, string magnitude_type) {

	// cout << magnitude_type;
	string mt = uppercase(magnitude_type);
	
	if (mt == "ML") { magnitude_type = ML; }
	if (mt == "MS") { magnitude_type = Ms; }
	if (mt == "MB") { magnitude_type = Mb; }
	if (mt == "MW") { magnitude_type = Mw; }

	//print_message(logfile, "Error: The magnitude_type is not valid");
	//exit (EXIT_FAILURE);
}

string earthquake::get_mag_type2str(Mag_type magnitude_type) {

	switch (magnitude_type) {

	case ML:  return "Ml";
	case Mb:  return "Mb";
	case Ms:  return "Ms";
	case Mw:  return "Mw";
	}
	// It should never get here!!
	exit(EXIT_FAILURE);
}

Mag_type str2Mag_type(string & b){

	string ss = uppercase(b);

	if (ss == "ML")  return ML;
	if (ss == "MB")  return Mb;
	if (ss == "MS")  return Ms;
	if (ss == "MW")  return Mw;

	// It should never get here!!
	exit(EXIT_FAILURE);
}

//**************************************************/

// Check the header of the input file
bool check_input_header(ifstream & inputfile, ofstream & outputfile) {

	// Declare variable types:
	// Date & Time variables ("mm/dd/yyyy or mm-dd-yyyy hh:mm:ss.fff time_zone"):

	int mm;

	string date, day, month, year, time, hour, minute, second;
	string line, time_zone, magnitude_type, magnitude_size;
	string longitude, latitude, depth;
	stringstream longt, lat, dep;
	ofstream logfile;

	earthquake eq_info;

	// Check data validation and storing them
	// First line for event ID

	getline(inputfile, line);

	eq_info.set_eventid(line);

	// Second line for date

	inputfile >> date >> time >> time_zone;
	eq_info.set_date(logfile, date, month, day, year, mm);

	eq_info.set_time(logfile, time, hour, minute, second);

	eq_info.set_time_zone(logfile, time_zone);

	// Third line for earthquake name

	inputfile.ignore();
	getline(inputfile, line);
	eq_info.set_earthquake_name(line);

	// Fourth line for epicenter info

	inputfile >> longitude; 
	eq_info.set_longitude(longitude);
	inputfile >> latitude;
	eq_info.set_latitude(latitude);
	inputfile >> depth;
	eq_info.set_depth(depth);

	inputfile >> magnitude_type;

	eq_info.set_magnitude_type(logfile, magnitude_type);
	//get_mag_type2str(eq_info, magnitude_type);

	inputfile >> magnitude_size;
	eq_info.set_magnitude_size(logfile, magnitude_size);

	// Print the header in the outputfile:

	//string a = month_num2enum(mm);

	outputfile << "# " << " "  << day << " " << eq_info.get_Month_Num2namestr(month_num2enum(mm)) << " "<< " " << year << " "
		<< eq_info.get_time() << " " << eq_info.get_time_zone() << " " << eq_info.get_mag_type2str(str2Mag_type(magnitude_type)) << " " << eq_info.get_magnitude_size()
		<< " " << eq_info.get_earthquake_name() << " " << "[" << eq_info.get_eventid() << "]" << "("
		<< eq_info.get_longitude() << "," << " " << eq_info.get_latitude() << "," << " " << eq_info.get_depth() << ")" << "\n";

	return 0;
}