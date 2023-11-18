// Lucas Mateus de Moraes - RA: 22.220.004-0

#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

#define MAX_CHILDREN 2
#define MAX_VALUE 100
#define MAX_NODES 1000

typedef struct {
    double value;
    int num_children;
    int children[MAX_CHILDREN];
} Node;

typedef struct {
    double sum;
    int path[MAX_NODES];
    int pathLength;
} Result;

Result computePaths(Node* tree, int idx) {
    Result res = {0, {0}, 0};

    if (idx == -1) return res;

    if (tree[idx].num_children == 0) {
        res.sum = tree[idx].value;
        res.path[res.pathLength++] = idx;
        return res;
    }

    double maxSum = -1;
    Result maxChildRes;

    #pragma omp parallel for
    for (int i = 0; i < tree[idx].num_children; ++i) {
        Result childRes = computePaths(tree, tree[idx].children[i]);
        #pragma omp critical
        {
            if (childRes.sum > maxSum) {
                maxSum = childRes.sum;
                maxChildRes = childRes;
            }
        }
    }

    #pragma omp critical
    {
        res.sum = tree[idx].value + maxSum;
        res.pathLength = maxChildRes.pathLength + 1;
        res.path[0] = idx;
        for (int i = 0; i < maxChildRes.pathLength; ++i) {
            res.path[i + 1] = maxChildRes.path[i];
        }
    }

    return res;
}

int main(int argc, char** argv) {
    // printf("Compilou\n");

    int N;
    scanf("%d", &N);

    Node* tree = (Node*)malloc(N * sizeof(Node));
    for (int i = 0; i < N; ++i) {
        scanf("%lf %d", &tree[i].value, &tree[i].num_children);
        for (int j = 0; j < tree[i].num_children; ++j) {
            scanf("%d", &tree[i].children[j]);
            tree[i].children[j]--; 
        }
    }

    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    Result localRes = computePaths(tree, 0);
    Result globalRes;

    MPI_Barrier(MPI_COMM_WORLD);

    MPI_Reduce(&localRes.sum, &globalRes.sum, 1, MPI_DOUBLE, MPI_MAX, 0, MPI_COMM_WORLD);
    MPI_Reduce(localRes.path, globalRes.path, MAX_NODES, MPI_INT, MPI_MAX, 0, MPI_COMM_WORLD);
    MPI_Reduce(&localRes.pathLength, &globalRes.pathLength, 1, MPI_INT, MPI_MAX, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        printf("Max Sum: %.2lf\n", globalRes.sum);
        printf("Path (size - %d): ", globalRes.pathLength);
        for (int i = 0; i < globalRes.pathLength; ++i) {
            printf("%d ", globalRes.path[i] + 1);
        }
        printf("\n");
    }

    free(tree);
    MPI_Finalize();
    return 0;
}


