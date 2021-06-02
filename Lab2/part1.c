
/*Name: Federico Madden
Date: 4/8/2020
Title: Lab2 - Step 1
Description: This program copies a file using fopen(), fread(), and fwrite()
*/
#include <stdio.h>
#include <pthread.h>
#include <time.h>

void copy_file(char *fname) {
    char buffer[64];
    FILE* f_read = fopen(fname, "r");
    FILE* f_write = fopen("dest1.dat", "w");
    size_t length;

    while(0 < (length = fread(buffer, 1, sizeof(buffer), f_read))){
        fwrite(buffer, 1 , length, f_write);
    }
    fclose(f_read);
    fclose(f_write);
}

int main(int argc, char *argv[]) {
    double cpu_time_used;
    clock_t start = clock();

    copy_file(argv[1]);

    clock_t end = clock();
    double time_elapsed = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Time Elapsed: %f\n", time_elapsed);
}