#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "headers/baseX.h"

int main(int argc, const char* argv[]) {
    if(argc < 2) {
        perror("ERR: required input string");
        return -1;
    }
    for(int i = 1; i < argc; i++) {
        const char* orgstr = argv[i];
        printf("Original String: %s\n", orgstr);
        uchar_t* encstr = base64_encode(orgstr);
        if(encstr) {
            printf("Encoded string: %s\n", encstr);
            char* decstr = base64_decode(encstr);
            if(decstr) {
                printf("Decoded string: %s\n", decstr);
                free(decstr);
            } else {    
                perror("ERR: base64_decode failed");
            }
            free(encstr);
        } else {
            perror("ERR: base64_encode failed");
        }
    }
    return 0;
}