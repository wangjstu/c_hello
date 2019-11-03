/**
 * 不要隐藏某个变量，就像上面scope_demo中对count所做的一样。这可能会产生一些隐蔽的bug，你认为你改变了某个变量但实际上没有。
 * 避免过多的全局变量，尤其是跨越多个文件。如果必须的话，要使用读写器函数，就像get_age。这并不适用于常量，因为它们是只读的。
 * 我是说对于THE_SIZE这种变量，如果你希望别人能够修改它，就应该使用读写器函数。
 * 在你不清楚的情况下，应该把它放在堆上。不要依赖于栈的语义，或者指定区域，而是要直接使用malloc创建它。
 * 不要使用函数级的静态变量，就像update_ratio。它们并不有用，而且当你想要使你的代码运行在多线程环境时，会有很大的隐患。
 * 对于良好的全局变量，它们也非常难于寻找。避免复用函数参数，因为你搞不清楚仅仅想要复用它还是希望修改它的调用者版本。
 */
#include "ex22.h"
#include "dbg.h"

//使用了const来创建常量，它可用于替代define来创建常量。
const char  *MY_NAME = "Wang jun";

void scope_demo(int count)
{
    log_info("count is %d", count);

    if (count > 10) {
        //count对于当前区块是局部变量，实际上不同于函数参数列表中的参数
        int count = 100;
        log_info("count in this scope is %d", count);
    }

    log_info("count is at exit %d", count);

    count = 3000;

    log_info("count after assign %d", count);
}

int main(int argc, char *argv[]) {

    log_info("My name: %s, age: %d", MY_NAME, get_age());
    //[INFO] (ex22_main.c:26) My name: Wang jun, age: 37

    set_age(100);

    log_info("My age now is: %d", get_age());
    //[INFO] (ex22_main.c:30) My age now is: 100

    log_info("THE_SIZE is : %d", THE_SIZE);
    print_size();
    /**
     * [INFO] (ex22_main.c:32) THE_SIZE is : 1000
     * [INFO] (ex22.c:47) I think size is 1000
     */

    log_info("Ratio at first: %f", update_ratio(2.0));
    log_info("Ratio again: %f", update_ratio(10.0));
    log_info("Ratio once more: %f", update_ratio(300.0));
    /**
     * [INFO] (ex22_main.c:35) Ratio at first: 1.000000
     * [INFO] (ex22_main.c:36) Ratio again: 2.000000
     * [INFO] (ex22_main.c:37) Ratio once more: 10.000000
     */

    int count = 4;
    scope_demo(count);
    /**
     * [INFO] (ex22_main.c:9) count is 4
     * [INFO] (ex22_main.c:17) count is at exit 4
     * [INFO] (ex22_main.c:21) count after assign 3000
     */
    scope_demo(count*20);
    /**
     * [INFO] (ex22_main.c:9) count is 80
     * [INFO] (ex22_main.c:14) count in this scope is 100
     * [INFO] (ex22_main.c:17) count is at exit 80
     * [INFO] (ex22_main.c:21) count after assign 3000
     */

    /**
     * count局部变量在调用后保持不变。你将它像一个变量一样传入函数，它一定不会发生改变。要想达到目的你需要我们的老朋友指针。
     * 如果你将指向count的指针传入函数，那么函数就会持有它的地址并且能够改变它。
     */
    log_info("count after calling scope_demo: %d", count);
    //[INFO] (ex22_main.c:47) count after calling scope_demo: 4

    return 0;
}