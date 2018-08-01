# HTTP Response
## http_response_constructor.h
### Struct & enum
- HTTP Response Header
```
typedef struct sc_http_response_t {
    char * http_version;
    char * status_code;
    char * status_msg;
    char * date;
    char * server;
    char * last_modified;
    char * etag;
    char * accept_ranges;
    char * content_length;
    char * keep_alive;
    char * connection; 
    char * content_type;
}sc_http_response_t;
```
- HTTP Status Code
```
enum http_status_code {
	HTTP_STATUS_CONTINUE			= 100,
	HTTP_STATUS_SWITCHING_PROTOCOLS		= 101,
	HTTP_STATUS_OK				= 200,
	HTTP_STATUS_CREATED			= 201,
	HTTP_STATUS_ACCEPTED			= 202,
	HTTP_STATUS_NON_AUTHORITATIVE		= 203,
	HTTP_STATUS_NO_CONTENT			= 204,
	HTTP_STATUS_RESET_CONTENT		= 205,
	HTTP_STATUS_PARTIAL_CONTENT		= 206,
	HTTP_STATUS_MULTIPLE_CHOICES		= 300,
	HTTP_STATUS_MOVED_PERMANENTLY		= 301,
	HTTP_STATUS_FOUND			= 302,
	HTTP_STATUS_SEE_OTHER			= 303,
	HTTP_STATUS_NOT_MODIFIED		= 304,
	HTTP_STATUS_USE_PROXY			= 305,
	HTTP_STATUS_TEMPORARY_REDIRECT		= 307,
	HTTP_STATUS_BAD_REQUEST			= 400,
	HTTP_STATUS_UNAUTHORIZED		= 401,
	HTTP_STATUS_PAYMENT_REQUIRED		= 402,
	HTTP_STATUS_FORBIDDEN			= 403,
	HTTP_STATUS_NOT_FOUND			= 404,
	HTTP_STATUS_METHOD_NOT_ALLOWED		= 405,
	HTTP_STATUS_NOT_ACCEPTABLE		= 406,
	HTTP_STATUS_PROXY_AUTH_REQUIRED		= 407,
	HTTP_STATUS_REQUEST_TIMEOUT		= 408,
	HTTP_STATUS_CONFLICT			= 409,
	HTTP_STATUS_GONE			= 410,
	HTTP_STATUS_LENGTH_REQUIRED		= 411,
	HTTP_STATUS_PRECONDITION_FAILED		= 412,
	HTTP_STATUS_REQUEST_ENTITY_TOO_LARGE	= 413,
	HTTP_STATUS_REQUEST_URI_TOO_LARGE	= 414,
	HTTP_STATUS_UNSUPPORTED_MEDIA_TYPE	= 415,
	HTTP_STATUS_REQUEST_RANGE_INVALID	= 416,
	HTTP_STATUS_EXPECTATION_FAILED		= 417,
	HTTP_STATUS_INTERNAL_ERROR		= 500,
	HTTP_STATUS_NOT_IMPLEMENTED		= 501,
	HTTP_STATUS_BAD_GATEWAY			= 502,
	HTTP_STATUS_SERVICE_UNAVAILABLE		= 503,
	HTTP_STATUS_GATEWAY_TIMEOUT		= 504,
	HTTP_STATUS_BAD_VERSION			= 505
};
```


### Function
- Init HTTP Response struct
```
sc_http_response_t res = {};
```
- Set version, Default = 1.1
```
void sc_res_version_set(sc_http_response_t * res, float http_version);
```
- Set status, Default = 200 OK
```
void sc_res_status_code_set(sc_http_response_t * res, int status_code);
```
- Set date, Default is now time
```
void sc_res_date_set(sc_http_response_t * res);
```
- Set server, Default = Linux Web Server
```
void sc_res_server_set(sc_http_response_t * res, char * server);
```
- Set last modified, Default is same with Date
```
void sc_res_last_modified_set(sc_http_response_t * res, char * last_modified);
```
- Set etag, Default = ""
```
void sc_res_etag_set(sc_http_response_t * res, char * etag);
```
- Set accept ranges, Default = bytes
```
void sc_res_accept_ranges_set(sc_http_response_t * res, char * type);
```
- Set content length, Default = 1024
```
void sc_res_content_length_set(sc_http_response_t * res, int content_length);
```
- Set keep alive, Default = timeout = 10, max = 100
```
void sc_res_keep_alive_set(sc_http_response_t * res, int timeout, int max);
```
- Set connection, Default = Keep-Alive
```
void sc_res_connection_set(sc_http_response_t * res, char * connection);
```
- Set content type, Default = text/plain
```
void sc_res_content_type_set(sc_http_response_t * res, char * sc_content_type_get);
```
- Send HTTP Response
```
void sc_response_send(sc_http_response_t* res, char * filename, int fd);
```
- Construct HTTP Response
```
void sc_res_construct(sc_http_response_t * res,char * http_response_header);
```
- Get Http status message by code
```
char *  sc_res_status_message_get(int status);
```
- Get content type by filename
```
char * sc_content_type_get(char * filename);
```
- Get dirctory tree
```
int sc_dirctory_desc(char * path, FILE * fd);
```