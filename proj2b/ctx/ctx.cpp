#include <iostream>
#include <fstream>
#include <fts.h>
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

void printCtx()
{
    char *paths[] = {"/proc", 0};

    FTS *tree = fts_open(paths, FTS_NOCHDIR, 0);
    if (!tree)
    {
        perror("fts_open");
        return;
    }

    FTSENT *node;
    int test2 = 0;
    int pid = 0;
    
    cout << "pid\tctx" << endl;
    while ((node = fts_read(tree)))
    {

        if (node->fts_level > 0 && node->fts_name[0] == '.')
            fts_set(tree, node, FTS_SKIP);
        else if (node->fts_info & FTS_D && node->fts_level == 1)
        {
            fts_set(tree, node, FTS_SKIP);
            test2++;
            sscanf(node->fts_name, "%d", &pid);
            if (pid != 0)
                cout << pid << "\t" << getCtx(pid) << endl;
        }
    }
    if (fts_close(tree))
    {
        perror("fts_close");
        return;
    }
}

int main()
{
    while (true)
    {
        system("clear");
        printCtx();
        sleep(1);
    }

    return 0;
}