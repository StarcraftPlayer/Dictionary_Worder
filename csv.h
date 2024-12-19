#include "file.h" // Meant to be used with file.h
#include <iostream>
#include <fstream>
#include <filesystem>
#include <vector>
#include <string>

using std::filesystem::exists, std::getline, std::string, std::ofstream, std::ifstream, std::filesystem::path, std::vector;

vector<string> lineToCSVLine(string line)
{
    return splitLineBy(',', line);
}

struct csvFile
{
    path fullPath;
    path name;
    vector<vector<string>> fileData;

    csvFile(string name)
        : name(name), fullPath(name)
    {
        createFile(this->fullPath);
        readFile();
    };

    csvFile(string name, path parentPath)
        : name(name)
    {
        this->fullPath = parentPath / this->name;
        createFile(this->fullPath);
        readFile();
    };

    vector<vector<string>> readFile()
    {
        fileData.clear();
        ifstream file(fullPath);
        string line = "";
        while (getline(file, line))
        {
            vector<string> cells = lineToCSVLine(line);
            fileData.push_back(cells);
        }
        return fileData;
    }

    void writeFile(vector<vector<string>> &data)
    {
        ofstream file(fullPath);
        fileData = data;
        for (vector<string> line : fileData)
        {
            for (int cellIndex = 0; cellIndex < line.size(); cellIndex++)
            {
                if (cellIndex == line.size() - 1)
                {
                    // Don't append a comma if it's the last, and make a new line
                    file << line[cellIndex] << "\n";
                }
                else
                {
                    // Append a comma if it's not the last
                    file << line[cellIndex] << ",";
                }
            }
        }
    }

    void saveFile()
    {
        writeFile(fileData);
    }

    void printFile()
    {
        std::cout << "// // // // //\nPrinting .csv file: " << this->fullPath << "\n";
        for (int lineIndex = 0; lineIndex < fileData.size(); lineIndex++)
        {
            std::cout << "Line " << lineIndex << ": ";
            for (int cellIndex = 0; cellIndex < fileData[lineIndex].size(); cellIndex++)
            {
                if (cellIndex == fileData[lineIndex].size() - 1)
                {
                    // Don't append a comma if it's the last, and make a new line
                    std::cout << fileData[lineIndex][cellIndex] << "\n";
                }
                else
                {
                    // Append a comma if it's not the last
                    std::cout << fileData[lineIndex][cellIndex] << ", ";
                }
            }
        }
        std::cout << "// // // // //\n";
    }

    void deleteLine(int index)
    {
        fileData.erase(fileData.begin() + index);
        saveFile();
    }

    void deleteLine(string key)
    {
        for (int lineIndex = 0; lineIndex < fileData.size(); lineIndex++)
        {
            if (fileData[lineIndex][0] == key)
            {
                deleteLine(lineIndex);
                break;
            }
        }
    }

    void deleteLine(string value, int cellIndex)
    {
        for (int lineIndex = 0; lineIndex < fileData.size(); lineIndex++)
        {
            if (fileData[lineIndex][cellIndex] == value)
            {
                deleteLine(lineIndex);
                break;
            }
        }
    }

    // Reads a line given a key value to look for
    vector<string> &readLine(string key)
    {
        for (int i = 0; i < fileData.size(); i++)
        {
            if (fileData[i][0] == key)
            {
                return fileData[i];
            }
        }
        printf("I couldnt find anything");
        // Create that line and return it as an empty one
        addLine(key);
        return fileData[fileData.size() - 1];
    }

    // Adds the line or edits it if a line with the same key is found
    void addLine(vector<string> line)
    {
        for (vector<string> &lineData : fileData)
        {
            if (lineData[0] == line[0])
            {
                lineData = line;
                saveFile();
                return;
            }
        }
        fileData.push_back(line);
        saveFile();
    }

    void addLine(string line)
    {
        std::cout << "I just got asked to make a line " << line << "\n";
        addLine(lineToCSVLine(line));
    }
};
