#ifndef INC_SDCARD_H_
#define INC_SDCARD_H_

#include <vector>
#include <string>

namespace FinalProject {
	class RFID {

	public:
		void tagScanned();
		void unknownTag();
		void loadTags(std::vector<string> tags);
	private:
		std::vector<string> knownTags;

	};
}

