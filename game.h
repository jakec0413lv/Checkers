#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Game {
private:
    char board[8][8];
    int redPiecesRemaining = 12;
    int blackPiecesRemaining = 12;
    int rows = 8;
    int cols = 8;

public:
    Game();
    void showBoard();
    void selectPiece(string );

    bool checkValidColumn(int );
    bool checkValidRow(int );
    bool checkPossibleMoves(string, int, int);
    bool checkPossibleJumpLeft(string color, int i, int j);
    bool checkPossibleJumpRight(string color, int i, int j);

    int getRemainingPieces(string );
};

Game::Game(){
    //Populate Board
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            if(i == 0 || i ==2){
                if(j % 2 == 0){
                    board[i][j] = 'R';
                    continue;
                }else{
                    board[i][j] = ' ';
                    continue;
                }
            }
            if(i == 1){
                if(j % 2 == 1){
                    board[i][j] = 'R';
                    continue;
                }else{
                    board[i][j] = ' ';
                }
            }
            if(i == 3 || i ==4){
                board[i][j] = ' ';
            }
            if(i == 5 || i ==7){
                if(j % 2 == 1){
                    board[i][j] = 'B';
                    continue;
                }else{
                    board[i][j] = ' ';
                    continue;
                }
            }
            if(i == 6){
                if(j % 2 == 0){
                    board[i][j] = 'B';
                    continue;
                }else{
                    board[i][j] = ' ';
                }
            }
        }   
    }
}

void Game::showBoard(){
    cout << "  ";
    for(int i = 0; i < cols; i++){
        cout << i << " ";
    }
    cout << '\n';
    cout << "------------------" << '\n';
    for(int i = 0; i < rows; i++){
        cout << i << "|";
        for(int j = 0; j < cols; j++){
            cout << board[i][j] << " ";
        }
        cout << '\n';
    }
}



bool Game::checkValidRow(int r){
    if(r < 0 || r > rows - 1){
        return false;
    }else{
        return true;
    }
}

bool Game::checkValidColumn(int c){
    if(c < 0 || c > cols - 1){
        return false;
    } else{
        return true;
    }
}

void Game::selectPiece(string color){
    int i;
    int j;
    int i_m;
    int j_m;

    bool correctPiece = false;
    bool validMove = false;

    do{

    if(color == "red"){
        cout << " ---------------- " << '\n';
        cout << "RED MOVE" << '\n';
        cout << " ---------------- " << '\n';
    } else{
        cout << " ---------------- " << '\n';
        cout << "BLACK MOVE" << '\n';
        cout << " ---------------- " << '\n';
    }

    cout << "Select row for desired piece: " << '\n';
        cin >> i;
    //Input validation & Proper Row Values
    while(!cin || !(checkValidRow(i))){
    cin.clear();
    cin.ignore(40, '\n'); 
    cout << "Select row for desired piece: " << '\n';
        cin >> i;
    }

    cout << "Select column for desired piece: " << '\n';
        cin >> j;
    //Input validation & Proper Col Values
    while(!cin || !(checkValidColumn(j))){
    cin.clear();
    cin.ignore(40, '\n'); 
    cout << "Select color for desired piece: " << '\n';
        cin >> j;
    }

    if(color == "red"){
        if(board[i][j] == 'R'){
            if(checkPossibleMoves("red", i, j)){
               cout << "Selected piece marked with an X" << '\n';
                board[i][j] = 'X';
                correctPiece = true; 
            }
            else{
                cout << "No possible moves!" << '\n';
                continue;
            }
        } else if(board[i][j] == 'B'){
            cout << "Please choose a piece of the correct color!"<< '\n';
            continue;
        } else{
            cout << "You selected an empty space.. Try again!" << '\n';
            continue;
        }
    }

    if(color == "black"){
        if(board[i][j] == 'B'){
            if(checkPossibleMoves("black", i, j)){
               cout << "Selected piece marked with an X" << '\n';
                board[i][j] = 'X';
                correctPiece = true; 
            } else{
                cout << "No possible moves!" << '\n';
            }
        } else if(board[i][j] == 'R'){
            cout << "Please choose a piece of the correct color!"<< '\n';
            continue;
        } else{
            cout << "You selected an empty space.. Try again!" << '\n';
            continue;
        }
    }

    showBoard();

    }while(!(correctPiece));

    do{

    cout << "Pick a row to move to: " << '\n';
        cin >> i_m;
    while(!cin || !(checkValidRow(i_m))){
        cin.clear();
        cin.ignore(40, '\n'); 
        cout << "Pick a row to move to: " << '\n';
        cin >> i_m;
    }

    cout << "Pick a column to move to: " << '\n';
        cin >> j_m;
    while(!cin || !(checkValidColumn(j_m))){
        cin.clear();
        cin.ignore(40, '\n'); 
        cout << "Pick to column to move to: " << '\n';
        cin >> i_m;
    }
    if(color == "red" && i_m < i ){
        cout << "Invalid Move" << '\n';
        continue;
    }
    if(color == "black" && i_m > i ){
        cout << "Invalid Move" << '\n';
        continue;
    }
//Check for invalid/asymmetric moves
    if((abs(i - i_m) > 2) || (abs(j - j_m) > 2) || (abs(i - i_m) != abs(j - j_m)) || (i - i_m == 0) || (j-j_m == 0)){
        cout << "Invalid Move" << '\n';
        continue;
    }

    if(color == "red"){
    //Move to empty space
    if(board[i_m][j_m] == ' ' && (abs(i - i_m) == 1) && (abs(j - j_m)) == 1 ){
        board[i][j] = ' ';
        board[i_m][j_m] = 'R';
        validMove = true;
    }
    //Jump over opposing piece
    if((checkPossibleJumpLeft("red", i, j) || checkPossibleJumpRight("red", i, j))  && (abs(i - i_m) == 2) && (abs(j - j_m)) == 2){
        board[i][j] = ' ';
        if(board[i_m - 1][j_m - 1] == 'B'){
            board[i_m - 1][j_m - 1] = ' ';
        }
        if (board[i_m - 1][j_m + 1] == 'B'){
            board[i_m - 1][j_m + 1] = ' ';
        }
        board[i_m][j_m] = 'X';
        i = i_m;
        j = j_m;
        while((checkPossibleJumpLeft("red", i, j) || checkPossibleJumpRight("red", i, j))){
            cout << "Second jump possible: " << '\n';   
            cout << "Select a row: " << '\n';
                cin >> i_m;
            while(!(checkValidRow(i_m)) && !cin && abs(i-i_m) != 2){
                cout << "Select a valid row" << '\n';
            }  
            cout << "Select a column: " << '\n';
                cin >> j_m;
            while(!(checkValidColumn(j_m)) && !cin && abs(j-j_m) != 2){
                cout << "Select a valid row" << '\n';
            }
            board[i][j] = ' ';
            if(board[i_m - 1][j_m - 1] == 'B'){
             board[i_m - 1][j_m - 1] = ' ';
            }
            if (board[i_m - 1][j_m + 1] == 'B'){
                board[i_m - 1][j_m + 1] = ' ';
            }
            board[i_m][j_m] = 'X';
            i = i_m;
            j = j_m;
            blackPiecesRemaining--;
        }
        board[i][j] = 'R';
        validMove = true;
        blackPiecesRemaining--;
    }
    }

    if(color == "black"){
    if(board[i_m][j_m] == ' ' && (abs(i - i_m) == 1) && (abs(j - j_m)) == 1 ){
        board[i][j] = ' ';
        board[i_m][j_m] = 'B';
        validMove = true;
    }
    if((checkPossibleJumpLeft("black", i, j) || checkPossibleJumpRight("black", i, j))  && (abs(i - i_m) == 2) && (abs(j - j_m)) == 2){
        board[i][j] = ' ';
        if(board[i_m + 1][j_m - 1] == 'R'){
            board[i_m + 1][j_m - 1] = ' ';
        }
        if (board[i_m + 1][j_m + 1] == 'R'){
            board[i_m + 1][j_m + 1] = ' ';
        }
        board[i_m][j_m] = 'X';
        i = i_m;
        j = j_m;
        showBoard();
        while((checkPossibleJumpLeft("black", i, j) || checkPossibleJumpRight("black", i, j))){
            cout << "Second jump possible: " << '\n';   
            cout << "Select a row: " << '\n';
                cin >> i_m;
            while(!(checkValidRow(i_m)) && !cin && abs(i-i_m) != 2){
                cout << "Select a valid row" << '\n';
            }  
            cout << "Select a column: " << '\n';
                cin >> j_m;
            while(!(checkValidColumn(j_m)) && !cin && abs(j-j_m) != 2){
                cout << "Select a valid row" << '\n';
            }
            board[i][j] = ' ';
            if(board[i_m + 1][j_m - 1] == 'R'){
             board[i_m + 1][j_m - 1] = ' ';
            }
            if (board[i_m + 1][j_m + 1] == 'R'){
                board[i_m + 1][j_m + 1] = ' ';
            }
            board[i_m][j_m] = 'X';
            i = i_m;
            j = j_m;
            redPiecesRemaining--;
            showBoard();
        }
        board[i][j] = 'B';
        validMove = true;
        redPiecesRemaining--;
    }
    }

    }while(!(validMove));
    cout << "Red Pieces Remaining: " << redPiecesRemaining <<'\n';
    cout << "Black Pieces Remaining: " << blackPiecesRemaining << '\n';
    showBoard();
    
}

bool Game::checkPossibleMoves(string color, int i, int j){
    bool movesLeft;
    bool movesRight;
    if(color == "red"){
        if(checkValidRow(i + 1) && checkValidColumn(j - 1)){
            if(board[i + 1][j - 1] == ' ' || checkPossibleJumpLeft("red", i, j)){
                movesLeft = true;
            }
        } else{
            movesLeft = false;
        }
        if(checkValidRow(i + 1) && checkValidColumn(j + 1)){
            if(board[i + 1][j + 1] == ' ' || checkPossibleJumpRight("red", i, j)){
                movesRight = true;
            }
        } else{
            movesRight = false;
        }
    }

    if(color == "black"){
        if(checkValidRow(i - 1) && checkValidColumn(j - 1)){
            if(board[i - 1][j - 1] == ' ' || checkPossibleJumpLeft("black", i, j)){
                movesLeft = true;
            }
        } else{
            movesLeft = false;
        }
        if(checkValidRow(i - 1) && checkValidColumn(j + 1)){
            if(board[i - 1][j + 1] == ' ' || checkPossibleJumpRight("black", i, j)){
                movesRight = true;
            }
        } else{
            movesRight = false;
        }
    }
    return (movesLeft || movesRight);
}

bool Game::checkPossibleJumpLeft(string color, int i, int j){
    if(color == "red"){
        if(checkValidRow(i + 2) && checkValidColumn(j - 2)){
            if(board[i + 1][j - 1] == 'B' && board[i + 2][j - 2] == ' '){
                return true;
            }
        }
}
    if(color == "black"){
        if(checkValidRow(i - 2) && checkValidColumn(j - 2)){
            if(board[i  -1][j - 1] == 'R' && board[i - 2][j - 2] == ' '){
                return true;
            }
        }
}
return false;
}

bool Game::checkPossibleJumpRight(string color, int i, int j){
    if(color == "red"){
        if(checkValidRow(i + 2) && checkValidColumn(j + 2)){
            if(board[i + 1][j + 1] == 'B' && board[i + 2][j + 2] == ' '){
                return true;
            }
        }
}
    if(color == "black"){
        if(checkValidRow(i - 2) && checkValidColumn(j + 2)){
            if(board[i - 1][j + 1] == 'R' && board[i - 2][j + 2] == ' '){
                return true;
            }
        }
}
return false;
}

int Game::getRemainingPieces(string color){
    if(color == "red"){
        return redPiecesRemaining;
    }else{
        return blackPiecesRemaining;
    }
}