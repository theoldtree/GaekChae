//
//  main.cpp
//  실습1
//
//  Created by 유정무 on 2020/10/16.
//

#include <iostream>
#include <stdexcept>
class Test {
    public:
        Test(char id) : id_(id) {}
        ~Test() {
            std::cout << "Destructor execution: "<< id_ << std::endl;
        }
    private:
        char id_;
};

int funcB() {
    Test r('B');
    throw std::runtime_error("Exception from funcB!\n");
    std::cout << "Executed in B" << std::endl;
    return 0;
}

int funcA() {
    Test r('A');
    funcB();
    std::cout << "Executed in A" << std::endl; return 0;
}

int main() {
    try {
        funcA();
    }
    catch (std::exception& e) {
        std::cout << "Exception : " << e.what();
    }
}

/* (실습 1-1) 분석결과 :
 
실행결과 :
 Destructor execution: B
 Executed. in A
 Destructor execution: A
 Program ended with exit code: 0
 
분석 : main -> funcA -> fumcB -> funcB종료 -> funcA 종료 -> main 종료
 main 함수의 try에서 funcA()가 실행되고
 funcA() 에서 A id를 가진 r 객체를 생성후 funcB를 실행한다
 funcB() 에서 B id를 가진 r 객체를 생성하고 funcB는 종료된다.
 funcB가 종료됨에 따라 B id 객체가 사라지고 파괴자를 실행된다. 실행결과는 첫번째 줄과 같다.
 다음으로 funcA로 다시 돌아와 funcA의 출력문을 화면에 나타낸뒤 함수가 종료되는데, 위와 같은원리로 파괴자가 실행된다.
 그결과는 2~3번째 줄과 같고 main 함수로 돌아와 예외가 발생하지 않았으므로 그대로 함수가 종료 된다.

 */


/* (실습 1-2) 분석결과 :

실행결과 :
 Destructor execution: B
 Destructor execution: A
 Exception : Exception from funcB!
 
분석 : main -> funcA -> fumcB -> funcB종료 -> funcA 종료 -> main 종료
 main 함수의 try에서 funcA()가 실행되고
 funcA() 에서 A id를 가진 r 객체를 생성후 funcB를 실행한다
 funcB() 에서 B id를 가진 r 객체를 생성하고 에러메세지와 함계 runtime_err을 발생시킨다.
 따라서 에러 이후에 있는 코드는 실행되지 않고 종료되고 funcB 와 funcA가 차례대로 종료된다.
 그에따른 실행결과는 1~2번째 줄과 같으며 마지막으로 main함수 내에서 오류가 발생했으므로
 catch문에서 오류를 잡고 에러메세지를 출력해준다.

*/
