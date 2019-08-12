#include <iostream>

typedef struct b_node
{
  int x;
  int y;
} board_node;

//can now declare a board_node

int int main(int argc, char const *argv[]) {

  board_node current_space;

  current_space.x = 5;
  current_space.y = 3;

  cout << "the current space is " << current_space.x << " " << current_space.y;
  cout << endl;

  return 0;
}
