//============================================================================
// Name        : Wallet.cpp
// Description : Wallet 클래스의 메소드를 정의한 소스파일
//============================================================================

#include <iostream>
#include <climits>
#include "Wallet.h"



void Wallet::add(int denomination, int amount){

	if(amount<=0){
		throw std::invalid_argument{"음수 또는 0 개수 입력 시도"};
	}

	int idx{0};

	switch(denomination){
	case 100:
		idx = 0;
		break;

	case 500:
		idx = 1;
		break;

	case 1000:
		idx = 2;
		break;

	case 5000:
		idx = 3;
		break;

	case 10000:
		idx = 4;
		break;

	case 50000:
		idx = 5;
		break;

	default:
		throw std::invalid_argument{"유효하지 않은 액면가 입력"};
	}

	if(INT_MAX - denomination_array[idx] < getCurrentAmount()){
		throw std::overflow_error{"최대 수용 금액 초과"};
	}

	M[idx]	+= amount;

}

void Wallet::spend(int amount){

	if(amount<=0){
		throw std::invalid_argument{"음수 또는 0 금액 인출 시도"};
	}
	if(amount > getCurrentAmount()){
		throw std::invalid_argument{"잔액을 초과하여 인출 시도"};
	}

	int idx{0};
	bool paid_by_lowerCurrency{false}; // 지불해야 할 금액보다 작은 액면가로 계산이 가능한지 여부
	int lowerCurrency_Sum{0};
	std::vector<int> temp_M = std::vector<int>(6,0); // 계산에 사용할 작은 액면가 화폐 개수를 저장하는 벡터

	while(denomination_array[idx] < amount){
		for(int i{0}; i<M[idx];++i){

			lowerCurrency_Sum += denomination_array[idx];
			++temp_M[idx];

			if(amount <= lowerCurrency_Sum){ // 지불해야 할 금액이 작은 액면가의 합보다 작거나 같은 경우
				paid_by_lowerCurrency = true;
				break;
			}
		}
		++idx;
	}

	int changes; // 잔돈

	if(paid_by_lowerCurrency){

		while(amount>0){
			for(int i{0}; i < temp_M[idx]; ++i){
				amount -= denomination_array[idx];
				--M[idx];

				if(amount<=0){ // 지불해야 할 금액을 모두 지불한 경우
					break;
				}
			}

			--idx;
		}
		changes = -amount;
	}

	else{
		changes = denomination_array[idx] - amount; // 현재 idx는 amount보다 큰 액면가 중에 가장 작은 액면가의 인덱스
		--M[idx];
	}

	calculate_changes(changes); // 잔돈 계산

}

void Wallet::calculate_changes(int changes){

	int idx{static_cast<int>(M.size()) - 1}; // 마지막 화폐부터 검사
	int denomination{0};

	while(changes!=0){

		denomination = denomination_array[idx];

		if(changes/denomination > 0){ // 해당 화폐로 잔돈이 나누어지는 경우
			M[idx] += changes/denomination; // 해당 화폐개수를 몫만큼 증가시킴
			changes %= denomination;
		}

		--idx;
	}
}

void Wallet::clear(){
	M = std::vector<int>(6,0);
}

int Wallet::getCurrentAmount() const noexcept{
	int current_amount{0};
	for(int i{0}; i< static_cast<int>(M.size());++i){
		current_amount += denomination_array[i] * M[i]; // 액면가 * 소지한 화폐개수
	}
	return current_amount;
}



