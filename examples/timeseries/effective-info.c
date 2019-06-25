#include <assert.h>
#include <stdio.h>
#include <inform/effective_info.h>

int main()
{
    {
        inform_error err = INFORM_SUCCESS;
        double const tpm[4] = {0.50,0.50,
                               0.25,0.75};

        double ei = inform_effective_info(tpm, NULL, 2, &err);
        assert(inform_succeeded(&err));
        printf("%.6lf\n", ei);
    }
    {
        inform_error err = INFORM_SUCCESS;
        double const tpm[4] = {0.50,0.50,
                               0.25,0.75};
        double const inter[2] = {0.488372, 0.511628};
        double ei = inform_effective_info(tpm, inter, 2, &err);
        assert(inform_succeeded(&err));
        printf("%.6lf\n", ei);
    }
}
