#include <stdio.h>
#include <stdlib.h>
#include<string.h>

typedef struct treenode{
    int num;
    int coin;
    int walked;
    int sum;
    struct treenode *parent;
    struct treenode *left;
    struct treenode *right;
} treeNode;

treeNode* insert(treeNode *,int,int,int,int *);
void print_max_path(treeNode *,int);

int main(){
    char input[16];
    treeNode *root = NULL;
    int max = 0;
    while(1){
        scanf("%s",input);
        if(strcmp(input,"00")==0) //when input = 00 ,leave the loop.
            break;
        char tmp[16];
        char *ptr = input;
        char *qtr = tmp; //store the number
        while(*ptr!=',')
            *qtr++ = *ptr++;
        *qtr = '\0';
        ptr++; //ptr = coin
        int num = atoi(tmp); //tmp to number
        int coin = atoi(ptr);//ptr to coin

        if(!root){ //root = empty node
            root = (treeNode *)malloc(sizeof(treeNode));
            root->num = num;
            root->coin = coin;
            root->walked = 0;
            root->parent = NULL;
            root->sum = coin;
            root -> left = root -> right = NULL; // create root
        }
        else
            root = insert(root,num,coin,root->sum,&max); // create new node
    }
    print_max_path(root,max); //print the max path
    printf("Coins: %d",max); // print the coins
}


treeNode* insert(treeNode *node, int num,int coin,int sum,int *max){
    if(node == NULL) {
        node = (treeNode *)malloc(sizeof(treeNode));
        node->num = num;
        node->coin = coin;
        node->walked = 0;
        node->parent = NULL;
        node->sum = sum + coin; // sum = the last sum + coin
        node -> left = node -> right = NULL; //create new node
        if(*max < node->sum)
            *max = node->sum;// if max<sum , max update.
    }
    int c = num - node->num;
    if(c>0){ //if number > node's number ,insert to right.
        node->right = insert(node->right,num,coin,node->sum,max);
        node->right->parent = node ;
    }
    else if(c<0){//if number < node's number ,insert to left.
        node->left = insert(node->left,num,coin,node->sum,max);
        node->left->parent = node ;
    }
    return node;
}



void print_max_path(treeNode *node, int max){
    if(node == NULL)
        return;
    treeNode *queue[128]; // create a empty queue

    int head,tail;
    head = 0;
    tail = 0;
    queue[tail++] = node; //queue[0] = root
    int count = 1; //count how many trajectories.

    while(head<tail){
        if(queue[head]->left!=NULL)
            queue[tail++] = queue[head]->left; //add to queue
        if(queue[head]->right!=NULL)
            queue[tail++] = queue[head]->right;//add to queue

        if(queue[head]->sum == max){ //if find the max
            printf("Trajectory %d:",count++); //print
            treeNode *temp  = queue[head] ;
                while(temp->parent != NULL){
                    temp->walked = 1;//record walked path
                    temp = temp->parent;//back to parent
                }
                temp->walked = 1 ;
                treeNode *result_path = temp ;
                while(result_path){
                    printf(" %d", result_path->num);   //print out
                    result_path->walked = 0 ;
                    if(result_path->left!= NULL && result_path->left->walked == 1)   //if the next node exists and walked=1
                        result_path = result_path->left ;
                    else if(result_path->right!= NULL &&result_path->right->walked == 1) //if the next node exists and walked=1
                        result_path = result_path->right ;
                    else
                        break ;
                }
                printf("\n");
        }
        head++;
    }
}
