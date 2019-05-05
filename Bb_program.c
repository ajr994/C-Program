#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define Name_Size 9
#define CMD_Size 81
#define Team_Size 9

struct player   {
    char name[Name_Size];
    int player_number;
    int batting_average;
};

void print(const char *cmd, const struct player team[], int num_players);
void print_player(const struct player *);
void add(const char *cmd, struct player team[], int *count);
void help();

int main()  {
    int num_players = 0;
    struct player team[Team_Size];
    printf("Play Ball!.\n\n");
    help();
    for (;;)    {
        char cmd[CMD_Size];
        printf("\nCommand: ");
        fgets(cmd, sizeof(cmd), stdin);
        switch (cmd[0]) {
            default:
                printf("Bad command '%c'.\n", cmd[0]);
                //falls through
            case 'h':
                help();
                break;
            case 'q':
                return 0;
            case 'a':
                add(cmd, team, &num_players);
                break;
            case 'p':
                print(cmd, team, num_players);
                break;
        }
    }
}

void help() {
    printf("a name number average (add a player)\n"
           "h (help)\n"
           "q (quit)\n"
           "p (print all players)\n"
           "p number (print one player)\n");
}
//Add this person to the roster
void add(const char *cmd, struct player team[], int *count) {
    if (*count == Team_Size)    {
        printf("Can't add anymore players, team is full.\n");
        return;
    }
    struct player *p = &team[*count];
    sscanf(cmd+1, "%s %d %d", p->name, &p->player_number, &p->batting_average);
    //Is there already a player with same number?
    for (int i=0; i<*count; i++)    {
        if (team[i].player_number == p->player_number)  {
            printf("The team already has a player #%d.\n", p->player_number);
            return;
        }
    }
    ++*count;
}
// Print the whole roster
void print(const char *cmd, const struct player team[], int num_players)    {
    int num;
    printf("%-8s %-3s %s\n", "Name", "Number", "Average");
    printf("%-8s %-3s %s\n", "========", "===", "======");
    if (sscanf(cmd+1, "%d", &num)==1)   {
        for (int i=0; i<num_players; i++)
            if (team[i].player_number == num)
            print_player(&team[i]);
    }
    else {
        for (int i=0; i<num_players; i++)
            print_player(&team[i]);
    }
}
//Print single player
void print_player(const struct player *p)   {
    printf("%-8s %-3d .%-3d\n", p->name, p->player_number, p->batting_average);
}
