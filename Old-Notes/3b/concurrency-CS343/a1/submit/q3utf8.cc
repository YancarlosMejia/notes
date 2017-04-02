#include <fstream>
#include <iostream>

using namespace std;
/*
 * Coroutine to determine if a series of bytes composes a valid
 * utf8 encoded character
 */


_Coroutine Utf8 {
  public:
    /*
     * Event triggered when a series of bytes composes a valid
     * utf8 encoded character
     */

    _Event Match {
      public:
        unsigned int unicode;
        Match( unsigned int unicode ) : unicode( unicode ) { }
    };

    /*
     * Event triggered when an invalid byte is processed
     */
    _Event Error {};
  private:
    /*
     * Union of structures to get bitfeilds of varying sizes from character
     * representing the byte currently being processed by the coroutine
     */
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
            unsigned char dt : 4;        // data
            unsigned char ck : 4;        // check
        } t3;
        struct {
            unsigned char dt : 3;        // data
            unsigned char ck : 5;        // check
        } t4;
        struct {                         // type for extra UTF-8 bytes
            unsigned char dt : 6;        // data
            unsigned char ck : 2;        // data
        } dt;
    } utf8;

  public:
    /*
     * Function for current process of coroutine
     */

    void main() {

        //Find the length of utf encoding, and process first byte
        int length;
        unsigned int total;
        if(utf8.t1.ck == 0){
            length = 1;
            total = utf8.t1.dt;
        } else if(utf8.t2.ck == 6){
            length = 2;
            total = utf8.t2.dt << ((length - 1) * 6);
        } else if(utf8.t3.ck == 14){

            length = 3;
            total = utf8.t3.dt << ((length - 1) * 6);
        } else if(utf8.t4.ck == 30){
            length = 4;
            total = utf8.t4.dt << ((length - 1) * 6);
        } else {
            length = 0;
            _Resume Error() _At resumer();
            return;
        } //if


        //Process bytes up to required length or newline character
        int i = 1;
        for(; utf8.ch != '\n' && i < length; i += 1){
            suspend();

            //Test that all characters has 10 prefix and add its value to running total
            if(i != 0 && (int)utf8.dt.ck != 2){
                _Resume Error() _At resumer();
                return;
            } else {
                total |= (utf8.dt.dt << ((length - i - 1) * 6));
            }
        } //for

        //If valid number of bytes have been processed check total against ranges
        if(i == length){
            if(length == 1 && total > 0x7F){
                _Resume Error() _At resumer();
            } else if(length == 2 && (total < 0x80 || total > 0x7FF)){
                _Resume Error() _At resumer();
            } else if(length == 3 && (total < 0x800 || total > 0xFFFF)){
                _Resume Error() _At resumer();
            } else if(length == 4 && (total < 0x10000 || total > 0x10FFFF)){
                _Resume Error() _At resumer();
            } else {
                _Resume Match(total) _At resumer();
            }
        } else {
            _Resume Error() _At resumer();
        } //if

        return;
    }

    /*
     * Function for moving on to next step in coroutine
     */

    void next( unsigned char ch ) {
        utf8.ch = ch;                     // insert character into union for analysis
        resume();
    }
};

void uMain::main() {
    istream *infile;
    unsigned char buffer[ 1 ];

    //Attempt to open input file
    if(argc > 1){
        try {
            infile = new ifstream( argv[1] );
            *infile >> noskipws;
        } catch( uFile::Failure ) {
            cerr << "Error! Could not open input file \"" << argv[1] << "\"" << endl;
            exit(-1);
        }
    } else {
        infile = &cin;
    }



    for ( ;; ) {
        //Read first character
        infile->read((char*)( &buffer[0]), 1);
        if ( infile->eof() ) {
            break;
        }//if

        //Check for empty line
        if(buffer[0] == '\n'){
            cout << " : Warning! Blank line." << endl;
            continue;
        }

        //Create coroutine
        Utf8 utf8;
        cout << "0x" ;
        for (;;){
            //Print character currently being processed
            if(buffer[0] != '\n') {
                cout << hex << (unsigned int)buffer[0];
            }//if

            //Advance coroutine
            try{
                _Enable{
                    utf8.next(buffer[0]);
                }
            } catch(Utf8::Match m){
                cout << " : valid 0x" << hex << m.unicode;
                break;
            }
            catch(Utf8::Error e){
                cout << " : invalid";
                break;
            }

            //Read next character
            infile->read((char*)( &buffer[0]), 1);
            if ( infile->eof() ) {
                break;
            } //if
        } //for

        //Check for extra characters
        if(buffer[0] != '\n'){
            infile->read((char*)( &buffer[0]), 1);

            if ( infile->eof() ) {
                break;
            }//if

            //Print extra characters prompt
            if(buffer[0] != '\n') {
                cout << ". Extra characters 0x";
            }//if

            //Print extra characters
            while(buffer[0] != '\n') {
                cout << hex << (unsigned int)buffer[0];

                infile->read((char*)( &buffer[0]), 1);
                if ( infile->eof() ) {
                    break;
                }//if
            } //while
        }

        //Print ending newline
        cout << endl;

        if ( infile->eof() ) {
            break;
        }//if
    } //for

    if (infile != &cin) {
        delete infile;
    }//if
}
