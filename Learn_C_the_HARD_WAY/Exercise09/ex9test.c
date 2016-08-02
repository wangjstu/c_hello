#include <stdio.h>

int main(int argc, char *argv[])
{
    int numbers[4] = {0};
    char name[4] = {'a'};
    name[3] = 'B';

    //first ,print them out raw
    printf("number: %d, %d, %d, %d\n", numbers[0], numbers[1], numbers[2], numbers[3]);//number: 0, 0, 0, 0
    printf("name: %c, %c, %c, %c\n", name[0], name[1], name[2], name[3]);//name: a, , , B
    printf("name: %s\n", name);//name: a

    //setup the numbers
    numbers[0] = 1;
    numbers[1] = 2;
    numbers[2] = 3;
    numbers[3] = 4;

    name[0] = 'Z';
    name[1] = 'e';
    name[2] = 'd';
    name[3] = '\0';

    //then print them out initialized
    printf("number: %d, %d, %d, %d\n", numbers[0], numbers[1], numbers[2], numbers[3]); //number: 1, 2, 3, 4
    printf("name: %c, %c, %c, %c\n", name[0], name[1], name[2], name[3]); //name: Z, e, d,
    printf("name: %s\n", name); //name: Zed

    // another way to use name
    char *another = "Zed";
    
    printf("another: %s\n", another); //another: Zed
    printf("another each: %c, %c, %c, %c\n", another[0], another[1], another[2], another[3]); //another each: Z, e, d,

    char name2[3] = "wjj";

    printf("name2: %c, %c, %c, %c\n", name2[0], name2[1], name2[2], name2[3]); //name2: w, j, j, Z  //out range of array set 
    printf("name2: %s\n", name2); //name2: wjjZed
   
    another = name2;
    printf("another: %s\n", another); //another: wjjZed
    
    /*
    *  //error: incompatible types when assigning to type ¡®char[3]¡¯ from type ¡®char *¡¯
    name2 = "wj";
    printf("change name2: %s\n", name2);    
    */

    /*
    *  // error: expected expression before ¡®{¡¯ token
    name2[3] = {'w', 'x'};
    printf("change name2 with array way: %s\n", name2);    
    */
   
    /*
    * //error: incompatible types when assigning to type ¡®char[3]¡¯ from type ¡®char *   
    name2 = another;
    printf("change name2 with array way: %s\n", name2);
    */

    return 0; 
}
