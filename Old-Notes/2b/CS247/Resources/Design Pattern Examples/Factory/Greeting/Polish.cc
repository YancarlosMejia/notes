/*
 *  Polish.cc
 *  Assignment 3
 *
 *  Created by Adam Lesinski on 10-07-24.
 *  Copyright 2010 Student. All rights reserved.
 *
 */

#include "Polish.h"

Polish::Polish()
{}

void Polish::outputMessage(std::ostream& out)
{
	out << "Witamy!";
}

PolishFactory::PolishFactory()
{}

Language* PolishFactory::createLanguage()
{
	return new Polish();
}