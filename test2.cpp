#include<iostream>
#include<utility>
#include<vector>
#include<list>
#include<queue>
#include<typeinfo>
using namespace std;


template<typename T>
class TreeStruct{    
    TreeStruct(const T &obj, int r = -1):data_(obj), rank_(r){}
    int rank_;
    TreeStruct *left, *right, *up;
    T data_;

    bool operator==(const TreeStruct<T>& rhs);
    bool operator!=(const TreeStruct<T>& rhs);
    
    template<class T1, class T2>
    friend class BinaryTree;
};


template<typename T1, typename T2 = typename T1::value_type>
class BinaryTree{
    public:

        //constructors...
        //
        BinaryTree(const BinaryTree<T1, T2> &rhs){}// If I comment this it gives error 
        BinaryTree():No_Of_Nodes(0){}
        BinaryTree(const T1 &unknownObject):givenObject(&unknownObject), No_Of_Nodes(0){
            createTree();
        }

        ~BinaryTree(){
            
        }
        
        void createTree(); 
        template<typename T>
        void addNode(const T &a); 

        BinaryTree<T1, T2> operator =(const BinaryTree<T1, T2> rhs);
        BinaryTree<T1, T2> operator =(BinaryTree<T1, T2>&& rhs); 
         


    private:

        //variables
        const T1* givenObject;
        bool inner;
        int No_Of_Nodes;   
        TreeStruct<T2> *Start1 = nullptr;
};

//all the function definition
template<typename T1, typename T2>
void BinaryTree<T1, T2>::createTree(){
    bool ST = true;
    for(auto it = begin(*givenObject); it!=end(*givenObject);++it){
        ++No_Of_Nodes;
        if(ST){
            ST = false;
            TreeStruct<T2> *Obj = new TreeStruct<T2>(*it);
            Obj->left = Obj->right = Obj->up = nullptr;
            Start1 = Obj;
        }
        else{
            addNode(*it);
            
        }
    }
}

template<typename T1, typename T2>
template<typename T>
void BinaryTree<T1, T2>::addNode(const T &a){    
    using innerType = T;
    ++No_Of_Nodes;
    TreeStruct<innerType> *temp = Start1;
    TreeStruct<innerType> *prev = temp;
    if(temp == nullptr){ 
        TreeStruct<T> *Obj = new TreeStruct<T>(a);
        Obj->left = Obj->right = Obj->up = nullptr;
        Start1 = Obj;
        return;
    }

    while(temp){
        prev = temp;
        if(temp->data_ < a){
            temp=temp->right;
        }
        else{
            temp = temp->left;
        }
        
    }
    
    if(prev && prev->data_ < a){
        prev->right = new TreeStruct<innerType>(a);
        prev->right->up = prev;
    }
    else {
        prev->left = new TreeStruct<innerType>(a);
        prev->left->up = prev;
    }
    return;
}


template<typename T1, typename T2>
BinaryTree<T1, T2> BinaryTree<T1, T2>::operator =(const BinaryTree<T1, T2> rhs){
    
    return *this;
}

int main(){
    string s1="abcd";
    string s2="xyz";

    BinaryTree<decltype(s1)> b1(s1);
    BinaryTree<decltype(s2)> b2(s2);
    b1 = b2;
}