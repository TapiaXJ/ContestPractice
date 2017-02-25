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

int get_hand_score(vector<Card>&, string&);
int get_pairs(vector<Card>&);
int get_hand_15(vector<Card>&);
int get_flush(vector<Card>&,string&);
int get_run(vector<Card>&,string&);
int get_nobs(vector<Card>&);

int main(){
	vector< vector<Card> > hands;
	vector<string> handTypes;
	vector<int> scores;
	int score=0;

	get_data(hands, handTypes);
	//sort the cards in each hand
	for(int i = 0; i < hands.size(); i++){
		sortCards(hands[i]);
	}

	//get the score of each hand
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
	score += get_pairs(cards);
	score += get_hand_15(cards);	
	score += get_flush(cards, type);
	score += get_run(cards,type);
	score += get_nobs(cards);
	return score;
}

int get_pairs(vector<Card>& cards){
	int score =0;
	int numPairs = 0;

	for(int i = 1; i < cards.size(); i++){
		if(cards[i-1].value == cards[i].value) {
			numPairs++;
		}
	}

	score = 2 * numPairs * numPairs - 1;
	return score;
}

int get_hand_15(vector<Card>& cards){
	int tmp=0, start=0, score=0, total=15;
	cout << "1\n";
	while(start < cards.size()){
	cout << "2\n";
		total -= cards[start].value;
		if(total < 0){
			for(int i=0; i<start; i++){
			cout << "3\n";
				if(total + cards[i].value==0){
					cout << "3a\n";
					total += cards[start].value;
					start++;
					score+=2;
					break;
				}	
			}
			start++;
		}
		else{start++;}
	cout << "4\n";
	}
	cout << "22\n";
	return score;
}

int get_flush(vector<Card>& cards,string& type){	
	//Check the first 4 cards
	for(int i = 1; i < cards.size() - 1; i++){
		if(cards[i-1].suit != cards[i].suit) {
			return 0;
		}
	}

	if(cards[0].suit == cards[cards.size() - 1].suit) {
		return 5;
	}

	//If 4 card flush and crib, no points
	if(type == "c"){
		return 0;
	}
	else {
		return 4;
	}
}

int get_run(vector<Card>& cards,string& type){
	int score =0;
	return score;
}

int get_nobs(vector<Card>& cards){
	int score =0;
	return score;

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
	string handTemp;
	while(getline(cin, temp)){
		vector<Card> cards;
		
		istringstream iss (temp);
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
