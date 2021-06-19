//============================================================================
// Name        : main.cpp
// Description : Wallet 클래스 실행, 테스트 파일
//============================================================================


#include <iostream>
#include "Wallet.h"

int main() {
	Wallet wallet;

	wallet.add(100,2);
	std::cout << wallet.getCurrentAmount() << '\n';

	wallet.add(500,4);
	std::cout << wallet.getCurrentAmount() << '\n';

	wallet.add(1000,5);
	std::cout << wallet.getCurrentAmount() << '\n';

	wallet.spend(1700);
	std::cout << wallet.getCurrentAmount() << '\n';

	wallet.clear();
	std::cout << wallet.getCurrentAmount() << '\n';



	//	wallet.add(2500,2); // 잘못된 액면가로 add 시도

	//	wallet.add(1000,-2); // 잘못된 화폐 개수로 add 시도

	//	for(int i{0}; i<100000; ++i){
	//		wallet.add(50000, 100'000'000); // 최대 수용 금액을 초과해서 add 시도
	//	}

	//	wallet.spend(-1000); // 음수 금액을 spend 시도

	//	wallet.spend(10000000); // 잔액을 초과해서 spend 시도



	return 0;
}





