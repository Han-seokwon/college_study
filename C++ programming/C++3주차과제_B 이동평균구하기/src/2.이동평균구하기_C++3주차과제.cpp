//============================================================================
// Name        : 이동평균구하기_C++3주차과제.cpp
// Description : C++ 프로그래밍 3주차 과제 문제B: 이동 평균 구하기
// 문제 출처: judge.koreatech.ac.kr
//============================================================================


#include <iostream>
#include <string>
#include <iomanip>
#include <cmath>

// 함수의 인자는 (입력 받은 정수배열, 평균을 저장할 배열, 이동 구간, 정수 개수)입니다.
void finfMovingAverage(int numArr1[], double avgArr2[], int range, int numCnt){
	int sum1{0};
	double range1{static_cast<double>(range)}; // 평균을 실수로 나타내기 위해 range를 double 타입으로 바꿔줍니다.

	for(int i{0}; i <= numCnt - range ; i++){

		if(i==0){ // 첫번째 반복에서는 이동 구간의 총합을 for문으로 구합니다.
			for(int j{0}; j<range; j++){
				sum1 += numArr1[j];
			}
		}
		else{ // 두번째 반복부터는, (이전 반목에서 구한 총합 - 이동 구간에서 제외된 값 + 이동구간에 추가된 값) 으로 총합을 구합니다.
			sum1 = sum1 - numArr1[i - 1] + numArr1[i + range -1];
		}

		// 평균을 소수점 첫째자리에서 반올림
		avgArr2[i] = std::round(sum1/range1*10)/10;
	}
}



int main() {

	int testcase{0}, range{0},numCnt{0};

	// 테스트 케이스 입력
	std::cin >> testcase;

	for(int i{0}; i<testcase; i++){// 테스트 케이스만큼 반복합니다.
		// 입력과정
		std::cin >> range >> numCnt; // 이동 구간, 정수 개수를 입력 받습니다.

		int *numArr{new int[numCnt]}; // 정수 개수에 맞게 배열을 할당합니다.
		double *avgArr{new double[numCnt + range +1]}; // 평균을 담을 배열은 (정수개수 - 이동 구간 + 1) 만큼 크기를 정합니다.

		int temp{0};
		for(int j{0}; j<numCnt; j++){ // 입력된 정수들을 numArr에 저장합니다.
			std::cin >> temp;
			numArr[j] = temp;

		}

		// 함수 실행
		finfMovingAverage(numArr, avgArr, range, numCnt);

		// 출력과정
		for(int k{0}; k<=numCnt-range; k++){
			std::cout << std::fixed << std::setprecision(1) << avgArr[k] << ' ';
		}
		std::cout << '\n';

		delete [] numArr, avgArr; // 할당된 메모리 해제
	}


	return 0;
}
