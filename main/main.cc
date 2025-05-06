#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>
#include <vector>
#include "Console/console.h"

using namespace std;
namespace fs = filesystem;

int main(int argc, const char *argv[])
{
    if (argc < 2)
    {
        cout << "You need to select an option\n";
    }
    else
    {
        string option = string(argv[1]);
        if (option == "-help")
        {
            ifstream helpFile("main/help.txt");
            string line = "";

            if (!helpFile.is_open())
            {
                cout << "Help file could not be opened.";
                return 0;
            }

            cout << "\n\n";
            while (getline(helpFile, line))
            {
                cout << line << "\n";
            }
            helpFile.close();
        }
        else if (argc == 2)
        {
            selectFunctionToRun(option);
        }
    }
}