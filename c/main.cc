#include <iostream>
#include "colors.h"


typedef enum piece_type
{

  EMPTY,
                            //BISHOP C starts on C, F on F
  WHITE_PAWN, WHITE_KNIGHT, WHITE_BISHOP_C, WHITE_BISHOP_F, WHITE_ROOK,
  BLACK_PAWN, BLACK_KNIGHT, BLACK_BISHOP_C, BLACK_BISHOP_F, BLACK_ROOK,

  WHITE_QUEEN, WHITE_KING,
  BLACK_QUEEN, BLACK_KING

} piece;


typedef enum color_type
{

  NONE,
  BLACK,
  WHITE

} color;



typedef struct board_node_type
{

  unsigned char x;      // how far are we along A to H (0 to 7)
  unsigned char y;      // how far are we along 1 to 8 (0 to 7)

  struct board_node_type * next;
  struct board_node_type * prev;

  piece current_contents;           // what's in the square
  color square_color;

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
void set_next_ptr(board_node &node, board_node * next_in)
{
  node.next = next_in;
}

void set_color(board_node &node, color color_in)
{
  node.square_color = color_in;
}

void set_contents(board_node &node, piece current_contents_in)
{
  node.current_contents = current_contents_in;
}




//THE BOARD

typedef struct action_type
{
    piece actor;          //who's moving?
    piece capture;         //who's died?

    unsigned char orig_x; //where are you coming from?
    unsigned char orig_y;

    unsigned char dest_x; //where are you going / capturing?
    unsigned char dest_y;

    bool make_queen;      //pawn makes it to the other side

} action;

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

  board_node * A1_ptr; // "head" - i.e. where's the origin (0,0)
  board_node * H8_ptr; // "tail"

  //for checking stalemate condtion
  unsigned char turns_since_white_capture;
  unsigned char turns_since_black_capture;

  //
  int num_legal_moves;
  action * list_of_moves;


} board;


//expects an initialized board (all spaces populated)
void reset_pieces(board &b)
{//put all the pieces in their initial locations

  board_node * current = b.A1_ptr;

  for(unsigned char i = 0; i < 64; i++)
  {

    // std::cout << "resetting pieces " << (int)i << " @ ";
    // std::cout << current << " ... " << std::flush;

    switch(i)
    {
      // BLACK SIDE    BLACK SQUARES             WHITE SQUARES
      // ROOK | KNIGHT | BISHOP_C | KING | QUEEN | BISHOP_F | KNIGHT | ROOK
      case  0: set_contents(*current, BLACK_ROOK);     break;
      case  1: set_contents(*current, BLACK_KNIGHT);   break;
      case  2: set_contents(*current, BLACK_BISHOP_C); break;
      case  3: set_contents(*current, BLACK_KING);     break;
      case  4: set_contents(*current, BLACK_QUEEN);    break;
      case  5: set_contents(*current, BLACK_BISHOP_F); break;
      case  6: set_contents(*current, BLACK_KNIGHT);   break;
      case  7: set_contents(*current, BLACK_ROOK);     break;

      // PAWNS
      case  8:
      case  9:
      case 10:
      case 11:
      case 12:
      case 13:
      case 14:
      case 15: //drop through
        set_contents(*current, BLACK_PAWN);     break;

      case 48:
      case 49:
      case 50:
      case 51:
      case 52:
      case 53:
      case 54:
      case 55: //drop through
        set_contents(*current, WHITE_PAWN);     break;

      // WHITE SIDE    WHITE SQUARES             BLACK SQUARES
      // ROOK | KNIGHT | BISHOP_C | KING | QUEEN | BISHOP_F | KNIGHT | ROOK
      case 56: set_contents(*current, WHITE_ROOK);     break;
      case 57: set_contents(*current, WHITE_KNIGHT);   break;
      case 58: set_contents(*current, WHITE_BISHOP_C); break;
      case 59: set_contents(*current, WHITE_KING);     break;
      case 60: set_contents(*current, WHITE_QUEEN);    break;
      case 61: set_contents(*current, WHITE_BISHOP_F); break;
      case 62: set_contents(*current, WHITE_KNIGHT);   break;
      case 63: set_contents(*current, WHITE_ROOK);     break;

      // THE REMAINING 4 ROWS ARE EMPTY
      default: set_contents(*current, EMPTY);          break;
    }

    current = current->next;

  }

}

bool isodd(unsigned char a)
{
  return a % 2;  //zero, you're even - one, you're odd
}

//GET A NEW BOARD
board get_a_board()
{

  board temp;
  board_node * temp_head;
  board_node * prev_node = NULL;
  board_node * current_node = new board_node(); //to be the first space

  unsigned char x,y;

  for(unsigned char loc = 0; loc < 64; loc++ )
  {

    if(!loc)  temp_head = current_node; //first one - (zero is false)

    // std::cout << "loc " << (int)loc << std::endl;


//integer division by 8
//result odd/even?
//sets the addresses then based on odd/even loc, alternating direction per row

    unsigned char loc8 = y = loc/8; //what row
    unsigned char offset = loc % 8; //what column

    //starting information for the square
    set_dimension(*current_node, offset, loc8);   //A1 is (x, y) = (0, 0)

    unsigned char temp = loc + (loc8 % 2);

    if(isodd(temp))
      set_color(*current_node, BLACK);
    else
      set_color(*current_node, WHITE);


    current_node->next = NULL;
    if(loc != 63) //location 63 is the end
      current_node->next = new board_node();


    current_node->prev = prev_node;
    prev_node = current_node;
    current_node = current_node->next;

  }

  temp.A1_ptr = temp_head;

  temp.turns_since_white_capture = 0;
  temp.turns_since_black_capture = 0;

  reset_pieces(temp);

  return temp;

}

void print(board b)
{//output the contents to the command line

  typedef struct space_type
  {

    color c_board;
    color c_piece;
    char content;

  } space;

  space board[8][8];

  board_node * current;
  current = b.A1_ptr;

//reformat the data
  for (int loc = 0; loc < 64; loc++)
  {
    board[ current->x ][ current->y ].c_board = current->square_color;

    piece temp = current->current_contents;

    switch(temp)
    {

      case EMPTY:
        board[ current->x ][ current->y ].content = ' ';
        board[ current->x ][ current->y ].c_piece = NONE;
        break;
      case WHITE_PAWN:
      case BLACK_PAWN:
        board[ current->x ][ current->y ].content = 'p';
        if(temp == WHITE_PAWN)
          board[ current->x ][ current->y ].c_piece = WHITE;
        else
          board[ current->x ][ current->y ].c_piece = BLACK;
        break;
      case WHITE_KNIGHT:
      case BLACK_KNIGHT:
        board[ current->x ][ current->y ].content = 'k';
        if(temp == WHITE_KNIGHT)
          board[ current->x ][ current->y ].c_piece = WHITE;
        else
          board[ current->x ][ current->y ].c_piece = BLACK;
        break;
      case WHITE_BISHOP_C:
      case WHITE_BISHOP_F:
      case BLACK_BISHOP_C:
      case BLACK_BISHOP_F:
        board[ current->x ][ current->y ].content = 'b';
        if(temp == WHITE_BISHOP_C || temp == WHITE_BISHOP_F)
          board[ current->x ][ current->y ].c_piece = WHITE;
        else
          board[ current->x ][ current->y ].c_piece = BLACK;
        break;
      case WHITE_ROOK:
      case BLACK_ROOK:
        board[ current->x ][ current->y ].content = 'R';
        if(temp == WHITE_ROOK)
          board[ current->x ][ current->y ].c_piece = WHITE;
        else
          board[ current->x ][ current->y ].c_piece = BLACK;
        break;
      case WHITE_QUEEN:
      case BLACK_QUEEN:
        board[ current->x ][ current->y ].content = 'Q';
        if(temp == WHITE_QUEEN)
          board[ current->x ][ current->y ].c_piece = WHITE;
        else
          board[ current->x ][ current->y ].c_piece = BLACK;
        break;
        break;
      case WHITE_KING:
      case BLACK_KING:
        board[ current->x ][ current->y ].content = 'K';
        if(temp == WHITE_KING)
          board[ current->x ][ current->y ].c_piece = WHITE;
        else
          board[ current->x ][ current->y ].c_piece = BLACK;
        break;
      default:
        board[ current->x ][ current->y ].content = ' ';
        board[ current->x ][ current->y ].c_piece = NONE;
        break;

    }
    current = current->next;
  }

  std::cout << std::endl;

  color piece_color;

  int n = 0;

  for(unsigned char x = 0; x < 8; x++)
  {
    for(unsigned char y = 0; y < 8; y++)
    {

      if(board[x][y].c_board == BLACK)
      {
        if(board[x][y].c_piece == BLACK)
          std::cout << T_RED;
        else if (board[x][y].c_piece == WHITE)
          std::cout << T_MAGENTA;


        std::cout << B_BLACK;
        std::cout << " "<< board[x][y].content << " " << RESET;
        n++;
      }
      else
      {

        if(board[x][y].c_piece == BLACK)
          std::cout << T_RED;
        else if (board[x][y].c_piece == WHITE)
          std::cout << T_MAGENTA;

        std::cout << B_WHITE << " "<< board[x][y].content << " " << RESET;
        n++;
      }

      // std::cout << " " << n  << ": "<< "k" << " ";  n++;
      // std::cout << x << y;

    }
    std::cout << RESET << "    column " << (char)(65+x) << std::endl;
  }

  for(unsigned char x = 0; x < 8; x++)
  {
    cout << " " << x + 1 << " ";
  }

  std::cout << RESET <<std::endl;

}


//MAIN
int main(int argc, char const *argv[]) {

  board b = get_a_board();

  print(b);

  return 0;
}
