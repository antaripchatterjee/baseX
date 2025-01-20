#ifndef __BASEX_H__
#define __BASEX_H__

#ifdef MAKEFILECOMPILE
#include "base64.h"
#include "base32.h"
#else
#include "../headers/base64.h"
#include "../headers/base32.h"
#endif // MAKEFILECOMPILING

#endif // __BASEX_H__