#include <iostream>
#include <vector>
#include <string>

#include "game.h"

using namespace std;


int main() {
    Game newGame;
    bool playing = true;

do{
    newGame.showBoard();
    newGame.selectPiece("red");
    newGame.selectPiece("black");
    if(newGame.getRemainingPieces("red") == 0 || newGAme.getRemainingPieces("black") == 0){
        playing = false;
    }
}while(playing);

    if(newGame.getRemainingPieces("red") == 0){
        cout << "BLACK WINS!" << '\n';
    }else{
        cout << "RED WINS!" << '\n';
    }
    return 0;
}