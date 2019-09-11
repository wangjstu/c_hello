#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

struct Person {
	char *name;
	int age;
	int height;
	int weight;
};

struct Person *Person_create(char *name, int age, int height, int weight){
	struct Person *who = malloc(sizeof(struct Person));
	assert(who != NULL);
	
	/**
 	* 原型：编辑
 	* 	extern char *strdup(char *s);
 	* 	头文件：string.h
 	* 说明：
 	* 	功 能: 将串拷贝到新建的位置处
 	* 	strdup()在内部调用了malloc()为变量分配内存，不需要使用返回的字符串时，需要用free()释放相应的内存空间，否则会造成内存泄漏。
 	* 返回值:
 	* 	返回一个指针,指向为复制字符串分配的空间;如果分配空间失败,则返回NULL值。
 	*/	
	who->name = strdup(name);
	who->age = age;
	who->height = height;
	who->weight = weight;

	return who;
}

void Person_destroy(struct Person *who)
{
	//不想显式释放内存又能避免内存泄露的办法是引入libGC库。
	//你需要把所有的malloc换成GC_malloc，然后把所有的free删掉。
	assert(who != NULL);
	free(who->name);
	free(who);
}


void Person_print(struct Person *who){
	printf("Name: %s\n", who->name);
	printf("age: %d\n", who->age);
	printf("height: %d\n", who->height);
	printf("weight: %d\n", who->weight);
}


int main(int argc, char * argv[]){
	printf("struct Person size is %ld\n", sizeof(struct Person));

	struct Person *jun = Person_create("wangjun", 29, 178, 72);
	struct Person *mei = Person_create("meibao", 29, 160, 43);
	
	printf("wangjun is at memory location %p:\n", jun);
	printf("wangjun size is %ld\n", sizeof(jun));
	Person_print(jun);

	printf("meibao is at memory location %p:\n", mei);
	Person_print(mei);

	//x->y是(*x).y的简写。
	jun->age+=20;
	Person_print(jun);

	Person_destroy(jun);
	Person_destroy(mei);


	return 0;
}
