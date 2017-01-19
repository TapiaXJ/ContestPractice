/*
Purpose: solve ACM contest problem socalcontest.org/current/prev_probs/fonebook.htm
*/

#include <iostream>
#include <iomanip>
#include <fstream>
//#include <sstream>
#include <string>
#include <vector>
#include <math.h>
using namespace std;

void fileLine_to_vector(string&, vector<string>&);
void input_to_vector(vector<string>&);

void vector_to_file(string&, vector<string>&);
void print_vector(vector<string>&);

void alphabetize(vector<string>&);
	bool compare_strings(string&, string&);

	void number_to_word(string&);
		void nine_digit_num(string&);
			void three_digit_num(string&);

	void special_to_spaces(string&); // changes any special character to spaces

	void string_to_lower(string&); //this function makes a string all lower case
		void char_to_lower(char&);


int main(){

	string inputFile = ("rawData.txt");
	string outputFile = ("outputData.txt");
	vector<string> data; //data vector
	
	//read data into vector line by line
	//fileLine_to_vector(inputFile, data);
	input_to_vector(data);

	//**perform algorithm here**
	alphabetize(data);

	//write output to file
	print_vector(data);
	
	return 0;
}

//reads from a file line by line into a vector
void fileLine_to_vector(string& filename, vector<string> &fileData){
	string data;
	ifstream fin;
	fin.open(filename.data());
	while(!fin.eof()){
		getline(fin, data); //reads a single line from the input file
		fileData.push_back(data);
	} 
	fin.close();
}

void input_to_vector(vector<string> &inputdata){
	//use getline and istringstream
	string data, temp;
	while(cin >> temp){
		data.append(temp);
		data.append(" ");
		/*
		if(data[data.length()]=='\n'){
			inputdata.push_back(data);
			cout << data << endl;
			data.erase(data.begin(),data.end());
		}
		*/
		cout << data << endl;
	}
}

void vector_to_file(string& filename, vector<string> &data){
	ofstream fout;	
	fout.open(filename.data());
	for(int i=0; i<data.size(); i++)
	{
		fout << resetiosflags(ios::adjustfield);
		fout << setiosflags(ios::left);
		fout << setw(52) << data[i].substr(7, data[i].length()).c_str();
		fout << setw(3) << " ";
		fout << data[i].substr(0,3) << " " << data[i].substr(3,4); //phone number
		if(i != data.size()-1){
			fout << endl;
		}
		//data[i].erase(data[i].begin(), data[i].end());
	} 
	fout.close();
}

void print_vector(vector<string> &data){
	for(int i=0; i<data.size(); i++)
	{
		cout << resetiosflags(ios::adjustfield);
		cout << setiosflags(ios::left);
		cout << setw(52) << data[i].substr(7, data[i].length()).c_str();
		cout << setw(3) << " ";
		cout << data[i].substr(0,3) << " " << data[i].substr(3,4); //phone number
		if(i != data.size()-1){
			cout << endl;
		}
		//data[i].erase(data[i].begin(), data[i].end());
	} 
}

void alphabetize(vector<string> &data){
	bool swap = false;
	string temp, t1, t2;
	for(int i=0; i<data.size(); i++){
		for(int j=(i+1); j<data.size(); j++){
			t1 = data[i].substr(7, data[i].length());
			t2 = data[j].substr(7, data[j].length());
			swap = compare_strings(t1, t2); //pass characters after the phone numbers of the two entries
			if(swap){
				temp = data[i];
				data[i] = data[j];
				data[j] = temp;
			}
		}
	} 
}

bool compare_strings(string& p1, string& p2){
	//prepare strings for comparison
	number_to_word(p1);
	number_to_word(p2);
	special_to_spaces(p1);
	special_to_spaces(p2);
	string_to_lower(p1);
	string_to_lower(p2);

	//comparison logic
	for (int pos1 = 0; pos1 < p1.size();) {
		for (int pos2 = 0; pos2 < p2.size();) {
    		if(p1[pos1] > p2[pos2]){
    			return true;
    		}
    		else if(p1[pos1] < p2[pos2]){
    			return false;
    		}
			else {
				pos1++ ; pos2++;
			}
		}
    }
    return false;
}

void special_to_spaces(string& s1){
	int counter=0;
	for(int i=0; i<s1.length(); i++){
		if(!(s1[i] >= 97 && s1[i] <= 122 || s1[i] >= 65 && s1[i] <= 90)){
			s1[i] = ' ';
		}
		if(counter>0){
			if(s1[i-1]>=65 && s1[i-1]<=90 && s1[i]>=65 && s1[i]<=90){
				s1.insert(s1.begin()+counter, ' ');
			}
		}
		counter++;
	}

}

void string_to_lower(string &data){
	for(int i=0; i<data.length(); i++){
		char_to_lower(data[i]);
	}
}

void char_to_lower(char &data){
	if(data >= 'A' && data <= 'Z'){
		data += 32;
	}
}

//converts and replaces the numbers in a string with their word equivalent
void number_to_word(string& num){
	string toWord, temp;
	int counter=0, index=0;
	bool flag = false;
	for(int i=0; i<num.length(); i++){
		if(num[i] >= 48 && num[i] <= 57){
			temp = num[i];
			toWord.append(temp);
			counter++;
			if(!flag){
				index=i;
				flag=true;
			}
		}
	}
	if(counter>1){		
		nine_digit_num(toWord);
		if(index!=0){
			temp = " ";
			temp.append(toWord);
			num.replace(index-1,counter+2,temp);
		}
		else{
			num.replace(index,counter+1,toWord);
		}
	}	
}

//converts up to a 9 digit number as a string to it's word equivalent
void nine_digit_num(string& num){
	//pass in a number from the range 0-999,999,999
	string thousand = "thousand ";
	string million = "million ";

	string word;

	while(num.length()<9){
		num.insert(0, "0");
	}
	string millions = num.substr(0,3);
	string thousands = num.substr(3,3);
	string hundreds = num.substr(6,3);

	//temp = three_digit_num(millions); //checks the millions place
	three_digit_num(millions);
	if(millions != "zero "){
		word.append(millions);
		word.append(million);
	}
	//temp = three_digit_num(thousands); //checks the thousands place
	three_digit_num(thousands);
	if(thousands != "zero "){	
		word.append(thousands);
		word.append(thousand);
	}
	three_digit_num(hundreds);
	word.append(hundreds); //checks the hundreds place

	num.resize(word.size());
	num = word;
}

//converts up to a 3 digit number to it's word equivalent
void three_digit_num(string& number){
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
	number.resize(word.size());
	number=word;
}
