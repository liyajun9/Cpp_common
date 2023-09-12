#include <string>
#include <stdio.h>
#include "charsetConvert.h"

int main(int argc, char **argv)
{
    std::string strGbk = "жпнд";
    std::string strUtf8;
    int ret = cpp_common::gbk2utf8(strGbk, strUtf8);
    if (ret < 0)
    {
        printf("gbk2utf8 failed\n");
        return -1;
    }
    printf("gbk2utf8: %s\n", strUtf8.c_str());

    std::string strGbk2;
    ret = cpp_common::utf82gbk(strUtf8, strGbk2);
    if (ret < 0)
    {
        printf("utf82gbk failed\n");
        return -1;
    }
    printf("utf82gbk: %s\n", strGbk2.c_str());

    return 0;
}
