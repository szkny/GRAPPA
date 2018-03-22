/*
 *  Save & Load Images
 */

#include<ctime>
#include<Save.h>

extern GRAPPA Gra;

const char *DefaultFileName = ".data.gra";

void Save(const char *savefile){
    if(Gra.CurrentLineID == -1) return;
    static char file[400];
    if(!strcmp(savefile,""))
        sprintf(file,"%s",DefaultFileName);
    else
        sprintf(file,"%s",savefile);
    FILE *fp_save = fopen(file,"w");
    time_t timer  = time(NULL);
    struct tm *local = localtime(&timer);
    char date[100];
    sprintf(date,"%04d/%02d/%02d %02d:%02d:%02d",
            local->tm_year+1900,local->tm_mon+1,
            local->tm_mday,local->tm_hour,local->tm_min,local->tm_sec);
    printf("\tsave (%s) -> '%s'\n",date,file);
    fprintf(fp_save,"#-- %s --#\n",date);
    fprintf(fp_save,"# CurrentLineID: %d\n\n",Gra.CurrentLineID);
    unsigned int id = 0;
    for(auto&& l : Gra.Line){
        fprintf(fp_save,"# ID: %d\n",id);
        fprintf(fp_save,"# width: %lf\n",l.Width);
        fprintf(fp_save,"# rgb: %lf\t%lf\t%lf\n",l.Color.R,
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


void Load(const char *loadfile){
    static char file[400];
    if(!strcmp(loadfile,""))
        sprintf(file,"%s",DefaultFileName);
    else
        sprintf(file,"%s",loadfile);

    FILE *fp_load = fopen(file,"r");
    if(!fp_load){
        printf("file not found. -> %s\n",file);
        return;
    }
    Gra.Reset();
    static char buf[100],param[100],date[100],time[100];
    double arg[3];
    std::vector<position> InitPosition;
    bool PosFlag = false;
    fseek(fp_load,0,SEEK_SET);
    fgets(buf,sizeof(buf),fp_load);
    sscanf(buf,"#-- %s %s --#",date,time);
    printf("\tload (%s %s) -> '%s'\n",date,time,file);
    fgets(buf,sizeof(buf),fp_load);
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


