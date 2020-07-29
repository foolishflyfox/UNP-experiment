// getcurtime.c
#include <time.h>
const char* getcurtime(){
    static char strtm[64];
    time_t t = time(NULL);
    strftime(strtm, sizeof(strtm), "%F %T", localtime(&t));
    return strtm;
}
