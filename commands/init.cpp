#include<iostream>
#include<filesystem>
#include<fstream>
#include "init.h"
using namespace std;

namespace fs = std::filesystem;

void init()
{
    if(fs::exists(".gitlite"))
    {
        cout << "Repository already exists." << endl;
        return;
    }
    else
    {
        fs::create_directory(".gitlite");
        fs::create_directory(".gitlite/staging");
        fs::create_directory(".gitlite/commits");
        ofstream metadataFile(".gitlite/metadata.txt");
        metadataFile << "GitLite repository initialized" << endl;
        metadataFile.close();
        cout << "Initialized empty GitLite repository in .gitlite" << endl;
    }
    
}
 