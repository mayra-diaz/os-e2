#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <semaphore.h>

#define loop(n) for(int i = 0; i < n; ++ i)
#define parpadeo() for(int i = 0; i < 1; i++) 
#define PERSONAS 10
sem_t wait;
volatile int priority_mujer[PERSONAS] = {0};
volatile int priority_hombre[PERSONAS] = {0};
volatile int available  = -1;
void* hombre_desea_entrar(void *mn);
void* mujer_desea_entrar(void *wmn);
void* hombre_sale(void* mn);
void* mujer_sale(void* wmn);
int agregar_mujeres();
int agregar_hombres();
void ready();

int main() {
  ready();
  return 0;
}

void ready(){
  sem_init(&wait, 0, 1);
  pthread_t women[PERSONAS];
  pthread_t men[PERSONAS];
  int identity[PERSONAS];
  loop(PERSONAS) {
      identity[i] = i;
      pthread_create(&women[i], NULL, mujer_desea_entrar, &identity[i]);
      pthread_create(&men[i], NULL, hombre_desea_entrar, &identity[i]);
  }
  loop(PERSONAS) {
      pthread_join(women[i],NULL);
      pthread_join(men[i],NULL);
  }
  sem_destroy(&wait);
}

void* hombre_desea_entrar(void *mn) {
  parpadeo() {
    priority_hombre[*(int*)mn] = 1;
    printf("Hombre %d espera entrar al baño\n", *(int*)mn); 
    while (agregar_mujeres())
      if (available  != *(int*)mn) {
        priority_hombre[*(int*)mn] = 0; 
        while (available  != -1);
        available  = *(int*)mn;
        while (agregar_mujeres());
        priority_hombre[*(int*)mn] = 1; 
      }
    sleep(1);
    printf("Hombre %d entra al baño\n", *(int*)mn); 
    available  = -1;
    sleep(1);
    hombre_sale(mn);
  }
  return NULL;
}

void* mujer_desea_entrar(void *wmn) {
  parpadeo() {
    priority_mujer[*(int*)wmn] = 1;
    printf("Mujer %d espera entrar al baño\n", *(int*)wmn);
    while (agregar_hombres())
      if (available  != *(int*)wmn) {
        priority_mujer[*(int*)wmn] = 0;
        while (available  != -1);
        available  = *(int*)wmn;	
        while (agregar_hombres());
        priority_mujer[*(int*)wmn] = 1; 
      }
    sleep(1);
    printf("Mujer %d entra al baño\n", *(int*)wmn); 
    available  = -1;
    sleep(1);
    mujer_sale(wmn);
  }
  return NULL;
}

void* mujer_sale(void* wmn) {
  printf("Mujer %d sale del baño\n", *(int*)wmn);
  priority_mujer[*(int*)wmn] = 0;
  sleep(1);
  return NULL;
}

void* hombre_sale(void* mn) {
  printf("Hombre %d sale del baño\n", *(int*)mn);
  priority_hombre[*(int*)mn] = 0;
  sleep(1);
  return NULL;
}

int agregar_mujeres() {
  sem_wait(&wait);
  loop(PERSONAS) if (priority_mujer[i]) {
      sem_post(&wait);
      return 1;
    }
  sem_post(&wait);
  return 0;
}

int agregar_hombres() {
  sem_wait(&wait); 
  loop(PERSONAS) if (priority_hombre[i]) {
        sem_post(&wait);
        return 1;
    }
  sem_post(&wait);
  return 0;
}