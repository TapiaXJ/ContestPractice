#include <iostream>
#include <sstream>
#include <vector>
#include <map>
#include <stack>

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

void get_data(vector< vector<Card> >&, vector<string>&, vector< vector<Card> >&);
void print_data(vector< vector<Card> >&, vector<string>&, vector<int>&);
void sortCards(vector<Card>&);

int value_to_real(int value);

int get_hand_score(vector<Card>&, string&);
int get_pairs(vector<Card>&);
int get_hand_15(vector<Card>&);
int get_flush(vector<Card>&,string&);
int get_run(vector<Card>&,string&);
int get_nobs(vector<Card>&);

int main(){
	vector< vector<Card> > hands;
	vector< vector<Card> > sorted;
	vector<string> handTypes;
	vector<int> scores;
	int score=0;

	get_data(hands, handTypes, sorted);
	//sort the cards in each hand
	for(int i = 0; i < hands.size(); i++){
		sortCards(sorted[i]);
	}

	//get the score of each hand
	for(int i=0; i<sorted.size(); i++){
		score = get_hand_score(sorted[i],handTypes[i]);
		scores.push_back(score);
	}	
	print_data(hands, handTypes, scores);		
}

int get_hand_score(vector<Card>& cards, string& type){
	int score=0;
	cout << "pairs: " << get_pairs(cards) << endl;
	score += get_pairs(cards);
	cout << "get 15: " << get_hand_15(cards) << endl;
	score += get_hand_15(cards);
	cout << "flush: " << get_flush(cards, type) << endl;	
	score += get_flush(cards, type);
	cout << "run: " << get_run(cards,type) << endl;
	score += get_run(cards,type);
	cout << "nobs: " << get_nobs(cards) << endl;
	score += get_nobs(cards);
	cout << endl;
	return score;
}

int get_pairs(vector<Card>& cards){
	int score =0;
	for(int i=0; i < cards.size()-1; i++){
		for(int j=i+1; j < cards.size();j++){
			if(cards[i].value==cards[j].value){
				score += 2;
			}
		}
	}
	return score;
}

int get_hand_15(vector<Card>& cards){
	int score = 0;

	for(int i = 0; i < cards.size(); i++){
		for(int j = i+1; j < cards.size(); j++){
			for(int k = j+1; k < cards.size(); k++){
				for(int p = k+1; p < cards.size(); p++){
					if(value_to_real(cards[i].value) + value_to_real(cards[j].value) + value_to_real(cards[k].value) + value_to_real(cards[p].value) == 15){
						score += 2;
					}
				}
			}
		}
	}

	for(int i = 0; i < cards.size(); i++){
		for(int j = i+1; j < cards.size(); j++){
			for(int k = j+1; k < cards.size(); k++){
				if(value_to_real(cards[i].value) + value_to_real(cards[j].value) + value_to_real(cards[k].value) == 15){
					score += 2;
				}
			}
		}
	}

	for(int i = 0; i < cards.size(); i++){
		for(int j = i+1; j < cards.size(); j++){
			if(value_to_real(cards[i].value) + value_to_real(cards[j].value) == 15){
				score += 2;
			}
		}
	}

	if(value_to_real(cards[0].value) + value_to_real(cards[1].value) + value_to_real(cards[2].value) + value_to_real(cards[3].value) + value_to_real(cards[4].value) == 15){
		score += 2;
	}
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
	int multiplier=1;
	stack<int> cardStack;
	
	for(int i=0; i<cards.size(); i++){
		if(cardStack.empty()){
			cardStack.push(cards[i].value);
		}
		else if(cardStack.top() == cards[i].value-1){
			cardStack.push(cards[i].value);
		}
		else if(cardStack.top() == cards[i].value){
			multiplier++;
		}
		else{
			if(cardStack.size()<3){
				for(int j=0;j<cardStack.size();j++){
					cardStack.pop();
				}
				cardStack.push(cards[i].value);
			}	
		}
	}

	if(get_pairs(cards) == 4){
		multiplier = 4;
	}
	if(cardStack.size()>=3){
		return cardStack.size()*multiplier;
	}
	else{
		return 0;
	}
}

int get_nobs(vector<Card>& cards){
	int score =0;
	for(int i = 0; i<cards.size()-1; i++){
		if(cards[i].value == 11 && cards[i].suit == cards[4].suit){
			score+=1;
			break;
		}
	}
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
int value_to_real(int value){
	if(value >= 10){return 10;}
	else{return value;}
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

void get_data(vector< vector<Card> >& hands, vector<string>& handTypes, vector< vector<Card> >& sorted){
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
		sorted.push_back(cards);
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


