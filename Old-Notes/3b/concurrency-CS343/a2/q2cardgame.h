/****************************************************
* Struct to hold player data for printer
****************************************************/

struct playerprinter{
    int deck;
    int took;
    bool dead = false; //is the player dead
    bool won = false; //did the player take last card
    bool last = false; //was player last one alive
    bool is_right = false; //did the player pass to the right
    bool touched = false; //was the slot in the buffer used yet
} ;

class Printer { //prints game state
    unsigned int NoOfPlayers;
    playerprinter *players;
    unsigned int deck;
  public:
    Printer( const unsigned int NoOfPlayers, const unsigned int NoOfCards );
    void prt( const unsigned int id, const unsigned int took, unsigned int PlayersRemaining );
    ~Printer();
  private:
    void flush(int remaining);
};


_Coroutine Player {
    Player *left;
    Player *right;
    static unsigned int playersCount;
    Printer *printer;
    int id;
    int deck;
  public:
    enum { DEATH_DECK_DIVISOR = 5 };
    static void players( unsigned int num ); // sets number of players in game
    Player( Printer &printer, unsigned int id );
    void start( Player &lp, Player &rp ); //called for each player from main to pass left and right, also sets uMain as resumer for termination
    void play( unsigned int deck ); //passes deck around to players
  private:
    void main();
};

