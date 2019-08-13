#include <vector>


//THE TYPE REPRESENTING THE CONTENT OF A SQUARE
typedef enum piece_type
{

  EMPTY,
                            //BISHOP C starts on C, F on F
  WHITE_PAWN, WHITE_KNIGHT, WHITE_BISHOP_C, WHITE_BISHOP_F, WHITE_ROOK,
  BLACK_PAWN, BLACK_KNIGHT, BLACK_BISHOP_C, BLACK_BISHOP_F, BLACK_ROOK,

  WHITE_QUEEN, WHITE_KING,
  BLACK_QUEEN, BLACK_KING

} piece;



//TO REPRESENT THE COLOR OF THE SQUARE
typedef enum color_type
{

  NONE,
  BLACK,
  WHITE

} color;



//TO REPRESENT A SQUARE
typedef struct board_node_type
{

  unsigned char x;      // how far are we along A to H (0 to 7)
  unsigned char y;      // how far are we along 1 to 8 (0 to 7)

  struct board_node_type * next;
  struct board_node_type * prev;

  piece current_contents;           // what's in the square
  color square_color;

} board_node;









//TO REPRESENT A MOVE
typedef struct _move_type
{
    piece actor;          //who's moving?
    piece capture;         //who's died?

    unsigned char orig_x; //where are you coming from?
    unsigned char orig_y;

    unsigned char dest_x; //where are you going / capturing?
    unsigned char dest_y;

    bool make_queen;      //pawn makes it to the other side

} _move;




//REPRESENTS A SPACE IN THE PRINT FUNCTION
typedef struct space_type
{

  color c_board;
  color c_piece;
  char content;

  bool selected;  //going to use this to represent possible moves

} space;



//TO REPRESENT THE STATE OF THE GAME
typedef enum board_state_type
{

  WHITE_TURN, WHITE_TURN_IN_CHECK,
  BLACK_TURN, BLACK_TURN_IN_CHECK,

  WHITE_VICTORY,
  BLACK_VICTORY,

  STALEMATE

} board_state;




//TO REPRESENT THE BOARD - MAKE THIS A CLASS
class board
{
public:

  board();


  board_state state; // what's going on?

  board_node * A1_ptr; // "head" - i.e. where's the origin (0,0)
  board_node * H8_ptr; // "tail"

  //for checking stalemate condtion
  unsigned char turns_since_white_capture;
  unsigned char turns_since_black_capture;

  unsigned char white_score;
  unsigned char black_score;

  unsigned char white_captures;
  unsigned char black_captures;

  bool gameover;


  //
  // int num_legal_moves; // not neccesary with vector
  std::vector<_move> list_of_moves; //use push_back() to add moves

  board_node dead_white_guys[16];
  board_node dead_black_guys[16];


  void print();
  void reset_pieces();




};
