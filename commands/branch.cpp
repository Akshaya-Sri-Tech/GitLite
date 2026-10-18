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
    else if(argc == 3)
    {
        string newBranch = argv[2];
        string branchPath = "repository/.gitlite/refs/heads/" + newBranch;

        if(fs::exists(branchPath))
        {
            cout << "Branch already exists: " << newBranch << endl;
            return;
        }

        if(newBranch == "HEAD")
        {
            cout << RED << "Invalid branch name." << RESET << endl;
            return;
        }

        string head;
        ifstream headFile("repository/.gitlite/HEAD");

        if(!headFile || !getline(headFile, head))
        {
            cout  << "Error reading HEAD." << endl;
            return;
        }

        headFile.close();

        if(head.rfind("ref: ", 0) != 0)
        {
            cout << "HEAD is not pointing to a branch."  << endl;
            return;
        }

        string currentRef = head.substr(5);
        string currentBranchPath = "repository/.gitlite/" + currentRef;

        if(!fs::exists(currentBranchPath))
        {
            cout << "Current branch reference not found."  << endl;
            return;
        }

        ifstream currentBranchFile(currentBranchPath);
        string commitHash;

        getline(currentBranchFile, commitHash);
        currentBranchFile.close();

        if(commitHash.empty())
        {
            cout << "Cannot create a branch before the first commit." << endl;
            return;
        }

        ofstream newBranchFile(branchPath);

        if(!newBranchFile)
        {
            cout << "Error creating branch." <<  endl;
            return;
        }

        newBranchFile << commitHash;
        newBranchFile.close();

        cout << "Branch '" << newBranch << "' created."  << endl;
    }
    else
    {
        cout << "Usage: ./gitlite branch" << endl;
    }
}