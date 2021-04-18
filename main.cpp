#include <iostream>
#include <vector>
#include <string>

#include "game.h"

using namespace std;


int main() {
    Game newGame;

do{
    newGame.showBoard();
    newGame.selectPiece("red");
    newGame.selectPiece("black");
}while(newGame.getRemainingPieces("red") != 0 && newGame.getRemainingPieces("black") != 0);

    if(newGame.getRemainingPieces("red") == 0){
        cout << "BLACK WINS!" << '\n';
    }else{
        cout << "RED WINS!" << '\n';
    }
    return 0;
}