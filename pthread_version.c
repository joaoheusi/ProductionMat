#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <unistd.h>

#define PRODUCT_AMOUT 1400

int sensorSignal();
void * productCount(void *arg);
void * productSum(void *arg);

pthread_mutex_t lock;
pthread_cond_t  reached_Count;

int products_gone_through = 0,product_weights[PRODUCT_AMOUT],random_number;


int main(){

      srand(time(NULL));
      int index, product_weights_SUM = 0;
      long no1=1, no2=2, no3=3, no4=4;
      clock_t sum_start, sum_end, mat_start, mat_end, main_start, main_end;
      double delta_sum, delta_mat, delta_main;
      pthread_mutexattr_t mutex_attr_prio_inherit;
      int mutex_protocol;

      pthread_mutexattr_init(&mutex_attr_prio_inherit);
      pthread_mutexattr_getprotocol(&mutex_attr_prio_inherit, PTHREAD_PRIO_INHERIT);

      if(mutex_protocol != PTHREAD_PRIO_INHERIT){
            pthread_mutexattr_setprotocol(&mutex_attr_prio_inherit, PTHREAD_PRIO_INHERIT);
      }

      main_start = clock();

      
      if (pthread_mutex_init(&lock,NULL)){
            printf("Not possible to start mutex.\n");
            return 6;
      }


      mat_start = clock();
      pthread_t mat_thread[3], thread_COUNT;

      pthread_create(&mat_thread[0], NULL, productSum, (void *), no1);
      pthread_create(&mat_thread[1], NULL, productSum, (void *), no2);
      pthread_create(&mat_thread[2], NULL, productSum, (void *), no3);
      pthread_create(&thread_COUNT, NULL, productSum, (void *), no4);

      while (products_gone_through < PRODUCT_AMOUT){

            printf("Products already gone through: %d.\n",products_gone_through);
      }
      
      for (index = 0; index <3; index++){
            pthread_join(mat_thread[index],NULL);
      }

      pthread_join(thread_COUNT,NULL);
      mat_end = clock();
      delta_mat = ((double)) (mat_end - mat_start) / CLOCKS_PER_SEC;

      sum_start = clock();
      for (index = 0; index < PRODUCT_AMOUT; i++){
            product_weights_SUM += product_weights[index];
      }
      
      sum_end = clock();
      delta_sum = ((double)) (sum_end - sum_start) /CLOCKS_PER_SEC;

      printf("Total product weight gone through: %d\n", product_weights_SUM);
      printf("Product count: %d\n",products_gone_through);

      main_end = clock();
      delta_main = ((double)) (main_end - main_start)/CLOCKS_PER_SEC;

      printf("#------Key Time Indicators Analysis------#");
      printf("MainExecution Time: %f\n.", delta_main);
      printf("WeightsSum Time: %f\n.", delta_sum);
      printf("ProductionMat Time: %f\n.", delta_mat);
      pthread_mutex_destroy(&lock);
      pthread_cond_destroy(&reached_Count);
      pthread_exit(NULL);

      return 0;
      
}

int sensorSignal(){
      random_number = rand()+1;
      if(random_number%2 == 0){
            return 1;
      }
      else {
            return 0;
      }
}

void *productCount(void *arg){
      long id = (long) arg;

      pthread_mutex_lock(&lock);
      while(products_gone_through<PRODUCT_AMOUT){
            pthread_cond_wait(&reached_Count, &lock);
      }
      pthread_mutex_unlock(&lock);
      pthread_exit(NULL);
}

void *productSum(void *arg){
      long id = (long) arg;
      while(products_gone_through < PRODUCT_AMOUT){
            if(sensorSignal()==1){
                  pthread_mutex_lock(&lock);
                  product_weights[products_gone_through] = rand()%33+1;
                  products_gone_through++;
                  if(products_gone_through == PRODUCT_AMOUT){
                        pthread_cond_signal(&reached_Count);
                  }

                  pthread_mutex_unlock(&lock);
            }
      }
      pthread_exit(NULL);
}