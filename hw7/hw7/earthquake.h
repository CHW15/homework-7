// earthquake class provides functions and parameters 
// in order to read the input header and check if it is valid

#ifndef EARTHQUAKE_H
#define EARTHQUAKE_H

//using namespace std;
//#include <cstring>

#include "mutualfunctions.h"
//#include "LNK2005errorpass.h"



enum Months {
	January = 1, February, March, April, May, June, July,
	August, September, October, November, December
};

enum Mag_type {                                  // case insensitive
	ML,
	Ms,
	Mb,
	Mw
};

class earthquake {

public:
	void set_eventid(string);
	void set_earthquake_name(string);
	void set_latitude(string);
	void set_longitude(string);
	void set_depth(string);
	void set_date(ofstream &, string &, string &, string &, string &, int &);
	void set_time(ofstream &, string, string &, string &, string &);
	void set_time_zone(ofstream &, string);
	void set_magnitude_size(ofstream &, string);
	void set_magnitude_type(ofstream &, string);

	double get_latitude();
	double get_longitude();
	double get_depth();

	string get_eventid();
	string get_earthquake_name();
	string get_mag_type2str(Mag_type);
	string get_date();
	string get_time();
	string get_time_zone();
	string get_magnitude_size();
	string get_Month_Num2namestr(Months);

private:
	string id;
	string date;
	string time;
	string timeZone;
	string earthquake_name;
	double latitude;
	double longitude;
	Mag_type magnitude_type;
	string magnitude_size;
	double depth;
};

Months month_num2enum(int);
Mag_type str2Mag_type(string &);
bool check_input_header(ifstream &, ofstream &);

#endif