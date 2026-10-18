#include "repository.h"
#include <iostream>
#include <fstream>
#include <filesystem>
using namespace std;

namespace fs = std::filesystem;

bool repositoryExists()
{
    return fs::exists("repository/.gitlite");
}

bool isRepositoryInitialized()
{
    if(!repositoryExists())
    {
        cout<<"Repository not initialized. Please run './gitlite init' first."<<endl;
        return false;
    }

    return true;
}