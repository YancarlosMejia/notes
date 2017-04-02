/*
 *  English.h
 *  Assignment 3
 *
 *  Created by Adam Lesinski on 10-07-24.
 *  Copyright 2010 Student. All rights reserved.
 *
 */

#ifndef H_ENGLISH
#define H_ENGLISH

#include "Language.h"

class EnglishFactory : public LanguageFactory
{
	friend class AbstractLanguageFactory;
public:
	virtual Language* createLanguage();
	
protected:
	EnglishFactory();
};
	
class English : public Language
{
	friend class EnglishFactory;
public:
	virtual void outputMessage(std::ostream& out);	
	
protected:
	English();
};

#endif