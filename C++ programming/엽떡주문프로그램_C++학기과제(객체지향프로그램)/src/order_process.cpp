//============================================================================
// Name        : order_process.cpp
// Description : 주문 선택 및 처리과정에서 사용되는 함수, 클래스를 정의한 파일입니다.
//============================================================================


#include <iostream>
#include <vector>
#include <stdexcept>
#include "Order.h"


extern std::vector<MainMenuData> mainMenu_DataList;
extern std::vector<SetMenuData> setMenu_DataList;

// 프로그램에서 사용할 주문 프로세스 스택
OrderProcess_Stack orderProcess_Stack;

// 주문 명령어(주문과정이 종료되고 뒤로가기, 앞 단계로 가기 등의 주문프로세스를 결정할 명령어)
OrderProcessCommand order_command{OrderProcessCommand::CONTINUE};


// OrderProcess_Stack 클래스

OrderProcess OrderProcess_Stack::get_Top_orderStack() const noexcept{
	if(!orderStack.empty()){
		return orderStack.top();
	}
	else{ // 실제로 주문과정에서 이 경우는 발생하지 않음
		throw std::runtime_error{"주문프로세스 스택이 비어있습니다."};
	}
}

// 주문 프로세스 스택의 가장 위의 요소를 스택에서 빼내고 반환
OrderProcess OrderProcess_Stack::pop_orderStack(){
	if(!orderStack.empty()){
		OrderProcess temp_OrderProcess{this->get_Top_orderStack()};
		orderStack.pop();
		return temp_OrderProcess;
	}
	else{ // 실제로 주문과정에서 이 경우는 발생하지 않음
		throw std::runtime_error{"주문프로세스 스택이 비어있습니다."};
	}
}

// 주문 프로세스 스택을 비움
void OrderProcess_Stack::clear_orderStack(){
	std::stack<OrderProcess> emptyStack;
	orderStack = emptyStack;
}

// 인자로 들어온 요소를 스택에 push
void OrderProcess_Stack::push_orderStack(OrderProcess current_OrderProcess){
	orderStack.push(current_OrderProcess);
}


// 현재 주문과정을 실행해도 되는지 여부를 확인
bool check_OrderProcess(OrderProcess current_OrderProcess){
	// 명령이 정상실행인 경우
	if(order_command == OrderProcessCommand::CONTINUE){
		return true;
	}
	else if(order_command == OrderProcessCommand::GO_BACK && // 현재 명령이 뒤로가기 이고
			orderProcess_Stack.get_Top_orderStack() == current_OrderProcess){ // 이전 주문단계가 현재 단계인 경우
		order_command = OrderProcessCommand::CONTINUE;
		orderProcess_Stack.pop_orderStack();
		return true;
	}
	else{
		return false;
	}
}
// 현재 과정이 정상적으로 종료되었는지 확인
void check_OrderProcess_WellEnded(OrderProcess current_OrderProcess){
	if(order_command == OrderProcessCommand::END){
		// 주문프로세스 스택에 현재 프로세스 추가
		orderProcess_Stack.push_orderStack(current_OrderProcess);
		// 이후 단계로 넘어감
		order_command = OrderProcessCommand::CONTINUE;
	}
}



void select_StartProgram(){
	while(order_command != OrderProcessCommand::END){

		// 시작 메뉴 선택
		int selected_StartProgram;
		print_StartProgram();
		std::cin >> selected_StartProgram;

		// 주문 시작
		if(selected_StartProgram == 1){

			// 주문 프로세스 스택 비우기
			orderProcess_Stack.clear_orderStack();

			OrderList orderList;
			select_Menu_Process(orderList); // 메뉴 선택과정 진행

			if(order_command == OrderProcessCommand::END){
				// 주문 종료인 경우 최종 주문 내역 출력
				print_OrderList(orderList, true);
			}
			// 뒤로가기, 주문 종료인 경우 이후의 단계는 정상실행
			order_command = OrderProcessCommand::CONTINUE;
		}
		// 프로그램 종료
		else if(selected_StartProgram == 2){
			order_command = OrderProcessCommand::END;
		}
		else{
			throw std::invalid_argument{"경고: 잘못된 번호 입력입니다."};
		}
	}
}



// 메뉴 선택과정(메뉴 종류 -> 메뉴선택 -> 주문추가 확인)
void select_Menu_Process(OrderList& orderList){

	MenuType selected_menuType;

	while(order_command != OrderProcessCommand::END){
		// 메뉴 종류 선택
		if(check_OrderProcess(OrderProcess::MENUTYPE_SELECT)){
			select_MenuType(selected_menuType);
			if(order_command == OrderProcessCommand::GO_BACK){
				break; // select_StartProgram()으로 돌아감
			}

			// 메뉴 종류에 맞는 메뉴 선택
			select_Menu(selected_menuType, orderList);

			// 새로운 메뉴 추가, 메뉴 취소, 주문 종료 중에 선택(이 단계에서는 뒤로가기 불가능)
			select_Order_End_Continue_Cancel(orderList);
		}
	}
}

// 메뉴 종류 선택
void select_MenuType(MenuType& selected_menuType){
	while(order_command != OrderProcessCommand::END){
		// 메뉴 종류 출력
		print_MenuType();
		int selected_MenuTypeNum;
		try{
			// 메뉴 종류 입력
			input_MenuType(selected_MenuTypeNum);
			if(order_command == OrderProcessCommand::GO_BACK){
				break;
			}
		}
		catch(const std::invalid_argument& error){
			input_error_catch(error);
			continue;
		}
		selected_menuType = static_cast<MenuType>(selected_MenuTypeNum);
		// 메뉴종류 선택 단계 종료
		order_command = OrderProcessCommand::END;
	}
	// 현재 단계가 정상적으로 종료되었는지 확인
	check_OrderProcess_WellEnded(OrderProcess::MENUTYPE_SELECT);
}


// 입력된 메뉴종류에 맞는 메뉴선택 프로세스를 실행
void select_Menu(MenuType selected_menuType, OrderList& orderList){
	switch(selected_menuType){
	case MenuType::MAIN:
		select_MainMenuProcess(orderList);
		break;

	case MenuType::SET:
		select_SetMenuProcess(orderList);
		break;

	case MenuType::SIDE:
		select_SideMenu(orderList);
		break;

		// 실제로 주문과정에서 이 경우는 발생하지 않음
	default:
		throw std::runtime_error{"처리할 수 없는 메뉴종류입니다."};
		break;
	}
}

// 메인 메뉴 선택 과정(메인메뉴 선택 -> 매운맛 선택 -> 토핑 선택 -> 주문 확인)
void select_MainMenuProcess(OrderList& orderList){
	MainMenu_OrderData MainMenu_OrderData{};
	while(order_command != OrderProcessCommand::END){
		// 뒤로가기가 실행되었는데 이전 단계가 메뉴종류 선택 단계인 경우
		if(order_command == OrderProcessCommand::GO_BACK && orderProcess_Stack.get_Top_orderStack() == OrderProcess::MENUTYPE_SELECT){
			break;
		}
		// 메뉴 선택
		select_MainMenu(MainMenu_OrderData);

		// 매운맛 선택
		select_SpicyLevel(MainMenu_OrderData);

		// 토핑 선택
		select_ToppingMenu(MainMenu_OrderData);

		// 주문 확인 단계
		select_Confirm_MainMenu(MainMenu_OrderData);

	}

	// 정상적으로 위의 과정들이 끝난경우
	if(order_command == OrderProcessCommand::END){
		// 주문내역에 주문데이터 추가
		orderList.add_Ordered_MainMenu(MainMenu_OrderData);
		order_command = OrderProcessCommand::CONTINUE;
	}

}

// 메인 메뉴 선택
void select_MainMenu(MainMenu_OrderData& MainMenu_order){
	if(check_OrderProcess(OrderProcess::MENU_SELECT)){
		while(order_command != OrderProcessCommand::END){

			// 메인 메뉴 출력
			print_MainMenu();
			// 메인 메뉴 입력
			int selected_MainMenuNum;
			input_MainMenu(selected_MainMenuNum);
			if(order_command == OrderProcessCommand::GO_BACK){
				break;
			}
			try{
				// 메인메뉴 주문데이터에 추가
				put_MainMenu_To_OrderData(selected_MainMenuNum, MainMenu_order);
			}
			catch(const std::invalid_argument& error){
				input_error_catch(error);
			}
		}
		check_OrderProcess_WellEnded(OrderProcess::MENU_SELECT);
	}
}


// 매운맛 선택
void select_SpicyLevel(MainMenu_OrderData& MainMenu_order){
	if(check_OrderProcess(OrderProcess::SPICY_SELECT)){
		while(order_command != OrderProcessCommand::END){

			// 매운맛을 선택할 수 없는 메뉴인 경우
			int selectable_SpicyLevelList_Size{
				static_cast<int>(mainMenu_DataList[MainMenu_order.get_ordered_MainMenuID()].get_selectable_SpicyLevelList().size())};
			if(selectable_SpicyLevelList_Size == 0){
				break;
			}
			// 매운맛 출력
			print_Selectable_SpicyLevel(mainMenu_DataList[MainMenu_order.get_ordered_MainMenuID()]);

			int selected_SpicyLevelNum;

			// 매운맛 입력
			input_SpicyLevel(selected_SpicyLevelNum, MainMenu_order);
			if(order_command == OrderProcessCommand::GO_BACK){
				break;
			}

			try{
				// 주문데이터에 매운맛 추가
				put_SpicyLevel_To_OrderData(selected_SpicyLevelNum, MainMenu_order);
			}
			catch(const std::invalid_argument& error){
				input_error_catch(error);
				continue;
			}

		}
		check_OrderProcess_WellEnded(OrderProcess::SPICY_SELECT);
	}
}

// 토핑 선택
void select_ToppingMenu(MainMenu_OrderData& MainMenu_order){
	if(check_OrderProcess(OrderProcess::TOPPING_SELECT)){
		while(order_command != OrderProcessCommand::END){
			// 토핑 리스트 초기화
			MainMenu_order.clear_Ordered_ToppingIDList();
			// 토핑 출력
			print_Selectable_ToppingMenu(mainMenu_DataList[MainMenu_order.get_ordered_MainMenuID()]);

			std::vector<int> selected_ToppingNums; // 사용자의 입력을 받을 토핑 번호리스트

			// 토핑 입력
			input_ToppingMenu(selected_ToppingNums, MainMenu_order);
			// 뒤로가기나 토핑 선택 안 함을 입력한 경우
			if(order_command == OrderProcessCommand::GO_BACK || order_command == OrderProcessCommand::END){
				break;
			}

			try{
				// 선택한 토핑들을 주문 데이터에 추가
				put_ToppingMenu_To_OrderData(selected_ToppingNums, MainMenu_order);
			}
			catch(const std::logic_error& error){ // 비정상 입력 or 최대 추가가능 토핑개수 초과
				input_error_catch(error);
				continue;
			}
		}
		check_OrderProcess_WellEnded(OrderProcess::TOPPING_SELECT);
	}
}



// 현재까지 주문한 메인 메뉴데이터를 주문내역에 추가할지 선택
void select_Confirm_MainMenu(MainMenu_OrderData& MainMenu_order){
	if(order_command == OrderProcessCommand::CONTINUE){ // CONTINUE인 경우에만 실행
		while(order_command != OrderProcessCommand::END){
			// 메인 메뉴 주문 확인 출력
			print_Confirm_MainMenu(MainMenu_order);
			int selected_confirm_orderNum;
			try{
				// 메인 메뉴 주문 확인 입력
				input_Confirm_Order(selected_confirm_orderNum);
				if(order_command == OrderProcessCommand::GO_BACK){
					break;
				}
			}
			catch(const std::invalid_argument& error){
				input_error_catch(error);
			}
		}
	}
}


// 세트메뉴 선택과정(세트 메뉴 선택 -> 옵션 선택 )
void select_SetMenuProcess(OrderList& orderList){
	SetMenu_OrderData SetMenu_OrderData{};
	while(order_command != OrderProcessCommand::END){
		// 뒤로가기가 실행되었는데 이전 단계가 메뉴종류 선택 단계인 경우
		if(order_command == OrderProcessCommand::GO_BACK && orderProcess_Stack.get_Top_orderStack() == OrderProcess::MENUTYPE_SELECT){
			break;
		}
		// 세트 메뉴 선택
		select_SetMenu(SetMenu_OrderData);

		// 옵션 선택
		select_Selectable_Options(SetMenu_OrderData);

		// 메인메뉴 옵션 추가 선택(매운맛 -> 토핑)
		select_MainMenu_OptionProcess(SetMenu_OrderData);

		// 주문 확정
		select_Confirm_SetMenu(SetMenu_OrderData);

	}

	// 정상적으로 위의 과정들이 끝난경우
	if(order_command == OrderProcessCommand::END){
		// 주문내역에 주문데이터 추가
		orderList.add_Ordered_SetMenu(SetMenu_OrderData);
		order_command = OrderProcessCommand::CONTINUE;
	}
}

void select_SetMenu(SetMenu_OrderData& SetMenu_OrderData){
	if(check_OrderProcess(OrderProcess::MENU_SELECT)){
		while(order_command != OrderProcessCommand::END){
			// 세트 메뉴 출력
			print_SetMenu();
			// 세트 메뉴 입력
			int selected_SetMenuNum;
			input_SetMenu(selected_SetMenuNum);
			if(order_command == OrderProcessCommand::GO_BACK){
				break;
			}
			try{
				// 세트메뉴 주문 데이터에 추가
				put_SetMenu_To_OrderData(selected_SetMenuNum,SetMenu_OrderData);
			}
			catch(const std::invalid_argument& error){
				input_error_catch(error);
			}
		}
		check_OrderProcess_WellEnded(OrderProcess::MENU_SELECT);
	}
}


void select_Selectable_Options(SetMenu_OrderData& SetMenu_order){
	if(check_OrderProcess(OrderProcess::OPTION_SELECT)){
		while(order_command != OrderProcessCommand::END){
			// 주문데이터의 옵션 리스트 초기화
			SetMenu_order.clear_all_OptionList();
			// 옵션 출력
			print_Selectable_Options(setMenu_DataList[SetMenu_order.get_ordered_SetMenuID()]);
			// 옵션 입력
			std::vector<int> selected_OptionNums; // 사용자의 입력을 받을 옵션 번호리스트
			input_Selectable_Options(selected_OptionNums);
			if(order_command == OrderProcessCommand::GO_BACK){
				break;
			}
			try{
				// 메인메뉴 옵션과, 기타메뉴 옵션으로 분리하여 주문데이터에 추가
				put_MainMenu_OtherMenu_Option(selected_OptionNums, SetMenu_order);
			}
			catch(const std::invalid_argument& error){
				input_error_catch(error);
			}

		}
		check_OrderProcess_WellEnded(OrderProcess::OPTION_SELECT);
	}
}


// 세트메뉴의 메인메뉴 옵션 선택과정(매운맛 선택 -> 토핑 선택)
void select_MainMenu_OptionProcess(SetMenu_OrderData& SetMenu_order){
	if(check_OrderProcess(OrderProcess::TOPPING_SELECT)){
		int MainMenu_OptionCnt{0};
		std::vector<int> ordered_MainMenu_OptionIDList = SetMenu_order.get_ordered_MainMenu_OptionIDList();

		MainMenu_OrderData MainMenu_Order;

		// 주문확정 단계에서 "뒤로가기"로 메인메뉴 옵션 선택단계로 왔는지 확인
		check_MainMenu_Option_Run_From_GO_BACK(MainMenu_OptionCnt, MainMenu_Order, SetMenu_order);

		// 모든 메인메뉴 옵션의 선택을 마칠 때까지 반복
		while(MainMenu_OptionCnt < static_cast<int>(ordered_MainMenu_OptionIDList.size())){
			// 메인 메뉴 ID 설정
			MainMenu_Order.set_ordered_MainMenuID_Price(ordered_MainMenu_OptionIDList[MainMenu_OptionCnt]);

			// 매운맛 선택
			select_SpicyLevel(MainMenu_Order);
			if(order_command == OrderProcessCommand::GO_BACK){
				// 뒤로가기가 실행되었는데 이전 단계가 옵션선택 단계인 경우
				if(orderProcess_Stack.get_Top_orderStack() == OrderProcess::OPTION_SELECT){
					break;
				}
				else if(orderProcess_Stack.get_Top_orderStack() == OrderProcess::TOPPING_SELECT){
					--MainMenu_OptionCnt;
					// 이전에 저장한 메인메뉴 옵션 데이터 불러오기
					MainMenu_Order = SetMenu_order.pop_ordered_MainMenu_OptionList();
				}
			}

			// 토핑 선택
			select_ToppingMenu(MainMenu_Order);

			// 토핑 선택이 정상적으로 종료된 경우
			check_MainMenu_Option_Topping_WellEnded(MainMenu_OptionCnt, MainMenu_Order, SetMenu_order);
		}
	}
}

// 주문확정 단계에서 "뒤로가기"로 메인메뉴 옵션 선택단계로 왔는지 확인
void check_MainMenu_Option_Run_From_GO_BACK(int& MainMenu_OptionCnt, MainMenu_OrderData MainMenu_Order, SetMenu_OrderData& SetMenu_order){
	int ordered_MainMenu_OptionList_Size = static_cast<int>(SetMenu_order.get_Ordered_MainMenu_OptionList().size());
	if(ordered_MainMenu_OptionList_Size){
		// 이전의 데이터를 불러옴
		MainMenu_Order = SetMenu_order.pop_ordered_MainMenu_OptionList();
		MainMenu_OptionCnt = ordered_MainMenu_OptionList_Size - 1;
	}
}

// 메인메뉴 옵션 선택단계에서 토핑 선택이 정상적으로 종료되었는지 확인
void check_MainMenu_Option_Topping_WellEnded(int& MainMenu_OptionCnt, MainMenu_OrderData MainMenu_Order, SetMenu_OrderData& SetMenu_order){
	if(order_command == OrderProcessCommand::CONTINUE){
		// 다음 옵션 선택으로 넘어감
		++MainMenu_OptionCnt;

		// 현재까지의 메인메뉴 옵션정보를 세트메뉴에 추가
		SetMenu_order.add_Ordered_MainMenu_Options(MainMenu_Order);

		// 메인메뉴 옵션 정보를 초기화
		MainMenu_OrderData temp_OrderData;
		MainMenu_Order = temp_OrderData;

	}
}




// 현재까지 주문한 세트 메뉴데이터를 주문내역에 추가할지 선택
void select_Confirm_SetMenu(SetMenu_OrderData& SetMenu_order){
	if(order_command == OrderProcessCommand::CONTINUE){
		while(order_command != OrderProcessCommand::END){
			// 세트 주문 확인 출력
			print_Confirm_SetMenu(SetMenu_order);
			int selected_confirm_orderNum;
			try{
				// 세트 주문 확인 입력
				input_Confirm_Order(selected_confirm_orderNum);
				if(order_command == OrderProcessCommand::GO_BACK){
					break;
				}
			}
			catch(const std::invalid_argument& error){
				input_error_catch(error);
			}
		}
	}

}



void select_SideMenu(OrderList& orderList){
	while(order_command != OrderProcessCommand::END){
		// 사이드 메뉴 출력
		print_SideMenu();

		// 사이드 메뉴 입력(주문할 수 있는 개수는 제한이 없음)
		std::vector<int> selected_SideMenuNums;
		int sideMenu_Cnt{0};
		input_SideMenu(sideMenu_Cnt, selected_SideMenuNums);
		if(order_command == OrderProcessCommand::GO_BACK){
			break;
		}

		try{
			// 입력된 사이드 메뉴들을 주문내역에 추가
			put_SideMenu_To_OrderData(sideMenu_Cnt, selected_SideMenuNums, orderList);
		}
		catch(const std::invalid_argument& error){
			input_error_catch(error);
		}
	}
	check_OrderProcess_WellEnded(OrderProcess::MENU_SELECT);
}

// 사용자로부터 사이드 메뉴를 입력받고 값의 유효성을 검사
void input_SideMenu(int& sideMenu_Cnt, std::vector<int>& selected_SideMenuNums){
	int sideMenuNum;
	do{
		std::cin >> sideMenuNum;
		if(sideMenuNum == static_cast<int>(OrderProcessCommand::GO_BACK)){
			order_command = OrderProcessCommand::GO_BACK;
			break;
		}
		selected_SideMenuNums.push_back(sideMenuNum);
		++sideMenu_Cnt;
	}while(std::getc(stdin)!= '\n');
}


// 사이드 메뉴들을 주문내역에 추가
void put_SideMenu_To_OrderData(int sideMenu_Cnt, std::vector<int> selected_SideMenuNums, OrderList& orderList){
	for(int i{0}; i< sideMenu_Cnt; ++i){
		int sideMenuNum{selected_SideMenuNums[i]};
		orderList.add_Ordered_SideMenuID(sideMenuNum - 1); // 유효하지 않은 값 전달시 예외 발생
	}
	order_command = OrderProcessCommand::END;
}


// 주문 종료, 주문 계속, 주문 취소 중에 선택
void select_Order_End_Continue_Cancel(OrderList& orderList){
	if(order_command == OrderProcessCommand::CONTINUE){
		while(order_command != OrderProcessCommand::END){
			print_OrderList(orderList);
			int select_Num;
			try{
				// 입력
				input_Order_End_Continue_Cancel(select_Num);
				if(order_command == OrderProcessCommand::CANCEl){
					// 주문 취소 실행
					select_Menu_To_Cancel(orderList);
				}
			}
			catch(const std::invalid_argument& error){
				input_error_catch(error);
				continue;
			}
			if(order_command == OrderProcessCommand::CONTINUE){ // 새로운 주문 받기를 선택한 경우에도 break해야 함
				break;
			}
		}
	}
}

// 취소할 주문(메인, 세트, 사이드 중에)을 선택
void select_Menu_To_Cancel(OrderList& orderList){
	int menuType{0};
	int menuNum{0};
	// 취소할  메뉴종류, 메뉴 번호 입력
	std::cin >> menuType >> menuNum;
	if(static_cast<int>(MenuType::MAIN) <= menuType && menuType <=  static_cast<int>(MenuType::SIDE)){
		orderList.cancel_Ordered_Menu(static_cast<MenuType>(menuType), menuNum);
	}
	else{
		throw std::invalid_argument{"경고: 잘못된 메뉴 종류 입력입니다."};
	}
}





























