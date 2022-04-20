/*
 * breathAnalyser.h
 *
 *  Created on: Mar 30, 2022
 *      Author: Danie
 */

#ifndef INC_BREATHANALYSER_H_
#define INC_BREATHANALYSER_H_


	breathAnalyser();
	float getPromille();
	void measurePromille();

	float sensorOutput;
	float valueRS;
	float valueR0;
	float ratio;
	float promille;
	int R2;

};
#endif /* INC_BREATHANALYSER_H_ */
