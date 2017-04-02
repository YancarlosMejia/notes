/*
 *  Greeting.cc
 *  Assignment 3
 *
 *  Created by Adam Lesinski on 10-07-25.
 *  Copyright 2010 Student. All rights reserved.
 *
 */

#include "Greeting.h"
#include "AbstractLanguageFactory.h"
#include "English.h"
#include "Polish.h"
#include <iostream>

Greeting::Greeting(std::string language) throw (std::bad_alloc)
{
	_language = LanguageFactorySingleton::getInstance().createLanguage(language);
	if (!_language)
	{
		throw std::bad_alloc();
	}
	
	/*
	 * This is to show that the constructor's of both the LanguageFactory's and
	 * the Language's themselves can not be called directly. End result is that
	 * Language's can only be created from the AbstractLanguageFactory.
	 */
	
	/*
	 Language* english = new English();
	 LanguageFactory* factory = new PolishFactory();
	 Language* polish = factory->createLanguage();
	 */
}

Greeting::~Greeting()
{
	if (_language)
	{
		delete _language;
	}
}

void Greeting::greet()
{
	if (_language)
	{
		_language->outputMessage(std::cout);
		std::cout << std::endl;
	}
}