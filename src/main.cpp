#include<iostream>
#include<unordered_map>
#include<functional>

#include "../commands/version.h"
#include "../commands/init.h"
#include "../commands/add.h"
#include "../commands/commit.h"
#include "../commands/log.h"
#include "../commands/checkout.h"

using namespace std;
int main(int argc, char* argv[])
{
    if(argc < 2)
    {
        cout << "Usage: gitlite <command>\n";
        return 0;
    }

    string command=argv[1];
    
    unordered_map<string, function<void()>>
    commands_list=
    {
        {"version",version},
        {"init",init},
        {"add",add},
        {"commit",commit},
        {"log",log},
        {"checkout",checkout}
    };
    if(commands_list.find(command)!=commands_list.end())
    {
        commands_list[command]();
    }
    else
    {
        cout<<"Unknown command: "<<command<<endl;
    }
    return 0;
}