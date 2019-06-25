#include <assert.h>
#include <inform/utilities.h>
#include <stdio.h>

void print_state(int const *state, size_t n)
{
    for (size_t i = 0; i < n; ++i)
    {
        printf("%d ", state[i]);
    }
    printf("\n");
}

int main()
{
    {
        inform_error err = INFORM_SUCCESS;
        int state[3];

        inform_decode(4, 2, state, 3, &err);
        print_state(state, 3);

        inform_decode(2, 2, state, 3, &err);
        print_state(state, 3);

        inform_decode(5, 2, state, 3, &err);
        print_state(state, 3);
    }

    {
        inform_error err = INFORM_SUCCESS;
        int state[3];

        inform_decode(48, 4, state, 3, &err);
        print_state(state, 3);

        inform_decode(12, 4, state, 3, &err);
        print_state(state, 3);

        inform_decode(41, 4, state, 3, &err);
        print_state(state, 3);
    }
}
