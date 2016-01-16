/*************************************************************************
	> File Name: test.c
	> Author: 
	> Mail: 
	> Created Time: 2016年01月16日 星期六 14时16分28秒
 ************************************************************************/

#include<stdio.h>
#include <stdlib.h>
#define true 1
int main(int argc,char **argv) 
{
    int a = 0;
    while (true) {
        printf("a:%d\n",a++);
        sleep(1);
        if (a==100) {
            break;
        }
        a++;
    }
    return 0;
}
