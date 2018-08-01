#ifndef _HTTP_HEADER_TABLE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct sc_header_table_t {
    char   key[30];
    char   value[30];
    struct sc_header_table_t *next;
} sc_header_table_t;

void
sc_line_seperate (char* line, char key[], char value[])
{
    sscanf(line, "%s%s", key, value);
}

sc_header_table_t*
sc_header_create (char key[], char value[]) 
{
	sc_header_table_t *new_header;
	new_header = (sc_header_table_t *)malloc(sizeof(sc_header_table_t));

    strcpy(new_header->key, key);
    strcpy(new_header->value, value);

    new_header->next = NULL;
	return new_header;
}

void 
sc_header_table_append (sc_header_table_t** root, sc_header_table_t* new_header) {
	if (root == NULL) {
		new_header->next = NULL;
		*root = new_header;
	}
	else{
		new_header->next = *root;
		*root = new_header;
	}
}

#endif