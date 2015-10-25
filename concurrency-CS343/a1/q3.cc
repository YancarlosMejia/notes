_Coroutine Utf8 {
  public:
    _Event Match {
      public:
        unsigned int unicode;
        Match( unsigned int unicode ) : unicode( unicode ) {}
    };
    _Event Error {};
  private:
    union UTF8 {
        unsigned char ch;                // character passed by cocaller
        struct {                         // types for 1st UTF-8 byte
            unsigned char dt : 7;        // data
            unsigned char ck : 1;        // check
        } t1;
        struct {
            unsigned char dt : 5;        // data
            unsigned char ck : 3;        // check
        } t2;
        struct {
            // YOU FIGURE IT OUT
        } t3;
        struct {
            // YOU FIGURE IT OUT
        } t4;
        struct {                         // type for extra UTF-8 bytes
            // YOU FIGURE IT OUT
        } dt;
    } utf8;
    // YOU MAY ADD PRIVATE MEMBERS
  public:
    // YOU MAY ADD CONSTRUCTOR/DESTRUCTOR IF NEEDED
    void next( unsigned char c ) {
        utf8.ch = c;                     // insert character into union for analysis
        resume();
    }
};
