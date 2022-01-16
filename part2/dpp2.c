#include<stdio.h>
#include<stdlib.h>
#include<semaphore.h>
#include<pthread.h>
#include<unistd.h>
#include<stdbool.h>
#define THREADS_NUM 5
int phils[5]={0,1,2,3,4};
sem_t forks[5];
sem_t sauces[4];
int semvals[4];
void* philosopher(void* n){
    while(1){
        //index of current philosopher 
        //int being pointed to by the pointer
        int ph_num=*(int *)n;
        int whichbowl;
        //index of left fork
        int left =ph_num;
        int sem_num=ph_num;
        //index of right fork
        int right=(ph_num+1)%5;
        // int semVal0,semVal1,semVal2,semVal3;
        sem_getvalue(&sauces[0],&semvals[0]);
        sem_getvalue(&sauces[1],&semvals[1]);
        sem_getvalue(&sauces[2],&semvals[2]);
        sem_getvalue(&sauces[3],&semvals[3]);
        printf("Philosopher %d is hungry\n",ph_num);
        // printf("The value of semaphore 0 is %d \n",semvals[0]);
        sleep(2.4);
        //for first philosopher
        if(ph_num==0){
            printf("Philosopher %d tries to take fork %d\n",ph_num,right);
            sem_wait(&forks[(ph_num+1)%5]);
            printf("Philosopher %d takes fork %d\n",ph_num,right);
            printf("Philosopher %d tries to take fork %d\n",ph_num,left);
            sem_wait(&forks[ph_num]);
            printf("Philosopher %d takes fork %d\n",ph_num,left);  
            // for(int i=0;i<4;i++){
                if(semvals[3]==1){
                    sem_wait(&sauces[3]);
                    whichbowl=3;
                    printf("Philosopher %d takes sauce bowl 3\n",ph_num);                    
                    // continue;
                }
                else if(semvals[2]==1){
                    sem_wait(&sauces[2]);
                    whichbowl=2;
                    printf("Philosopher %d takes sauce bowl 2\n",ph_num);                    
                    // continue;
                }
                else if(semvals[1]==1){
                    sem_wait(&sauces[1]);
                    whichbowl=1;
                    printf("Philosopher %d takes sauce bowl 1\n",ph_num);                    
                    // continue;
                }
                else if(semvals[0]==1){
                    sem_wait(&sauces[0]);
                    whichbowl=0;
                    printf("Philosopher %d takes sauce bowl 0\n",ph_num);                    
                    // continue;
                }
                // printf("Philosopher %d takes sauce bowl %d\n",sem_num);  
            // }  
             
        }
        //for rest of the philosophers
        else{
            printf("Philosopher %d tries to take fork %d\n",ph_num,left);
            sem_wait(&forks[ph_num]);
            printf("Philosopher %d takes fork %d\n",ph_num,left);
            printf("Philosopher %d tries to take fork %d\n",ph_num,right);
            sem_wait(&forks[(ph_num+1)%5]);
            printf("Philosopher %d takes fork %d\n",ph_num,right);       
            // printf("Philosopher %d takes sauce bowl %d\n",sem_num);  
            // for(int i=0;i<4;i++){
                if(semvals[0]==1){
                    sem_wait(&sauces[0]);
                    whichbowl=0;
                    printf("Philosopher %d takes sauce bowl 0\n",ph_num);                    
                    // continue;
                }
                else if(semvals[1]==1){
                    sem_wait(&sauces[1]);
                    whichbowl=1;
                    printf("Philosopher %d takes sauce bowl 1\n",ph_num);                    
                    // continue;
                }
                else if(semvals[2]==1){
                    sem_wait(&sauces[2]);
                    whichbowl=2;
                    printf("Philosopher %d takes sauce bowl 2\n",ph_num);                    
                    // continue;
                }
                else if(semvals[3]==1){
                    sem_wait(&sauces[3]);
                    whichbowl=3;
                    printf("Philosopher %d takes sauce bowl 3\n",ph_num);                    
                    // continue;
                }
                // printf("Philosopher %d takes sauce bowl %d\n",sem_num);  
            // }
        }
        printf("Philosopher %d is eating from the plate\n",ph_num);
        sleep(2.4);
        printf("Philosopher %d has now finished eating ....\n",ph_num);
        sem_post(&sauces[whichbowl]);
        printf("Philosopher %d puts down sauce bowl %d\n",ph_num,whichbowl);
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
        for(int i=0;i<THREADS_NUM -1;i++){
            sem_init(&sauces[i],0,1);
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
