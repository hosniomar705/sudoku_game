#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

static int size;
static int **difficulty_arr;
static int game_board[9][9]={{1,2,3,4,5,6,7,8,9},
                             {7,8,9,1,2,3,4,5,6},
                             {4,5,6,7,8,9,1,2,3},
                             {3,1,2,8,4,5,9,6,7},
                             {6,9,7,3,1,2,8,4,5},
                             {8,4,5,6,9,7,3,1,2},
                             {2,3,1,5,7,4,6,9,8},
                             {9,6,8,2,3,1,5,7,4},
                             {5,7,4,9,6,8,2,3,1}};

static int player_board[9][9];

void swap_rows(int r1,int r2)
{
    int temp;
    for(int i=0;i<9;i++)
    {
        temp = game_board[r1][i];
        game_board[r1][i] = game_board[r2][i];
        game_board[r2][i] = temp;
    }
}

void swap_cols(int c1,int c2)
{
    int temp;
    for(int i=0;i<9;i++)
    {
        temp = game_board[i][c1];
        game_board[i][c1] = game_board[i][c2];
        game_board[i][c2] = temp;
    }
}

void generate_board(void)
{
    srand(time(0));
    for(int i=0;i<30;i++)
    {
        if(rand()%2)
        {
            int block = (rand()%3)*3;
            swap_rows((rand()%3)+block,(rand()%3)+block);
        }
        else
        {
            int block = (rand()%3)*3;
            swap_cols((rand()%3)+block,(rand()%3)+block);
        }
    }

}

void print_board(void)
{
    for(int r=0;r<9;r++)
    {
        for(int c=0;c<9;c++)
        {
            if(c%3==0)
            {
                printf(" |");
            }
            printf("%d|",player_board[r][c]);
        }
        printf("\n");
        if((r+1)%3==0 && r!=8)
        {
            printf("  - - -   - - -   - - - \n");
        }
    }
    printf("\n");
}

int input_check(int sr,int sc,int v)
{
    //check sr for repeated numbers
    unsigned int presence = 0;
    presence |= (1 << v);
    for (int i = 0; i < 9; i++)
    {
        int num = player_board[sr][i];
        if ((presence >> num) & 1)
        {
            return 1;
        }
        if(num)
        {
            presence |= (1 << num);
        }
    }
    //check sc for repeated numbers
    presence = 0;
    presence |= (1 << v);
    for (int i = 0; i < 9; i++)
    {
        int num = player_board[i][sc];
        if ((presence >> num) & 1)
        {
            return 2;
        }
        if(num)
        {
            presence |= (1 << num);
        }
    }
    //check 3*3 block for repeated numbers
    presence = 0;
    presence |= (1 << v);
    for(int r=(sr/3)*3;r<((sr/3)*3)+3;r++)
    {
        for(int c=(sc/3)*3;c<((sc/3)*3)+3;c++)
        {
            int num = player_board[r][c];
            if ((presence >> num) & 1)
            {
                return 3;
            }
            if(num)
            {
                presence |= (1 << num);
            }
        }
    }
    return 0;
}

bool check_repeated_cells(int **arr,int sr,int sc,int len)
{
    for(int i=0;i<len;i++)
    {
        if(arr[i][0]==sr && arr[i][1]==sc)
        {
            return true;
        }
    }
    return false;
}

void choose_difficulty()
{
    int level;
    printf("choose level of difficulty(0,1,2):");
    scanf(" %d",&level);
    while(level<0 || level>2)
    {
        printf("please choose a valid level:");
        scanf("%d",&level);
    }
    srand(time(0));
    size = 25+5*(2-level);
    difficulty_arr = (int**)malloc(size*sizeof(int*));
    for(int i=0;i<size;i++)
    {
        *(difficulty_arr+i) = (int*)malloc(2* sizeof(int));
        difficulty_arr[i][0] = rand()%9;
        difficulty_arr[i][1] = rand()%9;
        if(check_repeated_cells(difficulty_arr,difficulty_arr[i][0],difficulty_arr[i][1],i))
        {
            i--;
            continue;
        }
        player_board[difficulty_arr[i][0]][difficulty_arr[i][1]] = game_board[difficulty_arr[i][0]][difficulty_arr[i][1]];
    }
}

void get_user_input(void)
{
    int r,c,value;
    printf("choose a row:");
    scanf(" %d",&r);
    printf("choose a column:");
    scanf(" %d",&c);
    printf("choose a value:");
    scanf(" %d",&value);
    r-=1;
    c-=1;
    if(r>8 || r<0)
    {
        printf("invalid number choose another row\n");
    }
    else if(c>8 || c<0)
    {
        printf("invalid number choose another column\n");
    }
    else if(check_repeated_cells(difficulty_arr,r,c,size))
    {
        printf("already known number choose another row or column\n");
    }
    else if(input_check(r,c,value)==1)
    {
        printf("repeated number in  the row\n");
    }
    else if(input_check(r,c,value)==2)
    {
        printf("repeated number in  the column\n");
    }
    else if(input_check(r,c,value)==3)
    {
        printf("repeated number in  the block\n");
    }
    else
    {
        player_board[r][c] = value;
    }

}

int check_win(void)
{
    for(int r=0;r<9;r++)
    {
        for(int c=0;c<9;c++)
        {
            if(player_board[r][c]==0)
            {
                return 0;
            }
            else if(input_check(r,c,0))
            {
                return 0;
            }

        }
    }
    return 1;
}


