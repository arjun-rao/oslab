#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

pthread_mutex_t buffer_mutex     = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t  canProduce   = PTHREAD_COND_INITIALIZER;
pthread_cond_t  canConsume   = PTHREAD_COND_INITIALIZER;


void *producer();
void *consumer();


int  item = 0;
int consumed = 0;
int buffer = 0;

#define MAX_BUFFER  3
#define MAX_ITEMS 10


int main()
{
   pthread_t thread1, thread2;

   pthread_create( &thread1, NULL, &producer, NULL);
   pthread_create( &thread2, NULL, &consumer, NULL);   

   pthread_join( thread2, NULL);
   pthread_join( thread1, NULL);

   printf("Items Produced Totally: %d\n",item);

   exit(EXIT_SUCCESS);
}

// Producer Process

void *producer()
{
    srand(time(NULL)); 
    int myrand = rand()%10;   
    for(;;)
    {
      // Lock mutex and then wait for signal to relase mutex
      pthread_mutex_lock( &buffer_mutex );
            
      // Wait while consumer() operates on count
      // mutex unlocked if condition varialbe in consumer() signaled.
      if(buffer==MAX_BUFFER || myrand%2)
        pthread_cond_wait( &canProduce, &buffer_mutex );
      
      
      while(buffer < MAX_BUFFER){
          myrand = rand()%10;
          if(myrand%2==0) break;
          item++;
          buffer++;          
          printf("Produced Item: %d\n",item);
      }
        
      
     
      //signal consumer()
      //pthread_cond_signal( &canConsume );


      pthread_mutex_unlock( &buffer_mutex );

      if(item >= MAX_ITEMS) return(NULL);
    }
}


// Consumer Process

void *consumer()
{
    srand(time(NULL)); 
    int myrand = rand()%10;
    for(;;)
    {

       pthread_mutex_lock( &buffer_mutex );
       
       if(buffer == 0)
       {
           pthread_cond_signal( &canProduce );           
           //pthread_cond_wait( &canConsume, &buffer_mutex );           
       }
       
       while( buffer > 0)
       {
          myrand = rand()%10;
          if(myrand%2) break;
          // Condition of if statement has been met.
          printf("Consumed Item: %d\n",++consumed);
          buffer--; 
          // Signal to free waiting thread by freeing the mutex.
          // Note: producer() is now permitted to produce more items                    
       }       
       pthread_mutex_unlock( &buffer_mutex );

       if(item >= MAX_ITEMS) return(NULL);
    }

}