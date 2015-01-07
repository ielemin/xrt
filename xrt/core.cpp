//
//  core.cpp
//  xrt
//
//  Created by Adrien on 25/12/2014.
//  Copyright (c) 2014 -. All rights reserved.
//

#include <iostream>
#include <fstream>
#include "core.h"

int Load(std::string fileName)
{
    std::ifstream fileStream;
    fileStream.open(fileName);
    if(!fileStream.is_open()) std::cout<<"Cannot read file"+fileName;
    
    std::string currentLine;
    int lineCount=0;
    
    while (fileStream.good())
    {
        getline(fileStream, currentLine);
        lineCount++;
    }
    
    fileStream.close();
    
    std::cout<<"Found "<<lineCount<<" lines in the file"<<'\n';
    
    return lineCount;
}