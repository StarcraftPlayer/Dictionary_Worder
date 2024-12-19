#pragma once

#include <iostream>
#include <fstream>
#include <filesystem>
#include <vector>
#include <string>
using std::vector, std::string;
namespace fs = std::filesystem;

bool fileExists(fs::path fullPath)
{
    return fs::exists(fullPath);
}

void createFile(fs::path fullPath)
{
    if (!fileExists(fullPath))
    {
        std::ofstream(fullPath).close();
    }
}

vector<string> splitLineBy(char separator, string line)
{
    vector<string> output;

    if (line.find(',') != string::npos)
    {
        do
        {
            output.push_back(line.substr(0, line.find(separator)));
            line = line.substr(line.find(separator) + 1);
        } while (line.find(separator) != string::npos);
    }
    output.push_back(line);

    return output;
}