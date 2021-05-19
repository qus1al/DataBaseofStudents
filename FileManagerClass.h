#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <string>
#include "StringBuilderClass.h"
#include "StudentClass.h"
using namespace std;
const string startRecordString = "### Start Record";
const string endRecordString = "### End Record";

class FileManagerClass : public StringBuilderClass
{
public:
    string FileName = "";
    FileManagerClass() {
        FileName = "";
    }
    FileManagerClass(string _FileName) {
        FileName = _FileName;
    }

    int GetRecordCount() {
        string line;
        int count = 0;
        std::ifstream inFile(FileName);
        if (inFile.is_open())
        {
            while (getline(inFile, line))
            {
                if (strcmp(line.c_str(), startRecordString.c_str()) == 0)
                    count++;
            }
        }
        inFile.close();
        return count;
    }
    static void display(string FileName) {
        string line;
        ifstream inFile(FileName);
        if (inFile.is_open())
            while (getline(inFile, line))
                std::cout << line << std::endl;
        inFile.close();
    }
};

