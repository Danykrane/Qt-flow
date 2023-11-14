// pointer on func

#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

// functions
bool decr(int a, int b){
    return a > b;
}

bool incr(int a, int b){
    return a < b;
}


vector<int> sortVec(vector<int> vec, bool (*func)(int a, int b)){
    sort(vec.begin(), vec.end(), func);
    return vec;
}

// // class
// class CalcPredicates{
    
//     public:
// bool decrCalc(int a, int b){
//     return a > b;
//     }

// bool incrCalc(int a, int b){
//     return a < b;
//     }
// };

// vector<int> sortVec(vector<int> vec, bool (CalcPredicates::*func)(int a, int b)){
//     sort(vec.begin(), vec.end(), func);
//     return vec;
// }



void showAll(const std::vector<int>&vec){
    for(const int&elem: vec){
        cout << elem << " ";
    }
    cout<<std::endl;
}

template <class T>
ostream &operator<<(ostream &out, const std::vector<T> &vec){
    for(const int&elem: vec){
        out << elem << " ";
    }
    return out;
}

int main()
{
    vector<int> vec = {31, 1, 5, -33, -4, 23, 0};
    
    
    // functions
    cout << (sortVec(vec, incr))<<endl;
    cout << (sortVec(vec, decr))<<endl;
    
    // // functions in class
    // CalcPredicates predicat;
    // cout << (sortVec(vec, predicat.incrCalc))<<endl;
    // cout << (sortVec(vec, predicat.decrCalc))<<endl;

    return 0;
}
