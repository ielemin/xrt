#include "core.h"

bool getCsvTableDimensions(string fileName, string csvDelimiter, long* nbCols, long* nbLines)
{
	// Set default values
	*nbCols = 0;
	*nbLines = 0;
	
	// Check file existence
	ifstream fileStream;
	fileStream.open(fileName);
	if(!fileStream.is_open())
	{
		std::cout<<"Cannot read file"+fileName;
		return false;
	}
	
	long currentLineCount=0;
	string currentLine;
	
	// Read the file header
	if (fileStream.good())getline(fileStream, currentLine);
	*nbCols = substringCounter(currentLine, csvDelimiter);
	
	// Count the lines
	while (fileStream.good())
	{
		getline(fileStream, currentLine);
		if (!currentLine.empty())        currentLineCount++;
	}
	
	// Properly close the file
	fileStream.close();
	
	// Assign values
	*nbLines = currentLineCount;
	
	return true;
}

bool split(string input,string delimiter,string* leftPart, string* rightPart)
{
	if (input.empty()||delimiter.empty())
	{
		*leftPart=input;
		*rightPart="";
		return false;
	}
	
	long delimiterPosition =input.find(delimiter);
	if (delimiterPosition<=0||delimiterPosition>=input.length()||delimiterPosition==string::npos)
	{
		*leftPart=input;
		*rightPart="";
		return true;
	}
	
	*leftPart = input.substr(0,delimiterPosition);
	*rightPart =input.substr(delimiterPosition+delimiter.length(),input.length());
	
	return true;
}

void loadVectorFromCsv(string fileName, double*const& output)
{
	// fileName existence already tested above
	ifstream fileStream;
	fileStream.open(fileName);
	
	long currentLineCount=0;
	string currentLine;
	
	// Skip the file header
	if (fileStream.good())getline(fileStream, currentLine);
	
	string left;
	string right;
	
	// Read the lines
	while (fileStream.good())
	{
		getline(fileStream, currentLine);
		if (currentLine.empty()) continue;
		split(currentLine,csvDelimiter,&left,&right);
		output[currentLineCount]= atof(right.c_str());
		currentLineCount++;
	}
	
	// Properly close the file
	fileStream.close();
}

int substringCounter(string input, string delimiter)
{
	int substringsCount = 0;
	string left;
	string right;
	
	while(split(input,csvDelimiter,&left,&right))
	{
		input = right;
		substringsCount++;
	}
	
	return substringsCount;
}