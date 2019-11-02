#ifndef __dbg_h_
#define __dbg_h_

#include <stdio.h>
#include <errno.h>
#include <string.h>

#ifdef NDEBUG
#define debug(M, ...)
#else
#define debug(M, ...) fprintf(stderr, "DEBUG %s:%d: " M "\n", __FILE__, __LINE__, ##__VA_ARGS__)
#endif

#define clean_errno() (errno == 0 ? "None" : strerror(errno))

/**
 * #用来把参数转换成字符串  #define P(A) printf("%s:%d\n",#A,A);  int a = 1, b = 2; P(a+b);输出的结果就是 a+b:3
 * -------------------------
 * ##运算符可以用于宏函数的替换部分。这个运算符把两个语言符号组合成单个语言符号，为宏扩展提供了一种连接实际变元的手段
 * ##就是个粘合剂，将前后两部分粘合起来，也就是有“字符化”的意思。但是“##”不能随意粘合任意字符，必须是合法的C语言标示
 * 符。在单一的宏定义中，最多可以出现一次“#”或“##”预处理操作符。如果没有指定与“#”或“##”预处理操作符相关的计算次序，
 * 则会产生问题。为避免该问题，在单一的宏定义中只能使用其中一种操作符(即，一份“#”或一个“##”，或都不用)。除非非常有
 * 必要，否则尽量不要使用“#”和“##”。
 * -------------------------
 * __VA_ARGS__ 是一个可变参数的宏，很少人知道这个宏，这个可变参数的宏是新的C99规范中新增的，目前似乎只有gcc支持
 * （VC6.0的编译器不支持）。实现思想就是宏定义中参数列表的最后一个参数为省略号（也就是三个点）。
 * -------------------------
 * ##__VA_ARGS__ 宏前面加上##的作用在于，当可变参数的个数为0时，这里的##起到把前面多余的","去掉的作用,否则会编译出错
 */
#define log_err(M, ...) fprintf(stderr, "[ERROR] (%s:%d: errno: %s) " M "\n", __FILE__, __LINE__, clean_errno(), ##__VA_ARGS__)

#define log_warn(M, ...) fprintf(stderr, "[WARN] (%s:%d: errno: %s) " M "\n", __FILE__, __LINE__, clean_errno(), ##__VA_ARGS__)

#define log_info(M, ...) fprintf(stderr, "[INFO] (%s:%d) " M "\n", __FILE__, __LINE__, ##__VA_ARGS__)

#define check(A, M, ...) if(!(A)) { log_err(M, ##__VA_ARGS__); errno=0; goto error; }

#define sentinel(M, ...) { log_err(M, ##__VA_ARGS__); errno = 0; goto error; }

#define check_mem(A) check((A), "Out of memory.")

#define check_debug(A, M, ...) if(!(A)) { debug(M, ##__VA_ARGS__); errno=0; goto error;}

#endif
