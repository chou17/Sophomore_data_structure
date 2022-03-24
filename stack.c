#include<stdio.h>

#define R_START 1
#define J_START 99

#define FLOOR1 0
#define FLOOR2 1

#define NEW 0
#define PATH 1
#define ELE 2
#define WALL 3


typedef struct position{
    int floor;
    int row;
    int column;
}Position; //recording Romeo & Juliet's position

int r_walk(Position *,int *, Position *, int *, int (*)[102], int (*)[102]);  //Romeo move
int j_walk(Position *,int *, Position *, int (*)[102], int (*)[102]); //Juliet move

int main(){
    int n=1,r_top=0,j_top=0;
    int f;
    char floor1[128][128]; //floor1 input
    char floor2[128][128]; //floor2 input
    int r_f1_path[101][102] = {NEW}; // using number to record the path Romeo passed or not in floor 1
    int r_f2_path[101][102] = {NEW};// using number to record the path Romeo passed or not in floor 2
    int j_f1_path[101][102] = {NEW};// using number to record the path Juliet passed or not in floor 1
    int j_f2_path[101][102] = {NEW};// using number to record the path Juliet passed or not in floor 2

    Position romeo[10240];//stack(Romeo's path)
    Position juliet[10240];//stack(Juliet's path)

    romeo[0].floor = FLOOR1;
    romeo[0].row = R_START;
    romeo[0].column = R_START;
    //Romeo start

    juliet[0].floor = FLOOR2;
    juliet[0].row = J_START;
    juliet[0].column = J_START;
    //Juliet start

    scanf("%d",&f);
    for(int i=0;i<101;i++)
        scanf("%s",floor1[i]);
    for(int i=0;i<101;i++){
        for(int j=0;j<102;j++){
            if (floor1[i][j] =='X'){
                r_f1_path[i][j]=WALL;
                j_f1_path[i][j]=WALL;
            }
            else if (floor1[i][j] =='o'){
                r_f1_path[i][j]=ELE;
                j_f1_path[i][j]=ELE;
            }
        }
    }
    //floor 1

    scanf("%d",&f);
    for(int i=0;i<101;i++)
        scanf("%s",floor2[i]);
    for(int i=0;i<101;i++){
        for(int j=0;j<102;j++){
            if (floor2[i][j] =='X'){
                r_f2_path[i][j]=WALL;
                j_f2_path[i][j]=WALL;
            }
            else if(floor2[i][j] =='o'){
                r_f2_path[i][j]=ELE;
                j_f2_path[i][j]=ELE;
            }
        }
    }
    //floor 2


    int result = 0;
    while(!result){
        result = r_walk(romeo,&r_top,juliet,&n,r_f1_path,r_f2_path); //Romeo walk
        if(romeo[r_top].floor==juliet[j_top].floor && romeo[r_top].row==juliet[j_top].row && romeo[r_top].column == juliet[j_top].column){
            printf("They encounter each other in (%d,%d,%d)",romeo[r_top].floor,romeo[r_top].column,romeo[r_top].row);
            break;
            //if the floor,row,column are the same ,they encounter each other,so leave this loop.
        }
        else if(romeo[r_top].floor==FLOOR2 && romeo[r_top].row==J_START && romeo[r_top].column==J_START){
            result = j_walk(romeo,&j_top,juliet,j_f1_path,j_f2_path);
            printf("They do not encounter each other in this maze.");
            break;
            //if Romeo arrived the position that Juliet started,it means they don't encounter each other,so leave this loop.
        }
        j_walk(romeo,&j_top,juliet,j_f1_path,j_f2_path);

        if(romeo[r_top].floor==juliet[j_top].floor && romeo[r_top].row==juliet[j_top].row && romeo[r_top].column == juliet[j_top].column){
            printf("They encounter each other in (%d,%d,%d)",romeo[r_top].floor,romeo[r_top].column,romeo[r_top].row);
            break;
            //if the floor,row,column are the same ,they encounter each other,so leave this loop.
        }
        else if(juliet[j_top].floor==FLOOR1 && juliet[j_top].row==R_START && juliet[j_top].column==R_START){
            printf("They do not encounter each other in this maze.");
            break;
            //if Juliet arrived the position that Romeo started,it means they don't encounter each other,so leave this loop.
        }
    }
    return 0;
}

int r_walk(Position *romeo,int *top, Position *juliet, int *n,int(*r_f1_path)[102],int(*r_f2_path)[102]){
    while(romeo[*top].floor == FLOOR1){//when Romeo did not go up stairs.
        if(r_f1_path[R_START][R_START] == ELE){//if where Romeo started is elevator.
            romeo[*top].floor = FLOOR2;//Romeo go up stairs.
            r_f2_path[R_START][R_START]=PATH;//record the position that Romeo walked.
            printf("==Round: %d==\n",*n);
            (*n)++;
            printf("Romeo: (%d,%d,%d)\n",romeo[*top].floor,romeo[*top].column,romeo[*top].row);
            //print Romeo's position.
            return 0;
        }
        else if(r_f1_path[romeo[*top].row][romeo[*top].column+1] == NEW ||
                r_f1_path[romeo[*top].row][romeo[*top].column+1] == ELE){
                //if Romeo's right is walkable and did not walk before.
            (*top)++;
            romeo[*top].floor = FLOOR1;
            romeo[*top].row = romeo[(*top)-1].row;
            romeo[*top].column = romeo[(*top)-1].column+1 ;
            //Romeo walked
            if(r_f1_path[romeo[*top].row][romeo[*top].column] == ELE){//if Romeo's position have elevator
                romeo[0].floor = FLOOR2;
                romeo[0].row = romeo[*top].row;
                romeo[0].column = romeo[*top].column;
                *top = 0;
                r_f2_path[romeo[*top].row][romeo[*top].column] = PATH;//record the position that Romeo walked.
                //Romeo go up stairs.
            }
            else
                r_f1_path[romeo[*top].row][romeo[*top].column]=PATH;//record the position that Romeo walked.
        }
        else if(r_f1_path[romeo[*top].row+1][romeo[*top].column]==NEW ||
                r_f1_path[romeo[*top].row+1][romeo[*top].column]==ELE){
                //if Romeo's down is walkable and did not walk before.
            (*top)++;
            romeo[*top].floor = FLOOR1;
            romeo[*top].column = romeo[(*top)-1].column;
            romeo[*top].row = romeo[(*top-1)].row+1;
            //Romeo walked
            if(r_f1_path[romeo[*top].row][romeo[*top].column] == ELE){//if Romeo's position have elevator
                romeo[0].floor = FLOOR2;
                romeo[0].row = romeo[*top].row;
                romeo[0].column = romeo[*top].column;
                *top = 0;
                r_f2_path[romeo[*top].row][romeo[*top].column] = PATH;//record the position that Romeo walked.
                 //Romeo go up stairs.
            }
            else
                r_f1_path[romeo[*top].row][romeo[*top].column]=PATH;//record the position that Romeo walked.
        }
        else if(r_f1_path[romeo[*top].row-1][romeo[*top].column]==NEW ||
                r_f1_path[romeo[*top].row-1][romeo[*top].column]==ELE){
                    //if Romeo's up is walkable and did not walk before.
            (*top)++;
            romeo[*top].floor = FLOOR1;
            romeo[*top].column = romeo[(*top)-1].column;
            romeo[*top].row = romeo[(*top-1)].row-1;
            //Romeo walked
            if(r_f1_path[romeo[*top].row][romeo[*top].column] == ELE){//if Romeo's position have elevator
                romeo[0].floor = FLOOR2;
                romeo[0].row = romeo[*top].row;
                romeo[0].column = romeo[*top].column;
                *top = 0;
                r_f2_path[romeo[*top].row][romeo[*top].column] = PATH;//record the position that Romeo walked.
                 //Romeo go up stairs.
            }
            else
                r_f1_path[romeo[*top].row][romeo[*top].column]=PATH;//record the position that Romeo walked.
        }
        else if(r_f1_path[romeo[*top].row][romeo[*top].column-1]==NEW ||
                r_f1_path[romeo[*top].row][romeo[*top].column-1]==ELE){
                    //if Romeo's left is walkable and did not walk before.
            (*top)++;
            romeo[*top].floor = FLOOR1;
            romeo[*top].row = romeo[(*top)-1].row;
            romeo[*top].column = romeo[(*top-1)].column-1;
            //Romeo walked
            if(r_f1_path[romeo[*top].row][romeo[*top].column] == ELE){//if Romeo's position have elevator
                romeo[0].floor = FLOOR2;
                romeo[0].row = romeo[*top].row;
                romeo[0].column = romeo[*top].column;
                *top = 0;
                r_f2_path[romeo[*top].row][romeo[*top].column] = PATH;//record the position that Romeo walked.
                 //Romeo go up stairs.
            }
            else
                r_f1_path[romeo[*top].row][romeo[*top].column]=PATH;//record the position that Romeo walked.
        }
        else
            (*top)--;//go back to the last position
        printf("==Round: %d==\n",*n);
        (*n)++;
        printf("Romeo: (%d,%d,%d)\n",romeo[*top].floor,romeo[*top].column,romeo[*top].row);
        return 0;
    }

    while(r_f2_path[J_START][J_START] == 0){
        if(r_f2_path[romeo[*top].row][romeo[*top].column+1] == NEW){
            //if Romeo's right is walkable and did not walk before.
            (*top)++;
            romeo[*top].floor = FLOOR2;
            romeo[*top].row = romeo[(*top)-1].row;
            romeo[*top].column = romeo[(*top)-1].column+1
            //Romeo walked;
            r_f2_path[romeo[*top].row][romeo[*top].column]=PATH;//record the position that Romeo walked.
        }
        else if(r_f2_path[romeo[*top].row+1][romeo[*top].column]==NEW){
            //if Romeo's down is walkable and did not walk before.
            (*top)++;
            romeo[*top].floor = FLOOR2;
            romeo[*top].column = romeo[(*top)-1].column;
            romeo[*top].row = romeo[(*top-1)].row+1;
            r_f2_path[romeo[*top].row][romeo[*top].column]=PATH;//record the position that Romeo walked.
        }
        else if(r_f2_path[romeo[*top].row-1][romeo[*top].column]==NEW){
            //if Romeo's up is walkable and did not walk before.
            (*top)++;
            romeo[*top].floor = FLOOR2;
            romeo[*top].column = romeo[(*top)-1].column;
            romeo[*top].row = romeo[(*top-1)].row-1;
            //Romeo walked
            r_f2_path[romeo[*top].row][romeo[*top].column]=PATH;//record the position that Romeo walked.
        }
        else if(r_f2_path[romeo[*top].row][romeo[*top].column-1]==NEW){
            //if Romeo's left is walkable and did not walk before.
            (*top)++;
            romeo[*top].floor = FLOOR2;
            romeo[*top].row = romeo[(*top)-1].row;
            romeo[*top].column = romeo[(*top-1)].column-1;
            //Romeo walked
            r_f2_path[romeo[*top].row][romeo[*top].column]=PATH;//record the position that Romeo walked.
        }
        else
            (*top)--;
        printf("==Round: %d==\n",*n);
        (*n)++;
        printf("Romeo: (%d,%d,%d)\n",romeo[*top].floor,romeo[*top].column,romeo[*top].row);
        return 0;
    }
    return 0;

}

int j_walk(Position *romeo,int *top, Position *juliet,int(*j_f1_path)[102],int(*j_f2_path)[102]){
    while(juliet[*top].floor == FLOOR2){
        if(j_f2_path[J_START][J_START] == ELE){
            juliet[*top].floor = FLOOR1;
            j_f1_path[J_START][J_START] = PATH;//record the position that Juliet walked.
            printf("Juliet: (%d,%d,%d)\n",juliet[*top].floor,juliet[*top].column,juliet[*top].row);
            return 0;
        }
        else if(j_f2_path[juliet[*top].row][juliet[*top].column-1] == NEW ||
                j_f2_path[juliet[*top].row][juliet[*top].column-1] == ELE){
                //if Juliet's left is walkable and did not walk before.
            (*top)++;
            juliet[*top].floor = FLOOR2;
            juliet[*top].row = juliet[(*top)-1].row;
            juliet[*top].column = juliet[(*top)-1].column-1 ;
            //Juliet walked
            if(j_f2_path[juliet[*top].row][juliet[*top].column] == ELE){//if Juliet's position have elevator
                juliet[0].floor = FLOOR1;
                juliet[0].row = juliet[*top].row;
                juliet[0].column = juliet[*top].column;
                *top = 0;
                j_f1_path[juliet[*top].row][juliet[*top].column] = PATH;//record the position that Juliet walked.
            }
            else
                j_f2_path[juliet[*top].row][juliet[*top].column]=PATH;//record the position that Juliet walked.
        }
        else if(j_f2_path[juliet[*top].row-1][juliet[*top].column]==NEW ||
                j_f2_path[juliet[*top].row-1][juliet[*top].column]==ELE ){
                //if Juliet's up is walkable and did not walk before.
            (*top)++;
            juliet[*top].floor = FLOOR2;
            juliet[*top].column = juliet[(*top)-1].column;
            juliet[*top].row = juliet[(*top-1)].row-1;
            //Juliet walked
            if(j_f2_path[juliet[*top].row][juliet[*top].column] == ELE){//if Juliet's position have elevator
                juliet[0].floor = FLOOR1;
                juliet[0].row = juliet[*top].row;
                juliet[0].column = juliet[*top].column;
                *top = 0;
                j_f1_path[juliet[*top].row][juliet[*top].column] = PATH;//record the position that Juliet walked.
            }
            else
                j_f2_path[juliet[*top].row][juliet[*top].column]=PATH;//record the position that Juliet walked.
        }
        else if(j_f2_path[juliet[*top].row+1][juliet[*top].column]==NEW ||
                j_f2_path[juliet[*top].row+1][juliet[*top].column]==ELE){
                //if Juliet's down is walkable and did not walk before.
            (*top)++;
            juliet[*top].floor = FLOOR2;
            juliet[*top].column = juliet[(*top)-1].column;
            juliet[*top].row = juliet[(*top-1)].row+1;
            //Juliet walked
            if(j_f2_path[juliet[*top].row][juliet[*top].column] == ELE){//if Juliet's position have elevator
                juliet[0].floor = FLOOR1;
                juliet[0].row = juliet[*top].row;
                juliet[0].column = juliet[*top].column;
                *top = 0;
                j_f1_path[juliet[*top].row][juliet[*top].column] = PATH;//record the position that Juliet walked.
            }
            else
                j_f2_path[juliet[*top].row][juliet[*top].column]=PATH;//record the position that Juliet walked.
        }
        else if(j_f2_path[juliet[*top].row][juliet[*top].column+1]==NEW ||
                j_f2_path[juliet[*top].row][juliet[*top].column+1]==ELE){
                //if Juliet's right is walkable and did not walk before.
            (*top)++;
            juliet[*top].floor = FLOOR2;
            juliet[*top].row = juliet[(*top)-1].row;
            juliet[*top].column = juliet[(*top-1)].column+1;
            //Juliet walked
            if(j_f2_path[juliet[*top].row][juliet[*top].column] == ELE){//if Juliet's position have elevator
                juliet[0].floor = FLOOR1;
                juliet[0].row = juliet[*top].row;
                juliet[0].column = juliet[*top].column;
                *top = 0;
                j_f1_path[juliet[*top].row][juliet[*top].column] = PATH;//record the position that Juliet walked.
            }
            else
                j_f2_path[juliet[*top].row][juliet[*top].column]=PATH;//record the position that Juliet walked.
        }
        else
            (*top)--;
        printf("Juliet: (%d,%d,%d)\n",juliet[*top].floor,juliet[*top].column,juliet[*top].row);
        return 0;
    }

    while(j_f1_path[R_START][R_START] == 0){
        if(j_f1_path[juliet[*top].row][juliet[*top].column-1] == NEW){
            (*top)++;
            juliet[*top].floor = FLOOR1;
            juliet[*top].row = juliet[(*top)-1].row;
            juliet[*top].column = juliet[(*top)-1].column-1 ;
            //Juliet walked
            j_f1_path[juliet[*top].row][juliet[*top].column]=PATH;//record the position that Juliet walked.
        }
        else if(j_f1_path[juliet[*top].row-1][juliet[*top].column]==NEW){
            (*top)++;
            juliet[*top].floor = FLOOR1;
            juliet[*top].column = juliet[(*top)-1].column;
            juliet[*top].row = juliet[(*top-1)].row-1;
            j_f1_path[juliet[*top].row][juliet[*top].column]=PATH;//record the position that Juliet walked.
        }

        else if(j_f1_path[juliet[*top].row+1][juliet[*top].column]==NEW){
            (*top)++;
            juliet[*top].floor = FLOOR1;
            juliet[*top].column = juliet[(*top)-1].column;
            juliet[*top].row = juliet[(*top-1)].row+1;
            //Juliet walked
            j_f1_path[juliet[*top].row][juliet[*top].column]=PATH;//record the position that Juliet walked.
        }

        else if(j_f1_path[juliet[*top].row][juliet[*top].column+1]==NEW){
            (*top)++;
            juliet[*top].floor = FLOOR1;
            juliet[*top].row = juliet[(*top)-1].row;
            juliet[*top].column = juliet[(*top-1)].column+1;
            //Juliet walked
            j_f1_path[juliet[*top].row][juliet[*top].column]=PATH;//record the position that Juliet walked.
        }
        else
            (*top)--;
        printf("Juliet: (%d,%d,%d)\n",juliet[*top].floor,juliet[*top].column,juliet[*top].row);
        return 0;
    }
    return 0;
}
