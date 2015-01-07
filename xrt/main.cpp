#include <iostream>
#include <fstream>
#include <math.h>
using namespace std;

// Challenge specifications
const int nbDataCols = 2;
const long nbDataPoints = 10000;
const string dataDirectoryName = "/users/adrien/Documents/dev/code/Cpp/xrt/xrt/data";
const string csvDelimiter = ",";

// Function declarations
bool getCsvTableDimensions(string fileName, long* nbCols, long* nbLines);
bool split(string input,string delimiter,string* leftPart, string* rightPart);
int substringCounter(string input, string delimiter);
void loadVectorFromCsv(string fileName, double*const& output);
bool computeReturnCorrelation(double* inputA,double* inputB,long inputLength,double* output);

int main(int argc, const char * argv[])
{
    cout << "Entering correlation analysis\n";
    
    // Reading file A according to challenge specs
    string fileNameA = dataDirectoryName+"/XR Assessment - PC1_A.CSV";
    long colCountA ,lineCountA;
    getCsvTableDimensions(fileNameA,&colCountA,&lineCountA);
    if((colCountA!=nbDataCols)||(lineCountA!=nbDataPoints))
    {
        cout << "Data file "<<fileNameA<<" does not follow challenge specifications\n";
        cout << "Line count is "<<lineCountA<<" ("<<nbDataPoints<<" expected)\n";
        cout << "Column count is "<<colCountA<<" ("<<nbDataCols<<" expected)\n";
        return -1;
    }
    double dataA[nbDataPoints];
    loadVectorFromCsv(fileNameA,dataA);
    
    // Reading file B according to challenge specs
    string fileNameB = dataDirectoryName+"/XR Assessment - PC1_B.CSV";
    long colCountB ,lineCountB;
    getCsvTableDimensions(fileNameB,&colCountB,&lineCountB);
    if((colCountB!=nbDataCols)||(lineCountB!=nbDataPoints))
    {
        cout << "Data file "<<fileNameB<<" does not follow challenge specifications\n";
        cout << "Line count is "<<lineCountB<<" ("<<nbDataPoints<<" expected)\n";
        cout << "Column count is "<<colCountB<<" ("<<nbDataCols<<" expected)\n";
        
        return -1;
    }
    double dataB[nbDataPoints];
    loadVectorFromCsv(fileNameB,dataB);
    
    // Computing correlation of returns
    double correl;
    if(!computeReturnCorrelation(dataA,dataB,nbDataPoints,&correl))
    {
        cout<<"Could not compute data correlation\n";
        return -1;
    }
    
    cout<<"The correlation of returns between the two series is "<<correl<<"\n";
    
    return 0;
}

bool getCsvTableDimensions(string fileName, long* nbCols, long* nbLines)
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

bool computeReturnCorrelation(double* inputA,double* inputB,long inputLength,double* output)
{
    // Running totals
    int sum1=0;
    double sumA=0;
    double sumB=0;
    double sumAA=0;
    double sumBB=0;
    double sumAB=0;
    
    // Current values
    double prevValueA = inputA[0];
    double prevValueB=inputB[0];
    double curValueA;
    double curValueB;
    double returnA;
    double returnB;
    
    for (int index=1;index < inputLength;index++)
    {
        curValueA=inputA[index];
        curValueB=inputB[index];
        
        // Securities with null price (and infinite returns) are ruled out
        if(curValueA==0||curValueB==0)
        {
            cout << "Value at zero for index "<<index<<"\n";
            continue;
        }
        
        returnA = curValueA/prevValueA-1;
        returnB = curValueB/prevValueB-1;
        
        sum1+=1;
        sumA+=returnA;
        sumB+=returnB;
        sumAA+=returnA*returnA;
        sumBB+=returnB*returnB;
        sumAB+=returnA*returnB;
        
        prevValueA=curValueA;
        prevValueB=curValueB;
    }
    
    // Statistics
    double avgA = sumA/sum1;
    double avgB = sumB/sum1;
    double varA = sumAA/sum1-avgA*avgA;
    double varB = sumBB/sum1-avgB*avgB;
    double covarAB = sumAB/sum1-avgA*avgB;
    
    // Consistency check
    if (varA<=0 || varB<=0) return false;
    
    // Output value
    *output = covarAB/(sqrt(varA*varB));
    
    return true;
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


