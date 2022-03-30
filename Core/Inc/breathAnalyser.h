/*
 * breathAnalyser.h
 *
 *  Created on: Mar 30, 2022
 *      Author: Danie
 */

#ifndef INC_BREATHANALYSER_H_
#define INC_BREATHANALYSER_H_

namespace FinalProject {

class breathAnalyser {
public:
	breathAnalyser();
	int getPromille();
	void measurePromille();
private:
	int promille;

};

} /* namespace FinalProject */

#endif /* INC_BREATHANALYSER_H_ */
