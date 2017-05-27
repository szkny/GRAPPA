#ifndef Define_h_
#define Define_h_

/***************************/


#ifndef Randf_
#define Randf_
//0~1の一様乱数の作成する関数
inline double randf(void){
    rand();rand();rand();rand();rand();rand();
    return rand()*(1.0/RAND_MAX);
}
#endif

#ifndef PI
#define PI 3.14159265359
#endif

/***************************/

#endif //"Define_h_"
