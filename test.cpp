#include<iostream>
#include<vector>
using namespace std;
template<typename T>
class my{
    public:
    // my(const T (&arr)[N]){
    //     cout<<"array type\n";
    // }
    my(const T& a):y(a){
        
        if(is_array<T>::value){
            cout<<"Its array!\n";
           
            cout<<*(y+1)<<endl;
        }
        else{
            cout<<"Not an array\n";
        }
    }
    const T& y;

};


template<typename T>
class one{
    public:
        one(const T& a):b(a){}
        const T& b;
};

int main(){
    int arr[]={1,2,3,4};
    vector<int> v{1,2,3};
     my<decltype(arr)> m(arr);
    one<decltype(arr)> a(arr);

}