
#include <stdio.h>
#include <pthread.h>
#include <time.h>
#include <pthread.h>
#include <string.h>

void* copy_file(void *arg) {
    char* fname = (char*) arg;

    char buffer[64];

    char copy[strlen(fname) + 5];
    strcpy(copy, "dest");
    strcat(copy, fname);
    
    FILE* f_read = fopen(fname, "r");
    FILE* f_write = fopen(copy, "w");
    size_t length;
    while (0 < (length = fread(buffer, 1, sizeof(buffer), f_read))){
        fwrite(buffer, 1 , length, f_write);
    }

    fclose(f_read);
    fclose(f_write);

    return 0;
}

int main(int argc, char *argv[]) {
    clock_t start = clock();

    pthread_t threads[argc-1];
    
    for(int i = 0; i < argc-1; ++i) {
        pthread_create(&threads[i], NULL, copy_file, (void*) argv[i+1]);
    }

    for (int i = 0; i < argc-1; i++) {
        pthread_join(threads[i],NULL);
    }

    clock_t end = clock();
    double elapsed = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Time Used: %f\n", elapsed);
}