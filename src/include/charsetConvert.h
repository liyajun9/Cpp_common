#ifndef CPP_COMMON_CHARSETCONVERT_H
#define CPP_COMMON_CHARSETCONVERT_H

#include <string>

namespace cpp_common
{
    /*
     * return:
     * success: the number of bytes of result string
     * error:   -1: internal error, -2: invalid parameter
    */
    int CharsetConvert(const char *pSrc, char *pDst, int nSrcLen, int nDstLen, const char *pSrcCharset, const char *pDstCharset);

    /*
     * return:
     * success: the number of bytes of result string
     * error:   -1: internal error, -2: invalid parameter
    */
    int gbk2utf8(const std::string &strGbk, std::string &strUtf8);

    /*
     * return:
     * success: the number of bytes of result string
     * error:   -1: internal error, -2: invalid parameter
    */
    int utf82gbk(const std::string &strUtf8, std::string &strGbk);
}

#endif //CPP_COMMON_CHARSETCONVERT_H
