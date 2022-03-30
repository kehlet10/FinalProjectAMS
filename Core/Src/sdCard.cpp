/*
 * sdCard.cpp
 *
 *  Created on: Mar 30, 2022
 *      Author: Danie
 */

#include <sdCard.h>

namespace FinalProject {

sdCard::sdCard() {
	// TODO Auto-generated constructor stub

}


	void sdCard::addTag()
	{
		//Tilføj til knownTags vector
	}
	void sdCard::addName()
	{
		//tilføj til names vector
	}

	std::vector<string> sdCard::getName()
	{
		return m_names;
	}
	std::vector<string> sdCard::getTag()
	{
		return knownTags;
	}

} /* namespace FinalProject */
