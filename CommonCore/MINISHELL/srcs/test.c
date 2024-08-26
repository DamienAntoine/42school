#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv, char **env)
{
    while (*env)
    {
        printf("%s\n", *env);
        env++;
    }
}