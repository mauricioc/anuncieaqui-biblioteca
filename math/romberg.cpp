long double romberg(long double a, long double b,
                    long double(*func)(long double)) {
    long double R[16][16], div = (b-a)/2;

    R[0][0] = div * (func(a) + func(b));
    for(int n = 1; n <= 15; n++, div /= 2) {
        R[n][0] = R[n-1][0]/2;
        for(long double sample = a + div; sample < b; sample += 2 * div)
            R[n][0] += div * func(a + sample);
    }

    for(int m = 1; m <= 15; m++)
        for(int n = m; n <= 15; n++)
            R[n][m] = R[n][m-1] + 1/(pow(4, m)-1) * (R[n][m-1] - R[n-1][m-1]);

    return R[15][15];
}
