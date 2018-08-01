#ifndef _SC_REQUEST_PARSER_H

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "sc_request_check.h"
#include "sc_url_parser.h"

void
sc_header_body_seperate (char* req_stream, char* header, char* body)
{
    char sp_header[SC_MAXLINE], sp_body[SC_MAXLINE];
    int bodyLength, hdrLength;
    char* bp = strstr(req_stream, "\r\n\r\n") + 4;

    bodyLength = strlen(bp);    
    
    for(int j = 0; j < bodyLength; j++)
        body[j] = bp[j];
    body[bodyLength] = '\0';

    hdrLength = strlen(req_stream) - bodyLength;

    for(int i = 0; i < hdrLength; i++)
        sp_header[i] = req_stream[i];
    sp_header[hdrLength] = '\0';
    strcpy(header, sp_header);
}

int
sc_content_length_get (char *contentLength)
{
    int length = atoi(contentLength);
    return length;
}

int
sc_status_line_seperate (char* line, char* method, char* url, char* version)
{
    if(sscanf(line, "%s %s %s", method, url, version) == EOF) 
        return 400;
    if(!sc_method_check(method))
        return 405;
    if(!sc_version_check(version)) 
        return 505;

    return 1;
}

int
sc_request_reader (char* req_stream, sc_http_request_t* req, sc_url_t* _url)
{ 
    char method[SC_MAXLINE], url[SC_MAXLINE], version[SC_MAXLINE];
    char header[SC_MAXLINE], body[SC_MAXLINE];

    sc_header_body_seperate(req_stream, header, body);

    char* line = strtok(header, "\r\n");
    if(!sc_status_line_seperate(line, method, url, version)) 
        return 400;

    strcpy(req->Method, method);
    strcpy(req->URL, url);
    strcpy(req->Version,version);
    sc_url_parse(req->URL, _url);

    line = strtok(NULL, "\r\n");
    while(line != NULL)
    {
        char key[SC_MAX_HEADER_SIZE], value[SC_MAX_HEADER_SIZE];
        sc_line_seperate(line, key, value);
        sc_header_table_append(&req->header, sc_header_create(key, value));

        line = strtok(NULL, "\r\n");
    }
    strcpy(req->Body, body);
    return 200;
}

#endif