#ifndef manage_h
#define manage_h
#include <filesystem>
#include <string>

using namespace std;
namespace fs = filesystem;

void manageJsonFiles();
vector<fs::path> accumulateJsonFiles(const fs::path &dir);

#endif