#include <iostream>
#include <sstream>
#include <vector>

using namespace std;


struct Card{
	int value;
	char suit;
	bool isStart;

	Card(int v, char s, bool b){
		value = v;
		suit = s;
		isStart = b;
	}
	Card(){};
};

void get_data(vector< vector<Card> >&, vector<string>&);
void print_data(vector< vector<Card> >&, vector<string>&, vector<int>&);
void sortCards(vector<Card>&);

int get_hand_score(vector<Card>&, vector<string>&);
int get_pairs(vector<Card>&);
int get_hand_15(vector<Card>&);
int get_flush(vector<Card>&,string&);
int get_run(vector<Card>&);
int get_nobs(vector<Card>&);

int main(){
	vector< vector<Card> > hands;
	vector<string> handTypes;
	vector<int> scores;
	int score=0;

	get_data(hands, handTypes);
	
	//sort the hands
	for(int i = 0; i < hands.size(); i++){
		sortCards(hands[i]);
	}

	//get each hands score
	for(int i=0; i<hands.size(); i++){
		score = get_hand_score(hands[i],handTypes[i]);
		scores.push_back(score);
	}	

	/*
	scores.push_back(1);
	scores.push_back(2);
	scores.push_back(3);
	scores.push_back(4);
	*/
	print_data(hands, handTypes, scores);		
}

int get_hand_score(vector<Card>& cards, string& type){
	int score=0;
	//OBscore += get_pairs(cards);
	score += get_hand_15(cards);	
	//score += get_flush(cards, type);
	//score += get_run(cards);
	//score += get_nobs(cards);
	return score;
}

int get_pairs(vector<Cards>& cards){

}

int get_hand_15(vector<Cards>& cards){
	int tmp=0, start=0, score=0, total=15;
	while(start < cards.size()){
		total -= cards[start];
		if(total < 0){
			for(int i=0; i<begin; i++){
				if(total + cards[i]==0){
					total += hand[start];
					start++;
					score+=2;
					break;
				}
			}
		}
	}
}

int get_flush(vector<Cards>& cards,string& type){

}

int get_run(vector<Cards>& cards,string& type){

}

int get_nobs(vector<Cards>& cards){


}



void sortCards(vector<Card>& cards){
	
	bool swap = true;

	while(swap){
		swap = false;

		for(int i = 1; i < cards.size(); i++){
			if(cards[i-1].value > cards[i].value){
				Card temp;
				temp = cards[i];
				cards[i] = cards[i-1];
				cards[i-1] = temp;
				swap = true;
			}
		}
	}
}

int char_to_value(char c){
	switch(c){
		case 'A': return 1;
		case 'K': return 13;
		case 'Q': return 12;
		case 'J': return 11;
		case 'T': return 10;
		default: return (c - '0');
	}
}

char value_to_char(int value){
	switch(value){
		case 13: return 'K';
		case 12: return 'Q';
		case 11: return 'J';
		case 10: return 'T';
		case 1: return 'A';
		default: return (char) value + '0';
	}
}

void get_data(vector< vector<Card> >& hands, vector<string>& handTypes){
	string temp;
	while(getline(cin, temp)){
		vector<Card> cards;

		istringstream iss(temp);

		string handTemp;
		iss >> handTemp;
		handTypes.push_back(handTemp);

		for(int i = 0; i < 4; i++){
			iss >> handTemp;
			Card newCard(char_to_value(handTemp[0]), handTemp[1], false);
			cards.push_back(newCard);
		}

		iss >> handTemp;
		Card start(char_to_value(handTemp[0]), handTemp[1], true);
		cards.push_back(start);
		hands.push_back(cards);
	}
	
}

void print_data(vector< vector<Card> >& hands, vector<string>& handTypes, vector<int>& scores){
	for(int i = 0; i < hands.size(); i++){
		if(handTypes[i] == "h"){
			cout << "Hand ";
		}
		else{
			cout << "Crib ";
		}
		for(int j = 0; j < hands[i].size(); j++){
			cout << value_to_char(hands[i][j].value) << hands[i][j].suit << " ";
		}
		
		cout << "= " << scores[i] << endl;
	}
}
