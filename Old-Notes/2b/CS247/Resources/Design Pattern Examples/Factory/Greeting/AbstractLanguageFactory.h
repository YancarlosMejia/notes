/*
 *  LanguageFactory.h
 *  Assignment 3
 *
 *  Created by Adam Lesinski on 10-07-24.
 *  Copyright 2010 Student. All rights reserved.
 *
 */

#ifndef H_ABSTRACT_LANGUAGE_FACTORY
#define H_ABSTRACT_LANGUAGE_FACTORY

#include "Language.h"
#include <map>

class LanguageFactorySingleton;

/* This factory creates individual factories for the respective languages.
 * In order to add a new language, the programmer has to define the language
 * and its factory. Then simply add the language's factory to this factory's constructor.
 */
class AbstractLanguageFactory
{
	friend class LanguageFactorySingleton;
public:
	Language* createLanguage(std::string lang);
	virtual ~AbstractLanguageFactory();
	
private:
	AbstractLanguageFactory();
	
	LanguageFactory* factory;
	std::map<std::string, LanguageFactory*> _languageMap;
};

/* Singleton used because there is no need for multiple factories */
class LanguageFactorySingleton
{
public:
	static AbstractLanguageFactory& getInstance();

private:
	static AbstractLanguageFactory _factory;
	LanguageFactorySingleton();
	LanguageFactorySingleton (const LanguageFactorySingleton&);
};

// Convenience, should this factory be used often
#define LangFactory LanguageFactorySingleton::getInstance()

#endif