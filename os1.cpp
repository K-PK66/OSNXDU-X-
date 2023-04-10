#include <fstream>
#include <unistd.h>
#include <stdio.h>
#include <iostream>
using namespace std;
int main()
{
    int flag = 0;
    string answer = "";
    auto x = vfork();
    if (!x)
    {
        ifstream in("os1.in");
        in >> answer;
        in.close();
        flag = 1;
        cout << "End of Child Process" << endl;
    }
    else
    {
        while (!flag)
            ;
        cout << "Start of Main Process" << endl;
        cout << answer << endl;
        cout << "End of Main Process" << endl;
    }
    return EXIT_SUCCESS;
}
