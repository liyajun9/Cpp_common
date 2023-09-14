#ifndef COMMON_RDWRN_H
#define COMMON_RDWRN_H

#include <sys/types.h>

namespace cpp_common {

    ssize_t readn(int fd, void *buf, size_t len);

    ssize_t preadn(int fd, void *buffer, size_t n, off_t offset);

    ssize_t writen(int fd, const void *buffer, size_t n, time_t timeout=0);

    ssize_t pwriten(int fd, const void *buffer, size_t n, off_t offset);
}

#endif //COMMON_RDWRN_H
