//============================================================================
// Name        : Leet342(Power_of_Four).cpp
// Description : C++ 프로그래밍 2주차과제 중 LeetCode 342. Power of Four 풀이
//============================================================================

//  LeetCode 통과여부: Success

//  <<코드 성능>>
//  Runtime: 0 ms, faster than 100.00% of C++ online submissions for Power of Four.
//  Memory Usage: 5.9 MB, less than 80.83% of C++ online submissions for Power of Four.

//  << 문제해결 접근법입니다. >>
//  2진수 비트중 홀수번째 자릿수 비트들은 4의 거듭제곱에 해당합니다.
//  따라서 짝수번째 자릿수 비트들은 모두 값이 0이고 홀수번째 자릿수 비트중 값이 1인 것이 하나만 있는 경우
//  해당 숫자는 4의 거듭제곱에 해당합니다. (예: 0b0100 = 4, 0b010000 = 16)

//  << 알고리즘 설명입니다. >>

//  첫째 자리 비트를 기준으로 비트를 하나씩 비교할 것이기 때문에 >> 연산자로 비트를 한칸씩 왼쪽으로 이동시키며 비교를 마친 비트를 제거해줍니다.
//  항상 비교하는 것은 첫번째 자리의 비트이므로 현재 비트가 몇번째 비트인지 기억하기 위해 digitCnt변수에 자릿수를 저장합니다.

//  (n&0x01)은 첫째 자리 비트는 n의 첫째자리 비트는 유지하고, 나머지 비트를 모두 0으로 바꿉니다.
//   따라서 (n&0x01)= 1이면 n의 첫째 자리 비트는 1입니다.

//   위와 비슷한 방식으로 자릿수의 홀수, 짝수 여부를 구할 수 있습니다.
//   (digitCnt&0x01) = 1이면 현재 자릿수가 홀수번째 자리이고, (digitCnt&0x01) = 0이면 짝수번째 자리입니다.

//  홀수번째 자릿수에서 1이 나오면 oneShowed변수를 true로 바꾸어주어 1이 나왔다는 사실을 기억합니다.
//  만약 oneShowed = true인데 홀수번째 자릿수에서 1이 또 나오면 4의 거듭제곱이 될 수 없으므로 false를 반환합니다.

//  짝수번째 자릿수에서 1이 나오면 false를 반환합니다.


#include <iostream>

bool isPowerOfFour(int n){
	if(n <= 0){ // 만약 n이 0보다 작거나 같으면 4의 거듭제곱이 될 수 없습니다.
		return false;
	}

	bool oneShowed{false};
	int digitCnt{1};

	while(n != 0){
		if(((digitCnt&0x01) == 1) && ((n&0x01) == 1)){
			if(oneShowed){
				return false;
			}
			oneShowed = true;
		}
		else if(((digitCnt&0x01) == 0) && ((n&0x01) == 1)){
			return false;
		}
		n = n >> 1;
		++digitCnt;
	}
	return true;
}

int main(){
	int n{0};
	std::cout << "n = ";
	std::cin >> n;
	std::cout << isPowerOfFour(n)<< std::endl;
	return 0;
}




