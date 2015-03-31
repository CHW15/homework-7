// earthquake class provides functions and parameters 
// in order to read the input header and check if it is valid

class earthquake {

public:
	void set_eventid(earthquake&, ifstream &, string);
	void set_date(earthquake &, ofstream &, string &, string &, string &, string &, int &);
	void set_time(earthquake &, ofstream &, string, string &, string &, string &);
	void set_time_zone(earthquake &, ofstream &, string);
	void set_magnitude_size(earthquake &, ofstream &, string);
	void set_magnitude_type(earthquake &, ofstream &, string);

	string get_mag_type2str(Mag_type);
	string uppercase(string &);
	string get_eventid(earthquake);
	string get_date(earthquake &);
	string get_time(earthquake &);
	string get_magnitude_size(earthquake &);
	string get_mag_type2str(earthquake, string);
	string get_Month_Num2namestr(Months);

	Months month_num2enum(int);

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