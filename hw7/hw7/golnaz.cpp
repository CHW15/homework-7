/****************************************************************************************************
* Programming Tools for  Engineers and Scientists - HW7
* by Golnaz Sarram
* March 20th, 2015

* Github Repoitory: https://github.com/Golnaz15

* Homework Description:
* This code will check a collection reports of earthquake event from sesmic stations
* using arrays, enumerators, and structures. It creats an output file and a log file.
****************************************************************************************************/

// Calling external libraries


#include "station.h"
//#include "LNK2005errorpass.h"

using namespace std;

//=========================================================================================/

int main() {

	string inputfilename;
	const string logfilename = "golnaz.log";
	const string outputfilename = "golnaz.out";

	string station_code;
	ifstream inputfile;
	ofstream outputfile, logfile;
	station entry[MAXvalidentry];
	string net_code;

	int valid_entries = 0, invalidEntries = 0, produced_signalnum = 0;

	// Generating the inputfile, outputfile and logfile

	print_message(logfile, "opening file: the input.in ");
	print_message(logfile, "\n");
	open_input(inputfile, logfile, cout, inputfilename);
	open_file(logfile, cout, "golnaz.log");
	open_file(outputfile, cout, "golnaz.out");

	// Calling the read_input function

	print_message(logfile, "processing input...");
	print_message(logfile, "\n");
	check_input_header(inputfile, outputfile);
	print_message(logfile, "header is read successfully!");
	print_message(logfile, "\n");

	read_input_signals(inputfile, outputfile, entry, valid_entries, invalidEntries, produced_signalnum);
	//print_output(outputfile, logfile, entry, valid_entries, invalidEntries, produced_signalnum);
	print_message(logfile, "signals are read correctly!");

	inputfile.close();
	outputfile.close();

	//getchar();
	return 0;
}