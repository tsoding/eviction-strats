#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

double rand_double(void)
{
    return (double)rand()/RAND_MAX;
}

int main(void)
{
    srand(getpid());
    size_t loops = rand_double()*2*1000*1000*1000;
    for (size_t i = 0; i < loops; ++i);
    return 0;
}
