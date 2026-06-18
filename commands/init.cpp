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
        fs::create_directory("repository/.gitlite");
        fs::create_directories("repository/.gitlite/staging");
        fs::create_directories("repository/.gitlite/commits");
        ofstream metadataFile("repository/.gitlite/metadata.txt");
        metadataFile << "GitLite repository initialized" << endl;
        metadataFile.close();
        cout << "Initialized empty GitLite repository in repository/.gitlite" << endl;
    }
    
}
 