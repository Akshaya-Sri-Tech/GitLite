
#include<iostream>
#include<string>
#include<fstream>
#include<filesystem>
#include<sstream>
#include<vector>
#include "branch.h"
#include "../utils/repository.h"

namespace fs = std::filesystem;
using namespace std;

void checkout(char* argv[], int argc)
{
    if(!isRepositoryInitialized())
        return;

    if(argc != 3)
    {
        cout << "Usage: gitlite checkout <branch_name>" << endl;
        return;
    }

    string branchName = argv[2];

    // Step 1: Check whether the branch exists
    string branchPath =
        "repository/.gitlite/refs/heads/" + branchName;

    if(!fs::exists(branchPath))
    {
        cout << "Branch does not exist: " << branchName << endl;
        return;
    }

    // Step 2: Read the target branch's commit hash
    ifstream branchFile(branchPath);
    string commitHash;

    if(!branchFile || !getline(branchFile, commitHash))
    {
        cout << "Error reading branch." << endl;
        return;
    }
    branchFile.close();

    if(commitHash.empty())
    {
        cout << "Branch has no commits yet." << endl;
        return;
    }

    // Step 3: Find the commit object using its hash
    string objectPath =
        "repository/.gitlite/objects/" +
        commitHash.substr(0, 2) + "/" +
        commitHash.substr(2);

    ifstream commitFile(objectPath);

    if(!commitFile)
    {
        cout << "Commit object not found." << endl;
        return;
    }

    // Step 4: Read filenames and hashes from the tree section
    string line;
    bool inTree = false;
    vector<pair<string, string>> files;

    while(getline(commitFile, line))
    {
        if(line == "tree:")
        {
            inTree = true;
            continue;
        }

        if(line.rfind("parent:", 0) == 0 ||
           line.rfind("timestamp:", 0) == 0 ||
           line.rfind("message:", 0) == 0)
        {
            inTree = false;
        }

        if(inTree)
        {
            size_t separator = line.find('|');

            if(separator != string::npos)
            {
                string filename = line.substr(0, separator);
                string fileHash = line.substr(separator + 1);

                // Remove optional spaces around the hash
                while(!filename.empty() && filename.back() == ' ')
                    filename.pop_back();

                while(!fileHash.empty() && fileHash.front() == ' ')
                    fileHash.erase(0, 1);

                if(!filename.empty() && !fileHash.empty())
                    files.push_back({filename, fileHash});
            }
        }
    }

    commitFile.close();

    // Step 5: Restore each file from its stored object
    for(const auto& file : files)
    {
        string filename = file.first;
        string fileHash = file.second;

        string fileObjectPath =
            "repository/.gitlite/objects/" +
            fileHash.substr(0, 2) + "/" +
            fileHash.substr(2);

        ifstream objectFile(fileObjectPath, ios::binary);

        if(!objectFile)
        {
            cout << "Missing file object for: "
                 << filename << endl;
            return;
        }

        // Read the saved file content
        string content(
            (istreambuf_iterator<char>(objectFile)),
            istreambuf_iterator<char>()
        );

        objectFile.close();

        // Write the content back to the working file
        ofstream outputFile(filename, ios::binary);

        if(!outputFile)
        {
            cout << "Could not restore file: "
                 << filename << endl;
            return;
        }

        outputFile.write(content.data(), content.size());
        outputFile.close();
    }

    // Step 6: Update HEAD after restoring files
    ofstream headFile("repository/.gitlite/HEAD");

    if(!headFile)
    {
        cout << "Error updating HEAD." << endl;
        return;
    }

    headFile << "ref: refs/heads/" << branchName;
    headFile.close();

    cout << "Switched to branch '" << branchName << "'." << endl;
}
