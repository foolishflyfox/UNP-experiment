// intro/experiment1-2/v2/test-va-arg.c
#include <stdarg.h>
#include <stdio.h>

void TestVaArg(const char* fmt, ...){
    va_list ap;
    char buf[256];
    va_start(ap, fmt);
    vsnprintf(buf, 255, fmt, ap);
    va_end(ap);
    fputs(buf, stdout);
    return;
}

int main(int argc, char* argv[]){
    int a = 10;
    const char* b = "Hello,world";
    float c = 1.262;
    long long d = 231234123;
    double e = 3.1415926;
    TestVaArg("a=%i\nb=%s\nc=%.1f\nd=%ld\ne=%lf\n",a,b,c,d,e);
    return 0;
}
