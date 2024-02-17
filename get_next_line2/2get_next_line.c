#include "get_next_line.h"
#include <stddef.h>
#include <fcntl.h>
size_t  ft_strlen(const char *str)
{
    size_t  size;

    size = 0;
    while (*str++)
        size++;
    return (size);
}

char    *ft_strdup(const char *s) 
{
    char    *s2;
    int     n;  
    int     i;  

    i = 0;
    n = ft_strlen(s) ;
    if (!n)
        return (NULL);
    s2 = malloc(n +1 * sizeof(const char));
    if (!s2)
        return (NULL);
    while (s[i])
    {
        s2[i] = s[i];
        i++;
    }   
    s2[i] = '\0';
    return (s2);
}

void    *ft_memchr(const void *buf,  size_t n )
{
    int c;

    c = '\n';
    while (n--)
    { 
        if (*(char *)(buf) == (char)c)
            return ((void *)(buf));
        buf++;
    }
    return (0);
}



int main()
{
    int     fd;
    char    *buf;
    static char    *nxtbuf;
    int     n_rd;
    ptrdiff_t nl_ptr;

    fd = open("file.txt", O_RDONLY);
    n_rd = BUFFER_SIZE + 1;
    buf = malloc(sizeof(char) * BUFFER_SIZE + 1 );
    while (n_rd >= BUFFER_SIZE)
    {
        nxtbuf = NULL;//malloc(sizeof(buf));
        n_rd = read(fd, buf, BUFFER_SIZE);
        nl_ptr = (char *)ft_memchr(buf,  BUFFER_SIZE);
        //printf(":%i:",-(int)(buf - nl_ptr));
        if (!nl_ptr)
            buf[n_rd] = '\0';
        else
        {
            nxtbuf = ft_strdup(nl_ptr);
            buf[-(int)(buf - nl_ptr)] = '\0';
        }
        if (!n_rd)
        {
            free(buf);
            free(nxtbuf);
        }     
        // printf()
        if (buf)
            printf(":%s:", buf);
        if (nxtbuf)
            printf(";%s;", nxtbuf);
    }

}
