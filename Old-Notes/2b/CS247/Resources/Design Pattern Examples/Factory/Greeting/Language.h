/*
 *  Language.h
 *  Assignment 3
 *
 *  Created by Adam Lesinski on 10-07-24.
 *  Copyright 2010 Student. All rights reserved.
 *
 */

#ifndef H_LANGUAGE
#define H_LANGUAGE

#include <ostream>
#include <string>

class Language;
class AbstractLanguageFactory;

/* The base language factory all other langauge factories inherit.
 * The only method needed to be subclassed is createLanguage().
 */
class LanguageFactory
{
	friend class AbstractLanguageFactory;
public:
	virtual ~LanguageFactory();
	
	virtual Language* createLanguage() = 0;
	
protected:
	LanguageFactory();
};

/* The base language. */
class Language
{
	/* LanguageFactory must be a friend in order to invoke the constructor of Language. */
	friend class LanguageFactory;
public:
	virtual void outputMessage(std::ostream& out) = 0;
	virtual ~Language();
	
protected:
	/* The constructor is protected so that it cannot be instantiated by anything other
	 * than its factory. It's not private because subclasses need to call it.
	 */
	Language();
};

#endif