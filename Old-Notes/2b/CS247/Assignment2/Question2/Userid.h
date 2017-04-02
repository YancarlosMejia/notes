#include <string>

class Userid {
public:
	Userid(std::string&);
	~Userid();	
	bool isActive() const;
	void activate();
	void deactivate();
private:
	std::string userid;
	bool activated;

	Userid();
	Userid(const Userid&);
	Userid& operator= (const Userid&); 

};