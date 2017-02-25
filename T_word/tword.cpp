#include <iostream>
#include <queue>
#include <vector>
#include <list>

using namespace std;

void get_data(vector<string>&, vector<string>&);
void print_data(vector<string>&, vector<int>&);
int compare(string&,string&);


struct wordDiff{
	
	string data;
	int diff;
	wordDiff(string s, int i){
		data = s;
		diff = i;
	}
	wordDiff(){}
};

void get_LL(list<string>&list, vector<string>&dict){
	for(int i =0; i<dict.size();i++){
		list.push_back(dict[i]);
	}

}

int main(){
	vector<string> dict;
	vector<string> problems;
	vector<int> solutions;
	get_data(dict, problems);		
	queue<wordDiff> q;

	for(int i=0; i<problems.size()/2;i++){		
	wordDiff w1(problems[i*2],0);
	list<string> LLdict;
	get_LL(LLdict, dict);

	list<string>::iterator firstIter = LLdict.begin();

	while(*firstIter != w1.data){
		firstIter++;
	}
	LLdict.erase(firstIter);

	q.push(w1);
	
	while(!q.empty()){
		int diff;
		wordDiff temp = q.front();
		q.pop();

		list<string>::iterator itr = LLdict.begin();
		while(itr != LLdict.end()){
			diff = compare(temp.data,*itr);
			cout << "Comparing: " << temp.data << " " << *itr << endl;
			cout<< "Comparing 2 values, diff: " << diff << " temp.diff: " << temp.diff << endl;
			if(diff==1){
				//cout <<"Difference was 1" << endl;
				wordDiff t1(*itr,temp.diff+1);
				q.push(t1);
				if(*itr==problems[(i*2)+1]){
					//cout << "found final word" << endl;
					solutions.push_back(temp.diff+1);
					goto end;
				}
				//cout<<"about to erase" << endl;
				LLdict.erase(itr++);
			}
			itr++;
		}
	}
	end:;
	}
	print_data(problems, solutions);
}


int compare(string& s1, string& s2){
	if(s1.length()!=s2.length()){return -1;} //-1 if not equal
	int result=0;
	
	//cout << "COMPARING: " << s1 << " " << s2 << endl;	
	for(int i=0; i<s1.length(); i++){
		if(s1[i]!=s2[i]){result++;}	
	}	
	return result;
}

void print_data(vector<string>&problems,vector<int>&solutions){
	for(int i=0; i<solutions.size();i++){
		cout << problems[i*2] << ' ' << problems[(i*2)+1] << ' ' << solutions[i] << endl; 
	}
		
}

void get_data(vector<string>&data,vector<string>&problems){
	string temp;
	getline(cin, temp);
	while(temp!="*"){
		data.push_back(temp);
		getline(cin, temp);
	} 
	while(cin >> temp){
		problems.push_back(temp);
	}
	//cout << "Finished getting data" << endl;
}

