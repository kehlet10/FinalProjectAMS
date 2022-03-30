

#include "RFID.h"




void RFID::tagScanned()
{
	//Input fra RFID reader. Check hvorvidt den er i vectoren.
	//Hvis ikke så kald UnkownTag

}

void RFID::unknownTag()
{
	//Tag findes ikke. Tilføj dette til vectoren
}

void RFID::loadTags(std::vector<string> tags)
{
	//Load known tags fra sdkortet

}
