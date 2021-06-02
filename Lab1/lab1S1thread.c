/*Name: Federico Madden
Date: 4/7/2020
Title: Lab1 - Step 1
Description: This program demonstrates multithreading in C
*/
#include <stdio.h>      /* printf, stderr */
#include <sys/types.h>  /* pid_t */
#include <unistd.h>     /* fork */
#include <stdlib.h>     /* atoi */
#include <errno.h>      /* errno */ 
#include <pthread.h>
/* main function with command-line arguments to pass */

void* thread_print(void* arg){
    int* n = (int*) arg;
    for (int i=0;i<100;i++) {
            printf("Child thread %d\n",i);
            usleep(*n);
        }
}
int main(int argc, char *argv[]) {
    int i, n;
    if (argc !=2){
	fprintf(stderr,"usage: ./a.out <seconds> \n");
	exit(0);
    } 
    n = atoi(argv[1]); // n microseconds to input from keyboard for delay
    printf("\n Before forking.\n");

    pthread_t id;
    pthread_create(&id, NULL, thread_print, &n);
    // Parent thread
    for (i=0;i<100;i++) {
        printf("\t \t \t Main thread %d \n",i);
        usleep(n);
    }
    pthread_join(id, NULL);
 
    return 0;
}
