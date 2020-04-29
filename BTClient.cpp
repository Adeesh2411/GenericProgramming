#include<iostream>
#include<vector>
#include<list>
#include<initializer_list>
#include "BinaryTree.hpp"
#include<string>
#include<algorithm>
using namespace std;
/*
    functions for client 
    1.NoOfNodes() =>returns the no of nodes present in the tree
    2.findNode(node) =>returns boolean value indicating whether node is present or not
    3.BalanceTree() => converts normal BST to height balanced binaryTree
    4.inOrder()
    5.preOrder()
    6.postOrder()
    7.addNode(node)
    8.deleteNode(node)
    9.begin()
    10.end()
    11.operator +(a, b) =>concating two trees
    12.operator ==, !=
    13.copy constructructor
    14.move constructor
    15.copy assignment
    16.move assignment

    5 different types of initialising is possible
    1. passing collection of objects , each object represents a node(with or without rank)
    2. passing collection of objects where entire objects represents a node(with or without rank)
    3. empty Tree   
*/

int main(){
    vector<int> vec2{1,3,5,9,7};
    vector<int> vec1{12,15,14,11,17,18};
    int ranks[6]={2,3,4,5,1,6};
    string s ="abcdef";

    BinaryTree<decltype(vec2)> b1(vec2);
    //find
    auto it = find(b1.begin(), b1.end(), 2);
    cout<<"value = ";
    cout<<*it<<endl;
    //all_of
    if ( std::all_of(b1.begin(), b1.end(), [](int i){return i%2;}) )
        cout << "All the elements are odd numbers.\n";

    //count
    int ct = count(b1.begin(), b1.end(), 100);
    cout<<"count = "<<ct<<endl;
    

    #if 0
    {
        //case 1 : given vector of integers
        cout<<"Given vector of integers\n";
        //if only collection of objects is passed, 
        //format : BinaryTree<type of Collection> b1(collection)
        BinaryTree<decltype(vec1)> b1(vec1);
        //traversal of Tree
        b1.inOrder();
        b1.postOrder();
        b1.preOrder();
        
        b1.BalanceTree();//balance tree is function which can height balance the binary tree
        cout<<"after balancing BST\n";
        b1.postOrder();
        b1.preOrder();
        b1.inOrder();

        cout<<"after adding 10 and 100\n";
        b1.addNode(10); //addNode() : adds the given object to tree, object need to be same type as earlier objects
        b1.addNode(200);
        b1.preOrder();
        
        cout<<"deleting node\n";
        b1.deleteNode(17); // deletes the perticular node from tree, if node is not present specifies warning message
        b1.deleteNode(200); //200 is not present
        b1.inOrder();
        cout<<" no of nodes in the above tree is "<<b1.NoOfNodes()<<endl;//noOfNodes() : returns the no Of Nodes at any given time
        cout<<boolalpha;
        cout<<"finding node in a tree\n";
        cout<<"node 100 is present ? : "<<b1.findNode(100)<<endl;
        cout<<"node 200 is present ? : "<<b1.findNode(200)<<endl; 
    
        cout<<"using iterator\n";
        for(auto it= b1.begin(); it!=b1.end(); it++)
            cout<<*it<<" ";//it performs level order traversal
        cout<<endl;

        cout<<"operator example\n";
        BinaryTree<decltype(vec1)> b2(vec2);
        BinaryTree<decltype(vec1)> b3(vec1);
        cout<<(b2==b3)<<endl;
        cout<<(b2==b1)<<endl;
        cout<<"merging two trees + "<<endl;
        b1 = b1+b2;
        b1.inOrder();
        cout<<"copy constructor \n";
        BinaryTree<decltype(vec1)> temp(b2);
        temp.inOrder();
        b2.inOrder();
        cout<<"move constructor \n";
        BinaryTree<decltype(vec1)>temp1(move(temp));
        temp1.preOrder();
        temp.preOrder();
        temp1.erase();
        cout<<"after erasing\n";
        temp1.preOrder();
    }
    cout<<endl;
    #endif
    #if 0
    {
        //Given collection and rank to compare
        // format : BinaryTree<collection type> b1(collection, rank)
        cout<<"given collection and rank to compare\n";
        BinaryTree<decltype(vec1)> b1(vec1, ranks); //here the objects are compared wrt ranks provided
        b1.inOrder(); b1.preOrder(); b1.postOrder();
        cout<<"after adding node 100\n";
        b1.addNode(100, true, 7); //here true indicates that given node is associated with rank, if not provided then warning message will
                                //be displayed saying ambiguous with rank
        b1.addNode(200); //warning : no rank specified
        b1.inOrder();

        cout<<"deleting node 17\n";
        b1.deleteNode(17); // object need to be specified to delete
        b1.inOrder(); 

        cout<<"balancing the tree\n";
        
        b1.BalanceTree();
        b1.inOrder(); b1.postOrder(); b1.preOrder();

        cout<<" no of nodes in the above tree is "<<b1.NoOfNodes()<<endl;//noOfNodes() : returns the no Of Nodes at any given time
        cout<<boolalpha;
        cout<<"finding node in a tree\n";
        cout<<"node 100 is present ? : "<<b1.findNode(100)<<endl;
        cout<<"node 200 is present ? : "<<b1.findNode(200)<<endl; 
    
        cout<<"using iterator\n";
        for(auto it= b1.begin(); it!=b1.end(); it++)
            cout<<*it<<" ";//it performs level order traversal
        cout<<endl;

        cout<<"operator example\n";
        int rank2[]={3,2,1,6,5,4};
        BinaryTree<decltype(vec1)> b2(vec1, ranks);
        BinaryTree<decltype(vec1)> b3(vec1 ,rank2);
        cout<<(b2==b3)<<endl;
        cout<<(b2==b1)<<endl;
        cout<<endl;
    }
    #endif

    #if 0
    {
        //given collection and each collection to act as node
        // format : BinaryTree<decltype of collection, decltype of collection>(collection, true)
        cout<<"entire collection to act as node\n";
        BinaryTree<decltype(s), decltype(s)> b1(s, true); // specify true to indicate that entire object to act as node
        cout<<"No of node = "<<b1.NoOfNodes()<<endl;
        b1.inOrder();
        cout<<"adding string\n";
        b1.addNode(string("fullMetal"));
        b1.addNode(string("ram"));
        b1.addNode(string("alchemist"));
        b1.preOrder();
        cout<<"after balancing tree\n";
        b1.BalanceTree();
        b1.preOrder();   
        cout<<"deleting node ram\n";
        b1.deleteNode(string("ram"));
        b1.preOrder();
        cout<<boolalpha;
        cout<<"finding node in a tree\n";
        cout<<"node ram is present ? : "<<b1.findNode(string("ram"))<<endl;
        cout<<"node fullMetal is present ? : "<<b1.findNode(string("fullMetal"))<<endl; 
    
        cout<<"using iterator\n";
        for(auto it= b1.begin(); it!=b1.end(); it++)
            cout<<*it<<" ";//it performs level order traversal
        cout<<endl;

        cout<<"operator example\n";
        BinaryTree<decltype(s), decltype(s)> b2(s, true);
        BinaryTree<decltype(s), decltype(s)> b3(s, true);
        cout<<(b2==b3)<<endl;
        cout<<endl;        
    }
    #endif
    #if 0
    {
        //given collection which acts as node given rank
        //format : BinaryTree<collection type, collection type> b1(collection ,rank)
        BinaryTree<decltype(vec1), decltype(vec1)> b1(vec1, 1);
        BinaryTree<decltype(vec1), decltype(vec1)> b2(vec2, 2);
        cout<<"No of nodes in b1 = "<<b1.NoOfNodes()<<endl;
        cout<<boolalpha;
        cout<<b1.findNode(vec1)<<endl;
        b1 = b1+b2;
        cout<<"No of nodes after merging = "<<b1.NoOfNodes()<<endl;
    }
    #endif
}