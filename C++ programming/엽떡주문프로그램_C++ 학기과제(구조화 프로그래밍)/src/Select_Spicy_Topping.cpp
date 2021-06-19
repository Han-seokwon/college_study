//============================================================================
// Name        : Select_Spicy_Topping.cpp
// Description : 선택한 메뉴에 대한 매운맛 단계를 선택하고, 토핑을 추가할 때 필요한 함수를 정의한 소스파일
//============================================================================

#include "menu.h"


// 사용자가 선택한 매운맛단계에 맞는 SpicyLevel 열거형을 반환
SpicyLevel selectSpicyLevel(MenuData& selectedMenu){

	std::vector<std::string> spicyLevel{"착한맛", "초보맛","덜매운맛", "오리지널", "매운맛"};

	int selectableSpicyLevelSize{static_cast<int>(selectedMenu.selectableSpicyLevelVector.size())}; // 사용자가 선택한 메뉴에서 고를 수 있는 매운맛 단계의 수

	while(true){
		std::cout << '\n'<< "-----------------------------"<< '\n';
		std::cout << "<매운맛을 선택합니다.>"<< '\n' << '\n';

		for(int i{0}; i<selectableSpicyLevelSize; ++i){ // 사용자가 선택한 메뉴에서 고를 수 있는 매운맛 단계를 하나씩 출력
			SpicyLevel spicy{selectedMenu.selectableSpicyLevelVector[i]};
			std::cout << "  " << i+1 <<". "<< spicyLevel[spicy-1]<< '\n';
		}
		int spicyChoice{-1};
		std::cout << '\n' << "(이전 단계로 돌아가려면 0을 입력)"<<'\n';
		std::cout << "선택하실 매운맛의 번호를 입력해주세요: ";
		std::cin >> spicyChoice;


		if(0<=spicyChoice&& spicyChoice<=selectableSpicyLevelSize){ //선택지에 맞는 번호가 입력된 경우
			std::cout << '\n' << "--> ";
			if(spicyChoice == GO_BACK){
				std::cout <<  "메뉴 선택 단계로 돌아갑니다." << '\n';
				return NONE;
			}
			else{
				SpicyLevel selectedSpicyLevel{selectedMenu.selectableSpicyLevelVector[spicyChoice-1]};
				std::cout << spicyLevel[selectedSpicyLevel-1]<<  "을(를) 선택하셨습니다." << '\n';
				return selectedSpicyLevel;
			}
		}

		else{ // 잘못된 입력이 들어온 경우
			printInputError();
		}
	}
}



// 토핑추가단계의 진행(새로운 토핑을 추가, 추가한 토핑을 취소, 토핑 추가 단계 종료)을 결정하고, 결정된 기능을 수행함
ProgramCommand selectToppingProcess(MenuData& selectedMenu, std::vector<MenuData*>& orderedToppingsVector){

	while(true){
		ProgramCommand command;

		command = selectToppingProcessOption(orderedToppingsVector);

		if(command==GO_BACK){ // 이전 단계로 돌아가는 경우

			std::vector<MenuData*> emptyToppingsVector;
			orderedToppingsVector = emptyToppingsVector; // 현재까지 저장된 토핑 데이터를 지움

			return GO_BACK;
		}

		else if(command==END){ // 토핑 추가 단계 종료
			return CONTINUE;
		}

		else if(command==CANCEL){ // 토핑 취소 선택
			cancelToppingProcess(selectedMenu, orderedToppingsVector);
			continue;
		}

		else if(command==CONTINUE){ // 토핑 추가 선택

			int toppingChoice;
			toppingChoice = selectTopping(selectedMenu); // 추가할 토핑을 선택하게 함

			if(toppingChoice==GO_BACK){ // 사용자가 이전 단계로 돌아가려는 경우
				continue;
			}

			orderedToppingsVector.push_back(selectedMenu.selectableToppingVector[toppingChoice-1]); // 선택한 토핑을 주문 데이터에 추가함

			printAddedToppings(selectedMenu, orderedToppingsVector); // 현재까지 추가된 토핑을 출력
		}
	}
}




// 사용자가 (이전 단계로 돌아가기, 토핑 추가, 추가한 토핑 취소, 토핑 추가종료) 중에서 선택하게하고 그에 맞는 ProgramCommand 열거형을 반환
ProgramCommand selectToppingProcessOption(std::vector<MenuData*>& orderedToppingsVector){

	std::vector<std::string> toppingProcessOption{"새로운 토핑 추가하기", "토핑 추가 그만하기", "추가한 토핑 취소하기"};
	int toppingProcessOptionSize{static_cast<int>(toppingProcessOption.size())};

	int orderedToppingsSize{static_cast<int>(orderedToppingsVector.size())}; // 현재까지 추가된 토핑의 개수

	while(true){
		std::cout << '\n' << "-----------------------------"<< '\n';
		std::cout << "<토핑 추가 단계>"<< '\n' << '\n';

		for(int i{0}; i<toppingProcessOptionSize;++i ){
			std::cout<< "  " <<i+1<<". " << toppingProcessOption[i];

			if(i+1==CONTINUE && orderedToppingsSize==5){ // 추가한 토핑이 5개인 경우 더 추가할 수 없음
				std::cout<< " [선택불가: 토핑을 더 추가할 수 없습니다].)";
			}

			if(i+1==CANCEL && orderedToppingsSize==0){ // 추가한 토핑이 없는 경우 토핑을 취소할 수 없음
				std::cout<< " [선택불가: 추가한 토핑이 없습니다.]";
			}
			std::cout<< '\n';
		}

		int toppingProcessChoice{-1};
		std::cout << '\n' << "(이전 단계로 돌아가려면 0을 입력)"<<'\n';
		std::cout << "선택하실 기능의 번호를 입력해주세요: ";
		std::cin >> toppingProcessChoice;

		if(0<=toppingProcessChoice&& toppingProcessChoice<=toppingProcessOptionSize){

			ProgramCommand command{static_cast<ProgramCommand>(toppingProcessChoice)};
			if(command == GO_BACK){
				std::cout << '\n' << "--> " << "이전 단계로 돌아갑니다." << '\n';
				return command;
			}
			else if(command == CONTINUE && orderedToppingsSize==5){
				printInputError();
			}
			else if(command == CANCEL && orderedToppingsSize==0){
				printInputError();
			}
			else{
				std::cout<< '\n' << "--> " <<  toppingProcessOption[toppingProcessChoice-1]<<  "을(를) 선택하셨습니다." << '\n';
				return command;
			}
		}

		else{
			printInputError();
		}
	}
}


// 사용자가 선택한 메뉴에 추가할 수 있는 토핑을 고르면 그에 맞는 정수형을 반환
int selectTopping(MenuData& selectedMenu){

	int selectableToppingSize{static_cast<int>(selectedMenu.selectableToppingVector.size())}; // 해당메뉴에서 선택할 수 있는 토핑의 개수

	while(true){
		std::cout << '\n'<< "-----------------------------"<< '\n';
		std::cout << "<토핑을 선택합니다.>"<< '\n' << '\n';

		for(int i{0}; i<selectableToppingSize; ++i ){
			std::cout<< "  " <<i+1<<". " << makeString_SelectedMenu(*(selectedMenu.selectableToppingVector[i]))<< '\n';
		}

		int toppingChoice{-1};
		std::cout << '\n' << "(이전 단계로 돌아가려면 0을 입력)"<<'\n';
		std::cout << "선택하실 토핑의 번호를 입력해주세요: ";
		std::cin >> toppingChoice;


		if(0<=toppingChoice&& toppingChoice<=selectableToppingSize){
			std::cout << '\n' << "--> ";
			if(toppingChoice == GO_BACK){
				std::cout << "메뉴 선택 단계로 돌아갑니다." << '\n';
				return toppingChoice;
			}
			else{
				std::cout << makeString_SelectedMenu(*(selectedMenu.selectableToppingVector[toppingChoice-1])) <<  "을(를) 선택하셨습니다." << '\n';
				return toppingChoice;
			}
		}
		else{
			printInputError();
		}
	}
}


// 사용자에게 현재 메뉴에 추가된 토핑들과 앞으로 추가할 수 있는 토핑의 개수를 보여줌
void printAddedToppings(MenuData& selectedMenu, std::vector<MenuData*>& orderedToppingsVector){

	const int MAX_TOPPING{5}; // 최대로 추가할 수 있는 토핑의 개수
	int orderedToppingsSize{static_cast<int>(orderedToppingsVector.size())}; // 현재까지 추가된 토핑의 개수

	std::cout <<'\n' <<  "-----------------------------"<< '\n';
	std::cout << "현재까지 [" <<  makeString_SelectedMenu(selectedMenu) << "]에 추가된 토핑" << '\n' << '\n';

	for(int i{0}; i<orderedToppingsSize;++i ){
		std::cout<< "  " <<i+1<<". " << makeString_SelectedMenu(*(orderedToppingsVector[i]))<< '\n';
	}

	std::cout << '\n';
	if(orderedToppingsSize<MAX_TOPPING){
		std::cout << "앞으로 " << MAX_TOPPING - orderedToppingsSize << "번 더 토핑을 추가할 수 있습니다." << '\n';
	}
	else{
		std::cout << "토핑을 "<< MAX_TOPPING <<"번 모두 추가했습니다." << '\n';
	}

}

// 사용자가 선택한 토핑을 주문데이터에서 삭제함
void cancelToppingProcess(MenuData& selectedMenu, std::vector<MenuData*>& orderedToppingsVector){
	int selectedTopping_To_Cancel;
	selectedTopping_To_Cancel=selectTopping_To_Cancel(selectedMenu, orderedToppingsVector);

	if(selectedTopping_To_Cancel != GO_BACK){
	orderedToppingsVector.erase(orderedToppingsVector.begin() + selectedTopping_To_Cancel-1); // 사용자가 선택한 토핑을 주문데이터에서 삭제
	}

}

// 사용자에게 취소할 토핑을 선택하게하고 그에 맞는 정수형을 반환
int selectTopping_To_Cancel(MenuData& selectedMenu, std::vector<MenuData*>& orderedToppingsVector){

	int orderedToppingsSize{static_cast<int>(orderedToppingsVector.size())}; // 현재까지 추가된 토핑의 개수

	while(true){
		std::cout << '\n' << "-----------------------------"<< '\n';
		std::cout << "<토핑을 취소합니다.>"<< '\n';
		std::cout << "현재까지 [" <<  makeString_SelectedMenu(selectedMenu) << "]에 추가된 토핑" << '\n' << '\n';

		for(int i{0}; i<orderedToppingsSize;++i ){
			std::cout<< "  " <<i+1<<". " << makeString_SelectedMenu(*(orderedToppingsVector[i]))<< '\n';
		}

		int topping_To_Cancel_Choice{-1};
		std::cout << '\n' << "(이전 단계로 돌아가려면 0을 입력)" << '\n';
		std::cout << "취소하실 토핑의 번호를 입력해주세요: ";
		std::cin >> topping_To_Cancel_Choice;


		if(0<=topping_To_Cancel_Choice&& topping_To_Cancel_Choice<=orderedToppingsSize){
			std::cout << '\n' << "--> ";
			if(topping_To_Cancel_Choice == GO_BACK){
				std::cout << "이전 단계로 돌아갑니다." << '\n';
				return topping_To_Cancel_Choice;
			}
			else{
				std::cout << makeString_SelectedMenu(*(orderedToppingsVector[topping_To_Cancel_Choice-1])) <<  "을(를) 취소합니다." << '\n';
				return topping_To_Cancel_Choice;
			}
		}
		else{
			printInputError();
		}
	}
}
