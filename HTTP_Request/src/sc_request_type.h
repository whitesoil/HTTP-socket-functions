#ifndef _SC_REQUEST_TYPE_H

#define SC_MAXLINE 8192
#define SC_MAX_HEADER_SIZE 30
#define SC_MAX_METHOD_SIZE 10
#define SC_MAX_URL_SIZE 150
#define SC_MAX_VERSION_SIZE 9

#include "sc_header_table.h"

typedef struct sc_http_request_t {
    char                Method[SC_MAX_METHOD_SIZE];
    char                URL[SC_MAX_URL_SIZE];
    char                Version[SC_MAX_VERSION_SIZE];
    sc_header_table_t*  header;
    char                Body[SC_MAXLINE];
} sc_http_request_t;

#endif