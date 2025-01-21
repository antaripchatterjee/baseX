#include <string.h>
#include <stdlib.h>
#include <stdint.h>

#ifdef MAKEFILECOMPILE
#include "base32.h"
#include "_utils.h"
#else
#include "../headers/base32.h"
#include "../headers/_utils.h"
#endif // MAKEFILECOMPILING

uchar_t* base32_encode(const char* orgstr) {
    uchar_t* encstr = NULL;
    size_t arglen, reslen, k = 0;
    const uchar_t base32_seq[33] = BASE32_SEQ;
    if(orgstr && (arglen = strlen(orgstr))) {
        reslen = ((arglen + 4) / 5) * 8;
        size_t alloc_size = sizeof(uchar_t) * (reslen + 1);
        encstr = (uchar_t*) malloc(alloc_size);
        uint8_t _t1[8] = { 0 };
        uchar_t _t2[6] = { 0 };
        if(encstr) {
            memset(encstr, '=', alloc_size);
            encstr[alloc_size-1] = '\0';
            for(size_t i = 0; i < (arglen+4)/5; i++) {
                memset(_t2, 0, sizeof(_t2));
                uint8_t l = ((i+1) * 5 <= arglen ? 5 : (arglen-i*5));
                memmove(_t2, orgstr+(i*5*sizeof(uchar_t)), sizeof(uchar_t) * l);
                _t1[0] = _t2[0] >> 3;
                _t1[1] = ((_t2[0] & 0b00000111) << 2) | (_t2[1] >> 6);
                _t1[2] = (_t2[1] & 0b00111111) >> 1;
                _t1[3] = ((_t2[1] & 0b00000001) << 4) | (_t2[2] >> 4);
                _t1[4] = ((_t2[2] & 0b00001111) << 1) | (_t2[3] >> 7);
                _t1[5] = (_t2[3] & 0b01111100) >> 2;
                _t1[6] = ((_t2[3] & 0b00000011) << 3) | (_t2[4] >> 5);
                _t1[7] = _t2[4] & 0b00011111;
                for(uint8_t j = 0; j <= (l == 5 ? 7 : ((l*8)/5)); j++) {
                    encstr[k++] = base32_seq[_t1[j]];
                }
            }

        }
    }
    return encstr;
}


char* base32_decode(const uchar_t* encstr) {
    char* decstr = NULL;
    size_t arglen, reslen, k = 0;
    const uchar_t base32_seq[33] = BASE32_SEQ;
    uint8_t seq_len = (uint8_t) strlen((const char*) base32_seq);
    if(encstr && (arglen = strlen((const char*)encstr))) {
        reslen = (arglen * 5) / 8;
        size_t alloc_size = sizeof(char) * (reslen + 1);
        decstr = (char*) malloc(alloc_size);
        if(decstr) {
            memset(decstr, 0, alloc_size);
            uint8_t _t1[8];
            uchar_t _t2[8];
            char _t3[6];
            uint8_t l = 5;
            for(size_t i = 0; i < arglen/8; i++) {
                if(l != 5) {
                    free(decstr);
                    return NULL;
                }
                memset(_t3, 0, sizeof(_t3));
                memset(_t2, 0, sizeof(_t2));
                memmove(_t2, encstr + (i*sizeof(_t2)), sizeof(_t2));
                uint8_t c = 0; // base32 valid char count
                for(uint8_t j = 0; j < sizeof(_t2); j++) {
                    _t1[j] = get_index_from_seq(_t2[j], base32_seq, seq_len);
                    if((_t1[j] == seq_len && j < 2) || _t1[j] == UINT8_MAX) {
                        free(decstr);
                        return NULL;
                    } else if(_t1[j] == seq_len) {
                        _t1[j] = 0;
                    } else {
                        c++;
                    }
                }
                if(c < 2 || ((c * 5) % 8) >= 5) {
                    free(decstr);
                    return NULL;
                } else if(c < 8) {
                    l = (c * 5) / 8;
                }
                _t3[0] = (_t1[0] << 3) | (_t1[1] >> 2);
                _t3[1] = (_t1[1] << 6) | (_t1[2] << 1) | (_t1[3] >> 4);
                _t3[2] = (_t1[3] << 4) | (_t1[4] >> 1);
                _t3[3] = (_t1[4] << 7) | (_t1[5] << 2) | (_t1[6] >> 3);
                _t3[4] = (_t1[6] << 5) | _t1[7];
                for(uint8_t j = 0; j < l; j++) {
                    decstr[k++] = _t3[j];
                }
            }
        }
    }
    return decstr;
}