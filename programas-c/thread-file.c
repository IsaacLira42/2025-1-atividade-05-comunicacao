#include <stdio.h>
#include <pthread.h>
#include <string.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
int ready = 0;

void* writer(void* arg) {
    FILE* file = fopen("comunicacao.txt", "w");
    fputs("Olá, threads via arquivo!\n", file);
    fclose(file);
    pthread_mutex_lock(&mutex);
    ready = 1;
    pthread_cond_signal(&cond);
    pthread_mutex_unlock(&mutex);
    return NULL;
}

void* reader(void* arg) {
    pthread_mutex_lock(&mutex);
    while(!ready) pthread_cond_wait(&cond, &mutex);
    pthread_mutex_unlock(&mutex);
    FILE* file = fopen("comunicacao.txt", "r");
    char buffer[1024];
    fgets(buffer, sizeof(buffer), file);
    printf("Leitor: %s", buffer);
    fclose(file);
    remove("comunicacao.txt");
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
