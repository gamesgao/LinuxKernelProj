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
        // cout << buffer << endl;
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
    // char **paths = argc > 1 ? argv + 1 : dot;

    FTS *tree = fts_open(paths, FTS_NOCHDIR, 0);
    if (!tree)
    {
        perror("fts_open");
        return;
    }

    FTSENT *node;
    int test2 = 0;
    int pid = 0;
    system("clear");
    cout << "pid\tctx" << endl;
    while ((node = fts_read(tree)))
    {

        if (node->fts_level > 0 && node->fts_name[0] == '.')
            fts_set(tree, node, FTS_SKIP);
        else if (node->fts_info & FTS_D && node->fts_level == 1)
        {
            fts_set(tree, node, FTS_SKIP);
            test2++;
            // printf("got file named %s at depth %d, "
            //     "accessible via %s from the current directory "
            //     "or via %s from the original starting directory\n",
            //     node->fts_name, node->fts_level,
            //     node->fts_accpath, node->fts_path);
            /* if fts_open is not given FTS_NOCHDIR,
             * fts may change the program's current working directory */

            sscanf(node->fts_name, "%d", &pid);
            if (pid != 0)
                cout << pid << "\t" << getCtx(pid) << endl;
        }
    }
    // if (errno) {
    //     perror("fts_read");
    //     return 1;
    // }

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
        printCtx();
        sleep(1);
    }

    return 0;
}