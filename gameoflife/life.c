#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define COLS  25
#define ROWS  25
#define CELLS  (COLS * ROWS)
#define ALIVE '*'
#define DEAD  ' '
#define GENS  100

void clear(void) {
    printf("\x1B[2J");
}

int cell_to_offset(int x, int y) {
    if (x < 0) {
        x = (-x) % COLS;
        x = COLS - x;
    }
    if (y < 0) {
        y = (-y) % COLS;
        y = COLS - y;
    }
    if (x >= COLS) x = x % COLS;
    if (y >= ROWS) y = y % ROWS;

    return y*COLS + x;
}

void set_cell(char *grid, int x, int y, char state) {
    grid[cell_to_offset(x, y)] = state;
}

char get_cell(char *grid, int x, int y) {
    return grid[cell_to_offset(x, y)];
}

void set_grid(char *grid, char state) {
    for (int y = 0; y < ROWS; y++) {
        for (int x = 0; x < COLS; x++) {
            set_cell(grid, x, y, state);
        }
    }
}

void print_grid(char *grid) {
    for (int y = 0; y < ROWS; y++) {
        for (int x = 0; x < COLS; x++) {
            printf("%c ", get_cell(grid, x, y));
        }
        printf("\n");
    }
}

int count_alive_neighbours(char *grid, int x, int y) {
    int count = 0;
    for (int i = -1; i <= 1; i++) { // Rows
        for (int j = -1; j <= 1; j++) { // Cols
            int col = x + j;
            int row = y + i;
            if (!(x == col && y == row) && get_cell(grid, col, row) == ALIVE) {
                count++;
            }
        }
    }
    return count;
}

void next_generation(char *old_grid, char *new_grid) {
    for (int y = 0; y < ROWS; y++) {
        for (int x = 0; x < COLS; x++) {
            int neighbours = count_alive_neighbours(old_grid, x, y);
            char state = DEAD;
            if (get_cell(old_grid, x, y) == ALIVE) {
                if (neighbours == 2 || neighbours == 3) state = ALIVE;
            } else {
                if (neighbours == 3) state = ALIVE;
            }
            set_cell(new_grid, x, y, state);
        }
    }
}

int main(void) {
    char old_grid[CELLS];
    char new_grid[CELLS];

    set_grid(old_grid, DEAD);

    // Initial Seed
    set_cell(old_grid, 5, 10, ALIVE);
    set_cell(old_grid, 5, 11, ALIVE);
    set_cell(old_grid, 4, 11, ALIVE);
    set_cell(old_grid, 5, 12, ALIVE);
    set_cell(old_grid, 6, 12, ALIVE);


    int generation_count = 1;
    while (1) {
        clear();
        printf("Generations: %d\n", generation_count);
        print_grid(old_grid);
        next_generation(old_grid, new_grid);
        generation_count++;
        usleep(100 * 700);

        clear();
        printf("Generations: %d\n", generation_count);
        print_grid(new_grid);
        next_generation(new_grid, old_grid);
        usleep(100 * 700);
    }
}
