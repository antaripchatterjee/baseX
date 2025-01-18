#ifndef __BASE64_H__
#define __BASE64_H__

#ifdef MAKEFILECOMPILE
#include "_types.h"
#else
#include "../headers/_types.h"
#endif // MAKEFILECOMPILING


#define BASE64_SEQ "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

uchar_t* base64_encode(const char* orgstr);
char* base64_decode(const uchar_t* encstr);


#ifdef __cplusplus
}
#endif // __cplusplus

#endif // __BASE64_H__