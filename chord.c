#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define M 5              
#define MAX_NODES 32

typedef struct Node {
    int id;                     
    struct Node* successor;     
    struct Node* predecessor;  
    struct Node* finger[M];   
} Node;

Node* nodes[MAX_NODES];
int nodeCount = 0;

Node* createNode(int id) {
    Node* n = (Node*)malloc(sizeof(Node));
    n->id = id;
    n->successor = n;
    n->predecessor = NULL;
    for (int i = 0; i < M; i++) n->finger[i] = n;
    nodes[nodeCount++] = n;
    return n;
}

//Kiểm tra value có nằm trong khoảng (start, end] hay không
int inInterval(int value, int start, int end, int inclusive) {
    if (start < end) {
        if (inclusive)
            return (value > start && value <= end);
        else
            return (value > start && value < end);
    } else { // vòng tròn modulo
        if (inclusive)
            return (value > start || value <= end);
        else
            return (value > start || value < end);
    }
}

Node* findSuccessor(Node* n, int id) {
    Node* pred = n;
    while (!inInterval(id, pred->id, pred->successor->id, 1)) {
        // tìm finger gần nhất trước id
        int found = 0;
        for (int i = M-1; i >= 0; i--) {
            if (inInterval(pred->finger[i]->id, pred->id, id, 0)) {
                pred = pred->finger[i];
                found = 1;
                break;
            }
        }
        if (!found) pred = pred->successor;
    }
    return pred->successor;
}

void initFingerTable(Node* newNode, Node* existing) {
    newNode->finger[0] = findSuccessor(existing, (newNode->id + 1) % (1<<M));
    newNode->successor = newNode->finger[0];
    newNode->predecessor = newNode->successor->predecessor;
    newNode->successor->predecessor = newNode;

    for (int i = 0; i < M-1; i++) {
        int start = (newNode->id + (1<<(i+1))) % (1<<M);
        if (inInterval(start, newNode->id, newNode->finger[i]->id, 1))
            newNode->finger[i+1] = newNode->finger[i];
        else
            newNode->finger[i+1] = findSuccessor(existing, start);
    }
}

void join(Node* newNode, Node* existing) {
    if (existing) {
        initFingerTable(newNode, existing);
    } else {
        for (int i = 0; i < M; i++)
            newNode->finger[i] = newNode;
        newNode->successor = newNode;
        newNode->predecessor = newNode;
    }
}

void printNode(Node* n) {
    printf("Node %d -> successor=%d, predecessor=%d\n",
        n->id,
        n->successor->id,
        n->predecessor ? n->predecessor->id : -1);
}
