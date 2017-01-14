#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>
#include <math.h>
using namespace std;

void fileLine_to_vector(string, vector<string>&);
void vector_to_file(string, vector<string>&);
void compare_strings(string, string);
void number_to_word(string&);
string nine_digit_num(string&);
string three_digit_num(string&);

int main(){

	string inputFile = ("rawData.txt");
	string outputFile = ("outputData.txt");
	string temp; //string container
	vector<string> data; //data vector
	
	//read data into vector line by line
	fileLine_to_vector(inputFile, data);

	//**perform algorithm here**
	for(int i=0; i<data.size();i++){ //replaces all numbers with word equivalents
		temp = data[i].substr(7, data[i].length());
		number_to_word(temp);
		data[i].replace(7,data[i].length(),temp);
	}

	//write output to file
	vector_to_file(outputFile, data);
	
	return 0;
}

//reads from a file line by line into a vector
void fileLine_to_vector(string filename, vector<string> &fileData){
	string data;
	ifstream fin;
	fin.open(filename.data());
	while(!fin.eof()){
		getline(fin, data); //reads a single line from the input file
		fileData.push_back(data);
	} 
	fin.close();
}

void vector_to_file(string filename, vector<string> &data){
	ofstream fout;	
	fout.open(filename.data());
	for(int i=0; i<data.size(); i++)
	{
		fout << resetiosflags(ios::adjustfield);
		fout << setiosflags(ios::left);
		fout << setw(52) << data[i].substr(7, data[i].length()).c_str();
		fout << setw(3) << " ";
		fout << data[i].substr(0,3) << " " << data[i].substr(3,4) << endl; //phone number
		data[i].erase(data[i].begin(), data[i].end());
	} 
	fout.close();
}

void compare_strings(string s1, string s2){
	int pos1, pos2 = 7;
}

//converts and replaces the numbers in a string with their word equivalent
void number_to_word(string& num){
	string toWord, temp;
	int counter=0, index=0;
	for(int i=0; i<num.length(); i++){
		if(num[i] >= 48 && num[i] <= 57){
			temp = num[i];
			toWord.append(temp);
			counter++;
			if(index==0){
				index==i;
			}
		}
	}
	if(counter!=0){
		temp = nine_digit_num(toWord);
		num.replace(index,counter+1,temp);
	}
	
}

//converts up to a 9 digit number as a string to it's word equivalent
string nine_digit_num(string& num){
	//pass in a number from the range 0-999,999,999
	string thousand = "thousand ";
	string million = "million ";

	string temp;
	string word;

	while(num.length()<9){
		num.insert(0, "0");
	}
	string millions = num.substr(0,3);
	string thousands = num.substr(3,3);
	string hundreds = num.substr(6,3);

	temp = three_digit_num(millions); //checks the millions place
	if(temp != "zero "){
		word.append(temp);
		word.append(million);
	}
	temp = three_digit_num(thousands); //checks the thousands place
	if(temp != "zero "){
		word.append(temp);
		word.append(thousand);
	}
	word.append(three_digit_num(hundreds)); //checks the hundreds place
	
	return word;
}

//converts up to a 3 digit number to it's word equivalent
string three_digit_num(string& number){
	string onesNames[] = {"zero ", "one ", "two ", "three ", "four ", "five ", "six ", "seven ", "eight ", "nine "};
	string teensNames[] = {"ten ", "eleven ", "twleve ", "thirteen ", "fourteen ", "fifteen ", "sixteen ", "seventeen ", "eighteen ", "nineteen "};
	string tensNames[] = {"ten ", "twenty ", "thirty ", "fourty ", "fifty ", "sixty ", "seventy ", "eighty ", "ninety "}; 
	string hundred = "hundred ";

	string word;

	if(number.length()==3 && number[0]!='0'){ //if the number is 3 digits
		word.append(onesNames[number[0]-48]);
		word.append(hundred);
		if(number[1]=='1'){
			word.append("and ");
			word.append(teensNames[number[2]-48]);
		}
		else if(number[1] > '1'){
			word.append("and ");
			word.append(tensNames[number[1]-49]);
		}
		else if(number[1]=='0'&&number[2]!='0'){
			word.append("and ");
		}
		if(number[1]!='1'&&number[2]!='0'){
			word.append(onesNames[number[2]-48]);
		}
	}
	if(number.length()==2 && number[0]!='0'){ //if the number is 2 digits
		if(number[0]=='1'){
			word.append(teensNames[number[1]-48]);
		}
		else if(number[0]!='0'){
			word.append(tensNames[number[0]-49]);
		}
		if(number[0]!='1' && number[1]!='0'){
			word.append(onesNames[number[1]-48]);
		}
	}
	if(number.length()==1 && number[0]!=0){ //if the number is 1 digit
		word.append(onesNames[number[0]-48]);
	}
	if(number.length()==3 && number[0]=='0'){ //if the number is 3 digits with a leading zero
		if(number[1]=='0'){ //if the number is 3 digits with two leading zeros
			word.append(onesNames[number[2]-48]);
		}
		else if(number[1]=='1'){
			word.append(teensNames[number[2]-48]);
		}
		else{
			word.append(tensNames[number[1]-49]);
			word.append(onesNames[number[2]-48]);
		}
	}
	if(number.length()==2 && number[0]=='0'){ //if the number is 2 digits with leading zero
		if(number[1]=='0'){ //if the number is two digits and all zeros
			word.append(onesNames[number[1]-48]);
		}
		word.append(onesNames[number[1]-48]);
	}
	if(number.length()==1 && number[0]=='0'){ //if the number is 1 digit and zero
		word.append(onesNames[number[0]-48]);
	}
	
	return word;
}





