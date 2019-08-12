//***************************************************************************************
// CHESS RE IMPLEMENTATION PROJECT - LINKED LIST BOARD - 7/23/2019                     //
//                                                                                     //          
// EACH BOARD SPACE NODES IS A LINK IN A LIST - A DOUBLE LINKED NODE (FORWARD AND BACK)//
//***************************************************************************************
#ifndef BOARD_NODE_H
#define BOARD_NODE_H

#include <iostream>

using namespace std;

//  DOUBLE LINKED NODE -- THIS CLASS ALSO DOES FUNCTION OF INITIALIZING EMPTY NODE
class board_node{

    public:
        board_node(){
            next_link = nullptr;
            previous_link = nullptr;
        }

        char get_coordinate() { return x_coordinate, y_coordinate; }
        board_node *previous() { return previous_link; }
        board_node *next(){ return next_link; }
        void set_next(board_node *nxt) { next_link = nxt; }
        void set_coordinate(char x, char y) { x_coordinate = x; y_coordinate = y;}

    //    static char get_xcoordinate(){ return x_coordinate; }
    //    static char get_ycoordinate(){ return y_coordinate; }

        void print() { cout << "x: " << x_coordinate << " y: " << y_coordinate; }
        // friend std::ostream &operator<<(std::ostream &outs, board_node &node);
   
    private:
        enum piece { empty, w_pawn, w_bishop, w_knight, w_rook, w_queen, w_king,
                     b_pawn, b_bishop, b_knight, b_rook, q_queen, b_king };
        bool white;
        char x_coordinate, y_coordinate;
        board_node *previous_link, *next_link;
};

// std::ostream &operator<<(std::ostream &outs, board_node &node){

//     outs<<std::endl<<"Coordinate: "<<node.x_coordinate<<" "<<node.y_coordinate;
//     return outs;
// }
#endif