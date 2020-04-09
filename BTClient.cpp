#include<iostream>
#include<vector>
#include<list>
#include "BinaryTree.hpp"
using namespace std;



int main(){
    list<int> v{2,3,1,4};
    BinaryTree<list<int>> bt(v);
    bt.display();
}