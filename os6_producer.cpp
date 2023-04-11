#include <sys/ipc.h>
#include <sys/shm.h>
#include <bits/stdc++.h>
#include <semaphore.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
using namespace std;
const int limit = 100;

int shmid;
char *p;

union sample
{
    sem_t sem;
    long long tmp;
};

sample *sem_input;
sample *sem_output;

void init()
{
    shmid = shmget((key_t)0x2333, 1024, 0666 | IPC_CREAT);
    if (shmid == -1)
        cout << "Create shared memory failed.\n", exit(-1);
    p = (char *)shmat(shmid, 0, 0);
    memset(p, 0, 1024);

    sem_input = new (p) sample;
    if (sem_init(&(sem_input->sem), 1, limit) < 0)
        cout << "Create sem_input failed\n", exit(-1);
    p += sizeof(sem_input);
    p += 32;
    cout << sem_input->tmp << "\n";

    sem_output = new (p) sample;
    if (sem_init(&(sem_output->sem), 1, 0) < 0)
        cout << "Create sem_output failed\n", exit(-1);
    p += sizeof(sem_output);
    p += 32;
    cout << sem_output->tmp << "\n";
}

int main()
{
    init();
    srand(time(NULL));
    while (true)
    {
        cout << sem_input->tmp << " " << sem_output->tmp << "\n";
        sem_wait(&(sem_input->sem));
        for (int i = 0; i < limit; i++)
            if (p[i] == 0)
            {
                p[i] = rand() % 26 + 'a';
                cout << "Producer make a '" << p[i] << "' on " << i << ".\n";
                sem_post(&(sem_output->sem));
                sleep(log(rand()) / 25.0);
                break;
            }
    }
}
