#include <stdio.h>
#include <stdatomic.h>

int test_atomic_int(int argc, char*argv[]) {
    (void)argc;
    (void)argv;
    atomic_int a = ATOMIC_VAR_INIT(0);
    atomic_store(&a, 5);
    printf("a: %d\n", atomic_load(&a));
    atomic_fetch_add(&a, 3);
    printf("a: %d\n", atomic_load(&a));
    return 0;
}