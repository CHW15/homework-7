// station class provides functions and parameters 
// in order to read the signal reports from input

#ifndef STATION_H
#define STATION_H

//#include "mutualfunctions.h"
//#include <cstring>

#include "earthquake.h"
//#include "LNK2005errorpass.h"


using namespace std;

enum Band_Type {
	LongPeriod,
	ShortPeriod,
	Broadband
};

enum Net_code {                                  // case sensitive
	CE,
	CI,
	FA,
	NP,
	WR
};

enum Inst_Type {
	HighGain,
	LowGain,
	Accelerometer
};

class station {

public:

	bool set_valid_Network_code(string);
	bool set_valid_Station_code(string);
	bool set_valid_Type_of_band(string);
	bool set_valid_Type_of_instrument(string);
	bool set_valid_Orientation(string);

	string get_Net_code2namestr();
	string get_Type_of_band2str();
	string get_Station_code();
	string get_Inst_Type2str();
	string get_Orientation();

	Net_code str2Net_code(string);
	Band_Type str2Band_Type(string);
	Inst_Type Inst_Type_str2enum(string);

private:
	Net_code    net_code;
	string      Station_Name;
	Band_Type   band_type;
	Inst_Type   inst_type;
	string      orientation;
};

void read_input_signals(ifstream &, ofstream &, station *, int  &, int &, int &, int &);
void print_output(ofstream &, ofstream &, station *, int &, int &, int &, int &);

#endif