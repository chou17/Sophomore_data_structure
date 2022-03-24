#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include<ctype.h>

#define MAX 1024
#define SWAP(x,y) {int t; t = x; x = y; y = t;}

char *getword(char *, char *) ;
int partition(int*,int,int);
void quickSort(int*,int,int);
int count = 0;

int main(){
    int num[MAX];
    char line[MAX];
    fgets(line,MAX,stdin);
    char *ptr = line;
    char word[MAX];
    while((ptr=getword(ptr,word)) != NULL)
        num[count++] = atoi(word);
    quickSort(num, 0, count-1);
}

void quickSort(int *number,int left,int right){
    int pivot,i,j;
    if(left < right) {
        i=left;
        j = right+1;
        pivot = number[left];
        do{
            do i++;  while(number[i]<pivot);
            do j--;  while(number[j]>pivot);
            if(i<j)  SWAP(number[i], number[j]);
        }while(i<j);
        SWAP(number[left], number[j]);
        for(int k=0;k<count-1;k++){
            printf("%d, ",number[k]);
        }
        printf("%d\n",number[count-1]);

        quickSort(number, left, j-1);
        quickSort(number, j+1, right);
    }
}


char *getword(char *text, char *word) {
    char *ptr = text;
    char *qtr = word;
    char *text_end = text + strlen(text);
    *word = '\0';

    while (ptr < text_end && !isdigit(*ptr)) //if point to symbol
        ptr ++; //point to next character

    while (ptr < text_end && isdigit(*ptr)) //if point to word
        *qtr++ = *ptr++; //store to word

    *qtr = '\0';
    return (*word == '\0') ? NULL : ptr;
}
