#include<iostream>
#include<string>
using namespace std;

template<typename T>
class TreeStruct{
    public:
        TreeStruct(const T &a){}
};

template<typename T1, typename T2 = typename T1::value_type>
class A{
    public:

        //constructors...
        // A(const A<T1, T2> &rhs){}
 
        A(const T1 &unknownObject):givenObject(&unknownObject), No_Of_Nodes(0){//entire collection is passed
            createTree();
        }

        ~A(){
            //Start1 = nullptr;
        }
       // A<T1, T2> operator =(const A<T1, T2> rhs);
        void createTree();

    private:
        //variables
        const T1* givenObject;
        bool inner;
        int No_Of_Nodes; 
        TreeStruct<T2> *Start1 = nullptr;  
};

// template<typename T1, typename T2>
// A<T1, T2> A<T1, T2>::operator =(const A<T1, T2> rhs){    
//     return *this;
// }


template<typename T1, typename T2>
void A<T1, T2>::createTree(){
    bool ST = true;
    for(auto it = begin(*givenObject); it!=end(*givenObject);++it){
        ++No_Of_Nodes;
        if(ST){
            ST = false;
            TreeStruct<T2> *Obj = new TreeStruct<T2>(*it);
            
            Start1 = Obj;
        }
        else{
            //
            
        }
    }
}

int main(){
    string s1="abcd";
    string s2="xyz";
    A<decltype(s1)> b1(s1);
    A<decltype(s2)> b2(s2);
    b1 = b2;
}