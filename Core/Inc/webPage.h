/*
 * RFID.h
 *
 *  Created on: Mar 30, 2022
 *      Author: Danie
 */

#ifndef INC_RFID_H_
#define INC_RFID_H_
#include <vector>
#include <string>

namespace FinalProject {

class webPage {
public:
	webPage();

private:
	std::vector<string> m_knownTags;
	std::vector<string> m_names;
	std::vector<int> m_promille;

	void loadData();

	void uploadData();

};


} /* namespace FinalProject */

#endif /* INC_RFID_H_ */
