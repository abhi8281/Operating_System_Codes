#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>

#define FIFO_NAME1 "com_pipe1"
#define FIFO_NAME2 "com_pipe2"

int main()
{
        char s[300],vowel[20],send[300];
        int num,fd1,fd2,i,k=0,wordcnt = 1,charcnt=0,linecnt=0,sig;
        FILE *fp;
        fp = fopen("fifo.txt","w");
        mknod(FIFO_NAME1,S_IFIFO | 0666,0);
        mknod(FIFO_NAME2,S_IFIFO | 0666,0);
        printf("waiting a producer...\n");
        fd1=open(FIFO_NAME1,O_RDONLY);
        fd2=open(FIFO_NAME2,O_WRONLY);
        printf("got a producer\n");
        if((num=read(fd1,s,300))==-1)
                perror("read");
        else
        {
                s[num]='\0';
                printf("tick:read %d bytes: \"%s\"\n" , num,s);
                k=0;
                vowel[0]='\0';
                wordcnt = 1;
                for(i=0;i<num;i++)
                {
                        if(s[i]=='a'|| s[i] == 'e' || s[i] == 'i' || s[i] == 'o' || s[i] == 'u')
                        {
                                vowel[k]=s[i];
                                k++;
                        }
                        if(s[i]!=' ' && s[i+1]!=' ')
                        {
                                wordcnt++;
                        }
                        if(s[i]=='.' && (s[i+1]==' ' || s[i+1]=='\0')){
                                linecnt++;
                        }
                        else if(s[i]!='.' && s[i]!=' '){
                                charcnt++;
                        }
                }
                vowel[k]='\0';

                sprintf(send,"for the given sentence: \nword count: %d\nvowel count: %d\ncharacter count :%d\nLines are %d\n",wordcnt,k,charcnt,linecnt);
                sig = write(fd2,send,strlen(send));
                if(sig == -1)
                {
                        perror("write");
                        exit(1);
                }
                else{
                        printf("\nwritten successfully to flile 2\n");
                }
        }
        fclose(fp);
        return 0;
}
