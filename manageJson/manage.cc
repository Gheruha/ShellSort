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

void manageJsonFiles()
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