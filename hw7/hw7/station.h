// station class provides functions and parameters 
// in order to read the signal reports from input

enum Band_Type {
	LongPeriod,
	ShortPeriod,
	Broadband
};

enum Months {
	January = 1, February, March, April, May, June, July,
	August, September, October, November, December
};

enum Mag_type {                                  // case insensitive
	ML = 1,
	Ms,
	Mb,
	Mw
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

	bool set_valid_Network_code(station &, string);
	bool set_valid_Station_code(station &, string);
	bool set_valid_Type_of_band(station &, string);
	bool set_valid_Type_of_instrument(station &, string);
	bool set_valid_Orientation(station &, string);

	
	string get_Net_code2namestr(station &);
	string get_Type_of_band2str(station &);
	string get_Station_code(station &);
	string get_Inst_Type2str(station &);
	string get_Orientation(station &);
    string uppercase(string &);
	
	Net_code str2Net_code(string);
	Band_Type str2Band_Type(string);
	Inst_Type Inst_Type_str2enum(string);

private:
	Net_code     net_code;
	string       Station_Name;
	Band_Type    band_type;
	Inst_Type    inst_type;
	string  orientation;
};

//**************************************************/





