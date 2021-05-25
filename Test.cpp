#include "sources/BinaryTree.hpp"
#include "doctest.h"
#include <sstream>
#include <iostream>

using namespace ariel;
using namespace std;

TEST_CASE("pre_order")
{
    //   int main(){
    BinaryTree<int> b;
    b.add_root(1);
    b.add_left(1, 2);
    b.add_left(2, 3);
    b.add_left(3, 4);
    b.add_left(4, 5);
    b.add_left(5, 6);
    b.add_right(5, 7);
    b.add_right(4, 8);
    b.add_right(1, 9);
    b.add_left(9, 10);
    b.add_right(10, 11);

    ostringstream pre_out;
    for (auto it = b.begin_preorder(); it != b.end_preorder(); ++it)
    {
        pre_out << (*it) << " ";
    }
    //   return 0;
    CHECK_EQ(pre_out.str(), "1 2 3 4 5 6 7 8 9 10 11 ");
}
TEST_CASE("in_order")
{
// int main()
// {
  BinaryTree<int> b;
  b.add_root(1);
  b.add_right(1, 6);
  b.add_left(6, 3);
  b.add_right(6, 7);
  b.add_left(3, 2);
  b.add_right(3, 5);
  b.add_left(5, 4);

  ostringstream pre_out;
  for (auto it = b.begin_inorder(); it != b.end_inorder(); ++it)
  {
    pre_out << (*it) << " ";
  }
  // return 0;
  CHECK_EQ(pre_out.str(), "1 2 3 4 5 6 7 ");
}
TEST_CASE("post_order")
{
// int main()
// {
  BinaryTree<int> b;
  b.add_root(7);
  b.add_right(7, 6);
  b.add_left(7, 1);
  b.add_right(6, 5);
  b.add_left(5, 3);
  b.add_right(5, 4);
  b.add_left(3, 2);

  ostringstream pre_out;
  for (auto it = b.begin_postorder(); it != b.end_postorder(); ++it)
  {
    pre_out << (*it) << " ";
  }
//   return 0;
  CHECK_EQ(pre_out.str(), "1 2 3 4 5 6 7 ");
}