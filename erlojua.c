#include <stdio>
#include <pthread.h>
#define MAIZTASUNA = 200;



int main(){
	//inicialization
	pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
	pthread_cond_t cond1 = PTHREAD_COND_INITIALIZER;
	pthread_cond_t cond2 = PTHREAD_COND_INITIALIZER;
	pid_t, clock, temp1, temp2;
	int tmpCount = 2;
	int done = 0;
	

	//clock
	clock = fork();
	if(clock<0){
		printf("FORK ERROR");
	} else if(clock ==0){
erlojua();
	}

	//temp
	temp1 = fork();
	if(temp1<0){
		printf("FORK ERROR");
	} else if(temp1 == 0){
		erlojua();
	}

	temp2 = fork();
	if(temp2 < 0){
		printf("FORK ERROR");
	} else if(temp2 ==0){
		erlojua();
	}
	



}
void erlojua(){
	while (true) {
		pthread_mutex_lock(&mutex);
		while (tmpCount > done){
			pthread_cond_wait(&cond1);
			pthread_mutex_wait(&mutex);
			//do sth
		}
	done = 0; 
	pthread_cond_signal(&cond2);
	pthread_mutex_unlock(&mutex);
}
void temporizadorea(){
	while (true) {
		done++;
		//do sth

		pthread_cond_signal(&cond);
		pthread_cond_wait(&cond2);
		pthrad_mutex_wait(&mutex);
		
	}
}

