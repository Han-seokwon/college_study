//============================================================================
// Name        : 문자열에있는세그먼트수_C++5주차과제.cpp
// Description : C++ 프로그래밍 5주차 과제 문제 A: 문자열에있는세그먼트수
// 문제 출처: judge.koreatech.ac.kr
//============================================================================

#include <iostream>
#include <string>
#include <limits>

int countSegment_String(const std::string& str1){
	int segmentCnt{0};
	bool isBlankBefore{true}; // 이전에 공백이 나왔는지 여부(처음부터 문자가 나온 경우를 대비해 true로 초기화)

	for(auto i=str1.cbegin(); i!=str1.cend(); ++i){

		if(*i==' '){ // 공백인 경우
			isBlankBefore = true;
		}

		else{ // 문자인 경우
			if(isBlankBefore){ // 이전에 공백이 나왔던 경우만 count함
				++segmentCnt;
				isBlankBefore = false;
			}
		}
	}
	return segmentCnt;
}

int main() {
	int testcase{0};

	// 테스트 케이스 입력
	std::cin >> testcase;
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	for(int i{0}; i<testcase; i++){// 테스트 케이스만큼 반복합니다.
		std::string str1;

		std::getline(std::cin, str1); // 문자열 입력과정

		std::cout << countSegment_String(str1) << '\n'; // 함수 실행 및 세그먼트 수 출력

	}
	return 0;
}
