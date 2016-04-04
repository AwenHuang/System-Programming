#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>

#define SIZE 100000
 
int main(int argc, char* argv[]){
		int c, comd_a = 0, comd_t = 0, comd_o = 0, comd_d = 0, comd_f = 0;
        char o_arg[100],d_arg[100],f_arg[100];
        while((c = getopt(argc, argv, "d:f:o:at")) != -1){
            switch(c){
               case'a':
                   comd_a = 1;
                   break;
               case't':
                   comd_t = 1;
                   break;
               case'd':
                   comd_d = 1;
                   strcpy(d_arg,optarg);
                   break;
               case'f':
                   comd_f = 1;
                   strcpy(f_arg,optarg);
                   break;
               case'o':
                   comd_o = 1;
                   strcpy(o_arg,optarg);
                   break;
               default:
               		printf("Error!\n");
                   
           }
        }
        long long num = 0;
        long long process = 1;
        
        double * data;
        data = (double *)malloc(SIZE * sizeof(double));
        double temp;
        
        if(comd_f){
            FILE * ptr = fopen(f_arg, "r");
            while(fscanf(ptr, "%lf", &temp) != EOF){
                data[num++] = temp;
                if(num % SIZE  == SIZE -2)
                    data = (double*)realloc(data, sizeof(double) * SIZE * (num/SIZE + 2));
            }
        }
        else
            while(fscanf(stdin, "%lf", &temp) != EOF){
                data[num++] = temp;
                if((num%SIZE) == SIZE -2)
                    data = (double*)realloc(data, sizeof(double) * SIZE * (num/SIZE + 2));
            }
   
        long long i;
        pid_t pid[SIZE];
        int fd[SIZE][2];
        long long sum;
        if(comd_d)
            process = atoi(d_arg);
        for(i = 0; i < process; i++){
            pipe(fd[i]);
            if((pid[i] = fork()) < 0){
                perror("fork error\n");
                abort();
            }
            else if(pid[i] == 0){
                char ans[500];
                close(fd[i][0]);
                long long j;
                long long p_sum = 0, n = 0;
                for(j = 0; j < num; j++){
                    if((j % process) == i){
                        p_sum += (long long)data[j];
                        n++;
                    }
                }
                if(comd_o){
                        pid_t child = getpid();
                        FILE * ptr2 = fopen(o_arg, "aw");
                        if(comd_a == 1){
                                fprintf(ptr2, "pid = %d, average is %lf\n", child    , (double)p_sum/n);
                        }
                        fprintf(ptr2, "Child Process: %d, sum = %lld\n", child, p_sum);
                }
                else{
                        pid_t child = getpid();
                        FILE * ptr2 = fopen(o_arg, "aw");
                        if(comd_a)
                                printf("pid = %d, average is %lf\n", (double)child, p_sum/n);
                        printf("Child Process: %d, sum = %lld\n", child, p_sum);
                }
                sprintf(ans, "%lld", p_sum);
                write(fd[i][1], &ans, 500);
                return 0;
            }
        }
        int status;
        pid_t pid2;
        int t = process;
        sum = 0;
        while(t > 0){
            if((pid2 = waitpid(-1, &status, 0)) < 0){
                printf("pid = %d\n", pid);
                fprintf(stderr, "waitpid error\n");
                exit(1);
            }
            --t;
        }
        for(i = 0; i < process; i++){
            char tp[101];
            close(fd[i][1]);
            read(fd[i][0], tp, 100);
            sum += atoi(tp);
       }
            if(comd_o){
            FILE * ptr2 = fopen(o_arg, "awa");
            fprintf(ptr2, "Parent process sum : %lld\n", sum); 
            }
        else
            printf("Parent process sum : %lld\n", sum);
   
        return 0;
}

