#ifndef manage_h
#define manage_h
#include <filesystem>
#include <string>

using namespace std;
namespace fs = filesystem;

vector<fs::path> accumulateJsonFiles(const fs::path &dir);
void seeJsonFiles();
void readJsonFiles();
void addJsonFile();
void sortJsonFile();

#endif