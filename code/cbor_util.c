#include "cbor_util.h"

void addUInt64ToMap(char* key, uint64_t value, CborEncoder* mapEncoder) {
    cbor_encode_text_stringz(mapEncoder, key);
    cbor_encode_uint(mapEncoder, value);
}

void addFloatToMap(char* key, float value, CborEncoder* mapEncoder) {
    cbor_encode_text_stringz(mapEncoder, key);
    cbor_encode_float(mapEncoder, value);
}

void addStringToMap(char* key, char* value, CborEncoder* mapEncoder) {
    cbor_encode_text_stringz(mapEncoder, key);
    cbor_encode_text_stringz(mapEncoder, value);
}

void printHexFromBuffer(uint8_t* buffer, CborEncoder* encoder) {
    size_t bufsize = cbor_encoder_get_buffer_size(encoder, buffer);
    printf("printHexFromBuffer Bufsize: %d\n", bufsize);
    for(uint8_t i=0; i<=bufsize; i++){
        printf("%02x ", buffer[i]);
    }
    printf("\n");
}