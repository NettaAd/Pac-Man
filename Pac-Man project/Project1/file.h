#ifndef _FILE
#define _FILE

#include "Location.h"

class File 
{
public:

    int isSubstring(string end, string file_name);
    vector<string> createFileList();
    vector<string> findFile(string file_name);
};

#endif
