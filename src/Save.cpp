/*
 *  Save & Load Images
 */

#include<Save.h>

extern GRAPPA Drawing;
const char *savefile = ".data.gra";

void Save(){
    if(Drawing.CurrentLineID == -1) return;
    FILE *fp_save = fopen(savefile,"w");
    time_t timer  = time(NULL);
    struct tm *local = localtime(&timer);
    char date[100];
    sprintf(date,"%04d/%02d/%02d %02d:%02d:%02d",
            local->tm_year+1900,local->tm_mon+1,
            local->tm_mday,local->tm_hour,local->tm_min,local->tm_sec);
    printf("\tsave (%s) -> '%s'\n",date,savefile);
    fprintf(fp_save,"#-- %s --#\n",date);
    fprintf(fp_save,"# CurrentLineID: %d\n\n",Drawing.CurrentLineID);
    unsigned int id = 0;
    for(auto&& l : Drawing.Line){
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


void Load(){
    FILE *fp_load = fopen(savefile,"r");
    if(!fp_load){
        printf("file not found. -> %s\n",savefile);
        return;
    }
    Drawing.Reset();
    char buf[100],param[100],date[100],time[100];
    double arg[3];
    std::vector<position> InitPosition;
    bool PosFlag = false;
    fseek(fp_load,0,SEEK_SET);
    fgets(buf,sizeof(buf),fp_load);
    sscanf(buf,"#-- %s %s --#",date,time);
    printf("\tload (%s %s) -> '%s'\n",date,time,savefile);
    fgets(buf,sizeof(buf),fp_load);
    sscanf(buf,"# %*s %d",&Drawing.CurrentLineID);
    while(fgets(buf,sizeof(buf),fp_load) != NULL){
        if(!strcmp(buf,"\n")){
            PosFlag = false;
            continue;
        }
        if(!strncmp(buf,"#",1)){
            sscanf(buf,"# %s %lf %lf %lf",param,&arg[0],&arg[1],&arg[2]);
            if(!strcmp(param,"ID:")){
                Drawing.Line.push_back( {{0,0,0},0,InitPosition} );
            }
            if(!strcmp(param,"width:"))
                Drawing.Line.back().Width = arg[0];
            if(!strcmp(param,"rgb:")){
                Drawing.Line.back().Color.R = arg[0];
                Drawing.Line.back().Color.G = arg[1];
                Drawing.Line.back().Color.B = arg[2];
            }
            if(!strcmp(param,"x,y:")) PosFlag = true;
            continue;
        }
        if(PosFlag){
            sscanf(buf,"%lf %lf",&arg[0],&arg[1]);
            Drawing.Line.back().P.push_back({(int)arg[0],(int)arg[1]});
            Drawing.FillPixel();
        }
    }
    if((int)(Drawing.Line.size()-1)<Drawing.CurrentLineID)
        Drawing.CurrentLineID = Drawing.Line.size()-1;
    fclose(fp_load);
    remove(savefile);
    fflush(stdout);
}


