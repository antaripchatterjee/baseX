#ifndef __BASE32_H__
#define __BASE32_H__

#ifdef MAKEFILECOMPILE
#include "_types.h"
#else
#include "../headers/_types.h"
#endif // MAKEFILECOMPILING


#define BASE32_SEQ "ABCDEFGHIJKLMNOPQRSTUVWXYZ234567"

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

uchar_t* base32_encode(const char* orgstr);
char* base32_decode(const uchar_t* encstr);


#ifdef __cplusplus
}
#endif // __cplusplus

#endif // __BASE32_H__