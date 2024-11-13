#include <iostream>
#include "GameState.h"
#include "Graph.h"
#include "Vertex.h"
#include "Queue.h"
#include <system_error>
#include <climits>
#include <iomanip>
#include <ostream>

using namespace std;

Vec validMove(GameState game){
    //Given Function, finds the first available slot to play (easy AI)
    for (int i = 0; i < game.size; i++){
        for (int j = 0; j < game.size; j++){
            if (game.grid[i][j] == -1){
                return Vec(i, j);
            }
        }
    }
    return Vec(0,0);
}


int score(GameState& state) {
    //Function used for determining best move by Hard AI
    if (state.hasWon(0)) {
        return -1;
    } else if (state.hasWon(1)) {
        return 1;
    } else if (state.turnCount == state.size * state.size) {
        return 0;
    }
    return 0;
}

int minimax(GameState& state, int depth, bool maximizingPlayer) {
    if (depth == 0 || state.done) {
        return score(state);
    }

    if (maximizingPlayer) {
        int bestScore = -100;
        for (int i = 0; i < state.size; i++) {
            for (int j = 0; j < state.size; j++) {
                //Double for loop to get the path with best score out of all possibilities
                if (state.grid[i][j] == -1) {
                    GameState nextState = state;
                    nextState.play(i, j);
                    int score = minimax(nextState, depth - 1, false);
                    bestScore = std::max(bestScore, score);
                }
            }
        }
        return bestScore;
    } else {
        int bestScore = 100;
        for (int i = 0; i < state.size; i++) {
            for (int j = 0; j < state.size; j++) {
                //Same thing as above but for the other player since they want the opposite score to win
                if (state.grid[i][j] == -1) {
                    GameState nextState = state;
                    nextState.play(i, j);
                    int score = minimax(nextState, depth - 1, true);
                    bestScore = std::min(bestScore, score);
                }
            }
        }
        return bestScore;
    }
}

Vec findBestMove(const GameState& game) {
    //Uses Score and MiniMax functions to look at all depths and find the best possible move
    int bestScore = -100;
    Vec bestMove = Vec(0, 0);

    for (int i = 0; i < game.size; i++) {
        for (int j = 0; j < game.size; j++) {
            if (game.grid[i][j] == -1) {
                GameState nextState = game;
                nextState.play(i, j);
                int score = minimax(nextState, 5, false);
                if (score > bestScore) {
                    bestScore = score;
                    bestMove = Vec(i, j);
                }
            }
        }
    }

    return bestMove;
}

int play(int gameMode, int difficulty, int size){ // game mode, difficulty, size
    GameState game = size;
    if(gameMode ==1){
        if(difficulty == 1){
            while(!game.done){
                    system("clear");
                    cout << game << endl;
                    int x, y;
                    if (game.currentTurn){
                        Vec move = validMove(game);
                        x = move.x;
                        y = move.y;
                    }
                    else{
                        cout << endl;
                        cout << "Enter move for (" << (!game.currentTurn ? "X" : "O") << "): ";
                        cin >> x >> y;
                    }
                    game.play(x, y);
                }
        }else if(difficulty == 2){
            while(!game.done){
                    system("clear");
                    cout << game << endl;
                    int x, y;
                    if (game.currentTurn){
                        cout << "Wait for Computer" << endl;
                        Vec move = findBestMove(game);
                        x = move.x;
                        y = move.y;
                    }
                    else{
                        cout << endl;
                        cout << "Enter move for (" << (!game.currentTurn ? "X" : "O") << "): ";
                        cin >> x >> y;
                    }
                    game.play(x, y);
                }
        }
    }else{
        while(!game.done){
                    system("clear");
                    cout << game << endl;
                    int x, y;
                    if (game.currentTurn){
                        cout << endl;
                        cout << "Enter move for (" << (!game.currentTurn ? "X" : "O") << "): ";
                        cin >> x >> y;
                    }
                    else{
                        cout << endl;
                        cout << "Enter move for (" << (!game.currentTurn ? "X" : "O") << "): ";
                        cin >> x >> y;
                    }
                    game.play(x, y);
                }
    }
        system("clear");
        cout << game << endl;
        cout << endl;
        if (game.hasWon(0)){
            cout << "Player X has won" << endl;
            return 1;
        }
        else if (game.hasWon(1)){
            cout << "Player O has won" << endl;
            return -1;
        }
        else {
            cout << "It's a tie" << endl;
            return 0;
        }
    return 0;
}


int settings(int mode, int diff, int size){
    system("clear");


    string disMode, disDiff;


    disMode = "AI";
    disDiff = "Easy";


    if(mode == 1){
        disMode = "AI";
    } else if(mode == 2){
        disMode = "HUMAN";
    }


    if(diff == 1){
        disDiff = "Easy";
    } else if(diff == 2){
        disDiff = "Hard";
    }


    // describe that you can change difficulty and size
    cout << right << setw(20) << "SETTINGS" << endl << endl;
    // the return here will go to difficulty menu, size menu, and player/AI menu
    cout << "1) Gamemode (" << disMode << ")" << endl
            << "    - AI or human opponent" << endl
        << "2) AI Difficulty (" << disDiff << ")" << endl
            << "    - Easy or Hard AI" << endl
        << "3) Board Size (" << size << ")" << endl
            << "    - Size of the board" << endl
        << "4) Back" << endl << endl;


    cout << "Input: ";


    int input;
    cin >> input;
    if (input == 1 || input == 2 || input == 3 || input == 4){
        return input;
    }
    else {
        cout << "Invlaid input" << endl;
        settings(mode, diff, size);
    }
    return 0;
}
int gameMode(){ // option 1
    system("clear");
    // cout options and describe
    cout << right << setw(20) << "GAMEMODE" << endl << endl;


    cout << "1) AI" << endl
        << "2) HUMAN" << endl << endl;


    cout << "Input: ";


    int input;
    cin.ignore();
    cin >> input;
    return input;


    // return 0;
}


int difficulty(){ // option 2
    system("clear");
    // prompt with 2 choices


    cout << right << setw(20) << "AI DIFFICULTY" << endl << endl;


    cout << "1) Easy" << endl
        << "2) Hard" << endl;
    cout << "Input: ";


    int input;
    cin.ignore();
    cin >> input;
    return input;


    // return 0;
}


int boardSize(){ // option 3
    system("clear");
    // prompt with 2 choices


    cout << right << setw(20) << "BOARD SIZE!" << endl << endl;


    cout << "Input a number for boardsize!" << endl;
    cout << "Input: ";


    int input;
    cin >> input;
    return input;
}




int main(){
    bool quit = false;
    int input, mode, diff, size; // default settings
    mode = 1;        
    diff = 1;
    size = 3;


    while(!quit){ // if the user chooses quit, it will exit the program
        system("clear");
        cout << std::right << std::setw(20) << "TIC-TAC-TOE" << endl << endl;
        // choices
        cout << "1) PLAY" << endl
                // play the game with selected settings
            << "2) SETTINGS" << endl
                // friend or AI
                // AI difficulty
                // Size
            << "3) QUIT" << endl << endl;
        cout << "Please input your choice: ";


// menu functionality
        cin >> input;
        if (input == 1){ // play
            int win;
            win = play(mode, diff, size);
            if(mode == 1){
                string temp = "d";
                if(win == 0){
                    // tie
                    cout << "Press enter to continue: ";
                    temp = cin.get();
                    cin.ignore();
                } else if (win == 1){
                    // win
                    cout << "Press enter to continue: ";
                    temp = cin.get();
                    cin.ignore();
                } else if (win == -1){
                    // lose
                    cout << "Press enter to continue: ";
                    temp = cin.get();
                    cin.ignore();
                }
            }

        } else
        if (input == 2){ // settings
            int x = settings(mode, diff, size);
            if (x == 1){ // gamemode
                mode = gameMode();
            } else if (x == 2) { // difficulty
                diff = difficulty();
            } else if (x == 3){ // board size
                size = boardSize();
            } else if(x == 4){ // back to main menu
                continue;
            }else{
                cout << "Invalid input" << endl;
            }
        } else
        if (input == 3){ // quit option
            quit = true;
        }
    }
    return 0;
}
