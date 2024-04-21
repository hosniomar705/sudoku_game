#include <stdio.h>
#include <stdlib.h>
void print_board(void);
void choose_difficulty();
void generate_board(void);
void get_user_input(void);
int check_win(void);

int main()
{
    generate_board();
    choose_difficulty();
    print_board();
    while(1)
    {
        get_user_input();
        print_board();
        if(check_win())
        {
            printf("congratulation you won");
            break;
        }
    }

    return 0;
}
