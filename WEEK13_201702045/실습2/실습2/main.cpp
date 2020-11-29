//
//  main.cpp
//  실습2
//
//  Created by 유정무 on 2020/11/29.
//

#include <iostream>
#include <string>

template <typename T>
auto sum(T x){
    return x;
}

template<typename T, typename... Args>
auto sum(T x, Args...args){
    return x + sum(args...);
}

int main(int argc, const char * argv[]) {
    auto x = sum(42.5, 10, 11.1f);
    std::cout << x;
    getchar();
}
