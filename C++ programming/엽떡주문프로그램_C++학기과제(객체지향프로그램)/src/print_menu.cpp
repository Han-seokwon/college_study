//============================================================================
// Name        : print_menu.cpp
// Description : 출력과 연관있는 함수를 정의한 소스파일
//============================================================================

#include <iostream>
#include <iomanip>
#include "Order.h"

extern std::vector<MainMenuData> mainMenu_DataList;
extern std::vector<SetMenuData> setMenu_DataList;
extern std::vector<OtherMenuData> sideMenu_DataList;
extern std::vector<OtherMenuData> toppingMenu_DataList;

const std::vector<std::string> spicyLevel ={"착한맛", "초보맛","덜매운맛", "오리지널", "매운맛"};

// 해당 메뉴를 이름+가격으로 출력
std::string string_Menu_Name_Price(const MenuData& menu){
	std::string str1 = menu.get_MenuName() + " (" + std::to_string(menu.get_Price()) + " 원)";
	return str1;
}

void print_StartProgram(){
	std::cout<< "\n=====================================[ 시작 메뉴 ]======================================\n" << "\n";
	std::vector<std::string> menuType{"주문 시작", "프로그램 종료"};
	for(int i{0}; i< static_cast<int>(menuType.size()); ++i){
		std::cout<< "(";
		std::cout.flags(std::ios::right);
		std::cout.width(2);
		std::cout << i+1 << ") ";
		std::cout.flags(std::ios::left);
		std::cout.width(15);
		std::cout << menuType[i];
		std::cout<< "\t";
	}
	std::cout<< "\n\n" ;
	std::cout<< " >> 번호 입력: ";
}



void print_MenuType(){
	std::cout<< "\n=====================================[ 메인 종류 선택 ]======================================\n" << "\n";
	std::cout<< "                                                              [101] 이전 단계로 돌아가기\n" << "\n";
	std::vector<std::string> menuType{"메인 메뉴", "세트 메뉴", "사이드 메뉴"};
	for(int i{0}; i< static_cast<int>(menuType.size()); ++i){
		std::cout<< "(";
		std::cout.flags(std::ios::right);
		std::cout.width(2);
		std::cout << i+1 << ") ";
		std::cout.flags(std::ios::left);
		std::cout.width(15);
		std::cout << menuType[i];
		std::cout<< "\t";
	}
	std::cout<< "\n\n" ;
	std::cout<< "(이전 단계로 돌아갈 경우 주문 내역이 초기화 됩니다.)\n" ;
	std::cout<< " >> 번호 입력: ";
}



void print_MainMenu(){
	std::cout<< "\n=====================================[ 메인 메뉴 선택 ]======================================\n" << "\n";
	std::cout<< "                                                              [101] 이전 단계로 돌아가기\n" << "\n";
	for(int i{0}; i< static_cast<int>(mainMenu_DataList.size()); ++i){
		std::cout<< "(";
		std::cout.flags(std::ios::right);
		std::cout.width(2);
		std::cout << i+1 << ") ";
		std::cout.flags(std::ios::left);
		std::cout.width(25);
		std::cout << string_Menu_Name_Price(mainMenu_DataList[i]);
		std::cout<< "\t";
		if(i%3 == 2 || i+1 == static_cast<int>(mainMenu_DataList.size())){
			std::cout<< "\n" ;
		}
	}
	std::cout<< "\n" ;
	std::cout<< " >> 번호 입력: ";
}

void print_Selectable_SpicyLevel(const MainMenuData& mainMenu){
	std::cout<< "\n=====================================[ "<< mainMenu.get_MenuName()<< "의 매운맛 선택 ]======================================\n" << "\n";
	std::cout<< "                                                              [101] 이전 단계로 돌아가기\n" << "\n";

	std::vector<SpicyLevel> selectable_SpicyLevel = mainMenu.get_selectable_SpicyLevelList();
	for(int i{0}; i< static_cast<int>(selectable_SpicyLevel.size()); ++i){
		std::cout<< "(";
		std::cout.flags(std::ios::right);
		std::cout.width(2);
		std::cout << i+1 << ") ";
		std::cout << spicyLevel[static_cast<int>(selectable_SpicyLevel[i]) - 1];
		std::cout<< "\n" ;
	}
	std::cout<< "\n" ;
	std::cout<< " >> 번호 입력: ";
}

void print_Selectable_ToppingMenu(const MainMenuData& mainMenu){
	std::cout<< "\n======================================[ "<< mainMenu.get_MenuName() <<"의 토핑 선택 ]=======================================\n" << "\n";
	std::cout<< "                                                              [101] 이전 단계로 돌아가기\n";
	std::cout<< "                                                              [103] 토핑 선택 안 함\n" << "\n";

	const std::vector<int> selectable_ToppingIDList = mainMenu.get_selectable_ToppingIDList();

	for(int i{0}; i< static_cast<int>(selectable_ToppingIDList.size()); ++i){
		std::cout<< "(";
		std::cout.flags(std::ios::right);
		std::cout.width(2);
		std::cout << i+1 << ") ";
		std::cout.flags(std::ios::left);
		std::cout.width(25);
		std::cout << string_Menu_Name_Price(toppingMenu_DataList[selectable_ToppingIDList[i]]);
		std::cout<< "\t";
		if(i%3 == 2 || i+1 == static_cast<int>(selectable_ToppingIDList.size())){
			std::cout<< "\n" ;
		}
	}
	std::cout<< "\n" ;
	std::cout<< "(5개까지 입력 가능 | 예: 1 1 3 -> 치즈 2개, 베이컨 1개)" << "\n";
	std::cout<< " >> 번호 입력: ";
}

// 주문된 메인 메뉴를 출력(주문 확인)
void print_Confirm_MainMenu(const MainMenu_OrderData& MainMenu_order){

	std::cout<< "\n_______________________________________( 메인 메뉴 주문 내용 확인 )________________________________________\n";
	std::cout<< "\n[ 선택하신 아래의 메뉴를 주문내역에 추가합니다. ] \n\n";

	std::cout<< "   - ";
	// 주문한 메뉴 출력
	print_Ordered_MainMenu(MainMenu_order);

	// 선택지 출력
	print_Confirm_OrderedMenu();
	std::cout<< "\n\n";
	std::cout<< "(이전단계로 돌아가는 경우 추가한 위의 토핑들은 사라집니다.)" << "\n";
	std::cout<< " >> 번호 입력: ";
}

void print_Ordered_MainMenu(const MainMenu_OrderData& MainMenu_order, bool isOptionPrint){
	// 주문한 메뉴 출력
	std::cout << mainMenu_DataList[MainMenu_order.get_ordered_MainMenuID()].get_MenuName();
	if(MainMenu_order.get_Ordered_SpicyLevel() != SpicyLevel::NONE){
		std::cout << " [" << spicyLevel[static_cast<int>(MainMenu_order.get_Ordered_SpicyLevel()) - 1] <<"]";
	}
	if(!isOptionPrint){
		std::cout << " ( " << mainMenu_DataList[MainMenu_order.get_ordered_MainMenuID()].get_Price() << "원 )";
	}
	std::cout << "\n";

	// 주문된 토핑 출력
	print_Ordered_Toppings(MainMenu_order.get_ordered_ToppingIDList());
}


// 주문된 토핑들 출력
void print_Ordered_Toppings(const std::vector<int>& ordered_ToppingIDList){
	for(int i{0}; i< static_cast<int>(ordered_ToppingIDList.size()); ++i){
		std::cout<< "       + ";
		std::cout << string_Menu_Name_Price(toppingMenu_DataList[ordered_ToppingIDList[i]]) << "\n";

	}
}

// 주문 확인 선택지를 출력
void print_Confirm_OrderedMenu(){
	// 선택지 출력
	std::vector<std::string> menuConfirm{"이전 단계로 돌아가기", "주문 내역에 추가하기"};
	for(int i{0}; i< static_cast<int>(menuConfirm.size()); ++i){
		std::cout<< "(";
		std::cout.flags(std::ios::right);
		std::cout.width(2);
		std::cout << i+1 << ") ";
		std::cout.flags(std::ios::left);
		std::cout.width(15);
		std::cout << menuConfirm[i];
		std::cout<< "\t";
	}
}




void print_SetMenu(){
	std::cout<< "\n=====================================[ 세트 메뉴 선택 ]======================================\n" << "\n";
	std::cout<< "                                                              [101] 이전 단계로 돌아가기\n" << "\n";
	for(int i{0}; i< static_cast<int>(setMenu_DataList.size()); ++i){
		std::cout<< "(";
		std::cout.flags(std::ios::right);
		std::cout.width(2);
		std::cout << i+1 << ") ";
		std::cout << string_Menu_Name_Price(setMenu_DataList[i]);
		std::cout<< "\n" ;
	}
	std::cout<< "\n" ;
	std::cout<< " >> 번호 입력: ";
}


// 해당 세트메뉴의 선택가능한 옵션을 출력
void print_Selectable_Options(const SetMenuData& setMenu){
	std::cout<< "\n======================================[ 옵션 선택 ]=======================================\n" << "\n";
	std::cout<< "                                                              [101] 이전 단계로 돌아가기\n" << "\n";

	std::cout<< " "<< setMenu.get_MenuName() <<"의 선택가능한 옵션 \n\n";

	std::vector<std::vector<int>> selectable_MainMenuID_OptionList = setMenu.get_selectable_MainMenuID_OptionList();
	std::vector<std::vector<MenuID>> selectable_OtherMenuID_OptionList = setMenu.get_selectable_OtherMenuID_OptionList();

	int selectable_size = static_cast<int>(selectable_MainMenuID_OptionList.size() + selectable_OtherMenuID_OptionList.size());

	for(int i{0}; i< selectable_size; ++i){
		std::cout<< " [ 옵션 " << i+1 << "선택 ]" << "\n";
		// 메인 메뉴 옵션 출력
		if(i < static_cast<int>(selectable_MainMenuID_OptionList.size())){
			for(int j{0}; j<static_cast<int>(selectable_MainMenuID_OptionList[i].size()); ++j){
				std::cout<< "  (";
				std::cout.flags(std::ios::right);
				std::cout.width(2);
				std::cout << j+1 << ") ";
				std::cout << string_Menu_Name_Price(mainMenu_DataList[selectable_MainMenuID_OptionList[i][j]]);
				std::cout<< "\n";
			}
		}
		// 기타 메뉴 옵션 출력
		else{
			int idx{i - static_cast<int>(selectable_OtherMenuID_OptionList.size())};
			for(int j{0}; j<static_cast<int>(selectable_OtherMenuID_OptionList[idx].size()); ++j){
				int Menu_idx{selectable_OtherMenuID_OptionList[idx][j].id};
				std::cout<< "  (";
				std::cout.flags(std::ios::right);
				std::cout.width(2);
				std::cout << j+1 << ") ";
				if(selectable_OtherMenuID_OptionList[idx][j].menuType == MenuType::SIDE ){
					std::cout << sideMenu_DataList[Menu_idx].get_MenuName();
				}
				else if(selectable_OtherMenuID_OptionList[idx][j].menuType == MenuType::TOPPING ){
					std::cout << toppingMenu_DataList[Menu_idx].get_MenuName();
				}
				std::cout<< "\n";
			}
		}
		std::cout<< "\n";
	}
	std::cout<< "(각 옵션의 번호 선택 | 예: 2 3 -> 옵션1의 2번, 옵션2의 3번)" << "\n";
	std::cout<< " >> 번호 입력: ";
}


// 주문된 세트 메뉴를 출력(주문 확인)
void print_Confirm_SetMenu(const SetMenu_OrderData& Ordered_setMenu){
	std::cout<< "\n_______________________________________( 세트메뉴 주문 내용 확인 )________________________________________\n";
	std::cout<< "\n[ 선택하신 아래의 메뉴를 주문내역에 추가합니다. ] \n\n";

	//  주문된세트메뉴 출력
	std::cout << "  - ";
	print_Ordered_SetMenu(Ordered_setMenu);

	// 선택지 출력
	print_Confirm_OrderedMenu();
	std::cout<< "\n\n";
	std::cout<< "(이전단계로 돌아가는 경우 추가한 위의 토핑들은 사라집니다.)" << "\n";
	std::cout<< " >> 번호 입력: ";
}


// 주문된 세트메뉴를 출력
void print_Ordered_SetMenu(const SetMenu_OrderData& Ordered_setMenu){

	std::cout << setMenu_DataList[Ordered_setMenu.get_ordered_SetMenuID()].get_MenuName() << "( "<< Ordered_setMenu.get_Ordered_Price() << "원 )" << "\n";
	int optionCnt{0};
	// 메인 메뉴 옵션 출력
	for(int j{0}; j< static_cast<int>(Ordered_setMenu.get_Ordered_MainMenu_OptionList().size()); ++j){
		std::cout<< "   [옵션" << optionCnt+1 << "]" << "\n";
		std::cout<< "     - ";
		print_Ordered_MainMenu(Ordered_setMenu.get_Ordered_MainMenu_OptionList()[optionCnt], true);
		++optionCnt;
	}

	// 기타메뉴 옵션 출력
	for(int j{0}; j< static_cast<int>(Ordered_setMenu.get_Ordered_OtherMenu_OptionList().size()); ++j){
		std::cout<< "   [옵션" << optionCnt+1 << "]" << "\n";
		print_Ordered_OtherMenu_Options(Ordered_setMenu.get_Ordered_OtherMenu_OptionList()[j]);
		++optionCnt;
	}

	// 기본 옵션 출력
	std::cout<< "   [기본 옵션]" << "\n";
	std::vector<MenuID> defalutMenuID_OptionList = setMenu_DataList[Ordered_setMenu.get_ordered_SetMenuID()].get_DefalutMenuID_OptionList();
	for(int j{0}; j< static_cast<int>(defalutMenuID_OptionList.size()); ++j){
		print_Ordered_OtherMenu_Options(defalutMenuID_OptionList[j]);
	}
	std::cout << "\n";
}


// 주문내역의 세트메뉴에서 기타 메뉴 옵션 or 기본 옵션을 출력
void print_Ordered_OtherMenu_Options(const MenuID& ordered_Option){
	std::cout<< "     - ";
	if(ordered_Option.menuType == MenuType::SIDE){
		std::cout << sideMenu_DataList[ordered_Option.id].get_MenuName() << "\n";
	}
	else if(ordered_Option.menuType == MenuType::TOPPING){
		std::cout << toppingMenu_DataList[ordered_Option.id].get_MenuName() << "\n";
	}

}



void print_SideMenu(){
	std::cout<< "\n=====================================[ 사이드 메뉴 선택 ]======================================\n" << "\n";
	std::cout<< "                                                              [101] 이전 단계로 돌아가기\n" << "\n";

	for(int i{0}; i< static_cast<int>(sideMenu_DataList.size()); ++i){
		std::cout<< "(";
		std::cout.flags(std::ios::right);
		std::cout.width(2);
		std::cout << i+1 << ") ";
		std::cout.flags(std::ios::left);
		std::cout.width(35);
		std::cout << string_Menu_Name_Price(sideMenu_DataList[i]);
		std::cout << "\t";
		if(i%2 == 1 || i+1 == static_cast<int>(sideMenu_DataList.size())){
			std::cout<< "\n" ;
		}
	}
	std::cout<< "\n" ;
	std::cout<< "(여러 개 입력 가능 | 예: 2 2 5 -> 계란찜 2개, 오뎅탕 1개)" << "\n";
	std::cout<< " >> 번호 입력: ";
}


// 주문내역 출력
void print_OrderList(const OrderList& orderList, bool isOrderEnd){
	if(isOrderEnd){
		std::cout<< "\n\n\n--------------------------------------{ 최종 주문 내역 }--------------------------------------\n\n";
	}
	else{
		std::cout<< "\n______________________________________( 현재까지의 주문 내역 )____________________________________\n" << "\n";
		std::cout<< "                                                                        [102] 주문 취소하기\n";
		std::cout<< "                                                                        [103] 주문 종료하기\n";
		std::cout<< "                                                                        [104] 새로운 메뉴 추가하기\n";
	}


	std::cout<< "{ 1.메인 메뉴 }" <<"\n\n";
	print_Ordered_MainMenuList(orderList.get_Ordered_MainMenuList());

	std::cout<< "{ 2.세트 메뉴 }"<<"\n\n";
	print_Ordered_SetMenuList(orderList.get_Ordered_SetMenuList());

	std::cout<< "{ 3.사이드 메뉴 }"<<"\n\n";
	print_Ordered_SideMenuList(orderList.get_Ordered_SideMenuIDList());

	std::cout << "\n";
	std::cout << " ===> [[총금액: " << orderList.get_total_Ordered_Price() << " 원]]\n\n";

	if(isOrderEnd){
		std::cout<< "\n-------------------------------------------------------------------------------------------\n\n\n";
	}
	else{
		std::cout<< "(취소하려는 경우 메뉴종류 번호 입력| 102 2 1 -> 세트메뉴 1번 취소)" << "\n";
		std::cout<< " >> 번호 입력: ";
	}
}


// 주문내역에서 주문된 메인메뉴들을 출력
void print_Ordered_MainMenuList(const std::vector<MainMenu_OrderData>& mainMenu_orderList){
	for(int i{0}; i< static_cast<int>(mainMenu_orderList.size()); ++i){
		std::cout<< " (";
		std::cout.flags(std::ios::right);
		std::cout.width(2);
		std::cout << i+1 << ") ";
		print_Ordered_MainMenu(mainMenu_orderList[i]);
		std::cout << "\n";
	}
}

// 주문내역에서 주문된 세트메뉴들을 출력
void print_Ordered_SetMenuList(const std::vector<SetMenu_OrderData>& setMenu_orderList){
	for(int i{0}; i< static_cast<int>(setMenu_orderList.size()); ++i){
		std::cout<< " (";
		std::cout.flags(std::ios::right);
		std::cout.width(2);
		std::cout << i+1 << ") ";
		print_Ordered_SetMenu(setMenu_orderList[i]);
	}
}


// 주문내역에서 주문된 사이드메뉴들을 출력
void print_Ordered_SideMenuList(const std::vector<int>& sideMenu_orderList){
	for(int i{0}; i< static_cast<int>(sideMenu_orderList.size()); ++i){
		std::cout<< " (";
		std::cout.flags(std::ios::right);
		std::cout.width(2);
		std::cout << i+1 << ") ";
		std::cout << string_Menu_Name_Price(sideMenu_DataList[sideMenu_orderList[i]]) << "\n";

	}
}


