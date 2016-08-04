#include<stdio.h>

int main(int argc, char *argv[])
{
    int i=0;
    
    //go through each string in argv
    //why am i skipping argv[0]? //
    for (i = 1; i < argc; i++) {
        printf("arg %d: %s\n", i, argv[i]);
    }
    
    //let's make our array of strings
    char *states[] = {
        "California", "oregon", "Washington", "Texas", "NULL", NULL
    };   
    int num_states = 6;
    
    //print array size of four site
    //printf("states size: %d\n", sizeof(states));

    for(i=0;i<num_states;i++){
        printf("state %d: %s\n", i, states[i]);
    }


    printf("set states value to argv\n");
    argv = states;
     
    for (i = 1; i < num_states; i++) {
        printf("arg %d: %s\n", i, argv[i]);
    }

    return 0;
}
