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
        reslen = ((arglen + 2) / 3) * 4;
        size_t alloc_size = sizeof(uchar_t) * (reslen + 1);
        encstr = (uchar_t*) malloc(alloc_size);
        uint8_t _t1[4] = { 0 };
        uchar_t _t2[4] = { 0 };
        if(encstr) {
            memset(encstr, '=', alloc_size);
            encstr[alloc_size-1] = '\0';
            for(size_t i = 0; i < (arglen+2)/3; i++) {
                memset(_t2, 0, sizeof(_t2));
                uint8_t l = ((i+1) * 3 <= arglen ? 3 : (arglen-i*3));
                memmove(_t2, orgstr+(i*3*sizeof(uchar_t)), sizeof(uchar_t) * l);
                _t1[0] = _t2[0] >> 2;
                _t1[1] = ((_t2[0] & 0b00000011) << 4) | (_t2[1] >> 4);
                _t1[2] = ((_t2[1] & 0b00001111) << 2) | (_t2[2] >> 6);
                _t1[3] = _t2[2] & 0b00111111;
                for(uint8_t j = 0; j < l+1; j++) {
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
    if(encstr && (arglen = strlen((const char*)encstr))) {
        reslen = (arglen * 3) / 4;
        if(encstr[arglen-1] == '=') {
            reslen--;
            if(encstr[arglen-2] == '=') reslen--;
        }
        size_t alloc_size = sizeof(char) * (reslen + 1);
        decstr = (char*) malloc(alloc_size);
        if(decstr) {
            memset(decstr, 0, alloc_size);
            // printf("%zu\n", reslen);
            uint8_t _t1[4];
            uchar_t _t2[4];
            char _t3[4];
            uint8_t l = 3;
            for(size_t i = 0; i < arglen/4; i++) {
                if(l != 3) {
                    free(decstr);
                    return NULL;
                }
                memset(_t3, 0, sizeof(_t3));
                memset(_t2, 0, sizeof(_t2));
                memmove(_t2, encstr + (i*sizeof(_t2)), sizeof(_t2));
                for(uint8_t j = 0; j < 4; j++) {
                    _t1[j] = get_index_from_seq(_t2[j], base32_seq, (uint8_t) strlen((const char*) base32_seq));
                    if((_t1[j] == 32 && j < 2) || _t1[j] == UINT8_MAX) {
                        free(decstr);
                        return NULL;
                    } else if(_t1[j] == 32) {
                        l--;
                        _t1[j] = 0;
                    }
                }
                _t3[0] = (_t1[0] << 2) | (_t1[1] >> 4);
                _t3[1] = (_t1[1] << 4) | (_t1[2] >> 2);
                _t3[2] = (_t1[2] << 6) | _t1[3];
                for(uint8_t j = 0; j < l; j++) {
                    decstr[k++] = _t3[j];
                }
            }
        }
    }
    return decstr;
}