#include "chess.h"
#include "colors.h"
#include <iostream>
#include <algorithm>

using namespace main_savitch_14;
using namespace std;


/*  OLD CHECKERS PIECE CLASS - MOST LIKELY TO DELTE THIS LATER BECAUSE ITS USLESS
piece::piece(){

    empty = 0;
    black = 0;
    white = 0;
    king = 0;
}
 */

checkers::checkers(){

    move_counter = 0;

    for (int i = 0; i < 3; i++){

        for (int j = 0; j < 8; j++){

            if (i == 0 || i == 2){//maybe don't mod by zero?

                if(j % 2 == 0){

                    board[i][j].empty = true;
                }else{

                    //board[i][j].empty = false;
                    board[i][j].black = true;
                }

            }else{

              if(j % 2 == 0){

                  //board[i][j].empty = false;
                  board[i][j].black = true;
              }else{

                  board[i][j].empty = true;
              }
            }
        }
    }

    for (int i = 3; i < 5; i++){

        for (int j = 0; j < 8; j++){

            if(i == 3){

                if(j % 2 != 0){

                    board[i][j].empty = true;
                }
            }else{

                if(j % 2 == 0){

                    board[i][j].empty = true;
                }
            }
        }
    }

    for (int i = 5; i < 8; i++){

        for (int j = 0; j < 8; j++){

            if(i == 5 || i == 7){

                if(j % 2 == 0){

                    board[i][j].white = true;

                }else{

                    board[i][j].empty = true;
                }

            }else{

                if(j % 2 == 0){

                    board[i][j].empty = true;
                }else{

                    board[i][j].white = true;
                }
            }
        }
    }
}

void checkers::test(std::ostream &outs){

        for (int i = 3; i < 5; i++){

            for (int j = 0; j < 8; j++){

                cout << board[i][j] << endl;
            }
        }
}

void piece::output(std::ostream& outs){

    outs << "empty: " << empty << endl;
    outs << "white: " << white << endl;
    outs << "black: " << black << endl;
    outs << "King: "  << king  << endl
         << endl;
}

ostream& operator <<(ostream& outs, piece& p){

    p.output(outs);
    return outs;
}

/*
//██╗███████╗    ██╗     ███████╗ ██████╗  █████╗ ██╗         ███████╗██╗   ██╗███╗   ██╗ ██████╗████████╗██╗ ██████╗ ███╗   ██╗
//██║██╔════╝    ██║     ██╔════╝██╔════╝ ██╔══██╗██║         ██╔════╝██║   ██║████╗  ██║██╔════╝╚══██╔══╝██║██╔═══██╗████╗  ██║
//██║███████╗    ██║     █████╗  ██║  ███╗███████║██║         █████╗  ██║   ██║██╔██╗ ██║██║        ██║   ██║██║   ██║██╔██╗ ██║
//██║╚════██║    ██║     ██╔══╝  ██║   ██║██╔══██║██║         ██╔══╝  ██║   ██║██║╚██╗██║██║        ██║   ██║██║   ██║██║╚██╗██║
//██║███████║    ███████╗███████╗╚██████╔╝██║  ██║███████╗    ██║     ╚██████╔╝██║ ╚████║╚██████╗   ██║   ██║╚██████╔╝██║ ╚████║
//╚═╝╚══════╝    ╚══════╝╚══════╝ ╚
*/

bool checkers::is_legal(const std::string& move){//use mod % move number to find if
       
                                                //computer or human is moving
  int temp_i1, temp_j1, temp_i2, temp_j2 = 0;

  

  bool is_king = 0;

  //input is a letter between a and h, which maps to a number between 65 and 72
  //subtracting 65(A), will give us a range of numbers which map to 0 - 7

  cout << endl << "move: " << move << endl;

  temp_i1 = move[0] - 'A';
  temp_j1 = move[1] - 48;
  temp_i2 = move[2] - 'A';
  temp_j2 = move[3] - 48;

    bool computers_turn = 0;

    if(move_counter % 2 == 0){

        computers_turn = 0;
    
    }else { computers_turn = true; }

  //if(move.length() is greater than 4 ... look for more moves after the first)

    if(computers_turn == true && board[temp_i1][temp_j1].white == false) return 0;

    if(!computers_turn && board[temp_i1][temp_j1].black == false) return 0;
    
  if(board[temp_i1][temp_j1].empty == true) return 0;// empty

  //cout << endl << "HEllo1!" << endl;

  if(board[temp_i2][temp_j2].empty == true) return 0;// space

  //cout << endl << "HEllo2!" << endl;

  if(!board[temp_i1][temp_j1].white && !board[temp_i1][temp_j1].black) return 0;//trying to move space with no piece

  //cout << endl << "HEllo3!" << endl;

  if(temp_j1 > 7 || temp_j1 < 0 || temp_j2 > 7 || temp_j2 < 0) return 0; //out of bounds

  //cout << endl << "HEllo4!" << endl;

    //if space trying to move to is occupied
    if(board[temp_i2][temp_j2].white == true || board[temp_i2][temp_j2].black == true){ return 0; }

    //cout << endl << "hello5!" << endl;
            
  if(move_counter == 0){ //if first move in the game then follow these special rules

    if(board[temp_i1][temp_j1].white == true && temp_i1 - temp_i2 != 1) return 0; //first stage

    //cout << endl << "HEllo5!" << endl;

    if(board[temp_i1][temp_j1].black == true && temp_i2 - temp_i1 != 1) return 0; //legal move check
    //cout << endl << "hello6" <<endl;
  
  }


//return 1;


  //if(temp_i1 == 2 || temp_i1 == 5) return 1;
  //cout << endl << "HEllo!" << endl;

    int cases = 0;


// |x|w|x|w|x|w|x|w| A
// |w|x|w|x|w|x|w|x| B
// |x|w|x|w|x|w|x|w| C
// | | | | | | | | | D
// | | | | | | | | | E
// |b|x|b|x|b|x|b|x| F
// |x|b|x|b|x|b|x|b| G
// |b|x|b|x|b|x|b|x| H
//  0 1 2 3 4 5 6 7
// [ ]           [ ] these outer cells could potentially move off the board (case 1)
//   [ ]       [ ]   these cells will move off the board if the move is a jump (case 2)
//     [      ]      these cells will not move off the board (case 3)

//this is applied horizontally and vertically


// |x|1|x|1|x|1|x|1| A
// |1|x|2|x|2|x|2|x| B
// |x|2|x|3|x|3|x|1| C
// |1|x|3|x|3|x|2|x| D
// |x|2|x|3|x|3|x|1| E
// |1|x|3|x|3|x|2|x| F
// |x|2|x|2|x|2|x|1| G
// |1|x|1|x|1|x|1|x| H
//  0 1 2 3 4 5 6 7

  //assume normal (case 3)
  if(temp_i1 == 3 && temp_j1 == 2 || temp_i1 == 5 && temp_j1 == 2 || temp_i1 == 2 && temp_j1 == 3 || //if() countinued on next line
     temp_i1 == 3 && temp_j1 == 2 || temp_i1 == 3 && temp_j1 == 4 || temp_i1 == 4 && temp_j1 == 3 ||
    temp_i1 == 5 && temp_j1 == 4 || temp_i1 == 2 && temp_j1 == 5 || temp_i1 == 4 && temp_j1 == 5) {

      //   cout << "case 3"<<endl<<endl;
    cases = 3; 
  }

  bool white_mover; // this will hold which colors piece is being moved

  if(board[temp_i1][temp_j1].white == true){ //checks to see which color piece is being moved
  
    white_mover = 1;

    }else{

        white_mover = 0; //if a white piece is NOT being moved, then mover must be black
    }

  //check if it's outside the range 2-5, if so, set to case 2=
  if(cases != 3 && temp_j1 - temp_i1 == temp_j1) cases = 1;
  if(cases != 3 && temp_i1 - temp_j1 == temp_i1) cases = 1;
  if(cases != 3 && temp_j1 == 7) cases = 1;
  if(cases != 3 && temp_i1 == 7) cases = 1;

  //if(cases != 3 && cases != 2)
  
  //check if either index is 0 or 7, if so, set to case 1
  if(cases != 3 && cases != 1) cases = 2;

  if(board[temp_i1][temp_j1].king == true){

      is_king = true;
  
  }else{ is_king = false; }
    
  //case decided, now handle it
  switch(cases){

    case 1:
        cout << "hello from case one!"<<endl<<endl;

        if(white_mover != 1){//stuff for black mover

            
        if(is_king){
            
            if(temp_i1 - temp_i2 == 1 || temp_i1 - temp_i2 == -1){//if not jumping

                if(!board[temp_i2][temp_j2].black && !board[temp_i2][temp_j2].white){

                    return 1;
                }        
            
            }else{

                //stuff for king jump
                
                if(temp_i1 - temp_i2 < 0){//if youre jumping down

                    if(temp_j1 - temp_j2 < 0){//jumping to the right and down

                        if(board[temp_i1+1][temp_j1+1].white){

                            return true;

                        }else{ return false; }
                    
                    }else{//jumping to the left and down
                        
                        if(board[temp_i1+1][temp_j1-1].white){

                            return true;

                        }else{ return false; }
                    }

                }else{

                    //if you're jumping up
                    if(temp_j1 - temp_j2 < 0){//jumping to the right and UP

                        if(board[temp_i1-1][temp_j1+1].white){

                            return true;

                        }else{ return false; }
                    
                    }else{//jumping to the left and UP
                        
                        if(board[temp_i1-1][temp_j1-1].white){

                            return true;

                        }else{ return false; }
                    }
                }
            }

        }

        //cases to check if you're not jumping
        if(temp_i1 - temp_i2 == -1){//if you're only moving one space forward
                
                if(board[temp_i2][temp_j2].white != true && board[temp_i2][temp_j2].black != true){//if there's an open space

                    return 1;
                }
            }
    

            if(temp_j1 < 6){//checking to see if moving a black piece before j1 = 6 is possible

                if(temp_j1 == temp_j2 - 2){ //CASES WHERE JUMPING RIGHT //MAKE SURE THIS WORKS LATER!!!

                    if(board[temp_i1+1][temp_j1+1].white == true){//check if white piece is between the two board spots

                        if(board[temp_i2][temp_j2].white == 0 && board[temp_i2][temp_j2].black == 0){

                            return 1;
                        
                        }else{ return 0; }//if the adjacent horizontal space is not empty, return false
                
                    }else{ return 0; }//if the space which is before the space being jumped to dose not have a white piece on it, return false
                        

                }else{//checking cases where JUMPING LEFT

                    if(board[temp_i1+1][temp_j1-1].white == true){//check if white piece is between the two board spots

                        if(board[temp_i2][temp_j2].white == 0 && board[temp_i2][temp_j2].black == 0){

                            return 1;

                        }else{ return 0; }

                    }else{ return 0; }

                }   
            }
                
        if(temp_j1 > 5){//most likely position j = 0 or 1 would be handled by the above if else code 

            if(board[temp_i1+1][temp_j1-1].white == true){

                if(board[temp_i2][temp_j2].white == false && board[temp_i2][temp_j2].black == false){

                    return 1;

                }else{ return 0; }
                        
            }else{ return 0; }
           
        }


    }else{//stuff for white mover

            if(is_king){
            
            if(temp_i1 - temp_i2 == 1 || temp_i1 - temp_i2 == -1){//if not jumping

                if(!board[temp_i2][temp_j2].black && !board[temp_i2][temp_j2].white){

                    return 1;
                }        
            
            }else{

                //stuff for king jump
                
                if(temp_i1 - temp_i2 < 0){//if youre jumping down

                    if(temp_j1 - temp_j2 < 0){//jumping to the right and down

                        if(board[temp_i1+1][temp_j1+1].black){

                            return true;

                        }else{ return false; }
                    
                    }else{//jumping to the left and down
                        
                        if(board[temp_i1+1][temp_j1-1].black){

                            return true;

                        }else{ return false; }
                    }

                }else{

                    //if you're jumping up
                    if(temp_j1 - temp_j2 < 0){//jumping to the right and UP

                        if(board[temp_i1-1][temp_j1+1].black){

                            return true;

                        }else{ return false; }
                    
                    }else{//jumping to the left and UP
                        
                        if(board[temp_i1-1][temp_j1-1].black){

                            return true;

                        }else{ return false; }
                    }
                }
            }

        }

        if(temp_i1 - temp_i2 == 1){//if you're only moving one space forward
                
                if(board[temp_i2][temp_j2].white != true && board[temp_i2][temp_j2].black != true){//if there's an open space

                    return 1;
                }
            }

            if(temp_j1 < 6){//checking to see if moving a white piece before j1 = 6 is possible

                if(temp_j1 == temp_j2 - 2){ //see if it's jumping a piece to the right //MAKE SURE THIS WORKS LATER!!!

                    if(board[temp_i1-1][temp_j1+1].black == true){//check if black piece is between the two board spots

                        if(board[temp_i2][temp_j2].white == 0 && board[temp_i2][temp_j2].black == 0){

                            return 1;
                        
                        }else{ return 0; }//if the adjacent horizontal space is not empty, return false
                
                    }else{ return 0; }//if the space which is before the space being jumped to dose not have a white piece on it, return false

                }else{ //jumping left

                    if(board[temp_i1-1][temp_j1-1].black == true){//check if white piece is between the two board spots

                        if(board[temp_i2][temp_j2].white == 0 && board[temp_i2][temp_j2].black == 0){

                            return 1;

                        }else{ return 0; }

                    }else{ return 0; }
                }

            }
                
        if(temp_j1 > 5){//most likely position j = 0 or 1 would be handled by the above if else code 

            if(board[temp_i1-1][temp_j1-1].black == true){//checking to see if a black piece is in space between jump

                if(board[temp_i2][temp_j2].white == false && board[temp_i2][temp_j2].black == false){//check if space is empty

                    return 1;

                }else{ return 0; }
                        
            }else{ return 0; }
           
        }
        
    }
      break;
////////////////////////////////////////////////////////////////////////////CASE TWO///////////////////////////////////////////////

    case 2:
        cout << "hello from case two!"<<endl<<endl;

        if(!white_mover){// case two black mover

            if(is_king){
            
            if(temp_i1 - temp_i2 == 1 || temp_i1 - temp_i2 == -1){//if not jumping

                if(!board[temp_i2][temp_j2].black && !board[temp_i2][temp_j2].white){

                    return 1;
                }        
            
            }else{

                //stuff for king jump
                
                if(temp_i1 - temp_i2 < 0){//if youre jumping down

                    if(temp_j1 - temp_j2 < 0){//jumping to the right and down

                        if(board[temp_i1+1][temp_j1+1].white){

                            return true;

                        }else{ return false; }
                    
                    }else{//jumping to the left and down
                        
                        if(board[temp_i1+1][temp_j1-1].white){

                            return true;

                        }else{ return false; }
                    }

                }else{

                    //if you're jumping up
                    if(temp_j1 - temp_j2 < 0){//jumping to the right and UP

                        if(board[temp_i1-1][temp_j1+1].white){

                            return true;

                        }else{ return false; }
                    
                    }else{//jumping to the left and UP
                        
                        if(board[temp_i1-1][temp_j1-1].white){

                            return true;

                        }else{ return false; }
                    }
                }
            }

        }

        if(temp_i1 - temp_i2 >= 0){ return 0;}


        //cases to check if you're not jumping
        if(temp_i1 - temp_i2 == -1){//if you're only moving one space forward
                
                if(board[temp_i2][temp_j2].white != true && board[temp_i2][temp_j2].black != true){//if there's an open space

                    return 1;
                }
            }

        //checks to see if your jumping to right
        if(temp_j1 - temp_j2 == -2){

            if(board[temp_i1+1][temp_j1+1].white == true){//checks to see if there's a white piece
                
                if(board[temp_i2][temp_j2].black == false && board[temp_i2][temp_j2].white == false){ 
                    
                    return 1; 

                }else { return 0; }

            }else{ return 0; }
        
        }else{//jumping to the left

            if(board[temp_i1+1][temp_j1-1].white == true){
                
                if(board[temp_i2][temp_j2].black == false && board[temp_i2][temp_j2].white == false){ 
                    
                    return 1;

                }else{ return 0; }

            }else{ return 0; }
        }
        
        
        }else{        //stuff for white mover

            if(is_king){
            
            if(temp_i1 - temp_i2 == 1 || temp_i1 - temp_i2 == -1){//if not jumping

                if(!board[temp_i2][temp_j2].black && !board[temp_i2][temp_j2].white){

                    return 1;
                }        
            
            }else{

                //stuff for king jump
                
                if(temp_i1 - temp_i2 < 0){//if youre jumping down

                    if(temp_j1 - temp_j2 < 0){//jumping to the right and down

                        if(board[temp_i1+1][temp_j1+1].black){

                            return true;

                        }else{ return false; }
                    
                    }else{//jumping to the left and down
                        
                        if(board[temp_i1+1][temp_j1-1].black){

                            return true;

                        }else{ return false; }
                    }

                }else{

                    //if you're jumping up
                    if(temp_j1 - temp_j2 < 0){//jumping to the right and UP

                        if(board[temp_i1-1][temp_j1+1].black){

                            return true;

                        }else{ return false; }
                    
                    }else{//jumping to the left and UP
                        
                        if(board[temp_i1-1][temp_j1-1].black){

                            return true;

                        }else{ return false; }
                    }
                }
            }

        }//END OF IS KING

            //if you're trying to move backwards and !king
            if(temp_i1 - temp_i2 <= 0){ return 0;}

            if(temp_i1 - temp_i2 == 1){//if you're only moving one space forward
                
                if(board[temp_i2][temp_j2].white != true && board[temp_i2][temp_j2].black != true){//if there's an open space

                    return 1;
                }
            }
        



        //checks to see if your jumping to right
        if(temp_j1 - temp_j2 == -2){

            if(board[temp_i1-1][temp_j1+1].black == true){//checks to see if there's a white piece
                
                if(board[temp_i2][temp_j2].black == false && board[temp_i2][temp_j2].white == false){ 
                    
                    return 1; 

                }else { return 0; }

            }else{ return 0; }
        
        }else{//jumping to the left

            if(board[temp_i1-1][temp_j1-1].black == true){
                
                if(board[temp_i2][temp_j2].black == false && board[temp_i2][temp_j2].white == false){ 
                    
                    return 1;

                }else{ return 0; }

            }else{ return 0; }
        }

    }
        
      break;

//////////////////////////////////////////////////////////////////////////CASE THREE/////////////////////////////////////////////////
    
    case 3:
        cout << "hello from case three!" << endl<<endl;
        
        if(!white_mover){//stuff for black mover

                    if(is_king){
            
            if(temp_i1 - temp_i2 == 1 || temp_i1 - temp_i2 == -1){//if not jumping

                if(!board[temp_i2][temp_j2].black && !board[temp_i2][temp_j2].white){

                    return 1;
                }        
            
            }else{

                //stuff for king jump
                
                if(temp_i1 - temp_i2 < 0){//if youre jumping down

                    if(temp_j1 - temp_j2 < 0){//jumping to the right and down

                        if(board[temp_i1+1][temp_j1+1].white){

                            return true;

                        }else{ return false; }
                    
                    }else{//jumping to the left and down
                        
                        if(board[temp_i1+1][temp_j1-1].white){

                            return true;

                        }else{ return false; }
                    }

                }else{

                    //if you're jumping up
                    if(temp_j1 - temp_j2 < 0){//jumping to the right and UP

                        if(board[temp_i1-1][temp_j1+1].white){

                            return true;

                        }else{ return false; }
                    
                    }else{//jumping to the left and UP
                        
                        if(board[temp_i1-1][temp_j1-1].white){

                            return true;

                        }else{ return false; }
                    }
                }
            }

        }

        
            if(temp_i1 - temp_i2 == -1){//if you're only moving one space forward
                
                if(board[temp_i2][temp_j2].white != true && board[temp_i2][temp_j2].black != true){//if there's an open space

                    return 1;
                }
            }

            //if you're trying to move backwards and !king
            if(temp_i1 - temp_i2 >= 0){ return 0;}
            
            //if you're making a jump to the right
            if((temp_j1 + 2) == temp_j2){

                if(board[temp_i1+1][temp_j1+1].white == true){

                    if(board[temp_i2][temp_j2].white == false && board[temp_i2][temp_j2].black == false){

                        return 1;
                    }

                }else{ return 0; } //make sure the space between jump has a white
            }

            //if making jump to the left
            if((temp_j1-2) == temp_j2){

                if(board[temp_i1+1][temp_j1-1].white == true){
                    
                    if(board[temp_i2][temp_j2].white == false && board[temp_i2][temp_j2].black == false){

                        return 1;
                    }
                
                }else{ return 0; } //make sure the space between jump as a white
            }

        }else{//stuff for white mover
            
            if(is_king){
            
            if(temp_i1 - temp_i2 == 1 || temp_i1 - temp_i2 == -1){//if not jumping

                if(!board[temp_i2][temp_j2].black && !board[temp_i2][temp_j2].white){

                    return 1;
                }        
            
            }else{

                //stuff for king jump
                
                if(temp_i1 - temp_i2 < 0){//if youre jumping down

                    if(temp_j1 - temp_j2 < 0){//jumping to the right and down

                        if(board[temp_i1+1][temp_j1+1].black){

                            return true;

                        }else{ return false; }
                    
                    }else{//jumping to the left and down
                        
                        if(board[temp_i1+1][temp_j1-1].black){

                            return true;

                        }else{ return false; }
                    }

                }else{

                    //if you're jumping up
                    if(temp_j1 - temp_j2 < 0){//jumping to the right and UP

                        if(board[temp_i1-1][temp_j1+1].black){

                            return true;

                        }else{ return false; }
                    
                    }else{//jumping to the left and UP
                        
                        if(board[temp_i1-1][temp_j1-1].black){

                            return true;

                        }else{ return false; }
                    }
                }
            }

        }


            if(temp_i2 - temp_i1 == -1){//if youre only moving one space forward


                if(board[temp_i2][temp_j2].white != true && board[temp_i2][temp_j2].black != true){//if there's an open space

                    return 1;
                }
            }

            if(temp_i1 - temp_i2 <= 0){ return 0; }
        
            if((temp_j1 + 2) == temp_j2){

                if(board[temp_i1-1][temp_j1+1].black == true){

                    if(board[temp_i2][temp_j2].white == false && board[temp_i2][temp_j2].black == false){

                        return 1;
                    }

                }else{ return 0; }
            }

            if((temp_j1 - 2) == temp_j2){

                if(board[temp_i1-1][temp_j1-1].black == true){ 

                    if(board[temp_i2][temp_j2].white == false && board[temp_i2][temp_j2].black == false){

                        return 1;
                    }

                }else{ return 0; }
            }
        }//end of stuff for white mover

      break;

    default:
      break;
      
}
}


//function which moves a piece
void checkers::make_move(const std::string& move){

//  cout << endl << "Moves: " << move_counter << endl << endl << endl;

    bool computers_turn = 0;

    bool is_king = 0;

    if(move_counter % 2 == 0){

        computers_turn = 0;
    
    }else { computers_turn = true; }

  int temp_i1, temp_j1, temp_i2, temp_j2;

  bool is_jump = 0;

 // input is a letter between a and h, which maps to a number between 65 and 72
 // subtracting 65(A), will give us a range of numbers which map to 0 - 7

  temp_i1 = move[0] - 'A';
  temp_j1 = move[1] - 48;
  temp_i2 = move[2] - 'A';
  temp_j2 = move[3] - 48;

  
    if(computers_turn == true && temp_i2 == 0){

        board[temp_i2][temp_j2].king = true;
    }

    if(!computers_turn && temp_i2 == 7){

        board[temp_i2][temp_j2].king = true;
    }

  if(board[temp_i1][temp_j1].white == true){

      if(temp_i1 - temp_i2 == 2){
          
          is_jump = 1;
      }
  }

    if(board[temp_i1][temp_j1].black == true){

      if(temp_i2 - temp_i1 == 2){
          
          is_jump = 1;
      }
  }

    if(board[temp_i1][temp_j1].king == true){

        if(temp_i1 - temp_i2 == -1){

            if(computers_turn){

                board[temp_i1][temp_j1].white = false;
                board[temp_i1][temp_j1].king = false;

                board[temp_i2][temp_j2].white = true;
                board[temp_i2][temp_j2].king = true;
                move_counter++;                
                return;

            }else{

                board[temp_i1][temp_j1].black = false;
                board[temp_i1][temp_j1].king = false;

                board[temp_i2][temp_j2].black = true;
                board[temp_i2][temp_j2].king = true;
                
                move_counter++;
                
                return;

            }
        }

        if(temp_i1 - temp_i2 == 1){

            if(computers_turn){

                board[temp_i1][temp_j1].white = false;
                board[temp_i1][temp_j1].king = false;

                board[temp_i2][temp_j2].white = true;
                board[temp_i2][temp_j2].king = true;
                
                move_counter++;

                return;
            }
        }

        if(computers_turn){//stuff for white king move


            if(temp_i1 - temp_i2 == -2){//if jumping down


                if(temp_j1 - temp_j2 < 0){//if moving king right

                    if(board[temp_i1+1][temp_j1+1].king == true){ board[temp_i1+1][temp_j1+1].king = false; }
                    board[temp_i1+1][temp_j1+1].black = false;

                    board[temp_i1][temp_j1].white = false;
                    board[temp_i1][temp_j1].black = false;


                    board[temp_i2][temp_j2].white = true;
                    board[temp_i2][temp_j2].king = true;

                move_counter++;

                    return;
    
                }else{//if moving king left

                    if(board[temp_i1+1][temp_j1-1].king == true){ board[temp_i1+1][temp_j1-1].king = false; }
                    board[temp_i1+1][temp_j1-1].black = false;

                    board[temp_i1][temp_j1].white = false;
                    board[temp_i1][temp_j1].black = false;


                    board[temp_i2][temp_j2].white = true;
                    board[temp_i2][temp_j2].king = true;

                move_counter++;

                    return;
                }

            }else{

                if(temp_j1 - temp_j2 < 0){//moving king right
                
                    if(board[temp_i1-1][temp_j1+1].king == true){ board[temp_i1+1][temp_j1+1].king = false; }
                    board[temp_i1-1][temp_j1+1].black = false;

                    board[temp_i1][temp_j1].white = false;
                    board[temp_i1][temp_j1].black = false;


                    board[temp_i2][temp_j2].white = true;
                    board[temp_i2][temp_j2].king = true;

                move_counter++;

                    return;
                    
                }else{//moving king left

                    if(board[temp_i1-1][temp_j1-1].king == true){ board[temp_i1-1][temp_j1-1].king = false; }
                    board[temp_i1-1][temp_j1-1].black = false;

                    board[temp_i1][temp_j1].white = false;
                    board[temp_i1][temp_j1].black = false;

                    
                    board[temp_i2][temp_j2].white = true;
                    board[temp_i2][temp_j2].king = true;

                move_counter++;

                    return;

                }
            }
        
        }else{//stuff for black king move

            if(temp_i1 - temp_i2 == -2){//if jumping down


                if(temp_j1 - temp_j2 < 0){//if moving king right

                    if(board[temp_i1+1][temp_j1+1].king == true){ board[temp_i1+1][temp_j1+1].king = false; }
                    board[temp_i1+1][temp_j1+1].white = false;

                    board[temp_i1][temp_j1].king = false;
                    board[temp_i1][temp_j1].black = false;

                    
                    board[temp_i2][temp_j2].black = true;
                    board[temp_i2][temp_j2].king = true;

                move_counter++;

                    return;
    
                }else{//if moving king left

                    if(board[temp_i1+1][temp_j1-1].king == true){ board[temp_i1+1][temp_j1-1].king = false; }
                    board[temp_i1+1][temp_j1-1].white = false;


                    board[temp_i1][temp_j1].king = false;
                    board[temp_i1][temp_j1].black = false;

                    
                    board[temp_i2][temp_j2].black = true;
                    board[temp_i2][temp_j2].king = true;

                move_counter++;

                    return;
                }

            }else{

                if(temp_j1 - temp_j2 < 0){//moving king right
                
                    if(board[temp_i1-1][temp_j1+1].king == true){ board[temp_i1+1][temp_j1+1].king = false; }
                    board[temp_i1-1][temp_j1+1].white = false;

                    board[temp_i1][temp_j1].king = false;
                    board[temp_i1][temp_j1].black = false;
                    
                    
                    board[temp_i2][temp_j2].black = true;
                    board[temp_i2][temp_j2].king = true;
                move_counter++;
                    return;
                    
                }else{//moving king left

                    if(board[temp_i1-1][temp_j1-1].king == true){ board[temp_i1-1][temp_j1-1].king = false; }
                    board[temp_i1-1][temp_j1-1].white = false;
                    
                    board[temp_i1][temp_j1].king = false;
                    board[temp_i1][temp_j1].black = false;

                    board[temp_i2][temp_j2].black = true;
                    board[temp_i2][temp_j2].king = true;

                move_counter++;

                    return;

                }
            }

            
        }


  }//end of king moving

    if(board[temp_i1][temp_j1].white == true && is_jump == true){

        if(temp_j1 - temp_j2 == -2){

            if(board[temp_i1-1][temp_j1+1].black == true){


                board[temp_i1][temp_j1].white = false;
                board[temp_i1][temp_j1].king = false;

                board[temp_i1-1][temp_j1+1].black = false;
                board[temp_i1-1][temp_j1+1].king = false;
                board[temp_i2][temp_j2].white = true;
                
                move_counter++;

                return;
            }

        }else{

            if(board[temp_i1-1][temp_j1-1].black == true){

                board[temp_i1][temp_j1].white = false;
                board[temp_i1][temp_j1].king = false;

                board[temp_i1-1][temp_j1-1].black = false;
                board[temp_i1-1][temp_j1-1].king = false;

                board[temp_i2][temp_j2].white = true;

                move_counter++;
                return;
            }
        }
    }


    if(board[temp_i1][temp_j1].black == true && is_jump == true){

        if(temp_j1 - temp_j2 == -2){

            if(board[temp_i1+1][temp_j1+1].white == true){

                board[temp_i1][temp_j1].black = false;
                board[temp_i1][temp_j1].king = false;

                board[temp_i1+1][temp_j1+1].white = false;
                board[temp_i1+1][temp_j1+1].king = false;
                
                board[temp_i2][temp_j2].black = true;

                move_counter++;

                return;
            }

        }else{

            if(board[temp_i1+1][temp_j1-1].white == true){

                board[temp_i1][temp_j1].black = false;
                board[temp_i1][temp_j1].king = false;

                board[temp_i1+1][temp_j1-1].white = false;
                board[temp_i1+1][temp_j1-1].king = false;
                
                board[temp_i2][temp_j2].black = true;

                move_counter++;

                return; 
            }
        }
    }




  if(board[temp_i1][temp_j1].white == true){

    //cout << "Hello from make_move!"<<endl;
    board[temp_i2][temp_j2].white = true;
    //return;// <-------notice return statement
  }

  if(board[temp_i1][temp_j1].black == true){

    board[temp_i2][temp_j2].black = true;
  }


  board[temp_i1][temp_j1].black = false;
  board[temp_i1][temp_j1].white = false;

    move_counter++;
    cout << endl << "Moves: " << move_counter << endl   ;

}

void checkers::display_status(){

    bool computers_turn = 0;

    if(move_counter % 2 == 0){

        computers_turn = 0;
    
    }else { computers_turn = true; }

  //if(move.length() is greater than 4 ... look for more moves after the first)

    if(computers_turn == true){ cout << "* * *  White turn  * * *"; }
    if(!computers_turn){ cout << "* * *  Black turn  * * *"; }

  char n = 'A';

    for (int i = 0; i < 8; i++) {
      cout << endl;
      cout << RESET;

      for (int j = 0; j < 8; j++) {

        if (board[i][j].empty == true) {

          cout << B_RED << "   ";
          //cout << B_RED << "  ";
        } else {

          if (board[i][j].black == true) {

              if(board[i][j].king){

                cout << B_YELLOW << " " << BLACK << "K" << B_YELLOW << " ";      
              
              }else{
                
                cout << B_YELLOW << " " << BLACK << "@" << B_YELLOW << " ";
              }
            //cout << B_YELLOW << " " << BLACK << "@" << B_YELLOW << " ";
          } else {

          	if(board[i][j].white == true){

                  if(board[i][j].king == true){

                      cout << B_YELLOW << " " << WHITE << "K" << B_YELLOW << " ";

                  }else{ 
                    
                      cout << B_YELLOW << " " << WHITE << "@" << B_YELLOW << " "; 
                    
                    }
              
              //cout << B_YELLOW << " " << WHITE << "@" << B_YELLOW << " ";
  	        
              }else{
              
              cout << B_YELLOW << "   ";
	          }
          }

        }

      }

      cout << B_BLUE << " " << BLACK << n << " " << RESET;
      n++;
      cout << RESET;
    }
    cout << endl << B_BLUE << BLACK <<" 0  1  2  3  4  5  6  7  =)" << RESET;
    cout << endl << "ONLY USE CAPS  -  BLACK MOVES FIRST";
    cout<< endl;
}

