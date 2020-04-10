#include<iostream>
#include<utility>
using namespace std;

//inner class of binary tree
template<typename T>
class TreeStruct{    
    TreeStruct(const T &obj):data_(obj){}

    TreeStruct *left, *right;
    T data_;

    template<class T1, class T2>
    friend class BinaryTree;
};


//Main class of binary tree
template<typename T1, typename T2 = typename T1::value_type>
class BinaryTree{
    public:
        //constructors...
        BinaryTree(){}
        BinaryTree(int n, int r):size1_(n),rank_(r){}
        BinaryTree(int n):size_(n){}
        BinaryTree(const T1 &unknownObject):givenObject(unknownObject){
            createTree();
        }
        ~BinaryTree(){
            deleteAll(Start);
            Start = nullptr;
        }

        void display();
        void display(TreeStruct<T2> *start);
        
        void createTree();
        void deleteAll(TreeStruct<T2>*);
        void addNode(const T2 &a);
    private:
        int size_;
        const T1& givenObject;
        int size1_;
        int rank_;    
        TreeStruct<T2> *Start;
};

//all the function definition
template<typename T1, typename T2>
void BinaryTree<T1, T2>::createTree(){
    bool ST = true;
    //using innerType = typename T1::value_type;
    for(auto it = begin(givenObject); it!=end(givenObject);++it){
        if(ST){
            ST = false;
            TreeStruct<T2> *Obj = new TreeStruct<T2>(*it);
            Obj->left = Obj->right = nullptr;
            Start = Obj;
        }
        else{
            addNode(*it);
        }
    }
}

template<typename T1, typename T2>
void BinaryTree<T1, T2>::addNode(const T2 &a){    
    using innerType = T2;

    TreeStruct<innerType> *temp = Start;
    TreeStruct<innerType> *prev = nullptr;
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
    }
    else {
        prev->left = new TreeStruct<innerType>(a);
    }
}

template<typename T1, typename T2>
void BinaryTree<T1, T2>::display(TreeStruct<T2> *start){
    if(start){
        std::cout<<start->data_<<" ";
        display(start->left);
        display(start->right);
    }

}

template<typename T1, typename T2>
void BinaryTree<T1, T2>::display(){
    display(Start);
    std::cout<<std::endl;
}

template<typename T1, typename T2>
void BinaryTree<T1, T2>::deleteAll(TreeStruct<T2>* Start){
    if(Start){
        deleteAll(Start->left);
        deleteAll(Start->right);
        delete Start;
        Start = nullptr;
    }
}