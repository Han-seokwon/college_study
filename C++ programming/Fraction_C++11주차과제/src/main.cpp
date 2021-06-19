//============================================================================
// Name        : main.cpp
// Description : 과제 8. 12장 연습문제 1 Fraction 클래스를 테스트하는 소스파일
//============================================================================

#include <iostream>
#include "Fraction.h"

int main() {
	Fraction frac1{11, 5};
	Fraction frac2{6, 5};
	Fraction frac3{4, 6};  // 4/6 == 2/3
	Fraction frac4{8, 12}; // 8/12 == 2/3

	std::cout << "[double로 타입변환]" << "\n";
	std::cout << "static_cast<double>(frac1) = "<< static_cast<double>(frac1) << "\n";

	std::cout << "\n";

	std::cout << "[단항연산자 -]" << "\n";
	std::cout << "static_cast<double>(-frac1)"<< static_cast<double>(-frac1) << "\n";

	std::cout << "\n";

	std::cout << "[이항연산자 + - * / ]" << "\n";
	std::cout << "frac2 = " << static_cast<std::string>(frac2) << "\n";
	std::cout << "frac3 = " << static_cast<std::string>(frac3) << "\n";

	std::cout << "frac2 + frac3 = " << static_cast<std::string>(frac2 + frac3) << "\n";
	std::cout << "frac2 - frac3 = " << static_cast<std::string>(frac2 - frac3) << "\n";
	std::cout << "frac2 * frac3 = " << static_cast<std::string>(frac2 * frac3) << "\n";
	std::cout << "frac2 / frac3 = " << static_cast<std::string>(frac2 / frac3) << "\n";

	std::cout << "\n";

	std::cout << "[비교연산자]" << "\n";
	std::cout << "frac2 > frac3 : " << (frac2 > frac3) << "\n";
	std::cout << "frac2 < frac3 : " << (frac2 < frac3) << "\n";
	std::cout << "frac2 >= frac3 : " << (frac2 >= frac3) << "\n";
	std::cout << "frac2 <= frac3 : " << (frac2 <= frac3) << "\n";
	std::cout << "frac2 == frac3 : " << (frac2 == frac3) << "\n";
	std::cout << "frac2 != frac3 : " << (frac2 != frac3) << "\n";

	std::cout << "\n";

	// 값이 같은 것끼리 비교
	std::cout << "frac3 = " << static_cast<std::string>(frac3) << "\n";
	std::cout << "frac4 = " << static_cast<std::string>(frac4) << "\n";

	std::cout << "frac4 == frac3 : " << (frac4 == frac3) << "\n";
	std::cout << "frac4 >= frac3 : " << (frac4 >= frac3) << "\n";
	std::cout << "frac4 <= frac3 : " << (frac4 <= frac3) << "\n";

	return 0;
}
