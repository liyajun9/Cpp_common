#include <iconv.h>
#include <cstring>
#include "charsetConvert.h"


namespace cpp_common
{
    int CharsetConvert(const char *pSrc, char *pDst, int nSrcLen, int nDstLen, const char *pSrcCharset, const char *pDstCharset)
    {
        if (pSrc == NULL || pDst == NULL || nSrcLen <= 0 || nDstLen <= 0 || pSrcCharset == NULL || pDstCharset == NULL)
        {
            return -2;
        }

        char *pSrcTmp = const_cast<char *>(pSrc);
        char *pDstTmp = pDst;
        size_t insize = (size_t)nSrcLen;
        size_t outsize = (size_t)nDstLen;

        iconv_t cd = iconv_open(pDstCharset, pSrcCharset);
        if (cd == iconv_t(-1))
        {
            return -1;
        }
        size_t ret = iconv(cd, (char **)&pSrcTmp, &insize, &pDstTmp, &outsize);
        iconv_close(cd);

        if (ret == size_t(-1))
        {
            if (errno == EILSEQ || errno == EINVAL)
                return -2;
            else
                return -1;
        }

        return nDstLen - (int)outsize;
    }

    int gbk2utf8(const std::string &strGbk, std::string &strUtf8)
    {
        int size = int(strGbk.size() * 4);  // 4 is enough
        char *pUtf8 = new char[size];
        memset(pUtf8, 0, size);
        int ret = CharsetConvert(strGbk.c_str(), pUtf8, (int)strGbk.size(), size, "GBK", "UTF-8");
        if (ret < 0)
        {
            delete []pUtf8;
            return ret;
        }
        strUtf8.assign(pUtf8, ret);
        delete []pUtf8;
        return ret;
    }

    int utf82gbk(const std::string &strUtf8, std::string &strGbk)
    {
        int size = int(strUtf8.size() * 3);  // 3 is enough
        char *pGbk = new char[size];
        memset(pGbk, 0, size);
        int ret = CharsetConvert(strUtf8.c_str(), pGbk, (int)strUtf8.size(), size, "UTF-8", "GBK");
        if (ret < 0)
        {
            delete []pGbk;
            return -1;
        }
        strGbk.assign(pGbk, ret);
        delete []pGbk;
        return ret;
    }
}
