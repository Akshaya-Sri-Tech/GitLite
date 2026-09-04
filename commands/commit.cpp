#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>
#include <ctime>
#include "commit.h"

using namespace std;
namespace fs = std::filesystem;

unsigned long long commitHash(const string& data)
{
    unsigned long long hash_val = 0;
    for(char ch : data)
    {
        hash_val = hash_val * 31 + static_cast<unsigned char>(ch);
    }
    return hash_val;
}

void commit(char* argv[], int argc)
{
    if(argc != 3)
    {
        cout << "Usage: ./gitlite commit \"message\"" << endl;
        return;
    }

    if(!fs::exists("repository/.gitlite"))
    {
        cout << "Repository not initialized. Please run './gitlite init' first." << endl;
        return;
    }

    if(!fs::exists("repository/.gitlite/index"))
    {
        cout << "Nothing to commit." << endl;
        return;
    }

    ifstream indexFile("repository/.gitlite/index");

    if(indexFile.peek() == ifstream::traits_type::eof())
    {
        cout << "Nothing to commit." << endl;
        return;
    }

    string indexData;
    string line;

    while(getline(indexFile, line))
    {
        indexData += line + "\n";
    }

    indexFile.close();

    string parent = "";

    ifstream headFile("repository/.gitlite/HEAD");
    string head;

    getline(headFile, head);
    headFile.close();

    if(head.rfind("ref: ", 0) == 0)
    {
        string ref = head.substr(5);
        ifstream branchFile("repository/.gitlite/" + ref);
        if(branchFile)
            getline(branchFile, parent);
        branchFile.close();
    }

    time_t now = time(nullptr);
    string timestamp = ctime(&now);
    string message = argv[2];
    string commitData;

    commitData += "tree:\n";
    commitData += indexData;

    commitData += "parent: ";
    commitData += parent.empty() ? "none\n" : parent + "\n";

    commitData += "timestamp: ";
    commitData += timestamp;

    commitData += "message: ";
    commitData += message + "\n";

    unsigned long long hash = commitHash(commitData);
    string commitHashValue = to_string(hash);

    string folder = commitHashValue.substr(0, 2);
    string object = commitHashValue.substr(2);

    fs::create_directories(
        "repository/.gitlite/objects/" + folder
    );

    ofstream commitFile(
        "repository/.gitlite/objects/" + folder + "/" + object
    );

    if(!commitFile)
    {
        cout << "Error creating commit object." << endl;
        return;
    }

    commitFile << commitData;
    commitFile.close();

    if(head.rfind("ref: ", 0) == 0)
    {
        string ref = head.substr(5);

        ofstream branchFile(
            "repository/.gitlite/" + ref
        );

        branchFile << commitHashValue;
        branchFile.close();
    }

    ofstream clearIndex("repository/.gitlite/index", ios::trunc);
    clearIndex.close();

    cout << "[" << head.substr(10) << " "
         << commitHashValue << "] "
         << message << endl;
}