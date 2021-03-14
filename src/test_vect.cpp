#include "test_vect.h"
#include <vector>
#include <stdio.h>

void test_vect(void) {
    std::vector <int> a;
    
    a.push_back(1);
    a.push_back(2);
    a.push_back(10);

    for(int i=0;i<a.size();i++) {
        printf("%d: %d\n", a[i]);
    }

}



