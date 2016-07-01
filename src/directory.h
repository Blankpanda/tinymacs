#ifndef _directory
#define _directory

#include <dirent.h>
#include "directory.h"

/* header definitions */

void getwdir();
void setwdir(DIR*);
char* d_nameRemoveFile(DIR*);
#endif
