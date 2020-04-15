#include<iostream>
#include<vector>
#include<list>
#include<initializer_list>
#include "BinaryTree.hpp"
#include<string>
using namespace std;



int main(){
    vector<int> vec2{1,3,4,5,6,7};
    vector<int> vec1{2,5,4};
    int arr[6]={2,3,4,5,1,6};
    BinaryTree<decltype(vec2)> b1(vec2, arr);
    b1.display();
}