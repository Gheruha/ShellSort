#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>
#include <vector>

using namespace std;
namespace fs = filesystem;

// Accumulate all the json files function

vector<fs::path> accumulateJsonFiles(const fs::path &dir)
{
    vector<fs::path> configs;

    // Check if the folder exists, if not, stop
    if (!fs::exists(dir) || !fs::is_directory(dir))
    {
        return configs;
    }

    // Accumulating the files
    for (auto &entry : fs::directory_iterator(dir))
    {
        if (entry.is_regular_file() && entry.path().extension() == ".json")
        {
            configs.push_back(entry.path());
        }
    }

    return configs;
}

void seeJsonFiles()
{
    vector<fs::path> configs = accumulateJsonFiles("configs");
    if (configs.empty())
    {
        cout << "There are no json files yet.\n";
    }
    else
    {
        for (size_t i = 0; i < configs.size(); i++)
        {
            cout << "[" << i + 1 << "] " << configs[i].filename().string() << "\n";
        }
    }
}

void readJsonFiles()
{
    vector<fs::path> configs = accumulateJsonFiles("configs");
    cout << "Which file do you want to read: ";
    int option;
    cin >> option;

    // Open and print the chosen file
    fs::path selected = configs[option - 1];
    ifstream ifs(selected);
    if (!ifs)
    {
        cerr << "Error: could not open " << selected << "\nRun -jsee to see available files.\n";
    }
    else
    {
        cout << "\n================== Contents of " << selected.filename().string() << " ==================\n";
        string line;
        while (getline(ifs, line))
        {
            cout << line << "\n";
        }
        cout << "================== end of file ==================\n";
    }
}