#include "earthquake.h"
#include "station.h"

string get_Month_Num2namestr (Months aa) {
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

Months month_num2enum (int a){

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

string get_mag_type2str(Mag_type bb) {
	switch (bb) {
	case ML:  return "Ml";
	case Mb:  return "Mb";
	case Ms:  return "Ms";
	case Mw:  return "Mw";
	}
	// It should never get here!!
	exit(EXIT_FAILURE);
}

Mag_type str2Mag_type(string b){

	string ss = uppercase(b);

	if (ss == "ML")  return ML;
	if (ss == "MB")  return Mb;
	if (ss == "MS")  return Ms;
	if (ss == "MW")  return Mw;

	// It should never get here!!
	exit(EXIT_FAILURE);
}

string get_Net_code2namestr(Net_code cc) {
	switch (cc) {
	case CE:   return "CE";
	case CI:   return "CI";
	case FA:   return "FA";
	case NP:   return "NP";
	case WR:   return "WR";
	}
	// It should never get here!!
	exit(EXIT_FAILURE);
}

Net_code str2Net_code(string c){

	string ss = uppercase(c);

	if (ss == "CE")  return CE;
	if (ss == "CI")  return CI;
	if (ss == "FA")  return FA;
	if (ss == "NP")  return NP;
	if (ss == "WR")  return WR;

	// It should never get here!!
	exit(EXIT_FAILURE);
}

string get_Type_of_band2str (Band_Type dd) {
	switch (dd) {
	case LongPeriod:   return "L";
	case ShortPeriod:  return "B";
	case Broadband:    return "H";
	}
	// It should never get here!!
	exit(EXIT_FAILURE);
}

Band_Type str2Band_Type(string d){

	string ss = uppercase(d);

	if (ss == "L")  return LongPeriod;
	if (ss == "B")  return ShortPeriod;
	if (ss == "H")  return Broadband;

	// It should never get here!!
	exit(EXIT_FAILURE);
}

string get_Inst_Type2str(Inst_Type ee) {
	switch (ee) {
	case HighGain:       return "H";
	case LowGain:        return "L";
	case Accelerometer:  return "N";
	}
	// It should never get here!!
	exit(EXIT_FAILURE);
}

Inst_Type Inst_Type_str2enum (string e){

	string ss = uppercase(e);

	if (ss == "H")  return HighGain;
	if (ss == "L")  return LowGain;
	if (ss == "N")  return Accelerometer;

	// It should never get here!!
	exit(EXIT_FAILURE);
}


// Check the header of the input file
bool check_input_header(ifstream &inputfile, ofstream &outputifle) {

	// Declare variable types:
	// Date & Time variables("mm/dd/yyyy or mm-dd-yyyy hh:mm:ss.fff time_zone"):

	double longitude = 0, latitude = 0, depth = 0;
	int mm;

	string date, day, month, year, time, hour, minute, second; 
	string line, time_zone, magnitude_type, magnitude_size;
	string longitude1, latitude1, depth1;
	stringstream longt, lat, dep;
	ofstream logfile;

	// First line for event ID

	earthquake eq_info;
	//Date date_elements;

	getline(inputfile, line);
	stringstream eventID (line);
	eventID >> eq_info.id;

	

	getline(inputfile, line);
	stringstream datetime (line);
	datetime >> eq_info.date;
	date = eq_info.date;

	datetime >> eq_info.time;
	time = eq_info.time;

	datetime >> eq_info.timeZone;
	time_zone = eq_info.timeZone;

	getline(inputfile, line);
	eq_info.earthquake_name = line;

	getline(inputfile, line);
	stringstream epicenter (line);

	epicenter >> eq_info.longtidue;
	longitude1 = eq_info.longtidue;
	longt << longitude1;
	longt >> longitude;

	epicenter >> eq_info.latitude;
	latitude1 = eq_info.latitude;
	lat << latitude1;
	lat >> latitude;

	epicenter >> eq_info.depth;
	depth1 = eq_info.depth;
	dep << depth1;
	dep >> depth;

	epicenter >> eq_info.magnitude_type;
	magnitude_type = eq_info.magnitude_type;

	epicenter >> eq_info.magnitude_size;
	magnitude_size = eq_info.magnitude_size;

	// check the stored data validation

	//string get_Month_Num2namestr, day, year;

	check_date(logfile, date, month, day, year, mm);
	check_time(logfile, time, hour, minute, second);
	check_time_zone(logfile, time_zone);
	check_magnitude(logfile, eq_info.magnitude_type, eq_info.magnitude_size);

	// Print the header in the outputifle:

	outputifle << "# " << " " << get_Month_Num2namestr(month_num2enum(mm)) << " " << day << " " << year << " " 
		<< time << " " << time_zone << " " << magnitude_type << " " << magnitude_size 
		<< " " << eq_info.earthquake_name << " " << "[" << eq_info.id << "]" << "(" 
		<< longitude << "," << " " << latitude << "," << " " << depth << ")" << "\n";

	return 0;
}