#include "Userid.h"
#include "Password.h"
#include <memory>

#ifndef USERACCOUNT_H
#define USERACCOUNT_H


class UserAccount {
public:
    UserAccount();  
    // constructs new account, querying the user for the userid and password
    // user is repeated prompted for userid and password until values are valid

    void authenticate( int numtries = 3 );
    // asks user for password; deactivates account after a specified number of incorrect guesses

    void deactivate();                  
    // deactivates account: userid still exists, but cannot authenticate
 
    void reactivate();                  
    // reactivates the account, asking the user for a new valid password
    // user is repeatedly prompted for a password until a valid value is provided

    bool check_deactivated() const;     
    // returns true if account is deactivated; otherwise, returns false
    
private:
    std::auto_ptr<Userid> userid_;
    std::auto_ptr<Password> passwd_;
    void Create(std::string);

    UserAccount(const UserAccount&);
    UserAccount& operator= (const UserAccount&); 
};

#endif