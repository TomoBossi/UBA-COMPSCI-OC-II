#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <assert.h>

#include "checkpoints.h"

void strPrint2(char* a, FILE* pFile) {
    if (a != NULL && pFile != NULL) {
        fputs(a, pFile);
    }
}

int main (void){
    // Checkpoint 2
	assert(alternate_sum_4(8,2,5,1) == 10);	

    assert(alternate_sum_4_using_c(8,2,5,1) == 10);

    assert(alternate_sum_4_simplified(8,2,5,1) == 10);

    assert(alternate_sum_8(1,1,1,1,1,1,5,3) == 2);

    uint32_t *res2 = malloc(sizeof(uint32_t));
    product_2_f(res2, 5, 2.5);
    assert(*res2 == 12);
    free(res2);

    double *res9 = malloc(sizeof(double));
    product_9_f(res9, 5, 2.5, 2, 3.12, 3, 0.49, 4, 0.39, 5, 0.88, 6, 0.42, 7, 0.3, 8, 0.2, 9, 1.3);
    assert(*res9 < 77967.73037813758 + 0.1 && *res9 > 77967.73037813758 - 0.1);
    free(res9);

    // Checkpoint 3

    // Checkpoint 4
    assert(strLen("") == 0);
    assert(strLen("abc") == 3);

    strPrint("Hello World\n", stdout);

    strPrint("", stdout);

    FILE* outputFile = fopen("output_file.txt", "w");
    strPrint("Hello File\n", outputFile);
    fclose(outputFile);

	return 0;
}
