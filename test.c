#include "chord.c"

int main() {
    Node* n0 = createNode(5);
    join(n0, NULL);

    Node* n1 = createNode(12);
    join(n1, n0);

    Node* n2 = createNode(25);
    join(n2, n0);

    Node* n3 = createNode(31);
    join(n3, n0);

    printf("===== Thông tin các node =====\n");
    for (int i = 0; i < nodeCount; i++) {
        printNode(nodes[i]);
    }

    printf("\n===== Tra cứu key =====\n");
    int keys[] = {7, 3, 20, 30};
    char* keyNames[] = {"apple", "banana", "chord", "distributed"};

    for (int i = 0; i < 4; i++) {
        Node* owner = findSuccessor(n0, keys[i]);
        printf("Key '%s' (id=%d) -> Node %d\n", keyNames[i], keys[i], owner->id);
    }
    return 0;
}
