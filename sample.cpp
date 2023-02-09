#include<bits/stdc++.h>
using namespace std;
using namespace std::chrono;
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
    		if ((i+1)%t == 0) 
    		{
      			lastskip->skip = tail;
      			lastskip=tail;
    		}
  	}
  return head;
}

vector<int> findIntersection(Node* h1, Node* h2) {
  	vector<int> result;
 	while (h1 != NULL && h2 != NULL)
 	{
    		if (h1->val == h2->val) 
    		{
      			result.push_back(h1->val);
      			h1 = h1->next;
      			h2 = h2->next;
    		}
    		else if (h1->val < h2->val) 
      			h1 = h1->next;
    		else 
      			h2 = h2->next;
  	}
  	return result;
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


int main()
{
    	vector<int> p1={71,24555,49000,49998,99998};
    	vector<int> p2;
    	for(int i=1;i<100000;i++)
    		p2.push_back(i);
    	Node * p11=constructAndAddSkipPointers(p1);
    	Node * p22=constructAndAddSkipPointers(p2);
     	// Start the clock
    	auto start = high_resolution_clock::now();
    	vector<int> ans=IntersectWithSkips(p11,p22);
    	auto stop = high_resolution_clock::now();
    	// Calculate the duration of the code
   	auto duration = duration_cast<microseconds>(stop - start);
    	cout << "\nTime taken by the Faster Skip pointers interesection " << duration.count() << " microseconds\n" << endl;
    	// Start the clock
    	auto start1 = high_resolution_clock::now();
    	vector<int> ans1=findIntersection(p11,p22);
    	auto stop1 = high_resolution_clock::now();
    	// Calculate the duration of the code
   	auto duration1 = duration_cast<microseconds>(stop1 - start1);
    	cout << "Time taken by the Normal intersection " << duration1.count() << " microseconds\n\n" << endl;
    	cout<<"Posting list containing common items\n";
    	for(int i=0;i<ans1.size();i++)
    		cout<<ans1[i]<<" "<<endl;
}
