#include<iostream>
#include<filesystem>
#include<fstream>
#include "init.h"
using namespace std;

namespace fs = std::filesystem;

void init()
{
    if(fs::exists("repository/.gitlite"))
    {
        cout << "Repository already exists." << endl;
        return;
    }
    else
    {
        fs::create_directories("repository/.gitlite");
        fs::create_directories("repository/.gitlite/objects");
        fs::create_directories("repository/.gitlite/refs/heads");

        ofstream headFile("repository/.gitlite/HEAD");
        headFile << "ref: refs/heads/main" << endl;
        headFile.close();
        ofstream("repository/.gitlite/refs/heads/main");
        ofstream("repository/.gitlite/index");

        cout << "Initialized empty GitLite repository in repository/.gitlite" << endl;
    }
}