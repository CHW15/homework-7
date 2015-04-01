#include "earthquake.h"
#include "station.h"

using namespace std;

string uppercase(string & s) {
	string result = s;
	for (int i = 0; i < (int)result.size(); i++)
		result[i] = toupper(result[i]);
	return result;
}

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



Inst_Type station::Inst_Type_str2enum (string e){

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