#include "colors.h"
#include <iostream>
#include <iomanip>


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

  unsigned char white_score;
  unsigned char black_score;

  unsigned char white_captures;
  unsigned char black_captures;


  //
  int num_legal_moves;
  action * list_of_moves;

  board_node dead_white_guys[16];
  board_node dead_black_guys[16];




} board;


//expects an initialized board (all spaces populated)
void reset_pieces(board &b)
{//put all the pieces in their initial locations

  b.state = WHITE_TURN;

  b.num_legal_moves = 0;
  b.list_of_moves = NULL;

  for(unsigned char i = 0; i < 16; i++)
  {
    b.dead_black_guys[i].current_contents = EMPTY;
    b.dead_black_guys[i].square_color = NONE;

    b.dead_white_guys[i].current_contents = EMPTY;
    b.dead_white_guys[i].square_color = NONE;
  }

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

    unsigned char temp_char = loc + (loc8 % 2);

    if(isodd(temp_char))
      set_color(*current_node, BLACK);
    else
      set_color(*current_node, WHITE);


    current_node->next = NULL;
    if(loc != 63) //location 63 is the end
      current_node->next = new board_node();
    else
    {
      temp.H8_ptr = current_node;
      // set_color(*current_node, BLACK);

    }


    current_node->prev = prev_node;
    prev_node = current_node;
    current_node = current_node->next;

  }

  temp.A1_ptr = temp_head;

  temp.turns_since_white_capture = 0;
  temp.turns_since_black_capture = 0;

  temp.white_score = 0;
  temp.black_score = 0;

  temp.white_captures = 0;
  temp.black_captures = 0;

  reset_pieces(temp);

  return temp;

}


typedef struct space_type
{

  color c_board;
  color c_piece;
  char content;

} space;



space get_space_from_board_node(board_node bn)
{
  space temp_space;

  temp_space.c_board = bn.square_color;

  piece temp = bn.current_contents;

  switch(temp)
  {

    case EMPTY:
      temp_space.content = '_';
      temp_space.c_piece = NONE;
      break;
    case WHITE_PAWN:
    case BLACK_PAWN:
      temp_space.content = 'p';
      if(temp == WHITE_PAWN)
        temp_space.c_piece = WHITE;
      else
        temp_space.c_piece = BLACK;
      break;
    case WHITE_KNIGHT:
    case BLACK_KNIGHT:
      temp_space.content = 'k';
      if(temp == WHITE_KNIGHT)
        temp_space.c_piece = WHITE;
      else
        temp_space.c_piece = BLACK;
      break;
    case WHITE_BISHOP_C:
    case WHITE_BISHOP_F:
    case BLACK_BISHOP_C:
    case BLACK_BISHOP_F:
      temp_space.content = 'b';
      if(temp == WHITE_BISHOP_C || temp == WHITE_BISHOP_F)
        temp_space.c_piece = WHITE;
      else
        temp_space.c_piece = BLACK;
      break;
    case WHITE_ROOK:
    case BLACK_ROOK:
      temp_space.content = 'R';
      if(temp == WHITE_ROOK)
        temp_space.c_piece = WHITE;
      else
        temp_space.c_piece = BLACK;
      break;
    case WHITE_QUEEN:
    case BLACK_QUEEN:
      temp_space.content = 'Q';
      if(temp == WHITE_QUEEN)
        temp_space.c_piece = WHITE;
      else
        temp_space.c_piece = BLACK;
      break;
      break;
    case WHITE_KING:
    case BLACK_KING:
      temp_space.content = 'K';
      if(temp == WHITE_KING)
        temp_space.c_piece = WHITE;
      else
        temp_space.c_piece = BLACK;
      break;
    default:
      temp_space.content = '_';
      temp_space.c_piece = NONE;
      break;
    }

    return temp_space;
}

void print(board b)
{//output the contents to the command line

  space board[8][8];

  space white_graveyeard[16];
  space black_graveyeard[16];

  for(unsigned char i = 0; i < 16; i++)
  {
    white_graveyeard[i] = get_space_from_board_node(b.dead_white_guys[i]);
    black_graveyeard[i] = get_space_from_board_node(b.dead_black_guys[i]);
  }


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


  std::cout << std::endl << RESET;

  switch (b.state) {

    case WHITE_TURN:
      std::cout << "    ";
      std::cout << B_WHITE << T_BLACK;
      std::cout <<  "    IT\'S WHITE\'S TURN   ";
      break;
    case BLACK_TURN:

      std::cout << "    ";
      std::cout << B_BLACK << T_WHITE;
      std::cout <<  "    IT\'S BLACK\'S TURN   ";
      break;

    case WHITE_VICTORY:
      std::cout << "            ";
      std::cout << T_BLACK << B_WHITE;
      std::cout << "     WHITE WINS  ";
      break;

    case BLACK_VICTORY:

      std::cout << "            ";
      std::cout << T_WHITE << B_BLACK;
      std::cout << "     BLACK WINS  ";
      break;


    case STALEMATE:
        std::cout << "            ";
        std::cout << T_RED << B_BLUE;
        std::cout << "     STALEMATE  ";
      break;//maybe do a win by points thing

    default:

      std::cout << "            ";
      std::cout << T_RED << B_BLACK;
      std::cout << "     SOMETHING\'S FUCKED  ";
      break;
  }

  std::cout << RESET << std::endl;

  std::cout << std::endl << " BLACK SCORE: ";
  if(b.black_score)
    std::cout << std::setw(4) << b.black_score;
  else
    std::cout << "ZERO";
  std::cout << "    ";

  for(unsigned char x = 0; x < 8; x++)
  {
    cout << " " << x + 1 << " ";
  }

  std::cout << "      ";

  std::cout << "WHITE SCORE: ";
  if(b.white_score)
    std::cout << std::setw(4) << b.white_score;
  else
    std::cout << "ZERO" << std::endl;

  color piece_color;

  int n = 0;

  for(unsigned char x = 0; x < 8; x++)
  {

    //black graveyard (killed white pieces)

    std::cout << " " << T_WHITE << B_YELLOW << "| ";
    std::cout << RESET << " ";


    std::cout << T_MAGENTA << "  " << white_graveyeard[x].content;
    std::cout << RESET << " ";

    std::cout << " " << T_WHITE << B_YELLOW << "_" << RESET;


    std::cout << T_MAGENTA << "  " << white_graveyeard[x+8].content;
    std::cout << " " << RESET << " ";


    std::cout << " " << T_WHITE << B_YELLOW << "| ";
    std::cout << RESET << "   ";

    std::cout << RESET << (char)(65+x) << " ";


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

    }
    std::cout << RESET << " " << (char)(65+x) << "   ";
    std::cout << T_WHITE << B_YELLOW << "| " << RESET;

    //white graveyard (killed black pieces)

    std::cout << T_RED << "   " << black_graveyeard[x].content;
    std::cout << RESET << " ";
    std::cout << " " << T_WHITE << B_YELLOW << "_" << RESET;



    std::cout << T_RED << "  " << black_graveyeard[x+8].content;
    std::cout << " " << RESET << " ";

    std::cout << " " << T_WHITE << B_YELLOW << "| ";
    std::cout << RESET << " ";


    std::cout << RESET <<std::endl;
  }

  std::cout << " " << T_WHITE << B_YELLOW << "________________ ";

  std::cout << RESET <<"      ";

  for(unsigned char x = 0; x < 8; x++)
  {
    cout << " " << x + 1 << " ";
  }

  std::cout << "    " << T_WHITE << B_YELLOW << "________________ ";


  std::cout << RESET <<std::endl << std::endl;

}
