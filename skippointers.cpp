#include <iostream>
#include <fstream>
#include <bits/stdc++.h>
using namespace std;

struct Node {
	  int val;
	  Node* next;
	  Node* skip;
};

bool hasSkip(Node* node) {
	  return node->skip != nullptr;
}

Node* skip(Node* node) {
	  return node->skip;
}

Node* constructAndAddSkipPointers(const vector<int>& v) {
  	Node* head = nullptr;
  	Node* tail = nullptr;
  	int n=v.size();
  	int t=sqrt(n);
  	Node* lastskip=nullptr;
  	for (int i = 0; i < n ; i++)
  	{
    	Node* newNode = new Node({v[i], nullptr, nullptr});
    	if (head == nullptr) 
    	{
      		head = newNode;
      		tail = newNode;
      		lastskip=newNode;
    	}
    	else 
    	{
      		tail->next = newNode;
      		tail = newNode;
    	}
	if ((i+1)%t == 0)                // to add the skip pointers after every sqrt(n) of elements
	{
      		lastskip->skip = tail;
      		lastskip=tail;
    	}
  	}
  	return head;
}


vector<int> IntersectWithSkips(Node* p1, Node* p2) {
	  vector<int> answer;
	  while (p1 != nullptr && p2 != nullptr) 
	  {
	    	if (p1->val == p2->val) 
	    	{
	      		answer.push_back(p1->val);
      			p1 = p1->next;
      			p2 = p2->next;
    		}	
    		else if (p1->val < p2->val)
    		{
      			if (hasSkip(p1) && (skip(p1)->val <= p2->val))
      			{
       		 		while (hasSkip(p1) && (skip(p1)->val <= p2->val)) 
          				p1 = skip(p1);
      			} 
      			else 
        			p1 = p1->next;
    		}
    		else 
    		{
      			if (hasSkip(p2) && (skip(p2)->val <= p1->val)) 
      			{
        			while (hasSkip(p2) && (skip(p2)->val <= p1->val))
          				p2 = skip(p2);
      			} 
      			else 
        			p2 = p2->next;
    		}
  	}
  return answer;
}

map<string, set<int>> build_index(vector<string> files)             // building the inverted index 
{
	map<string, set<int>> inverted_index;
  	for (int doc_id = 0; doc_id < files.size(); ++doc_id)              // reading the files one by one
  	{
    		ifstream file(files[doc_id]);     // open the file         
    			string line;            
    		while (getline(file, line))           // read until the EOF         
    		{
      			stringstream ss(line);           // reading the line
      			string word;
      			while (ss >> word)                // take the single word  
      			{
        			transform(word.begin(), word.end(), word.begin(), ::tolower);       // convert to lower case
        			inverted_index[word].insert(doc_id + 1);                                                    // adding it into set
      			}
    		}
  	}
  	return inverted_index;
}
int main() {
  	vector<string>  files ;
  	for(int i=1;i<=128;i++)                   // reading the files name
  	{ 
  		string temp="/home/srikanth/Information retrieval/files/";
  		string t=to_string(i);
  		temp=temp+t+".txt";
  		files.push_back(temp);              
        }
  	map<string,set<int>> inverted_index = build_index(files);
  	/*for (auto &[word, doc_ids] : inverted_index) 
  	{
    		cout << word << " : {";
    		for (auto it = doc_ids.begin(); it != doc_ids.end(); ++it) {
    			cout << *it << " ";
  		}
    		cout << "}" << endl;
  	}*/
  	string word1,word2;
  	cout<<"*******  FASTER Postings List Intersection via Skip pointers  ********\n"<<endl;
  	cout<<"     Enter two words    "<<endl;
  	cin>>word1>>word2;
  	transform(word1.begin(), word1.end(), word1.begin(), ::tolower);
  	transform(word2.begin(), word2.end(), word2.begin(), ::tolower);
  	set<int> temp1=inverted_index[word1];
  	set<int> temp2=inverted_index[word2];
  	vector<int> p1(temp1.begin(),temp1.end());
  	vector<int> p2(temp2.begin(),temp2.end());
  	if(p1.size()==0 || p2.size()==0)
  	{
  		cout<<"The given word doesn't exist in the inverted index"<<endl;
  		return 0;
  	}
  	Node * p11=constructAndAddSkipPointers(p1);
        Node * p22=constructAndAddSkipPointers(p2);
        vector<int> ans=IntersectWithSkips(p11,p22);
        cout<<"\nPostings list containing common items of '"<<word1<<"' and '"<<word2<<"'"<<endl;
    	for(int i=0;i<ans.size();i++)
    		cout<<ans[i]<<" ";
    	cout<<endl;
  	return 0;
}

