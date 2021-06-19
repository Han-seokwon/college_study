//============================================================================
// Name        : Order_Process.cpp
// Description : 주문 프로그램 실행에 필요한 함수들을 정의한 소스파일
//============================================================================

#include "menu.h"

// 주문 프로그램(메뉴종류 선택 -> 메뉴 선택 -> 주문내역 출력)을 실행
ProgramCommand startOrderProcess(std::vector<std::vector<MenuData>>& AllMenuData, std::vector<SetMenuData>& AllSetMenuData){

	ProgramCommand command{CONTINUE}; // 각 단계를 어떻게 실행할 것인지에 대한 명령, CONTINUE: 정상적으로 진행

	OrderProcess previous_process; //  이전에 실행한 단계

	std::vector<OrderProcess> finishedProcessStack; // 종료된 단계의 정보를 저장하는 스택

	TotalOrderHistory orderHistory; // 주문내역을 저장할 구조체

	MenuListOptions selectedMenuList;

	while(true){

		if(command == GO_BACK){ // 사용자가 이전단계로 돌아가려는 경우

			previous_process = lastProcess(finishedProcessStack); // 이전으로 돌아갈 단계를 찾음

			if(previous_process == NA){ // 이전으로 돌아갈 단계없는 경우
				return GO_BACK;
			}
		}

		// <메뉴종류 선택>
		if(command == CONTINUE || (command == GO_BACK && previous_process == OrderProcess::MENULIST_SELECT)){ //  정상진행 or command가 이전단계이고, 이전단계가 메뉴종류 선택 단계인 경우

			int selectedMenuListNum;
			selectedMenuListNum = selectMenuList(); // 메뉴 종류 선택

			if(selectedMenuListNum == GO_BACK){ // 사용자가 이전단계로 돌아간다고한 경우
				command = GO_BACK;
				continue;
			}

			selectedMenuList = changeType_To_MenuListOptions(selectedMenuListNum); // 선택한 메뉴종류를 MenuListOptions로 매칭

			finishedProcessStack.push_back(MENULIST_SELECT); // 현재 종료된 단계를 스택에 push

			command = CONTINUE; // 이후의 단계는 정상진행

		}

		OrderedData tempOrder; // 선택한 메뉴에 대한 데이터를 저장할 구조체

		// <메뉴선택>
		if(command == CONTINUE){
			if(selectedMenuList == SET_MENU){

				tempOrder.isSetMenu = true;

				command = selectSetMenuProcess(tempOrder.orderedSetMenu, AllSetMenuData); // 선후조건 : GO_BACK or END
				if(command == GO_BACK){
					continue;
				}

				tempOrder.orderedSetMenu.orderedSetMenuPrice = calculateOrderPrice(tempOrder); //선택한 메뉴의 가격계산
			}

			else{// 일반메뉴(세트메뉴 이외의 메뉴)를 선택한 경우

				command = selectMenuProcess(tempOrder.orderedMenu ,AllMenuData[selectedMenuList]); // 선후조건 : GO_BACK or END
				if(command == GO_BACK){
					continue;
				}

				tempOrder.orderedMenu.orderedPrice = calculateOrderPrice(tempOrder);
			}

			orderHistory.orderedDataVector.push_back(tempOrder); // 주문한 메뉴의 데이터를 주문내역에 추가

			orderHistory.totalPrice = calculateTotalPrice(orderHistory); // 주문내역의 총가격 계산

			command = CONTINUE;
		}

		// <주문 계속 선택단계>
		if(command == CONTINUE || (command == GO_BACK && previous_process == ORDER_CONTINUE_SELECT)){

			printOrderList(orderHistory); // 주문내역 출력

			while(true){
				// 주문 계속 여부를 물어봄
				command = selectMenuProcessOption(orderHistory); // 선후조건 : CONTINUE, CANCEL, END

				if(command==CONTINUE){ // 추가 주문을 선택한 경우
					printContinueOrderProcess();
					finishedProcessStack.push_back(ORDER_CONTINUE_SELECT);
					break;
				}

				else if(command==CANCEL){ // 주문 취소를 선택한 경우
					cancelOrderProcess(orderHistory);
					printOrderList(orderHistory);
				}

				else{ // command==END 주문 종료를 선택한 경우
					printEndOrderProcess(orderHistory);
					return END;
				}
			}

		}
	}
}

// 사용자가 메뉴종류를 선택하면 그에 맞는 정수형을 반환
int selectMenuList(){

	std::vector<std::string> menuList{"엽기메뉴", "엽기닭발메뉴","세트메뉴", "사이드메뉴"};
	int menuListSize{static_cast<int>(menuList.size())};

	std::cout << '\n' << "-----------------------------"<< '\n';
	std::cout << "<메뉴종류를 선택합니다.>"<< '\n'<< '\n';

	while(true){

		for(int i{0}; i<menuListSize; ++i){
			std::cout << "  " << i+1 <<". "<< menuList[i]<< '\n';
		}

		int menuListChoice{-1};
		std::cout << '\n' << "(시작 단계로 돌아가려면 0을 입력)"<< '\n';
		std::cout << "선택하실 메뉴종류의 번호를 입력해주세요: ";
		std::cin >> menuListChoice;

		if(0<=menuListChoice&& menuListChoice<=menuListSize){ // 선택지에 맞는 번호가 입력된 경우
			std::cout << '\n' << "--> ";

			if(menuListChoice == GO_BACK){
				std::cout << "이전 단계로 돌아갑니다." << '\n';
			}

			else{
				std::cout << menuList[menuListChoice-1] << "을(를) 선택하셨습니다." << '\n';
			}
			return menuListChoice;
		}

		else{ // 잘못된 입력이 들어온 경우
			printInputError();
		}
	}
}

// selectMenuList()에서 선택한 메뉴종류의 int 타입을 그에 맞는 MenuListOptions 열거형으로 변환해주는 함수
MenuListOptions changeType_To_MenuListOptions(int selectedMenuList){
	if(selectedMenuList==1){
		return YUPPGY_MENU;
	}
	else if(selectedMenuList==2){
		return CHICKEN_FEET_MENU;
	}
	else if(selectedMenuList==3){
		return SET_MENU;
	}
	else{ // selectedMenuList==4
		return SIDE_MENU;
	}
}

// 선택한 메뉴의 총가격(메뉴의 가격 + 추가한 토핑 가격)을 계산하여 총가격을 정수형으로 반환
int calculateOrderPrice(OrderedData& order){
	int orderPrice{0};

	if(order.isSetMenu){ // 세트메뉴인 경우
		orderPrice += order.orderedSetMenu.orderedSetMenuData->setPrice; // 세트메뉴의 가격을 더함

		int optionSize{static_cast<int>(order.orderedSetMenu.selectedOptions.size())}; // 해당 세트메뉴의 선택가능한 옵션 개수

		for(int i{0}; i<optionSize ; ++i){
			OrderMenuData& OptionData{order.orderedSetMenu.selectedOptions[i]};
			int optionToppingSize{static_cast<int>(OptionData.orderedToppingsVector.size())};

			for(int j{0}; j<optionToppingSize ; ++j){ // 해당 옵션에 추가된 토핑의 가격을 더함
				orderPrice += OptionData.orderedToppingsVector[j]->price;
			}
		}
	}

	else{ // 일반 메뉴인 경우
		orderPrice += order.orderedMenu.orderedMenuData->price;  // 메뉴의 가격을 더함

		std::vector<MenuData*>& MenuToppings{order.orderedMenu.orderedToppingsVector};
		int toppingSize{static_cast<int>(MenuToppings.size())};

		for(int i{0}; i<toppingSize; ++i){// 해당 메뉴에 추가된 토핑의 가격을 더함
			orderPrice += MenuToppings[i]->price;
		}
	}

	return orderPrice;
}


// 주문내역의 각 주문에 대한 가격을 계산하여 총가격을 정수형으로 반환
int calculateTotalPrice(TotalOrderHistory& orderHistory){
	int totalPrice{0};
	int orderSize{static_cast<int>(orderHistory.orderedDataVector.size())}; // 주문내역에 추가된 주문의 개수

	for(int i{0}; i<orderSize; ++i){
		if(orderHistory.orderedDataVector[i].isSetMenu){ // 세트메뉴인 경우
			totalPrice+=orderHistory.orderedDataVector[i].orderedSetMenu.orderedSetMenuPrice;
		}
		else{ // 일반메뉴인 경우
			totalPrice+=orderHistory.orderedDataVector[i].orderedMenu.orderedPrice;
		}
	}
	return totalPrice;
}





// 현재까지의 주문내역(주문된 메뉴들 + 총가격)을 출력함
void printOrderList(TotalOrderHistory& orderHistory){

	std::vector<std::string> spicyLevel{"착한맛", "초보맛","덜매운맛", "오리지널", "매운맛"};

	int orderHistorySize{static_cast<int>(orderHistory.orderedDataVector.size())};

	std::cout << '\n'<< "________________________________"<< '\n';
	std::cout << "<주문내역>"<< '\n' << '\n';

	if(orderHistorySize > 0){

		for(int i{0}; i<orderHistorySize; ++i ){

			if(orderHistory.orderedDataVector[i].isSetMenu){ // 세트메뉴인 경우

				OrderSetMenuData& orderSetMenu{orderHistory.orderedDataVector[i].orderedSetMenu};
				std::cout <<' ' << i+1 <<". "<< orderSetMenu.orderedSetMenuData->setMenuName<< " (+" <<  orderSetMenu.orderedSetMenuData->setPrice <<"원)" << '\n';

				// 해당 세트메뉴에서 선택한 옵션 출력
				int optionSize{static_cast<int>(orderSetMenu.selectedOptions.size())}; // 선택가능한 옵션의 개수
				std::cout << '\n' << "  [선택된 옵션]" << '\n';

				for(int j{0}; j<optionSize; ++j){
					OrderMenuData& OptionData{orderSetMenu.selectedOptions[j]};

					std::cout << "   (" << j+1<<") " << OptionData.orderedMenuData->menuName;

					// 해당 옵션에 선택된 매운맛 단계 출력
					SpicyLevel selectedSpicyLevel{OptionData.orderedSpicy};
					if(selectedSpicyLevel != NONE){ // 옵션에 매운맛 단계가 선택된 경우
						std::cout << " ["<< spicyLevel[selectedSpicyLevel-1] << "] ";
					}
					std::cout << '\n';

					// 해당 옵션에 추가된 토핑출력
					int toppingSize{static_cast<int>(OptionData.orderedToppingsVector.size())}; // 해당 옵션에 추가된 토핑개수
					for(int k{0}; k<toppingSize; ++k){
						std::cout << "     + " << makeString_SelectedMenu(*(OptionData.orderedToppingsVector[k])) << '\n';
					}
				}

				// 해당 세트메뉴의 기본 옵션 출력
				std::cout << '\n' << "  [기본 옵션]" << '\n';
				int defalutSize{static_cast<int>(orderSetMenu.orderedSetMenuData->menuDefalutVector.size())};

				for(int j{0}; j<defalutSize;++j){
					std::cout << "   (" << j+1<<") " << orderSetMenu.orderedSetMenuData->menuDefalutVector[j]->menuName << '\n';
				}

				std::cout << '\n'<< "  금액: " << orderSetMenu.orderedSetMenuPrice << "원" << '\n' << '\n';
			}

			else{ // 일반메뉴인 경우
				OrderMenuData& orderMenu{orderHistory.orderedDataVector[i].orderedMenu};
				std::cout <<' ' << i+1 <<". "<< makeString_SelectedMenu(*(orderMenu.orderedMenuData)) ;

				SpicyLevel selectedSpicyLevel{orderMenu.orderedSpicy};
				if(selectedSpicyLevel != NONE){ // 매운맛 단계가 선택된 경우
					std::cout << " ["<< spicyLevel[selectedSpicyLevel-1] << "] ";
				}
				std::cout << '\n';

				// 해당 메뉴에 추가한 토핑 출력
				int toppingSize{static_cast<int>(orderMenu.orderedToppingsVector.size())};
				for(int k{0}; k<toppingSize; ++k){
					std::cout << "     + " << makeString_SelectedMenu(*(orderMenu.orderedToppingsVector[k])) << '\n';
				}
				std::cout << '\n' << "  금액: " << orderMenu.orderedPrice << "원" << '\n' << '\n';
			}

		}

		std::cout << " =>[총금액: " << orderHistory.totalPrice << "원]" << '\n';

	}
	else{
		std::cout << '\n' << "- 주문된 메뉴가 없습니다." << '\n';
	}
	std::cout << '\n'<< "________________________________"<< '\n';
}


// 해당 메뉴의 이름과 가격을 하나의 문자열로 만들어 반환함
std::string makeString_SelectedMenu(MenuData& selectedMenu, bool isSelectOptionProcess){
	std::string str1;

	if(isSelectOptionProcess){ // 옵션선택의 경우 추가 가격이 들지 않으므로 +0원
		str1 =  selectedMenu.menuName + " (+ 0원)";
	}
	else{
		str1 =  selectedMenu.menuName + " (+" +std::to_string(selectedMenu.price)+ "원)";
	}

	return str1;
}


// 메뉴 선택이 끝나고 사용자에게 주문을 계속할지를 물어보고 그에 맞는 ProgramCommand를 반환함
ProgramCommand selectMenuProcessOption(TotalOrderHistory& orderHistory){
	std::vector<std::string> menuProcessOption{"추가로 메뉴 선택하기", "주문 종료하기", "선택한 주문 취소하기"};
	int menuProcessOptionSize{static_cast<int>(menuProcessOption.size())};

	int orderHistorySize{static_cast<int>(orderHistory.orderedDataVector.size())};

	while(true){
		std::cout << '\n'<<  "-----------------------------"<< '\n';
		std::cout << "<주문을 계속할지 선택합니다.>"<< '\n'<< '\n';

		for(int i{0}; i<menuProcessOptionSize; ++i ){
			std::cout<< "  " <<i+1<<". " << menuProcessOption[i];

			if(i==2 && orderHistorySize==0){ // 주문내역에 메뉴가 없는 경우
				std::cout<< "[선택불가: 취소할 메뉴가 없습니다.]" ;
			}
			std::cout << '\n';
		}


		int menuProcessChoice{-1};
		std::cout << '\n' << "위의 선택지에 맞는 번호를 입력해주세요: ";
		std::cin >> menuProcessChoice;


		if(1<=menuProcessChoice && menuProcessChoice<=menuProcessOptionSize){

			if(menuProcessChoice== CANCEL && orderHistorySize==0){ // 주문 취소를 선택했는데 주문내역에 메뉴가 없는 경우
				printInputError();
			}

			else{
				std::cout << '\n' << "--> ";
				std::cout << menuProcessOption[menuProcessChoice-1] << "을(를) 선택하셨습니다." << '\n';
				if(menuProcessChoice == CONTINUE){
					return CONTINUE;
				}
				else if(menuProcessChoice == END){
					return END;
				}
				else{
					return CANCEL;
				}
			}
		}

		else{
			printInputError();
		}
	}
}


// 사용자가 취소하려고 하는 주문을 주문내역에서 삭제함
void cancelOrderProcess(TotalOrderHistory& orderHistory){

	printOrderList(orderHistory); // 주문내역 출력

	int cancelMenuChoice;
	cancelMenuChoice = selectMenu_To_Cancel(orderHistory); // 주문내역에서 취소할 메뉴를 선택
	if(cancelMenuChoice != GO_BACK){
		orderHistory.orderedDataVector.erase(orderHistory.orderedDataVector.begin() + cancelMenuChoice -1);
		std::cout << '\n' <<  "[선택하신 메뉴가 정상적으로 삭제되었습니다.]" << '\n';
	}
}


// 사용자에게 주문내역중에 취소하고 싶은 메뉴를 선택하게하고 그에 맞는 정수형을 반환함
int selectMenu_To_Cancel(TotalOrderHistory& orderHistory){

	int orderHistorySize{static_cast<int>(orderHistory.orderedDataVector.size())};

	while(true){
		int cancelMenuChoice{-1};

		std::cout << '\n' << "<메뉴를 취소합니다.>";
		std::cout << '\n'<< "(이전 단계로 돌아가려면 0을 입력)"<< '\n';
		std::cout << "위의 주문내역에서 취소할 메뉴의 번호를 입력해주세요.";
		std::cin >> cancelMenuChoice;

		if(0<=cancelMenuChoice && cancelMenuChoice<=orderHistorySize){
			std::cout <<'\n' << "-->";
			if(cancelMenuChoice == GO_BACK){
				std::cout << "이전 단계로 돌아갑니다." << '\n'<< '\n';
				return cancelMenuChoice;
			}
			else{
				OrderedData& orderData{orderHistory.orderedDataVector[cancelMenuChoice-1]};
				if(orderHistory.orderedDataVector[cancelMenuChoice-1].isSetMenu){ // 세트메뉴인 경우
					std::cout <<  orderData.orderedSetMenu.orderedSetMenuData->setMenuName << "을(를) 선택하셨습니다." << '\n';
				}
				else{ // 일반메뉴인 경우
					std::cout <<  orderData.orderedMenu.orderedMenuData->menuName << "을(를) 선택하셨습니다." << '\n';
				}

				return cancelMenuChoice;
			}
		}

		else{
			printInputError();
		}
	}
}

// 사용자가 추가로 메뉴를 선택한다고 했을 때, 안내문구를 출력함
void printContinueOrderProcess(){
	std::cout << '\n' << "[현재까지의 주문내역을 저장하고 메뉴종류 선택단계로 돌아갑니다.]" << '\n';
}


// 사용자가 주문을 종료한다고 했을 때, 최종주문내역을 출력함
void printEndOrderProcess(TotalOrderHistory& orderHistory){
	std::cout << '\n' << "[최종주문내역을 출력합니다.]";
	printOrderList(orderHistory);
	std::cout << '\n' << "[시작메뉴로 돌아갑니다.]" << '\n';
}

