#ifndef __xrt__core__
#define __xrt__core__

#include <iostream>
#include <fstream>
#include "challenge_specs.h"

using namespace std;

// Function declarations
bool getCsvTableDimensions(string fileName, string csvDelimiter, long* nbCols, long* nbLines);
bool split(string input,string delimiter,string* leftPart, string* rightPart);
int substringCounter(string input, string delimiter);
void loadVectorFromCsv(string fileName, double*const& output);

#endif /* defined(__xrt__core__) */
