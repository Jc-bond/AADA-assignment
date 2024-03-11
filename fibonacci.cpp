#include <bits/stdc++.h>

using namespace std;

int fibonacci(int n)
{
    int rec[n + 1] = {-1};
    rec[0] = 0;
    rec[1] = 1;
    for (int i = 2; i <= n; i++)
    {
        rec[i] = rec[i - 1] + rec[i - 2];
    }
    return rec[n];
}

int fib(int n)
{
    if (n == 0 || n == 1)
    {
        return n;
    }
    return fib(n - 1) + fib(n - 2);
}

int fib_R(int n)
{
    if (n == 0 || n == 1)
        return n;
    return fib_R(n - 1) + fib_R(n - 2);
}

int main()
{
    int a = fib_R(5);
    cout << a << endl;
}