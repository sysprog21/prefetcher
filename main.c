#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

#include <xmmintrin.h>

#define TEST_W 4096
#define TEST_H 4096

/* provide the implementations of naive_transpose,
 * sse_transpose, sse_prefetch_transpose
 */

#include "impl.c"

int main(void)
{
    /* verify the result of 4x4 matrix */
    {
        int testin[16] = { 0, 1,  2,  3,  4,  5,  6,  7,
                           8, 9, 10, 11, 12, 13, 14, 15 };
        int testout[16];

        for (int y = 0; y < 4; y++) {
            for (int x = 0; x < 4; x++)
                printf(" %2d", testin[y * 4 + x]);
            printf("\n");
        }
        printf("\n");
        sse_transpose(testin, testout, 4, 4);
        for (int y = 0; y < 4; y++) {
            for (int x = 0; x < 4; x++)
                printf(" %2d", testout[y * 4 + x]);
            printf("\n");
        }
    }

    {
        struct timeval stime, etime;
        int *src =  (int *) malloc(sizeof(int) * TEST_W * TEST_H);
        int *out0 = (int *) malloc(sizeof(int) * TEST_W * TEST_H);
        int *out1 = (int *) malloc(sizeof(int) * TEST_W * TEST_H);
        int *out2 = (int *) malloc(sizeof(int) * TEST_W * TEST_H);

        srand(time(NULL));
        for (int y = 0; y < TEST_H; y++) {
            for (int x = 0; x < TEST_W; x++)
                *(src + y * TEST_W + x) = rand();
        }

        gettimeofday(&stime, NULL);
        sse_prefetch_transpose(src, out0, TEST_W, TEST_H);
        gettimeofday(&etime, NULL);
        printf("sse prefetch: %ld us\n",
               (etime.tv_sec - stime.tv_sec) * 1000000 +
               (etime.tv_usec - stime.tv_usec));

        gettimeofday(&stime, NULL);
        sse_transpose(src, out1, TEST_W, TEST_H);
        gettimeofday(&etime, NULL);
        printf("sse: %ld us\n",
               (etime.tv_sec - stime.tv_sec) * 1000000 +
               (etime.tv_usec - stime.tv_usec));

        gettimeofday(&stime, NULL);
        naive_transpose(src, out2, TEST_W, TEST_H);
        gettimeofday(&etime, NULL);
        printf("naive: %ld us\n",
               (etime.tv_sec - stime.tv_sec) * 1000000 +
               (etime.tv_usec - stime.tv_usec));

        free(src);
        free(out0);
        free(out1);
        free(out2);
    }

    return 0;
}
