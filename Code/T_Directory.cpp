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
		for(char* i = data.begin()+7; i!=data.end(); i++){ //write all characters after the 7th to file (name)
			fout << *i;
		}
		for(char* i = data.begin(); i!=data.begin()+7; i++){ //write characters 1-7 to file (phonenumber)
			fout << *i;
			if(i==data.begin()+2){ //add a space after the first 3 digits of the phone number
				fout << " ";
			}
		}
		if(!fin.eof()){
			fout << endl;
		}
	} 
	fin.close();
	fout.close();

	return 0;

}

