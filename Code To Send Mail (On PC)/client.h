#include <iostream>
#include <fstream>
#include <string.h>
using namespace std;
/* Structs */
struct MSG
{
    string T,F,S,TT,O;
};
struct MSG m;
class client{
    
private:
    string date;
public:
    bool is_email(string);
    string send_to_apache(const string,const string);
    void get_option();
    void send_file();
    void fetch_file();
};

string client::send_to_apache(const string ip_address,const string file_name)
{
    string command = "/usr/bin/curl -s --data-binary \"@";
    command += file_name;
    command += "\" -H \"Content-Type: application/x-www-form-urlencoded\" -X POST http://";
    command += ip_address;
    command += "/echo.php";
    FILE *pf = popen(command.c_str(),"r");
    
    if(pf){
        char data[10240];
        fread(data,1, 10240 , pf);
        pclose(pf);
        command = data;
    } else command = "error";
    return command;
    //curl -d "@/Users/kmsobh/work/AUC/AUC_Adjunct/Courses/Spring_2018/CSCE-110/code/files/test.txt" -H "Content-Type: application/x-www-form-urlencoded" -X POST http://192.168.56.102/echo.php
    
}
bool client::is_email(string entry) {
    if(entry.find('@')!=string::npos)
        if(entry.find('.')!=string::npos)
            return true;
    return false;
}
void client::get_option()
{
    cout<<"Do you want to (send/fetch) a message?"<< endl;
    cin>>m.O;
    while((m.O!="send")&&( m.O!="fetch"))
    {
        cout<<"Error picking an option. Either type send or fetch only."<<endl;
        cin>>m.O;
    }
    long seconds = time(0);
     date = to_string(seconds);
}
void client::send_file()
{
    cout<<"To: (Email Format)"<<endl;
    cin>>m.T;
    while(is_email(m.T)!=true)
    {
        cout<<"Incorrect Email Format, Try Again."<<endl;
        cin>>m.T;
    }
    cout<<"From: (Email Format)"<<endl;
    cin>>m.F;
    while(is_email(m.F)!=true)
    {
        cout<<"Incorrect Email Format, Try Again."<<endl;
        cin>>m.F;
    }
    cout<<"Subject:"<<endl;
    cin.ignore();
    getline(cin,m.S);
    cout<<"Message:"<<endl;
    
    getline (cin,m.TT);
    //File
    
    ofstream cfile;
    cfile.open("/Users/Ramy/Desktop/Project/Project/msg_"+date+".out");
    cfile<<m.O<<endl;
    cfile<<"To:"<<m.T<<endl;
    cfile<<"From:"<<m.F<<endl;
    cfile<<"Subject:"<<m.S<<endl;
    cfile<<"Text:"<<m.TT<<endl;
    cfile.close();
    cout << send_to_apache("192.168.56.102","/Users/Ramy/Desktop/Project/Project/msg_"+date+".out")<<endl;
}
void client::fetch_file()
{
    cout<<"Enter the email that you want to fetch its messages"<<endl;
    cin>>m.T;
    
    //File
    long seconds = time(0);
    string date = to_string(seconds);
    ofstream cfile;
    cfile.open("/Users/Ramy/Desktop/Project/Project/msg_"+date+".out");
    cfile<<m.O<<endl;
    cfile<<"To:"<<m.T<<endl;
    cfile.close();
    cout << send_to_apache("192.168.56.102","/Users/Ramy/Desktop/Project/Project/msg_"+date+".out")<<endl;
}
