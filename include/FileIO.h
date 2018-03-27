#ifndef FILEIO_h_
#define FILEIO_h_
/*****************************/

#include<iostream>
#include<GRAPPA.h>

class FileIO{
    private:
        std::string EditFileName;
    public:
        void Save(const char *savefile);
        void Load(const char *loadfile);
        bool EmptyEditFileName();
};

/*****************************/
#endif  // FILEIO_h_
