    set<i64> prime;
    for (int i = 1; i * i <= q; i++) {
        if (i != 1 && q % i == 0) {
            prime.insert(i);
        } 
        if (q % (q / i) == 0) {
            prime.insert(q / i);
        }
    }