//============================================================================
// Name        : 문자열을정수로바꾸기_C++3주차과제.cpp
// Description : C++ 프로그래밍 3주차 과제 문제B: 이동 평균 구하기
// 문제 출처: judge.koreatech.ac.kr
//============================================================================

#include <iostream>
#include <string>
#include <limits>
#include <climits>

int changeStringToInt(std::string& word){

    int number1{0};
    int digit{0};
    bool isNegative{false}; // - 부호가 나왔는지 여부를 확인하는 변수입니다.
    bool isNum{false}; // 숫자가 나왔는지 여부를 확인하는 변수입니다.

    for(int i{0}; i<word.size(); i++){
        if('0' <= word[i] && word[i] <= '9'){

            digit = static_cast<int>(word[i] - '0');

            if(number1 > (INT_MAX - digit)/10){ // number1*10 + digit이 INT_MAX 를 넘어가면 음수일 경우 INT_MIN을 양수일 경우 INT_MAX를 반환합니다.
                if(isNegative){
                    return INT_MIN;
                }
                return INT_MAX;
            }

            number1 = number1*10 + digit;

            isNum = true;
        }

        else{ // 숫자 이외의 입력이 들어온 경우

            if(isNum) break; // 숫자 뒤로 숫자가 아닌값(부호, 문자 등)이 오면 반복문을 나가 저장한 정수까지만 반환합니다.

            else{ // 숫자보다 문자들이 먼저온 경우

                if(i!=0 && (word[i-1]=='-' || word[i-1]=='+')) return 0; // 바로 이전에 부호가 있는데, 문자가 온 경우는 정수변환이 불가능하므로 0을 반환합니다.


                if(word[i] == '-') isNegative=true ;

                else if(word[i] == '.') break; // 소수점이 입력된 경우도 반복문을 나갑니다.

                // -, +, . 이 아니고 공백문자도 아니므로 영문자입니다.
                else if(word[i] != ' ' && word[i] != '+' && !isNum) return 0; // 영문자가 숫자보다 먼저 입력된 경우도 정수변환이 불가능하므로 0을 반환합니다.

            }

        }
    }
    return isNegative? -number1 : number1;

}



int main() {

    int testcase{0};

    // 테스트 케이스 입력
    std::cin >> testcase;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    for(int i{0}; i<testcase; i++){// 테스트 케이스만큼 반복합니다.

        // 입력과정
        std::string str1;
        std::getline(std::cin, str1);

        // 함수 실행 및 출력
        std::cout << changeStringToInt(str1) << std::endl;
    }

    return 0;
}
