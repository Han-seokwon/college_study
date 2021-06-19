//============================================================================
// Name        : 못생긴수_C++5주차과제.cpp
// Description : C++ 프로그래밍 5주차 과제 문제 B: 못생긴수
// 문제 출처: judge.koreatech.ac.kr
//============================================================================

#include <iostream>
using namespace std;


bool isUglyNumber(int num1){
    if(num1==1){ // 1인 경우는 못생긴 수
        return true;
    }
    else if(num1<=0){ // 0이하이면 못생긴 수가 아님
        return false;
    }

    while(num1!=1){

        if(!(num1&0x01)){ // num1가 2로 나누어 떨어지는 경우(비트연산자와 논리곱을 이용)
            num1 >>= 1; // 비트연산자로 나누기 2
        }
        else if(!(num1%3)){ // num1가 3으로 나누어 떨어지는 경우
            num1 /= 3;
        }
        else if(!(num1%5)){ // num1가 5로 나누어 떨어지는 경우
            num1 /= 5;
        }

        else{ // 2, 3, 5 이외에 나누어지는 수가 있으면 못생긴 수가 아님
            return false;
        }
    }

    return true; // num1의 소인수가 2,3,5 중에서 밖에 없으므로 못 생긴 수
}



int main() {

    int testcase{0};

    // 테스트 케이스 입력
    std::cin >> testcase;

    for(int i{0}; i<testcase; i++){// 테스트 케이스만큼 반복합니다.

        // 입력과정
        int num1;
        std::cin >> num1;
        isUglyNumber(num1);
        // 함수 실행 및 출력
        isUglyNumber(num1)? std::cout<<"true" : std::cout<<"false";
        std::cout << '\n';

    }

    return 0;
}
