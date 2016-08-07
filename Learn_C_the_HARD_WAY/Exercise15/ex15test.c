#include<stdio.h>

int main(int argc, char *argv[])
{
    char *point_name = "aaaa";
    int age = 22;
    int *point_age = &age;

    /**
    * 每个字符占一个字节，每一个数字占一个字节
    * 1、指向字符串的指针(*point_name),其实point_name是字符串开头的地址，如果使用*point_name则返回第一个字符，如果使用point_name，则返回整个字符串
    * 2、指向数字的指针(*point_age),声明的时候必须是指向一个已经存在的数字变量的地址(不能int *point_age=33;),point_age是该数字的地址，要输出该数字必须*point_age
    *
    */ 
    printf("point_name: %s\npoint_age %d\n", point_name, *point_age);

    /*
    * //warning: format ‘%s’ expects type ‘char *’, but argument 2 has type ‘int *’ 
    int ages[] = {23, 34, 13, 46,2}; 
    printf("ages %s\n", ages);
    */

    return 0;
}
