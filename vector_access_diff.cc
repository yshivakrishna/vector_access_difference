#include<iostream>
#include<sys/time.h>
#include<mmintrin.h>
#include<xmmintrin.h>
#include<immintrin.h>
using namespace std;

#ifndef NUM_REPEATS
#define NUM_REPEATS 100000
#endif

typedef unsigned long long ticks;

static __inline__ ticks getticks(void)
{
    unsigned a, d;
    __asm volatile("rdtsc" : "=a" (a), "=d" (d)::"memory");
    return (((ticks)a) | (((ticks)d) << 32));
}

volatile uint32_t array[]  __attribute__ ((aligned (64))) ={1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16};
volatile uint32_t array2[]  __attribute__ ((aligned (64))) ={1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16};
volatile uint32_t array3[]  __attribute__ ((aligned (64))) ={1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16};
int main()
{
    __m128i temp1, temp2, temp3, temp4;
    /* Access once before the critical loop to remove the overhead of fpu fault */
    temp1 = *(__m128i*)array;
    temp2 = *(__m128i*)(array + 4);
    temp3 = *(__m128i*)(array+8);
    temp4 = *(__m128i*)(array+12);
    int x = 0, y = 1;
    volatile auto a = getticks();
    for (int j = 0; j < NUM_REPEATS; j++) {
#ifdef MEASURE_INT
        for (int i = 0; i < 16; i++) {
            x = array[i];
            y = array2[i];
            //array2[i] = x;
            //array3[i] = x;
        }
#else
        temp1 = *(__m128i*)array;
        temp2 = *(__m128i*)(array + 4);
        temp3 = *(__m128i*)(array+8);
        temp4 = *(__m128i*)(array+12);
        temp1 = *(__m128i*)array2;
        temp2 = *(__m128i*)(array2 + 4);
        temp3 = *(__m128i*)(array2+8);
        temp4 = *(__m128i*)(array2+12);
#endif
    }
    volatile auto b = getticks();
    cout<<"numticks ="<<(b-a)/NUM_REPEATS<<endl;
}
