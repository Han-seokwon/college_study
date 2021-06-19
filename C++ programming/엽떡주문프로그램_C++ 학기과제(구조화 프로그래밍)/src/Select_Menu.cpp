//============================================================================
// Name        : Select_Menu.cpp
// Description : 메뉴를 선택하는 과정에 필요한 함수를 정의한 소스파일
//============================================================================


#include "menu.h"


// 메뉴 선택과정(메뉴 선택-> 매운맛 선택 -> 토핑 추가)를 실행, 세트메뉴 옵션을 선택할 때도 사용됨
ProgramCommand selectMenuProcess(OrderMenuData& orderMenuData, std::vector<MenuData>& selectedMenuListData, bool isSelectOptionProcess){

	ProgramCommand command{CONTINUE}; // 각 단계를 어떻게 실행할 것인지에 대한 명령

	OrderProcess previous_process;

	std::vector<OrderProcess> finishedProcessStack; // 종료된 단계의 정보를 저장하는 스택

	while(command!=END){

		if(command == GO_BACK){ // 사용자가 이전단계로 돌아가려는 경우
			previous_process = lastProcess(finishedProcessStack); // 이전으로 돌아갈 단계를 찾음
		}

		// <메뉴 선택단계>
		if(command == CONTINUE || (command == GO_BACK && previous_process == OrderProcess::MENU_SELECT)){ // 정상 실행 or command가 이전단계이고, 이전단계가 메뉴선택 단계인 경우

			int selectedMenu;
			selectedMenu=selectMenu(selectedMenuListData, isSelectOptionProcess);

			if(selectedMenu == GO_BACK){
				return GO_BACK; // 메뉴종류 선택 단계로 돌아감
			}

			orderMenuData.orderedMenuData = &selectedMenuListData[selectedMenu-1]; // 주문 데이터에 선택한 메뉴정보 추가

			finishedProcessStack.push_back(OrderProcess::MENU_SELECT); // 현재 종료된 단계를 스택에 push

			command = CONTINUE; // 이후 단계는 정상적으로 진행
		}


		// <매운맛 선택 단계>
		if(command == CONTINUE || (command == GO_BACK && previous_process == OrderProcess::SPICY_SELECT)){

			int selectableSpicyLevelSize{static_cast<int>(orderMenuData.orderedMenuData->selectableSpicyLevelVector.size())}; // 선택한 메뉴에서 선택가능한 매운맛 단계의 개수

			if(0<selectableSpicyLevelSize){ // 매운맛 선택이 가능한 경우


				SpicyLevel selectedSpicyLevel;
				selectedSpicyLevel = selectSpicyLevel(*(orderMenuData.orderedMenuData));

				if(selectedSpicyLevel == SpicyLevel::NONE){// 사용자 이전단계로 돌아간다고한 경우
					command = GO_BACK;
					continue;
				}

				else{
					orderMenuData.orderedSpicy = selectedSpicyLevel; // 주문데이터에 매운맛 정보 추가
				}

				finishedProcessStack.push_back(OrderProcess::SPICY_SELECT);

				command = CONTINUE;
			}
		}

		// <토핑 추가 단계>
		if(command == CONTINUE || (command == GO_BACK && previous_process == OrderProcess::TOPPING_SELECT)){

			int selectableToppingSize{static_cast<int>(orderMenuData.orderedMenuData->selectableToppingVector.size())}; // 선택한 메뉴에서 선택가능한 토핑의 개수

			if(0<selectableToppingSize){ // 토핑 추가가 가능한 경우

				// 사용자로부터 토핑을 입력받아 주문 데이터에 토핑 추가
				command = selectToppingProcess(*(orderMenuData.orderedMenuData), orderMenuData.orderedToppingsVector); // 선후조건 : GO_BACK or CONTINUE

				if(command==GO_BACK){
					continue;
				}

				finishedProcessStack.push_back(OrderProcess::TOPPING_SELECT);

				command = CONTINUE;
			}
		}

		if(isSelectOptionProcess){ // 옵션메뉴 선택과정인 경우
			return CONTINUE;
		}

		// 현재까지 선택한 메뉴데이터를 주문데이터에 추가할 것인지를 물어봄
		command = selectPutMenu_Or_GoBack(); // 선후 조건 : GO_BACK or END
	}

	return END; // 메뉴 선택단계 종료
}


// 메뉴종류에 맞는 메뉴들 중에서 사용자가 선택한 메뉴에 맞는 정수형을 반환
int selectMenu(std::vector<MenuData>& selectedMenuList, bool isSelectOptionProcess){

	int menuSize{static_cast<int>(selectedMenuList.size())}; // 메뉴종류에 해당하는 메뉴 개수

	while(true){
		std::cout << '\n'<< "-----------------------------"<< '\n';
		std::cout << "<메뉴를 선택합니다.>"<< '\n' << '\n';

		for(int i{0}; i<menuSize; ++i){
			std::cout<< "  " <<i+1<<". " << makeString_SelectedMenu(selectedMenuList[i], isSelectOptionProcess) << '\n';
		}

		int menuChoice{-1};
		if(isSelectOptionProcess){
			std::cout << '\n' << "(이전 단계로 돌아가려면 0을 입력 [2번째 옵션 선택부터는 이전 옵션 선택 단계로 돌아감])"<< '\n';
		}
		else{
			std::cout << '\n' << "(이전 단계로 돌아가려면 0을 입력)"<< '\n';
		}
		std::cout << "선택하실 메뉴의 번호를 입력해주세요: ";
		std::cin >> menuChoice;

		if(0<=menuChoice && menuChoice<=menuSize){ // 선택지에 맞는 번호가 입력된 경우
			std::cout << '\n' << "--> ";

			if(menuChoice == GO_BACK){
				std::cout << "이전 단계로 돌아갑니다." << '\n';
			}

			else{
				std::cout << makeString_SelectedMenu(selectedMenuList[menuChoice-1], isSelectOptionProcess) << "을(를) 선택하셨습니다." << '\n';
			}

			return menuChoice;
		}

		else{// 잘못된 입력이 들어온 경우
			printInputError();
		}
	}
}


// 최종적으로 메뉴를 주문데이터에 추가할 것인지를 물어보고 그에 맞는 ProgramCommand을 반환함
ProgramCommand selectPutMenu_Or_GoBack(){

	int putMenuChoice{-1};
	std::vector<std::string> putMenuOption{"이전 단계로 돌아가기", "주문내역에 메뉴 추가하기"};
	int putMenuOptionSize{static_cast<int>(putMenuOption.size())};

	while(true){
		std::cout << '\n'<< "-----------------------------"<< '\n';
		std::cout << "현재까지 선택한 메뉴정보를 주문내역에 추가하시겠습니까?" << '\n' << '\n';
		for(int i{0}; i<putMenuOptionSize; ++i){
			std::cout << ' ' << i <<". "<< putMenuOption[i]<< '\n';
		}

		std::cout << '\n' <<  "위의 선택지에 맞는 번호를 입력해주세요: ";
		std::cin >> putMenuChoice;

		if(0 <= putMenuChoice && putMenuChoice < putMenuOptionSize){
			std::cout << '\n' << "--> ";
			if(putMenuChoice == GO_BACK){
				std::cout << "이전단계로 돌아갑니다." << '\n';
				return GO_BACK;
			}
			else{
				std::cout << "메뉴정보를 추가했습니다." << '\n';
				return END;
			}
		}
		else{
			printInputError();
		}
	}
}

//  종료된 단계의 정보를 저장하는 스택에서 이전에 실행한 단계를 찾아서 반환함
OrderProcess lastProcess(std::vector<OrderProcess>& finishedProcessStack){
	OrderProcess previous_process;

	int finishedProcessStackSize{static_cast<int>(finishedProcessStack.size())};

	if(finishedProcessStackSize > 0){ // 이전에 실행한 단계를 스택에서 꺼냄
		previous_process = finishedProcessStack[finishedProcessStackSize-1];

		finishedProcessStack.erase(finishedProcessStack.begin() + finishedProcessStackSize - 1);

		return previous_process;
	}
	else{
		return NA;
	}
}



// <<<< 세트메뉴 >>>>

// 세트 메뉴 선택 과정(세트 메뉴선택 -> 옵션 선택)을 실행
ProgramCommand selectSetMenuProcess(OrderSetMenuData& orderSetMenu, std::vector<SetMenuData>& AllSetMenuData){

	ProgramCommand command{CONTINUE};  // 각 단계를 어떻게 실행할 것인지에 대한 명령, (CONTINUE: 정상실행)
	OrderProcess previous_process; //  이전에 실행한 단계
	std::vector<OrderProcess> finishedProcessStack; // 종료된 단계의 정보를 저장하는 스택

	int optionCnt{0}; // 현재 선택하고 있는 옵션의 순서
	int menuOptionSize;

	while(command!=END){

		if(command == GO_BACK){ // 사용자가 이전단계로 돌아가려는 경우
			previous_process = lastProcess(finishedProcessStack);// 이전으로 돌아갈 단계를 찾음
		}

		// <세트메뉴 선택>
		if((command == CONTINUE ) || (command == GO_BACK && previous_process == OrderProcess::MENU_SELECT)){ // 정상 실행이거나, 이전으로 돌아가려는 단계가 "메뉴선택" 단계인 경우에 이 단계를 실행함

			int selectedSetMenu;
			selectedSetMenu = selectSetMenu(AllSetMenuData); // 세트 메뉴를 선택

			if(selectedSetMenu==GO_BACK){
				return GO_BACK; // 메뉴종류 선택 단계로 돌아감
			}

			orderSetMenu.orderedSetMenuData = &AllSetMenuData[selectedSetMenu-1]; // 주문데이터에 선택된 세트메뉴 추가

			finishedProcessStack.push_back(OrderProcess::MENU_SELECT); // 현재 종료된 단계를 스택에 push

			menuOptionSize = static_cast<int>(orderSetMenu.orderedSetMenuData->menuOptionsVector.size()); // 세트메뉴의 옵션의 개수

			command = CONTINUE;

		}


		// <옵션선택>
		while(optionCnt < menuOptionSize){ // 모든 옵션의 선택을 마칠 때까지 반복

			if((command == CONTINUE ) || (command == GO_BACK && previous_process == OrderProcess::OPTION_SELECT)){

				if(command == GO_BACK){ // 뒤로 가기로 이 단계를 실행한 경우 이전에 선택한 옵션데이터를 삭제함
					orderSetMenu.selectedOptions.erase(orderSetMenu.selectedOptions.begin() + optionCnt);
				}

				OrderMenuData tempOrderMenuData;
				bool isSelectOptionProcess{true};

				std::cout << '\n' <<  "[세트메뉴의 " << optionCnt+1 << "번째 옵션을 선택합니다.]" ;

				// 옵션 선택과정(옵션 선택 -> 매운맛 선택 -> 토핑 추가)을 진행
				command = selectMenuProcess(tempOrderMenuData ,orderSetMenu.orderedSetMenuData->menuOptionsVector[optionCnt], isSelectOptionProcess); // 선후 조건 GO_BACK or CONTINUE

				if(command==GO_BACK){
					if(optionCnt==0){ // 첫번째 옵션 선택 단계인 경우, 이전 단계는 세트메뉴 선택 단계임
						break;
					}
					else{
						optionCnt-=1; // 이전 옵션 선택으로 돌아감
						break;
					}
				}

				orderSetMenu.selectedOptions.push_back(tempOrderMenuData);

				finishedProcessStack.push_back(OrderProcess::OPTION_SELECT);

				optionCnt+=1;
			}

		}

		// 현재까지 선택한 메뉴데이터를 주문데이터에 추가할 것인지를 물어봄
		if(command == CONTINUE){
			command = selectPutMenu_Or_GoBack(); // 선후 조건 : GO_BACK or END
			if(command==GO_BACK){
				optionCnt -= 1;
			}
		}

	}
	return END;
}


// 사용자가 선택한 세트메뉴에 맞는 정수형을 반환
int selectSetMenu(std::vector<SetMenuData>& AllSetMenuData){

	int setMenuSize{static_cast<int>(AllSetMenuData.size())}; // 세트메뉴의 개수

	while(true){
		std::cout << '\n' << "-----------------------------"<< '\n';
		std::cout << "세트메뉴를 선택합니다."<< '\n' << '\n';
		for(int i{0}; i<setMenuSize; ++i){
			std::cout<< ' ' <<i+1<<". " << AllSetMenuData[i].setMenuName << " (+" <<  AllSetMenuData[i].setPrice <<"원)" << '\n';
		}

		int setMenuChoice{-1};
		std::cout << '\n' << "(이전 단계로 돌아가려면 0을 입력)"<< '\n';
		std::cout << "선택하실 세트메뉴의 번호를 입력해주세요: ";
		std::cin >> setMenuChoice;

		if(0<=setMenuChoice && setMenuChoice<=setMenuSize){

			std::cout << '\n' << "--> ";
			if(setMenuChoice == GO_BACK){
				std::cout << "메뉴종류 선택 단계로 돌아갑니다." << '\n';
			}

			else{
				std::cout << AllSetMenuData[setMenuChoice-1].setMenuName << " (" <<
						AllSetMenuData[setMenuChoice-1].setPrice <<"원)" << "을(를) 선택하셨습니다." << '\n';
			}

			return setMenuChoice;
		}

		else{
			printInputError();
		}
	}


}


