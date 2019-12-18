#include <thread>
using namespace std;

struct MSG{
    string T,TT,F,S;
};
struct Node{

    thread *t;
    string msg;
    Node *next;
};

class List{
private:
    Node *head, *tail, *cur;
public:
    
    List(){
        head = NULL;
        cur = NULL;
        tail = NULL;
    }
    
    Node* insertNode(string);
    bool checkDuplicate(string,Node*);
    int deleteNode(string );
    void printAll();
    
    ~List(){
        head = NULL;
        cur = NULL;
        tail = NULL;
    }
    
};

void List::printAll(){
    cout<<"----- Linked List -----"<<endl;
    cur = head;
    
    if ( cur != NULL )
    {
        if(cur==head)
            cout<<cur->msg<<endl;
        
        while ( cur->next != NULL)
        {
            if(cur==head)
                cout<<cur->msg<<endl;
            cur = cur->next;
            cout<<cur->msg<<endl;
            
        }
    }
}

Node* List::insertNode(string item)
{
    if(head==NULL)
    {
        head = new Node;
        head->next = NULL;
        head->msg = item;
        tail = cur = head;
        return cur;
    }
    else
    {   cur = head;
        if(checkDuplicate(item,head))
            return cur;
        if ( cur != NULL ) {
            while ( cur->next != NULL)
            {
                if(checkDuplicate(item,cur))
                    return cur;
                cur = cur->next;
            }
        }
        if(checkDuplicate(item,cur))
            return cur;
        cur->next = new Node;
        cur = cur->next;
        cur->next = NULL;
        cur->msg = item;
        tail = cur;
    }
    return cur;
}
int List::deleteNode(string item){
    Node *temp=new Node;
    cur = head;
    if ( cur != NULL )
    {
        if(cur->msg==item)
        {
            temp=cur->next;
            cur=cur->next;
            delete(temp);
            head=cur;
            return 0;
        }
        while ( cur->next != NULL)
        {
            if(cur->msg==item)
            {
                temp=cur->next;
                cur=cur->next;
                delete(temp);
                head=cur;
                return 0;
            }
            if(cur->next->msg==item)
            {
                if(cur->next==tail)
                {
                    temp=cur->next;
                    cur->next=NULL;
                    delete(temp);
                    tail=cur;
                    return 0;
                }
                temp=cur->next;
                cur->next=cur->next->next;
                delete(temp);
            }
            
            cur = cur->next;
        }
    }
    return 0;
}
bool List::checkDuplicate(string item, Node* temp){
    if(temp->msg==item)
        return true;
    return false;
}
/* ------------------------------------------------------------------------------- */
struct StructNode{
    MSG x;
    StructNode *next;
};
class StructList{
private:
    StructNode *head, *tail, *cur;
public:
    
    StructList(){
        head = NULL;
        cur = NULL;
        tail = NULL;
    }
    
    int insertStructNode(MSG);
    bool checkStructDuplicate(MSG,StructNode*);
    int deleteStructNode(MSG);
    MSG getNode(string);
    bool findNode(string);
    void printStructAll();
    
    ~StructList(){
        head = NULL;
        cur = NULL;
        tail = NULL;
    }
    
};

void StructList::printStructAll(){
    cout<<"----- Linked List -----"<<endl;
    cur = head;
    
    if ( cur != NULL )
    {
        if(cur==head)
            cout<<cur->x.T<<endl;
        while ( cur->next != NULL)
        {
       
            cur = cur->next;
            cout<<cur->x.T<<endl;

        }
    }
}

int StructList::insertStructNode(MSG x)
{
    if(head==NULL)
    {
        head = new StructNode;
        head->next = NULL;
        head->x = x;
        tail = cur = head;
    }
    else
    {   cur = head;
        if(checkStructDuplicate(x,head))
            return 0;
        if ( cur != NULL ) {
            while ( cur->next != NULL)
            {
                if(checkStructDuplicate(x,cur))
                    return 0;
                cur = cur->next;
            }
        }
        if(checkStructDuplicate(x,cur))
            return 0;
        cur->next = new StructNode;
        cur = cur->next;
        cur->next = NULL;
        cur->x = x;
        tail = cur;
    }

    return 0;
}
int StructList::deleteStructNode(MSG x){
    StructNode *temp=new StructNode;
    cur = head;
    
    if ( cur != NULL )
    {
        if(cur->x.T==x.T)
        {
            temp=head;
            cur=cur->next;
            delete(temp);
            head=cur;
            return 0;
        }
        while ( cur->next != NULL)
        {
            if(cur->x.T==x.T)
            {
                temp=cur->next;
                cur=cur->next;
                delete(temp);
                head=cur;
                return 0;
            }
            if(cur->next->x.T==x.T)
            {
                if(cur->next==tail)
                {
                    temp=cur->next;
                    cur->next=NULL;
                    delete(temp);
                    tail=cur;
                    return 0;
                }
                temp=cur->next;
                cur->next=cur->next->next;
                delete(temp);
            }
            
            cur = cur->next;
        }
    }
    return 0;
}
bool StructList::checkStructDuplicate(MSG x, StructNode* temp){
    if(temp->x.T==x.T)
        return true;
    return false;
}

bool StructList::findNode(string to){
    cur = head;
    if ( cur != NULL )
    {
        if(cur->x.T==to)
            return true;
        while ( cur->next != NULL)
        {
            if(cur->x.T==to)
                return true;
            if(cur->next->x.T==to)
            {
                return true;
            }
            
            cur = cur->next;
        }
    }
    return false;
}
MSG StructList::getNode(string to){
    cur = head;
    if ( cur != NULL )
    {
        if(cur->x.T==to)
            return cur->x;
        while ( cur->next != NULL)
        {
            if(cur->x.T==to)
                return cur->x;
            if(cur->next->x.T==to)
            {
                return cur->x;
            }
            
            cur = cur->next;
        }
    }
    return (cur->x);

}

