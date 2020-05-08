//
//  playMove.cpp
//  TicTacTo
//
//  Updated by Tarek Abdelrahman on 2019-06-07.
//  Created by Tarek Abdelrahman on 2018-05-15.
//  Copyright © 2018-2019 Tarek Abdelrahman. All rights reserved.
//

#include "tictactoe.h"
#include "gameState.h"
#include <iostream>
void playMove(gameState& game_state) {
  
    //the next turn should be "X" or "O" 
    int term;
    if (game_state.get_turn()==true){
        term=X;
    }
    else{
        term=O;
    }
    
    //determine the coordinate that the player clicked on
    int row, col;
    row = game_state.get_clickedRow();
    col = game_state.get_clickedColumn();
    
    //to check if the coordinate is valid or invalid (if the position is empty, then it is valid, if the position is either has X or O then invalid and need to get another position)
    if (game_state.get_gameBoard(row, col) == Empty) {
        //valid case can be continued
        game_state.set_moveValid(true);
        //put the turn on the board
        game_state.set_gameBoard(row, col, term);
        //change the next term to be the other one of the current term
        game_state.set_turn(!game_state.get_turn());
    } 
    else {
        //invalid case
        game_state.set_moveValid(false);
    }

    
    
    //all conditions for game over (win+no win)
    if ((game_state.get_gameBoard(0, 0) == X && game_state.get_gameBoard(0, 1) == X && game_state.get_gameBoard(0, 2) == X) || (game_state.get_gameBoard(0, 0) == O && game_state.get_gameBoard(0, 1) == O && game_state.get_gameBoard(0, 2) == O)) {
            game_state.set_winCode(1);
            game_state.set_gameOver(true);
    }
    if ((game_state.get_gameBoard(1, 0) == X && game_state.get_gameBoard(1, 1) == X && game_state.get_gameBoard(1, 2) == X) || (game_state.get_gameBoard(1, 0) == O && game_state.get_gameBoard(1, 1) == O && game_state.get_gameBoard(1, 2) == O)) {
        game_state.set_winCode(2);
        game_state.set_gameOver(true);
    }
    if ((game_state.get_gameBoard(2, 0) == X && game_state.get_gameBoard(2, 1) == X && game_state.get_gameBoard(2, 2) == X) || (game_state.get_gameBoard(2, 0) == O && game_state.get_gameBoard(2, 1) == O && game_state.get_gameBoard(2, 2) == O)) {
        game_state.set_winCode(3);
        game_state.set_gameOver(true);
    }
    if ((game_state.get_gameBoard(0, 0) == X && game_state.get_gameBoard(1, 0) == X && game_state.get_gameBoard(2, 0) == X) || (game_state.get_gameBoard(0, 0) == O && game_state.get_gameBoard(1, 0) == O && game_state.get_gameBoard(2, 0) == O)) {
        game_state.set_winCode(4);
        game_state.set_gameOver(true);
    }
    if ((game_state.get_gameBoard(0, 1) == X && game_state.get_gameBoard(1, 1) == X && game_state.get_gameBoard(2, 1) == X) || (game_state.get_gameBoard(0, 1) == O && game_state.get_gameBoard(1, 1) == O && game_state.get_gameBoard(2, 1) == O)) {
        game_state.set_winCode(5);
        game_state.set_gameOver(true);
    }
    if ((game_state.get_gameBoard(0, 2) == X && game_state.get_gameBoard(1, 2) == X && game_state.get_gameBoard(2, 2) == X) || (game_state.get_gameBoard(0, 2) == O && game_state.get_gameBoard(1, 2) == O && game_state.get_gameBoard(2, 2) == O)) {
        game_state.set_winCode(6);
        game_state.set_gameOver(true);
    }
    if ((game_state.get_gameBoard(0, 0) == X && game_state.get_gameBoard(1, 1) == X && game_state.get_gameBoard(2, 2) == X) || (game_state.get_gameBoard(0, 0) == O && game_state.get_gameBoard(1, 1) == O && game_state.get_gameBoard(2, 2) == O)) {
        game_state.set_winCode(7);
        game_state.set_gameOver(true);
    }
    if ((game_state.get_gameBoard(0, 2) == X && game_state.get_gameBoard(1, 1) == X && game_state.get_gameBoard(2, 0) == X) || (game_state.get_gameBoard(0, 2) == O && game_state.get_gameBoard(1, 1) == O && game_state.get_gameBoard(2, 0) == O)) {
        game_state.set_winCode(8);
        game_state.set_gameOver(true);
    }
    if (game_state.get_gameBoard(0, 0) == Empty && game_state.get_gameBoard(0, 1) == Empty && game_state.get_gameBoard(0, 2) == Empty &&
            game_state.get_gameBoard(1, 0) == Empty && game_state.get_gameBoard(1, 1) == Empty && game_state.get_gameBoard(1, 2) == Empty &&
            game_state.get_gameBoard(2, 0) == Empty && game_state.get_gameBoard(2, 1) == Empty && game_state.get_gameBoard(2, 2) == Empty
            && (!game_state.get_gameOver())) {
        game_state.set_winCode(0);
        game_state.set_gameOver(true);
    }

    

        
    
}

