#include<iostream>
#include<string>
#include<fstream>
#include<filesystem>
#include "add.h"
namespace fs = std::filesystem;
using namespace std;    

string computeHash(string file_name)
{
    ifstream file(file_name);
    if(!file)
    {
        cout<<"File not found: "<<file_name<<endl;
        exit(1);
    }
    char ch;
    unsigned long long blob=0;
    while((file.get(ch)))
    {
        blob=blob*31+static_cast<unsigned char>(ch);
    }
    return to_string(blob);
}

void add(char* argv[], int argc)
{
    if(argc != 3)
    {
        cout<<"Usage: ./gitlite add <file_name>"<<endl;
        return;
    }

    if(!fs::exists("repository/.gitlite"))
    {
        cout<<"Repository not initialized. Please run './gitlite init' first."<<endl;
        return;
    }

    string file_name=argv[2];

    string file_hash = computeHash(file_name);
    string folder= file_hash.substr(0, 2);
    string object=file_hash.substr(2);
    fs::create_directories("repository/.gitlite/staging/objects/"+folder);
    ofstream objectFile("repository/.gitlite/staging/objects/"+folder+"/"+object, ios::binary);
    if(!objectFile)
    {
        cout<<"Error creating object file."<<endl;
        return;
    }
    ifstream file(file_name);
    if(!file)
    {
        cout<<"File not found: "<<file_name<<endl;
        exit(1);
    }
    
    objectFile << file.rdbuf();

    ofstream indexFile("repository/.gitlite/staging/index.txt", ios::app);
    if(!indexFile)
    {
        cout<<"Error opening index file."<<endl;
        return;
    }
    indexFile << file_name << " |" << file_hash << endl;
    indexFile.close();

    
    cout<<"File added to staging area: "<<file_name<<endl;

}