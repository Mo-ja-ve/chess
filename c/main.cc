#include <iostream>

typedef struct b_node
{
  int x;
  int y;
} board_node;

//can now declare a board_node

int main(int argc, char const *argv[]) {

  // board_node current_space;

  // current_space.x = 5;
  // current_space.y = 3;

  board_node * A0_ptr = new board_node();

  std::cout << "the current space is ";
  std::cout << A0_ptr->x << " ";
  std::cout << A0_ptr->y << std::endl;

  return 0;
}
