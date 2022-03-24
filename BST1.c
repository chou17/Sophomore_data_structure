#include <stdio.h>
#include <stdlib.h>
#include<string.h>

typedef struct treenode{
    int num;
    struct treenode *left;
    struct treenode *right;
} treeNode;

treeNode* insert(treeNode *,int);
void print_inorder(treeNode *);
void print_level(treeNode *);


int main(){

    char input[8];
    treeNode *root = NULL;
    while(1){
        scanf("%s",input);
        if(strcmp(input,"00")==0)
            break;
        int n = atoi(input); //input to num
        root = insert(root,n); // insert to tree
    }
    printf("Infixorder: ");
    print_inorder(root);
    printf("\n");
    printf("Levelorder: ");
    print_level(root);
}


treeNode* insert(treeNode *node, int num){
    if(node == NULL) {
        treeNode *temp;
        temp = (treeNode *)malloc(sizeof(treeNode));
        temp->num = num;
        temp -> left = temp -> right = NULL;
        return temp;
    }
    int c = num - node->num;
    if(c>0) //if number > node number ,insert to right.
        node->right = insert(node->right,num);
    else if(c<0) //if number > node number ,insert to left.
        node->left = insert(node->left,num);
    return node;
}

void print_inorder(treeNode *node){  //inorder
    if(node == NULL)
        return;
    print_inorder(node->left);
    printf("%d ", node->num);
    print_inorder(node->right);
}

void print_level(treeNode *node){ //level order
    if(node == NULL)
        return;
    treeNode *queue[128];

    int head,tail;
    head = 0;
    tail = 0;
    queue[tail++] = node; //store the node to print

    while(head<tail){ //if there are nodes didn't print out.
        printf("%d ",queue[head]->num); //print the first in one.
        if(queue[head]->left!=NULL)
            queue[tail++] = queue[head]->left; //add the left node to queue
        if(queue[head]->right!=NULL)
            queue[tail++] = queue[head]->right;//add the right node to queue
        head++; //to the next one to print out
    }
}


