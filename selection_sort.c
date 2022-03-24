#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

#define MAX 1024

int count = 0;

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

void swap(int *a, int *b){
  int temp;
  temp = *a;
  *a = *b;
  *b= temp;
}

void selection_sort(int num[], int n){
  int i, j, min_id;
  for(i = 0; i<n-1; i++){
    min_id = i;
    for(j=i+1; j<n; j++){
      if (num[j] < num[min_id])
        min_id = j;
    }
    swap(&num[i], &num[min_id]);
    for(int i = 0; i<count-1; i++)
        printf("%d, ", num[i]);
    printf("%d\n",num[count-1]);
  }
}

int main(){

    int num[MAX];
    char line[MAX];
    fgets(line,MAX,stdin);
    char *ptr = line;
    char word[MAX];
    while((ptr=getword(ptr,word)) != NULL)
        num[count++] = atoi(word);

    selection_sort(num, count);



}
