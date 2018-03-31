#ifndef FILEIO_h_
#define FILEIO_h_
/*****************************/

#include<iostream>
#include<fstream>
#include<vector>
#include<GRAPPA.h>

class FileIO{
    private:
        std::vector<std::string> FormatID;
        std::string EditFileName;

    public:
        FileIO();
        ~FileIO(){};
        void Save(std::string savefile);
        void Load(std::string loadfile);
        void DrawFileName();
        std::vector<std::string> GetFormatID();

    protected:
        bool EmptyEditFileName();
        bool CheckFileFormat(std::ifstream &fp_load);
};

/*****************************/
#endif  // FILEIO_h_
