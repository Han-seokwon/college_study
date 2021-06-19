//============================================================================
// Name        : main.cpp
// Description : 힉기과제 main.cpp 입니다.
//============================================================================

#include <iostream>
#include <limits>
#include "menu.h"

const int g_menuListCount{4};
const int g_setMenuCount{5};


int main(){
	std::vector<std::vector<MenuData>> AllMenuData(g_menuListCount);
	std::vector<SetMenuData> AllsetMenuData(g_setMenuCount);

	// 메뉴데이터를 구성함
	makeMenu(AllMenuData);
	makeSetMenu(AllMenuData, AllsetMenuData);

	std::cout << "   <<<엽기떡볶이 주문 프로그램>>>     " << '\n';
	while(true){
		if(selectStartProgram()==1){ // 주문프로그램을 시작한 경우
			if(startOrderProcess(AllMenuData, AllsetMenuData) == GO_BACK){ // 뒤로 가기를 선택한 경우
				continue;
			}
		}
		else{ // 프로그램 종료를 선택한 경우
			break;
		}
	}
	std::cout << '\n' << "       <<<프로그램 종료>>>         " << '\n';

	return 0;
}



// 사용자에게 시작메뉴를 선택하면 그에 맞는 정수형을 반환함
int selectStartProgram(){
	int startProgramChoice{0};
	std::vector<std::string> startProgramOption{"주문 시작", "프로그램 종료"};
	int startProgramOptionSize{static_cast<int>(startProgramOption.size())};

	while(true){
		std::cout <<'\n'<< "-----------------------------"<< '\n';
		std::cout << "<시작메뉴입니다.>"<< '\n' << '\n';
		for(int i{0}; i<startProgramOptionSize; ++i){
			std::cout << "  " << i+1 <<". "<< startProgramOption[i]<< '\n';
		}
		std::cout << '\n'<< "실행하실 기능의 번호를 입력해주세요: ";
		std::cin >> startProgramChoice;

		if(1<=startProgramChoice && startProgramChoice<=startProgramOptionSize){
			std::cout << '\n' << "--> ";
			std::cout << startProgramOption[startProgramChoice-1] << "을(를) 선택하셨습니다." << '\n';
			return startProgramChoice;
		}
		else{
			printInputError();
		}
	}
}

// 사용자가 잘못된 입력을 했을 때 경고문을 출력함
void printInputError(){
	std::cout << '\n' << "<<입력이 잘못되었습니다!!!>>"<< '\n';
	std::cout << "선택지에 맞는 번호를 입력해주세요."<< '\n' ;
	std::cin.clear();
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}
