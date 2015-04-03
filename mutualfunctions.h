
#ifndef MUTUAL_FUNCTIONS_H
#define MUTUAL_FUNCTIONS_H

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <ostream>
#include <cstdlib>
#include <sstream>
#include <istream>
#include <stdio.h>
#include <vector>
#include <stdlib.h>
#include <numeric>
#include <cstring>
#include <cctype>

#include "earthquake.h"
#include "station.h"

using namespace std;

static const int MAXvalidentry = 300;

string inputfilename = "golnaz.in", outputfilename = "golnaz.out", logfilename = "golnaz.log";

void open_file(ofstream &, ostream &, string);
void open_input(ifstream &, ofstream &, ostream &, string);
void print_message(ofstream &, const string &);
void print_position(ofstream &, int &);
string uppercase(string);

#endif
