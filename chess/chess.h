#include "game.h"
#include "board_dnode.h"

using namespace main_savitch_14;

/* OLD CHECKERS PIECE CLASS - PIECE REPRESENTED EACH POSSIBLE PIECE ON THE BOARD 
class piece : public game{

    public:

    piece();

    void output(std::ostream &outs);

    bool empty; //THESE WHITE, BLACK PIECES WERE SOMETHING I TRIED TO ADD WHEN I WAS TRYING TO REWORK THE CHECKERS GAME INTO CHESS
    bool white_king, white_queen, white_rook, white_knight01, white_knight02; 
    bool black_king, black_queen, black_rook, black_knight01, black_knight02;
};
*/

class chess : public game{

    public:
      chess();

      //game *clone() { return clone(); }
      //void output(std::ostream &outs);
      void display_status();
      bool is_legal(const std::string& move);
      void make_move(const std::string& move);

      void test(std::ostream &outs);

      int move_counter;

    private:
      board_dnode board_space;
};
std::ostream &operator<<(std::ostream &outs, piece &p);
