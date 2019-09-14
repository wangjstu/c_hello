/**
 * $ make ex17
 * cc -Wall -g    ex17.c   -o ex17
 * $ ./ex17 db.dat c
 * $ ./ex17 db.dat s 1 zed zed@zedshaw.com
 * $ ./ex17 db.dat s 2 frank frank@zedshaw.com
 * $ ./ex17 db.dat s 3 joe joe@zedshaw.com
 * $
 * $ ./ex17 db.dat l
 * 1 zed zed@zedshaw.com
 * 2 frank frank@zedshaw.com
 * 3 joe joe@zedshaw.com
 * $ ./ex17 db.dat d 3
 * $ ./ex17 db.dat l
 * 1 zed zed@zedshaw.com
 * 2 frank frank@zedshaw.com
 * $ ./ex17 db.dat g 2
 * 2 frank frank@zedshaw.com
 * $
 * $ valgrind --leak-check=yes ./ex17 db.dat g 2
 * # cut valgrind output...
 * $
 */
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
};

struct Database{
	struct Address rows[MAX_ROWS];
};

struct Connection{
	FILE *file;
	struct Database *db;
};

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
	int rc = fread(conn->db, sizeof(struct Database), 1, conn->file);
	if (rc != 1) die("Failed to load database.");
}

struct Connection *Database_open(const char *filename, char mode)
{
	struct Connection *conn = malloc(sizeof(struct Connection));
	if(!conn) die("Memory error");

	conn->db = malloc(sizeof(struct Database));
	if(!conn->db) die("Memory error");

	if(mode == 'c') {
		conn->file = fopen(filename, "w");
	} else {
		conn->file = fopen(filename, "r+");
		if(conn->file){
			Database_load(conn);
		}
	}

	if(!conn->file) die("Failed to open the file");
	return conn;
}

void Database_close(struct Connection *conn)
{
	if(conn){
		if(conn->file) fclose(conn->file);
		if(conn->db) free(conn->db);
		free(conn);
	}
}

void Database_write(struct Connection *conn)
{
	rewind(conn->file);
	
	int rc = fwrite(conn->db, sizeof(struct Database), 1, conn->file);
	if(rc != 1) die("Failed to write database");

	rc = fflush(conn->file);
	if(rc == -1) die("Cannot flush database");
}

void Database_create(struct Connection *conn)
{
	int i = 0;

	for(i = 0; i < MAX_ROWS; i++) {
		//init the prototype
		struct Address addr = {.id = i, .set = 0};
		// then jush assign it
		conn->db->rows[i] = addr;
	}
}

void Database_set(struct Connection *conn, int id, const char *name, const char *email)
{
	struct Address *addr = &conn->db->rows[id];
	if(addr->set) die("Already set, dlete it first");	
	
	addr->set = 1;
	char *res = strncpy(addr->name, name, MAX_DATA);
	if(!res) die("Name copy failed");
	
	res = strncpy(addr->email, email, MAX_DATA);
	if(!res) die("email copy failed");
}

void Database_get(struct Connection *conn, int id)
{
	struct Address *addr = &conn->db->rows[id];

	if(addr->set) {
		Address_print(addr);
	} else {
		die("ID is not set");
	}
}

void Database_delete(struct Connection *conn, int id)
{
	struct Address addr = {.id = id, .set = 0};
	conn->db->rows[id] = addr;
}

void Database_list(struct Connection *conn)
{
	int i = 0;
	struct Database *db = conn->db;

	for(i = 0; i<MAX_ROWS; i++) {
		struct Address *cur = &db->rows[i];
		if(cur->set) {
			Address_print(cur);
		}
	}
}


int main(int argc, char *argv[])
{
	printf("Ext 17 堆和栈的内存分配\n");
	
	if(argc < 3) die("USAGE: ex17 <dbfile> <action> [action params]");
	
	char *filename = argv[1];
	char action = argv[2][0];

	struct Connection *conn = Database_open(filename, action);
	int id = 0;

	if(argc > 3) id = atoi(argv[3]);
	if(id >= MAX_ROWS) die("There's not that many records.");

	switch(action) {
		case 'c':
			Database_create(conn);
			Database_write(conn);
			break;
		case 'g':
			if(argc != 4) die("Need an id to get");
			Database_get(conn, id);
			break;
		case 's':
			if(argc != 6) die("Need id, name, email to set");
			Database_set(conn, id, argv[4], argv[5]);
			Database_write(conn);
			break;
		case 'd':
			if(argc != 4) die("Need id to delete");
			Database_delete(conn, id);
			Database_write(conn);
			break;
		case 'l':
			Database_list(conn);
			break;
		default:
			die("Invalid action, only: c=create, g=get, s=set, d=del, l=list");
	}

	Database_close(conn);

	return 0;
}
