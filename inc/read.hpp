#ifndef __FILEMANAGER__
#define __FILEMANAGER__

#include <vector>
#include <sstream>

class FileManager {
    private:
        std::vector<char *> _streams;
    public:
        ~FileManager();
        void ReadFile(const char * filename);
        const char * GetFile(int index);
};

#endif