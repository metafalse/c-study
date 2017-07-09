/******************************************************************************/
/*                                                                            */
/*  Topic: BTrees                                                             */
/*                                                                            */
/*  Objective: Read the input values from an input file                       */
/*             and insert the values into a BTree node                        */
/*             and traverse it and print the values in an output file         */
/*                                                                            */
/*  Comments:                                                                 */
/*                                                                            */
/******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdarg.h>

#define MAX 4
#define MIN 2
#define TRUE 1
#define FALSE 0
#define INFILENAME "input14.doc"
#define OUTFILENAME "output14.doc"

struct btreeNode {
    int val[MAX + 1], count;
    struct btreeNode *link[MAX + 1];
};

void insert(int);
bool setValueInNode(int, struct btreeNode *, struct btreeNode **);
void addValToNode(int, int, struct btreeNode *, struct btreeNode *);
void splitNode(int, int, struct btreeNode *, struct btreeNode *, struct btreeNode **);
void intrav(struct btreeNode *);
int pfprintf(FILE *, const char *, ...);

FILE *pIn, *pOut;
struct btreeNode *root;
int *pval;

int main() {
    int data;

    // open input and output file
    if ((pIn = fopen(INFILENAME, "r")) == NULL) {
        printf("%s could not be opend\n", INFILENAME);
        return -1;
    }
    if ((pOut = fopen(OUTFILENAME, "w")) == NULL) {
        printf("%s could not be opend\n", OUTFILENAME);
        return -1;
    }

    while (fscanf(pIn, "%d", &data) != EOF)
        insert(data);

    pfprintf(pOut, "The Data after insert in inorder traversal\n");
    intrav(root);
    pfprintf(pOut, "\n");

    fclose(pIn);
    fclose(pOut);
}

void insert(int val) {
    printf("insert val:%d\n", val);
    int i;
    struct btreeNode *child, *newNode;
    pval = &i;

    if (!setValueInNode(val, root, &child))
        return;

    newNode = (struct btreeNode *) malloc(sizeof(struct btreeNode));
    newNode->val[1] = i;
    newNode->count = 1;
    newNode->link[0] = root;
    newNode->link[1] = child;
    root = newNode;
}

bool setValueInNode(int val, struct btreeNode *node, struct btreeNode **child) {
    printf("setValueInNode val:%d *node:%p **child:%p\n", val, node, child);
    int pos;

    if (!node) {
        *pval = val;
        *child = NULL;
        return TRUE;
    }

    if (val < node->val[1])
        pos = 0;
    else {
        for (pos = node->count; val < node->val[pos] && pos > 1; pos--);
        if (val == node->val[pos])
            return FALSE;
    }

    if (setValueInNode(val, node->link[pos], child)) {
        if (node->count < MAX)
            addValToNode(*pval, pos, node, *child);
        else {
            splitNode(*pval, pos, node, *child, child);
            return TRUE;
        }
    }
    return FALSE;
}

void addValToNode(int val, int pos, struct btreeNode *node, struct btreeNode *child) {
    printf("addValToNode val:%d pos:%d *node:%p *child:%p\n", val, pos, node, child);
    int i = node->count;

    while (i > pos) {
        node->val[i + 1] = node->val[i];
        node->link[i + 1] = node->link[i];
        i--;
    }
    node->val[i + 1] = val;
    node->link[i + 1] = child;
    node->count++;
}

void splitNode(int val, int pos, struct btreeNode *node, struct btreeNode *child, struct btreeNode **newNode) {
    printf("splitNode val:%d pos:%d *node:%p *child:%p **newNode:%p\n", val, pos, node, child, newNode);
    int median, i;

    median = pos > MIN ? MIN + 1 : MIN;

    *newNode = (struct btreeNode *)malloc(sizeof(struct btreeNode));
    i = median + 1;
    while (i <= MAX) {
        (*newNode)->val[i - median] = node->val[i];
        (*newNode)->link[i - median] = node->link[i];
        i++;
    }
    node->count = median;
    (*newNode)->count = MAX - median;

    if (pos <= MIN)
        addValToNode(val, pos, node, child);
    else
        addValToNode(val, pos - median, *newNode, child);

    *pval = node->val[node->count];
    (*newNode)->link[0] = node->link[node->count];
    node->count--;
}

void intrav(struct btreeNode *node) {
    if (!node)
        return;

    int i;
    for (i = 0; i < node->count; i++) {
        intrav(node->link[i]);
        pfprintf(pOut, "%d ", node->val[i + 1]);
    }
    intrav(node->link[i]);
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
