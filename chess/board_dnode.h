//***************************************************************************************
// CHESS RE IMPLEMENTATION PROJECT - LINKED LIST BOARD - 7/23/2019                     //
//                                                                                     //          
// EACH BOARD SPACE NODES IS A LINK IN A LIST - A DOUBLE LINKED NODE (FORWARD AND BACK)//
//***************************************************************************************

#include <iostream>

using namespace std;


class board_dnode{

    public:
        board_dnode(){
            piece = ' ';
            next_pointer = nullptr;
            previous_pointer = nullptr;
        }

    private:
        string piece;
        
        board_dnode *next_pointer, *previous_pointer;
};

