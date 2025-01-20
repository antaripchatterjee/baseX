#ifndef __UTILS_H__
#define __UTILS_H__

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

static inline uint8_t get_index_from_seq(uchar_t uch, const uchar_t* basex_seq, uint8_t seq_len) {
    uint8_t i = 0;
    if(uch == '=') return seq_len;
    while(i < seq_len && uch != basex_seq[i++]);
    if(i == seq_len+1) return UINT8_MAX;
    return i-1;
}


#ifdef __cplusplus
}
#endif // __cplusplus

#endif // __UTILS_H__