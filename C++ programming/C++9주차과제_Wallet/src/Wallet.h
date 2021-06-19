//============================================================================
// Name        : Wallet.h
// Description : Wallet 클래스를 선언한 헤더파일
//============================================================================

#ifndef WALLET_H_
#define WALLET_H_
#include <vector>

class Wallet{

private:
	std::vector<int> M = std::vector<int>(6,0);
	static inline const int denomination_array[6] = {100, 500, 1'000, 5'000, 10'000, 50'000};
	void calculate_changes(int changes);

public:
	Wallet() = default;
	virtual ~Wallet() = default;
	void add(int denomination, int amount);
	void spend(int amount);
	void clear();
	int getCurrentAmount() const noexcept;

};


#endif /* WALLET_H_ */
