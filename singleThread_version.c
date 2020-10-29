#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define PRODUCT_AMOUT 1400

int sensorSignal();


int main(){

      srant(time(NULL));
      int count1, index =0;
      int product_weights_SUM =0, products_gone_through=0, product_weights[PRODUCT_AMOUT], random_number;

      clock_t sum_start, sum_end, mat_start, mat_end, main_start, main_end;
      double delta_sum, delta_main, delta_mat;

      main_start = clock();

      mat_start = clock();

      while(products_gone_through < PRODUCT_AMOUT){
            if(sensorSignal() == 1){
                  products_gone_through++;
                  product_weights[index] = rand()%33+1;
                  index++;
                  printf("Products already gone through: %d.\n",products_gone_through);
            }
      }

      mat_end = clock();

      delta_mat = ((double)) (mat_end - mat_start) / CLOCKS_PER_SEC;

      sum_start = clock();

      for(index = 0, index < PRODUCT_AMOUT;index++){
            product_weights_SUM += product_weights[index];
      }

      sum_end = clock();

      delta_sum = ((double)) (sum_end -sum_start)/CLOCKS_PER_SEC;
      printf("Total product weight gone through: %d\n", product_weights_SUM);


      main_end = clock();
      delta_main = ((double)) (main_end - main_start)/CLOCKS_PER_SEC;

      printf("#------Key Time Indicators Analysis------#");
      printf("MainExecution Time: %f\n.", delta_main);
      printf("WeightsSum Time: %f\n.", delta_sum);
      printf("ProductionMat Time: %f\n.", delta_mat);


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