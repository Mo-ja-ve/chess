//***************************************************************************************
// CHESS RE IMPLEMENTATION PROJECT - LINKED LIST BOARD - 7/23/2019                     //
//                                                                                     //          
// EACH BOARD SPACE NODES IS A LINK IN A LIST - A DOUBLE LINKED NODE (FORWARD AND BACK)//
//***************************************************************************************

#include <iostream>

using namespace main_savitch_14;
using namespace std;

//  DOUBLE LINKED NODE -- THIS CLASS ALSO DOES FUNCTION OF INITIALIZING EMPTY NODE
class board_node{

    public:
        board_node(){
            piece = ' ';
            coordinate = "TEST";
            next_pointer = nullptr;
            previous_pointer = nullptr;
        }

        string node_get_coordinate() { return coordinate; }

    private:
        string piece, coordinate;
        board_node *next_pointer, *previous_pointer;
};