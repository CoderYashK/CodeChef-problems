/*
A message through time Problem Code: TIME14
All submissions for this problem are available.

 

There was a watch.

 
Input

A string

 
Output

A string containing only '!' and '?'

 
Constraints

The input string is a permutation of ['A', 'E', 'L', 'M', 'O', 'R', 'S', 'U']

 
Example

Input:
LAM

Output:
?!???!!!
*/

    #include<bits/stdc++.h>
    using namespace std;
    int main()
    {
    	string s;
    	cin >> s;
    	char arr[8]={'A','E','L','M','O','R','S','U'};
    	for(int i=0;i<s.size();i++)
    	{
    		if(s[i]=='A')
    			cout << "?!";
    		else if(s[i]=='E')
    			cout<<"?";
    		else if(s[i]=='L')
    			cout<<"?!??";
    		else if(s[i]=='M')
    			cout << "!!";
    		else if(s[i]=='O')
    			cout<<"!!!";
    		else if(s[i]=='R')
    			cout << "?!?";
    		else if(s[i]=='S')
    			cout << "???";
    		else if(s[i]=='U')
    			cout << "??!";
    	}
    }
     
