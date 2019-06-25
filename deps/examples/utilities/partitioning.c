#include <assert.h>
#include <inform/utilities.h>
#include <stdio.h>

void print_partitioning(size_t *part, size_t n)
{
    for (size_t i = 0; i < n; ++i) printf("%ld ", part[i]);
    printf("\n");
}

int main()
{
    {
        size_t const size = 3;

        size_t *part = inform_first_partitioning(size);
        size_t npart = 1;

        print_partitioning(part, size);
        while ((npart = inform_next_partitioning(part, size)))
        {
            print_partitioning(part, size);
        }
    }

    {
        size_t const size = 9;
        size_t *part = inform_first_partitioning(size);
        size_t npart = 1, bell_number = 1;
        while ((npart = inform_next_partitioning(part,size)))
        {
            bell_number += 1;
        }
        assert(bell_number == 21147);
        printf("%ld\n", bell_number);
    }
}
