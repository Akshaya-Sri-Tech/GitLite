#include<iostream>
#include<string>
#include<fstream>
#include<filesystem>
#include "branch.h"
#include "../utils/repository.h"
#include "../utils/colors.h"
namespace fs = std::filesystem;
using namespace std;    

void branch(char* argv[], int argc)
{
     if(!isRepositoryInitialized())
            return;
    if(argc == 2)
    {
        string refPath = "repository/.gitlite/refs/heads";
        if(!fs::exists(refPath))
        {
            cout << "No branches found." << endl;
            return;
        }
        string currentBranch;
        ifstream headFile("repository/.gitlite/HEAD");
        if(headFile)
        {
            getline(headFile, currentBranch);
            headFile.close();
        }
        if(currentBranch.rfind("ref: ", 0) == 0)
        {
            currentBranch = currentBranch.substr(5);
            currentBranch = fs::path(currentBranch).filename().string();
        }
        
        cout << "Branches:" << endl;
        for(const auto& entry : fs::directory_iterator(refPath))
        {
            if(entry.is_regular_file())
            {
                string branchName = entry.path().filename().string();
                if(branchName == currentBranch)
                {
                    cout << GREEN << "* " << branchName << RESET<<endl;
                }
                else
                {
                    cout << "  " << branchName << endl;
                }
            }
        }
    }
    else if (argc == 3)
    {
        string newBranch = argv[2];
        ofstream("repository/.gitlite/refs/heads/"+newBranch);
    }
    else
    {
        cout << "Usage: ./gitlite branch" << endl;
    }
}