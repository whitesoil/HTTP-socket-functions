#ifndef _SC_REQUEST_CHECK_H

#include <string.h>
#include <stdlib.h>

#include "sc_content_type.h"
#include "sc_http_method.h"
#include "sc_http_version.h"
#include "sc_request_type.h"

int 
sc_method_check (char *method)
{
    for(int i = 0; i < SC_HTTP_METHOD_NUM; i++)
        if(strcmp(sc_http_method_table[i], method))
            return 1;
    return 0;
}

int
sc_version_check (char* version)
{
    for(int i = 0; i < SC_HTTP_VERSION_NUM; i++)
        if(strcmp(sc_http_version_table[i], version))
            return 1;
    return 0;
}

int
sc_content_type_check (char *type)
{
    for(int i = 0; i < SC_CONTENT_TYPE_NUM; i++)
        if(strstr(type, sc_content_type_table[i].mime_type))
            return 1;
    return 0;
}

#endif