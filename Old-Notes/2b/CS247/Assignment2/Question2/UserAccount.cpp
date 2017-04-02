#include "UserAccount.h"
#include <string>
#include <iostream>
#include <stdexcept>

//Creates new UserAccount by creating new UserId and new Password, looping until a valid input is entered.
UserAccount::UserAccount() {
	std::string username, password;
	Create("userid");
	Create("password");
}  

//Allows the user to attempt numtries number of times to input a string matching this UserAccount's password. If the max number of tries is exceeded deactivate the account. If the account is deactivated an error is thrown.
void UserAccount::authenticate( int numtries ) {
	if(check_deactivated()) {
		std::cout << "Account has been deactivated." << std::endl;
		return;
	}
	std::string attempt;
	for(; numtries > 0; numtries-=1) {
		std::cout << "Enter password: ";
		std::cin >> attempt;
		if(passwd_->validate(attempt)) {
			return;
		}
		if(numtries != 1) {
			std::cout << "Invalid password. You have " << numtries-1  << " tries to get it right." << std::endl;
		}
	}
	std::cout <<"Imposter!! Account is being deactivated!!" << std::endl;
	deactivate();
}
//Deactivates the UserAccount
void UserAccount::deactivate() {
	userid_->deactivate();
}
//Reactivates the UserAccount
void UserAccount::reactivate() {
	if(check_deactivated()) {
		Create("password");
	}
	userid_->activate();
}           
//Returns if the UerAccount has been deactivated
bool UserAccount::check_deactivated() const {
	return !userid_->isActive();
}
//Calls the correct constructor for the given data type and loops while that constructors throws an exception
void UserAccount::Create(std::string type) {
	bool unset = true;
	std::string input;
	while(unset) {
		try {
			std::cout<<"Enter preferred " << type<<": ";
			std::cin>>input;
			if(type == "userid") {
				userid_.reset(new Userid(input));
			}
			if(type == "password") {
				passwd_.reset(new Password(input));
			}
			unset = false;
		}
		catch (const std::runtime_error e) {
			std::cout<<e.what();
		}
	}
}