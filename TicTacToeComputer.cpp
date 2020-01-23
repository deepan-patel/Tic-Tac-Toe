/*TIC-TAC-TOE [game]

Deepan Patel
CSCI 1060U-008
NOV 4th 2018

*/

#include <iostream>
#include <string>
#include <sstream>
#include <ctime>
#include <cstdlib>

using namespace std;
//gobal variables
int row;
int col;
bool isPLayer1;

//Each type of win sets to false if can no longer be won there
//each index corrisponds to type number ex. rows_check[0] means row 1
bool rows_check[] = {true,true,true};
bool cols_check[] = {true,true,true};
bool di_check[] = {true,true};

//All the count var for each type of win
int r1Count = 0;
int r2Count = 0;
int r3Count = 0;
int c1Count = 0;
int c2Count = 0;
int c3Count = 0;
int d1Count = 0;
int d2Count = 0;



//Arrays for each type of count
int columns[]  = {c1Count,c2Count,c3Count};
int rows[]  = {r1Count,r2Count,r3Count};
int diagonals[] = {d1Count,d2Count};

const int SIZE = 3;

//declaration of functions
void displayBoard(string b[][SIZE]);
bool userFirst();
bool currentPlayerWon(string b[][SIZE], string symbol);

//All new functions made
//generate a smart calclulated move based of the user decision
void computerMove(int& row,int& col,string board[][SIZE]);
//updates count based on player type & what location can still be won
void updateCount(int& row,int& col,bool isPLayer1);
//Determines the row and col where the computer should place it value
//return true if decided
bool determinePlacement(int& row,int& col,string board[][SIZE]);


int main() {
  //construct board
  string board[SIZE][SIZE];

  int position_id = 1;
  for (int i=0; i< SIZE; i++) {
    for (int j=0; j < SIZE; j++) {
        board[i][j] = to_string(position_id);
      /*  stringstream ss;
        ss << position_id;
        board[i][j] = ss.str();
        */position_id++;
    }
  }

  //Initial game output
  cout << "Welcome to Tic-Tac-Toe" << endl;

  bool userTurn = userFirst();

  if (userTurn == true) {
    cout << "Player goes first!" << endl;
  } else {
    cout << "Computer goes first!" << endl;
  }

  //Loop for turn taking in game
  int positionsRemaining = SIZE * SIZE;
  bool userWon = false;
  bool computerWon = false;

  while ((positionsRemaining > 0)
        && (!userWon) && (!computerWon)) {
      displayBoard(board);

      //User's turn
      if (userTurn) {
        bool validMove = false;
        isPLayer1 = true;
        while (!validMove) {
          int position_id;
          cout << "Enter a position: ";
          cin >> position_id;
          if ((position_id <= (SIZE*SIZE))
              && (position_id > 0)) {
            int row = (position_id-1)/SIZE;
            int col = (position_id-1)%SIZE;
            //cout << "row = " << row << " col = " << col << endl;
            if ((board[row][col] != "X")
                && (board[row][col] != "O")) {
                  board[row][col] = "X";
                  //count is updated once placed
                  updateCount(row,col,isPLayer1);

                  validMove = true;
            } else {
              cout << "Position already used. Try again." << endl;
            }

          } else {
            cout << "Position invalid. Try again." << endl;
          }
        }
        positionsRemaining--;
        userWon = currentPlayerWon(board, "X");
        userTurn = false;
      }

      //Computer's turn
      else {
        isPLayer1 = false;
        //Computer chooses a spot then it is placed
        computerMove(row,col,board);
        positionsRemaining--;
        computerWon = currentPlayerWon(board, "O");
        userTurn = true;
      }
  
  }

  //Display game result
  displayBoard(board);
  if (userWon) {
    cout << "Congratulations! You have won!" << endl;
  } else if (computerWon) {
    cout << "The computer has won. Try again." << endl;
  } else {
    cout << "Out of moves. Try again." << endl;
  }
  return 0;
}

void displayBoard(string b[][SIZE]) {
  cout << "Tic-tac-toe board:" << endl << endl;
  for (int i=0; i< SIZE; i++) {
    for (int j=0; j < SIZE; j++) {
        cout << b[i][j] << "\t";
    }
    cout << endl;
  }
  cout << endl;
}

bool userFirst() {
  //set seed for random number generation
  srand(time(NULL));

  //generate a random number
  //0 for computer
  //1 for user
  int num = rand()%2;
  if (num == 0) {
    return false;
  }
  return true;
}

//Return true if player/computer with symbol (X or O) has won
bool currentPlayerWon(string b[][SIZE], string symbol) {
  //Horizontal case
  //Loop through each row
  for (int i=0; i < SIZE; i++) {
    bool rowWinDetected = true;
    //Check all positions in row and see if they are the same symbol
    for (int j = 0; j < SIZE; j++) {
      if (b[i][j] != symbol) {
        rowWinDetected = false;
      }
    }
    if (rowWinDetected) {
      return true;
    }
  }

  //Vertical case
  //Loop through each column
  for (int i=0; i < SIZE; i++) {
    bool colWinDetected = true;
    //Check all positions in column and see if they are the same symbol
    for (int j = 0; j < SIZE; j++) {
      if (b[j][i] != symbol) {
        colWinDetected = false;
      }
    }
    if (colWinDetected) {
      return true;
    }
  }

  //Diagonal case #1
  bool diagonal1WinDetected = true;
  for (int i=0; i < SIZE; i++) {
    if (b[i][i] != symbol) {
      diagonal1WinDetected = false;
    }
  }
  if (diagonal1WinDetected) {
    return true;
  }

  //Diagonal case #2
  bool diagonal2WinDetected = true;
  for (int i=0; i < SIZE; i++) {
    if (b[(SIZE-1)-i][i] != symbol) {
      diagonal2WinDetected = false;
    }
  }
  if (diagonal2WinDetected) {
    return true;
  }

  //otherwise win not diagonal2WinDetected
  return false;

}

void computerMove(int& row,int& col,string board[][SIZE]){
  bool validMove = false;

  while (!validMove) {

      //int row = rand()%SIZE;
      //int col = rand()%SIZE;

      determinePlacement(row,col,board);
      if ((board[row][col] != "X")
          && (board[row][col] != "O")) {
            board[row][col] = "O";
            validMove = true;
            updateCount(row,col,isPLayer1);
      }
  }
}
void updateCount(int& row,int& col,bool isPLayer1){
  //The reason for odd number is if you have a sum like 8 that mean theres a
  //combination of x and o's therefore you can not win there anymore
  //& with odd number you can never get a common case which might cause an error
  //for computer the incrm is 5 and for the player it is 3
  int incrm = 5;

  if(isPLayer1){
    incrm = 3;
  }

  //updates the count for rows and columns
  columns[col] += incrm;
  rows[row] += incrm;

  //checks for diagonal incrm for d1
  if(row == 1 && col == 1){
    diagonals[0] += incrm;
  }

  if(row == 1 && col == 1){
    diagonals[1] += incrm;
  }

  if((row == 0 && col==0) || (row == 2 && col == 2)){
    diagonals[0] += incrm;
  }

  //checks for diagnal incrm for d2
  if((row == 0 && col==2) || (row == 2 && col == 0)){
    diagonals[1] += incrm;
  }


  //check if columns,rows and diagnals are still playable
  //sets to false if not
  if(columns[col]%5!=0 && columns[col]%3!=0){
    cols_check[col] = false;
  }
  if(rows[row]%5!=0 && rows[row]%3!=0){
    rows_check[row] = false;
  }
  if(diagonals[0]%5!=0 && diagonals[0]%3!=0){
    di_check[0] = false;
  }
  if(diagonals[1]%5!=0 && diagonals[1]%3!=0){
    di_check[1] = false;
  }

}

//returns true if placement is made
bool determinePlacement(int& row,int& col,string board[][SIZE]){

  //check for Horizontal Wins
  //Check for vertical wins
  for(int c=0;c<3;c++){
    //if there are any cases where someone is too win place it there
    //Check for columns win and places accordingly
    if( (columns[c]/3.0 == 2) || (columns[c]/5.0 == 2)){
      col = c;
      cout << col << endl;
      for(int r=0;r<3;r++){
        if ((board[r][c] != "X") && (board[r][c] != "O")){
          row = r;
          return true;
        }

      }
    }
  }

  for(int i=0;i<3;i++){
    //if there are any cases where someone is too win place it there
    //Check for row win and places accordingly
    if( (rows[i]/3.0 == 2) || (rows[i]/5.0 == 2)){
      row = i;
      for(int j=0;j<3;j++){
        if ((board[i][j] != "X") && (board[i][j] != "O")){
          col = j;
          return true;
        }

      }
    }
  }

  //Checks diagonals wins and places accordingly for d1
  if( (diagonals[0]/3.0 == 2) || (diagonals[0]/5.0 == 2)){
    for(int d=0;d<3;d++){
      if ((board[d][d] != "X") && (board[d][d] != "O")){
        col = d;
        row = d;
        return true;
      }

    }
  }

  //Checks diagonals wins and places accordingly for d2
  for (int i=0; i < SIZE; i++) {
    if ((board[(SIZE-1)-i][i] != "X") && (board[(SIZE-1)-i][i] != "O")){
      row = (SIZE-1) - i;
      col = i;
      return true;
    }

  }


  //Chooses randomly if there are no win cases
  row = rand()%SIZE;
  col = rand()%SIZE;
  return true;
}
