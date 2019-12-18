#include "client.h"

int main()
{
    string option;
    client user;
    user.get_option();
    if(m.O=="send")
        user.send_file();
    if(m.O=="fetch")
        user.fetch_file();
    
    return 0;
}
