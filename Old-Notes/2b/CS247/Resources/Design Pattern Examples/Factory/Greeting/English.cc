/*
 *  English.cc
 *  Assignment 3
 *
 *  Created by Adam Lesinski on 10-07-24.
 *  Copyright 2010 Student. All rights reserved.
 *
 */

#include "English.h"

English::English()
{}

void English::outputMessage(std::ostream& out)
{
	out << "Welcome!";
}

EnglishFactory::EnglishFactory()
{}

Language* EnglishFactory::createLanguage()
{
	return new English();
}