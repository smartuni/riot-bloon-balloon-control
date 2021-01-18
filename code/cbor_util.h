#include "stdint.h"
#include "cbor.h"

void addUInt64ToMap(char* key, uint64_t value, CborEncoder* mapEncoder);
void addFloatToMap(char* key, float value, CborEncoder* mapEncoder);
void addStringToMap(char* key, char* value, CborEncoder* mapEncoder);
void printHexFromBuffer(uint8_t* buffer, CborEncoder* encoder);