// inet_aton-demo.c
#include <stdio.h>
#include <arpa/inet.h>
int main(){
    const char *a1="256.12.13.14";
    const char *a2="255.12.13.14";
    const char *a3 = "192.168.1.23";
    union {
        struct in_addr addr;
        unsigned char c[4];
    }b;
    // 判断地址是否有效，有效返回1，否则返回0
    printf("%s is %svalidate\n",a1,inet_aton(a1, NULL)?"":"in");
    printf("%s is %svalidate\n",a2,inet_aton(a2, NULL)?"":"in");
    if(inet_aton(a3, &b.addr)==1)
        for(int i=0; i<sizeof(b.c); ++i)
            printf("%u%c", b.c[i], i==sizeof(b.c)-1?'\n':',');
    else
        printf("%s is invalidate\n", a3);
}

