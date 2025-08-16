#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <unistd.h>

float rand_float(void)
{
    return (float)rand()/RAND_MAX;
}

int main()
{
    srand(getpid());
    int duration = rand_float()*500*1000;
    usleep(duration);
    return 0;
}
