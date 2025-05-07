#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>
#include <vector>
#include "third_party/json/json.hpp"

using namespace std;
namespace fs = filesystem;
using json = nlohmann::json;

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

// See all the available json files
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

void addJsonFile()
{
    fs::path dir = "configs";
    if (!fs::exists(dir))
        fs::create_directory(dir);

    // Ask for filename
    cout << "Enter new JSON filename (without extension): ";
    string name;
    cin >> name;
    fs::path filepath = dir / (name + ".json");
    if (fs::exists(filepath))
    {
        cout << "❌ A file named “" << filepath.filename() << "” already exists.\n";
        return;
    }

    // Open for writing
    ofstream ofs(filepath);
    if (!ofs)
    {
        cerr << "❌ Could not create “" << filepath << "”.\n";
        return;
    }

    // Read multi-line JSON from the user
    cout << "Paste your JSON now. End with a line containing just a single dot (.)\n";
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // flush leftover newline
    string line;
    while (true)
    {
        getline(cin, line);
        if (line == ".")
            break;
        ofs << line << "\n";
    }
    ofs.close();

    cout << "✅ Created “" << filepath.filename() << "” with your content.\n";
}

/// 2) Let the user delete an existing JSON file
void deleteJsonFile()
{
    vector<fs::path> configs = accumulateJsonFiles("configs");
    if (configs.empty())
    {
        cout << "There are no JSON files to delete.\n";
        return;
    }

    // List them
    cout << "Which file do you want to delete?\n";
    for (size_t i = 0; i < configs.size(); ++i)
    {
        cout << "  [" << i + 1 << "] " << configs[i].filename().string() << "\n";
    }
    cout << "Enter number: ";
    size_t choice;
    cin >> choice;
    if (choice < 1 || choice > configs.size())
    {
        cerr << "❌ Invalid selection.\n";
        return;
    }

    fs::path toDelete = configs[choice - 1];
    cout << "Deleting “" << toDelete.filename() << "” … ";
    if (fs::remove(toDelete))
    {
        cout << "Done.\n";
    }
    else
    {
        cout << "Failed!\n";
    }
}

// Reading the file that the user wants
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

void sortJsonFile()
{
    vector<fs::path> configs = accumulateJsonFiles("configs");
    cout << "Which file do you want to sort: ";
    int option;
    cin >> option;

    // 1) Load & parse
    fs::path filepath = configs[option - 1];
    ifstream ifs(filepath);
    if (!ifs)
    {
        cerr << "❌ Could not open for reading: " << filepath << "\n";
        return;
    }
    json j;
    try
    {
        ifs >> j;
    }
    catch (const exception &e)
    {
        cerr << "❌ JSON parse error: " << e.what() << "\n";
        return;
    }
    if (!j.is_array())
    {
        cerr << "❌ Expected a JSON array at top level\n";
        return;
    }

    // 2) Read & validate choice
    string field;
    while (true)
    {
        cout << "Available fields:\n";
        for (auto &[key, val] : j[0].items())
        {
            cout << " 🔑 " << key << "\n";
        }
        cout << "\nSort by which field: ";
        cin >> field;

        if (!j[0].contains(field))
        {
            cerr << "❌ Invalid field\n";
            continue;
        }
        break;
    }

    // 3) Perform the sort
    sort(j.begin(), j.end(),
         [&](const json &a, const json &b)
         {
             // if field missing or not string, treat as empty
             auto sa = a.value(field, ""s);
             auto sb = b.value(field, ""s);
             return sa < sb;
         });

    // 4) Write back (overwriting)
    ofstream ofs(filepath);
    if (!ofs)
    {
        cerr << "❌ Could not open for writing: " << filepath << "\n";
        return;
    }
    ofs << j.dump(4) << "\n";
    cout << "✅ Sorted “" << filepath.filename().string()
         << "” by “" << field << "” and saved.\n";
}