#include<stdio.h>

int main(int argc, char *argv[])
{
    //go through each string in argv
    int i = 0;
    while (i < argc) {
        printf("arg %d: %s\n", i, argv[i]);
        i++;
    }
    
    //let's make our own array of strings
    char *states[] = {
        "California", "oregon", "Washington", "Texas"
    };
    
    int num_states = 4;
    i = 0; // watch for this
    while (i < num_states) {
        printf("state %d: %s\n", i, states[i]);
        i++;
    }

    char *cp_argv[] = {};
    i = 0;
    while (i < argc) {
        printf("cp argv %d to cp_argv\n", i);
        cp_argv[i] = argv[i];
        i++;
    }
    

    i = 0; // watch for this
    while (i < argc) {
        printf("cp_argv  %d: %s\n", i, cp_argv[i]);
        i++;
    }

    return 0;
}
