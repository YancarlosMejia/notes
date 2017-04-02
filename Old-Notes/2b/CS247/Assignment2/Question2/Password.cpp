#include "Password.h"
#include <stdexcept>


//Error class for instances where the string being used to set the password is of inadequate strength
class PasswordError : public std::runtime_error {
public:
	explicit PasswordError(const std::string& msg) : std::runtime_error(msg) {}
};

//Constructs a new password from the given string and tests if that string matches the stated strength rules
Password::Password(std::string& pass): password(pass) {
	int upper = 0;
	int digits = 0;
	std::string errors = "Password :\n";
	for(int i = 0; i < pass.length(); i++) {
		if(isupper(pass[i])) {
			upper += 1;
		}
		if(isdigit(pass[i])){
			digits += 1;
		}
	}
	if(pass.length() < 8) {
		errors += "    - must be at least 8 characters\n";
	}
	if(upper < 2) {
		errors += "    - must include at least 2 capital letters\n";
	} 
	if(digits < 2) {
		errors += "    - must include at least 2 digits\n";
	}
	if(pass.find_first_of("~!@#$%^&*()_-+={}[]:;<,>.?/") == std::string::npos) {
		errors += "    - must include at least 1 symbol\n";
	}
	if(errors != "Password :\n") {
		throw PasswordError(errors);
	}
}

//Returns if the password matches a given string
bool Password::validate(std::string& pass) const{
	return pass == password;
}