#define _GLIBCXX_USE_CXX11_ABI 0
#include <iostream>
#include <fstream>
#include <string.h>
#include <dirent.h>
#include <unistd.h>
#include <thread>
using namespace std;
string directory = "/tmp/spool";
#include "directory.h"


int main(){
    
    while(checkdirectory(directory)!=true)
        sleep(5);
    while(true)
    {
        checkfolders(directory);
        sleep(5);
    }
    return 0;
}

