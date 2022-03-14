#include<stdio.h>
#include<stdlib.h>
#include <string.h>

#define no 0
#define right 1
#define up 2
#define left 3
#define down 4

void print_yes(int r,int (*result)[5]){
    //If it can be merged,print yes and the finished puzzle.(Rotating to the original situation.)
    printf("YES\n");
    if(r==0){
        for(int i=1; i<4; i++){
            for(int j=1; j<4; j++)
                printf("%d",result[i][j]);
            printf("\n");
        }
    }
    else if(r==1){
        int ans1[5][5];
        int ans2[5][5];
        int ans3[5][5];

        rotate(ans1,result);
        rotate(ans2,ans1);
        rotate(ans3,ans2);
        //(Rotating to the original situation.)

        for(int i=1; i<4; i++){
            for(int j=1; j<4; j++)
                printf("%d",ans3[i][j]);
            printf("\n");
        }
    }
    else if(r==2){
        int ans1[5][5];
        int ans2[5][5];

        rotate(ans1,result);
        rotate(ans2,ans1);
        //(Rotating to the original situation.)

        for(int i=1; i<4; i++){
            for(int j=1; j<4; j++)
                printf("%d",ans2[i][j]);
            printf("\n");
        }
    }
    else if(r==3){
        int ans1[5][5];
        rotate(ans1,result);
        //(Rotating to the original situation.)

        for(int i=1; i<4; i++){
            for(int j=1; j<4; j++)
                printf("%d",ans1[i][j]);
            printf("\n");
        }
    }
}

int cmp(int way,int (*result)[5], int (*im_puzzle)[5],int (*move_puzzle)[5]){
    for(int j=1;j<4;j++){
        for(int k=1;k<4;k++){
            if(way == no)
                result[j][k] = im_puzzle[j][k] + move_puzzle[j][k];
            else if(way == right)
                result[j][k] = im_puzzle[j][k] + move_puzzle[j][k+1];
            else if(way == up)
                result[j][k] = im_puzzle[j][k] + move_puzzle[j-1][k];
            else if(way == left)
                result[j][k] = im_puzzle[j][k] + move_puzzle[j][k-1];
            else if(way == down)
                result[j][k] = im_puzzle[j][k] + move_puzzle[j+1][k];

            if(result[j][k] > 2 || result[j][k] ==0) //determine the two puzzle is merged or not by adding the two array up.(if the number >2  or <1 means it isn't merged. )
                return 1;
        }
    }
    return 0;

}

void rotate(int (*tmp)[5],int (*im_puzzle)[5]){
    tmp[1][3] = im_puzzle[1][1];
    tmp[2][3] = im_puzzle[1][2];
    tmp[3][3] = im_puzzle[1][3];
    tmp[1][2] = im_puzzle[2][1];
    tmp[2][2] = im_puzzle[2][2];
    tmp[3][2] = im_puzzle[2][3];
    tmp[1][1] = im_puzzle[3][1];
    tmp[2][1] = im_puzzle[3][2];
    tmp[3][1] = im_puzzle[3][3];
}

int main(){
    int n;
    scanf("%d",&n);//Enter a number to decide how many sets of puzzles to compare.

    for(int i=0;i<n;i++){
        int num;
        int im_puzzle[5][5]= {0};
        int move_puzzle[5][5]= {0};
        int tmp1[5][5]= {0};
        int tmp2[5][5] = {0};
        int tmp3[5][5] = {0};
        int result[5][5] ={0};

        int not=0;

        for(int j=1;j<4;j++){
            scanf("%d",&num);
            im_puzzle[j][1] = num/100%10;
            im_puzzle[j][2] = num/10%10;
            im_puzzle[j][3] = num%10;
            //The first array is an immovable puzzle.
        }

        for(int j=1;j<4;j++){
            scanf("%d",&num);
            move_puzzle[j][1] = num/100%10;
            move_puzzle[j][2] = num/10%10;
            move_puzzle[j][3] = num%10;
            //the second array is a movable puzzle.
        }

        not = cmp(no,result,im_puzzle,move_puzzle);//
        if(not==0){
            print_yes(0,result);
            continue;
        }
     //If it can¡¦t merge,move and rotate the immovable puzzle to merge the movable puzzle.

        rotate(tmp1,im_puzzle);//Rotating the immovable puzzle 90 degree
        not=cmp(no,result,tmp1,move_puzzle);
        if(not==0){
            print_yes(1,result);
            continue;
        }

        rotate(tmp2,tmp1);//180 degree
        not=cmp(no,result,tmp2,move_puzzle);
        if(not==0){
            print_yes(2,result);
            continue;
        }
        rotate(tmp3,tmp2);//270 degree.
        not=cmp(no,result,tmp3,move_puzzle);
        if(not==0){
            print_yes(3,result);
            continue;
        }

        not=cmp(right,result,im_puzzle,move_puzzle);//move the puzzle right.
        if(not==0){
            print_yes(0,result);
            continue;
        }

        rotate(tmp1,im_puzzle);//move the puzzle right,and rotating the immovable puzzle 90 degree.
        not=cmp(right,result,tmp1,move_puzzle);
        if(not==0){
            print_yes(1,result);
            continue;
        }

        rotate(tmp2,tmp1);//move the puzzle right,and rotating the immovable puzzle 180 degree.
        not=cmp(right,result,tmp2,move_puzzle);
        if(not==0){
            print_yes(2,result);
            continue;
        }
        rotate(tmp3,tmp2);//move the puzzle right,and rotating the immovable puzzle 270 degree.
        not=cmp(right,result,tmp3,move_puzzle);
        if(not==0){
            print_yes(3,result);
            continue;
        }
        not=cmp(up,result,im_puzzle,move_puzzle);//move the puzzle up.
        if(not==0){
            print_yes(0,result);
            continue;
        }
        rotate(tmp1,im_puzzle);//move the puzzle up,and rotating the immovable puzzle 90 degree.
        not=cmp(up,result,tmp1,move_puzzle);
        if(not==0){
            print_yes(1,result);
            continue;
        }
        rotate(tmp2,tmp1);//move the puzzle up,and rotating the immovable puzzle 180 degree.
        not=cmp(up,result,tmp2,move_puzzle);
        if(not==0){
            print_yes(2,result);
            continue;
        }
        rotate(tmp3,tmp2);//move the puzzle up,and rotating the immovable puzzle 270 degree.
        not=cmp(up,result,tmp3,move_puzzle);
        if(not==0){
            print_yes(3,result);
            continue;
        }
        not=cmp(left,result,im_puzzle,move_puzzle);//move the puzzle left.
        if(not==0){
            print_yes(0,result);
            continue;
        }
        rotate(tmp1,im_puzzle);//move the puzzle left,and rotating the immovable puzzle 90 degree.
        not=cmp(left,result,tmp1,move_puzzle);
        if(not==0){
            print_yes(1,result);
            continue;
        }
        rotate(tmp2,tmp1);//move the puzzle left,and rotating the immovable puzzle 180 degree.
        not=cmp(left,result,tmp2,move_puzzle);
        if(not==0){
            print_yes(2,result);
            continue;
        }
        rotate(tmp3,tmp2);//move the puzzle left,and rotating the immovable puzzle 270 degree.
        not=cmp(left,result,tmp3,move_puzzle);
        if(not==0){
            print_yes(3,result);
            continue;
        }
        not=cmp(down,result,im_puzzle,move_puzzle);//move the puzzle down.
        if(not==0){
            print_yes(0,result);
            continue;
        }

        rotate(tmp1,im_puzzle);//move the puzzle down,and rotating the immovable puzzle 90 degree.
        not=cmp(down,result,tmp1,move_puzzle);
        if(not==0){
            print_yes(1,result);
            continue;
        }
        rotate(tmp2,tmp1);//move the puzzle down,and rotating the immovable puzzle 180 degree.
        not=cmp(down,result,tmp2,move_puzzle);
        if(not==0){
            print_yes(2,result);
            continue;
        }
        rotate(tmp3,tmp2);//move the puzzle down,and rotating the immovable puzzle 270 degree.
        not=cmp(down,result,tmp3,move_puzzle);
        if(not==0){
            print_yes(3,result);
            continue;
        }
        printf("NO\n");
    }
}
