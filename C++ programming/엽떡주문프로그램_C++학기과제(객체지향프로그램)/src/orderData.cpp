//============================================================================
// Name        : orderData.cpp
// Description : 주문데이터를 처리하는 함수, 클래스를 정의한 소스파일입니다.
//============================================================================


#include <iostream>
#include <vector>
#include <stdexcept>
#include "Order.h"

std::string WRONGINPUT_ERROR_MESSAGE{"\n경고: 잘못된 번호를 입력했습니다. 선택지에 맞는 번호를 입력해주세요.\n"};

// 최대로 추가할 수 있는 토핑의 개수
const int MAX_TOPPING_COUNT{5};


extern std::vector<MainMenuData> mainMenu_DataList;
extern std::vector<SetMenuData> setMenu_DataList;
extern std::vector<OtherMenuData> sideMenu_DataList;
extern std::vector<OtherMenuData> toppingMenu_DataList;


// MainMenu_OrderData 클래스

int MainMenu_OrderData::get_ordered_MainMenuID() const noexcept{
	return ordered_MainMenuID;
}

int MainMenu_OrderData::get_Ordered_Price() const noexcept{
	return ordered_Price;
}

SpicyLevel MainMenu_OrderData::get_Ordered_SpicyLevel() const noexcept{
	return ordered_SpicyLevel;
}

const std::vector<int>& MainMenu_OrderData::get_ordered_ToppingIDList() const noexcept{
	return ordered_ToppingIDList;
}

// 메인메뉴의 인덱스를 받아 주문된 메뉴와 가격을 설정
void MainMenu_OrderData::set_ordered_MainMenuID_Price(int ordered_MenuID){
	if(0 <= ordered_MenuID && ordered_MenuID < static_cast<int>(mainMenu_DataList.size())){
		ordered_MainMenuID = ordered_MenuID;
		ordered_Price = mainMenu_DataList[ordered_MenuID].get_Price();
	}
	else{
		throw std::invalid_argument{WRONGINPUT_ERROR_MESSAGE};
	}
}

void MainMenu_OrderData::set_SpicyLevel(int ordered_SpicyNum){

	std::vector<SpicyLevel> temp_selectable_SpicyLevels = mainMenu_DataList[ordered_MainMenuID].get_selectable_SpicyLevelList();

	if(0 <= ordered_SpicyNum && ordered_SpicyNum < static_cast<int>(temp_selectable_SpicyLevels.size())){
		ordered_SpicyLevel = temp_selectable_SpicyLevels[ordered_SpicyNum];
	}
	else{
		throw std::invalid_argument{WRONGINPUT_ERROR_MESSAGE};
	}
}

// 사용자가 주문한 토핑을 추가
void MainMenu_OrderData::add_Ordered_ToppingID(int ordered_toppingNum){
	if(static_cast<int>(ordered_ToppingIDList.size()) < MAX_TOPPING_COUNT){
		std::vector<int> temp_selectable_ToppingIDList = mainMenu_DataList[ordered_MainMenuID].get_selectable_ToppingIDList();
		if(0 <= ordered_toppingNum && ordered_toppingNum < static_cast<int>(temp_selectable_ToppingIDList.size())){
			ordered_ToppingIDList.push_back(temp_selectable_ToppingIDList[ordered_toppingNum]);
			// 주문된 토핑의 가격 추가
			ordered_Price += toppingMenu_DataList[temp_selectable_ToppingIDList[ordered_toppingNum]].get_Price();
		}
		else{
			throw std::invalid_argument{WRONGINPUT_ERROR_MESSAGE};
		}
	}
	else{
		throw std::length_error{"\n경고: 토핑은 최대 " + std::to_string(MAX_TOPPING_COUNT) + "개까지만 추가할 수 있습니다.\n"};
	}

}

// 주문된 토핑들을 모두 삭제함(뒤로가기할 때 사용)
void MainMenu_OrderData::clear_Ordered_ToppingIDList(){
	std::vector<int> empty_ToppingList;
	ordered_ToppingIDList = empty_ToppingList;

	// 토핑을 뺀 원래 메뉴가격으로 초기화
	ordered_Price = mainMenu_DataList[ordered_MainMenuID].get_Price();
}



// SetMenu_OrderData 클래스

int SetMenu_OrderData::get_ordered_SetMenuID() const noexcept{
	return ordered_SetMenuID;
}

int SetMenu_OrderData::get_Ordered_Price() const noexcept{
	return ordered_Price;
}

const std::vector<int>& SetMenu_OrderData::get_ordered_MainMenu_OptionIDList() const noexcept{
	return ordered_MainMenu_OptionIDList;
}

const std::vector<MainMenu_OrderData>& SetMenu_OrderData::get_Ordered_MainMenu_OptionList() const noexcept{
	return ordered_MainMenu_OptionList;
}

const std::vector<MenuID>& SetMenu_OrderData::get_Ordered_OtherMenu_OptionList() const noexcept{
	return ordered_OtherMenu_OptionList;
}



void SetMenu_OrderData::set_ordered_SetMenuID_Price(int ordered_MenuID){
	if(0 <= ordered_MenuID && ordered_MenuID < static_cast<int>(setMenu_DataList.size())){
		ordered_SetMenuID = ordered_MenuID;
		ordered_Price = setMenu_DataList[ordered_MenuID].get_Price();
	}
	else{
		throw std::invalid_argument{"경고: 입력하신 번호에 맞는 세트메뉴가 존재하지 않습니다."};
	}
}

// 사용자가 메인메뉴 옵션 중에 특정 번호를 입력하면 그에 맞는 메인메뉴의 id를 추가함
void SetMenu_OrderData::add_Ordered_MainMenu_OptionIDList(int ordered_mainMenu_OptionNum){
	int idx{static_cast<int>(ordered_MainMenu_OptionIDList.size())};
	std::vector<int> selectable_MainMenuID_Option =  setMenu_DataList[ordered_SetMenuID].get_selectable_MainMenuID_OptionList()[idx];
	if(0<= ordered_mainMenu_OptionNum && ordered_mainMenu_OptionNum < static_cast<int>(selectable_MainMenuID_Option.size())){
		ordered_MainMenu_OptionIDList.push_back(selectable_MainMenuID_Option[ordered_mainMenu_OptionNum]);
	}
	else{
		throw std::invalid_argument{"경고: 입력하신 번호에 맞는 옵션이 존재하지 않습니다."};
	}
}




// 주문한(매운맛, 토핑을 추가한) 메인메뉴 옵션을 주문정보에 추가함
void SetMenu_OrderData::add_Ordered_MainMenu_Options(const MainMenu_OrderData& ordered_mainMenu_Options){
	ordered_MainMenu_OptionList.push_back(ordered_mainMenu_Options);

	// 해당 메인 메뉴에서 토핑을 추가한 경우 그만큼 가격 추가
	// 토핑 포함 가격 - 원래 가격 =  토핑 가격
	ordered_Price += ordered_mainMenu_Options.get_Ordered_Price() - mainMenu_DataList[ordered_mainMenu_Options.get_ordered_MainMenuID()].get_Price();
}

// 사용자가 주문한 기타 메뉴 옵션을 주문정보에 추가함
void SetMenu_OrderData::add_Ordered_OtherMenu_Options(int ordered_other_OptionNum){
	int ordered_OtherMenu_OptionList_Size{static_cast<int>(ordered_OtherMenu_OptionList.size())};
	// 현재 선택할 수 있는 기타메뉴 옵션
	std::vector<MenuID> temp_selectable_OtherMenuID_Options = setMenu_DataList[ordered_SetMenuID].get_selectable_OtherMenuID_OptionList()[ordered_OtherMenu_OptionList_Size];

	if(0 <= ordered_other_OptionNum && ordered_other_OptionNum < static_cast<int>(temp_selectable_OtherMenuID_Options.size())){
		ordered_OtherMenu_OptionList.push_back(temp_selectable_OtherMenuID_Options[ordered_other_OptionNum]);
	}
	else{
		throw std::invalid_argument{"경고: 잘못된 옵션 번호가 입력되었습니다."};
	}
}

// 주문된 옵션들을 모두 삭제함(뒤로가기할 때 사용)
void SetMenu_OrderData::clear_all_OptionList(){
	std::vector<int> empty_ordered_MainMenu_OptionIDList;
	std::vector<MainMenu_OrderData> empty_ordered_MainMenu_OptionList;
	std::vector<MenuID> empty_ordered_OtherMenu_OptionList;

	ordered_MainMenu_OptionIDList = empty_ordered_MainMenu_OptionIDList;
	ordered_MainMenu_OptionList = empty_ordered_MainMenu_OptionList;
	ordered_OtherMenu_OptionList = empty_ordered_OtherMenu_OptionList;
}

// 주문된 메인 메뉴 옵션들 중 가장 뒤의 원소를 삭제하고 반환(뒤로가기할 때 사용)
MainMenu_OrderData SetMenu_OrderData::pop_ordered_MainMenu_OptionList(){
	int size{static_cast<int>(ordered_MainMenu_OptionList.size())};
	MainMenu_OrderData temp_MainMenu_OrderData = ordered_MainMenu_OptionList[size -1];
	// 가장 뒤의 원소 삭제
	ordered_MainMenu_OptionList.erase(ordered_MainMenu_OptionList.begin() + size);
	return temp_MainMenu_OrderData;
}


// OrderList 클래스

int OrderList::get_total_Ordered_Price() const noexcept{
	return total_Ordered_Price;
}

const std::vector<MainMenu_OrderData>& OrderList::get_Ordered_MainMenuList() const noexcept{
	return ordered_MainMenuList;
}

const std::vector<SetMenu_OrderData>& OrderList::get_Ordered_SetMenuList() const noexcept{
	return ordered_SetMenuList;
}

const std::vector<int>& OrderList::get_Ordered_SideMenuIDList() const noexcept{
	return ordered_SideMenuIDList;
}


// 주문된 메인 메뉴를 주문내역에 추가함
void OrderList::add_Ordered_MainMenu(const MainMenu_OrderData& ordered_Menu){
	ordered_MainMenuList.push_back(ordered_Menu);
	total_Ordered_Price += ordered_Menu.get_Ordered_Price();
}

// 주문된 세트메뉴를 주문내역에 추가함
void OrderList::add_Ordered_SetMenu(const SetMenu_OrderData& ordered_SetMenu){
	ordered_SetMenuList.push_back(ordered_SetMenu);
	total_Ordered_Price += ordered_SetMenu.get_Ordered_Price();
}

// 주문된 사이드메뉴를 주문내역에 추가함
void OrderList::add_Ordered_SideMenuID(int ordered_SideMenuID){
	if(0 <= ordered_SideMenuID && ordered_SideMenuID < static_cast<int>(sideMenu_DataList.size())){
		ordered_SideMenuIDList.push_back(ordered_SideMenuID);
		total_Ordered_Price += sideMenu_DataList[ordered_SideMenuID].get_Price();
	}
	else{
		throw std::invalid_argument{WRONGINPUT_ERROR_MESSAGE};
	}
}

// 사용자가 취소한 메뉴를 주문내역에서 삭제함
void OrderList::cancel_Ordered_Menu(MenuType menutype, int menu_num){
	int mainMenuList_Size{static_cast<int>(ordered_MainMenuList.size())};
	int setMenuList_Size{static_cast<int>(ordered_SetMenuList.size())};
	int sideMenuList_Size{static_cast<int>(ordered_SideMenuIDList.size())};

	if(0 < menu_num ){
		switch(menutype){
		case MenuType::MAIN:
			if(menu_num <= mainMenuList_Size){
				total_Ordered_Price -= ordered_MainMenuList[ menu_num - 1].get_Ordered_Price(); // 메뉴가 빠지면 그 가격을 총 가격에서 빼줌
				ordered_MainMenuList.erase(ordered_MainMenuList.begin() + menu_num - 1); // 주문 리스트에서도 삭제
			}
			else{
				throw std::invalid_argument{"경고: 입력하신 메뉴 번호가 존재하지 않습니다."};
			}
			break;
		case MenuType::SET:
			if(menu_num <= setMenuList_Size){
				total_Ordered_Price -= ordered_SetMenuList[ menu_num - 1].get_Ordered_Price();
				ordered_SetMenuList.erase(ordered_SetMenuList.begin() + menu_num - 1);
			}
			else{
				throw std::invalid_argument{"경고: 입력하신 메뉴 번호가 존재하지 않습니다."};
			}
			break;

		case MenuType::SIDE:
			if(menu_num <= sideMenuList_Size){
				total_Ordered_Price -= sideMenu_DataList[ordered_SideMenuIDList[ menu_num - 1]].get_Price();
				ordered_SideMenuIDList.erase(ordered_SideMenuIDList.begin() + menu_num - 1);
			}
			else{
				throw std::invalid_argument{"경고: 입력하신 메뉴 번호가 존재하지 않습니다."};
			}
			break;

		default:
			throw std::invalid_argument{"경고: 잘못된 메뉴 종류 입력입니다."};
		}
	}
	else{
		throw std::invalid_argument{"경고: 입력하신 메뉴 번호가 존재하지 않습니다."};
	}
}














