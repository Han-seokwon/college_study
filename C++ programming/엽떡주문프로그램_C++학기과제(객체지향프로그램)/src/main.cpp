//============================================================================
// Name        : main.cpp
// Version     : 프로그램을 실행하는 main() 함수가 있는 소스파일
//============================================================================

#include <iostream>
#include <limits>
#include "order.h"

// 주문 명령어
extern OrderProcessCommand order_command;

int main(){
	// 주문 데이터 만들기
	make_MenuData();
	// 주문과정 시작
	while(order_command != OrderProcessCommand::END){
		try{
			select_StartProgram(); // 1. 주문시작 or 2. 프로그램 종료
		}
		catch(const std::invalid_argument& error){
			input_error_catch(error);
		}
		catch(const std::runtime_error& error){
			std::cout<< "\n" << error.what() << "\n";
		}
	}

	std::cout<< "\n[프로그램이 종료되었습니다.]\n" ;

	return 0;

}
