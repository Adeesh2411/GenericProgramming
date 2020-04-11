#include<iostream>
#include<utility>
#include<vector>
using namespace std;

//inner class of binary tree
template<typename T>
class TreeStruct{    
    TreeStruct(const T &obj, int r = -1):data_(obj), rank_(r){}
    int rank_;
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
        BinaryTree(const T1& unknownObject, int N):givenObject(unknownObject), rank_(N){
           initialise();
        }
        BinaryTree(const T1 &unknownObject):givenObject(unknownObject){
            createTree();
        }
        ~BinaryTree(){
            deleteAll(Start);
            Start = nullptr;
        }
        //function declarations
        void display();// to display the tree
        void display(TreeStruct<T2> *start); // to display the tree 
        
        void createTree(); // Creating tree if collection is given
        void deleteAll(TreeStruct<T2>*); // called by dtor at the end 
        void addNode(const T2 &a); // adding node at the required position
        void initialise();//Initialise the Start pointer for separate allocation
        void insertNode(const T1& unknownObject, int rank);// inserting the given object at 
                                                           //specified position for given rank     
        void BalanceTree();//time complexity = O(n) and Space = O(n)
        

    private:
        void storeNode(TreeStruct<T2>* St, vector<TreeStruct<T2>*> &v1);//store all the nodes
        TreeStruct<T2>* BuildBalancedTree(vector<TreeStruct<T2>*> &v1, int start, int end);// AVL
        const T1& givenObject;
        int rank_;    
        TreeStruct<T2> *Start = nullptr;
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
    cout<<endl;
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

template<typename T1, typename T2>
void BinaryTree<T1, T2>::initialise(){
    TreeStruct<T2> *Obj = new TreeStruct<T2>(givenObject, rank_);
        Obj->left = Obj->right = nullptr;
        Start = Obj;
}


template<typename T1, typename T2>
void BinaryTree<T1, T2>::insertNode(const T1 &a, int rank){    
    using innerType = T2;

    TreeStruct<innerType> *temp = Start;
    TreeStruct<innerType> *prev = nullptr;
    while(temp){
        prev = temp;
        if(temp->rank_ < rank){
            temp=temp->right;
        }
        else{
            temp = temp->left;
        }
    }
    if(prev && prev->rank_ < rank){
        prev->right = new TreeStruct<innerType>(a, rank);
    }
    else {
        prev->left = new TreeStruct<innerType>(a, rank);
    }
}

template<typename T1, typename T2>
void BinaryTree<T1, T2>::BalanceTree(){
    vector<TreeStruct<T2>*> v;
    storeNode(Start, v);
    Start = BuildBalancedTree(v, 0, v.size()-1);
}

template<typename T1, typename T2>
void BinaryTree<T1, T2>::storeNode(TreeStruct<T2>* root, vector<TreeStruct<T2>*> &v){
    if(root){
        storeNode(root->left, v);
        v.push_back(root);
        storeNode(root->right, v);
    }
}

template<typename T1, typename T2>
TreeStruct<T2>* BinaryTree<T1, T2>::BuildBalancedTree(vector<TreeStruct<T2>*> &v, int start, int end){
    if(start<=end){
        int mid = (start+end)/2;
       
        v[mid]->left = BuildBalancedTree(v, start, mid - 1);
        v[mid]->right = BuildBalancedTree(v, mid+1, end); 
        return v[mid];
    }
    return nullptr;
}