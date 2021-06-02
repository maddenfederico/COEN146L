
/*Name: Federico Madden
Date: 4/8/2020
Title: Lab2 - Step 2
Description: This program copies a file using open(), read(), and write())
*/

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>

void copy_file(char *f) {
    char buffer[64];

    int f_read = open(f, O_RDONLY);
    int f_write = open("dest2.dat", O_WRONLY | O_CREAT);
    
    long int n;
    while ((n = read(f_read, buffer, sizeof(buffer))) > 0){
        write(f_write, buffer, n);
    }

    close(f_read);
    close(f_write);
}

int main(int argc, char *argv[]) {
    double cpu_time_used;
    clock_t start = clock();

    copy_file(argv[1]);

    clock_t end = clock();
    double time_elapsed = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Time Elapsed: %f\n", time_elapsed);
}