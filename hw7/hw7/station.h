// station class provides functions and parameters 
// in order to read the signal reports from input

class station {

public:
	
	string get_mag_type2str(Mag_type);
	string get_Net_code2namestr(Net_code);
	string get_Type_of_band2str(Band_Type);
	string get_Inst_Type2str(Inst_Type);

	Mag_type str2Mag_type(string);
	Net_code str2Net_code(string);
	Band_Type str2Band_Type(string);
	Inst_Type Inst_Type_str2enum (string);

private:
	Net_code     net_code;
	Band_Type    band_type;
	Inst_Type    inst_type;
	string       Station_Name;
	string  orientation;
};

