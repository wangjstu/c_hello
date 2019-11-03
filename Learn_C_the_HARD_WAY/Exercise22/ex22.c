/**
 * extern
 * 这个关键词告诉编译器“这个变量已存在，但是他在别的‘外部区域’里”。通常它的意思是一个.c文件要用到另一个.c文件中定义的变量。
 *  这种情况下，我们可以说ex22.c中的THE_SIZE变量能被ex22_main.c访问到。
 * static（文件）
 * 这个关键词某种意义上是extern的反义词，意思是这个变量只能在当前的.c文件中使用，程序的其它部分不可访问。
 *  要记住文件级别的static（比如这里的THE_AGE）和其它位置不同。
 * static（函数）
 * 如果你使用static在函数中声明变量，它和文件中的static定义类似，但是只能够在该函数中访问。
 *  它是一种创建某个函数的持续状态的方法，但事实上它很少用于现代的C语言，因为它们很难和线程一起使用。
 * 在上面的两个文件中，你需要理解如下几个变量和函数：
 * THE_SIZE
 * 这个你使用extern声明的变量将会在ex22_main.c中用到。
 * get_age和set_age
 * 它们用于操作静态变量THE_AGE，并通过函数将其暴露给程序的其它部分。你不能够直接访问到THE_AGE，但是这些函数可以。
 * update_ratio
 * 它生成新的ratio值并返回旧的值。它使用了函数级的静态变量ratio来跟踪ratio当前的值。
 * print_size
 * 打印出ex22.c所认为的THE_SIZE的当前值。
 */
#include <stdio.h>
#include "ex22.h"
#include "dbg.h"


/**
 * THE_SIZE
 * 这个你使用extern声明的变量将会在ex22_main.c中用到。
 * get_age和set_age
 * 它们用于操作静态变量THE_AGE，并通过函数将其暴露给程序的其它部分。你不能够直接访问到THE_AGE，但是这些函数可以。
 * update_ratio
 * 它生成新的ratio值并返回旧的值。它使用了函数级的静态变量ratio来跟踪ratio当前的值。
 * print_size
 * 打印出ex22.c所认为的THE_SIZE的当前值。
 */
int THE_SIZE = 1000;

static int THE_AGE = 37;

int get_age() {
    return THE_AGE;
}

void set_age(int age) {
    THE_AGE = age;
}

double update_ratio(double new_ratio) {
    static double ratio = 1.0;

    double old_ratio = ratio;
    ratio = new_ratio;

    return old_ratio;
}

void print_size() {
    log_info("I think size is %d", THE_SIZE);
}
