#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<string.h>


void die(const char *message)
{
	if (errno) {
		perror(message);
	} else {
		printf("ERROR: %s\n", message);
	}
	exit(1);
}

typedef int (*compare_cb)(int a, int b);

int *bubble_sort(int *numbers, int count, compare_cb cmp)
{
	int i = 0;
	int j = 0;
	int *target = malloc(count * sizeof(int));

	if (!target) die("Memory error.");

	memcpy(target, numbers, count * sizeof(int));
	
	for (i = 0; i < count; i++) {
		for (j = 0; j < count-1-i; j++) {
			if (cmp(target[j], target[j+1]) > 0) {
				target[j] = target[j] ^ target[j+1];
				target[j+1] = target[j] ^ target[j+1];
				target[j] = target[j] ^ target[j+1];
			}
		}
	}
	
	return target;
}

int sorted_order(int a, int b)
{
	return a - b;
}

int reverse_order(int a, int b)
{
	return b - a;
}

void test_sorting(int *numbers, int count, compare_cb cmp)
{
	int i = 0;
	unsigned char *data = (unsigned char *)cmp;
	for (i = 0; i < 25; i++) { 
		printf("%02x:", data[i]);
	}
	printf("\n");

	int *sorted = bubble_sort(numbers, count, cmp);
	if(!sorted) die("Failed to sort as requested");

	for (i = 0; i < count; i++){
		printf("%d ", sorted[i]);
	}
	printf("\n");
	free(sorted);
}

int main(int argc, char *argv[])
{
	printf("函数指针\n");

	if (argc < 2) die("USAGE: ex18 4 3 1 5 6");

	int count = argc - 1;
	int i = 0;
	char **inputs = argv+1;

	int *numbers = malloc(count * sizeof(int));
	if (!numbers) die("Memmory error.");

	for (i = 0; i < count; i++) {
   		numbers[i] = atoi(inputs[i]); //atoi是把字符串转换成整型数的一个函数
	}

	test_sorting(numbers, count, sorted_order);
	test_sorting(numbers, count, reverse_order);

	free(numbers);

	return 0;
}
