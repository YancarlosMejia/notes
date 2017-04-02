/*
 *  French.cc
 *  Assignment 3
 *
 *  Created by Adam Lesinski on 10-07-24.
 *  Copyright 2010 Student. All rights reserved.
 *
 */

#include "French.h"

French::French()
{}

void French::outputMessage(std::ostream& out)
{
	out << "Bienvenue!";
}

FrenchFactory::FrenchFactory()
{}

Language* FrenchFactory::createLanguage()
{
	return new French();
}