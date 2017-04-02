#include <string>

class Password{
public:
	Password(std::string&);
	bool validate(std::string&) const;

private:
	std::string password;
	Password();
};