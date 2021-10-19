/*******************************************************************************
 * CS 103 Twenty-One (Blackjack) PA
 * Name: Timothy Lin
 * USC email: ttLin@usc.edu
 * Comments (you want us to know):
 *
 *
 ******************************************************************************/

// Add other #includes if you need
#include <iostream>
#include <cstdlib>

using namespace std;

/* Prototypes */
void shuffle(int cards[]);
void printCard(int id);
int cardValue(int id);
void printHand(int hand[], int numCards);
int getBestScore(int hand[], int numCards);

const int NUM_CARDS = 52;

/**
 * Global arrays to be used as look-up tables, if desired.
 * It is up to you if and how you want to use these 
 */
const char suit[4] = {'H','S','D','C'};
const char* type[13] = 
  {"2","3","4","5","6","7",
   "8","9","10","J","Q","K","A"};
const int value[13] = {2,3,4,5,6,7,8,9,10,10,10,10,11};

/**
 * Should permute the deck of cards, effectively shuffling it.
 * You must use the Fisher-Yates / Durstenfeld shuffle algorithm
 *  described in the assignment writeup.
 */
void shuffle(int cards[])
{
  /******** You complete ****************/
  
  //Initializing deck of 52 cards to have values 0-51 in that order
  for (int i = 0; i <=51; i +=1) {
    cards[i] = i;
  }
  
  //Shuffle with given Fisher-Yates/Durstenfeld shuffle algorithm
  for (int i = 51; i >= 1; i -= 1) {
    int j = rand() % (i + 1);
    int temp_hold = cards[i];
    cards[i] = cards[j];
    cards[j] = temp_hold;
  }

}

/**
 * Prints the card in a "pretty" format:   "type-suit"
 *  Examples:  K-C  (King of clubs), 2-H (2 of hearts)
 *  Valid Types are: 2,3,4,5,6,7,8,9,10,J,Q,K,A
 *  Valid Suits are: H, D, C, S
 */
void printCard(int id)
{
  /******** You complete ****************/
  
  //Determines card type 
  const char* card_type = type[id % 13];
  
  //Determines card suit
  char card_suit;
  if (id <= 12) {
    card_suit = suit[0];
  }
  else if (id <= 25) {
    card_suit = suit[1];
  }
  else if (id <= 38) {
    card_suit = suit[2];
  }
  else if (id <= 51) {
    card_suit = suit[3];
  }
  
  //Prints out "card_type-card_suit"
  cout << card_type << "-" << card_suit;
 
}

/**
 * Returns the numeric value of the card.
 *  Should return 11 for an ACE and can then
 *  be adjusted externally based on the sum of the score.
 */
int cardValue(int id)
{
  /******** You complete ****************/

  //Determines card value and returns that number
  int card_value = value[id % 13];
  return card_value;

}

/**
 * Should print out each card in the hand separated by a space and
 * then print a newline at the end.  
 * Should use printCard() to print out each card.
 */
void printHand(int hand[], int numCards)
{
  /******** You complete ****************/

  //Loops through each card in hand array and performs printCard action
  for (int i = 0; i < numCards; i +=1) {
    printCard(hand[i]);
    cout << " ";
  }

}

/**
 * Should return the total score of the provided hand.  
 * ACES should be treated as 11s to make the highest possible hand
 *  and only being reduced to 1s as needed to avoid busting.
 */
int getBestScore(int hand[], int numCards)
{
  /******** You complete ****************/

  //Calculates total score of all cards (before transforming aces)
  int score = 0;
  for (int i = 0; i < numCards; i += 1) {
      score += cardValue(hand[i]);
    }
  
  //Changes ace(s) from 11 to 1 if they make the total score over 21
  while (score > 21) {
    for (int i = 0; i < numCards; i += 1) {
      if (cardValue(hand[i]) == 11) {
        cardValue(hand[i]) == 1;
        score -= 10;
        break;
      }
    }
    break;
  }
  
  //Returns total score
  return score;

}

/**
 * Main program logic for the game of 21
 */
int main(int argc, char* argv[])
{
  //---------------------------------------
  // Do not change this code -- Begin
  //---------------------------------------
  if(argc < 2){
    cout << "Error - Please provide the seed value." << endl;
    return 1;
  }
  int seed = atoi(argv[1]);
  srand(seed);

  int cards[52];
  int dhand[9];
  int phand[9];
  //---------------------------------------
  // Do not change this code -- End
  //---------------------------------------

  /******** You complete ****************/
  //Plays game once, and allows for game to be replayed if condition of play_again = yes is satisfied at end
  string play_again;
  do {
    
  shuffle(cards);
  
  //Draws first four cards; two for dealer and two for player
  phand[0] = cards[0];
  dhand[0] = cards[1];
  phand[1] = cards[2];
  dhand[1] = cards[3];
  int phand_index_counter = 2;
  int dhand_index_counter = 2;
  int card_index_counter = 4;
  
  //Prints out initial cards
  cout << "Dealer: ? "; printCard(dhand[1]); cout << endl;
  cout << "Player: "; printHand(phand, 2); cout << endl;
   
  //Calculates initial player score
  int player_score = getBestScore(phand, phand_index_counter);
  
  //If player score is under 21, allows them to hit or stay
  while (player_score < 21) {
    
    //Asks user if they want to draw or stay and stores response into variable hit_stay
    cout << "Type 'h' to hit and 's' to stay:" << endl;
    string hit_stay;
    cin >> hit_stay;
    
    //Draws card into player's hand, adds to appropriate counters, prints player's hand, updates score
    if (hit_stay == "h") {
      phand[phand_index_counter] = cards[card_index_counter];
      phand_index_counter += 1;
      card_index_counter += 1;
      cout << "Player: "; printHand(phand, phand_index_counter); cout << endl;
      player_score = getBestScore(phand, phand_index_counter);
    }
    
    //Exits loop prematurely if player chooses to stand or inputs other characer
    else {
      break;
    }

  }
  
  //If player score exceeds 21, they bust and lost. Prints player score vs dealer score
  //Defines true/false variable that tells whether player has busted or not
  bool player_bust = false;
  if (player_score > 21) {
    cout << "Player busts" << endl; 
    cout << "Lose " << player_score << " " << getBestScore(dhand, dhand_index_counter) << endl;
    player_bust = true;
  }
  
  //Calculates dealer's initial score
  int dealer_score = getBestScore(dhand, dhand_index_counter);
  
  //If dealer score is under 17, dealer will keep drawing until dealer score is at least 17
  while (dealer_score < 17 && player_bust == false) {
    dhand[dhand_index_counter] = cards[card_index_counter];
    dhand_index_counter += 1;
    card_index_counter += 1;
    dealer_score = getBestScore(dhand, dhand_index_counter);
  }
  
  //Prints out dealer's hand
  if (player_bust == false) {
    cout << "Dealer: "; printHand(dhand, dhand_index_counter); cout << endl;
  }
    
  //If dealer score exceeds 21, they bust and player wins. Prints player score vs dealer score
  //Defines true/false variable that tells whether dealer has busted or not
  bool dealer_bust = false;
  if (dealer_score > 21 && player_bust == false) {
    cout << "Dealer busts" << endl;
    cout << "Win " << player_score << " " << dealer_score << endl;
    dealer_bust = true;
  }
  
  //If neither busts, compares scores and outputs whether player won/lost/tie plus the scores
  if (player_score > dealer_score && player_bust == false && dealer_bust == false) {
    cout << "Win " << player_score << " " << dealer_score << endl;
    }
  else if (player_score < dealer_score && player_bust == false && dealer_bust == false) {
    cout << "Lose " << player_score << " " << dealer_score << endl;
    }
  else if (player_score == dealer_score && player_bust == false && dealer_bust == false) {
    cout << "Tie " << player_score << " " << dealer_score << endl;
    }
  
  
  cout << endl << "Play again? [y/n]" << endl;
  cin >> play_again;
  
  } while (play_again == "y");
  return 0;
}
