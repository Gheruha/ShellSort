#include <iostream>
#include <string>
#include <fstream>
#include <filesystem>
#include <vector>
#include "manageJson/manage.h"

using namespace std;


void selectFunctionToRun(string option)
{
    if (option == "-json")
    {
        manageJsonFiles();
    }
    else
    {
        cout << "There are no options like this yet.\nFor help use -help tag\n";
    }
}