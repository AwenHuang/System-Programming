#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <signal.h>
#include <unistd.h>

int fish_num = 0;
int fish_got = 0;
int put = 0;

void got(int sig){
		int i;
		if(fish_got == 0){
				fish_got = 1;
				printf("\033[1;33mA fish is eating a bait!\033[m\n");
				for(i=3; i>=1; i--){
						if(i > 1);
							sleep(1);
						if(put == 0) // player has press the ctrl_z again -> pull the fish
								break;
						printf("The remain time to pull the fishing pole:\033[1;31m%d\033[m\n",i);
				}	
				if(put == 1)
						alarm(1);
		}
		else{
				fish_got = 0;
				printf("\033[31mThe fish has escaped!\033[m\n");
		}
}
void game_start(int sig){
		srand(time(NULL));
		int t;
		if(put == 0){ // put
				put = 1;
				printf("\n\033[1;34mPut\033[m the fishing pole\n");
				alarm(0);
				t = (rand()%3)+3;
				//printf("time = %d\n",t);
				alarm(t);
		}
		else{ // pull
				put = 0;
				printf("\n\033[1;34mPull\033[m the fishing pole\n");
				if(fish_got == 1){
						alarm(0);
						fish_got = 0;
						printf("\033[1;32mGot a fish! The number of currently grabbed fishes: %d\033[m\n", ++fish_num);
				}
				alarm(0);
		}
}
void game_end(int sig){
		 printf("\n\033[1;37mThe number of totally grabbed fishes : %d\033[m\n",fish_num);
		 exit(0);
}
int main(){
		signal(SIGINT,game_start);
		signal(SIGALRM,got);
		signal(SIGTSTP,game_end);
		while(1){
				pause();
		}
		exit(0);
}
