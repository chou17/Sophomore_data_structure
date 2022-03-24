#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>

#define MAX 32

typedef struct node Node;
struct node{
    char str[MAX];
    struct node *next;
};

char *getword(char *,char *); //only get word(without symbol)
Node *create_new_node(Node *,char *); //create a new node
Node *delete_node(Node *,Node *);//delete the repeat word
void free_node(Node *);//free all node

int main(){
    Node *head = NULL; //node's head
    char line[MAX]; //input
    char word[MAX]; //only word(without symbol)

    while(scanf("%s",line)!=EOF){ //input
        char *ptr = line; //point to line
        char *o_line = line;
        int print_location = 0; //record where to print

        while ((ptr=getword(ptr,word)) != NULL){ //only get word(without symbol)
            head = create_new_node(head,word); //add a new node to head
            Node *current = head->next;
            while(current != NULL) {
                if(strcmp(word,current->str)==0){ //check repeat or not
                    int index = 1;
                    Node *tmp = head->next;
                    while(tmp != current){
                        index++; //the repeat word's index
                        tmp = tmp->next;
                    }
                    size_t w_len = strlen(word);
                    char *location = ptr - w_len;
                    int gap = location - line;
                    for( ; print_location<gap; print_location++)
                        printf("%c",line[print_location]); //print the line that doesn't repeat
                    printf("%d",index); //print the repeat word's index
                    o_line = location + w_len;
                    print_location += (w_len); //print line
                    head = delete_node(head,current); //delete the old node
                }
            current = current->next; //point to next node
            }
        }
    if(o_line!=NULL) //if leave the loop still have line that didn't print
        printf("%s ",o_line);
    }
    free_node(head);//free the node
}

char *getword(char *text, char *word) {
    char *ptr = text;
    char *qtr = word;
    char *text_end = text + strlen(text);
    *word = '\0';

    while (ptr < text_end && !isalpha(*ptr)) //if point to symbol
        ptr ++; //point to next character

    while (ptr < text_end && isalpha(*ptr)) //if point to word
        *qtr++ = *ptr++; //store to word

    *qtr = '\0';
    return (*word == '\0') ? NULL : ptr;
}


Node *create_new_node(Node *head,char *word){
    Node *newnode = (Node *) malloc(sizeof(Node));
    strcpy(newnode->str,word);
    if(head == NULL){
        newnode->next=NULL;
        return newnode;
    }
    newnode->next = head;
    return newnode;
}

Node *delete_node(Node *head,Node *node){
	Node* ptr=head;
    while(ptr->next!=node)
        ptr = ptr->next;
    ptr->next=node->next;
	free(node);
	return head;
}

void free_node(Node *head){
    while (head != NULL){
       Node *tmp = head;
       head = head->next;
       free(tmp);
    }
}
