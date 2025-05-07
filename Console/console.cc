#include <iostream>
#include <string>
#include <fstream>
#include <filesystem>
#include <vector>
#include "manageJson/manage.h"

using namespace std;

void selectFunctionToRun(string &option)
{
    if (option == "-jsee")
    {
        cout << "configs/files\n";
        seeJsonFiles();
    }
    else if (option == "-jread")
    {
        readJsonFiles();
    }
    else if (option == "-jadd"){
        addJsonFile();
    }
    else if (option == "-jsort"){
        sortJsonFile();
    }
    else
    {
        cout << "There are no options like this yet.\nFor help use -help tag\n";
    }
}