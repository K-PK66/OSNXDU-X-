#include <unistd.h>
#include <bits/stdc++.h>
using namespace std;

int main()
{
    auto fa = getpid();
    int _pipeline[2];
    int ret = pipe(_pipeline);
    if (ret < 0)
    {
        cout << "Pipeline error!\n";
        return 0;
    }
    auto x = fork();
    if (x == 0)
    {
        close(_pipeline[1]);
        char s[100];
        memset(s, '\0', sizeof(s));
        read(_pipeline[0], s, sizeof(s));
        cout << "fa : " << getpid() << " reading " << s << "\n";
    }
    else
    {
        close(_pipeline[0]);
        char *msg = NULL;
        msg = "TestMessage";
        write(_pipeline[1], msg, strlen(msg));
        cout << "ch : " << getpid() << " Write success!\n";
    }
    return 0;
}