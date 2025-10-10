#include <stdio.h>
#include <stdlib.h>

void print_help() {
    printf("Usage:\n");
    printf("  range N\t\t- prints [0, 1, ... N-1]\n");
    printf("  range M N\t\t- prints [M, M+1, ... N-1]\n");
    printf("  range M N S\t\t- prints [M, M+S, M+2S, ... N-1]\n");
}

int main(int argc, char *argv[]) {
    int start = 0, end = 0, step = 1;
    
    if (argc == 1) {
        print_help();
        return 0;
    }
    
    if (argc == 2) {
        end = atoi(argv[1]);
    } else if (argc == 3) {
        start = atoi(argv[1]);
        end = atoi(argv[2]);
    } else if (argc == 4) {
        start = atoi(argv[1]);
        end = atoi(argv[2]);
        step = atoi(argv[3]);
        
        if (step == 0) {
            fprintf(stderr, "Error: step cannot be zero\n");
            return 1;
        }
    } else {
        fprintf(stderr, "Error: too many arguments\n");
        print_help();
        return 1;
    }
    
    if (step > 0) {
        for (int i = start; i < end; i += step) {
            printf("%d\n", i);
        }
    } else {
        for (int i = start; i > end; i += step) {
            printf("%d\n", i);
        }
    }
    
    return 0;
}
