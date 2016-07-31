#include <stdio.h>

int main(int argc, char *argv[])
{
    int areas[] = {10, 12, 13, 14, 20};
    char name[] = "Zed";
    char full_name[] = {
    'z', 'e', 'd', ' ', 'A', '.', ' ', 'S', 'h', 'a', 'w', '\0'
    };
    
    //WARNING: On some systems you may have to change the %ld in this code to a %u since it will use unsigned ints
    printf("The size of an int: %u\n", sizeof(int)); //4
    printf("The size of areas (int[]): %u\n", sizeof(areas)); //20
    printf("The number of ints in areas: %u\n", sizeof(areas)/sizeof(int)); //5
    printf("The first area is %d, the 2nd %d.\n", areas[0], areas[2]); //10, 13
    
    printf("The size of a char: %u\n", sizeof(char)); //1
    printf("The size of name (char[]): %u\n", sizeof(name)); //4
    printf("The number of chars: %u\n", sizeof(name)/sizeof(char)); //4

    printf("The size of full_name (char[]): %u\n", sizeof(full_name)); //12
    printf("The number of chars: %u\n", sizeof(full_name)/sizeof(char)); //12
    
    printf("name=\"%s\" and full_name=\"%s\"\n", name, full_name); //name="Zed" and full_name="zed A. Shaw"

    return 0;
}
