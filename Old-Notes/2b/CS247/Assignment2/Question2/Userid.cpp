#include "Userid.h"
#include <set>
#include <stdexcept>


//Global set of userids that are assigned to an existing account
std::set<std::string> Username;

//Error class for instances of an invalid input for UserIds
class UserIdError : public std::runtime_error {
public:
	explicit UserIdError(const std::string& msg) : std::runtime_error(msg) {}
};

//Constructs a new userid if the given string is not already take, if it is throw an exception
Userid::Userid(std::string& username) : userid(username){
	activated = true;
	if(Username.find(userid) != Username.end()) {
		throw UserIdError("Userid \"" + userid + "\" already exists.  Please try again.\n");
	}
	Username.insert(userid); 
}

//Destruct userid and remove the userid string from the set of taken userids
Userid::~Userid() {
	Username.erase(userid);
}

//Returns if an userid is active
bool Userid::isActive() const {
	return activated;
}

//Activates a userid
void Userid::activate() {
	activated = true;
}

//Deactivates a userid
void Userid::deactivate() {
	activated = false;
}
