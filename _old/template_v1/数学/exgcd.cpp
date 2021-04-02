void exgcd(int a, int b, int g, int &x, int &y) {
    if (b == 0) {
        x = 1, y = 0;
        g = a;
    } else {
        exgcd(b, a % b, g, y, x);
        y -= x * (a / b);
    }
}
