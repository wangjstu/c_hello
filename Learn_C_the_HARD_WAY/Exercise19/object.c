#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<assert.h>
#include "object.h"


/**
 * int Object_int(void *self);
 * void Object_destroy(void *self);
 * void Object_describe(void *self);
 * void *Object_move(void *self, Direction direction);
 * int Object_attack(void *self, int damage);
 * void *Object_new(size_t size, Object proto, char *description);
 */

void Object_destroy(void *self)
{
	Object *obj = self;
	if (obj) {
		if(obj->description) free(obj->description);
		free(obj);
	}
}

void Object_describe(void *self)
{
	Object *obj = self;
	printf("%s.\n", obj->description);
}

int Object_init(void *self)
{
	return 1;	
}

void *Object_move(void *self, Direction direction)
{
	printf("You can't go that direction.\n");
	return NULL;
}

int Object_attack(void *self, int damage)
{
    printf("You can't attack that.\n");
    return 0;
}

// size_t是一些C/C++标准在stddef.h中定义的。这个类型足以用来表示对象的大小。size_t的真实类型与操作系统有关。
// 在32位架构中被普遍定义为：
// typedef   unsigned int size_t;
// 而在64位架构中被定义为：
// typedef  unsigned long size_t;
// int 固定四个字节
void *Object_new(size_t size, Object proto, char *description)
{
	if (!proto.init) proto.init = Object_init;
	if (!proto.describe) proto.describe = Object_describe;
	if (!proto.destroy) proto.destroy = Object_destroy;
	if (!proto.attack) proto.attack = Object_attack;
	if (!proto.move) proto.move = Object_move;

	// calloc函数原型：void* calloc（unsigned int num，unsigned int size）；
	// 功能：在内存的动态存储区中分配num个长度为size的连续空间，
	// 函数返回一个指向分配起始地址的指针；如果分配不成功，返回NULL。
	// calloc在动态分配完内存后，自动初始化该内存空间为零，而malloc不做初始化，
	// 分配到的空间中的数据是随机数据。其中malloc的简介如下：extern void* malloc(unsigned int size)；
	Object *el = calloc(1, size);
	*el = proto;
	
	//extern char *strdup(char *s);将串拷贝到新建的位置处,头文件：string.h
	//strdup不是标准的c函数。strdup()在内部调用了malloc()为变量分配内存，
	//不需要使用返回的字符串时，需要用free()释放相应的内存空间，否则会造成内存泄漏。
	
	//char *strcpy(char* dest, const char *src); 头文件：#include <string.h>和 #include <stdio.h>
	//功能：把从src地址开始且含有NULL结束符的字符串复制到以dest开始的地址空间
	//说明：strcpy是标准的C语言标准库函数。src和dest所指内存区域不可以重叠且dest必须有足够的空间
	//来容纳src的字符串。
	el->description = strdup(description);
	
	if(!el->init(el)) {
		el->destroy(el);
		return NULL;
	} else {
		return el;
	}
}
