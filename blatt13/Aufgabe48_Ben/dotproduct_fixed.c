#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

/* Define global data where everyone can see them */
#define NUMTHRDS 8
#define VECLEN 1000000
int *a, *b; 
long sum=0;

/*Define a mutex that can be seen global which allows the threads to lock on the sum 
to add their part of the dot product to it.
*/
pthread_mutex_t mutexsum;



void *dotprod(void *arg)
{
  /* Each thread works on a different set of data.
   * The offset is specified by the arg parameter. The size of
   * the data for each thread is indicated by VECLEN.
   */
   int i, start, end, offset, len;
   long tid = (long)arg;
   offset = tid;
   len = VECLEN;
   start = offset*len;
   end   = start + len;

/* Perform my section of the dot product */
   printf("thread: %ld starting. start=%d end=%d\n",tid,start,end-1);

	long mysum = 0;	

	for (i=start; i<end ; i++){
		mysum += (a[i] * b[i]);
	} 

	/*Critical section: Here the working thread has to add its part of the dot product to the global result
	Therefore we implement a mutex to lock on the variable while changing its value	
	*/
	
	/*Lock to the mutex, this call blocks when another thread is accessing the resource*/	
	pthread_mutex_lock(&mutexsum);
	/*Add the own part to the result*/
	sum += mysum;
	/*Unlock the mutex, such that the resource becomes available to the other threads*/	
	pthread_mutex_unlock(&mutexsum);

   printf("thread: %ld done. Global sum now is=%li\n",tid,sum);

   pthread_exit((void*) 0);
}



int main (int argc, char *argv[])
{
long i;
void *status;
pthread_t threads[NUMTHRDS];
pthread_attr_t attr;

/* Assign storage and initialize values */
a = (int*) malloc (NUMTHRDS*VECLEN*sizeof(int));
b = (int*) malloc (NUMTHRDS*VECLEN*sizeof(int));
  
for (i=0; i<VECLEN*NUMTHRDS; i++)
  a[i]= b[i]=1;

/* Create threads as joinable, each of which will execute the dot product
 * routine. Their offset into the global vectors is specified by passing
 * the "i" argument in pthread_create().
 */
pthread_attr_init(&attr);
pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
for(i=0; i<NUMTHRDS; i++) 
   pthread_create(&threads[i], &attr, dotprod, (void *)i); 

pthread_attr_destroy(&attr);

/* Wait on the threads for final result */
for(i=0; i<NUMTHRDS; i++) 
  pthread_join(threads[i], &status);

/* After joining, print out the results and cleanup */
printf ("Final Global Sum=%li\n",sum);
free (a);
free (b);
pthread_exit(NULL);
}   

