#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <dirent.h>
void search(char c, char *s, char *fn)
{
        int fd, i = 0, cnt = 0, j = 0;
        char ch, buff[80], *p;
        fd = open(fn, O_RDONLY);
        if (fd == -1)
        {
                printf("file can not be opened");
                return;
        }
        switch (c)
        {
        case 'f':
                while (read(fd, &ch, 1) != 0)
                {
                        if (ch == '\n')
                        {
                                buff[j] = '\0';
                                if (strstr(buff, s) != NULL)
                                {
                                        printf("%d:%s", buff);
                                        break;
                                }
                                j = 0;
                        }

                        else
                                buff[j++] = ch;
                }
                break;
        case 'c':
                while (read(fd, &ch, 1) != 0)
                {
                        if (ch == '\n')
                        {
                                buff[j] = '\0';
                                if (strstr(buff, s) != NULL)
                                {
                                        cnt++;
                                }
                                j = 0;
                        }

                        else
                                buff[j++] = ch;
                }
                printf("\ntotal no of occurences %d \n", cnt);
                break;

        case 'a':
                while (read(fd, &ch, 1) != 0)
                {
                        if (ch == '\n')
                        {
                                buff[j] = '\0';
                                if (strstr(buff, s) != NULL)
                                {
                                        printf("%d:%s\n", buff);
                                }
                                j = 0;
                        }

                        else
                                buff[j++] = ch;
                }
                break;
        }
}
int main()
{
        char buff[80], t1[20], t2[20], t3[20], t4[20];
        int n, pid, k = 0, status;
        system("clear");
        while (1)
        {
                printf("myshell$");
                fflush(stdin);
                fgets(buff, 80, stdin);
                t1[0] = t2[0] = t3[0] = t4[0] = '\0';
                n = sscanf(buff, "%s%s%s%s", t1, t2, t3, t4);
                if (strcmp(t1, "exit\0") == 0)
                        exit(0);
                if (strcmp(t1, "search\0") == 0)
                        search(t2[0], t3, t4);
                else if ((pid = fork()) == 0)
                        switch (n)
                        {
                        case 1:
                                execlp(t1, t1, (char *)0);
                                break;
                        case 2:
                                execlp(t1, t1, t2, (char *)0);
                                break;
                        case 3:
                                execlp(t1, t1, t2, t3, (char *)0);
                                break;
                        }
                else
                        waitpid(-1, &status, 0);
        }
}