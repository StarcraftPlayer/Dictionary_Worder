#include <iostream>
#include "csv.h"
#include "directory.h"
#include "file.h"
#include <string.h>
#include <random>

using std::getline, std::cin, std::stoi, std::string;

int main()
{
    /**/ directory settings = directory("settings");
    /**/ /**/ csvFile set_csv = csvFile("settings.csv", settings.fullPath);
    /**/ directory dictionary = directory("dictionary");
    /**/ /**/ csvFile dic_csv = csvFile("dictionary.csv", dictionary.fullPath);

    if (set_csv.readLine("first_time")[1] != "false")
    {
        set_csv.addLine("first_time,false");
        printf("Hello!  It has been detected that this is your first time!\n");
        printf("Please specify how many words you would like to pop-up everytime this program is opened: ");

        string input = "";
        while (true)
        {
            getline(cin, input);
            try
            {
                stoi(input);
                break;
            }
            catch (const std::invalid_argument &e)
            {
                std::cout << "Error: Invalid input, not a number." << std::endl;
            }
            catch (const std::out_of_range &e)
            {
                std::cout << "Error: Number out of range." << std::endl;
            }
        }
        set_csv.addLine("word_count," + input);
        printf("Thank you, your result has been stored in the settings file\n");
    }

    printf("Retrieving # of words...\n");
    int numWords = stoi(set_csv.readLine("word_count")[1]);
    printf("# of words to get: %i\n", numWords);
    printf("Searching through the dictionary now...\n");

    int dic_max_lines = dic_csv.fileData.size();

    // Chatgpt generated code <<<<<<<<<<<<<<<<<<<<<
    // ||

    // Create a random number generator
    std::random_device rd;  // Seed the random number generator with a hardware random device
    std::mt19937 gen(rd()); // Mersenne Twister random number generator

    // Define a distribution range (e.g., between 1 and 100)
    std::uniform_int_distribution<> dist(0, dic_max_lines - 1);

    // ||
    // Chatgpt generated code <<<<<<<<<<<<<<<<<<<<<

    for (int i = 0; i < numWords; i++)
    {
        int random_number = dist(gen);
        const string word = dic_csv.fileData[random_number][0];
        printf("> > Word #%i is %s.  Getting definitions:\n", i, word.c_str());
        int def_iter = 0;
        for (int bad_performance = 0; bad_performance < dic_max_lines; bad_performance++)
        {
            if (dic_csv.fileData[bad_performance][0] == word)
            {
                ++def_iter;
                printf("> > > > Definition #%i: ", def_iter);
                int def_size = dic_csv.fileData[bad_performance].size() - 2;
                printf("%s", dic_csv.fileData[bad_performance][2].c_str());
                for (int i_hate_commas = 1; i_hate_commas < def_size; i_hate_commas++)
                {
                    printf(", %s", dic_csv.fileData[bad_performance][i_hate_commas + 2].c_str());
                }
                printf("\n");
            }
        }
    }

    printf("Waiting for input for you to shut down the program...\n");
    string exit = "";
    getline(cin, exit);

    return 0;
}