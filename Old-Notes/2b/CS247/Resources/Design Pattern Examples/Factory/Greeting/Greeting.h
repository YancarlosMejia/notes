/*
 *  Greeting.h
 *  Assignment 3
 *
 *  Created by Adam Lesinski on 10-07-25.
 *  Copyright 2010 Student. All rights reserved.
 *
 */

#ifndef H_GREETING
#define H_GREETING

#include <string>
#include <new>

class Language;

class Greeting
{
public:
	Greeting(std::string language) throw (std::bad_alloc);
	~Greeting();
	void greet();
private:
	Language* _language;
};

#endif