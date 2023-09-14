#include <unistd.h>
#include <cerrno>
#include "rdwrn.h"                      /* Declares readn() and writen() */

namespace cpp_common {

/* Read 'n' bytes from 'fd' into 'buf', restarting after partial
   reads or interruptions by a signal handlers */

    ssize_t
    readn(int fd, void *buffer, size_t n, time_t timeout)
    {
        ssize_t numRead;                    /* # of bytes fetched by last read() */
        size_t totRead;                     /* Total # of bytes read so far */
        char *buf;

        buf = (char *)buffer;                       /* No pointer arithmetic on "void *" */
        for (totRead = 0; totRead < n; ) {
            numRead = read(fd, buf, n - totRead);

            if (numRead == 0)               /* EOF */
                return (ssize_t)totRead;             /* May be 0 if this is first read() */
            if (numRead == -1) {
                if (errno == EINTR)
                    continue;               /* Interrupted --> restart read() */
                else if (errno == EAGAIN)
                {
                    fd_set rdd;
                    FD_ZERO(&rdd);
                    FD_SET(fd, &rdd);
                    struct timeval tv = {0};
                    tv.tv_sec = timeout;
                    int ret = select(fd + 1, &rdd, NULL, NULL, &tv);
                    if (ret == 0)
                        return -1;      /* timeout */
                    else if (ret == -1) {
                        if (errno == EINTR)
                            continue;
                        else
                            return -1; /* error */
                    }
                    else
                        continue;
                }
                else
                    return -1;              /* Some other error */
            }
            totRead += numRead;
            buf += numRead;
        }
        return (ssize_t)totRead;                     /* Must be 'n' bytes if we get here */
    }

    /*pread only used with block IO*/
    ssize_t
    preadn(int fd, void *buffer, size_t n, off_t offset)
    {
        ssize_t numRead;                    /* # of bytes fetched by last read() */
        size_t totRead;                     /* Total # of bytes read so far */
        char *buf;

        buf = (char *) buffer;                       /* No pointer arithmetic on "void *" */
        for (totRead = 0; totRead < n; ) {
            numRead = pread(fd, buf, n - totRead, (off_t)(offset + totRead));

            if (numRead == 0)               /* EOF */
                return (ssize_t)totRead;             /* May be 0 if this is first read() */
            if (numRead == -1) {
                if (errno == EINTR)
                    continue;               /* Interrupted --> restart read() */
                else
                    return -1;              /* Some other error */
            }
            totRead += numRead;
            buf += numRead;
        }
        return (ssize_t)totRead;                     /* Must be 'n' bytes if we get here */
    }



/* Write 'n' bytes to 'fd' from 'buf', restarting after partial
   write or interruptions by a signal handlers */

    ssize_t
    writen(int fd, const void *buffer, size_t n, time_t timeout)
    {
        ssize_t numWritten;                 /* # of bytes written by last write() */
        size_t totWritten;                  /* Total # of bytes written so far */
        const char *buf;

        buf = (char *) buffer;                       /* No pointer arithmetic on "void *" */
        for (totWritten = 0; totWritten < n; ) {
            numWritten = write(fd, buf, n - totWritten);
            /* The "write() returns 0" case should never happen, but the
               following ensures that we don't loop forever if it does */
            if (numWritten <= 0) {
                if (numWritten == -1) {
                    if (errno == EINTR)
                        continue;               /* Interrupted --> restart write() */
                    else if (errno == EAGAIN) {
                        if (timeout > 0) {      /* Nonblock IO --> wait for writable or return -1 according to timeout param*/
                            fd_set wrd;
                            FD_ZERO(&wrd);
                            FD_SET(fd, &wrd);

                            struct timeval tv = {0};
                            tv.tv_sec = timeout;
                            int ret = select(fd + 1, NULL, &wrd, NULL, &tv);
                            if (ret == 0)
                                return -1;      /* timeout */
                            else if (ret == -1) {
                                if (errno == EINTR)
                                    continue;
                                else
                                    return -1; /* error */
                            }
                            else {
                                continue;
                            }
                        }
                        else
                            return -1;  /* timeout <= 0, return immediately */
                    }
                    else
                        return -1;     /* Some other error */
                }
                else
                    return -1;        /* numWritten == 0 */
            }
            totWritten += numWritten;
            buf += numWritten;
        }
        return (ssize_t)totWritten;                  /* Must be 'n' bytes if we get here */
    }

    /*pwrite only used with block IO*/
    ssize_t
    pwriten(int fd, const void *buffer, size_t n, off_t offset)
    {
        ssize_t numWritten;                 /* # of bytes written by last write() */
        size_t totWritten;                  /* Total # of bytes written so far */
        const char *buf;

        buf = (char *) buffer;                       /* No pointer arithmetic on "void *" */
        for (totWritten = 0; totWritten < n; ) {
            numWritten = pwrite(fd, buf, n - totWritten, (off_t)(offset + totWritten));

            /* The "write() returns 0" case should never happen, but the
               following ensures that we don't loop forever if it does */

            if (numWritten <= 0) {
                if (numWritten == -1 && errno == EINTR)
                    continue;               /* Interrupted --> restart write() */
                else
                    return -1;              /* Some other error */
            }
            totWritten += numWritten;
            buf += numWritten;
        }
        return (ssize_t)totWritten;                  /* Must be 'n' bytes if we get here */
    }

}
