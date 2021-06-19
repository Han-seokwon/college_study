//============================================================================
// Name        : Leet397(Integer_Replacement).cpp
// Description : C++ 프로그래밍 2주차과제 중 LeetCode 397. Integer Replacement 풀이
//============================================================================

//  LeetCode 통과여부: Success

//  Runtime: 4 ms, faster than 48.44% of C++ online submissions for Integer Replacement.
//  Memory Usage: 6.9 MB, less than 25.07% of C++ online submissions for Integer Replacement.


//  << 문제해결 접근법입니다. >>

//  입력되는 값의 범위가 1 <= n <= 2^31 - 1 이므로, 2^31 - 1이 입력되었을 때 n+1 연산을 수행하면 오버플로우가 발생합니다.
//  따라서 queue의 자료형을 unsigned int로 설정하였습니다.


//  << 알고리즘 설명입니다. >>

//  반복문을 통해 n/2 또는 n+1, n-1 연산을 진행하며 연산 결과들을 queue에 저장합니다.
//  연산결과가 1이 될 때가지 반복합니다.

//  queue의 앞에 있는 요소를 꺼내 홀수, 짝수 여부를 판별하고 그에 맞는 연산을 진행합니다.
//  queue의 앞 부분의 위치를 queueFront, 큐의 뒷 부분의 위치를 queueEnd에 저장하며 반복이 끝날 때마다 queueFront+1 합니다.

//  n이 홀수일 때는 n/2이므로 연산결과가 1개 증가하여 queueEnd+1하고,
//  n이 짝수일 때는 n+1, n-1이므로 연산결과가 2개 증가하므로 queueEnd+2를 합니다.

//  queue는 연산결과와 연산횟수를 저장하기 위해 2차원 배열로 만들어 queue[k][0]: 연산결과, queue[k][1]: 연산횟수를 저장합니다.



#include <iostream>
#include <climits>
#include <cstdlib>
const int MAXQUEUE{150000}; // queue의 크기는 연산결과들을 모두 담을 수 있도록 적당히 크게 설정하였습니다.

int integerReplacement(int n){

	unsigned int queue[MAXQUEUE][2]; // [k][0]: 연산결과, [k][1]: 연산횟수
	unsigned int queueFront{0};
	unsigned int queueEnd{1};

	unsigned int popedNum{0}; // queue의 앞에 있는 요소의 연산결과를 저장하는 변수

	unsigned int operationCnt{0}; // 연산횟수를 저장하는 변수

	queue[0][0] = n;
	queue[0][1] = 0;

	while(1){

		popedNum = queue[queueFront][0];
		operationCnt = queue[queueFront][1];

		if(popedNum == 1){
			return operationCnt;
		}


		if((popedNum&0x01)){// 홀수가 입력된 경우
			queue[queueEnd][0] = popedNum + 1;
			queue[queueEnd][1] = operationCnt + 1;


			queue[queueEnd + 1][0] = popedNum - 1;
			queue[queueEnd + 1][1] = operationCnt + 1;

			queueEnd += 2;
		}

		else{// 짝수가 입력된 경우
			queue[queueEnd][0] = popedNum/2;
			queue[queueEnd][1] = operationCnt + 1;

			queueEnd += 1;
		}

		++queueFront;
	}
}

int main(){
	int n{0};
	std::cout << "n = ";
	std::cin >> n;
	std::cout << integerReplacement(n) << std::endl;
	return 0;
}

