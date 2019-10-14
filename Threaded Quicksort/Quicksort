#define _POSIX_C_SOURCE 199309L 
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>
#include <limits.h>
#include <fcntl.h>
#include <time.h>
#include <pthread.h>
#include <inttypes.h>
#include <math.h>

long long int n;

int * shareMem(size_t size){
    key_t mem_key = IPC_PRIVATE;
    int shm_id = shmget(mem_key, size, IPC_CREAT | 0666);
    return (int*)shmat(shm_id, NULL, 0);
}


int partition (int arr[],int lo, int hi) 
{ 
    int pivotInd = rand()%(hi - lo+1) + lo;
     int tem=arr[pivotInd];
     arr[pivotInd]=arr[hi];
     arr[hi]=tem;
    int pivot = arr[hi];     
    int i = (lo - 1);   

    for (int i1 = lo; i1 <= hi- 1; i1++) 
    { 
        if (arr[i1] < pivot) 
        { 
            i++;    
            int temp = arr[i];
            arr[i]=arr[i1];
            arr[i1]=temp;
        } 
    } 
    int temp = arr[i+1];
    arr[i+1]=arr[hi];
    arr[hi]=temp;
    return (i + 1); 
} 

void norm_quickSort(int arr[],int lo, int hi) 
{ 
    if (lo < hi) 
    { 

        int pi = partition(arr, lo, hi); 
        norm_quickSort(arr, lo, pi - 1); 
        norm_quickSort( arr,pi + 1, hi); 
    } 
} 
void conc_quickSort(int arr[],int lo, int hi) 
{ 
    if (lo < hi) 
    { 
        if(hi-lo+1<=5){
            int a[5], mi=INT_MAX, mid=-1;
            for(int i=lo;i<hi;i++)
            {
                int j=i+1; 
                for(;j<=hi;j++)
                    if(arr[j]<arr[i] && j<=hi) 
                    {
                        int temp = arr[i];
                        arr[i] = arr[j];
                        arr[j] = temp;
                    }
                }
                return;
            } 

            int pi = partition(arr, lo, hi); 
            int pid1 = fork();
            int pid2;
            if(pid1==0){
                conc_quickSort(arr, lo, pi - 1); 

                _exit(1);
            }
            else{
                pid2 = fork();
                if(pid2==0){
            //sort right half array
                    conc_quickSort(arr,pi + 1, hi); 

                    _exit(1);
                }
                else{
                    int status;
                    waitpid(pid1, &status, 0);
                    waitpid(pid2, &status, 0);
                }
            }
            return;

        } 
    } 


    struct arg{
        int l;
        int r;
        int* arr;    
    };

    void *threaded_quickSort(void* a) 
    { 
        struct arg *args = (struct arg*) a;
        int lo = args->l;
        int hi = args->r;
        int *arr = args->arr;
        if(lo>hi) return NULL;
        if (lo < hi) 
        { 
            if(hi-lo+1<=5){
                int a[5], mi=INT_MAX, mid=-1;
                for(int i=lo;i<hi;i++)
                {
                    int j=i+1; 
                    for(;j<=hi;j++)            
                        if(arr[j]<arr[i] && j<=hi) 
                        {
                            int temp = arr[i];
                            arr[i] = arr[j];
                            arr[j] = temp;
                        }
                    }
                    return NULL;
                }

                int pi = partition( arr,lo, hi); 

//sort left half array
                struct arg a1;
                a1.l = lo;
                a1.r = pi;
                a1.arr = arr;
                pthread_t tid1;
                pthread_create(&tid1, NULL, threaded_quickSort, &a1);


    //sort right half array
                struct arg a2;
                a2.l = pi+1;
                a2.r = hi;
                a2.arr = arr;
                pthread_t tid2;
                pthread_create(&tid2, NULL, threaded_quickSort, &a2);


    //wait for the two halves to get sorted
                pthread_join(tid1, NULL);
                pthread_join(tid2, NULL);


            } 
        } 

        void runSorts(){

            struct timespec ts;

    //getting shared memory
            int *arr = shareMem(sizeof(int)*(n+1));
            for(int i=0;i<n;i++) scanf("%d", arr+i);
                int brr[n+1];
            int crr[n+1];
            for(int i=0;i<n;i++) brr[i] = arr[i];
                for(int i=0;i<n;i++) crr[i] = arr[i];

                    printf("Running concurrent quicksort for n = %lld\n", n);
                clock_gettime(CLOCK_MONOTONIC_RAW, &ts);
                long double st = ts.tv_nsec/(1e9)+ts.tv_sec;

                conc_quickSort(arr, 0, n-1);
                for (int i = 0; i < n; ++i)
                {
                    printf("%d ",arr[i]);
                }
                printf("\n");

                clock_gettime(CLOCK_MONOTONIC_RAW, &ts);
                long double en = ts.tv_nsec/(1e9)+ts.tv_sec;
                printf("time = %Lf\n", en - st);
                long double t1 = en-st;
                pthread_t tid;
                struct arg a;
                a.l = 0;
                a.r = n-1;
                a.arr = brr;
                printf("Running threaded quicksort for n = %lld\n", n);
                clock_gettime(CLOCK_MONOTONIC_RAW, &ts);
                st = ts.tv_nsec/(1e9)+ts.tv_sec;

                pthread_create(&tid, NULL,threaded_quickSort, &a);
                pthread_join(tid, NULL);
                for (int i = 0; i < n; ++i)
                {
                   printf("%d ",brr[i] );
               } 
               printf("\n");
               clock_gettime(CLOCK_MONOTONIC_RAW, &ts);
               en = ts.tv_nsec/(1e9)+ts.tv_sec;
               printf("time = %Lf\n", en - st);
               long double t2 = en-st;

               printf("Running normal quicksort for n = %lld\n", n);
               clock_gettime(CLOCK_MONOTONIC_RAW, &ts);
               st = ts.tv_nsec/(1e9)+ts.tv_sec;

               norm_quickSort(crr,0,n-1); 
               for (int i = 0; i < n; ++i)
               {
                   printf("%d ",crr[i] );
               } 
               printf("\n");

               clock_gettime(CLOCK_MONOTONIC_RAW, &ts);
               en = ts.tv_nsec/(1e9)+ts.tv_sec;
               printf("time = %Lf\n", en - st);
               long double t3 = en - st;

               printf("normal quicksort ran:\n\t[ %Lf ] times faster than concurrent quicksort\n\t[ %Lf ] times faster than threaded quicksort\n\n\n", t1/t3, t2/t3);
               shmdt(arr);
               return;
           }

           int main(){

            scanf("%lld", &n);
            runSorts();
            return 0;
        }
