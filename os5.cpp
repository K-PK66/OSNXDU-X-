#include <unistd.h>
#include <sys/stat.h>
#include <cstring>
#include <iostream>
#include <fstream>

#define PATH "/tmp/tmp_fifo.tmp"

using namespace std;

int main()
{
    auto r = mkfifo(PATH, S_IFIFO | 0666);
    auto x = fork();
    if (x == 0)
    {
        ofstream out(PATH);
        for (int i = 1; i <= 10; i++)
        {
            out << i << "\n"
                << flush;
            cout << "Child " << getpid() << " write " << i << "\n";
            sleep(1);
        }
        out << "Fin.\n"
            << flush;
        cout << "Child ends!\n";
    }
    else
    {
        ifstream in(PATH);
        string s;
        while (getline(in, s) and s != "Fin.")
        {
            cout << "Father " << getpid() << " read " << s << "\n";
        }
        cout << "Father ends!\n";
    }
}
