#include "file.h" // Meant to be used with file.h
#include <iostream>
#include <fstream>
#include <filesystem>
#include <vector>

using std::vector, std::ofstream, std::ifstream, std::getline, std::string;
namespace fs = std::filesystem;

struct directory;
struct directory
{
    fs::path fullPath = "";
    fs::path name = "";
    vector<string> fileData;

    directory(string name, fs::path parentPath = "", bool isFile = false)
        : name(name), fullPath(parentPath / name)
    {
        std::cout << "Making file of: " << fullPath << '\n';
        if (!isFile)
        {
            fs::create_directory(fullPath);
        }
        else
        {
            createFile(fullPath);
            fileData = readFile();
        }
    };

    operator fs::path() const
    {
        return fs::path(this->fullPath);
    }

    vector<string> readFile()
    {
        vector<string> fileData;
        ifstream file(fullPath, std::ios_base::openmode::_S_in);
        string line = "";
        while (getline(file, line))
        {
            fileData.push_back(line);
        }
        return fileData;
    }

    void writeFile(vector<string> newData)
    {
        ofstream file(fullPath);
        for (string line : newData)
        {
            file << line << "\n";
        }
    }

    void saveFile()
    {
        ofstream file(fullPath);
        for (string line : fileData)
        {
            file << line << "\n";
        }
    }

    void printFile()
    {
        std::cout << "-- -- -- -- -- -- -- -- -- -- --\n";
        std::cout << ">> Printing content of: " << fullPath << " <<\n";
        for (int i = 0; i < fileData.size(); i++)
        {
            std::cout << "Line " << i << ": " << fileData[i] << '\n';
        }
        std::cout << "-- -- -- -- -- -- -- -- -- -- --\n";
    }

    void editLine(int index, string newData)
    {
        this->fileData[index] = newData;
        saveFile();
    }
};
