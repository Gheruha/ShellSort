#ifndef manage_h
#define manage_h
#include <filesystem>
#include <string>

using namespace std;
namespace fs = filesystem;

void seeJsonFiles();
void readJsonFiles();
vector<fs::path> accumulateJsonFiles(const fs::path &dir);
void sortJsonFile();

#endif