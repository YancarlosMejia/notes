/*
 *  French.h
 *  Assignment 3
 *
 *  Created by Adam Lesinski on 10-07-24.
 *  Copyright 2010 Student. All rights reserved.
 *
 */

#ifndef H_FRENCH
#define H_FRENCH

#include "Language.h"

class FrenchFactory : public LanguageFactory
{
	friend class AbstractLanguageFactory;
public:
	virtual Language* createLanguage();
	
protected:
	FrenchFactory();
};
	
class French : public Language
{
	friend class FrenchFactory;
public:
	virtual void outputMessage(std::ostream& out);
	
protected:
	French();
};

#endif