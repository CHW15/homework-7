
#ifndef MUTUALFUNCTIONS_H
#define MUTUALFUNCTIONS_H

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

//#include "earthquake.h"
//#include "station.h"

#include "LNK2005errorpass.h"

using namespace std;

static const int MAXvalidentry = 300;

string inputfilename;
const string logfilename = "golnaz.log";

void open_file(ofstream &, ostream &, string);
void open_input(ifstream &, ofstream &, ostream &, string);
void print_message(ofstream &, const string &);
void print_position(ofstream &, int &);
string uppercase(string&);

#endif
