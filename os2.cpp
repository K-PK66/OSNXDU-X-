#include <thread>
#include <mutex>
#include <bits/stdc++.h>
#include <unistd.h>
using namespace std;
static int sample = 1;
static int n = 20;
mutex mutx;
void thread1(int n)
{
    while (sample <= n)
    {
        if (mutx.try_lock())
        {
            cout << "Thread1 = " << sample << "\n";
            sleep(10);
            sample++;
            mutx.unlock();
        }
    }
}
int main()
{
    thread t1(thread1, n);
    while (sample <= n)
    {
        if (mutx.try_lock())
        {
            cout << "MainThread = " << sample << "\n";
            sample++;
            mutx.unlock();
        }
    }
    return 0;
}
