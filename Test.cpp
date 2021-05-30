#include "sources/BinaryTree.hpp"
#include "doctest.h"
#include <sstream>
#include <iostream>
#include <functional>

using namespace ariel;
using namespace std;
using std::placeholders::_1;

TEST_CASE("pre_order_int")
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
    CHECK_EQ(pre_out.str(), "1 2 3 4 5 6 7 8 9 10 11 ");
    ostringstream pre_out2;
    auto tempend = ++++++b.begin_preorder();
    for (auto it = b.begin_preorder(); it != tempend; ++it)
    {
        
        pre_out2 << *it << ' ';
    }
    //   return 0;
    CHECK_EQ(pre_out2.str(), "1 2 3 ");
}
TEST_CASE("in_order_int")
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
    cout << b << endl;
    ostringstream out;
    for (auto it = b.begin_inorder(); it != b.end_inorder(); ++it)
    {
        cout << *it << endl;
        out << (*it) << " ";
    }
    CHECK_EQ(out.str(), "1 2 3 4 5 6 7 ");
    ostringstream out2;
    auto tempend = ++++++b.begin_inorder();
    cout << *tempend << endl << endl;

    for (auto it = b.begin_inorder(); it != tempend; ++it)
    {
        out2 << *it << ' ';
    }
    //   return 0;
    CHECK_EQ(out2.str(), "1 2 3 ");
}
TEST_CASE("post_order_int")
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

    ostringstream post_out;
    for (auto it = b.begin_postorder(); it != b.end_postorder(); ++it)
    {
        post_out << (*it) << " ";
    }
    //   return 0;
    CHECK_EQ(post_out.str(), "1 2 3 4 5 6 7 ");
    ostringstream post_out2;
    auto tempend = ++++++b.begin_postorder();
    for (auto it = b.begin_postorder(); it != tempend; ++it)
    {
        post_out2 << *it << ' ';
    }
    //   return 0;
    CHECK_EQ(post_out2.str(), "1 2 3 ");
}

TEST_CASE("pre_order_string")
{
    //   int main(){
    BinaryTree<string> b;
    b.add_root("1");
    b.add_left("1", "2");
    b.add_left("2", "3");
    b.add_left("3", "4");
    b.add_left("4", "5");
    b.add_left("5", "6");
    b.add_right("5", "7");
    b.add_right("4", "8");
    b.add_right("1", "9");
    b.add_left("9", "10");
    b.add_right("10", "11");

    ostringstream pre_out;
    for (auto it = b.begin_preorder(); it != b.end_preorder(); ++it)
    {
        pre_out << (*it) << " ";
    }
    CHECK_EQ(pre_out.str(), "1 2 3 4 5 6 7 8 9 10 11 ");
    ostringstream pre_out2;
    auto tempend = ++++++b.begin_preorder();
    for (auto it = b.begin_preorder(); it != tempend; ++it)
    {
        pre_out2 << *it << ' ';
    }
    //   return 0;
    CHECK_EQ(pre_out2.str(), "1 2 3 ");
}

TEST_CASE("in_order_string")
{
    // int main()
    // {
    BinaryTree<string> b;
    b.add_root("1");
    b.add_right("1", "6");
    b.add_left("6", "3");
    b.add_right("6", "7");
    b.add_left("3", "2");
    b.add_right("3", "5");
    b.add_left("5", "4");

    ostringstream out;
    for (auto it = b.begin_inorder(); it != b.end_inorder(); ++it)
    {
        out << (*it) << " ";
    }
    CHECK_EQ(out.str(), "1 2 3 4 5 6 7 ");
    ostringstream out2;
    auto tempend = ++++++b.begin_inorder();
    for (auto it = b.begin_inorder(); it != tempend; ++it)
    {
        out2 << *it << ' ';
    }
    //   return 0;
    CHECK_EQ(out2.str(), "1 2 3 ");
}

TEST_CASE("post_order_string")
{
    // int main()
    // {
    BinaryTree<string> b;
    b.add_root("7");
    b.add_right("7", "6");
    b.add_left("7", "1");
    b.add_right("6", "5");
    b.add_left("5", "3");
    b.add_right("5", "4");
    b.add_left("3", "2");

    ostringstream post_out;
    for (auto it = b.begin_postorder(); it != b.end_postorder(); ++it)
    {
        post_out << (*it) << " ";
    }
    ostringstream post_out2;
    auto tempend = ++++++b.begin_postorder();
    for (auto it = b.begin_postorder(); it != tempend; ++it)
    {
        post_out2 << *it << ' ';
    }
    //   return 0;
    CHECK_EQ(post_out.str(), "1 2 3 4 5 6 7 ");
    CHECK_EQ(post_out2.str(), "1 2 3 ");
}
struct person
{
    int age;
    person(int age) : age(age) {}
    person() : age(0) {}
    int get_age() const
    {
        return this->age;
    }
    bool operator!=(person other)
    {
        return this->age != other.age;
    }

    bool operator==(person other)
    {
        return !(*this != other);
    }
    friend ostream &operator<<(ostream &os, const person &p);
};
ostream &operator<<(ostream &os, const person &p)
{
    return (os << p.get_age() << ' ');
}
TEST_CASE("operator->")
{
    // int main(){
    BinaryTree<person> b;
    b.add_root(3);
    b.add_left(3, 15);
    b.add_right(3, 6);
    CHECK_EQ(3, b.begin_preorder()->age);
    CHECK_EQ(15, b.begin_inorder()->age);
    b.add_left(15, 1).add_right(15, 2);
    CHECK_NOTHROW(cout << b << endl;);
    cout << ++++++++b.begin_postorder()->age << endl;
    CHECK_EQ(3, (++++++++b.begin_postorder())->age);
    CHECK_EQ(6, (++++++b.begin_postorder())->age);
}
TEST_CASE("operator*")
{

    BinaryTree<person> b;
    b.add_root(3);
    b.add_left(3, 15);
    b.add_right(3, 6);
    CHECK_EQ(3, (*b.begin_preorder()).get_age());
    CHECK_EQ(15, (*b.begin_inorder()).get_age());
    b.add_left(15, 1).add_right(15, 2);
    CHECK_NOTHROW(cout << b << endl;);
    CHECK_EQ(3, (*(++++++++b.begin_postorder())).get_age());
    CHECK_EQ(6, (*(++++++b.begin_postorder())).get_age());
}