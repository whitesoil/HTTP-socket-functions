#ifndef _SC_URL_PARSER_H

#include <string.h>

#define SC_ARG_KEY_MAXLEN       30
#define SC_ARG_VALUE_MAAXLEN    40
#define SC_PATH_LENGTH          30
#define SC_ARGUEMENT_STREAM_MAXLEN 120

enum {STATIC, DYNAMIC};

typedef struct sc_url_arguement_t {
    char                key[SC_ARG_KEY_MAXLEN];
    char                value[SC_ARG_VALUE_MAAXLEN];
    struct sc_url_arguement_t* next;
} sc_url_arguement_t;

typedef struct sc_url_t {
    char                path[SC_PATH_LENGTH];
    sc_url_arguement_t  *args;
} sc_url_t;

void
sc_string_getter(char* p, char arr[])
{
    int len = strlen(p);
    for(int i = 0; i < len; i++)
        arr[i] = *(p + i);

    arr[len] = *(p + len);
}

void
sc_arg_seperate(char* line, char key[], char value[])
{
    char *kp = strtok(line, "=");
    char *vp = strtok(NULL, "=");
    sc_string_getter(kp, key);
    sc_string_getter(vp, value);
}

sc_url_arguement_t*
sc_url_arguement_create (char key[], char value[])
{
	sc_url_arguement_t *new_arguement;
	new_arguement = (sc_url_arguement_t *)malloc(sizeof(sc_url_arguement_t));

    strcpy(new_arguement->key, key);
    strcpy(new_arguement->value, value);

    new_arguement->next = NULL;
	return new_arguement;
}

void
sc_arguement_append(sc_url_arguement_t** root, sc_url_arguement_t* new_arguement)
{
	if (root == NULL) {
		new_arguement->next = NULL;
		*root = new_arguement;
	}
	else{
		new_arguement->next = *root;
		*root = new_arguement;
	}
}

int
sc_url_arguement_parser(char* arguments, sc_url_t* url)
{
    char *p = strtok(arguments, "&");

    if( p == NULL ) return STATIC;
    else {
        while( p != NULL){
            char key[SC_ARG_KEY_MAXLEN], value[SC_ARG_VALUE_MAAXLEN];
            sc_arg_seperate(p, key, value);
            sc_arguement_append(&(url->args),sc_url_arguement_create(key, value));
            p = strtok(NULL, "&");
        }
    }
    return DYNAMIC;
}

char*
sc_url_arguement_find (sc_url_t* url, char key[])
{
    sc_url_arguement_t* p = url->args;
    while( p->next != NULL)
        if(strcmp(p->key, key))
            return p->value;

    return NULL;
}

int
sc_url_parse (char* str, sc_url_t* url)
{
    char* ptr;
    char arguements[SC_ARGUEMENT_STREAM_MAXLEN];

    strcat(url->path,strtok(str, "?"));

    for(int i=0; i<strlen(url->path)-1; i++)
        url->path[i] = url->path[i+1];
    url->path[strlen(url->path)-1] = '\0';
    
    ptr = strtok(NULL, "?");
    if ( ptr == NULL ) 
        return STATIC;
    else 
    {
        sc_string_getter(ptr, arguements);     
        int type = sc_url_arguement_parser(arguements, url);
        return type;
    }
}

#endif