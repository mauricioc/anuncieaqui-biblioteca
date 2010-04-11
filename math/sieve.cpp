const unsigned MAX = 1000000020/60, MAX_S = sqrt(MAX/60);

unsigned w[16] = {1, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 49, 53, 59};
unsigned short notprime[MAX];
vector<int> primes;

void sieve() {
    unsigned mod[16][16], di[16][16];
    for(int i = 0; i < 16; i++)
        for(int j = 0; j < 16; j++) {
            di[i][j] = (w[i]*w[j])/60;
            mod[i][j] = lower_bound(w, w + 16, (w[i]*w[j])%60) - w;
        }

    primes.push_back(2); primes.push_back(3); primes.push_back(5);

    memset(notprime, 0, sizeof notprime);
    for(unsigned i = 0; i < MAX; i++)
        for(int j = (i==0); j < 16; j++) {
            if(notprime[i] & (1<<j)) continue;
            primes.push_back(60*i + w[j]);

            if(i > MAX_S) continue;
            for(unsigned k = i, done = false; !done; k++)
                for(int l = 0; l < 16 && !done; l++) {
                    unsigned mult = 60*i*k + i*w[l] + k*w[j] + di[j][l];
                    if(mult >= MAX) done = true;
                    else notprime[mult] |= 1<<mod[j][l];
                }
        }
}
