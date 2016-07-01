#include <dirent.h>

#include "directory.h"
#include "debugLogger.h"

static DIR *wdir_ptr;

// TODO: different functions for getting the current working directory and a listing of the directory and ent
void setwdir(DIR *directory)
{
     DIR wdir = *directory;
     wdir_ptr = &wdir;

     // for debug console
     char* DebugString = d_nameRemoveFile(wdir_ptr);
     // WriteDebugMessage(DEBUG_NOTIFY, __FILE__, (char *)wdir_ptr);
}


void getwdir(void)
{
     DIR *wd;
     wd = opendir("C:\\Users\\CalebsComp\\Desktop");     
     setwdir(wd);
     
     DIR *directory;
     dirent *ent;

     if((directory = opendir("."))) {
	  while(ent = readdir(directory)) {
	       WriteDebugMessage(DEBUG_NOTIFY, __FILE__, ent->d_name);
	  }
	  closedir(directory);
     } else {
	  perror("");
     }
}


char* d_nameRemoveFile(DIR *directory)
{
     char* path = (char *) directory;
     // remove the file portion from the directory string
     return "";
     
}
// char* getwdir_s()
// {
     
// }


// char** getwdir_as()
// {
     
// }
