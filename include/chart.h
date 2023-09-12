
#include "tokeniser.h"

typedef struct {
    unsigned short side;
    int x;
    int y;
    Token* token;
} Chart;

void draw_chart(Chart* chart);

void handle_input(Chart* chart);
