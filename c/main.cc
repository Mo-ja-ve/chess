#include <iostream>


typedef enum piece_type
{
  EMPTY,
              //KNIGHT B starts on B, G on G  //BISHOP C starts on C, F on F
  WHITE_PAWN, WHITE_KNIGHT_B, WHITE_KNIGHT_G, WHITE_BISHOP_C, WHITE_BISHOP_F,
  BLACK_PAWN, BLACK_KNIGHT_B, BLACK_KNIGHT_G, BLACK_BISHOP_C, BLACK_BISHOP_F,

  WHITE_ROOK, WHITE_QUEEN, WHITE_KING,
  BLACK_ROOK, BLACK_QUEEN, BLACK_KING

} piece;



typedef struct board_node_type
{

  unsigned char x;      // how far are we along A to H (0 to 7)
  unsigned char y;      // how far are we along 1 to 8 (0 to 7)

  struct board_node_type * up;      // +y
  struct board_node_type * down;    // -y

  struct board_node_type * right;   // +x
  struct board_node_type * left;    // -x

  piece current_contents;           // what's in the square

} board_node;

//can now declare a board_node



//INITIALIZATION

// DIMENSION
void set_dimension(board_node &node, unsigned char x_in, unsigned char y_in)
{
  node.x = x_in;
  node.y = y_in;
}



// POINTERS
void set_up_ptr(board_node &node, board_node * up_in)
{
  node.up = up_in;
}

void set_down_ptr(board_node &node, board_node * down_in)
{
  node.down = down_in;
}

void set_right_ptr(board_node &node, board_node * right_in)
{
  node.right = right_in;
}

void set_left_ptr(board_node &node, board_node * left_in)
{
  node.left = left_in;
}



//THE BOARD

typedef enum board_state_type
{

  WHITE_TURN,
  BLACK_TURN,

  WHITE_VICTORY,
  BLACK_VICTORY,

  STALEMATE

} board_state;


typedef struct board_type
{

  board_state state; // what's going on?

  board_node * A1_ptr; // where's (0,0)

} board;


void reset_pieces(board &b)
{
  //put all the pieces in their initial locations
}









int main(int argc, char const *argv[]) {

  // board_node current_space;

  // current_space.x = 5;
  // current_space.y = 3;

  board b;

  board_node * A1_ptr = new board_node();

  b.A1_ptr = A1_ptr;

  // std::cout << "the current space is ";
  // std::cout << A1_ptr->x << " ";
  // std::cout << A1_ptr->y << std::endl;

  set_dimension(*A1_ptr, 0, 0);   //A1 is (x, y) = (0, 0)

  board_node * current_space;
  current_space = A1_ptr;



  for(unsigned char x = 0; x < 8; x++ )
  {
    for(unsigned char y = 0; y < 8; y++ )
    {

    }
  }



  return 0;
}
