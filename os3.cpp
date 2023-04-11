#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <bits/stdc++.h>

using namespace std;

void sig_handle(int sig)
{
    cout << "Sigint get!\n";
    signal(SIGINT, SIG_DFL);
}

int main()
{
    auto fa = getpid();
    auto x = fork();
    if (getpid() == fa)
    {
        cout << "fa : " << getpid() << "\n";
        if (signal(SIGINT, sig_handle) == SIG_ERR)
        {
            cout << "ERROR!\n";
        }
        sleep(100);
    }
    else
    {
        cout << "ch : " << getpid() << "\n";
        kill(getppid(), SIGINT);
    }
}