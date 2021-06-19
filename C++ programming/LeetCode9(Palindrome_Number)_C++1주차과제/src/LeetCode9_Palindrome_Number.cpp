//============================================================================
// Name        : LeetCode9_Palindrome_Number.cpp
// Description : C++ 프로그래밍 LeetCode 9. Palindrome Number 풀이
//============================================================================

//  LeetCode 통과여부: Success

//  <<코드 성능>>
//  Runtime: 8 ms, faster than 79.15% of C++ online submissions for Palindrome Number.
//  Memory Usage: 5.9 MB, less than 58.54% of C++ online submissions for Palindrome Number.

//  <<알고리즘 설명입니다.>>
//  1. 정수 x의 자릿수를 digits에 저장(예: x = 100 일 때 digits = 3 )
//  2. x를 맨 앞과 맨 뒤에서 부터 차례로 조회(frontDigt과 rearDigt에 자릿수 저장)
//  3. 각각 앞과 뒤에서 조회한 두 개의 정수를 비교(frontNum와 rearNum에 저장)
//  4. 두 숫자가 같으면 frontDigt-1, rearDigt+1 하여 2번부터 다시 반복(digits/2만큼 반복)
//  4-1. 두 숫자가 다른 경우 false 반환 후 종료
//  5. 반복이 끝날 때까지 4-1 케이스가 나오지 않았다면 true 반환 후 종료

#include <cmath>
#include <cstdio>
#include <iostream>

bool isPalindrome(int x) {
	// 만약 x가 음수라면 false 반환 후 종료
	if(x < 0){
		return false;
	}

	int digits{0};
	int num1{x};
	int share{1};

	// 1번 과정
	while(share != 0){
		share = num1/10;
		num1 = share;
		digits++;
	}


	int frontDigt{digits};
	int rearDigt{1};
	int frontNum{0};
	int rearNum{0};

	// frontDivideNum과 rearDivideNum는 각 자릿수에 맞게 x를 나누는 식별자
	int frontDivideNum{0};
	int rearDivideNum{0};

	// frontDigt과 rearDigt이 같다면 1자리 숫자이므로 true 반환 후 종료
	if(frontDigt == rearDigt){
		return true;
	}


	else{
		// 2번 과정
		for(int i{0}; i<digits/2; i++){


			frontDivideNum= (int)pow(10.0,((double)frontDigt - 1.0));
			rearDivideNum = (int)pow(10.0,(double)rearDigt);

			// 4번 과정
			// x/10^(frontDigt-1)을 통해 frontDigt자리를 포함하여 앞의 정수들을 구하고 %10을 하여 frontDigt에 해당하는 자릿수의 정수만 가져옴
			frontNum = (x / frontDivideNum)%10;
			// x%10^(rearDigt)을 통해 rearDigt자리를 포함하여 뒤의 정수들을 구하고 10^(rearDigt)로 나눠주어 rearDigt에 해당하는 자릿수의 정수만 가져옴
			rearNum = (x % rearDivideNum) / (rearDivideNum/10);

			// 4-1번 과정
			if(frontNum != rearNum){
				return false;
			}
			frontDigt--;
			rearDigt++;

		}
		return true;
	}

};


// main 함수에서는 x를 입력받고, 입력받은 x를 인자로 전달해 isPalindrome 실행
int main(){
	int x{0};
	std::cout << "x를 입력: ";
	std::cin >> x;
	if(isPalindrome(x)){
		std::cout << "true\n";
	}
	else{
		std::cout << "false\n";
	}
	std::cout << sizeof(long) << std::endl;
	return 0;
}
