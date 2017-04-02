/*
 *  Polish.h
 *  Assignment 3
 *
 *  Created by Adam Lesinski on 10-07-24.
 *  Copyright 2010 Student. All rights reserved.
 *
 */

#ifndef H_POLISH
#define H_POLISH

#include "Language.h"

class PolishFactory : public LanguageFactory
{
	friend class AbstractLanguageFactory;
public:
	virtual Language* createLanguage();
	
protected:
	PolishFactory();
};

class Polish : public Language
{
	friend class PolishFactory;
public:
	virtual void outputMessage(std::ostream& out);
	
protected:
	Polish();
};

#endif