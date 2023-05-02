#include "file.h"

int File:: isSubstring(string end, string file_name)
{
    int M = (int)end.length();
    int N = (int)file_name.length();

    /* A loop to slide pat[] one by one */
    for (int i = 0; i <= N - M; i++) 
    {
        int j;

        /* For current index i, check for pattern match */
        for (j = 0; j < M; j++)
            if (file_name[i + j] != end[j])
                break;
        
        if (j == M)
            return i;
    }

    return -1;
}
vector<string> File:: createFileList()
{
    // Declaring Vector of String type
    vector<string> file_names_list;
    struct stat file_stats = { 0 };
    struct dirent* dent;
    DIR* dirp = opendir(".");
    
    if (dirp != NULL)    {
        do   {
            dent = readdir(dirp);

            if (dent)  {
                if (isSubstring(".screen", dent->d_name) != -1) 
                {
                    // Strings can be added at any time with push_back
                    file_names_list.push_back(dent->d_name);

                   // cout << "file: " << dent->d_name << endl;
                }
            }
        } while (dent);
    }
    closedir(dirp);

    return file_names_list;
}
vector<string> File:: findFile(string file_name)
{
    // Declaring Vector of String type
    vector<string> file_names_list;
    struct stat file_stats = { 0 };
    struct dirent* dent;
    DIR* dirp = opendir(".");

    if (dirp != NULL)
    {
        do
        {
            dent = readdir(dirp);

            if (dent)
            {
                if (isSubstring(file_name, dent->d_name) != -1)
                {

                    // Strings can be added at any time with push_back
                    file_names_list.push_back(dent->d_name);

                    cout << "file: " << dent->d_name << endl;
                    closedir(dirp);

                    return file_names_list;
                }
            }

        } while (dent);
    }

    closedir(dirp);

    return file_names_list;
}