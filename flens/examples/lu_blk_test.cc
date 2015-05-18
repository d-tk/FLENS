#include <flens/flens.cxx>
#include <algorithm>
#include <iostream>

#ifdef WITH_OPERATORS
#   include <flens/examples/lu/lu_blk_with_operators.h>
#else
#   include <flens/examples/lu/lu_blk_with_flensblas.h>
#endif

#include <flens/examples/lu/check_lu.h>
#include <flens/examples/lu/timer.h>

using namespace flens;
using namespace std;

int
main()
{
    const int m  = 2000;
    const int n  = 2000;
    const int mn = std::min(m, n);

    GeMatrix<FullStorage<double> >  A(m,n), A_org;
    DenseVector<Array<int> >        p(mn);
    Underscore<int>                 _;

    fillRandom(A);

    // store original A for checking the factorization later
    A_org = A;

    double t0 = ATL_walltime();
    if (lu_blk(A, p) != 0) {
        cout << "Matrix is singular or close to singular" << endl;
        return 1;
    }
    t0 = ATL_walltime() - t0;

    cout << "Time elapsed: " << t0 << endl;

    cout << "Checking results:" << endl;
    cout << "|| A-P*L*U ||_1 = " << check_LU(A_org, A, p) << endl;
    return 0;
}