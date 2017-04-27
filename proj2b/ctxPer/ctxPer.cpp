#include <iostream>
#include <fstream>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

using namespace std;

int getCtx(long pid)
{
    char *buffer = 0;
    ifstream fin;
    char *ptr = 0;
    int result = 0;
    char path[20];
    sprintf(path, "/proc/%ld/ctx", pid);
    buffer = new char[80];
    fin.open(path);
    if (fin)
    {
        fin.getline(buffer, 80, '\n');
    }
    else
    {
        cout << "gg" << endl;
        fin.close();
        return 0;
    }
    fin.close();
    ptr = buffer;
    while (*ptr++ != '\0')
    {
        if (*ptr >= '0' && *ptr <= '9')
        {
            result = result * 10 + *ptr - '0';
        }
    }
    delete buffer;
    return result;
}



int main(int argc, char *argv[])
{
    long pid;
    pid = atoi(argv[1]);
    while (true)
    {
        system("clear");
        cout << "pid\tctx" << endl;
        cout << pid << "\t" << getCtx(pid) << endl;
        sleep(1);
    }

    return 0;
}