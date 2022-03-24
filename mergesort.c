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

void merge(int *num, int *arr,int i,int m,int n){
    int j,k,t;
    j = m+1;
    k=i;

    while(i<=m && j<=n){
        if(num[i] <= num[j])
            arr[k++] = num[i++];
        else
            arr[k++] = num[j++];
    }

    if(i>m){
        for(t = j;t<=n; t++)
            arr[k+t-j] = num[t];

    }

    else{
        for(t = i;t<=m;t++)
            arr[k+t-i] = num[t];

    }




}


void merge_pass(int *num,int*arr,int n,int s){
    int i,j;

    for(i = 0; i <= n-2*s+1; i+=2*s)
        merge(num,arr,i,i+s-1,i+2*s-1);
    if(i+s-1 < n)
        merge(num,arr,i,i+s-1,n);
    else{
        for(j=i;j<=n;j++)
            arr[j] = num[j];

    }



}

void merge_sort(int *num,int n){
    int s = 1;
    int arr[MAX];
    while(s<n){
        merge_pass(num,arr,n,s);
        s*=2;

        for(int a=0;a<count-1;a++)
            printf("%d, ",arr[a]);
        printf("%d\n",arr[count-1]);

        merge_pass(arr,num,n,s);
        s*=2;

        for(int a=0;a<count-1;a++)
            printf("%d, ",num[a]);
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
    merge_sort(num,count-1);

    int min = num[1] - num[0];

    for(int i=2;i<count;i++){
        int c = num[i]-num[i-1];
        if(c < min){
            min = c;
        }
    }
    printf("Minimum gap: %d",min);


}
