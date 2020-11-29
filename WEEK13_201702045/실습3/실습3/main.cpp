//
//  main.cpp
//  실습3
//
//  Created by 유정무 on 2020/11/29.
//

#include <iostream>
#include <algorithm>
#include <forward_list>
#include <functional>

class compLess{
    bool operator()(int x, int y){
        return x>y;
    }
};

class compGreater{
    bool operator()(int x, int y){
        return x<y;
    }
};

template <typename FowardIterator, typename Compare>
void bubble_sort(FowardIterator first, FowardIterator last, Compare comp){
    for(auto sorted = first; first != last; last = sorted){
        sorted = first;
        for(auto cur = first, prev = first; ++cur != last; ++prev){
            if(comp(*cur, *prev)){
                std::iter_swap(cur, prev);
                sorted = cur;
            }
        }
    }
}

int main() {
std::forward_list<int> values{ 7, 0, 6, 1, 5, 2, 4, 3 };
std::cout << "오름차순 정렬" << std::endl;
//compLess compLess; //Functor 생성
bubble_sort(values.begin(), values.end(), compLess);
for (auto it = values.begin(); it != values.end(); ++it) {
std::cout << ' ' << *it; }
std::cout << std::endl;
std::cout << "내림차순 정렬" << std::endl;
//compGreater compGreater; //Functor 생성
bubble_sort(values.begin(), values.end(), compGreater);
for (auto it = values.begin(); it != values.end(); ++it) {
std::cout << ' ' << *it; }
std::cout << std::endl;
getchar(); }
