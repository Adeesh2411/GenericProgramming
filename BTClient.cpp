#include<iostream>
#include<vector>
#include<list>
#include<initializer_list>
#include "BinaryTree.hpp"
#include<string>
using namespace std;
/*
    1.arithmetic operation
    2.addition of two binary tree's
    3.
*/

int main(){
    vector<int> vec2{1,3,4,5,6,7};
    vector<int> vec1{2,5,4,1,7,8};
    int ranks[6]={2,3,4,5,1,6};
    string s ="abcdef";

    #if 1
    
         //creating BST for given collection of objects, where each object acts as node, without rank
        //format = <decltype()>(collection)
        BinaryTree<decltype(vec2)> b1(vec2);
        cout<<"collection of objects without rank\n";
        b1.display();
        cout<<"adding a node 10\n";
        b1.addNode(10);
        b1.display();
        cout<<"deleting a node 4\n";
        b1.deleteNode(4);
        b1.display();
        cout<<"displaying using iterator\n";
        for(auto it=b1.begin();it!=b1.end();it++){
            cout<<*it<<" ";
        }
        cout<<endl<<endl;
    
    #endif
    #if 1
        cout<<"given collection to act as node\n";
        //given collection to act as each node
        //format =<decltype(), decltype()> (collection, rank, true)
        BinaryTree<decltype(vec2), decltype(vec2)> b2(vec2,1, true);//true indicates your passing current object itself to act as node
        //addNode format = (object, true, rank) or (object);
        b2.addNode(vec1,true, 2);
        b2.addNode(vec2, true, 3);
        b2.deleteNode(vec2);
        cout<<endl;
    #endif
    #if 1
    
        //passing collection with array of ranks
        //format =<decltype()>(collection, array)
        cout<<"given collection with array of ranks\n";
        BinaryTree<decltype(vec2)> b3(vec2, ranks);
        b3.display();
        b3.addNode(62,true, 7); //pass true as second argument saying that rank exists 
        b3.display();
        b3.deleteNode(62);
        b3.display();
        cout<<"Using Iterator to print\n";
        for(auto it=b3.begin();it!=b3.end();it++){
            cout<<*it<<" ";
        }
        cout<<endl<<endl;

    
    #endif
    #if 1
    
        //passing collection which act as entire node without rank
        //format =<decltype(), decltype()>(Object, true)
        cout<<"given collection to act as entire node without rank\n";
        BinaryTree<decltype(s), decltype(s)> b4(s, true);
        b4.addNode(string("xyz"));
        b4.display();
        b4.deleteNode(s);
        b4.display();
        cout<<"display using iterator\n";
        for(auto it=b4.begin();it!=b4.end();it++){
            cout<<*it<<" ";
        }
        cout<<endl<<endl;

    
    #endif

    #if 1
        //copy and move operator
        cout<<"copy and move ctors\n";
        BinaryTree<decltype(vec1)> b5(vec1);
        BinaryTree<decltype(vec2)> b6(move(b5));
        b5.display();
        b6.display();
    #endif
}