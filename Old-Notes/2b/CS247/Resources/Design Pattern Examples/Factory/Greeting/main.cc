#include <iostream>
#include <string>
#include "Greeting.h"
using namespace std;

int main (int argc, const char** argv)
{
	if (argc < 2)
	{
		cout << "usage: greeting language" << endl;
		return 0;
	}
	
	try
	{
		Greeting greeting(argv[1]);
		greeting.greet();
	}
	catch (exception e)
	{
		cout << "Unrecognized language" << endl;
	}
	
	return 0;
}
