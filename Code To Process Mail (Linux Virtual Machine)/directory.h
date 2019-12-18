#include <iostream>
#include <fstream>
#include <string.h>
#include <mutex>
#include <dirent.h>
#include "linkedlist.h"
using namespace std;
List Folders;
StructList List;
bool checkdirectory(string);
void checkfolders(string);
void processFile(string);
int getfilename(string);
void check(string,string);
void send(string,bool);
void fetch(string,bool,string);
void file_to_struct(string);
void falsefile(string);

mutex mtx_add;

bool checkdirectory(string directory)
{
    DIR *dir;
    if ((dir = opendir (directory.c_str())) != NULL)
    {
        closedir (dir);
        return true;
    }
    return false;
}
void checkfolders (string dir_name) {
    DIR *dp; // Directory
    struct dirent *ep; // Directory entry
    dp = opendir (dir_name.c_str()); // Open directory
    if (dp != NULL) { // If Not NULL then directory opened
        ep = readdir (dp); // Read first item from directory
        while (ep != NULL){ // If ep != NULL then we have a valid directory item
            if ( strcmp (ep->d_name,".") != 0 && strcmp (ep->d_name,"..") != 0 && strcmp (ep->d_name,".DS_Store") != 0 ) { // Exclude special files/dirs
                {
                    if ( ep->d_type == DT_DIR) {
                    string ipadd=ep->d_name;
                    Node* test=  Folders.insertNode(ipadd); // Print item (file/directory) name
                    test->t = new thread(processFile,ipadd);
                    }
                }
            }
            ep = readdir (dp); // Read next directory item
        }
        closedir (dp); // Close directory after reading all items
    }
}

void processFile(string folder)
{
    while(true)
    {
    string dir=directory+"/"+folder;
    getfilename(dir);
       
    }
}
int getfilename(string direc)
{
    string f;
    DIR *dirr;
    struct dirent *entt;
    if ((dirr = opendir (direc.c_str())) != NULL) {
        while ((entt = readdir (dirr)) != NULL) {
            if ( strcmp (entt->d_name,".") != 0 && strcmp (entt->d_name,"..") != 0 && strcmp (entt->d_name,".DS_Store") != 0 ) { // Exclude special files/dirs
                {
                f=entt->d_name;
            if(f.length()>=4)//Checks if name is bigger than 4(With extension)
                if(f.substr( f.length() - 4 ) == ".out")//Checks if extension is .out
                {
                    f=f.substr(0, f.size()-4);//Sends the name of file without extension
                    check(direc,f);
                }
            }
        }
    }
        closedir (dirr);
    }
    else
        return 0;
    
    return 0;
    return 0;
}

void check(string direc, string file)
{
    string address=direc+"/"+file+"";
    bool flag=false;
    //Reading the file
    ifstream cfile;
    cfile.open((address+".out").c_str());
    cfile.peek();
    if (cfile) //Check Open
    {
        if(!cfile.eof())//Check Empty
        {
            string To,action;
            getline(cfile, action);
            getline(cfile, To);
            if(To!="To:")//Check if there is a reciever
                flag=true;
            if(action=="send")
                send(address,flag);
            else if(action=="fetch")
                fetch(address,flag,To);
            else
                falsefile(address);
        }
    else
        falsefile(address);
    cfile.close();
    }
}


void send(string address,bool flag)
{
    if(flag)
    {//Success
        ofstream file;
        file.open((address+ ".in").c_str());
        file<<"SUCCESS"<<endl;
        file.close();
        
        
        file_to_struct(address);

        remove((address+ ".out").c_str()); //Turns string name to characters to delete file
    }
    else
    {//Failure
        ofstream file;
        file.open((address+ ".in").c_str());
        file<<"FAILURE"<<endl;
        file.close();
        remove((address+ ".out").c_str()); //Turns string name to characters to delete file
    }
}
void fetch(string address, bool flag, string To)
{
    if(flag)
    {//Success
        
        if(List.findNode(To))
                {
                    MSG x=List.getNode(To);
                    ofstream  file;
                    file.open((address+ ".in").c_str());
                    file<<x.T<<endl;
                    file<<x.F<<endl;
                    file<<x.S<<endl;
                    file<<x.TT<<endl;
                    file.close();
                    remove((address+ ".out").c_str());
                    mtx_add.lock();
                    List.deleteStructNode(x);
                    mtx_add.unlock();
                    return;
                }
            else
            {//Failure
                ofstream file;
                file.open((address+ ".in").c_str());
                file<<"FAILURE"<<endl;
                file<<"This User Has No Messages."<<endl;
                file.close();
                remove((address+ ".out").c_str());
            }
        
        
    }
    else
    {//Failure
        ofstream file;
        file.open((address+ ".in").c_str());
        file<<"FAILURE"<<endl;
        file<<"Error In Getting The Message."<<endl;
        file.close();
        remove((address+ ".out").c_str());
    }
}
void file_to_struct(string address)
{
    MSG m;
    string temp;
    ifstream pfile;
    pfile.open((address+ ".out").c_str());
    getline(pfile,temp);
    getline(pfile,m.T);
    getline(pfile,m.F);
    getline(pfile,m.S);
    getline(pfile,m.TT);
    pfile.close();
    mtx_add.lock();
    List.insertStructNode(m);
    mtx_add.unlock();

}
void falsefile(string address)
{
    
    ofstream file;
    file.open((address+ ".in").c_str());
    file<<"ERROR! \nYour Request Couldn't Be Recieved!"<<endl;
    file.close();
    remove((address+ ".out").c_str()); //Turns string name to characters to delete file
}
