//============================================================================
// Name        : Fraction.h
// Description : 과제 8. 12장 연습문제 1 Fraction 클래스를 정의한 헤더파일
//============================================================================

#ifndef FRACTION_H_
#define FRACTION_H_

#include <stdexcept>
#include <algorithm>
#include <cstdlib>

struct Fraction_struct{
	int n;
	int d;
};

class Fraction{
private:
	int n{0};
	int d{1};

	// 약분 메소드
	Fraction_struct abbreviate(const Fraction& fraction) const{
		Fraction_struct tmp{fraction.n, fraction.d};
		int min_value = std::min(abs(tmp.n), tmp.d);

		for(int i{min_value}; i>=2; --i){ //
			if((tmp.n%i==0) && (tmp.d%i==0)){ // 공약수인 경우
				tmp.n /= i;
				tmp.d /= i;
				break; // 큰 수부터 시작했으므로 최대 공약수임 -> 이후 약분하지 않아도 됨
			}
		}
		return tmp;
	}

public:
	Fraction() = default;
	explicit Fraction(int n, int d=1): n{n}, d{d}{
		if(d==0) throw std::invalid_argument("Fraction(n, d): 분모는 0이 될 수 없음");
		if((n>=0&&d<0)||(n<0&&d<0)){
			this->n = -n;
			this->d = -d;
		}
	}

	virtual ~Fraction() = default;

	int numerator() const noexcept {return n;}

	int nominator() const noexcept {return d;}

	explicit operator std::string() const{
		if(n%d == 0) return std::to_string(n/d);
		return std::to_string(n) + "/" + std::to_string(d);
	}

	// 타입변환 연산자 double
	explicit operator double() const noexcept {
		return static_cast<double>(n)/d;
	}

	// 단항 연산자 -
	Fraction operator-() const noexcept{
		return Fraction(-n, d);
	}

	// 이항연산자 +
	Fraction operator+(const Fraction& other) const{
		Fraction tmp(*this);

		if(tmp.d == other.d){ // 분모가 같은 경우
			tmp.n += other.n;
		}

		else{ // 분모가 다른 경우 -> 통분
			tmp.n = (tmp.n*other.d) + (other.n*tmp.d);
			tmp.d = tmp.d * other.d;
		}

		Fraction_struct abbrev_tmp(abbreviate(tmp)); // 약분
		tmp.n = abbrev_tmp.n;
		tmp.d = abbrev_tmp.d;

		return tmp;
	}

	// 이항연산자 -
	Fraction operator-(const Fraction& other) const {
		return operator+(Fraction{-other.n, other.d});
	}

	// 이항연산자 *
	Fraction operator*(const Fraction& other) const{
		Fraction tmp(*this);
		// 분자끼리, 분모끼리 곱셈
		tmp.n *= other.n;
		tmp.d *= other.d;

		Fraction_struct abbrev_tmp(abbreviate(tmp)); // 약분
		tmp.n = abbrev_tmp.n;
		tmp.d = abbrev_tmp.d;

		return tmp;
	}

	// 이항연산자 /
	Fraction operator/(const Fraction& other) const{
		if(other.n==0){
			throw std::invalid_argument("0으로 나눌수 없음");
		}
		// 분모의 나눗셈 -> 분모의 역수를 곱함
		return operator*(Fraction{other.d, other.n});
	}

	// 비교연산자 >
	bool operator>(const Fraction& other) const{
		return operator-(other).n > 0 ; // other로 뺄셈을 한 후 분자가 0보다 크면 other보다 큰 것임
	}

	// 비교연산자 <
	bool operator<(const Fraction& other) const{
		return other.operator>(*this);
	}

	// 비교연산자 >=
	bool operator>=(const Fraction& other) const{
		return !operator<(other);
	}

	// 비교연산자 <=
	bool operator<=(const Fraction& other) const{
		return !operator>(other);
	}

	// 비교연산자 ==
	bool operator==(const Fraction& other) const{
		return operator-(other).n == 0 ;
	}

	// 비교연산자 !=
	bool operator!=(const Fraction& other) const{
		return !operator==(other) ;
	}


};



#endif /* FRACTION_H_ */
