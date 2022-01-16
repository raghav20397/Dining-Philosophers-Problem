#include<stdio.h>
#include<stdlib.h>
#include<semaphore.h>
#include<pthread.h>
#include<unistd.h>
#include<stdbool.h>
#define THREADS_NUM 5
int phils[5]={0,1,2,3,4};
sem_t forks[5];
void* philosopher(void* n){
    while(1){
        //index of current philosopher 
        //int being pointed to by the pointer
        int ph_num=*(int *)n;
        //index of left fork
        int left =ph_num;
        //index of right fork
        int right=(ph_num+1)%5;
        printf("Philosopher %d is hungry\n",ph_num);
        sleep(2.3);
        //for first philosopher
        if(ph_num==0){
            printf("Philosopher %d tries to take fork %d\n",ph_num,right);
            sem_wait(&forks[(ph_num+1)%5]);
            printf("Philosopher %d takes fork %d\n",ph_num,right);
            printf("Philosopher %d tries to take fork %d\n",ph_num,left);
            sem_wait(&forks[ph_num]);
            printf("Philosopher %d takes fork %d\n",ph_num,left);        
        }
        //for rest of the philosophers
        else{
            printf("Philosopher %d tries to take fork %d\n",ph_num,left);
            sem_wait(&forks[ph_num]);
            printf("Philosopher %d takes fork %d\n",ph_num,left);
            printf("Philosopher %d tries to take fork %d\n",ph_num,right);
            sem_wait(&forks[(ph_num+1)%5]);
            printf("Philosopher %d takes fork %d\n",ph_num,right);       
        }
        printf("Philosopher %d is eating from the plate\n",ph_num);
        sleep(2.4);
        printf("Philosopher %d has now finished eating .... \n",ph_num);
        sem_post(&forks[ph_num]);
        printf("Philosopher %d puts down fork %d\n",ph_num,left);
        sem_post(&forks[(ph_num+1)%5]);
        printf("Philosopher %d puts down fork %d\n",ph_num,right);        
    }
}

int main(){    
        pthread_t threads[THREADS_NUM];
        for(int i=0;i<THREADS_NUM;i++){
            sem_init(&forks[i],0,1);
        }
        // while(true){
        //     int i=0;
        //     phils[i]=i;
        //     pthread_create(&threads[i],NULL,philosopher,&phils[i]);
        //     phils[i]++;
        // }
        for(int i=0;i<THREADS_NUM;i++){
            // phils[i]=0;
            pthread_create(&threads[i],NULL,philosopher,&phils[i]);
            printf("Philosopher %d is thinking\n", phils[i]);
            
        }
        for(int i=0;i<THREADS_NUM;i++){
            pthread_join(threads[i],NULL);
        }                 
}
