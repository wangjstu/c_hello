#ifndef _object_h
#define _object_h

typedef enum {
	NORTH, SOUTH, EAST, WEST
} Direction;

typedef struct {
	char *description;
	int (*init)(void *self);
	void (*describe)(void *self);
	void (*destroy)(void *self);
	void *(*move)(void *self, Direction direction);
	int (*attack)(void *self, int damage);
} Object;

int Object_int(void *self);
void Object_destroy(void *self);
void Object_describe(void *self);
void *Object_move(void *self, Direction direction);
int Object_attack(void *self, int damage);
void *Object_new(size_t size, Object proto, char *description);

#define NEW(T, N) Object_new(sizeof(T), T##Proto, N)		//创建了一个宏，就像模板函数一样.T、N还有New都被“注入”进了右边的代码中。T##Proto语法表示“将Proto连接到T的末尾”，所以如果你写下NEW(Room, "Hello.")，就会在这里变成RoomProto
#define _(N) proto.N			//这个宏是一种为对象系统设计的“语法糖”，将obj->proto.blah简写为obj->_(blah)。它不是必需的，但是它是一个接下来会用到的有趣的小技巧。

#endif
