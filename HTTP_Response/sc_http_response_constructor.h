#ifndef __H_HTTP_H
#define __H_HTTP_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>

#define BUF_SIZE 1024

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
    char * sc_content_type_get;
}sc_http_response_t;

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

void sc_res_version_set(sc_http_response_t *, float);
void sc_res_status_code_set(sc_http_response_t *, int);
void sc_res_date_set(sc_http_response_t *);
void sc_res_server_set(sc_http_response_t *, char *);
void sc_res_last_modified_set(sc_http_response_t *, char *);
void sc_res_etag_set(sc_http_response_t *, char *);
void sc_res_accept_ranges_set(sc_http_response_t *, char *);
void sc_res_content_length_set(sc_http_response_t *, int);
void sc_res_keep_alive_set(sc_http_response_t *, int, int);
void sc_res_connection_set(sc_http_response_t *, char *);
void sc_res_content_type_set(sc_http_response_t *, char *);

void sc_res_construct(sc_http_response_t *,char *);
char * sc_res_status_message_get(int);
char * sc_content_type_get(char *);
void sc_response_send(sc_http_response_t *, char *, int);
int sc_dirctory_desc(char * path, FILE * fd);

void sc_res_version_set(sc_http_response_t * res, float http_version){
    res->http_version = (char *)malloc(sizeof(char)*8);
    snprintf(res->http_version,8,"HTTP/%.1f",http_version);
}

void sc_res_status_code_set(sc_http_response_t * res, int status_code){
    res->status_code = (char *)malloc(sizeof(char)*4);
    snprintf(res->status_code,4,"%d",status_code);
    res->status_msg = (char *)malloc(sizeof(char)*30);
    snprintf(res->status_msg,30,"%s",sc_res_status_message_get(status_code));
}

void sc_res_date_set(sc_http_response_t * res){
    char date[40];
    time_t now = time(0);
    struct tm tm = *gmtime(&now);
    strftime(date, sizeof date, "Date: %a, %d %b %Y %H:%M:%S %Z", &tm);
    res->date = (char *)malloc(sizeof(char)*40);
    snprintf(res->date,40,"%s", date);
}

void sc_res_server_set(sc_http_response_t * res, char * server){
    res->server = (char *)malloc(sizeof(char)*30);
    snprintf(res->server,30,"Server: %s",server);
}

void sc_res_last_modified_set(sc_http_response_t * res, char * last_modified){
    res->last_modified = (char *)malloc(sizeof(char)*40);
    snprintf(res->last_modified,40,"Last Modified: %s", last_modified);
}

void sc_res_etag_set(sc_http_response_t * res, char * etag){
    res->etag = (char *)malloc(sizeof(char)*40);
    snprintf(res->etag,40,"ETag: \"%s\"", etag);
}

void sc_res_accept_ranges_set(sc_http_response_t * res, char * type){
    res->accept_ranges = (char*)malloc(sizeof(char)*25);
    snprintf(res->accept_ranges,25,"Accept-Ranges: %s",type);
}

void sc_res_content_length_set(sc_http_response_t * res, int content_length){
    res->content_length = (char *)malloc(sizeof(char)*30);
    snprintf(res->content_length,30,"Content-Length: %d", content_length);
}

void sc_res_keep_alive_set(sc_http_response_t * res, int timeout, int max){
    res->keep_alive = (char *)malloc(sizeof(char)*45);
    snprintf(res->keep_alive,45,"Keep-Alive: timeout=%d, max=%d", timeout, max);
}

void sc_res_connection_set(sc_http_response_t * res, char * connection){
    res->connection = (char *)malloc(sizeof(char)*30);
    snprintf(res->connection,30,"Connection: %s", connection);
}

void sc_res_content_type_set(sc_http_response_t * res, char * sc_content_type_get){
    res->sc_content_type_get = (char *)malloc(sizeof(char)*60);
    snprintf(res->sc_content_type_get,60,"Content-Type: %s; charset=utf-8",sc_content_type_get);
}

void sc_res_construct(sc_http_response_t * res,char * http_response_header){
    if(res->http_version ==0 || res->status_code==0 || res->status_msg ==0){
        sc_res_version_set(res,1.1);
        sc_res_status_code_set(res,HTTP_STATUS_INTERNAL_ERROR);   
    }
    snprintf(http_response_header,100,"%s %s %s\r\n",res->http_version,res->status_code,res->status_msg);

    if(res->date == 0){
        sc_res_date_set(res);
    }
    strcat(http_response_header,res->date);
    strcat(http_response_header,"\r\n");

    if(res->server == 0){
        sc_res_server_set(res,"Linux Web Server");
    }
    strcat(http_response_header,res->server);
    strcat(http_response_header,"\r\n");    

    if(res->last_modified == 0){
        char date[40];
        time_t now = time(0);
        struct tm tm = *gmtime(&now);
        strftime(date, sizeof date, "Date: %a, %d %b %Y %H:%M:%S %Z", &tm);
        sc_res_last_modified_set(res,date);
    }
    strcat(http_response_header,res->last_modified);
    strcat(http_response_header,"\r\n");

    if(res->etag != 0){
      strcat(http_response_header,res->etag);
    	strcat(http_response_header,"\r\n"); 
    }

    if(res->accept_ranges == 0){
        sc_res_accept_ranges_set(res, "bytes");
    }
    strcat(http_response_header,res->accept_ranges);
    strcat(http_response_header,"\r\n");

    if(res->content_length != 0){        
				strcat(http_response_header,res->content_length);
    		strcat(http_response_header,"\r\n");
    }
    

    // if(res->keep_alive == 0){
    //     sc_res_keep_alive_set(res,10,100);
    // }
    // strcat(http_response_header,res->keep_alive);
    // strcat(http_response_header,"\r\n");

    // if(res->connection == 0){
    //     sc_res_connection_set(res,"Keep-Alive");
    // }
    // strcat(http_response_header,res->connection);
    // strcat(http_response_header,"\r\n");

    if(res->sc_content_type_get == 0){
        sc_res_content_type_set(res,"text/html");
    }
    strcat(http_response_header,res->sc_content_type_get);
    strcat(http_response_header,"\r\n");

    strcat(http_response_header,"\r\n");
}

char *  sc_res_status_message_get(int status)
{
	switch (status) {
	case HTTP_STATUS_CONTINUE:
		return "Continue";
		break;
	case HTTP_STATUS_SWITCHING_PROTOCOLS:
		return "Switching Protocols";
		break;
	case HTTP_STATUS_OK:
		return "OK";
		break;
	case HTTP_STATUS_CREATED:
		return "Created";
		break;
	case HTTP_STATUS_ACCEPTED:
		return "Accepted";
		break;
	case HTTP_STATUS_NON_AUTHORITATIVE:
		return "Non-Authoritative Information";
		break;
	case HTTP_STATUS_NO_CONTENT:
		return "No Content";
		break;
	case HTTP_STATUS_RESET_CONTENT:
		return "Reset Content";
		break;
	case HTTP_STATUS_PARTIAL_CONTENT:
		return "Partial Content";
		break;
	case HTTP_STATUS_MULTIPLE_CHOICES:
		return "Multiple Choices";
		break;
	case HTTP_STATUS_MOVED_PERMANENTLY:
		return "Moved Permanently";
		break;
	case HTTP_STATUS_FOUND:
		return "Found";
		break;
	case HTTP_STATUS_SEE_OTHER:
		return "See Other";
		break;
	case HTTP_STATUS_NOT_MODIFIED:
		return "Not Modified";
		break;
	case HTTP_STATUS_USE_PROXY:
		return "Use Proxy";
		break;
	case HTTP_STATUS_TEMPORARY_REDIRECT:
		return "Temporary Redirect";
		break;
	case HTTP_STATUS_BAD_REQUEST:
		return "Bad Request";
		break;
	case HTTP_STATUS_UNAUTHORIZED:
		return "Unauthorized";
		break;
	case HTTP_STATUS_PAYMENT_REQUIRED:
		return "Payment Required";
		break;
	case HTTP_STATUS_FORBIDDEN:
		return "Forbidden";
		break;
	case HTTP_STATUS_NOT_FOUND:
		return "Not Found";
		break;
	case HTTP_STATUS_METHOD_NOT_ALLOWED:
		return "Method Not Allowed";
		break;
	case HTTP_STATUS_NOT_ACCEPTABLE:
		return "Not Acceptable";
		break;
	case HTTP_STATUS_PROXY_AUTH_REQUIRED:
		return "Proxy Authentication Required";
		break;
	case HTTP_STATUS_REQUEST_TIMEOUT:
		return "Request Time-out";
		break;
	case HTTP_STATUS_CONFLICT:
		return "Conflict";
		break;
	case HTTP_STATUS_GONE:
		return "Gone";
		break;
	case HTTP_STATUS_LENGTH_REQUIRED:
		return "Length Required";
		break;
	case HTTP_STATUS_PRECONDITION_FAILED:
		return "Precondition Failed";
		break;
	case HTTP_STATUS_REQUEST_ENTITY_TOO_LARGE:
		return "Request Entity Too Large";
		break;
	case HTTP_STATUS_REQUEST_URI_TOO_LARGE:
		return "Request-URI Too Large";
		break;
	case HTTP_STATUS_UNSUPPORTED_MEDIA_TYPE:
		return "Unsupported Media Type";
		break;
	case HTTP_STATUS_REQUEST_RANGE_INVALID:
		return "Requested range not satisfiable";
		break;
	case HTTP_STATUS_EXPECTATION_FAILED:
		return "Expectation Failed";
		break;
	case HTTP_STATUS_INTERNAL_ERROR:
		return "Internal Server Error";
		break;
	case HTTP_STATUS_NOT_IMPLEMENTED:
		return "Not Implemented";
		break;
	case HTTP_STATUS_BAD_GATEWAY:
		return "Bad Gateway";
		break;
	case HTTP_STATUS_SERVICE_UNAVAILABLE:
		return "Service Unavailable";
		break;
	case HTTP_STATUS_GATEWAY_TIMEOUT:
		return "Gateway Time-out";
		break;
	case HTTP_STATUS_BAD_VERSION:
		return "HTTP Version not supported";
		break;
	default:
		return "";
		break;
	}
}

char * sc_content_type_get(char * filename){
  if(!strcmp(filename,"html")||!strcmp(filename,"html")){
    return "text/html";
  }else if(!strcmp(filename,"css")){
	return  "text/css";
  }else if(!strcmp(filename,"csv")){
	return  "text/csv";
  }else if(!strcmp(filename,"ics")){
	return  "text/calendar";
  }else if(!strcmp(filename,"rtf")){
	return  "text/rtf";
  }else if(!strcmp(filename,"gif")){
    return "image/gif";
  }else if(!strcmp(filename,"jpeg") || !strcmp(filename,"jpe") || !strcmp(filename,"jpg")){
    return "image/jpeg";
  }else if(!strcmp(filename,"bmp")){
    return "image/bmp";
  }else if(!strcmp(filename,"ico")){
    return "image/x-icon";
  }else if(!strcmp(filename,"png")){
    return "image/png";
  }else if(!strcmp(filename,"svg")){
    return "image/svg+xml";
  }else if(!strcmp(filename,"tif") || !strcmp(filename,"tiff")){
    return "image/tiff";
  }else if(!strcmp(filename,"mp3")){
    return "audio/mp3";
  }else if(!strcmp(filename,"au")){
    return "audio/au";
  }else if(!strcmp(filename,"snd")){
    return "audio/basic";
  }else if(!strcmp(filename,"m4a") || !strcmp(filename,"m4b") || !strcmp(filename,"m4p")){
    return "audio/mp4a-latm";
  }else if(!strcmp(filename,"mpga")){
    return "audio/mpeg";
  }else if(!strcmp(filename,"wav")){
    return "audio/x-wav";
  }else if(!strcmp(filename,"pdf")){
    return "application/pdf";
  }else if(!strcmp(filename,"bin") || !strcmp(filename,"class") || !strcmp(filename,"dll") || !strcmp(filename,"dmg") || !strcmp(filename,"dms") || !strcmp(filename,"exe")){
    return "application/octet-stream";
  }else if(!strcmp(filename,"dir")){
    return "application/x-director";
  }else if(!strcmp(filename,"js")){
    return "application/x-javascript";
  }else if(!strcmp(filename,"ppt")){
    return "application/vnd.ms-powerpoint";
  }else if(!strcmp(filename,"sh")){
    return "application/x-sh";
  }else if(!strcmp(filename,"tar")){
    return "application/x-tar";
  }else if(!strcmp(filename,"xls")){
    return "application/vnd.ms-excel";
  }else if(!strcmp(filename,"xml")){
    return "application/xml";
  }else if(!strcmp(filename,"zip")){
    return "application/zip";
  }else if(!strcmp(filename,"avi")){
    return "video/x-msvideo";
  }else if(!strcmp(filename,"mov")){
    return "video/quicktime";
  }else if(!strcmp(filename,"mp4")){
    return "video/mp4";
  }else if(!strcmp(filename,"mpeg")){
    return "video/mpeg";
  }else{
    return "text/plain";
  }
}

void sc_response_send(sc_http_response_t* res, char * filename, int fd){
	FILE* file;
	FILE* response_stream;
	int content_length;
	char * response_header = (char *)malloc(sizeof(char)*300);
	char txt_buffer[BUF_SIZE];
	int bin_buffer[BUF_SIZE];
	response_stream = fdopen(dup(fd),"w");


	struct stat file_info;
  stat(filename,&file_info);
	char * directory = (char *)malloc(sizeof(char)*1024);
  if(S_ISDIR(file_info.st_mode)){
		sc_res_content_type_set(res,"text/html");		
		sc_res_construct(res,response_header);
		fputs(response_header,response_stream);
		sc_dirctory_desc(filename,response_stream);		
		fflush(response_stream);
		fclose(response_stream);
		return;
  }

	
	file = fopen(filename, "r");
	if(file == NULL){
		sc_res_status_code_set(res,HTTP_STATUS_NOT_FOUND);
		sc_res_construct(res,response_header);
		fputs(response_header,response_stream);
		fclose(response_stream);
		free(response_header);
		return;
	}else{
  		fseek(file, 0, SEEK_END);
  		content_length = ftell(file);
		fclose(file);
	}
	sc_res_content_type_set(res,sc_content_type_get(filename));
	sc_res_content_length_set(res,content_length);

	sc_res_construct(res,response_header);
	fputs(response_header,response_stream);
	
	if(!strcmp(res->sc_content_type_get,"text")){
		file = fopen(filename,"r");
		while(fgets(txt_buffer,BUF_SIZE,file)!=NULL){
          fputs(txt_buffer, response_stream);
          fflush(response_stream);
        }
	}else{
		 file = fopen(filename,"rb");
        while(fread(bin_buffer,sizeof(int),BUF_SIZE,file)!=0){
          fwrite(bin_buffer,sizeof(int),BUF_SIZE,response_stream);
          fflush(response_stream);
        }
	}
  	fflush(response_stream);
  	fclose(response_stream);
	fclose(file);
  	return;
}

int sc_dirctory_desc(char * path, FILE * fd){
        DIR* dirptr;
        struct dirent* dir;
        dirptr = opendir(path);
        struct stat file_info;
        char pathname2[255] = " ";

        if(dirptr==NULL) {
                return 1;
        }

        char * pathname;
        while((dir = readdir(dirptr))) {
                if(dir->d_ino != 0&& strcmp(".",dir->d_name) && strcmp("..",dir->d_name)) {
												int length = sizeof(path)+sizeof(dir->d_name)+1;
                        pathname = (char*)malloc(length);
                        snprintf(pathname,length,"%s/%s",path,dir->d_name);

                        if(stat(pathname,&file_info)==-1) {
                                perror("asdf");
                        }
                        strcpy(pathname2,pathname);
                        free(pathname);
                        if(S_ISREG(file_info.st_mode)) {
                          fprintf(fd,"<p>%-30s\t<p>",pathname2);																		                          													
                        }else if(S_ISDIR(file_info.st_mode)){
                          fprintf(fd,"<p>%-30s*\t0%o<p>",pathname2);																					                          																					
                        }
												fflush(fd);
                        sc_dirctory_desc(pathname2,fd);
                }
        }
        rewinddir(dirptr);
        closedir(dirptr);
        return 0;
}

#endif