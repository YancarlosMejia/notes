/*
 *  LanguageFactory.cc
 *  Assignment 3
 *
 *  Created by Adam Lesinski on 10-07-24.
 *  Copyright 2010 Student. All rights reserved.
 *
 */

#include "AbstractLanguageFactory.h"
#include "English.h"
#include "French.h"
#include "Polish.h"

AbstractLanguageFactory LanguageFactorySingleton::_factory;

/* Add new language factories here */
AbstractLanguageFactory::AbstractLanguageFactory()
{
	_languageMap["english"] = new EnglishFactory();
	_languageMap["french"] = new FrenchFactory();
	_languageMap["polish"] = new PolishFactory();
}

/* Deletes the language factories */
AbstractLanguageFactory::~AbstractLanguageFactory()
{
	std::map<std::string, LanguageFactory*>::iterator it = _languageMap.begin();
	while (it != _languageMap.end())
	{
		delete (*it).second;
		it++;
	}
}

/* Looks up the language in the language factory map and creates the required
 * language using it's corresponding factory. Returns null if no language is found.
 */
Language* AbstractLanguageFactory::createLanguage(std::string lang)
{
	std::map<std::string, LanguageFactory*>::iterator it = _languageMap.find(lang);
	if (it == _languageMap.end())
	{
		return NULL;
	}
	return (*it).second->createLanguage();
}

/* ---------------------------------------
 * LanguageFactorySingleton Implementation
 * ---------------------------------------
 */

/* Retrieves the static instance of AbstractLanguageFactory. */
AbstractLanguageFactory& LanguageFactorySingleton::getInstance()
{
	return _factory;
}