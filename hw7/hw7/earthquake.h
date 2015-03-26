// earthquake class provides functions and parameters 
// in order to read the input header and check if it is valid

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

class earthquake {

public:
	bool is_valid_date(int &, int &, int &);
	bool is_valid_time(int, int, int);

	string get_Month_Num2namestr(Months);
	string uppercase(string &);
	
	Months month_num2enum(int);

private:
	string id;
	string date;
	string time;
	string timeZone;
	string earthquake_name;
	string latitude;
	string longtidue;
	string magnitude_type;
	string magnitude_size;
	string depth;
};

void check_date(ofstream & logfile, string & date, string & month, string & day, string & year, int & mm) {

	int dd, yyyy;
	stringstream month1, day1, year1;

	// Check for the date format (it must be mm/dd/year or mm-dd-year and 10 digits)

	if (date.length() == 10) {

		month = date.substr(0, 2);
		month1 << month;
		month1 >> mm;

		string day = date.substr(3, 2);
		day1 << day;
		day1 >> dd;
		string year = date.substr(6, 4);

		year1 << year;
		year1 >> yyyy;

		//cout << "m : " << mm << "d :" << dd << "y : " << yyyy <<"\n";
		// Meanwhile month, day and year should be valid numbers

		if (!isdigit (date[0]) || !isdigit (date[1]) || !isdigit (date[3]) ||!isdigit (date[4])) {
			print_message(logfile, "Error: Date of earthquake is not valid. ");
			exit (EXIT_FAILURE);
		}

		if (!isdigit (date[6]) || !isdigit (date[7]) || !isdigit (date[8]) || !isdigit (date[9])) {
			print_message(logfile, "Error: Date of earthquake is not valid. ");
			//exit (EXIT_FAILURE);
		} else {
			if (mm < 0 || mm > 13 || dd < 0 || dd > 32 || yyyy < 1850 || yyyy > 2016) {
				print_message(logfile, "Error: Date digits are not valid. ");
				exit (EXIT_FAILURE);
			}
		}

		if ((date[2] != '/' || date[5] != '/') && (date[2] != '-' || date[5] != '-')) {
			print_message(logfile, "Error: Date format is not valid. ");
			exit (EXIT_FAILURE);
		} 
	} else {
		print_message(logfile, "Error: Date of earthquake is not valid. ");
		exit (EXIT_FAILURE);
	}
}


void check_time(ofstream & logfile, string time, string & hour, string & minute, string & second) {

	int hr, min;
	float  sec = 0;
	stringstream hr1,min1,sec1;
	earthquake eq_info;

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

		if (!isdigit (time[0]) || !isdigit (time[1]) || !isdigit (time[3]) ||!isdigit (time[4])) {
			print_message(logfile, "Error: time of earthquake is not valid. ");
			exit (EXIT_FAILURE);
		}

		if (!isdigit (time[6]) || !isdigit (time[7]) || !isdigit (time[9]) || !isdigit (time[10]) || !isdigit (time[11])) {
			print_message(logfile, "Error: time of earthquake is not valid. ");
			exit (EXIT_FAILURE);
		}

		if (hr < 0 || hr > 24 || min < 0 || min > 60 || sec < 0.0009 || sec > 59.9999 ) {
			print_message(logfile, "Error: time digits are not valid. ");
			//exit (EXIT_FAILURE);
		}
		if (time[2] != ':' || time[5] != ':' || time[8] != '.') {
			print_message(logfile, "Error: time format is not valid.");
			//exit (EXIT_FAILURE);
		} 
	} else {
		print_message(logfile, "Error: time of earthquake is not valid.");
		//exit (EXIT_FAILURE);
	}
}

void check_time_zone(ofstream & logfile, string time_zone) {

	int tzl = 0;
	string str = time_zone;
	const char *cstr = str.c_str();
	tzl = strlen(cstr);
	if ((tzl != 3) || (!isalpha (time_zone[0])) || (!isalpha (time_zone[1])) || (!isalpha (time_zone[2]))) {
		print_message(logfile, "Error: Time_zone is not valid");
		//exit (EXIT_FAILURE);
	}
}

// Functions for converting the entries to uppercase and check for validation 

string uppercase(string & s) {
	string result = s;
	for (int i = 0; i < (int)result.size(); i++)
		result[i] = toupper(result[i]);
	return result;
}

void check_magnitude(ofstream & logfile, string magnitude_type, string magnitude_size) {

	int mag_size;
	stringstream mg;
	mg << magnitude_size;
	mg >> mag_size;

	if ( mag_size < 0 ) {
		print_message(logfile, "Error: The magnitude_size is not valid");
		//exit (EXIT_FAILURE);
	}
	cout << magnitude_type;
	string mt = uppercase(magnitude_type);
	if ((mt != "ML") && (mt != "MS") && (mt != "MB") && (mt != "MW")) {
		print_message(logfile, "Error: The magnitude_type is not valid");
		//exit (EXIT_FAILURE);
	}
}

