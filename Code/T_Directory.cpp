#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>
#include <math.h>
using namespace std;

void fileLine_to_vector(string, vector<string>&);

int main(){

	string filename = ("rawData.txt");
	vector<string> data;

	//read data into vector line by line
	fileLine_to_vector(filename, data);

	//**perform algorithm here**



	//write output to file
	ofstream fout;	
	fout.open("outputData.txt");
	for(int i=0; i<data.size(); i++)
	{
		cout << data[i] << endl;
		fout << resetiosflags(ios::adjustfield);
		fout << setiosflags(ios::left);
		fout << setw(52) << data[i].substr(7, data[i].length()).c_str();
		fout << setw(3) << " ";
		fout << data[i].substr(0,3) << " " << data[i].substr(3,4) << endl; //phone number
		data[i].erase(data[i].begin(), data[i].end());
	} 
	fout.close();
	return 0;
}

void fileLine_to_vector(string filename, vector<string> &fileData){
	string data;
	ifstream fin;
	fin.open(filename.data());
	while(!fin.eof())
	{
		getline(fin, data); //reads a single line from the input file
		fileData.push_back(data);
	} 
	fin.close();
}

