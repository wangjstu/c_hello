#include<stdio.h>
#include<assert.h>
#include<stdlib.h>
#include<errno.h>
#include<string.h>

#define MAX_DATA 512
#define MAX_ROWS 100

struct Address{
	int id;
	int set;
	char name[MAX_DATA];
	char email[MAX_DATA];
}

struct Database{
	struct Address rows[MAX_ROWS];
}

struct Connection{
	FILE *file;
	struct Database *db;
}

void die(const char *message)
{
	if (errno) {
		perror(message);
	} else {
		printf("ERROR: %s\n", message);
	}
	exit(1);
}

void Address_print(struct Address *addr)
{
	printf("%d %s %s\n", addr->id, addr->name, addr->email);
}

void Database_load(struct Connection *conn)
{
	/**
 	*  size_t fread(void *ptr, size_t size, size_t nmemb, FILE *stream) 
 	*  参数:
 	*	ptr -- 这是指向带有最小尺寸 size*nmemb 字节的内存块的指针。
 	*	size -- 这是要读取的每个元素的大小，以字节为单位。
 	*	nmemb -- 这是元素的个数，每个元素的大小为 size 字节。
 	*	stream -- 这是指向 FILE 对象的指针，该 FILE 对象指定了一个输入流。
 	*/
	int rc = fread(conn->db, sizeof(struct Database), 1, *conn->file);
	if (rc != 1) die("Failed to load database.");
}

struct Connection *Database_open()
{
}

void Database_close(struct Connection *conn)
{
}

void Database_write(struct Connection *conn)
{
}

void Database_create(struct Connection *conn)
{
}

void Database_set(struct Connection *conn, int id, const char *name, const char *email)
{
}

void Database_get(struct Connection *conn, int id)
{
}

void Database_delete(struct Connection *conn, int id)
{
}

void Database_list(struct Connection *conn)
{
}


int main(int argc, char *argv[])
{
	printf("Ext 17 堆和栈的内存分配\n");
	return 0;
}
