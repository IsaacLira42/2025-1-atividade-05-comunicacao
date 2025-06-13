#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
char shared_mem[1024];

void* writer(void* arg) {
    pthread_mutex_lock(&mutex);
    strcpy(shared_mem, "Olá, threads via memória!");
    pthread_mutex_unlock(&mutex);
    return NULL;
}

void* reader(void* arg) {
    pthread_mutex_lock(&mutex);
    printf("Leitor: %s\n", shared_mem);
    pthread_mutex_unlock(&mutex);
    return NULL;
}

int main() {
    pthread_t t1, t2;
    pthread_create(&t1, NULL, writer, NULL);
    pthread_create(&t2, NULL, reader, NULL);
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    return 0;
}
