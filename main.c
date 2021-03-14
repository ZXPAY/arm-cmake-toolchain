#include <stdio.h>
#include "add.h"
#include "fpu.h"
#include "test_vect.h"

int main(void) {

    enable_fpu();

    int c = add(10, 20);
    
    float w = 1.413;
    float b = 1.2 + w;
    float d = f32_mul(b, 3.14);

    printf("Hello world !!!\n");
    printf("%f\n", b);

    test_vect();

    return 0;
}
