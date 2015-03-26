


// Check the table of reports from input file and return the signals output
bool check_input_signals(ifstream & inputfile, station entry[MAXvalidentry], int valid_entries, int invalidEntries, int produced_signalnum) {

	int entry_pos = 0;

	ofstream logfile;
	ofstream outputfile;
	string net_code, Station_Name, band_type, inst_type, orientation;
	string string;

	// check the stored data validation

	while (valid_entries < MAXvalidentry) {             // or wile inputfile.eof()

		int m = -1;

		cout << "reading signals";

		inputfile >> net_code;

		entry_pos++;

		if (!is_valid_Network_code(net_code)) {
			print_message(logfile, "Error: Entry # ");
			print_position(logfile, entry_pos);
			print_message(logfile, "ignored. Invalid_Network_code");
			m++;
			return true;
		}

		cout << entry_pos;

		entry_pos++;
		inputfile >> Station_Name;
		if (!is_valid_Station_code(Station_Name)) {
			print_message(logfile, "Error: Entry # ");
			print_position(logfile, entry_pos);
			print_message(logfile, "ignored. Invalid_Station_code");
			m++;
			return true;
		}

		entry_pos++;
		inputfile >> band_type;
		if ( !is_valid_Type_of_band(band_type)) {
			print_message(logfile, "Error: Entry # ");
			print_position(logfile, entry_pos);
			print_message(logfile, "ignored. Invalid Type_of_band");
			m++;
			return true;
		}

		entry_pos++;
		inputfile >> inst_type;
		if ( !is_valid_Type_of_instrument(inst_type)) {
			print_message(logfile, "Error: Entry # ");
			print_position(logfile, entry_pos);
			print_message(logfile, "ignored. Invalid Type_of_band");
			m++;
			return true;
		}

		entry_pos++;
		inputfile >> orientation;
		if ( !is_valid_Orientation(orientation)) {
			print_message(logfile, "Error: Entry # ");
			print_position(logfile, entry_pos);
			print_message(logfile, "ignored. as an invalid Orientation");
			m++;
			return true;
		}

		if (m = (-1)) {

			valid_entries++;
			produced_signalnum = produced_signalnum + orientation.size(); 

			entry[valid_entries].net_code     =  str2Net_code(net_code);
			entry[valid_entries].Station_Name =  Station_Name;
			entry[valid_entries].band_type    =  str2Band_Type(band_type);
			entry[valid_entries].inst_type    =  Inst_Type_str2enum(inst_type);
			entry[valid_entries].orientation  =  orientation;

			return true;

		} else {
			invalidEntries++;
		}
		return false;
	}
}

void print_output(ofstream & outputfile, ofstream & logfile, station entry[MAXvalidentry], int valid_entries, int invalidEntries, int produced_signalnum) {

	string orientation;
	int length = orientation.length();
	int length1 = abs (length);


	// print all the signals to the output file
	for (int i = 0; i < valid_entries; i++) {
		for (int j = 0; j < length1; j++) {

			stringstream records;
			records << entry[valid_entries].net_code << ".";
			records << entry[valid_entries].Station_Name << ".";
			records << entry[valid_entries].band_type;
			records << entry[valid_entries].inst_type;
			records << entry[valid_entries].orientation[j] << endl;

			outputfile << records.str();
			cout << records.str();
		}
	}

	outputfile << valid_entries << "\n";
	print_message(logfile, "invalid entries ignored:");
	print_position(logfile, invalidEntries);
	print_message(logfile, "valid entries read:");
	print_position(logfile, valid_entries);
	print_message(logfile, "signal name produced");
	print_position(logfile, cout, produced_signalnum);
	print_message(logfile, "Finished!");

	outputfile.close();
}