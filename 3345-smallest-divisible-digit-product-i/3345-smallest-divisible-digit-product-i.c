int smallestNumber(int n, int t) {
    while (1)
    {
        int x = n;
        int pro = (x == 0) ? 0 : 1;

        while (x != 0)
        {
            pro *= (x % 10);
            x /= 10;
        }

        if (pro % t == 0)
            return n;

        n++;
    }
}