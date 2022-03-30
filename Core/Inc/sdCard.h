/*
 * sdCard.h
 *
 *  Created on: Mar 30, 2022
 *      Author: Danie
 */

#ifndef INC_SDCARD_H_
#define INC_SDCARD_H_

#include <vector>
#include <string>

namespace FinalProject {

class sdCard {
public:
	sdCard();

	void addTag();
	void addName();

	std::vector<string> getName();
	std::vector<string> getTag();
private:
	std::vector<string> m_names;
	std::vector<string> m_knownTags;

};

} /* namespace FinalProject */

#endif /* INC_SDCARD_H_ */
