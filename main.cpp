/*
 * main.cpp
 *
 *  Created on: Dec 11, 2020
 *      Author: Muhamed
 */


#include <bits/stdc++.h>
using namespace std;

class TrieNode
{
public:

    unordered_map<char,TrieNode*> child;
    bool isLast;
    // Default Constructor
    TrieNode()
    {
        // Initialize all the Trie nodes with NULL
        for (char i = 'a'; i <= 'z'; i++)
            child[i] = NULL;

        isLast = false;
    }
};

TrieNode *root = NULL;

void insert(string s)
{
    int len = s.length();

    TrieNode *itr = root;
    for (int i = 0; i < len; i++)
    {

        TrieNode *nextNode = itr->child[s[i]];
        if (nextNode == NULL)
        {
            nextNode = new TrieNode();
            itr->child[s[i]] = nextNode;
        }

        itr = nextNode;
        cout<<s[i]<<"->";

        if (i == len - 1){
            itr->isLast = true;
            cout<<endl;
        }
    }
}

void displayContactsUtil(TrieNode *curNode, string prefix)
{
    if (curNode->isLast)
        cout << prefix << endl;
    for (char i = 'a'; i <= 'z'; i++)
    {
        TrieNode *nextNode = curNode->child[i];
        if (nextNode != NULL)
        {
           displayContactsUtil(nextNode, prefix + (char)i);
        }

    }
}



void insertIntoTrie(string contacts[],int n)
{
    root = new TrieNode();
    for (int i = 0; i < n; i++)
    {
        insert(contacts[i]);
    }
}

void displayContacts(string str)
{
    TrieNode *prevNode = root;

    string prefix = "";
    int len = str.length();

    int i;
    for (i=0; i<len; i++)
    {

        prefix += (char)str[i];


        char lastChar = prefix[i];


        TrieNode *curNode = prevNode->child[lastChar];
        if (curNode == NULL)
        {
            cout << "No Results Found for " << prefix << endl;
            i++;
            break;
        }
        cout << "Suggestions based on " << prefix<<  " are"<<endl;
        displayContactsUtil(curNode, prefix);
        prevNode = curNode;
    }

    for (; i<len; i++)
    {
        prefix += (char)str[i];
        cout << "No Results Found for " << prefix
             << " n";
    }
}

int main(int argc , char* argv[])
{

	string Person[100]; // maximum 100 persons
	string inputData ;
	if(argc > 1){

			for(int i = 1 ; i < argc ;i++)
			{
				Person[i-1] = argv[i];

			}

		// Size of the Contact List
		    int n = sizeof(Person)/sizeof(string);

		    // Insert all the Contacts into Trie
		    insertIntoTrie(Person, n);

		    	cin>>inputData;

		    string query = inputData;

		    // Note that the user will enter 'g' then 'e', so
		    // first display all the strings with prefix as 'g'
		    // and then all the strings with prefix as 'ge'
		    displayContacts(query);
	}
	else
	{
		cout<<"U didnt Enter Anything";
	}



    // Contact list of the User



    return 0;
}
