#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <unistd.h>
#include "life.h"

//author: Kevin Good

char* pad(char array[]);
char* calc(char arr[]);
char* trim(char array[]);
void create_board(char arr[]);


int main(int argc, char *argv[])
{

    int gen;
    char* finArr;

    /*checks for correct number of arguments*/
    if(argc<2){
        printf("Too few arguments.\n");
        return -1;
    }
    if(argc>3){
        printf("Too many arguments.\n");
        return -1;
    }
    if(argc==2){
        gen = 0;
    }
    else{
        gen = atoi(argv[2]);
    }
    char **grid = parse_life(argv[1]);
    char arr[2002];
    int idx = 0;
    /*transfers matrix into 1d array*/
    for(int i = 0;i<24;i++){
        for(int j=0;j<80;j++){
            arr[idx] = grid[i][j];
            idx = idx+1;
        }
        arr[idx]= '\n';
        idx = idx+1;
        arr[idx] = '\0';

    }
    /*0 generations specified, returns original input*/
    if(gen==0){
        finArr = arr;
    }
    /*1st generation specified */
    if(gen==1){
        finArr = pad(arr);
        finArr = calc(finArr);
        finArr = trim(finArr);
    }
    /*2+ generations specified*/
    if(gen>1){
        create_board(arr);
        finArr = pad(arr);
        finArr = calc(finArr);
        finArr = trim(finArr);
        create_board(finArr);
    for(int g = 1;g<gen;g++){
        finArr = pad(finArr);
        finArr = calc(finArr);
        finArr = trim(finArr);
        create_board(finArr); //calls and updates display for every generation


        }
    }
    printf("%s",finArr);

    return 0;

}

/*pads the input array with a border of dead cells
 * since the game is on a infinite space the dead
 * cells mimic the space beyond the boarder
 * */
char* pad(char grid[]){
    int idx = 0;
    int gidx = 0;
    char* temp = malloc (sizeof(char)*2158);
    for(int i = 0;i<82;i++){
        temp[i]='x';
        idx = idx+1;

    }
    temp[idx]= '\n';
    idx = idx+1;
    for(int i = 0;i<24;i++){
        temp[idx]='x';
        idx = idx+1;
        for(int j=0;j<80;j++){
            temp[idx] = grid[gidx];
            idx = idx+1;
            gidx = gidx+1;
        }
        temp[idx]= 'x';
        idx = idx+1;
        temp[idx]= '\n';
        idx = idx+1;
        gidx = gidx+1;

    }

    for(int i = 0;i<82;i++){
        temp[idx]='x';
        idx =idx+1;
    }
    temp[idx]= '\n';
    idx = idx+1;
    temp[idx]='\0';

    return temp;
}
/*calculates new dead and alive cells returns in new array*/
char* calc(char arr[]){
    char* newArr = malloc(sizeof(char)*2158);
    for(int k=0;k<2158;k++){
        if(arr[k]=='X'){
            /*Checks all 8 neighboring cells to get count of alive neighbors*/
            int nbCount = 0;
            if(arr[k-84]=='X'){nbCount = nbCount+1;}
            if(arr[k-83]=='X'){nbCount = nbCount+1;}
            if(arr[k-82]=='X'){nbCount = nbCount+1;}
            if(arr[k-1]=='X'){nbCount = nbCount+1;}
            if(arr[k+1]=='X'){nbCount = nbCount+1;}
            if(arr[k+82]=='X'){nbCount = nbCount+1;}
            if(arr[k+83]=='X'){nbCount = nbCount+1;}
            if(arr[k+84]=='X'){nbCount = nbCount+1;}
            /*If cell is alive and has proper number of
             * alive neighbors the cell remains alive, else cell dies*/
            if(nbCount == 2 || nbCount == 3){
                newArr[k]=arr[k];
            }
            else{
                newArr[k]=' ';
            }
        }
        if(arr[k]==' '){
            int nbCount = 0;
            if(arr[k-84]=='X'){nbCount = nbCount+1;}
            if(arr[k-83]=='X'){nbCount = nbCount+1;}
            if(arr[k-82]=='X'){nbCount = nbCount+1;}
            if(arr[k-1]=='X'){nbCount = nbCount+1;}
            if(arr[k+1]=='X'){nbCount = nbCount+1;}
            if(arr[k+82]=='X'){nbCount = nbCount+1;}
            if(arr[k+83]=='X'){nbCount = nbCount+1;}
            if(arr[k+84]=='X'){nbCount = nbCount+1;}
            if(nbCount == 3){
                newArr[k]='X';
            }
            else{
                newArr[k]=arr[k];
            }
        }

     }

    return newArr;
    }

/*trims dead cells off of border*/
char* trim(char arr[]){
    char *trarr = malloc (sizeof (char)*2002);
    int idx = 83;
    int tidx = 0;
    for(int i = 0;i<24;i++){
        idx = idx+1;
        for(int j = 0;j<80;j++){
                trarr[tidx]=arr[idx];

            idx = idx+1;
            tidx = tidx+1;
        }
        idx = idx+1;
        trarr[tidx]='\n';
        tidx = tidx+1;
        idx = idx+1;

    }
    return trarr;
}

/*method to print cell grid to terminal*/
void create_board(char arr[]){

    initscr();			/* Start curses mode 		*/
    raw();				/* Line buffering disabled	*/
    noecho();			/* Don't echo() while we do getch */
    int idx = 0;

    for(int i = 0;i<24;i++){
        for(int j=0;j<81;j++){
            if(arr[idx]==' '){
                mvprintw(i,j," ");
            }
            else if(arr[idx]=='X'){
                mvprintw(i,j,"X");
            }
            idx = idx+1;
        }

    }

    refresh();

    sleep(1); //generation is displayed for one second.


    endwin();
}
