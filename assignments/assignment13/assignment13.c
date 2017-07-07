/******************************************************************************/
/*                                                                            */
/*  Topic: Binary Trees                                                       */
/*                                                                            */
/*  Objective: Read the input values from the input file                      */
/*             and insert the values into a binary tree node                  */
/*             and traverse it and print the values in an output file         */
/*                                                                            */
/*  Comments: The code in chapter 26 modified to make it work as desired      */
/*                                                                            */
/******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdarg.h>

#define MAXSTACK 100
#define DEFAULT 9999
#define EMPTYSTACK -1
#define TRUE 1
#define FALSE 0
#define INFILENAME "input13.doc"
#define OUTFILENAME "output13.doc"

struct nodetype {
    int info;
    struct nodetype *left;
    struct nodetype *right;
};
typedef struct nodetype *NODEPTR;
typedef struct nodetype NODE;

typedef struct stack {
	struct nodetype *tree;
	struct stack *next;
} NODESTACK;

bool isValidInput(int);
void intrav(NODEPTR);
void intravnr(NODEPTR);
void pretrav(NODEPTR);
void pretravnr(NODEPTR);
void postrav(NODEPTR);
void postravnr(NODEPTR);
NODEPTR get_treenode();
NODEPTR maketree(int);
void setbintree(NODEPTR, int);
bool deletenode(NODEPTR, int);
void push(NODESTACK **, NODEPTR);
NODEPTR pop(NODESTACK **);
NODEPTR peek(NODESTACK **);
int pfprintf(FILE *, const char *, ...);

FILE *pIn, *pOut;
NODESTACK *nodestack = NULL;

int main() {
    NODEPTR btree = NULL;
    int number;

    // open input and output file
    if ((pIn = fopen(INFILENAME, "r")) == NULL) {
        printf("%s could not be opend\n", INFILENAME);
        return -1;
    }
    if ((pOut = fopen(OUTFILENAME, "w")) == NULL) {
        printf("%s could not be opend\n", OUTFILENAME);
        return -1;
    }

    // scan values from input file into binary tree
    if (fscanf(pIn, "%d", &number) == EOF) {
        pfprintf(pOut, "input file is empty");
        exit(1);
    }
    btree = maketree(number);
    while (fscanf(pIn, "%d", &number) != EOF)
        setbintree(btree, number);

    // traverse the tree in some way and print the results
    pfprintf(pOut, "Traverse the tree in inorder recursively\n");
    intrav(btree);
    pfprintf(pOut, "\nTraverse the tree in inorder non-recursively\n");
    intravnr(btree);
    pfprintf(pOut, "\nTraverse the tree in preorder recursively\n");
    pretrav(btree);
    pfprintf(pOut, "\nTraverse the tree in preorder non-recursively\n");
    pretravnr(btree);
    pfprintf(pOut, "\nTraverse the tree in postorder recursively\n");
    postrav(btree);
    pfprintf(pOut, "\nTraverse the tree in postorder non-recursively\n");
    postravnr(btree);
    pfprintf(pOut, "\n");

    while (btree != NULL) { // until the tree is empty
        // prompt user to enter a value to be deleted from the tree or quit
        do {
            number = DEFAULT;
            pfprintf(pOut, "Enter a character to be deleted or -1 to quit: ");
            scanf(        "%d",  &number);
            fprintf(pOut, "%d\n", number);
            while (getchar() != '\n')
                continue;
        } while (!isValidInput(number));

        if (number == -1)
            break;

        if (deletenode(btree, number))
            pfprintf(pOut, "%d deleted.\n", number);
        else
            pfprintf(pOut, "%d not found.\n", number);

        // the tree contents in inorder after deleting
        pfprintf(pOut, "Traverse the tree in inorder recursively\n");
        intrav(btree);
        pfprintf(pOut, "\n");
    }

    fclose(pIn);
    fclose(pOut);
}

bool isValidInput(int number) {
    if (number != DEFAULT)
        return TRUE;

    pfprintf(pOut, "invalid input\n");
    return FALSE;
}

void intrav(NODEPTR tree) {
    if (tree == NULL)
        return;

    intrav(tree->left); // traverse the left subtree
    pfprintf(pOut, "%d ", tree->info); // visit the node
    intrav(tree->right); // traverse the right subtree
}

void intravnr(NODEPTR tree) {
    NODEPTR curr = tree;
    NODESTACK *s = NULL;

    while (TRUE) {
        if (curr != NULL) {
            push(&s, curr);
            curr = curr->left;
        }
        else if (s != NULL) {
            curr = pop(&s);
            pfprintf(pOut, "%d ", curr->info);
            curr = curr->right;
        }
        else
            break;
    }
}

void pretrav(NODEPTR tree) {
    if (tree == NULL)
        return;

    pfprintf(pOut, "%d ", tree->info); // visit the node
    pretrav(tree->left); // traverse the left subtree
    pretrav(tree->right); // traverse the right subtree
}

void pretravnr(NODEPTR tree) {
    if (tree == NULL)
        return;

    NODEPTR curr = tree;
    NODESTACK *s = NULL;
    push(&s, curr);

    while (s != NULL) {
        curr = pop(&s);
        pfprintf(pOut, "%d ", curr->info);

        if (curr->right)
            push(&s, curr->right);
        if (curr->left)
            push(&s, curr->left);
    }
}

void postrav(NODEPTR tree) {
    if (tree == NULL)
        return;

    postrav(tree->right); // traverse the right subtree
    postrav(tree->left); // traverse the left subtree
    pfprintf(pOut, "%d ", tree->info); // visit the node
}

void postravnr(NODEPTR tree) {
    if (tree == NULL)
        return;

    NODEPTR prev = NULL;     
    NODESTACK *stack = NULL;
    push(&stack, tree);

    while (stack != NULL) {
        NODEPTR curr = peek(&stack);
        if (prev == NULL || prev->right == curr || prev->left == curr) {
            if (curr->right)
                push(&stack, curr->right);
            else if (curr->left)
                push(&stack, curr->left);
        } 
        else if (curr->right == prev && curr->left)
            push(&stack, curr->left);
        else {
            pfprintf(pOut, "%d ", curr->info);
            pop(&stack);
        }
        prev = curr;
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
    pfprintf(pOut, "%d is read into the tree\n", x);

    return p;
}

void setbintree(NODEPTR p, int x) {
    NODEPTR s = p;

    while (s != NULL) {
        if (s->info == x) {
            pfprintf(pOut, "%d is duplicate entry\n", x);
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

bool deletenode(NODEPTR tree, int key) {
    NODEPTR p, r, f, s, q; 
    q = NULL;
    p = tree;

    // Search for the node with the key, set p to point to the node and q to its parent, if any.
    while (p != NULL && p->info != key) {
        q = p;
        p = key < p->info ? p->left : p->right;
    }
    if (p == NULL)
        // The key does not exists in the tree, leave the tree unchanged
        return FALSE;

    // set the variable r to the node that will replace node(p). 
    // first two cases: the node to be deleted has at most one child.
    if (p->left == NULL)
        r = p->right;
    else if (p->right == NULL)
        r = p->left;
    else {
        // third case: node(p) has two children.
        // Set r to the inorder successor of p and f to the parent of r.
        f = p;
        r = p->right;
        s = r->left; // s is left child of r

        while (s != NULL) {
            f = r;
            r = s;
            s = r->left;
        }

        if (f != p) { // at this point, r is the inorder successor of p
            f->left = r->right; // p is not parent of r, set it to p->left
            r->right = p->right; // remove node r and replace
        }
        r->left = p->left; // set left child of r, r takes place of p
    }

    // insert node(r) into position formerly occupied by node(p)
    if (q == NULL) // node(p) was the root
        tree = r;
    else if (p == q->left)
        q->left = r;
    else
        q->right = r;

    free(p);
    return TRUE;
}

void push(NODESTACK **topptr, NODEPTR tree) {
    NODESTACK *newnode = (NODESTACK*) malloc(sizeof(NODESTACK));

    if (newnode == NULL) {
        pfprintf(pOut, "Stack Overflow\n");
        exit(1);
    }

    newnode->tree = tree;
    newnode->next = (*topptr);
    (*topptr) = newnode;
}

NODEPTR pop(NODESTACK **topptr) {
    NODEPTR res;
    NODESTACK *top;

    if (*topptr == NULL) {
        pfprintf(pOut, "Stack Underflow\n");
        exit(1);
	}

    top = *topptr;
    res = top->tree;
    *topptr = top->next;

    free(top);
    return res;
}

NODEPTR peek(NODESTACK **topptr) {
    NODEPTR res;
    NODESTACK *top;

    if (*topptr == NULL) {
        pfprintf(pOut, "Stack Underflow\n");
        exit(1);
    }

    return (*topptr)->tree;
}

// a function combining printf and fprintf
int pfprintf(FILE *fp, const char *format, ...) {
    va_list ap;
    int result;

    va_start(ap, format);
    result = vfprintf(fp, format, ap);
    va_end(ap);
    if (fp != stdout && fp != stderr) {
        va_start(ap, format);
        result = vprintf(format, ap);
        va_end(ap);
    }

    return result;
}
