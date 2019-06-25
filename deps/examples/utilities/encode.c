#include <assert.h>
#include <inform/utilities.h>
#include <stdio.h>

int main()
{
    {
        inform_error err = INFORM_SUCCESS;
        int32_t code;

        code = inform_encode((int[]){1,0,0}, 3, 2, &err);
        assert(!err && code == 4);
        printf("%d\n", code);

        code = inform_encode((int[]){0,1,0}, 3, 2, &err);
        assert(!err && code == 2);
        printf("%d\n", code);

        code = inform_encode((int[]){1,0,1}, 3, 2, &err);
        assert(!err && code == 5);
        printf("%d\n", code);
    }

    {
        inform_error err = INFORM_SUCCESS;
        int32_t code;

        code = inform_encode((int[]){3,0,0}, 3, 4, &err);
        assert(!err && code == 48);
        printf("%d\n", code);

        code = inform_encode((int[]){0,3,0}, 3, 4, &err);
        assert(!err && code == 12);
        printf("%d\n", code);

        code = inform_encode((int[]){2,2,1}, 3, 4, &err);
        assert(!err && code == 41);
        printf("%d\n", code);
    }
}
