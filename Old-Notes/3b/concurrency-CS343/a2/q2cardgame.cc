#include <iostream>
#include <algorithm>
#include <math.h>
#include <fstream>
using namespace std;

#include "q2cardgame.h"
#include "PRNG.h"

unsigned int Player::playersCount;
PRNG *prng;

//Function to initialize global players count
void Player::players( unsigned int num ) {
   Player::playersCount = num;
}

//Player constructor
Player::Player( Printer &printer, unsigned int id ){
    Player::id = id;
    Player::printer = &printer;
}

//Initialize left and right pointers and start function
void Player::start( Player &lp, Player &rp ) {
    Player::left = &lp;
    Player::right = &rp;
    resume();
}

//Take a turn
void Player::play( unsigned int deck ) {
    Player::deck = deck;
    resume();
}

//Main function
void Player::main() {
    suspend();
    //Loop for each turn
    for(;;) {
        //If last remaining player return
        if(playersCount == 1){
            printer->prt(id, 0, playersCount);
            return;
        }//if

        //Take random number of cards
        int sub = (*prng)(1, 8);
        //send data to printer function
        printer->prt(id, sub, playersCount);
        //If you were passed a death deck die
        if(deck % DEATH_DECK_DIVISOR == 0) {
            //decriment number of players
            players(playersCount - 1);
            //reassign neighbors left and right pointers
            left->right = right;
            right->left = left;
        }//if
        //Remove those cards from deck
        deck -= sub;
        //If you have taken the last card print winning amount and return
        if(deck <= 0){
            printer->prt(id, sub, playersCount);
            return;
        }//if
        //Pass deck to neighbors
        if(deck % 2 == 0){
            right->play(deck);
        } else {
            left->play(deck);
        }//if
    }//for
}

//Printer constructor
Printer::Printer( const unsigned int NoOfPlayers, const unsigned int NoOfCards ){
    Printer::NoOfPlayers = NoOfPlayers;
    Printer::deck = NoOfCards;
    //Print header
    cout << "Players: " << NoOfPlayers << "    " << "Cards: " << NoOfCards << endl;
    for(unsigned int i = 0; i < NoOfPlayers; i++){
        cout << "P" << i << "\t";
    }//for
    cout << endl;
    //Initialize buffer of players
    players = new playerprinter[NoOfPlayers];
}

//Printer destructor
Printer::~Printer(){
    //deallocate memory for player buffer
    delete players;
}

//Printer prt function, called in Player main
void Printer::prt( const unsigned int id, const unsigned int took, unsigned int playersRemaining ){
    //If player buffer is full flush it
    if(players[id].touched){
        flush(id);
    }//if
    //If player took more cards than existed take only whats left
    int took_min = (deck - took < 0) ? deck : took;
    //Assigning player data to player struct
    players[id] = playerprinter();
    players[id].touched = true;
    players[id].took = took_min;
    players[id].dead = deck % Player::DEATH_DECK_DIVISOR == 0;
    players[id].last = playersRemaining == 1;
    players[id].won = deck - took_min <= 0;
    deck -= took_min;
    players[id].deck = max((int)deck, 0);
    players[id].is_right = deck % 2 == 0;
    //If player won flush despite buffer not being full
    if (deck <= 0 || playersRemaining == 1){
        flush(-1);
    }//if
}

//Printer flush function, called in prt function
void Printer::flush(int id){
    //Iterate through player buffer
    for(unsigned int i = 0; i < NoOfPlayers; i++){
        //If player slot was not used print tab and continue
        if(!players[i].touched){
            cout << "\t";
            continue;
        }//if
        //if player was the last alive print deck
        if(players[i].last){
            cout << "#" << players[i].deck << "#";
            //print player's death status
            if(players[i].dead){
                cout << "X";
            }//if
            cout <<'\t';
            continue;
        }//if
        //print players card data
        cout << players[i].took << ":" << players[i].deck;
        //print player's winning status
        if(players[i].won){
            cout << '#';
        } else {
            //if player passed print direction
            if(players[i].is_right){
                cout << '>';
            } else {
                cout << '<';
            }//if
        }//if
        //print player's death status
        if(players[i].dead){
            cout << "X";
        }//if
        //if player caused buffer overflow print marker
        if(i == (int)id) {
            cout << "*";
        }//if
        //print column spacing
        cout << "\t";
        //mark spot in buffer as available
        players[i].touched = false;

    }//for
    cout << endl;
}


void uMain::main() {
    //Wrap in a loop for multiple games
    int seed = getpid();
    int games = 5;
    //read in seed value and number of games
    switch (argc) {
        case 3:
            seed = stoi(argv[2]);
            if (seed <= 0) {
                cerr << "Error: seed value must be positive." << endl;
                exit(-1);
            }//if
        case 2:
            games = stoi(argv[1]);
            if (games < 0) {
                cerr << "Error: games value must be positive." << endl;
                exit(-1);
            }//if
    }
    //initialize randomizer with seed
    prng = new PRNG(seed);
    //loop for each game
    for(int g = 0; g < games; g++){
        //initialize random values
        unsigned int N = (*prng)(2, 10);
        int deck = (*prng)(10, 200);
        int starter = (*prng)(0, N-1);
        //Set number of players
        Player::players(N);
        //Make printer
        Printer print = Printer(N, deck);
        //Build players
        Player *players[N];
        for(unsigned int i = 0; i < N; i++){
            players[i] = new Player(print, i);
        }//for
        //Build left right relationship
        for(unsigned int i = 0; i < N; i++){
            Player *l = ( i != 0) ? players[i-1] : players[N-1];
            Player *r = ( i != N-1) ? players[i+1] : players[0];
            players[i]->start(*l, *r);
        }//for
        //start game
        players[starter]->play(deck);
        //delete players at end of game
        for(unsigned int i = 0;i < N; i++){
            delete players[i];
        }//for
        //print newline if it is not the last game
        if(g != games -1){
            cout << endl;
        }//if
    }//for
    //delete randomizer
    delete prng;
}
