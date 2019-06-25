#include <assert.h>
#include <inform/information_flow.h>
#include <stdio.h>

int main()
{
    {
        inform_error err = INFORM_SUCCESS;
        int const ws[8] = {0,0,1,0,1,1,0,1};
        int const xs[8] = {0,0,1,0,1,1,0,1};
        int const ys[8] = {0,0,1,0,1,1,0,1};
        int const zs[8] = {0,0,0,0,0,0,0,0};

        double flow = 0.0;

        flow = inform_information_flow(xs, ys, NULL, 1, 1, 0, 1, 8, 2, &err);
        assert(!err);
        printf("%.6lf\n", flow);

        flow = inform_information_flow(xs, ys, ws, 1, 1, 1, 1, 8, 2, &err);
        assert(!err);
        printf("%.6lf\n", flow);

        flow = inform_information_flow(ws, zs, ys, 1, 1, 1, 1, 8, 2, &err);
        assert(!err);
        printf("%.6lf\n", flow);
    }

    {
        inform_error err = INFORM_SUCCESS;
        int const ws[8] = {0,0,1,0,1,1,0,1};
        int const xs[8] = {0,0,1,0,1,1,0,1};
        int const ys[8] = {1,0,1,0,0,1,1,0};
        int const zs[8] = {1,0,0,0,1,0,1,1};

        double flow = 0.0;

        flow = inform_information_flow(xs, ys, NULL, 1, 1, 0, 2, 8, 2, &err);
        assert(!err);
        printf("%.6lf\n", flow);

        flow = inform_information_flow(xs, ys, ws, 1, 1, 1, 1, 8, 2, &err);
        assert(!err);
        printf("%.6lf\n", flow);

        flow = inform_information_flow(ws, zs, ys, 1, 1, 1, 1, 8, 2, &err);
        assert(!err);
        printf("%.6lf\n", flow);
    }
}
