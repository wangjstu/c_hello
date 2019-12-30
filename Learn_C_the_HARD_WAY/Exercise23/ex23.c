#include <stdio.h>
#include <string.h>
#include "dbg.h"
/**
 * 达夫设备
 * *原因*
 * 首先需要了解的一件事，就是C对于它的一些语法是弱检查的。这就是你可以将do-while的一部分放入switch语句的一部分的原因，并且在其它地方的另一部分还可以正常工作。如果你观察带有goto again的我的版本，它实际上更清晰地解释了工作原理，但要确保你理解了这一部分是如何工作的。
 * 第二件事是switch语句的默认贯穿机制可以让你跳到指定的case，并且继续运行直到switch结束。
 * 最后的线索是count % 8以及顶端对n的计算。
 * 现在，要理解这些函数的工作原理，需要完成下列事情：
 * 将代码抄写在一张纸上。
 * 当每个变量在switch之前初始化时，在纸的空白区域，把每个变量列在表中。
 * 按照switch的逻辑模拟执行代码，之后再正确的case处跳出。
 * 更新变量表，包括to、from和它们所指向的数组。
 * 当你到达while或者我的goto时，检查你的变量，之后按照逻辑返回do-while顶端，或者again标签所在的地方。
 * 继续这一手动的执行过程，更新变量，直到确定明白了代码如何运作。
 *
 * *应用场景*
 * 这个小技巧的目的是手动编写“循环展开”。大而长的循环会非常慢，所以提升速度的一个方法就是找到循环中某个固定的部分，之后在循环中复制代码，序列化地展开。例如，如果你知道一个循环会执行至少20次，你就可以将这20次的内容直接写在源代码中。
 * 达夫设备通过将循环展开为8个迭代块，来完成这件事情。这是个聪明的办法，并且可以正常工作。但是目前一个好的编译器也会为你完成这些。你不应该这样做，除非少数情况下你证明了它的确可以提升速度。
 *
 */

int normal_copy(char *from, char *to, int count)
{
	int i = 0;
	for(i = 0; i < count; i++) {
		to[i] = from[i];
	}

	return i;
}

int duffs_device(char *from, char *to, int count)
{
	{
		int n = (count + 7) / 8;
		
		switch(count % 8) {
			case 0: do { *to++ = *from++;
				case 7: *to++ = *from++;
				case 6: *to++ = *from++;
				case 5: *to++ = *from++;
				case 4: *to++ = *from++;
				case 3: *to++ = *from++;
				case 2: *to++ = *from++;
				case 1: *to++ = *from++;
			} while(--n > 0);
		}
	}
	
	return count;
}

int zeds_device(char *from, char *to, int count)
{
	{
		int n = (count + 7)/8;
		
		switch(count % 8) {
			case 0:
			again: *to++ = *from++;

			case 7: *to++ = *from++;
			case 6: *to++ = *from++;
			case 5: *to++ = *from++;
			case 4: *to++ = *from++;
			case 3: *to++ = *from++;
			case 2: *to++ = *from++;
			case 1: *to++ = *from++;
				if (--n > 0) goto again;
		}
	}
	
	return count;
}

int valid_copy(char *data, int count, char expects)
{
	int i = 0;
	for(i = 0; i < count; i++) {
		if (data[i] != expects) {
			log_err("[%d] %c != %c", i, data[i], expects);
			return 0;		
		}
	}
	return 1;
}

int main(int argc, char *argv[])
{
	char from[1000] = {'a'};
	char to[1000] = {'c'};
	int rc = 0;

	memset(from, 'x', 1000);
	memset(to, 'y', 1000);
	check(valid_copy(to, 1000, 'y'), "Not initialized right.");

	rc = normal_copy(from, to, 1000);
	check(rc == 1000, "Normal copy failed:%d", rc);
	check(valid_copy(to, 1000, 'x'), "Normal copy failed.")

	memset(to, 'y', 1000);

	rc = duffs_device(from, to, 1000);
	check(rc == 1000, "Duff's device failed: %d", rc);
	check(valid_copy(to, 1000, 'x'), "Duff's device failed copy.");

	memset(to, 'y', 1000);
	
	rc = zeds_device(from, to, 1000);
	check(rc == 1000, "Zed's device failed: %d", rc);
	check(valid_copy(to, 1000, 'x'), "Zed's device failed copy.");

	
	return 0;

error:
	return 1;
}
