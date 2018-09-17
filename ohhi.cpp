/**
 * ohhi.cpp
 *
 * EECS 183
 * Project 3: 0h h1
 * Winter 2018
 *
 * Abpreet Kaur, Anne Lin
 * abpreetk linanne
 *
 * Project 3 C++ Program to play a game of Ohhi
 */

#include <iostream>
#include <cctype>
#include "utility.h"
#include "ohhi.h"

/**
 * --------------------------------------------------------
 * ---------- UTILITY FUNCTIONS ---------------------------
 * --------------------------------------------------------
 */

int count_unknown_squares(const int board[MAX_SIZE][MAX_SIZE], int size) {
    // Counts Oh h1 board for unknown squares using row and column array
    int i = 0;
    int j = 0;
    int countUnknown = 0;
    
    for (i = 0; i < size; i++) {
        for (j = 0; j < size; j++) {
            if (board[i][j] == UNKNOWN) {
                countUnknown++;
            }
        }
    }
    return countUnknown;
}

/**
 * --------------------------------------------------------
 * --------- VALIDITY CHECKING FUNCTIONS ------------------
 * --------------------------------------------------------
 */


bool row_has_no_threes_of_color(const int board[MAX_SIZE][MAX_SIZE],
                                int size,
                                int row,
                                int color) {
    
    //if color is red (red is X)
    if (color == 1) {
        for (int i = 0; i < size - 2; i++) {
            if (board[row][i] == 'X' && board[row][i + 1] == 'X' &&
                board[row] [i + 2] == 'X') {
                return false;
            }
        }
    }
    
    //if color is blue (blue is O)
    if (color == 2) {
        for (int i = 0; i < size - 2; i++) {
            if (board[row][i] == 'O' && board[row][i + 1] == 'O'&&
                board[row][i + 2] == 'O') {
                return false;
            }
        }
    }
    return true;
}


bool col_has_no_threes_of_color(const int board[MAX_SIZE][MAX_SIZE],
                                int size,
                                int col,
                                int color) {
    
    //if color is red (red is X)
    if (color == 1) {
        for (int i = 0; i < size - 2; i++) {
            if (board[col][i] == 'X' && board[col][i + 1] == 'X' &&
                board[col] [i + 2] == 'X') {
                return false;
            }
        }
    }
    
    //if color is blue (blue is O)
    if (color == 2) {
        for (int i = 0; i < size - 2; i++) {
            if (board[col][i] == 'O' && board[col][i + 1] == 'O' &&
                board[col] [i + 2] == 'O') {
                return false;
            }
        }
    }
    return true;
}


bool rows_are_different(const int board[MAX_SIZE][MAX_SIZE],
                        int size,
                        int row1,
                        int row2) {
    
    int counter = 0;
    
    for (int i = 0; i < size; i++) {
        if (board[row1][i] == UNKNOWN ||
            board[row2][i] == UNKNOWN) {
            return true;
        }
        
        if (board[row1][i] == board[row2][i]) {
            counter++;
        }
        
    }
    
    if (counter == size) {
        return false;
    } else {
        return true;
    }
    
}


bool cols_are_different(const int board[MAX_SIZE][MAX_SIZE],
                            int size,
                            int col1,
                            int col2) {
        
    int counter = 0;
        
    for (int i = 0; i < size; i++) {
        if (board[i][col1] == UNKNOWN ||
            board[i][col2] == UNKNOWN) {
                return true;
        }
            
        if (board[i][col1] == board[i][col2]) {
                counter++;
        }
            
    }
    
    if (counter == size) {
            return false;
    } else {
            return true;
    }

}

bool board_has_no_duplicates(const int board[MAX_SIZE][MAX_SIZE], int size) {
    
    for(int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if(rows_are_different(board, size, i, j) &&
               cols_are_different(board, size, i, j)) {
                return true;
            }
        }
    }
    return false;
}


/**
 * --------------------------------------------------------
 * ---------- SOLVING FUNCTIONS ---------------------------
 * --------------------------------------------------------
*/


void solve_three_in_a_row(int board[MAX_SIZE][MAX_SIZE],
                          int size,
                          int row,
                          bool announce) {
    
    int opposite_color = 0;
    int new_mark_location = 0;
    
    for (int i = 0; i < size - 1; i++) {
        //cases:
        
        //establish what the opposite color is
        if (board[row][i] == 1) {
            opposite_color = 2;
        } else if (board[row][i] == 2){
            opposite_color = 1;
        }
        
        //two consecutive tiles
        if (board[row][i] == board[row][i+1]) {
            
            //first two are consecutive
            if (i == 0 && board[row][2] == UNKNOWN) {
                new_mark_location = 2;
                mark_square_as (board, size, row, new_mark_location, opposite_color, announce);
                
            //last two are consecutive
            } else if (i == size - 2 && board[row][size - 3] == UNKNOWN) {
                new_mark_location = size - 3;
                mark_square_as(board, size, row, new_mark_location, opposite_color, announce);
                
            //middle two are consecutive
            } else if (board[row][i - 1] == UNKNOWN && board[row][i + 2] == UNKNOWN)
                new_mark_location = i - 1;
            mark_square_as(board, size, row, new_mark_location, opposite_color, announce);
            
            new_mark_location = i + 2;
            mark_square_as(board, size, row, new_mark_location, opposite_color, announce);
        }
    }
    
        //unknown in between two tiles
        int i = 0;
    
        if (i < size - 2 && board[row][i] == board[row][i + 2] && board[row][i + 1] == UNKNOWN) {
            new_mark_location = i + 1;
            mark_square_as(board, size, row, new_mark_location, opposite_color, announce);
        }
}

void solve_three_in_a_column(int board[MAX_SIZE][MAX_SIZE],
                             int size,
                             int col,
                             bool announce) {
    int opposite_color = 0;
    int new_mark_location = 0;
    
    for (int i = 0; i < size - 1; i++) {
        //cases:
        
        //establish what the opposite color is
        if (board[i][col] == 1) {
            opposite_color = 2;
        } else if (board[i][col] == 2){
            opposite_color = 1;
        }
        
        //two consecutive tiles
        if (board[i][col] == board[i + 1][col]) {
            
            //first two are consecutive
            if (i == 0 && board[2][col] == UNKNOWN) {
                new_mark_location = 2;
                mark_square_as (board, size, new_mark_location, col, opposite_color, announce);
                
            //last two are consecutive
            } else if (i == size - 2 && board[size - 3][col] == UNKNOWN) {
                new_mark_location = size - 3;
                mark_square_as(board, size, new_mark_location, col, opposite_color, announce);
                
            //middle two are consecutive
            } else if (board[i - 1][col] == UNKNOWN && board[i + 2][col] == UNKNOWN)
                new_mark_location = i - 1;
            mark_square_as(board, size, new_mark_location, col, opposite_color, announce);
            
            new_mark_location = i + 2;
            mark_square_as(board, size, new_mark_location, col, opposite_color, announce);
        }
        
        //unknown in between two tiles
        if (i < size - 2 && board[i][col] == board[i + 2][col] && board[i + 1][col] == UNKNOWN) {
            new_mark_location = i + 1;
            mark_square_as(board, size, new_mark_location, col, opposite_color, announce);
        }
    }
    
    return;
}


void solve_balance_row(int board[MAX_SIZE][MAX_SIZE],
                       int size,
                       int row,
                       bool announce) {
    int blueVal = 0;
    int redVal = 0;
    int col;
    
    //Determine how many red and blue squares in col using counter
    for (col = 0; col < size; col++) {
        if (board[row][col] == BLUE) {
            blueVal++;
        }
        
        if (board[row][col] == RED) {
            redVal++;
        }
    }
    
    //Check for only half squares are color (red or blue) and replace with underrepresented color
    if (blueVal == size / 2) {
        for (col = 0; col < size; col++) {
            if (board[row][col] == UNKNOWN) {
                mark_square_as(board, size, row, col, RED, announce);
            }
        }
    }
    else if (redVal == size / 2) {
        for (int col = 0; col < size; col++) {
            if (board[row][col] == UNKNOWN) {
                mark_square_as(board, size, row, col, BLUE, announce);
            }
        }
    }
    
}

void solve_balance_column(int board[MAX_SIZE][MAX_SIZE],
                          int size,
                          int col,
                          bool announce) {
    int blueVal = 0;
    int redVal = 0;
    int row;
    
    //Determine how many red and blue squares in col using counter
    for (row = 0; row < size; row++) {
        if (board[row][col] == BLUE) {
            blueVal++;
        }
        
        if (board[row][col] == RED) {
            redVal++;
        }
    }
    
    //Check for only half squares are color (red or blue) and replace with underrepresented color
    if (blueVal == size / 2) {
        for (row = 0; row < size; row++) {
            if (board[row][col] == UNKNOWN) {
                mark_square_as(board, size, row, col, RED, announce);
            }
        }
    }
    else if (redVal == size / 2) {
        for (int row = 0; row < size; row++) {
            if (board[row][col] == UNKNOWN) {
                mark_square_as(board, size, row, col, BLUE, announce);
            }
        }
    }
    
}


/**
 * --------------------------------------------------------
 * ---------- GAMEPLAY FUNCTIONS --------------------------
 * --------------------------------------------------------
 */

bool board_is_solved(const int board[MAX_SIZE][MAX_SIZE], int size) {
    // write your code here

    // replace this return statement
    return false;
}

bool check_valid_input(int size, int row_input, char col_input,
                       char color_char, int &row, int &col) {
    // write your code here

    // replace this return statement
    return false;
}

bool check_valid_move(const int original_board[MAX_SIZE][MAX_SIZE],
                      const int current_board[MAX_SIZE][MAX_SIZE],
                      int size, int row, int col, int color) {
    // write your code here

    // replace this return statement
    return false;
}


/**
 * --------------------------------------------------------
 * ---------------- S'MORES FUNCTIONS    ------------------
 * ---------- DO NOT DELETE THESE FUNCTIONS ---------------
 * ------------- FOR THE REGULAR PROJECT ------------------
 * --------------------------------------------------------
 */

void solve_lookahead_row(int board[MAX_SIZE][MAX_SIZE],
                         int size,
                         int row,
                         bool announce) {
    // write your code here

    return;
}

void solve_lookahead_column(int board[MAX_SIZE][MAX_SIZE],
                            int size,
                            int col,
                            bool announce) {
    // write your code here
    return;
}


