#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main(){

	string data;
	ifstream fin;
	ofstream fout;
	
	fin.open("rawData.txt");
	fout.open("outputData.txt");

	//1. read in data from a text file
	//2. write modified data to a text file
	while(!fin.eof())
	{
		getline(fin, data); //reads a single line from the input file
		fout << data.substr(7, data.length());
		fout << data.substr(0,3) << " " << data.substr(3,4);
		if(!fin.eof()){
			fout << endl;
		}
	} 
	fin.close();
	fout.close();

	return 0;

}

