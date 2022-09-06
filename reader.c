#include "shell.h"
#include <stdio.h> 
#include <stdlib.h>
#include <errno.h>
#include <string.h>

char *read_cmd(void)
{
    char buff[1024];
    char *ptr = NULL;
    char ptrlen = 0;

    while(fgets(buff, 1024, stdin))
    {
        int bufflen = strlen(buff);

        if(!ptr)
        {
            ptr = malloc(bufflen+1);
        }
        else
        {
            char *ptr2 = realloc(ptr, ptrlen+bufflen+1);

            if(ptr2)
            {
                ptr = ptr2;
            }
            else
            {
                free(ptr);
                ptr = NULL;
            }
        }

        if(!ptr)
        {
            fprintf(stderr, "error: failed to alloc buffer: %s\n", strerror(errno));
            return NULL;
        }

        strcpy(ptr+ptrlen, buff);

        if(buff[bufflen-1] == '\n')
        {
            if(bufflen == 1 || buff[bufflen-2] != '\\')
            {
                return ptr;
            }

            ptr[ptrlen+bufflen-2] = '\0';
            bufflen -= 2;
            print_prompt2();
        }

        ptrlen += bufflen;
    }
    return ptr;
}