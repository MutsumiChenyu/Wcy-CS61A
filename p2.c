#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <getopt.h>
#include <unistd.h>

#define MAX_PLAYERS 9
#define MAX_CARDHELD 100

int pnum = 0;
int inic = 0;
int rounds = 0;
int decks = 0;

typedef struct // define the cards
{
    char *type;
    int cnum;
} card;

typedef struct // define the players
{
    int cardcount;
    char *name;
    card cardheld[MAX_CARDHELD];
    char *score;
} player;

player players[MAX_PLAYERS];
int card_num = 0;
card cards[52]; // Establish the decks
char *types[] = {"Hearts", "Diamonds", "Spades", "Clubs"};

//Functions Declaration
void giving(player *p, int n);
void shuffling(void);
card playing(player *p);
int firster(void);
void effect(card *c)
void action(card *c)
void defense(void)
void regular(card *c)
void attack(card *c)

//getopt Argument-related
typedef struct
{
    int pnum;
    int rounds;
    int inic;
    int decks;
    int auto_mode;
    int log_mode;
} Config;

void print_help() {
    printf("Usage:\n");
    printf("  -n, --player-number <n>\n");
    printf("  -r, --rounders <r>\n");
    printf("  -c, --initial-cards <c>\n");
    printf("  -d, --decks <d>\n");
    printf("  -a, --auto\n");
    printf("  -h, --help\n");
    printf("      --log\n");
}

int main(int argc, char *argv[])
{
    Config cfg = {0};

    static struct option opts[] = {
        {"player-number", required_argument, 0, 'n'},
        {"rounders",       required_argument, 0, 'r'},
        {"initial-cards",  required_argument, 0, 'c'},
        {"decks",          required_argument, 0, 'd'},
        {"auto",           no_argument,       0, 'a'},
        {"help",           no_argument,       0, 'h'},
        {"log",            no_argument,       0,  1 },
        {0, 0, 0, 0}
    };

    int opt;
    while ((opt = getopt_long(argc, argv, "n:r:c:d:ah", opts, NULL)) != -1)
    {
        switch (opt)
        {
            case 'n': cfg.pnum = atoi(optarg);   break;
            case 'r': cfg.rounds = atoi(optarg); break;
            case 'c': cfg.inic = atoi(optarg);   break;
            case 'd': cfg.decks = atoi(optarg);  break;
            case 'a': cfg.auto_mode = 1;         break;
            case 'h': print_help(); return 0;
            case 1:   cfg.log_mode = 1;          break;
            default:  fprintf(stderr, "Invalid option.\n"); return 7;
        }
    }
    if (cfg.pnum < 2)   return printf("Failed\n"), 4;
    if (cfg.rounds < 1) return printf("Failed\n"), 1;
    if (cfg.inic < 0)   return printf("Failed\n"), 5;
    if (cfg.decks < 2)  return printf("Failed\n"), 2;
    if (cfg.log_mode) {
        FILE *lf = fopen("Journal.txt", "a");
        fprintf(lf, "Launch correctly\n");
        fclose(lf);
    }

    printf("Players=%d, Rounds=%d, Init=%d, Decks=%d\n",
        cfg.pnum, cfg.rounds, cfg.inic, cfg.decks);

    int code = 0; 
    for (int i = 2; i <= 13; i++) 
    {
        for (int p = 0; p < 4; p++)
        {   
            cards[code].type = types[p]; 
            cards[code].cnum = i; 
            code++; 
        } 
    } 
    for (int i = 1; i <= pnum; i++) 
    { 
        players[i].name = get_string("Player%i:", i); 
        printf("\n"); 
    }
    
    //The core code for the game
    shuffling();
    giving();
    int index = firster();
    while(players[index].cardcount != 0)
    {

    }

    return 0;
}









//The definition of all the functions used in the "main"

void shuffling(void) // Shuffling the decks
{
    for (int i = 0; i < 52; i++)
    {
        int j = rand() % (i + 1);//need to add pointer to write in the Journal
        card temp = cards[i];
        cards[i] = cards[j];
        cards[j] = temp;
    }
}

void giving(player p[], int n)
{
    int index = 0;
    for(int i = 0;i < pnum;i++)
    {
        for(int r = 0;r < n;r++)
        {
            p[i].cardheld[r] = cards[index];
            index++;
        }
    }
}

card playing(player p[])
{
    printf("\n%s,you have these cards:\n", p[].name);//the writing ways p-> means the pointer p pointed at name this string
    for (int i = 0; i < p[].cardcount[]; i++)
    {
        printf("%s,%s\n", p[].cardheld[].type, p[].cardheld[].cnum);
    }

    int giving_num = get_string("Card Number(2~A)?");
    char *giving_type = get_string("Card Type(Hearts,Diamonds,Spades,Clubs)?");
    if (strcmp(p[].cardheld[].cnum, giving_num) == 0 && strcmp(giving_type, p[].cardheld[].type) == 0)
    {
        printf("Player:%s had played this card:%s %s", p->name, giving_type, giving_num);
    }
    system("clear");

    card card_played;
    card_played.type = giving_type;
    card_played.cnum = giving_num;

    return card_played;
}

int firster(void)//排序--抽一张卡--大小--决定顺序
{
    for(int i = 0;i < pnum;i++)
    {
        giving();
    }

    int min = players[0].cardheld.cnum;
    int min_num = 1;

    for(int k = 1;k < pnum;k++)
    {
        if(players[k].cardheld.cnum < min)
        {
            min = players[k].cardheld.cnum;
            min_num = k + 1;//最小的是第k + 1个人
        }
    }

    return min_num;
}

void sequence(int n)
{
    
}

void effect(card *c)
{
    if(c->cnum == 2 || c->cnum == 3)
    {
        attack(&c);
    }
    else if(c->cnum == 7)
    {
        defense();
    }
    else if(c->cnum == 12 || c->cnum == 11)
    {
        action(&c);
    }
    else
    {
        regular(&c);
    }
}

void attack(card *c)
{
    if(c->cnum == 2)
    {

    }
    else
    {

    }
}

void action(card *c)
{
    if(c->cnum == 2)
    {

    }
    else
    {

    }
}

void defense(void)
{

}

void regular(card *c)
{

}


