//MADE BY:Spidy-PS(PRIYANSH SHARMA)
#include<bits/stdc++.h>
using namespace std;

#define end _end
#define next _nxt

int total=1000;
const int Max=500500;
int end[Max];
int next[27][Max];
int SC_count=0;
bool created[Max];
int sz=0;

vector<string> AC_ans;
vector<string> S_ans;

void FTS_insert(string &s)
{
    int v=0;
    for(int i=0;i<s.size();i++)
    {
        int c=s[i]-'a';
        if(!created[next[c][v]])
        {
            next[c][v]=++sz;
            created[sz]=1;
        }
        v=next[c][v];
    }
    ++end[v];
}

bool FTS_search(string tmp)
{
    int v=0;
    for(int i=0;i<tmp.size();i++)
    {
        int c=tmp[i]-'a';
        if(!created[next[c][v]])
            return false;
        v=next[c][v];
    }
    return end[v]>0;
}
 
int Full_text_search()
{
    ifstream myFile;
    myFile.open("test.csv");
    int row_count =0 ;
    string line;
    int i=0;
    string key[total];
    while(getline(myFile,line))
    {   
        row_count +=1;
        stringstream  lineStream(line);
        string cell;
        int column_count = 0 ;
        while(getline(lineStream,cell,','))
        {
            column_count+=1;
            if ( column_count == 2)
            {
                key[i]=cell;
                i++;
                FTS_insert(cell);
            }
        }
    }
    myFile.close();
    string a;
    cout<<"\n INSERT THE NAME YOU WANT TO FIND IN CONTACT LIST : "<<endl;
    cin>>a;
    cout<<endl;
    if(FTS_search(a)==0)
       cout<<"Record not found in your contact list."<<endl;
    if(FTS_search(a)) 
    {
        cout<<"Record found in your contact list."<<endl;
        ifstream myFile;
        myFile.open("test.csv");
        int row_count =0 ;
        string line;
        int pos=0;
        while(getline(myFile,line))
        {   
            row_count +=1;
            stringstream  lineStream(line);
            string cell;
            int column_count = 0 ;
            while(getline(lineStream,cell,','))
            {
                column_count+=1;
                if ( column_count == 2)
                {
                    if(cell.compare(a)==0)
                    {
                        pos=row_count;
                        break;
                    }
                }
            }   
        }
        myFile.close();
        myFile.open("test.csv");
        row_count =0 ;
        string line1;
        while(getline(myFile,line1))
        {   
            row_count +=1;
            stringstream  lineStream(line1);
            string cell;
            int column_count = 0 ;
            while(getline(lineStream,cell,','))
            {
                column_count+=1;
                if(row_count==pos && (column_count==1 || column_count==2 || column_count==3 || column_count==4 || column_count==5))
                {
                    if(column_count==1)
                        cout<<"Id \t\t:  ";
                    if(column_count==2)
                        cout<<"Name \t\t:  ";
                    if(column_count==3)
                        cout<<"Contact Number  :  ";
                    if(column_count==4)
                        cout<<"Operator \t:  ";
                    if(column_count==5)
                        cout<<"Location \t:  ";
                    cout<<cell<<endl;
                }
            }
        }
    }
    return 0;
}

struct S_Trie
{
    int index;
    S_Trie* child[26];
    S_Trie()
    {
        for (int i = 0; i < 26; i++)
            child[i] = NULL;
        index = -1;
    }
};

void S_insert(S_Trie* root, string str, int index)
{
    S_Trie* node = root;
    for (int i = 0; i < str.size(); i++) {
        char ind = str[i] - 'a';
        if (!node->child[ind])
            node->child[ind] = new S_Trie();
        node = node->child[ind];
    }
    node->index = index;
}

bool S_preorder(S_Trie* node, string arr[])
{
    if (node == NULL)
        return false;
    for (int i = 0; i < 26; i++) 
    {
        if (node->child[i] != NULL) 
        {
            if (node->child[i]->index != -1)
                S_ans.push_back(arr[node->child[i]->index]);
            S_preorder(node->child[i], arr);
        }
    }
}

void S_printSorted(string arr[], int n)
{
    S_Trie* root = new S_Trie();
    for (int i = 0; i < n; i++)
        S_insert(root, arr[i], i);
    S_preorder(root, arr);
}

int sort_name()
{
    int a,b;
    cout<<" \n ENTER THE RANGE (A,B) : "<<endl;
    cin>>a>>b;
    cout<<endl;
    cout<<"\t\t\t\t\t\tContact list sorted by Name :\n"<<endl;
    cout<<"ID\t\t\tNAME\t\t\tNUMBER\t\t\tOPERATOR\t\tLOCATION"<<endl;
    int n;
    n=b-a+1;
    int i=0;
    string arr[n];
    ifstream myFile;
        myFile.open("test.csv");
        int row_count =0 ;
        string line;
        while(getline(myFile,line))
        {   
            row_count +=1;
            stringstream  lineStream(line);
            string cell;
            int column_count = 0 ;
            while(getline(lineStream,cell,','))
            {
                column_count+=1;
                if(column_count==2 and row_count>=a and row_count<=b)
                {
                    arr[i]=cell;
                    i++;
                    break;
                }
            }        
        }
    S_printSorted(arr, n);
    int q=S_ans.size();
    int index[q]={-1};
    int p=0;
    while(q--)
    {  
        ifstream myFile;
        myFile.open("test.csv");
        int row_count =0 ;
        string line;
        while(getline(myFile,line))
        {   
            row_count +=1;
            stringstream  lineStream(line);
            string cell;
            int column_count = 0 ;
            int vai=p;
            while(getline(lineStream,cell,','))
            {
                column_count+=1;
                string abc=S_ans.at(p); 
                if ( column_count == 2)
                {
                    if(cell.compare(abc)==0)
                    {
                        index[p]=row_count;
                        p++;
                        break;
                    }
                }
            }
            if(vai<p)
            {
               break;
            }
        }
    }
    q=S_ans.size();
    p=0;
    while(q--)
    {  
        ifstream myFile;
        myFile.open("test.csv");
        int row_count =0 ;
        string line;
        while(getline(myFile,line))
        {   
            row_count +=1;
            stringstream  lineStream(line);
            string cell;
            int column_count = 0 ;
            while(getline(lineStream,cell,','))
            {
                column_count+=1;
                if((index[p]==row_count) && (column_count==1 || column_count==2 || column_count==3 || column_count==4 || column_count==5))
                {
                    if(cell.size()<8)
                        cout<<cell<<"\t\t\t";
                    else
                        cout<<cell<<"\t\t";
                }
            }
            if(index[p]==row_count)
            {
                p++;
                cout<<endl;
            }   
        }
    }
    S_ans.clear();
    return 0;
}

int sort_operator()
{
    int a,b;
    cout<<" \n ENTER THE RANGE (A,B) : "<<endl;
    cin>>a>>b;
    cout<<endl;
    cout<<"INPUT THE OPERATOR : "<<endl;
    string opr;
    cin>>opr;
    cout<<"\t\t\t\t\t\tContact list sorted by Operator :\n"<<endl;
    cout<<"ID\t\t\tNAME\t\t\tNUMBER\t\t\tOPERATOR\t\tLOCATION"<<endl;
    int n;
    n=b-a+1;
    int i=0;
    string arr[n];
    ifstream myFile;
        myFile.open("test.csv");
        int row_count =0 ;
        string line;
        while(getline(myFile,line))
        {   
            row_count +=1;
            stringstream  lineStream(line);
            string cell;
            int column_count = 0 ;
            while(getline(lineStream,cell,','))
            {
                column_count+=1;
                if(column_count==2 and row_count>=a and row_count<=b)
                {
                    arr[i]=cell;
                }
                if(column_count==4 and row_count>=a and row_count<=b)
                {
                    if(cell.compare(opr)==0)
                    {
                        i++;
                        break;
                    }
                }
            }        
        }
    S_printSorted(arr, i);
    int q=S_ans.size();
    int index[q]={-1};
    int p=0;
    while(q--)
    {  
        ifstream myFile;
        myFile.open("test.csv");
        int row_count =0 ;
        string line;
        while(getline(myFile,line))
        {   
            row_count +=1;
            stringstream  lineStream(line);
            string cell;
            int column_count = 0 ;
            int vai=p;
            while(getline(lineStream,cell,','))
            {
                column_count+=1;
                string abc=S_ans.at(p);
                if ( column_count == 2)
                {                    
                    if(cell.compare(abc)==0)
                    {
                        index[p]=row_count;
                        p++;
                        break;
                    }
                }
            }
            if(vai<p)
            {
               break;
            }
        }
    }
    q=S_ans.size();
    p=0;
    while(q--)
    {  
        ifstream myFile;
        myFile.open("test.csv");
        int row_count =0 ;
        string line;
        while(getline(myFile,line))
        {   
            row_count +=1;
            stringstream  lineStream(line);
            string cell;
            int column_count = 0 ;
            while(getline(lineStream,cell,','))
            {
                column_count+=1;
                if((index[p]==row_count) && (column_count==1 || column_count==2 || column_count==3 || column_count==4 || column_count==5))
                {
                    if(cell.size()<8)
                        cout<<cell<<"\t\t\t";
                    else
                        cout<<cell<<"\t\t";
                }
            }            
            if(index[p]==row_count)
            {
                p++;
                cout<<endl;
            }   
        }
    }
    S_ans.clear();
    return 0;
}

int sort_loc()
{
    int a,b;
    cout<<" \n ENTER THE RANGE (A,B) : "<<endl;
    cin>>a>>b;
    cout<<endl;
    cout<<"INPUT THE LOCATION : "<<endl;
    string loc;
    cin>>loc;
    cout<<"\t\t\t\t\t\tContact list sorted by Location :\n"<<endl;
    cout<<"ID\t\t\tNAME\t\t\tNUMBER\t\t\tOPERATOR\t\tLOCATION"<<endl;
    int n;
    n=b-a+1;
    int i=0;
    string arr[n];
    ifstream myFile;
        myFile.open("test.csv");
        int row_count =0 ;
        string line;
        while(getline(myFile,line))
        {   
            row_count +=1;
            stringstream  lineStream(line);
            string cell;
            int column_count = 0 ;
            while(getline(lineStream,cell,','))
            {
                column_count+=1;
                if(column_count==2 and row_count>=a and row_count<=b)
                {
                    arr[i]=cell;
                }
                if(column_count==5 and row_count>=a and row_count<=b)
                {
                    if(cell.compare(loc)==0)
                    {
                        i++;
                        break;
                    }
                }
            }        
        }
    S_printSorted(arr, i);
    int q=S_ans.size();
    int index[q]={-1};
    int p=0;
    while(q--)
    {  
        ifstream myFile;
        myFile.open("test.csv");
        int row_count =0 ;
        string line;
        while(getline(myFile,line))
        {   
            row_count +=1;
            stringstream  lineStream(line);
            string cell;
            int column_count = 0 ;
            int vai=p;
            while(getline(lineStream,cell,','))
            {
                column_count+=1;
                string abc=S_ans.at(p);
                if ( column_count == 2)
                {
                    if(cell.compare(abc)==0)
                    {
                        index[p]=row_count;
                        p++;
                        break;
                    }
                }
            }
            if(vai<p)
            {
               break;
            }
        }
    }
    q=S_ans.size();
    p=0;
    while(q--)
    {  
        ifstream myFile;
        myFile.open("test.csv");
        int row_count =0 ;
        string line;
        while(getline(myFile,line))
        {   
            row_count +=1;
            stringstream  lineStream(line);
            string cell;
            int column_count = 0 ;
            while(getline(lineStream,cell,','))
            {
                column_count+=1;
                if((index[p]==row_count) && (column_count==1 || column_count==2 || column_count==3 || column_count==4 || column_count==5))
                {
                    if(cell.size()<8)
                        cout<<cell<<"\t\t\t";
                    else
                        cout<<cell<<"\t\t";
                }
            }
            if(index[p]==row_count)
            {
                p++;
                cout<<endl;
            }   
        }
    }
    S_ans.clear();
    return 0;
}

int sort_op()
{
    int choice;
    cout<<"\n\n\n\t\t\t\t\t\t  SORT OPERATIONS in a given range (a,b)"<<endl;
    cout<<endl<<endl<<endl;
    cout<<"\n\t\t\t\t\t\t 1: SORT CONTACT LIST BY NAME "<<endl<<endl;
    cout<<"\n\t\t\t\t\t\t 2: SORT CONTACT LIST BY OPERATOR"<<endl<<endl;
    cout<<"\n\t\t\t\t\t\t 3: SORT CONTACT LIST BY LOCATION "<<endl<<endl;
    cout<<"\n\t\t\t\t\t\t 4: EXIT"<<endl<<endl;
    cout<<"------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------"<<endl; 
    cin>>choice;
    switch(choice)
    {
        case 1:
        {
            system("cls");
            sort_name();
            break;
        }
        case 2:
        {
            system("cls");
            sort_operator();
            break;
        }
        case 3:
        {
            system("cls");
            sort_loc();
            break;
        }
        case 4:
        {
            system("cls");
            cout<<"\n\n\n";
            cout<<"\t\t\t\t\t\tThank you";
            break;
        }
        default:
        {
            system("cls");
            cout<<"\n\n\n";
            cout<<"\n \t\t\t\t\t\tWrong choice entered"<<endl;
            break;
        }
    }
}

struct TrieNode_AC
{
    struct TrieNode_AC *children[26];
    bool isWordEnd;
};

struct TrieNode_AC *getNode(void)
{
    struct TrieNode_AC *pNode = new TrieNode_AC;
    pNode->isWordEnd = false;
    for (int i = 0; i < 26; i++)
        pNode->children[i] = NULL;
    return pNode;
}

void AC_insert(struct TrieNode_AC *root, const string key)
{
    struct TrieNode_AC *pCrawl = root;
    for (int level = 0; level < key.length(); level++)
    {
        int index = key[level]-'a';
        if (!pCrawl->children[index])
            pCrawl->children[index] = getNode();

        pCrawl = pCrawl->children[index];
    }
    pCrawl->isWordEnd = true;
}

bool AC_search(struct TrieNode_AC *root, const string key)
{
    int length = key.length();
    struct TrieNode_AC *pCrawl = root;
    for (int level = 0; level < length; level++)
    {
        int index = key[level]-'a';
        if (!pCrawl->children[index])
            return false;
        pCrawl = pCrawl->children[index];
    }
    return (pCrawl != NULL && pCrawl->isWordEnd);
}

bool AC_isLastNode(struct TrieNode_AC *root)
{
    for (int i = 0; i < 26; i++)
        if (root->children[i])
            return 0;
    return 1;
}

void AC_suggestionsRec(struct TrieNode_AC* root, string currPrefix)
{
    if (root->isWordEnd)
    {
        AC_ans.push_back(currPrefix);
    }
    if (AC_isLastNode(root))
        return;
    for (int i = 0; i < 26; i++)
    {
        if (root->children[i])
        {
            currPrefix.push_back(97 + i);
            AC_suggestionsRec(root->children[i], currPrefix);
            currPrefix.pop_back();
        }
    }
}

int AC_printAutoSuggestions(TrieNode_AC* root, const string query)
{
    struct TrieNode_AC* pCrawl = root;
    int level;
    int n = query.length();
    for (level = 0; level < n; level++)
    {
        int index = query[level]-'a';
        if (!pCrawl->children[index])
            return 0;
        pCrawl = pCrawl->children[index];
    }
    bool isWord = (pCrawl->isWordEnd == true);
    bool isLast = AC_isLastNode(pCrawl);
    if (isWord && isLast)
    {
        AC_ans.push_back(query); 
        return -1;
    }
    if (!isLast)
    {
        string prefix = query;
        AC_suggestionsRec(pCrawl, prefix);
        return 1;
    }
}

int auto_comp()
{
    struct TrieNode_AC* root = getNode();
    ifstream myFile;
    myFile.open("test.csv");
    int row_count =0 ;
    string line;
    while(getline(myFile,line))
    {   
        row_count +=1;
        stringstream  lineStream(line);
        string cell;
        int column_count = 0 ;
        while(getline(lineStream,cell,','))
        {
            column_count+=1;
            if(column_count==2)
            {
                AC_insert(root,cell);
            }
        }        
    }
    string key;
    cout<<"\n Insert the initials of the contact name : "<<endl;
    cin>>key;
    cout<<endl<<endl<<endl;
    int comp = AC_printAutoSuggestions(root, key);
    if (comp == -1)
        cout << "No other Name found with this prefix in the contact list"<<endl;
    else if (comp == 0)
        cout << "No Name found with this prefix in the contact list\n";
    cout<<"ID\t\t\tNAME\t\t\tNUMBER\t\t\tOPERATOR\t\tLOCATION"<<endl<<endl;
    int q=AC_ans.size();
    int index[q]={-1};
    int p=0;
    while(q--)
    {  
        ifstream myFile;
        myFile.open("test.csv");
        int row_count =0 ;
        string line;
        while(getline(myFile,line))
        {   
            row_count +=1;
            stringstream  lineStream(line);
            string cell;
            int column_count = 0 ;
            int vai=p;
            while(getline(lineStream,cell,','))
            {
                column_count+=1;
                string abc=AC_ans.at(p);
                if ( column_count == 2)
                {
                    if(cell.compare(abc)==0)
                    {
                        index[p]=row_count;
                        p++;
                        break;
                    }
                }
            }
            if(vai<p)
            {
               break;
            }
        }
    }
    q=AC_ans.size();
    p=0;
    while(q--)
    {  
        ifstream myFile;
        myFile.open("test.csv");
        int row_count =0 ;
        string line;
        while(getline(myFile,line))
        {   
            row_count +=1;
            stringstream  lineStream(line);
            string cell;
            int column_count = 0 ;
            while(getline(lineStream,cell,','))
            {
                column_count+=1;
                if((index[p]==row_count) && (column_count==1 || column_count==2 || column_count==3 || column_count==4 || column_count==5))
                {
                    if(cell.size()<8)
                        cout<<cell<<"\t\t\t";
                    else
                        cout<<cell<<"\t\t";
                }
            }
            if(index[p]==row_count)
            {
                p++;
                cout<<endl;
            }   
        }
    }
    return 0;
}

struct TrieNode_SC {
    TrieNode_SC* Trie[256];
    bool isEnd;
    TrieNode_SC()
    {
        for (int i = 0; i < 256; i++) {
            Trie[i] = NULL;
        }
        isEnd = false;
    }
};

void SC_InsertTrie(TrieNode_SC* root, string s)
{

    TrieNode_SC* temp = root;
    for (int i = 0; i < s.length(); i++) {
        if (temp->Trie[s[i]] == NULL) {
            temp->Trie[s[i]] = new TrieNode_SC();
        }
        temp = temp->Trie[s[i]];
    }
    temp->isEnd = true;
}

void SC_printSuggestions(TrieNode_SC* root, string res)
{
    if (root->isEnd == true) 
    {
        SC_count++;
        cout<<SC_count<<" : ";
        cout << res << endl;
    }
    for (int i = 0; i < 256; i++) 
    {
        if (root->Trie[i] != NULL) 
        {
            res.push_back(i);
            SC_printSuggestions(root->Trie[i], res);
            res.pop_back();
        }
    }
}

bool SC_checkPresent(TrieNode_SC* root, string key)
{
    for (int i = 0; i < key.length(); i++) 
    {
        if (root->Trie[key[i]] == NULL) 
        {
            cout<<"NO , The record with same spelling is not present in contact list\n"<<endl<<endl<<endl;
            cout<<"\nRecords with similar Names :\n"<<endl<<endl;
            SC_printSuggestions(root, key.substr(0, i));
            return false;
        }
        root = root->Trie[key[i]];
    }
    if (root->isEnd == true) 
    {
        return true;
    }
    cout<<"NO , The record with same spelling is not present in contact list"<<endl<<endl<<endl;
    cout<<"Records with similar Names :"<<endl<<endl;
    SC_printSuggestions(root, key);
    return false;
}

int spell_check()
{
    ifstream myFile;
    myFile.open("test.csv");
    int row_count =0 ;
    string line;
    vector<string> str ;
    while(getline(myFile,line))
    {   
        row_count +=1;
        stringstream  lineStream(line);
        string cell;
        int column_count = 0 ;
        while(getline(lineStream,cell,','))
        {
            column_count+=1;
            if ( column_count == 2)
            {
                str.push_back(cell);
            }
        }
    }
    myFile.close();
    string key;
    cout<<"\n ENTER THE CONTACT NAME : "<<endl;
    cin>>key;
    cout<<endl;
    TrieNode_SC* root = new TrieNode_SC();
    for (int i = 0; i < str.size(); i++) 
    {
        SC_InsertTrie(root, str[i]);
    }
    if (SC_checkPresent(root, key)) 
    {
        cout << "YES , The record with same spelling is present in contact list\n "<<endl;
        myFile.open("test.csv");
        int row_count =0,pos=0;
        while(getline(myFile,line))
        {   
            row_count +=1;
            stringstream  lineStream(line);
            string cell;
            int column_count = 0 ;
            while(getline(lineStream,cell,','))
            {
                column_count+=1;
                if ( column_count == 2)
                {
                    if(cell.compare(key)==0)
                    {
                        pos=row_count;
                        break;
                    }
                }
            }
        }    
        myFile.close();
        myFile.open("test.csv");
        row_count =0;
        while(getline(myFile,line))
        {   
            row_count +=1;
            stringstream  lineStream(line);
            string cell;
            int column_count = 0 ;
            while(getline(lineStream,cell,','))
            {
                column_count+=1;
                if(row_count==pos && (column_count==1 || column_count==2 || column_count==3 || column_count==4 || column_count==5))
                {
                    if(column_count==1)
                        cout<<"Id \t\t:  ";
                    if(column_count==2)
                        cout<<"Name \t\t:  ";
                    if(column_count==3)
                        cout<<"Contact Number  :  ";
                    if(column_count==4)
                        cout<<"Operator \t:  ";
                    if(column_count==5)
                        cout<<"Location \t:  ";
                    cout<<cell<<endl;
                }
            }
            if(row_count>pos)
                break;
        } 
        myFile.close();    
    }
    return 0;
}

int insert_on_dataset()
{
    ofstream my;
    my.open("test.csv",ios::app);
    total++;
    stringstream ss;
    ss << total;
    string str = ss.str();
    my<<str<<",";
    int i=0;
    string a1,a2,a3,a4;
    cout<<"Name \t\t:  "<<endl;
    cin>>a1;
    cout<<"Contact Number  :  "<<endl;
    cin>>a2;
    cout<<"Operator \t:  "<<endl;
    cin>>a3;
    cout<<"Location \t:  "<<endl;
    cin>>a4;
    my<<a1<<","<<a2<<","<<a3<<","<<a4<<endl;
    cout<<"\n NEW RECORD INSERTED"<<endl;
    return 0;
}

int delete_in_dataset()
{
    fstream fin, fout; 
    fin.open("test.csv", ios::in); 
    fout.open("test12.csv", ios::out);
    int row_count =0 ;
    string line;
    int id;
    cout << "Enter the id of the record to be deleted: "<<endl;
    cin >> id; 
    int count=0;
    while(getline(fin,line))
    {   
        row_count +=1;
        stringstream  lineStream(line);
        string cell;
        int column_count = 0 ;
        string a1,a2,a3,a4,a5;
        while(getline(lineStream,cell,','))
        {
            column_count+=1;
            if(row_count==id)
            {
                count=1;
                a1="zzzzz";
                a2="zzzzz";
                a3="zzzzz";
                a4="zzzzz";
                a5="zzzzz";
            }
            else
            {
                if(column_count==1 )
                    a1=cell;
                if(column_count==2 )
                    a2=cell;
                if(column_count==3 )
                    a3=cell;
                if(column_count==4 )
                    a4=cell;
                if(column_count==5 )
                    a5=cell;
            }
        }
        fout<<a1<<","<<a2<<","<<a3<<","<<a4<<","<<a5<<endl;
    }
    if (count == 1) 
        cout << "Record deleted\n"; 
    else
        cout << "Record not found\n"; 
    fin.close(); 
    fout.close();
    fstream my;
    my.open("test.csv",ios::out | ios::trunc);
    my.close(); 
    fin.open("test12.csv", ios::in); 
    fout.open("test.csv", ios::out);
    row_count =0 ;
    while(getline(fin,line))
    {   
        row_count +=1;
        stringstream  lineStream(line);
        string cell;
        int column_count = 0 ;
        string a1,a2,a3,a4,a5;
        while(getline(lineStream,cell,','))
        {
            column_count+=1;
            if(column_count==1 )
                a1=cell;
            if(column_count==2 )
                a2=cell;
            if(column_count==3 )
                a3=cell;
            if(column_count==4 )
                a4=cell;
            if(column_count==5 )
                a5=cell;
        }
        fout<<a1<<","<<a2<<","<<a3<<","<<a4<<","<<a5<<endl;
    }
    fin.close(); 
    fout.close();
    my.open("test12.csv",ios::out | ios::trunc);
    my.close(); 
    return 0;
}

int operation_on_dataset()
{
    int choice;
    cout<<"\n\n\n\t\t\t\t\t\t  DATASET OPERATIONS"<<endl;
    cout<<endl<<endl<<endl;
    cout<<"\n\t\t\t\t\t\t 1: Insert  a new entry in dataset"<<endl<<endl;
    cout<<"\n\t\t\t\t\t\t 2: delete a entry from dataset"<<endl<<endl;
    cout<<"\n\t\t\t\t\t\t 3: EXIT"<<endl<<endl;
    cout<<"------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------"<<endl;  
    cin>>choice;
    switch(choice)
    {
        case 1:
        {
            system("cls");
            char ch='Y';
            while(ch=='Y')
            {
                system("cls");
                insert_on_dataset();
                cout<<"\n\n\n\n\t DO YOU WANT TO INSERT MORE ENTRY ? (Y/N) :"<<endl;
                cin>>ch;
            }
            break;
        }
        case 2:
        {
            system("cls");
            delete_in_dataset();
            break;
        }
        case 3:
        {
            system("cls");
            cout<<"\n\n\n";
            cout<<"\t\t\t\t\t\tThank you";
            break;
        }
        default:
        {
            system("cls");
            cout<<"\n\n\n";
            cout<<"\n \t\t\t\t\t\tWrong choice entered"<<endl;
            break;
        }
    }
    return 0;
}

int contact_list()
{
    int choice;
    cout<<"\n\n\n\t\t\t\t\t\t   CONTACT LIST OPERATIONS"<<endl;
    cout<<endl<<endl<<endl;
    cout<<"\n\t\t\t\t\t\t 1: FULL TEXT SEARCH "<<endl<<endl;
    cout<<"\n\t\t\t\t\t\t 2: SORT THE CONTACT LIST AS PER REQUIREMENT"<<endl<<endl;
    cout<<"\n\t\t\t\t\t\t 3: AUTO-COMPLETE OPERATION "<<endl<<endl;
     cout<<"\n\t\t\t\t\t\t 4: SPELL- CHECKER OPERATION "<<endl<<endl;
    cout<<"\n\t\t\t\t\t\t 5: EXIT"<<endl<<endl;
    cout<<"------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------"<<endl;    cin>>choice;
    switch(choice)
    {
        case 1:
        {
            system("cls");
            Full_text_search();
            break;
        }
        case 2:
        {
            system("cls");
            sort_op();
            break;
        }
        case 3:
        {
            system("cls");
            auto_comp();
            break;
        }
        case 4:
        {
            system("cls");
            spell_check();
            break;
        }
        case 5:
        {
            system("cls");
            cout<<"\n\n\n";
            cout<<"\t\t\t\t\t\tThank you";
            break;
        }
        default:
        {
            system("cls");
            cout<<"\n\n\n";
            cout<<"\n \t\t\t\t\t\tWrong choice entered"<<endl;
            break;
        }
    }
    return 0;
}

int main() 
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    system("cls");
    int choice;
    cout<<"\n\n\n\t\t\t\t\t\t   WELCOME TO Public Call Operations"<<endl;
    cout<<endl<<endl<<endl;
    cout<<"\n\t\t\t\t\t\t 1: Operations on Dataset"<<endl<<endl;
    cout<<"\n\t\t\t\t\t\t 2: Access the Contact List"<<endl<<endl;
    cout<<"\n\t\t\t\t\t\t 3: EXIT"<<endl<<endl;
    cout<<"------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------"<<endl;
    cin>>choice;
    switch(choice)
    {
        case 1:
        {
            system("cls");
            operation_on_dataset();
            break;
        }
        case 2:
        {
            system("cls");
            contact_list();
            break;
        }
        case 3:
        {
            system("cls");
            cout<<"\n\n\n";
            cout<<"\t\t\t\t\t\tThank you";
            break;
        }
        default:
        {
            system("cls");
            cout<<"\n\n\n";
            cout<<"\n \t\t\t\t\t\tWrong choice entered"<<endl;
            break;
        }
    }
    return 0;
}
