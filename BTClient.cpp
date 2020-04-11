#include<iostream>
#include<vector>
#include<list>
#include<initializer_list>
#include "BinaryTree.hpp"
#include<string>
using namespace std;



int main(){
    vector<int> vec{2,3,4};
    int arr[4]={2,31,4,1};
    string s="xyzabcd";
    
    BinaryTree<int, int> a(1,1);
    a.insertNode(2,2);
    a.insertNode(3,3);
    a.insertNode(4,4);
    a.display();
    a.BalanceTree();
    a.display();
}