#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>
#include "log.h"

using namespace std;
namespace fs = std::filesystem;

void log()
{
    if(!fs::exists("repository/.gitlite"))
    {
        cout << "Repository not initialized. Please run './gitlite init' first." << endl;
        return;
    }

    if(!fs::exists("repository/.gitlite/HEAD"))
    {
        cout << "No commits yet." << endl;
        return;
    }

    ifstream headFile("repository/.gitlite/HEAD");
    string head;
    getline(headFile, head);
    headFile.close();

    if(head.rfind("ref: ", 0) != 0)
    {
        cout << "Invalid HEAD." << endl;
        return;
    }

    string ref = head.substr(5);
    ifstream branchFile("repository/.gitlite/" + ref);

    if(!branchFile)
    {
        cout << "No commits yet." << endl;
        return;
    }

    string commitHash;
    getline(branchFile, commitHash);
    branchFile.close();

    while(!commitHash.empty())
    {
        string folder = commitHash.substr(0, 2);
        string object = commitHash.substr(2);

        string path =
            "repository/.gitlite/objects/" + folder + "/" + object;

        ifstream commitFile(path);

        if(!commitFile)
        {
            cout << "Error reading commit object." << endl;
            return;
        }

        string line;
        string parent;
        string timestamp;
        string message;

        while(getline(commitFile, line))
        {
            if(line.rfind("parent: ", 0) == 0)
            {
                parent = line.substr(8);
            }
            else if(line.rfind("timestamp: ", 0) == 0)
            {
                timestamp = line.substr(11);
            }
            else if(line.rfind("message: ", 0) == 0)
            {
                message = line.substr(9);
            }
        }

        commitFile.close();

        cout << "commit " << commitHash << endl;
        cout << "Date:   " << timestamp << endl;
        cout << "\n    " << message << "\n" << endl;

        if(parent == "none")
            break;

        commitHash = parent;
    }
}