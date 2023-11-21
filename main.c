#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main (int argc, char* argv[]){

    int array[] = {1,1,1,1,2,2,2,2};
    int tam= (sizeof(array)/sizeof(int));
    int start;
    int end;
    int counter=0;
    int fd[2];
    int resultado;


    if(pipe(fd)<0){
        perror("Pipe creation");
        exit(EXIT_FAILURE);

    }

    int pid = fork();
    
    if(pid==0){
        close(fd[0]);
        start=0;
        end=(tam/2);
        for(int x=start; x<end; x++){
            counter += array[x];
        }
        
        write(fd[1], &counter, sizeof(counter));
        printf("La suma del hijo es %d\n", counter);
    }

    else{
        start=(tam/2);
        end=tam;
        close(fd[1]);
        for(int x=start; x<end; x++){
            counter += array[x];
        }   

        read(fd[0], &resultado, sizeof(resultado));
        wait(NULL);
        printf("Total sum dadito diablo %d\n", counter);
        printf("Suma total padre e hijo %d\n", resultado+counter);
    }    
    exit(EXIT_SUCCESS);

}

