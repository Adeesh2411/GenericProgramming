#include<iostream>

//inner class of binary tree
template<typename T>
class TreeStruct{    
    TreeStruct(const T &obj):data_(obj){}

    TreeStruct *left, *right;
    T data_;

    template<typename T1>
    friend class BinaryTree;
};


//Main class of binary tree
template<typename T1>
class BinaryTree{
    public:
        //constructors...
        BinaryTree(int n, int r):size1_(n),rank_(r){}
        BinaryTree(int n):size_(n){}
        BinaryTree(){}
        BinaryTree(T1 &unknownObject):givenObject(unknownObject){
            createTree();
        }
        ~BinaryTree(){
            deleteAll(Start);
            Start = nullptr;
        }

        void display();
        void display(TreeStruct<typename T1::value_type> *start);
        
        void createTree();
        void deleteAll(TreeStruct<typename T1::value_type>*);
        void addNode(const typename T1::value_type &a);

    private:
        int size_;
        T1 givenObject;
        int size1_;
        int rank_;    
        TreeStruct<typename T1::value_type> *Start;
};


//all the function definition
template<typename T1>
void BinaryTree<T1>::createTree(){
    bool ST = true;
    using innerType = typename T1::value_type;
    for(auto it = begin(givenObject); it!=end(givenObject);++it){
        if(ST){
            ST = false;
            TreeStruct<innerType> *Obj = new TreeStruct<innerType>(*it);
            Obj->left = Obj->right = nullptr;
            Start = Obj;
        }
        else{
            addNode(*it);
        }
    }
}

template<typename T1>
void BinaryTree<T1>::addNode(const typename T1::value_type &a){    
    using innerType = typename T1::value_type;

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

template<typename T1>
void BinaryTree<T1>::display(TreeStruct<typename T1::value_type> *start){
    if(start){
        std::cout<<start->data_<<" ";
        display(start->left);
        display(start->right);
    }

}

template<typename T1>
void BinaryTree<T1>::display(){
    display(Start);
    std::cout<<std::endl;
}

template<typename T1>
void BinaryTree<T1>::deleteAll(TreeStruct<typename T1::value_type>* Start){
    if(Start){
        deleteAll(Start->left);
        deleteAll(Start->right);
        delete Start;
        Start = nullptr;
    }
}
