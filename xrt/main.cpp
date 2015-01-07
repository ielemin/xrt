#include "main.h"

//// Challenge specifications
//const int nbDataCols = 2;
//const long nbDataPoints = 10000;
//const string dataDirectoryName = "/users/adrien/Documents/dev/code/Cpp/xrt/xrt/data";

// Function declarations
// -> none

int main(int argc, const char * argv[])
{
    cout << "Entering correlation analysis\n";
    
    // Reading file A according to challenge specs
    string fileNameA = dataDirectoryName+"/XR Assessment - PC1_A.CSV";
    long colCountA ,lineCountA;
    getCsvTableDimensions(fileNameA,csvDelimiter,&colCountA,&lineCountA);
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
    getCsvTableDimensions(fileNameB,csvDelimiter,&colCountB,&lineCountB);
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


