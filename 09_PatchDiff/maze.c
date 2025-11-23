#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 6
#define H (2*N + 1)
#define W (2*N + 1)

char maze[H][W];
int used[N][N];

int dx[4] = {1, -1, 0, 0};
int dy[4] = {0, 0, 1, -1};

void shuffle(int *a, int n) {
    for (int i = n - 1; i > 0; --i) {
        int j = rand() % (i + 1);
        int t = a[i]; a[i] = a[j]; a[j] = t;
    }
}

void dfs(int x, int y) {
    used[x][y] = 1;
    int dirs[4] = {0, 1, 2, 3};
    shuffle(dirs, 4);

    for (int i = 0; i < 4; i++) {
        int d = dirs[i];
        int nx = x + dx[d];
        int ny = y + dy[d];

        if (nx < 0 || ny < 0 || nx >= N || ny >= N) continue;
        if (used[nx][ny]) continue;

        int wx = 2*x + 1 + (nx - x);
        int wy = 2*y + 1 + (ny - y);
        maze[wx][wy] = '.';

        dfs(nx, ny);
    }
}

int main(void) {
    srand(time(NULL));

    for (int i = 0; i < H; i++)
        for (int j = 0; j < W; j++)
            maze[i][j] = '#';

    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            maze[2*i+1][2*j+1] = '.';

    dfs(0, 0);

    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++)
            putchar(maze[i][j]);
        putchar('\n');
    }
}
