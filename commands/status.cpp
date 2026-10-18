
#include<iostream>
#include<fstream>
#include<filesystem>
#include<string>
using namespace std;

namespace fs = std::filesystem;

void status()
{
    if(!fs::exists("repository/.gitlite"))
    {
        cout<<"Repository not initialized. Please run './gitlite init' first."<<endl;
        return;
    }

    ifstream headFile("repository/.gitlite/HEAD");
    string head;

    if(!headFile || !getline(headFile, head))
    {
        cout<<"Error reading HEAD file."<<endl;
        return;
    }

    headFile.close();

    string branch = "HEAD";
    string parent = "";

    if(head.rfind("ref: ", 0) == 0)
    {
        string ref = head.substr(5);
        branch = fs::path(ref).filename().string();

        ifstream branchFile("repository/.gitlite/" + ref);

        if(branchFile)
            getline(branchFile, parent);

        branchFile.close();
    }

    cout<<"On branch "<<branch<<endl;

    if(!fs::exists("repository/.gitlite/index"))
    {
        cout<<"Error: index file not found."<<endl;
        return;
    }

    ifstream indexFile("repository/.gitlite/index");

    if(!indexFile)
    {
        cout<<"Error opening index file."<<endl;
        return;
    }

    string line;
    bool hasStagedFiles = false;

    while(getline(indexFile, line))
    {
        if(!line.empty())
        {
            if(!hasStagedFiles)
                cout<<"Changes to be committed:"<<endl;

            cout<<"  "<<line<<endl;
            hasStagedFiles = true;
        }
    }

    indexFile.close();

    if(hasStagedFiles)
        return;

    if(parent.empty())
    {
        cout<<"No files added yet."<<endl;
        cout<<"Nothing to commit."<<endl;
    }
    else
    {
        cout<<"Working tree clean."<<endl;
        cout<<"Everything up to date."<<endl;
    }
}
