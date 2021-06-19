//============================================================================
// Name        : 특정요소제거하기_C++3주차과제.cpp
// Description : C++ 프로그래밍 3주차 과제 문제A: 특정 요소 제거하기
// 문제 출처: judge.koreatech.ac.kr
//============================================================================


#include <iostream>
#include <string>

int removeNumInArray(int *numArr, int size, int removeNum){
	int arrayLenth{0}; // in-place 이후 배열의 크기를 구하는 변수입니다.
	int j{0};

	for(int i{0}; i< size; i++){
		// 배열을 순회하며 제거할 값이랑 다른 경우만 기존의 배열에 값을 저장해줍니다.
		if(numArr[i] != removeNum){
			numArr[j] = numArr[i];
			++j;
			++arrayLenth; // 제거할 값을 제외한 배열의 크기를 증가시킵니다.
		}
	}

	return arrayLenth;

}


int main() {
	int testcase{0}, removeNum{0},numCnt{0};
	int temp{0};

	// 테스트 케이스 입력
	std::cin >> testcase;

	for(int i{0}; i<testcase; i++){// 테스트 케이스만큼 반복합니다.

		// 입력과정
		std::cin >> removeNum >> numCnt;

		int *numArr{new int[numCnt]}; // 정수 개수에 맞게 배열을 할당합니다.

		for(int j{0}; j<numCnt; j++){ // 입력된 정수들을 numArr에 저장합니다.
			std::cin >> temp;
			numArr[j] = temp;
		}

		// 함수 실행
		numCnt = removeNumInArray(numArr, numCnt, removeNum);

		// 출력과정
		std::cout << numCnt << '\n';
		for(int k{0}; k<numCnt; k++){
			std::cout << numArr[k] << ' ';
		}
		std::cout << '\n';

		delete [] numArr; // 할당한 메모리를 해제합니다.
	}



	return 0;
}

