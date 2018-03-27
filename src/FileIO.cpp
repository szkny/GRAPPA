/*
 *  Save & Load Images
 */

#include<ctime>
#include<FileIO.h>
#include<Declaration.h>

extern GRAPPA Gra;


void FileIO::Save(const char *savefile){
    if( Gra.CurrentLineID == -1 ){
        printf("no content to save.\n");
        fflush(stdout);
        return;
    }
    std::string _filename;
    if(!strcmp(savefile,"")){
        if( EmptyEditFileName() ){
            printf("no file name.\n");
            fflush(stdout);
            return;
        }else{
            _filename = EditFileName;
            std::cout<<_filename<<std::endl;
        }
    }else // savefile is not anonymous
        _filename = savefile;
    FILE *fp_save = fopen(_filename.c_str(),"w");
    time_t timer  = time(NULL);
    struct tm *local = localtime(&timer);
    char date[100];
    sprintf(date,"%04d/%02d/%02d %02d:%02d:%02d",
            local->tm_year+1900,local->tm_mon+1,
            local->tm_mday,local->tm_hour,local->tm_min,local->tm_sec);
    printf("\tsave (%s) -> '%s'\n",date,_filename.c_str());
    fprintf(fp_save,"#-- %s --#\n",date);
    fprintf(fp_save,"# WindowSize:\t\t%d,%d\n",Gra.WX,Gra.WY);
    fprintf(fp_save,"# CurrentLineID:\t%d\n\n",Gra.CurrentLineID);
    unsigned int id = 0;
    for(auto&& l : Gra.Line){
        fprintf(fp_save,"# ID:\t\t%d\n",id);
        fprintf(fp_save,"# width:\t%lf\n",l.Width);
        fprintf(fp_save,"# rgb:\t\t%lf\t%lf\t%lf\n",
                                        l.Color.R,
                                        l.Color.G,
                                        l.Color.B);
        fprintf(fp_save,"# x,y:\n");
        for(auto&& p : l.P){
            fprintf(fp_save,"%d\t%d\n",p.x,p.y);
        }
        fprintf(fp_save,"\n");
        ++id;
    }
    fclose(fp_save);
    fflush(fp_save);
    fflush(stdout);
}


void FileIO::Load(const char *loadfile){
    if(!strcmp(loadfile,"")){
        printf("no file name.\n");
        fflush(stdout);
        return;
    }
    FILE *fp_load = fopen(loadfile,"r");
    if(!fp_load){
        printf("file not found. -> '%s'\n",loadfile);
        fflush(stdout);
        return;
    }
    EditFileName = loadfile;
    Gra.Reset();
    static char buf[100],param[100],date[100],time[100];
    double arg[3];
    std::vector<position> InitPosition;
    bool PosFlag = false;
    fseek(fp_load,0,SEEK_SET);
    fgets(buf,sizeof(buf),fp_load);
    sscanf(buf,"#-- %s %s --#",date,time);
    printf("\tload (%s %s) -> '%s'\n",date,time,loadfile);
    fgets(buf,sizeof(buf),fp_load);
    sscanf(buf,"# %*s %lf,%lf",&arg[0],&arg[1]);
    glutReshapeWindow((int)arg[0],(int)arg[1]);
    sscanf(buf,"# %*s %d",&Gra.CurrentLineID);
    while(fgets(buf,sizeof(buf),fp_load) != NULL){
        if(!strcmp(buf,"\n")){
            PosFlag = false;
            continue;
        }
        if(!strncmp(buf,"#",1)){
            sscanf(buf,"# %s %lf %lf %lf",param,&arg[0],&arg[1],&arg[2]);
            if(!strcmp(param,"ID:"))
                Gra.Line.push_back( {{0,0,0},0,InitPosition} );
            if(!strcmp(param,"width:"))
                Gra.Line.back().Width = arg[0];
            if(!strcmp(param,"rgb:"))
                Gra.Line.back().Color = {arg[0],arg[1],arg[2]};
            if(!strcmp(param,"x,y:"))
                PosFlag = true;
            continue;
        }
        if(PosFlag){
            sscanf(buf,"%lf %lf",&arg[0],&arg[1]);
            Gra.Line.back().P.push_back( {(int)arg[0],(int)arg[1]} );
            Gra.FillPixel();
        }
    }
    if((int)(Gra.Line.size()-1)<Gra.CurrentLineID)
        Gra.CurrentLineID = Gra.Line.size()-1;
    fclose(fp_load);
    // remove(file);
    fflush(stdout);
}


bool FileIO::EmptyEditFileName(){
    if(EditFileName.size()){
        return false;
    }else{
        return true;
    }
}

