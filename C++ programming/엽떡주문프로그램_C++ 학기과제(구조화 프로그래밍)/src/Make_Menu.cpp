//============================================================================
// Name        : Make_Menu.cpp
// Description : 메뉴 데이터를 구성하는데 필요한 함수를 정의한 소스파일입니다.
//============================================================================

#include <iostream>
#include <string>
#include <cstdlib>
#include <vector>
#include "menu.h"
using namespace std;


// 일반메뉴(세트메뉴를 제외)의 데이터를 하나의 2차원 벡터(AllMenuData)에 담음
void makeMenu(std::vector<std::vector<MenuData>>& AllMenuData){

	std::vector<std::vector<std::string>> DataOf_MenuNameVector{ // 모든 메뉴의 이름 데이터를 담는 벡터
		{"엽기 떡볶이", "엽기 오뎅","엽기 반반", "엽기 닭볶음탕","2인 엽기떡볶이", "엽기 로제떡볶이", "엽기 로제오뎅", "엽기 로제반반"}, // 엽기메뉴

		{"엽기 통닭발", "엽기 무뼈닭발","엽기 오돌뼈", "엽기 닭날개", "엽기 국물닭발"}, // 엽기 닭발메뉴

		{"주먹김밥", "계란찜", "계란야채죽", "치즈죽", "오뎅탕", "엽도그[1개]", "바삭치즈만두[7개]",
				"모둠튀김[야채1 + 김말이1 + 만두2]", "김말이[3개]", "야채튀김[1개]","튀김만두[4개]", "순대[300g]",
				"공깃밥", "버터꿀봉 달콤치즈", "버터꿀봉 매콤땡초", "고추맵봉 달콤치즈", "고추맵봉 매콤땡초", "음료[유산균] 450ml"},// SIDE 메뉴

		{"치즈", "햄[7개]", "베이컨", "계란[2개]", "메추리알[5개]","퐁당치즈만두", "우동사리",
				"당면사리", "중국당면", "떡추가", "오뎅추가"}, //토핑

	};

	std::vector<std::vector<int>> DataOf_MenuPriceVector{// 모든 메뉴의 가격 데이터를 담는 벡터
		{14000, 14000, 14000, 24000, 9000, 16000, 16000, 16000}, // 엽기메뉴

		{14000, 15000, 14000, 14000, 15000}, // 엽기 닭발메뉴

		{2000, 2000, 5000, 6000, 6000, 2000, 2000, 2000, 2000, 1000, 2000, 3000, 1000,
				11000, 11000, 11000, 11000, 1000}, // SIDE 메뉴

		{3000,1000,3000,1500,1000,2000,2000,2000,2500,1000,1000} // 토핑
	};


	int menuListCount{static_cast<int>(DataOf_MenuNameVector.size())};
	for(int i{0}; i<menuListCount;++i){
		int menuCount{static_cast<int>(DataOf_MenuNameVector[i].size())};

		for(int j{0}; j<menuCount;++j){
			MenuData tempMenuData;
			tempMenuData.menuName = DataOf_MenuNameVector[i][j];
			tempMenuData.price = DataOf_MenuPriceVector[i][j];
			AllMenuData[i].push_back(tempMenuData);
		}
	}

	// 선택할 수 있는 매운맛 단계 데이터 추가
	putSelectableSpicyLevel(AllMenuData[YUPPGY_MENU]); // 엽기메뉴만 매운맛 선택 가능

	// 선택할 수 있는 토핑 데이터 추가
	putSelectableToppings(AllMenuData);

}


// 메뉴데이터에 선택가능한 매운맛 단계들을 추가함
void putSelectableSpicyLevel(std::vector<MenuData>& MenuListData){

	int MenuListDataSize{static_cast<int>(MenuListData.size())}; // 메뉴종류에 포함된 메뉴의 개수

	for(int i{0}; i<MenuListDataSize; ++i){
		if(MenuListData[i].menuName=="2인 엽기떡볶이"){ // 초보맛 선택 불가
			MenuListData[i].selectableSpicyLevelVector = {KIND, LESS_SPICY, ORIGINAL, VERY_SPICY};
			continue;
		}
		else if(MenuListData[i].menuName.substr(0,9)=="엽기 로제"){ // "엽기 로제"로 시작하는 메뉴는 착한맛과 오리지널만 선택 가능
			MenuListData[i].selectableSpicyLevelVector = {KIND, ORIGINAL};
			continue;
		}
		MenuListData[i].selectableSpicyLevelVector = {KIND, BEGINNER, LESS_SPICY, ORIGINAL, VERY_SPICY};
	}

}


// 메뉴데이터에 선택가능한 토핑들의 데이터를 추가함
void putSelectableToppings(std::vector<std::vector<MenuData>>& AllMenuData){

	int toppingMenuSize{static_cast<int>(AllMenuData[TOPPING].size())}; // 토핑 메뉴의 개수

	// <엽기메뉴 토핑데이터 추가>
	int yuppgyMenuSize{static_cast<int>(AllMenuData[YUPPGY_MENU].size())}; // 엽기메뉴에 해당하는 메뉴의 개수

	for(int i{0}; i<yuppgyMenuSize; ++i){

		if(AllMenuData[YUPPGY_MENU][i].menuName =="엽기 닭볶음탕"){ // 엽기 닭볶음탕은 떡, 오뎅추가가 불가능함

			for(int j{0}; j<toppingMenuSize-2;++j){ // 떡추가, 오뎅추가는  각각 AllMenuData[TOPPING]의 맨뒤에 위치하여 toppingMenuSize-2를 사용
				AllMenuData[YUPPGY_MENU][i].selectableToppingVector.push_back(&AllMenuData[TOPPING][j]);
			}
		}

		else{
			for(int j{0}; j<toppingMenuSize;++j){
				AllMenuData[YUPPGY_MENU][i].selectableToppingVector.push_back(&AllMenuData[TOPPING][j]);
			}
		}
	}

	// <엽기 닭발메뉴 토핑데이터 추가>
	int chickenFeetMenuSize{static_cast<int>(AllMenuData[CHICKEN_FEET_MENU].size())}; // 엽기 닭발메뉴에 해당하는 메뉴의 개수

	for(int i{0}; i<chickenFeetMenuSize; ++i){ // 엽기닭발메뉴는 치즈, 햄, 베이컨, 계란, 메추리알만 추가 가능

		for(int j{0}; j<5;++j){ // AllMenuData[TOPPING][0] ~ [5]가 위의 토핑들임
			AllMenuData[CHICKEN_FEET_MENU][i].selectableToppingVector.push_back(&AllMenuData[TOPPING][j]);
		}

		if(AllMenuData[CHICKEN_FEET_MENU][i].menuName =="엽기 국물닭발"){ // 엽기 국물닭발은 떡추가 가능
			AllMenuData[CHICKEN_FEET_MENU][i].selectableToppingVector.push_back(&AllMenuData[TOPPING][9]); // AllMenuData[TOPPING][9] : 떡추가
		}
	}
}


// 세트메뉴의 데이터들을 하나의 1차원 벡터(AllsetMenuData)에 담음
void makeSetMenu(std::vector<std::vector<MenuData>>& AllMenuData, std::vector<SetMenuData>& AllsetMenuData){

	std::vector<std::string> DataOf_SetMenuNameVector{
		"A set[(엽떡 or 엽오 or 반반) + 모둠튀김 + (계란 or 메추리알)]",
		"B set[(엽떡 or 엽오 or 반반) + 모둠튀김 + (계란 or 메추리알) + 주먹김밥]",
		"C set[(엽떡 or 엽오 or 반반) + 모둠튀김 + (계란 or 메추리알) + 주먹김밥 + 당면]",
		"Family set[(엽떡 or 엽오 or 반반) + 엽기닭발메뉴 중 택1 + 주먹김밥]",
		"엽기닭발 set[엽기 닭발메뉴 중 택 1 + 주먹김밥]"
	};

	std::vector<int> DataOf_SetMenuPriceVector{
		17000, 19000, 21000, 28000, 16000
	};

	int setMenuCount{static_cast<int>(DataOf_SetMenuNameVector.size())}; // 세트메뉴의 개수

	for(int i{0}; i<setMenuCount; ++i){
		SetMenuOptions setMenu{static_cast<SetMenuOptions>(i)};

		AllsetMenuData[i].setMenuName = DataOf_SetMenuNameVector[i];

		AllsetMenuData[i].setPrice = DataOf_SetMenuPriceVector[i];

		putSetMenuOption(AllMenuData, AllsetMenuData[i], setMenu); // 세트메뉴의 옵션들에 대한 데이터 추가

		putSetMenuDefalut(AllMenuData, AllsetMenuData[i], setMenu); // 세트메뉴에서 기본으로 제공되는 메뉴들에 대한 데이터 추가
	}

}



// 세트메뉴에 해당하는 옵션들을 세트 메뉴 데이터에 추가함
void putSetMenuOption(std::vector<std::vector<MenuData>>& AllMenuData, SetMenuData& setMenuData, SetMenuOptions setMenu){

	switch (setMenu){
	case A_Set: case B_Set: case C_Set:
		setMenuData.menuOptionsVector={
				// 엽기떡볶이, 엽기오뎅, 엽기반반
				{AllMenuData[YUPPGY_MENU][0], AllMenuData[YUPPGY_MENU][1],AllMenuData[YUPPGY_MENU][2]},
				// 계란(2개), 메추리알(5)
				{AllMenuData[TOPPING][3], AllMenuData[TOPPING][4]}
		};
		break;

	case Family_Set:
		setMenuData.menuOptionsVector = {
				// 엽기떡볶이, 엽기오뎅, 엽기반반
				{AllMenuData[YUPPGY_MENU][0], AllMenuData[YUPPGY_MENU][1],AllMenuData[YUPPGY_MENU][2]},
				// 닭발메뉴
				{AllMenuData[CHICKEN_FEET_MENU][0], AllMenuData[CHICKEN_FEET_MENU][1],
						AllMenuData[CHICKEN_FEET_MENU][2], AllMenuData[CHICKEN_FEET_MENU][3]}
		};
		break;

	case Yuppgy_Chicken_Feet_Set:
		setMenuData.menuOptionsVector={
				// 닭발메뉴
				{AllMenuData[CHICKEN_FEET_MENU][0], AllMenuData[CHICKEN_FEET_MENU][1],
						AllMenuData[CHICKEN_FEET_MENU][2], AllMenuData[CHICKEN_FEET_MENU][3]}
		};
		break;
	}
}


// 세트메뉴에 해당하는 기본 메뉴들을 세트 메뉴 데이터에 추가함
void putSetMenuDefalut(std::vector<std::vector<MenuData>>& AllMenuData, SetMenuData& setMenuData, SetMenuOptions setMenu){

	switch (setMenu){

	case A_Set:
		setMenuData.menuDefalutVector = {// 모둠튀김
				&AllMenuData[SIDE_MENU][7]
		};
		break;

	case B_Set:
		setMenuData.menuDefalutVector = {// 모둠튀김, 주먹김밥
				&AllMenuData[SIDE_MENU][7], &AllMenuData[SIDE_MENU][0]
		};
		break;

	case C_Set:
		setMenuData.menuDefalutVector = {// 모둠튀김, 주먹김밥, 당면
				&AllMenuData[SIDE_MENU][7], &AllMenuData[SIDE_MENU][0], &AllMenuData[TOPPING][8]
		};
		break;

	case Family_Set: case Yuppgy_Chicken_Feet_Set:
		setMenuData.menuDefalutVector = {// 주먹김밥
				&AllMenuData[SIDE_MENU][0]
		};
		break;
	}
}


