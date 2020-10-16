//
//  main.cpp
//  실습2
//
//  Created by 유정무 on 2020/10/16.
//

#include <iostream>
bool funcA() {
    int c;
    std::cout << "input(number) : ";
    std::cin >> c;
    if (c < 10){ //Let's assume this is exception
        throw std::out_of_range("Invalid Input!!\n");
        return false;
    }
    return true;
}
int main() {
    try{
        funcA();
    }
    catch(std::exception& e){
        std::cout << "Exception : " << e.what();
    }
    return 0;
}
