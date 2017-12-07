/*
 *  Save & Load Images
 */

#include<Save.h>

extern GRAPPA Drawing;
const char *savefile = ".data.gra";

void Save(){
    if(!Drawing.LineID) return;
    FILE *fp_save = fopen(savefile,"w");
    time_t timer  = time(NULL);
    struct tm *local = localtime(&timer);
    char date[50];
    sprintf(date,"%04d/%02d/%02d_%02d:%02d:%02d",
            local->tm_year+1900,local->tm_mon+1,
            local->tm_mday,local->tm_hour,local->tm_min,local->tm_sec);
    printf("\tsave (%s) -> '%s'\n",date,savefile);
    fprintf(fp_save,"#-- %s --#\n",date);
    for(int i=1;i<=Drawing.LineID;++i){
        fprintf(fp_save,"# ID: %d\n",i);
        fprintf(fp_save,"# width: %lf\n",Drawing.LineWidth[i]);
        fprintf(fp_save,"# rgb: %lf\t%lf\t%lf\n",Drawing.LineColor[0][i],
                                                 Drawing.LineColor[1][i],
                                                 Drawing.LineColor[2][i]);
        fprintf(fp_save,"# x,y:\n");
        for(int j=0;j<Drawing.Counter[i];++j){
            fprintf(fp_save,"%d\t%d\n",Drawing.Px[j][i],Drawing.Py[j][i]);
        }
        fprintf(fp_save,"\n");
    }
    fflush(fp_save);
    fclose(fp_save);
}


void Load(){
    FILE *fp_load = fopen(savefile,"r");
    if(!fp_load){
        printf("file not found. -> %s\n",savefile);
        return;
    }
    Drawing.Reset();
    char buf[50],param[50],date[50];
    int  id = 0;
    int  counter = 0;
    double tmp[3];
    bool PosFlag = false;
    fseek(fp_load,0,SEEK_SET);
    fgets(buf,sizeof(buf),fp_load);
    sscanf(buf,"#-- %s --#",date);
    printf("\tload (%s) -> '%s'\n",date,savefile);
    fflush(stdout);
    while(fgets(buf,sizeof(buf),fp_load) != NULL){
        if(!strncmp(buf,"#",1)){
            sscanf(buf,"%*c %s %lf %lf %lf",param,&tmp[0],&tmp[1],&tmp[2]);
            if(!strcmp(param,"ID:")){
                id = tmp[0];
                Drawing.LineID = id;
            }
            if(!strcmp(param,"width:"))
                Drawing.LineWidth[id] = tmp[0];
            if(!strcmp(param,"rgb:"))
                for(int j=0;j<3;++j)
                    Drawing.LineColor[j][id] = tmp[j];
            if(!strcmp(param,"x,y:")) PosFlag = true;
            continue;
        }
        if(PosFlag){
            sscanf(buf,"%lf %lf",&tmp[0],&tmp[1]);
            counter = Drawing.Counter[id];
            Drawing.Px[counter][id] = tmp[0];
            Drawing.Py[counter][id] = tmp[1];
            ++Drawing.Counter[id];
            Drawing.FillPixel();
        }
        if(!strcmp(buf,"\n")){
            PosFlag = false;
            continue;
        }
    }
    fclose(fp_load);
    remove(savefile);
}


