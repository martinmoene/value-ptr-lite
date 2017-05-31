#include "value_ptr.hpp"
#include <string>

using namespace nonstd;

struct Tree
{
    std::string const name;
    value_ptr<Tree> left;
    value_ptr<Tree> right;

    Tree()
    : name()
    , left()
    , right()
    {}

    Tree(
        std::string const & name
        , value_ptr<Tree> const & left  = value_ptr<Tree>()
        , value_ptr<Tree> const & right = value_ptr<Tree>() )
    : name ( name  )
    , left ( left  )
    , right( right )
    {}
};

int main()
{
    Tree root = Tree( "root", Tree("left-0"), Tree("right-0") );

    assert( root.name        == "root" );
    assert( root.left->name  == "left-0" );
    assert( root.right->name == "right-0" );

    root.left  = root; // Copy of root assigned to left
    root.right = root; //   and we don't have cyclic references

    assert( root.name        == "root" );
    assert( root.left->name  == "root" );
    assert( root.right->name == "root" );
}

// cl  -EHsc -I../include/nonstd/ 02-tree.cpp && 02-tree.exe
// g++ -std=c++11 -I../include/nonstd/ -o 02-tree.exe 02-tree.cpp && 02-tree.exe
