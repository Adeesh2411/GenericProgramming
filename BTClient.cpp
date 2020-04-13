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
    string s="abcdefghxyz";
    
    BinaryTree<decltype(s)> a(s);
    a.BalanceTree();
    a.display();
    a.deleteNode('e');
    a.display();
    
}