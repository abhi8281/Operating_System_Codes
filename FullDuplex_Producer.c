#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define FIFO_NAME1 "com_pipe1"
#define FIFO_NAME2 "com_pipe2"

int main()
{
        char s1[300]="", s2[300]="";
        int num,fd1,fd2,byt;
        mknod(FIFO_NAME1,S_IFIFO | 0666,0);
        mknod(FIFO_NAME2,S_IFIFO | 0666,0);
        printf("Waiting for the consumer...\n");
        fd1=open(FIFO_NAME1,O_WRONLY);
        fd2=open(FIFO_NAME2,O_RDONLY);
        printf("got a consumer , type some stuff : ");
        fgets(s1,sizeof(s1),stdin);

        if((num=write(fd1,s1,strlen(s1))) == -1){
                perror("write");
        }
        else
        {
                printf("speak: worte %d bytes to file\n",num);
                byt = read(fd2,s2,300);
                printf(" %s\n",s2);
        }
return 0;
}

