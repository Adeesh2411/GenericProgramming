#include<iostream>
#include<vector>
#include<list>
#include<initializer_list>
#include "BinaryTree.hpp"
#include<string>
using namespace std;



int main(){
    vector<int> vec2{1,3,4,5,6,7};
    vector<int> vec1{2,5,4,1,7,8};
    int ranks[6]={2,3,4,5,1,6};
    string s ="abcdef";

    #if 0
    {
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
    }
    #endif
    #if 0
    {
        //given collection to act as each node
        //format =<decltype(), decltype()> (collection, rank, true)
        BinaryTree<decltype(vec2), decltype(vec2)> b1(vec2,1, true);//true indicates your passing current object itself to act as node
        //addNode format = (object, true, rank) or (object);
        b1.addNode(vec1,true, 2);
        b1.addNode(vec2, true, 3);
        b1.deleteNode(vec2);
    }
    #endif
    #if 0
    {
        //passing collection with array of ranks
        //format =<decltype()>(collection, array)
        BinaryTree<decltype(vec2)> b1(vec2, ranks);
        b1.display();
        b1.addNode(62,true, 7); //pass true as second argument saying that rank exists 
        b1.display();
        b1.deleteNode(62);
        b1.display();
    }
    #endif
    #if 1
    {
        //passing collection which act as entire node without rank
        //format =<decltype(), decltype()>(Object, true)
        BinaryTree<decltype(s), decltype(s)> b1(s, true);
        b1.addNode(string("xyz"));
        // b1.display();
        // b1.deleteNode(s);
        // b1.display();

        for(auto it=b1.begin();it!=b1.end();it++){
            cout<<*it<<endl;
        }
    }
    #endif
}