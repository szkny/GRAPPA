#ifndef Color_h_
#define Color_h_

/***************** Hue to RGB Class ****************/

class hue2rgb{
    private:
        double r,g,b;
    public:
        /* h:0~hmax */
        hue2rgb(double h, double hmax);
        inline double R();
        inline double G();
        inline double B();
};


inline hue2rgb::hue2rgb(double h, double hmax){
    r = 1.0;
    g = 1.0;
    b = 1.0;
    double hue = h/hmax*360.0;
    if(hue<0)        while(hue<0)   hue += 360;
    else if(360<hue) while(360<hue) hue -= 360;
    if(0<=hue&&hue<60){
        r = 1.0;
        g = hue/60.0;
        b = 0.0;
    }
    else if(60<=hue&&hue<120){
        r = (120-hue)/60;
        g = 1.0;
        b = 0.0;
    }
    else if(120<=hue&&hue<180){
        r = 0.0;
        g = 1.0;
        b = (hue-120)/60;
    }
    else if(180<=hue&&hue<240){
        r = 0.0;
        g = (240-hue)/60;
        b = 1.0;
    }
    else if(240<=hue&&hue<300){
        r = (hue-240)/60;
        g = 0.0;
        b = 1.0;
    }
    else if(300<=hue&&hue<=360){
        r = 1.0;
        g = 0.0;
        b = (360-hue)/60;
    }
}


inline double hue2rgb::R(){
    return r;
}
inline double hue2rgb::G(){
    return g;
}
inline double hue2rgb::B(){
    return b;
}


/**************************************************/

#endif //"Color_h_"
