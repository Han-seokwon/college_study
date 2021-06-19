//============================================================================
// Name        : input_or_put_orderData.cpp
// Description : 주문 입력 및 입력 받은 값을 주문데이터에 추가하는데 사용되는 함수를 정의한 파일
//============================================================================


#include <iostream>
#include <vector>
#include <stdexcept>
#include "Order.h"

extern std::vector<SetMenuData> setMenu_DataList;


// 주문 명령어
extern OrderProcessCommand order_command;

extern std::string WRONGINPUT_ERROR_MESSAGE;

// 메뉴 종류의 개수
const int MENUTYPE_SIZE{3};

void input_MenuType(int& selected_MenuTypeNum){
	std::cin >> selected_MenuTypeNum;
	// 사용자가 뒤로가기를 입력한 경우
	if(selected_MenuTypeNum == static_cast<int>(OrderProcessCommand::GO_BACK)){
		order_command = OrderProcessCommand::GO_BACK;
	}
	// 잘못된 메뉴종류 입력
	else if(0 >= selected_MenuTypeNum || selected_MenuTypeNum > MENUTYPE_SIZE){
		throw std::invalid_argument{WRONGINPUT_ERROR_MESSAGE};
	}
}




// 사용자로부터 메인메뉴를 입력
void input_MainMenu(int& selected_MainMenuNum){
	std::cin >> selected_MainMenuNum;
	if(selected_MainMenuNum == static_cast<int>(OrderProcessCommand::GO_BACK)){
		order_command = OrderProcessCommand::GO_BACK;
	}
}



// 사용자가 선택한 메인 메뉴를 주문데이터에 추가
void put_MainMenu_To_OrderData(int selected_MainMenuNum, MainMenu_OrderData& MainMenu_order){
	MainMenu_order.set_ordered_MainMenuID_Price(selected_MainMenuNum-1); // 유효하지 않은 값 전달시 예외 발생
	// 메인 메뉴 선택 단계종료
	order_command = OrderProcessCommand::END;
}




// 사용자로부터 매운맛을 입력
void input_SpicyLevel(int& selected_SpicyLevelNum, MainMenu_OrderData& MainMenu_order){
	std::cin >> selected_SpicyLevelNum;
	if(selected_SpicyLevelNum == static_cast<int>(OrderProcessCommand::GO_BACK)){
		order_command = OrderProcessCommand::GO_BACK;
	}
}



// 사용자가 입력한 매운맛을 주문데이터에 추가
void put_SpicyLevel_To_OrderData(int selected_SpicyLevelNum, MainMenu_OrderData& MainMenu_order){
	MainMenu_order.set_SpicyLevel(selected_SpicyLevelNum-1); // 유효하지 않은 값 전달시 예외 발생
	// 매운맛 선택 단계를 종료
	order_command = OrderProcessCommand::END;
}



// 사용자로부터 토핑을 입력받음
void input_ToppingMenu(std::vector<int>& selected_ToppingNums, MainMenu_OrderData& MainMenu_order){
	int toppingNum;
	do{
		// 입력
		std::cin >> toppingNum;

		// 사용자가 뒤로가기를 입력한 경우
		if(toppingNum == static_cast<int>(OrderProcessCommand::GO_BACK)){
			order_command = OrderProcessCommand::GO_BACK;
			break;
		}
		// 토핑 선택 안 함을 입력한 경우
		else if(toppingNum == static_cast<int>(OrderProcessCommand::END)){
			order_command = OrderProcessCommand::END;
			break;
		}

		// 선택된 번호를 토핑 번호리스트에 추가
		selected_ToppingNums.push_back(toppingNum);

	}while(std::getc(stdin)!= '\n');
}


// 사용자가 선택한 토핑을 주문데이터에 추가
void put_ToppingMenu_To_OrderData(std::vector<int> selected_ToppingNums, MainMenu_OrderData& MainMenu_order){
	for(int i{0}; i< static_cast<int>(selected_ToppingNums.size()); ++i){
		int toppingNum{selected_ToppingNums[i]};
		// 선택된 토핑을 주문데이터에 추가
		MainMenu_order.add_Ordered_ToppingID(toppingNum-1); // 유효하지 않은 값 전달시 예외 발생
	}
	// 토핑 선택 단계 종료
	order_command = OrderProcessCommand::END;

}



// 주문 확인 단계에서 사용자로부터 선택지(뒤로가기 or 주문확정)를 입력
void input_Confirm_Order(int &selected_confirm_orderNum){
	std::cin >> selected_confirm_orderNum;
	if(selected_confirm_orderNum == 1){
		order_command = OrderProcessCommand::GO_BACK;
	}
	else if(selected_confirm_orderNum == 2){
		order_command = OrderProcessCommand::END;
	}
	else{
		throw std::invalid_argument{WRONGINPUT_ERROR_MESSAGE};
	}
}


// 사용자로부터 세트메뉴를 입력
void input_SetMenu(int& selected_SetMenuNum){
	std::cin >> selected_SetMenuNum;
	if(selected_SetMenuNum == static_cast<int>(OrderProcessCommand::GO_BACK)){
		order_command = OrderProcessCommand::GO_BACK;
	}
}


// 사용자가 선택한 세트메뉴를 주문데이터에 추가
void put_SetMenu_To_OrderData(int selected_SetMenuNum, SetMenu_OrderData& SetMenu_OrderData){
	SetMenu_OrderData.set_ordered_SetMenuID_Price(selected_SetMenuNum - 1); // 유효하지 않은 값 전달시 예외 발생
	// 메인 메뉴 선택 단계종료
	order_command = OrderProcessCommand::END;
}



// 사용자로부터 선택가능한 옵션 메뉴를 입력
void input_Selectable_Options(std::vector<int>& selected_OptionNums){
	int optionNum;
	do{
		// 입력
		std::cin >> optionNum;

		// 사용자가 뒤로가기를 입력한 경우
		if(optionNum == static_cast<int>(OrderProcessCommand::GO_BACK)){
			order_command = OrderProcessCommand::GO_BACK;
			break;
		}
		// 선택된 번호를 옵션 번호리스트에 추가
		selected_OptionNums.push_back(optionNum);

	}while(std::getc(stdin)!= '\n');
}


// 사용자로부터 입력받은 옵션 번호들을 메인메뉴 옵션과, 기타메뉴 옵션으로 분리하여 주문데이터에 추가
void put_MainMenu_OtherMenu_Option(std::vector<int>& selected_OptionNums, SetMenu_OrderData& SetMenu_order){
	int selectable_MainMenuID_OptionList_Size = static_cast<int>(setMenu_DataList[SetMenu_order.get_ordered_SetMenuID()].get_selectable_MainMenuID_OptionList().size());
	int selectable_OtherMenuID_OptionList_Size = static_cast<int>(setMenu_DataList[SetMenu_order.get_ordered_SetMenuID()].get_selectable_OtherMenuID_OptionList().size());

	std::vector<int> selected_MainMenu_OptionNums; // 메인 메뉴 옵션 번호 리스트
	std::vector<int> selected_OtherMenu_OptionNums; // 기타 메뉴 옵션 번호 리스트

	// 입력된 옵션 개수들과 선택할 수 있는 옵션의 개수가 일치하는 경우
	if(static_cast<int>(selected_OptionNums.size()) == selectable_MainMenuID_OptionList_Size + selectable_OtherMenuID_OptionList_Size){
		// 입력된 옵션들을 분리
		for(int i{0}; i < static_cast<int>(selected_OptionNums.size()); ++i){
			// 메인 메뉴 옵션
			if(i < selectable_MainMenuID_OptionList_Size){
				SetMenu_order.add_Ordered_MainMenu_OptionIDList(selected_OptionNums[i] - 1); // 유효하지 않은 값 전달시 예외 발생
			}
			// 기타 메뉴 옵션
			else{
				// 바로 주문데이터에 입력
				SetMenu_order.add_Ordered_OtherMenu_Options(selected_OptionNums[i] - 1); // 유효하지 않은 값 전달시 예외 발생
			}
		}
	}
	else{
		throw std::invalid_argument{"경고: 입력하신 옵션 번호가 많거나 부족합니다. 각 옵션에 맞는 번호를 입력해주세요."};
	}
	order_command = OrderProcessCommand::END;
}


// 사용자로부터 선택가능한 옵션 메뉴를 입력
void input_Order_End_Continue_Cancel(int& select_Num){
	std::cin >> select_Num;
	// 주문 취소하기
	if(select_Num == static_cast<int>(OrderProcessCommand::CANCEl)){
		order_command = OrderProcessCommand::CANCEl;

	}
	// 주문 종료하기
	else if(select_Num == static_cast<int>(OrderProcessCommand::END)){
		order_command = OrderProcessCommand::END;
	}
	// 새로운 메뉴 추가하기
	else if(select_Num == static_cast<int>(OrderProcessCommand::CONTINUE)){
		order_command = OrderProcessCommand::CONTINUE;
	}
	else{
		throw std::invalid_argument{WRONGINPUT_ERROR_MESSAGE};
	}
}








