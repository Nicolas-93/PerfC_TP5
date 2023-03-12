#ifndef INI_PARSER_INCLUDED
#define INI_PARSER_INCLUDED

#include "monde.h"
#include <stdio.h>
#include <string.h>

#define IS_OPT(opt, literal) (strcmp(opt, literal) == 0)

int ini_getopt(FILE* f, char** opt_name, char** opt_val);
Monde parse_conf(char* filename);

#endif
