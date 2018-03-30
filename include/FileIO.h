#ifndef FILEIO_h_
#define FILEIO_h_
/*****************************/

#include<iostream>
#include<vector>
#include<GRAPPA.h>

class FileIO{
    private:
        std::vector<std::string> FormatID;
        std::string EditFileName;

    public:
        FileIO();
        ~FileIO(){};
        void Save(const char *savefile);
        void Load(const char *loadfile);
        void DrawFileName();
        std::vector<std::string> GetFormatID();

    protected:
        bool EmptyEditFileName();
        bool CheckFileFormat(FILE *loadfile);
};

/*****************************/
#endif  // FILEIO_h_
