#include <iostream>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sys/stat.h>
#include <filesystem>
#include <dirent.h>

using namespace std;

class Tools
{
public:
    string trim_ends(string str)
    {
        str.erase(str.begin());
        str.erase(str.end() - 1);
        return str;
    }
    vector<string> split_str(string str, string delimeter)
    {
        vector<string> splittedStrings = {};
        size_t pos = 0;

        while ((pos = str.find(delimeter)) != string::npos)
        {
            string token = str.substr(0, pos);
            if (token.length() > 0)
                splittedStrings.push_back(token);
            str.erase(0, pos + delimeter.length());
        }
        if (str.length() > 0)
            splittedStrings.push_back(str);
        return splittedStrings;
    }
    bool dir_exists(const char *pzPath)
    {
        if (pzPath == NULL)
        {
            return false;
        }
        DIR *pDir;
        bool bExists = false;
        pDir = opendir(pzPath);
        if (pDir != NULL)
        {
            bExists = true;
            (void)closedir(pDir);
        }

        return bExists;
    }
    bool file_exists(const char *filepath)
    {
        struct stat buffer;
        return (stat(filepath, &buffer) == 0);
    }
    // current datetime
    string getCurrentDateTime()
    {
        time_t now = time(0);
        struct tm tstruct;
        char buf[80];
        tstruct = *localtime(&now);
        strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);
        return buf;
    }
};