//***************************************************************************************
// CHESS RE IMPLEMENTATION PROJECT - LINKED LIST BOARD - 7/23/2019                     //
//                                                                                     //          
// EACH BOARD SPACE NODES IS A LINK IN A LIST - A DOUBLE LINKED NODE (FORWARD AND BACK)//
//***************************************************************************************

#include <iostream>

using namespace std;

//  DOUBLE LINKED NODE -- THIS CLASS ALSO DOES FUNCTION OF INITIALIZING EMPTY NODE
class board_node{

    public:
        board_node(){
            next_pointer = nullptr;
            previous_pointer = nullptr;
        }

        char node_get_coordinate() { return x_coordinate, y_coordinate; }

    private:
        enum piece { empty, w_pawn, w_bishop, w_knight, w_rook, w_queen, w_king,
                     b_pawn, b_bishop, b_knifht, b_rook, q_queen, b_king };
        bool white;
        unsigned char x_coordinate, y_coordinate;

        board_node *next_pointer, *previous_pointer;
};