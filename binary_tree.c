#include <stdio.h>
#include <stdlib.h>

struct nodetype {
    int info;
    struct nodetype *left;
    struct nodetype *right;
};
typedef struct nodetype *NODEPTR;
typedef struct nodetype NODE;

NODEPTR maketree(int);
void intrav(NODEPTR);
NODEPTR get_treenode();
void setbintree(NODEPTR, int);

NODEPTR ndptr;
NODE nd;
NODEPTR current_ptr;
NODE current_nd;

int main() {
    NODEPTR btree = NULL;
    int number;
    printf("please enter the next node info: ");
    scanf("%d", &number);
    btree = maketree(number);
    printf("please enter the next node info: ");
    while (scanf("%d", &number) != EOF) {
        setbintree(btree, number);
        printf("please enter the next node info: ");
    }
    printf("\n\ninordered binary tree node info:\n");
    intrav(btree);
    printf("\nend of inordered binary tree node search\n");
}

void intrav(NODEPTR tree) {
    if (tree != NULL) {
        intrav(tree->left);
        printf("%d\n", tree->info);
        intrav(tree->right);
    }
}

NODEPTR get_treenode() {
    NODEPTR p;
    p = (NODEPTR) malloc(sizeof(struct nodetype));
    return p;
}

NODEPTR maketree(int x) {
    NODEPTR p;
    p = get_treenode();
    p->info = x;
    p->left = NULL;
    p->right = NULL;
    return p;
}

void setbintree(NODEPTR p, int x) {
    NODEPTR s = p;
    while (s != NULL) {
        if (s->info == x) {
            printf("\nduplicate entry\n");
            return;
        }
        if (s->info > x)
            if (s->left == NULL) {
                s->left = maketree(x);
                return;
            }
            else
                s = s->left;
        else if (s->right == NULL) {
            s->right = maketree(x);
            return;
        }
        else
            s = s->right;
    }
}
