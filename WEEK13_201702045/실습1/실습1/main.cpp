//
//  main.cpp
//  실습1
//
//  Created by 유정무 on 2020/11/29.
//

#include <iostream>

template <typename T, int num = 2>
T add_num(T t){
    return t + num;
}

int main(int argc, const char * argv[]) {
    int x=3;
    std::cout << "x: " << add_num(x) << std::endl;
}
