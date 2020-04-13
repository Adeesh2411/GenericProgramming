#include<iostream>
#include<utility>
#include<vector>
#include<list>
#include<queue>
using namespace std;

//inner class of binary tree
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



//Main class of binary tree
template<typename T1, typename T2 = typename T1::value_type>
class BinaryTree{
    public:
        //constructors...
        BinaryTree(const T1& unknownObject, int N):givenObject(unknownObject), rank_(N), No_Of_Nodes(0),rankExists(true){
           initialise();   
        }
        BinaryTree(const T1 &unknownObject):givenObject(unknownObject), No_Of_Nodes(0), rankExists(false){
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
        void addNode(const T2 &a); // adding node at the specific position
        void addNode(const T1& unknownObject, int rank);// inserting the given object at 
                                                           //specified position for given rank     

        template<typename T>
        bool deleteNode(const T& obj);//

        void BalanceTree();//time complexity = O(n) and Space = O(n)(n = pointers to inner class)
        int NoOfNodes(); // returns the no of nodes
        int No_Of_Level(); //get total no of levels TODO
        int get_level_No();//   TODO
        // ==, !=, =, ++(pre and post)
        // check with allocator
        // level, swap, 
        using value_type = T2;
        using pointer = T2*;
        using const_reference = const T2&;
        using reference = T2&;

        //operator overloading ...
        BinaryTree<T1, T2>& operator =(const BinaryTree<T1, T2>& rhs); // copy operator (=)
        BinaryTree<T1, T2>& operator =(BinaryTree<T1, T2>&& rhs); // move() 
        bool operator==(const BinaryTree<T1, T2>& rhs); // equality operator
        bool operator!=(const BinaryTree<T1, T2>& rhs); // inequality operator
        
        
        //variables
        bool rankExists;
        int rank_; 
    private:
        void storeNode(TreeStruct<T2>* St, vector<TreeStruct<T2>*> &v1);// store all the nodes
        TreeStruct<T2>* BuildBalancedTree(vector<TreeStruct<T2>*> &v1, int start, int end);// for building balance tree
        void AssignTop(TreeStruct<T2>* child, TreeStruct<T2>* parent);
        void deleteAll(TreeStruct<T2>*); // called by dtor at the end 
        void initialise();//Initialise the Start pointer for separate allocation
        
        //variables
        const T1& givenObject;
        int No_Of_Nodes;   
        TreeStruct<T2> *Start = nullptr;

};

//all the function definition
template<typename T1, typename T2>
void BinaryTree<T1, T2>::createTree(){
    bool ST = true;
    //using innerType = typename T1::value_type;
    for(auto it = begin(givenObject); it!=end(givenObject);++it){
        ++No_Of_Nodes;
        if(ST){
            ST = false;
            TreeStruct<T2> *Obj = new TreeStruct<T2>(*it);
            Obj->left = Obj->right = Obj->up = nullptr;
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
        prev->right->up = prev;
    }
    else {
        prev->left = new TreeStruct<innerType>(a);
        prev->left->up = prev;
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
    ++No_Of_Nodes;
    TreeStruct<T2> *Obj = new TreeStruct<T2>(givenObject, rank_);
        Obj->left = Obj->right = Obj->up = nullptr;
        Start = Obj;
}


template<typename T1, typename T2>
void BinaryTree<T1, T2>::addNode(const T1 &a, int rank){    
    using innerType = T2;
    ++No_Of_Nodes;
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
        prev->right->up = prev; 
    }
    else {
        prev->left = new TreeStruct<innerType>(a, rank);
        prev->left->up= prev;
    }
}

template<typename T1, typename T2>
void BinaryTree<T1, T2>::BalanceTree(){
    vector<TreeStruct<T2>*> v;
    storeNode(Start, v);
    Start = BuildBalancedTree(v, 0, v.size()-1);
    AssignTop(Start,nullptr);
}

template<typename T1, typename T2>
void BinaryTree<T1, T2>::storeNode(TreeStruct<T2>* root, std::vector<TreeStruct<T2>*> &v){
    if(root){
        storeNode(root->left, v);
        v.push_back(root);
        storeNode(root->right, v);
    }
}
template<typename T1, typename T2>
void BinaryTree<T1, T2>::AssignTop(TreeStruct<T2>* child, TreeStruct<T2>* parent){
    if(child){
        child->up = parent;
        AssignTop(child->left, child); AssignTop(child->right, child);
    }
}


template<typename T1, typename T2>
TreeStruct<T2>* BinaryTree<T1, T2>::BuildBalancedTree(std::vector<TreeStruct<T2>*> &v, int start, int end){
    if(start<=end){
        int mid = (start+end)/2;
       
        v[mid]->left = BuildBalancedTree(v, start, mid - 1);
        v[mid]->right = BuildBalancedTree(v, mid+1, end); 
        return v[mid];
    }
    return nullptr;
}

template<typename T1, typename T2>
int BinaryTree<T1, T2>::NoOfNodes(){
    return No_Of_Nodes;
}

// template<typename T1, typename T2>
// BinaryTree<T1, T2>& BinaryTree<T1, T2>::operator =(const BinaryTree<T1, T2>& rhs){
//     if(rhs.rankExists){
//         BinaryTree<T1, T2> temp = BinaryTree<T1, T2>(rhs)
//     }
// }

template<typename T1, typename T>
template<typename T2>
bool BinaryTree<T1, T>::deleteNode(const T2& node){
    TreeStruct<T2>* temp;
    if(node == (Start->data_)){//check for root node
        if(Start->left == nullptr && Start->right == nullptr){
            delete Start;
            Start = nullptr;
            return true; 
        }
        else if(Start ->left == nullptr){
            temp = Start->right;
            Start->right->up =nullptr; 
            Start->right = nullptr;
            delete Start;
            Start = temp; return true;
        }
        else if(Start->right == nullptr){
            temp = Start->left;
            Start->left->up=nullptr;
            Start->left = nullptr;
            delete Start;
            Start = temp;return true;
        }
        else{
            temp = Start->right;
            if(temp->left == nullptr) {
                temp->left = Start->left;
                Start->left = Start->right = nullptr;
                delete Start; Start = temp;
                return true;
            }
            while(temp->left) temp = temp->left;
            temp->up->left = temp->right;

            temp->left = Start->left;
            temp->right = Start->right;
            return true;
        }
    }
    queue<TreeStruct<T2>*> que;
    que.push(Start);
    
    TreeStruct<T2>* rt;
    while(!que.empty()){
        temp = que.front();
        if(temp->data_ == node){
            
            if(temp->left ==nullptr && temp->right == nullptr){
                if(temp->up->left && temp->up->left->data_ == node) temp->up->left = nullptr;
                else temp->up->right = nullptr;
                delete temp;
                return true;
            }
            
            else if(temp->left == nullptr  ){
                if(temp->up->left && temp->up->left->data_ == node){
                    temp->up->left = temp->right;
                }
                else{
                    temp->up->right = temp->right;
                }
            }
            else if(temp->right == nullptr){
                if(temp->up->left && temp->up->left->data_ == node){
                    temp->up->left = temp->left;
                }
                else{
                    temp->up->right = temp->left;
                }
            }//both end is present
            else{
                rt = temp->right;
                while(rt->left) rt = rt->left;
                rt->up->left = rt->right;
                rt->up = temp->up;
                if(temp->up->left && temp->up->left->data_ == node){
                    temp->up->left = rt;
                }
                else temp->up->right = rt;
                rt->left = temp->left;
                rt->right = temp->right;
            }
            delete temp;
            return true;
        }
        que.pop();
        if(temp->left) que.push(temp->left);
        if(temp->right) que.push(temp->right);
    }
    cout<<"given node is not present in the Tree\n";
    return false;
}

template<typename T>
bool TreeStruct<T>::operator==(const TreeStruct<T>& rhs){
    return rhs.data_ == data_;
}
template<typename T>
bool TreeStruct<T>::operator!=(const TreeStruct<T>& rhs){
    return !(rhs.data_ == data_);
}