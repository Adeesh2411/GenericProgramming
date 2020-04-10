#include<iostream>
#include<vector>
#include<list>
#include<initializer_list>
#include "BinaryTree.hpp"
using namespace std;



int main(){
    vector<int> vec{2,3,4};
    int arr[4]={2,31,4,1};

    BinaryTree<decltype(vec)> bt(vec);
    bt.display();
}