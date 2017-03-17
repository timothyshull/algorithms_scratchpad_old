#include <cmath>
#include <iostream>
#include <cstdlib>
#include "Point.h"

struct node {
    point p;
    node *next;

    node(point pt, node *t) {
        p = pt;
        next = t;
    }
};

typedef node *link;

static link **grid;
static int G;
static int cnt = 0;
static float d;

void gridinsert(float x, float y) {
    int X = (int) (x * G + 1);
    int Y = (int) (y * G + 1);
    point p;
    p.x = x;
    p.y = y;
    link s;
    link t = new node(p, grid[X][Y]);

    for (int i = X - 1; i <= X + 1; i++) {
        for (int j = Y - 1; j <= Y + 1; j++) {
            for (s = grid[i][j]; s != 0; s = s->next) {
                if (distance(s->p, t->p) < d) {
                    cnt++;
                }
            }
        }
    }
    grid[X][Y] = t;
}

// included from 3.16
int **malloc2d(int r, int c) {
    int **t = new int *[r];

    for (int i = 0; i < r; i++) {
        t[i] = new int[c];
    }

    return t;
}

// included from 3.8
float randFloat() {
    return (float) (1.0 * rand() / RAND_MAX);
}

int main(int argc, char *argv[]) {
    int i;
    int N = atoi(argv[1]);
    d = (float) atof(argv[2]);
    G = (int) (1 / d);
    grid = (link **) malloc2d(G + 2, G + 2);

    for (i = 0; i < G + 2; i++) {
        for (int j = 0; j < G + 2; j++) {
            grid[i][j] = 0;
        }
    }

    for (i = 0; i < N; i++) {
        gridinsert(randFloat(), randFloat());
    }
    std::cout << cnt << " pairs within " << d << "\n";

    return 0;
}