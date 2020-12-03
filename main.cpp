#include<bits/stdc++.h>
using namespace std;

struct contact{
    string fname,lname,num,email,job;
};

int Num;    //used to read number of contact from file
int LEFT=0,RIGHT=0;     //used in searching algorithm
contact h;  //used to store data
vector <contact> v;     //used to create a vector of contact
string VNum;    //used to change integer Num variable to string variable
vector<pair<contact,int> >tmp;  //used to create vector of pair
//contact in first and position in second
//to use in delete and update function

//Function to help in sorting struct with first name
bool FIRST(const contact &i, const contact &j){
    return i.fname < j.fname;
}

//Function to get Number of Contact from file
int vector_Number(){
    ifstream file("vector_number.txt");
    getline(file,VNum);
    stringstream VecNum(VNum);
    VecNum >> Num;
    file.close();
    return Num;
}

//Function to Update Number of contact in file
void UpdateVec_Number(int New_vecNum){
    ofstream file("vector_number.txt");
    file<< New_vecNum <<endl;
    file.close();
}

//function to update contact data with a good layout
void layout(vector<contact>&v){
    ofstream file("Vector_Print_Data.txt");
    for(int i=0;i<Num;i++){
    char ch[21]="   *****************";
    file<<"   First Name:  "<<v[i].fname<<"\n"
        <<"   Last Name:  "<<v[i].lname<<"\n"
        <<"   Mobile Number:  "<<v[i].num<<"\n"
        <<"   Email:  "<<v[i].email<<"\n"
        <<"   Job:  "<<v[i].job<<"\n";
    file<<ch<<endl;
    }file.close();
}

//Function to update contact data in a sorted way
void sorted_Data(vector<contact>&v){
    ofstream file("Vector_Data.txt");
    for(int i=0; i<Num; ++i)
    {
        file<<v[i].fname<<"\n"
            <<v[i].lname<<"\n"
            <<v[i].num<<"\n"
            <<v[i].email<<"\n"
            <<v[i].job<<endl;
    }
    file.close();
}

//function to store contact data
void Update_Data(string a,string b,string c,string d,string e){
    ofstream file("Data.txt",ofstream::app);
    file<<a<<"\n"
        <<b<<"\n"
        <<c<<"\n"
        <<d<<"\n"
        <<e<<endl;
    file.close();
}

//function to get contact data from file when open project
void ReadVector_Data(){
    v.clear();
    ifstream file("Data.txt");
    vector_Number();
    contact temp;
    string a,b,c,d,e;
    for(int i=0; i<Num; i++)
    {
        getline(file,a);
        temp.fname=a;
        getline(file,b);
        temp.lname=b;
        getline(file,c);
        temp.num=c;
        getline(file,d);
        temp.email=d;
        getline(file,e);
        temp.job=e;
        v.push_back(temp);
    }
    file.close();
    sort(v.begin(),v.end(),FIRST);
    sorted_Data(v);
    layout(v);
}

bool Check_Number(string x){
    bool t=false;
    for(int i=0;i<x.size();++i){
        if(isdigit(x[i])||x.size()>50){
            t=true;
        }
    }
    return t;
}

bool Check_alpha(string x){
    bool t=false;
    for(int i=0;i<x.size();++i){
        if(isalpha(x[i]))
        t=true;
    }
    return t;
}

bool Check_Email(string x){
    bool t=false;
    int s=x.find('@');
    int ss=x.find(".com");
    if(s<1||s+1>=ss){
        t=true;
    }
    return t;
}

//Function to add contact
void add(vector<contact>&v,contact h){
    bool t=false;
do{
    t=false;
    cout<<"\nContact first name: ";
    cin>>h.fname;
    if(Check_Number(h.fname))
        cout<<"\n\tPlease enter a valid name.\n\n";
    else t=true;
    }while(!t);
do{
    t=false;
    cout<<"\nContact last name: ";
    cin>>h.lname;
    if(Check_Number(h.lname))
        cout<<"\n\tPlease enter a valid name.\n\n";
    else t=true;
    }while(!t);
do{
    t=false;
    cout<<"\nContact mobile number: ";
    cin>>h.num;
    if(h.num.size()!=11 || Check_alpha(h.num))
        cout<<"\n\tPlease enter a valid mobile number.\n\n";
    else t=true;
    }while(!t);
do{
        t=false;
    cout<<"\nContact email: ";
    cin>>h.email;
    if(Check_Email(h.email))
        cout<<"\n\tPlease enter a valid email.\n\n";
    else t=true;
    }while(!t);
do{
        t=false;
    cout<<"\nContact job: ";
    cin>>h.job;
    if(Check_Number(h.job))
            cout<<"\n\tPlease enter a valid job name.\n\n";
    else t=true;
}while(!t);

    Update_Data(h.fname,
                h.lname,
                h.num,
                h.email,
                h.job);
    vector_Number();
    Num++;
    UpdateVec_Number(Num);
    ReadVector_Data();
}

//function to print contact
void view_all(){
    string line;
    ifstream file("Vector_Print_Data.txt");
    while(getline(file,line))
        cout<<line<<endl;
}

//Binary Search Upper bound function to get all right equal contact
int Upper_bound(vector<contact>&v,string s,int n){
int lo = 0, hi = n;
   while (lo < hi) {
      int mid = lo + (hi - lo)/2;
      if (v[mid].fname > s)
         hi = mid;
      else
         lo = mid + 1;
   }
   return lo;
}

//Binary Search Lower bound function to get all left equal contact
int Lower_bound(vector<contact>&v,string s,int n){
int lo = 0, hi = n;
   while (lo < hi) {
      int mid = lo + (hi - lo)/2;
      if (v[mid].fname < s)
         lo = mid + 1;
      else
         hi = mid;
   }
   return lo;
}

//function to Binary search on first name
//because it is sorted by first name
void Binary_search_F(vector<contact>&v,string s,int n){
    tmp.clear();
    if(!v.empty()){
           LEFT=Lower_bound(v,s,n);
           RIGHT=Upper_bound(v,s,n);
        for(int i=LEFT;i<RIGHT;i++){
            cout<<"\nFound:"
                <<"\nFirst Name:\t"<<v[i].fname
                <<"\nLast Name:\t"<<v[i].lname
                <<"\nMobile Number:\t"<<v[i].num
                <<"\nEmail:\t"<<v[i].email
                <<"\nJob:\t"<<v[i].job
                <<"\nAt Position\t"<<i+1
                <<"\n******************\n";
                tmp.push_back(make_pair(v[i],i));
        }
        if(tmp.size()==0)
            cout<<"Not Found"<<endl;
    }
    else {
        cout<<"Contact is Empty"<<endl;
    }
}

//function to linear search on last name,number,email or job
vector<pair<contact,int> > Linear_search(int P,vector<contact>&v,string s,int n){
    int pos=0;
    tmp.clear();
    if(!v.empty()){
    for(int i=0;i<n;++i){
        if(P=='L' || P=='l'){
            if(v[i].lname==s){
            pos=i;
            tmp.push_back(make_pair(v[i],pos));
            }
        }
        else if(P=='N'||P=='n'){
            if(v[i].num==s){
            pos=i;
            tmp.push_back(make_pair(v[i],pos));
            }
        }
        else if(P=='E'||P=='e'){
            if(v[i].email==s){
            pos=i;
            tmp.push_back(make_pair(v[i],pos));
            }
        }
        else if(P=='J'||P=='j'){
            if(v[i].job==s){
            pos=i;
            tmp.push_back(make_pair(v[i],pos));
            }
        }
    }
     return tmp;
    }else{cout<<"Contact is Empty"<<endl;}
}

//function to delete contact
void Delete(vector<contact>&v,string s,int m){
    int pos;
    bool t=false;
    Binary_search_F(v,s,m);
    do{
    cout<<"Chose by position which one you need to delete"<<endl;
    cin>>pos;
    if(pos<LEFT || pos>RIGHT)
        cout<<"Enter right Position"<<endl;
    else{ t=true;
    v.erase(v.begin()+pos-1);
    cout<<"Contact Deleted"<<endl;
    }
    }while(!t);
    UpdateVec_Number(Num-1);
    ofstream file("Data.txt");
    vector_Number();
    for(int i=0; i<Num; ++i){
        file<<v[i].fname<<"\n"
            <<v[i].lname<<"\n"
            <<v[i].num<<"\n"
            <<v[i].email<<"\n"
            <<v[i].job<<endl;
    }
    file.close();
    ReadVector_Data();
}

//function to edit contact
void Edit(vector<contact>&v,string d,int m){
    int pos;
    bool t=false;
    Binary_search_F(v,d,m);
    do{
    cout<<"Chose by position which one you need to Edit"<<endl;
    cin>>pos;
   if(pos<LEFT || pos>RIGHT)
        cout<<"Enter right Position"<<endl;
    else{ t=true;
    char op;
    bool t=false;
    do{
    cout<<"F To Edit in First name\n"
        <<"L To Edit in Last name\n"
        <<"N To Edit in number\n"
        <<"E To Edit in email\n"
        <<"J To Edit in job\n"
        <<"B To Back to menu\n";
    cin>>op;
    switch(op){
    case 'F':
    case 'f':{
        string name;
        do{
                t=false;
        cout<<"\nContact new first name: ";
        cin>>name;
        if(Check_Number(name))
            cout<<"\n\tPlease enter a valid name.\n\n";
        else t=true;
        }while(!t);
        v[pos-1].fname=name;
        break;
    }
    case 'L':
    case 'l':{
        string name;
        do{
                t=false;
        cout<<"\nContact new last name: ";
        cin>>name;
        if(Check_Number(name))
            cout<<"\n\tPlease enter a valid name.\n\n";
        else t=true;
        }while(!t);
        v[pos-1].lname=name;
        break;
    }
    case 'N':
    case 'n':{
        string number;
        do{
                t=false;
        cout<<"\nContact new mobile number: ";
        cin>>number;
        if(Check_alpha(number)||number.size()!=11){
            cout<<"\n\tPlease enter a valid mobile number.\n\n";
            }else t=true;
        }while(!t);
        v[pos-1].num=number;
        break;
    }
    case 'E':
    case 'e':{
        string email;
        bool t=false;
        do{
        cout<<"\nContact new email: ";
        cin>>email;
        if(Check_Email(email))
            cout<<"\n\tPlease enter a valid email.\n\n";
        else t=true;
        }while(!t);
        v[pos-1].email=email;
        break;
    }
    case 'J':
    case 'j':{
        string job;
        do{
                t=false;
        cout<<"\nContact New job: ";
        cin>>job;
        if(Check_Number(job))
            cout<<"\n\tPlease enter a valid name.\n\n";
    else t=true;
}while(!t);
        v[pos-1].job=job;
        break;
    }
    default:{
        if(op=='B'|| op=='b')
        continue;
        else{
        cout << "ERROR: Wrong Option answer\n" << endl;
        break;
        }
    }
   }}while(op!='B' && op!='b');
    }}while(!t);
    ofstream file("Data.txt");
    vector_Number();
    for(int i=0; i<Num; ++i){
        file<<v[i].fname<<"\n"
            <<v[i].lname<<"\n"
            <<v[i].num<<"\n"
            <<v[i].email<<"\n"
            <<v[i].job<<endl;
    }
    file.close();
    ReadVector_Data();
}

int main(){
char Op;    //to choose option user will do
do{
    string c,z;
    cout<<"\n\tA to Add contact"
        <<"\n\tP to Print all contacts"
        <<"\n\tS to Search for a contact"
        <<"\n\tD to Delete contact"
        <<"\n\tU to Update contact"
        <<"\n\tQ to Quit\n";
    cin>>Op;
    system("CLS");  //to Clear Console
    switch(Op){
    case 'A':
    case 'a':{
        add(v,h);
        break;
    }
    case 'P':
    case 'p':{
        view_all();
        break;
    }
    case 'S':
    case 's':{
        bool t=false;   //to keep in program if user put wrong option
        char sm;
        do{
        cout<<"How you need to search?\n"
            <<"By First name press 'F'\n"
            <<"By Last name press 'L'\n"
            <<"By Number press 'N'\n"
            <<"By Email press 'E'\n"
            <<"By Job press 'J'\n"
            <<"To Back to menu press 'B'\n";
            cin>>sm;
            system("CLS");
            switch(sm){
                case 'F':
                case 'f':{
                    string s;
                    do{
                        t=false;
                        cout<<"Enter First name You Want To Search\n";
                        cin>>s;
                    if(Check_Number(s)){
                        cout<<"\n\tPlease enter a valid name.\n\n";
                    }
                    else{
                        t=true;
                        ReadVector_Data();
                        Binary_search_F(v,s,v.size());
                        }
                    }while(!t);
                break;
                }
                case 'L':
                case 'l':{
                        string s;
                        do{
                        t=false;
                        cout<<"Enter Last name You Want To Search\n";
                        cin>>s;
                        if(Check_Number(s))
                        cout<<"\n\tPlease enter a valid name.\n\n";
                        else{ t=true;
                        ReadVector_Data();
                        Linear_search(sm,v,s,v.size());
                        if(tmp.size()==0)
                            cout<<"Not Found"<<endl;
                        else
                        for(int i=0;i<tmp.size();++i){
                            cout<<"\nFound:"
                            <<"\nFirst Name:\t"<<tmp[i].first.fname
                            <<"\nLast Name:\t"<<tmp[i].first.lname
                            <<"\nMobile Number:\t"<<tmp[i].first.num
                            <<"\nEmail:\t"<<tmp[i].first.email
                            <<"\nJob:\t"<<tmp[i].first.job
                            <<"\nAt Position\t"<<tmp[i].second
                            <<"\n******************\n";
                        }
                        }
                }while(!t);
                break;
                }
                case 'N':
                case 'n':{
                        string s;
                        do{
                        t=false;
                        cout<<"Enter Number You Want To Search\n";
                        cin>>s;
                        if(Check_alpha(s)||s.size()!=11)
                        cout<<"\n\tPlease enter a valid mobile number.\n\n";
                        else
                            t=true;
                        if(t){
                        ReadVector_Data();
                        Linear_search(sm,v,s,v.size());
                        if(tmp.size()==0)
                            cout<<"Not Found"<<endl;
                        else
                        for(int i=0;i<tmp.size();++i){
                            cout<<"\nFound:"
                            <<"\nFirst Name:\t"<<tmp[i].first.fname
                            <<"\nLast Name:\t"<<tmp[i].first.lname
                            <<"\nMobile Number:\t"<<tmp[i].first.num
                            <<"\nEmail:\t"<<tmp[i].first.email
                            <<"\nJob:\t"<<tmp[i].first.job
                            <<"\nAt Position\t"<<tmp[i].second
                            <<"\n******************\n";
                        }
                        }
                        }while(!t);
                        break;
                    }
                case 'E':
                case 'e':{
                    string s;
                    do{
                    t=false;
                    cout<<"Enter Email You Want To Search\n";
                    cin>>s;
                   if(Check_Email(s))
                    cout<<"\n\tPlease enter a valid email.\n\n";
                    else {t=true;
                     ReadVector_Data();
                    Linear_search(sm,v,s,v.size());
                    if(tmp.size()==0)
                        cout<<"Not Found"<<endl;
                    else
                    for(int i=0;i<tmp.size();++i){
                        cout<<"\nFound:"
                        <<"\nFirst Name:\t"<<tmp[i].first.fname
                        <<"\nLast Name:\t"<<tmp[i].first.lname
                        <<"\nMobile Number:\t"<<tmp[i].first.num
                        <<"\nEmail:\t"<<tmp[i].first.email
                        <<"\nJob:\t"<<tmp[i].first.job
                        <<"\nAt Position\t"<<tmp[i].second
                        <<"\n******************\n";
                    }
                    }
                }while(!t);
                    break;
                            }
                case 'J':
                case 'j':{
                        string s;
                        do{
                        t=false;
                        cout<<"Enter Job You Want To Search\n";
                        cin>>s;
                        if(Check_Number(s))
                        cout<<"\n\tPlease enter a valid Job name.\n\n";
                        else{ t=true;
                        ReadVector_Data();
                        Linear_search(sm,v,s,v.size());}
                        if(tmp.size()==0)
                            cout<<"Not Found"<<endl;
                        else
                        for(int i=0;i<tmp.size();++i){
                            cout<<"\nFound:"
                            <<"\nFirst Name:\t"<<tmp[i].first.fname
                            <<"\nLast Name:\t"<<tmp[i].first.lname
                            <<"\nMobile Number:\t"<<tmp[i].first.num
                            <<"\nEmail:\t"<<tmp[i].first.email
                            <<"\nJob:\t"<<tmp[i].first.job
                            <<"\nAt Position\t"<<tmp[i].second
                            <<"\n******************\n";
                        }
                        }while(!t);
                        break;
                    }
                case 'B':
                case 'b':{
                        break;
                        }
                    default:
                          cout << "ERROR: Wrong Option answer\n" << endl;
                          break;
                        }
                        }while(sm!='B'&&sm!='b');
                        break;
                    }
            case 'D':
            case 'd':{
                cout<<"Enter contact first name you want to delete\n";
                cin>>c;
                ReadVector_Data();
                Delete(v,c,v.size());
                break;
            }
            case 'U':
            case 'u':{
                cout<<"Enter contact first name you want to edit\n";
                cin>>z;
                ReadVector_Data();
                Edit(v,z,v.size());
                break;
            }
    default:{
            if(Op=='Q'|| Op=='q')
                cout<<"Phone System Ended"<<endl;
            else{
            cout << "ERROR: Wrong Option answer\n" << endl;
            break;}
    }
        }
    }while(Op!='Q' && Op!='q');
        return 0;
}
