#include<iostream>
#include<utility>
#include<vector>
#include<list>
#include<queue>
#include<typeinfo>
using namespace std;

//inner class of binary tree
template<typename T>
class TreeStruct{    
    TreeStruct(const T &obj, int r = -1):data_(obj), rank_(r){}
    int rank_;
    TreeStruct *left, *right, *up;
    T data_;

    bool operator<(const TreeStruct<T>& rhs);
    bool operator!=(const TreeStruct<T>& rhs);
    bool operator==(const TreeStruct<T>& rhs);
    
    template<class T1, class T2>
    friend class BinaryTree;
};



//Main class of binary tree
template<typename T1, typename T2 = typename T1::value_type>
class BinaryTree{
    public:

        //constructors...
        //copy and move constructor
        BinaryTree(const BinaryTree<T1, T2> &rhs);
        BinaryTree(BinaryTree<T1, T2> &&rhs); 
        //dealing with ranks
        BinaryTree(const T1 &unknownobject, int* rank)
        :givenObject(&unknownobject), setFlag(false),No_Of_Nodes(0), rank_(rank){
            createTree();
        } 

        BinaryTree():No_Of_Nodes(0){} // for empty variable 

        BinaryTree(const T1&unknownObject, bool SetFlag):givenObject(&unknownObject), setFlag(SetFlag),No_Of_Nodes(0),rank_(nullptr){
            initialise();//for creating a node for given object 
        }

        BinaryTree(const T1 &unknownObject):givenObject(&unknownObject), No_Of_Nodes(0),setFlag(false), rank_(nullptr){//entire collection is passed
            createTree(); //create a tree for a collection
        }

        ~BinaryTree(){
            deleteAll(Start1);
            Start1 = nullptr;
        }
        //function declarations
        void display();// to display the tree 
        
        template<typename T>
        void addNode(const T &a, int rank = -1); // adding node at the specific position

        template<typename T>
        bool deleteNode(const T& obj);//

        void BalanceTree();//time complexity = O(n) and Space = O(n)(n = pointers to inner class)
        int NoOfNodes(); // returns the no of nodes
        int No_Of_Level(); //get total no of levels TODO
        bool findNode(const T2& obj, int rank = -1);

        using value_type = T2;
        using pointer = T2*;
        using const_reference = const T2&;
        using reference = T2&;

        //operator overloading ...
        void operator =(const BinaryTree<T1, T2>& rhs); // copy operator (=)
        void operator =(BinaryTree<T1, T2>&& rhs); // move() 
        bool operator==(const BinaryTree<T1, T2>& rhs); // equality operator
        bool operator!=(const BinaryTree<T1, T2>& rhs); // inequality operator
        
        
        //variables
        int *rank_; 
        bool setFlag;

    private:
        void display(TreeStruct<T2> *start); // to display the tree
        void createTree(); // Creating tree if collection is given
        void storeNode(TreeStruct<T2>* St, vector<TreeStruct<T2>*> &v1);// store all the nodes
        TreeStruct<T2>* BuildBalancedTree(vector<TreeStruct<T2>*> &v1, int start, int end);// for building balance tree
        void AssignTop(TreeStruct<T2>* child, TreeStruct<T2>* parent);
        void deleteAll(TreeStruct<T2>*); // called by dtor at the end 
        void initialise();//Initialise the Start1 pointer for separate allocation
        bool cmp(TreeStruct<T2> &a, TreeStruct<T2>&b);
        void AssignNodes(TreeStruct<T2> *a, const TreeStruct<T2>* b);//used for copy operator
        bool cmpNodes(TreeStruct<T2> *a, const TreeStruct<T2>* b);
        bool SearchNode(TreeStruct<T2> ref, TreeStruct<T2>* st);
        //variables
        const T1* givenObject;
        int No_Of_Nodes;   
        TreeStruct<T2> *Start1 = nullptr;
};

//all the function definition
template<typename T1, typename T2>
void BinaryTree<T1, T2>::createTree(){
    bool ST = true;
    for(auto it = begin(*givenObject); it!=end(*givenObject);++it){
        if(ST){
            ++No_Of_Nodes;
             ST = false;
            int R = -1;
            if(rank_ != nullptr) R = *(rank_);
            TreeStruct<T2> *Obj = new TreeStruct<T2>(*it, R);
            Obj->left = Obj->right = Obj->up = nullptr;
            Start1 = Obj;
        }
        else{
            if(rank_ == nullptr)
                addNode(*it);
            else addNode(*it, *(rank_+No_Of_Nodes));
        }
    }
}

template<typename T1, typename T2>
template<typename T>
void BinaryTree<T1, T2>::addNode(const T &a, int rank){    //passed a collection first
    if((Start1 ->rank_ == -1 && rank != -1 )||(Start1->rank_ !=-1 && rank == -1)){
        cout<<"Warning : Ambiguous with rank\n";return;
    }
    using innerType = T;
    ++No_Of_Nodes;
    TreeStruct<innerType> *Node = new TreeStruct<innerType>(a, rank);

    TreeStruct<innerType> *temp = Start1;
    TreeStruct<innerType> *prev = temp;

    if(temp == nullptr){//first time adding.. 
        Node->left = Node->right = Node->up = nullptr;
        Start1 = Node;
        return;
    }

    while(temp){
        prev = temp;
        if(cmp(*temp, *Node)){
            temp=temp->right;
        }
        else{
            temp = temp->left;
        }   
    }
    if(prev && cmp(*prev, *Node)){
        prev->right = Node;
        prev->right->up = prev;
    }
    else {
        prev->left = Node;
        prev->left->up = prev;
    }
    return;
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
    display(Start1);
    cout<<endl;
}

template<typename T1, typename T2>
void BinaryTree<T1, T2>::deleteAll(TreeStruct<T2>* Start1){
    if(Start1){
        deleteAll(Start1->left);
        deleteAll(Start1->right);
        delete Start1;
        Start1 = nullptr;
    }
}

template<typename T1, typename T2>
void BinaryTree<T1, T2>::initialise(){
    ++No_Of_Nodes;
    TreeStruct<T2> *Obj = new TreeStruct<T2>(*givenObject);
        Obj->left = Obj->right = Obj->up = nullptr;
        Start1 = Obj;
}


template<typename T1, typename T2>
void BinaryTree<T1, T2>::BalanceTree(){
    vector<TreeStruct<T2>*> v;
    storeNode(Start1, v);
    Start1 = BuildBalancedTree(v, 0, v.size()-1);
    AssignTop(Start1,nullptr);
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

template<typename T1, typename T>
template<typename T2>
bool BinaryTree<T1, T>::deleteNode(const T2& node){
    TreeStruct<T2>* temp;
    if(node == (Start1->data_)){//check for root node
        if(Start1->left == nullptr && Start1->right == nullptr){
            delete Start1;
            Start1 = nullptr;
            return true; 
        }
        else if(Start1 ->left == nullptr){
            temp = Start1->right;
            Start1->right->up =nullptr; 
            Start1->right = nullptr;
            delete Start1;
            Start1 = temp; return true;
        }
        else if(Start1->right == nullptr){
            temp = Start1->left;
            Start1->left->up=nullptr;
            Start1->left = nullptr;
            delete Start1;
            Start1 = temp;return true;
        }
        else{
            temp = Start1->right;
            if(temp->left == nullptr) {
                temp->left = Start1->left;
                Start1->left = Start1->right = nullptr;
                delete Start1; Start1 = temp;
                return true;
            }
            while(temp->left) temp = temp->left;
            temp->up->left = temp->right;

            temp->left = Start1->left;
            temp->right = Start1->right;
            return true;
        }
    }
    queue<TreeStruct<T2>*> que;
    que.push(Start1);
    
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
    return (rhs.data_ == data_ && rhs.rank_ == rank_);
}
template<typename T>
bool TreeStruct<T>::operator!=(const TreeStruct<T>& rhs){
    return !(rhs.data_ == data_ && rhs.rank_ == rank_);
}

template<typename T1, typename T2>
void BinaryTree<T1, T2>::operator =(const BinaryTree<T1, T2>& rhs){   
    deleteAll(Start1);
    givenObject= rhs.givenObject;
    //AssignNodes(Start1, rhs.Start1);
    if(rhs.Start1){
        Start1 = new TreeStruct<T2>(rhs.Start1->data_, rhs.Start1->rank_);
        AssignNodes(Start1, rhs.Start1);    
    }
    AssignTop(Start1, nullptr);
    No_Of_Nodes = rhs.No_Of_Nodes;
    setFlag = rhs.setFlag;
    rank_ = rhs.rank_;
}

template<typename T1, typename T2>
void BinaryTree<T1, T2>::AssignNodes(TreeStruct<T2> *cur, const TreeStruct<T2>* rhs){
    if(rhs){
        if(rhs->left){
            cur->left = new TreeStruct<T2>(rhs->left->data_, rhs->left->rank_);
            AssignNodes(cur->left, rhs->left);
        }
        else cur->left = nullptr;
        
        if(rhs->right){
            cur->right = new TreeStruct<T2>(rhs->right->data_, rhs->right->rank_);
            AssignNodes(cur->right, rhs->right);
        }
        else cur->right = nullptr;
    }
}

template<typename T1, typename T2>
bool BinaryTree<T1, T2>:: cmp(TreeStruct<T2>& a,TreeStruct<T2>& b){
    if(a.rank_ == -1 || b.rank_ == -1){
        return a.data_<b.data_;
    }
    else {
        return a.rank_<b.rank_;
    }
}
template<typename T>
bool TreeStruct<T>::operator<(const TreeStruct<T>& rhs){
    return (this->data_)<rhs.data_;
}

template<typename T1, typename T2>
void BinaryTree<T1, T2>::operator=(BinaryTree<T1,T2>&& rhs){
    deleteAll(Start1);
    givenObject= rhs.givenObject;
    //AssignNodes(Start1, rhs.Start1);
    if(rhs.Start1){
        Start1 = new TreeStruct<T2>(rhs.Start1->data_, rhs.Start1->rank_);
        AssignNodes(Start1, rhs.Start1);    
    }
    AssignTop(Start1, nullptr);
    No_Of_Nodes = rhs.No_Of_Nodes;
    setFlag = rhs.setFlag;
    rank_ = rhs.rank_;
    deleteAll(rhs.Start1);
    rhs.Start1 = nullptr;
}

template<typename T1, typename T2>
bool BinaryTree<T1,T2>::operator==(const BinaryTree<T1, T2>& rhs){
    return cmpNodes(Start1, rhs.Start1);
}

template<typename T1, typename T2>
bool BinaryTree<T1,T2>::operator!=(const BinaryTree<T1, T2>& rhs){
    return !cmpNodes(Start1, rhs.Start1);
}

template<typename T1, typename T2>
bool BinaryTree<T1, T2>::cmpNodes(TreeStruct<T2> *a, const TreeStruct<T2>* b){
    if(a && b ){
        if(*a == *b){
            return cmpNodes(a->left, b->left) && cmpNodes(a->right, b->right);
        }
        else {
            return false;
        }
    }
    else if(a || b) return false;
    return true;
}
//copy and move ctors

template<typename T1, typename T2>
BinaryTree<T1, T2>::BinaryTree(const BinaryTree<T1, T2>& rhs){
    givenObject= rhs.givenObject;
    if(rhs.Start1){
        Start1 = new TreeStruct<T2>(rhs.Start1->data_, rhs.Start1->rank_);
        AssignNodes(Start1, rhs.Start1);    
    }
    AssignTop(Start1, nullptr);
    No_Of_Nodes = rhs.No_Of_Nodes;
    setFlag = rhs.setFlag;
    rank_ = rhs.rank_;
}

template<typename T1, typename T2>
BinaryTree<T1, T2>::BinaryTree(BinaryTree<T1, T2>&& rhs){
    givenObject= rhs.givenObject;
    if(rhs.Start1){
        Start1 = new TreeStruct<T2>(rhs.Start1->data_, rhs.Start1->rank_);
        AssignNodes(Start1, rhs.Start1);    
    }
    AssignTop(Start1, nullptr);
    No_Of_Nodes = rhs.No_Of_Nodes;
    setFlag = rhs.setFlag;
    rank_ = rhs.rank_;
    deleteAll(rhs.Start1);
    rhs.Start1 = nullptr;
}

template<typename T1, typename T2>
bool BinaryTree<T1, T2>::findNode(const T2& obj, int rank){
    return SearchNode(TreeStruct<T2>(obj, rank), Start1);
}

template<typename T1, typename T2>
bool BinaryTree<T1, T2>::SearchNode(TreeStruct<T2> ref1,TreeStruct<T2>* cur){
    if(cur){
        if(*cur == ref1) return true;
        else return SearchNode(ref1, cur->left) || SearchNode(ref1, cur->right);
    }
    return false;
}