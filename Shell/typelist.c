#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <dirent.h>

void typeline(char *s, char *fn) {
    int i = 0, j = 0, cnt = 0, n, num;
    char c, buff[80];
    FILE *fd;

    fd = fopen(fn, "r");

    if (fd == NULL) {
        printf("file cannot be opened\n");
        return;
    }

    n = atoi(s);

    if (n == 0)
        c = 'a';
    else if (n > 0)
        c = '+';
    else
        c = '-';

    switch (c) {
        case 'a':
            while (fgets(buff, 80, fd)) {
                printf("%s", buff);
            }
            break;
        case '+':
            cnt = 0;
            while (fgets(buff, 80, fd)) {
                printf("%s", buff);
                cnt++;
                if (cnt == n)
                    break;
            }
            break;
        case '-':
            cnt = 0;
            while (fgets(buff, 80, fd)) {
                cnt++;
            }
            num = cnt + n;
            j = 0;
            fseek(fd, 0, SEEK_SET);
            while (fgets(buff, 80, fd) && j < num) {
                j++;
            }
            while (fgets(buff, 80, fd)) {
                printf("%s", buff);
            }
            break;
    }

    fclose(fd);
}

int main() {
    char buff[80], t1[20], t2[20], t3[20], t4[20];
    int n, pid, k = 0, status;

    system("clear");

    while (1) {
        printf("my_shell$");
        fflush(stdin);
        fgets(buff, 80, stdin);

        t1[0] = t2[0] = t3[0] = t4[0] = '\0';
        n = sscanf(buff, "%s%s%s%s", t1, t2, t3, t4);

        if (strcmp(t1, "exit\0") == 0) {
            exit(0);
        }

        if (strcmp(t1, "typeline\0") == 0) {
            typeline(t2, t3);
        } else if ((pid = CreateProcess()) == 0) {
            switch (n) {
                case 1:
                    execlp(t1, t2, NULL);
                    break;
                case 2:
                    execlp(t1, t2, t3, NULL);
                    break;
                case 3:
                    execlp(t1, t2, t3, t4);
                    break;
            }
        }
    }

    return 0;
}