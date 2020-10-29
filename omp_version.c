#include <stdio.h>
#include <omp.h>
#include <time.h>

#define PRODUCT_AMOUT 1400


int index =0, products_gone_through = 0, product_weights[PRODUCT_AMOUT], random_number;

int sensorSignal(){
      random_number = rand()+1;
      if(random_number%2 == 0){
            return 1;
      }
      else {
            return 0;
      }
}

void productSum(void *arg){
      while(products_gone_through < PRODUCT_AMOUT){
            if(sensorSignal() == 1){
                  if(products_gone_through < PRODUCT_AMOUT){
                        #pragma omp parallel reduction(+:products_gone_through){
                              products_gone_through++;
                              product_weights[index] = rand()%33+1;
                              index++;
                        }
                  }
            }
      }
}

int main(){

      clock_t main_start, main_end;
      double delta_main;
      
      ompt_set_num_threads(3);
      
      srand(time(NULL));

      int count1=0,count2,count3;
      int product_weights_SUM = 0;
      productSum();



      printf("Products gone Through: %d\n", products_gone_through);
      main_start = clock();
      
      for(count1 =0;count1 <PRODUCT_AMOUT;count1++){
            product_weights_SUM += product_weights[count1];
      }

      main_end = clock();

      delta_main = ((double) (main_end - main_start)) /CLOCKS_PER_SEC;

      printf("#------Key Time Indicators Analysis------#");
      printf("MainExecution Time: %f\n.", delta_main);
      printf("Total product weight gone through: %d\n", product_weights_SUM);

      return 0;

}