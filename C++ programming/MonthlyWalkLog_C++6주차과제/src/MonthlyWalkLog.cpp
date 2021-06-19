//============================================================================
// Name        : MonthlyWalkLog.cpp
// Description : 매월 걸은 거리를 기록하는 클래스
//============================================================================


#include <iostream>

class MonthlyWalkLog{
private:
	double dailyDistance[31]{0};
public:
	const int year;
	const int month;
public:
	MonthlyWalkLog(int year, int month):
		year{checkYear(year)}, month{checkMonth(month)} {}

		void recordDistance(int dat, double distance){

			if(isValidDate(year, month, dat)){ // 입력된 요일이 유효한 경우

				if(0 <= distance){ // 거리정보가 0보다 큰 경우

					if(dailyDistance[dat]){ // 입력한 요일에 이미 거리정보가 입력된 경우
						char distanceChange;
						std::cout << dat <<"일은 이미 "<< dailyDistance[dat] <<"m로 거리정보가 기록되었습니다." << '\n';
						std::cout << distance << "m로 거리정보를 바꾸시겠습니까?(y/n)";
						std::cin >> distanceChange; //

						if(distanceChange == 'y'){ // 거리정보를 바꾸겠다고 한 경우
							dailyDistance[dat] = distance;
						}
					}

					else{ // 입력한 요일에 입력된 거리정보가 없는 경우
						dailyDistance[dat] = distance;
					}
				}

				else{ // 거리정보가 음수인 경우
					std::cout << "거리정보로 음수를 입력할 수 없습니다." << '\n';
				}
			}

			else{ // 입력된 요일이 유효한 값이 아닌 경우
				std::cout << year <<"년의 " << month << "월에는 "
						<< dat << " 일이 존재하지 않습니다." << '\n';
			}
		}

		// 입력한 요일에 걸은 거리를 반환하는 메소드
		double getDay(int day){
			return dailyDistance[day];
		}



private:
		int checkYear(int year) const {
			if(1970<year){
				return year;
			}
			else{ // 유효하지 않은 년도가 인자로 전달된 경우는 사용자로부터 다시 입력받습니다.
				int newInputYear;
				std::cout << "MonthlyWalkLog의 year인자는 1970년 이상으로만 입력할 수 있습니다." << '\n';
				std::cout << "년도를 다시 입력해주세요: ";
				std::cin >> newInputYear;
				return checkYear(newInputYear); //재귀함수를 이용해 유효한 값이 입력될 때까지 입력을 받음
			}

		}
		int checkMonth(int month) const {
			if(1<= month && month <=12){
				return month;
			}
			else{ // 유효하지 않은 월이 인자로 전달된 경우는 사용자로부터 다시 입력받습니다.
				int newInputMonth;
				std::cout << "MonthlyWalkLog의 month인자는 1~12월 사이로만 입력할 수 있습니다." << '\n';
				std::cout << "월을 다시 입력해주세요: ";
				std::cin >> newInputMonth;
				return checkMonth(newInputMonth); //재귀함수를 이용해 유효한 값이 입력될 때까지 입력을 받음
			}
		}

		// 년과 월에 맞는 요일이 입력되었는지 검사하는 메소드
		bool isValidDate(int year, int month, int date) const{
			switch(month){
			case 1: case 3: case 5: case 7: case 8: case 10: case 12:
				// 1,3,5,7,8,10,12월은 31일까지 있음
				if(0<date&&date<=31) return true;

				else return false;

			case 4: case 6: case 9: case 11:
				// 4,6,9,11월은 30일까지 있음
				if(0<date&&date<=30) return true;

				else return false;

			case 2:
				// 2월인 경우
				if(0<date&&date<=28) return true;

				else if(date == 29){ // 29일이 입력된 경우
					// 윤년인 경우
					if(year%400==0||(year%100 && year%4==0)) return true;

					else return false;
				}

				else return false;
			}
			// month의 유효성은 checkMonth()에서 검사하므로 defalut 불필요
		}
};



int main() {

	// 테스트 케이스

	// 1. checkYear(), checkMonth() 메소드 테스트

	// 잘못된 년, 월이 입력된 경우
	MonthlyWalkLog walkLog1(1900, 20);
	std::cout << "최종 입력된 년/월: "<< walkLog1.year << ", " << walkLog1.month << '\n';


	// 2. recordDistance() 테스트

	MonthlyWalkLog walkLog2(2010, 2);

	// (예외상황1) 해당 년의 월의 일수에서 벗어난 요일이 입력된 경우
	walkLog2.recordDistance(29, 100); // 2010년은 평년이어서 29일이 존재하지 않음
	walkLog2.recordDistance(-1, 100);

	// (예외상황2) 입력된 거리수치가 음수인 경우
	walkLog2.recordDistance(14, -50);


	// (예외상황3) 걸은 거리를 입력하려는 요일에 이미 거리정보가 입력된 경우
	walkLog2.recordDistance(5, 50);
	walkLog2.recordDistance(5, 777);
	std::cout << walkLog2.year<< "년 " << walkLog2.month<< "월 "
			<< 5 << "일에 걸은 거리:"<< walkLog2.getDay(5) << "m" << '\n';


	return 0;
}
