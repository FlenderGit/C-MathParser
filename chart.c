#include <stdio.h>
#include <stdlib.h>

#include <conio.h>
#include "include/chart.h"
#include "include/eval.h"

void draw_chart(Chart* chart)
{

    double* results = malloc(sizeof(double)*(chart->side*2+1));
    if (results==NULL){
        printf("ERROR ALOOC");
        exit(1);
    }

    int i;
    for(i=0; i<chart->side*2+1; ++i){
        results[i] = eval_var(chart->token, chart->x-chart->side+i);
        printf("%d : %g\n", i, results[i]);
    }

    
    for(int y=chart->y+chart->side+1;y>chart->y-chart->side;--y){
        printf("|");
        i=0;
        for(int x=chart->x-chart->side;x<chart->x+chart->side+1;++x){
            
            if(results[i]==y){
                printf("X");
            } else if(x==0||y==0){
                printf("O");
            } else {
                printf(" ");
            }
            ++i;
        }
        printf("|\n");
    }
    
    free(results);
}

void handle_input(Chart* chart)
{
    int ch;
    
    for(;;) {
        ch = _getch();

        if (ch == 27) {
            printf("Vous avez appuyé sur la touche 'Esc'. Sortie du programme...\n");
            break;
        }

        _Bool isArrow = 0;

        switch(ch) {
            case 72: chart->y++; isArrow=1; break;
            case 77: chart->x++; isArrow=1; break;
            case 80: chart->y--; isArrow=1; break;
            case 75: chart->x--; isArrow=1; break;
        }

        if(isArrow){
            printf("\e[1;1H\e[2J");
            draw_chart(chart);
            printf("Use arraws to move or esc to quit");
        }
    }
}
