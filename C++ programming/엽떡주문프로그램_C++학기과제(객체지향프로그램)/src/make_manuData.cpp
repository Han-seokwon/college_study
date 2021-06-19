//============================================================================
// Name        : make_manuData.cpp
// Description : 메뉴데이터와 관련된 클래스, 함수를 정의한 소스파일
//============================================================================

#include <vector>
#include "Order.h"



std::vector<MainMenuData> mainMenu_DataList = {
		MainMenuData{"엽기 떡볶이", 14000}, MainMenuData{"엽기 오뎅", 14000}, MainMenuData{"엽기 반반", 14000},
		MainMenuData{"엽기 닭볶음탕", 24000}, MainMenuData{"2인 엽기떡볶이", 9000}, MainMenuData{"엽기 로제떡볶이", 16000},
		MainMenuData{"엽기 로제오뎅", 16000}, MainMenuData{"엽기 로제반반", 16000}, MainMenuData{"엽기 통닭발", 14000},
		MainMenuData{"엽기 무뼈닭발", 15000}, MainMenuData{"엽기 오돌뼈", 14000} , MainMenuData{"엽기 닭날개", 14000},
		MainMenuData{"엽기 국물닭발", 15000}
};


std::vector<SetMenuData> setMenu_DataList = {
		SetMenuData{"A set[(엽떡 or 엽오 or 반반) + 모둠튀김 + (계란 or 메추리알)]", 17000},
		SetMenuData{"B set[(엽떡 or 엽오 or 반반) + 모둠튀김 + (계란 or 메추리알) + 주먹김밥]", 19000},
		SetMenuData{"C set[(엽떡 or 엽오 or 반반) + 모둠튀김 + (계란 or 메추리알) + 주먹김밥 + 당면]", 21000},
		SetMenuData{"Family set[(엽떡 or 엽오 or 반반) + 엽기닭발메뉴 중 택1 + 주먹김밥]", 28000},
		SetMenuData{"엽기닭발 set[엽기 닭발메뉴 중 택 1 + 주먹김밥]", 16000}
};


std::vector<OtherMenuData> sideMenu_DataList = {
		OtherMenuData{"주먹김밥", 2000}, OtherMenuData{"계란찜", 2000}, OtherMenuData{"계란야채죽", 5000}, OtherMenuData{"치즈죽", 6000},
		OtherMenuData{"오뎅탕", 6000}, OtherMenuData{"엽도그(1개)", 2000}, OtherMenuData{"바삭치즈만두(7개)", 2000},
		OtherMenuData{"모둠튀김", 2000},
		OtherMenuData{"김말이[3개]", 2000}, OtherMenuData{"야채튀김[1개]", 1000}, OtherMenuData{"튀김만두[4개]", 2000}, OtherMenuData{"순대[300g]", 3000},
		OtherMenuData{"공깃밥", 1000}, OtherMenuData{"버터꿀봉 달콤치즈", 11000}, OtherMenuData{"버터꿀봉 매콤땡초", 11000}, OtherMenuData{"고추맵봉 달콤치즈", 11000},
		OtherMenuData{"고추맵봉 매콤땡초", 11000}, OtherMenuData{"음료[유산균] 450ml", 1000}

};

std::vector<OtherMenuData> toppingMenu_DataList = {
		OtherMenuData{"치즈",3000 }, OtherMenuData{"햄[7개]",1000 }, OtherMenuData{"베이컨",3000 },
		OtherMenuData{"계란[2개]",1500 },OtherMenuData{"메추리알[5개]",1000 },
		OtherMenuData{"퐁당치즈만두",2000 }, OtherMenuData{"우동사리",2000 },
		OtherMenuData{"당면사리", 2000 }, OtherMenuData{"중국당면",2000 },
		OtherMenuData{"떡추가", 1000}, OtherMenuData{"오뎅추가", 1000}
};

// 메뉴데이터를 유지하는 클래스 정의

// MenuData 정의
MenuData::MenuData(const std::string& menuName, int price): menuName(menuName), price{price}{ }

int MenuData::get_Price() const noexcept{
	return price;
}

const std::string& MenuData::get_MenuName() const noexcept{
	return menuName;
}

// MainMenuData 정의
MainMenuData::MainMenuData(const std::string& menuName, int price): MenuData(menuName, price){}

const std::vector<SpicyLevel>& MainMenuData::get_selectable_SpicyLevelList() const noexcept{
	return selectable_SpicyLevelList;
}
const std::vector<int>& MainMenuData::get_selectable_ToppingIDList() const noexcept{
	return selectable_ToppingIDList;
}

// 선택가능한 매운맛 단계를 추가함
void MainMenuData::add_Seletable_SpicyLevels(SpicyLevel spicy){
	bool already_Exist{false};
	for(int i{0}; i<static_cast<int>(selectable_SpicyLevelList.size()); ++i){
		if(selectable_SpicyLevelList[i] == spicy){
			already_Exist = true;
			break;
		}
	}
	// 이미 추가한 것이 아닐 경우 push
	if(!already_Exist){
		selectable_SpicyLevelList.push_back(spicy);
	}
}

// 선택가능한 토핑을 추가
void MainMenuData::add_Selectable_ToppingID(int toppingID){
	// 토핑 리스트에 있는 값인지 확인
	if(0 <= toppingID && toppingID < static_cast<int>(toppingMenu_DataList.size())){
		// 이미 추가한 토핑인지 확인
		bool already_Exist{false};
		for(int i{0}; i< static_cast<int>(selectable_ToppingIDList.size()); ++i){
			if(selectable_ToppingIDList[i] == toppingID){
				already_Exist = true;
				break;
			}
		}
		// 이미 추가한 것이 아닐 경우 push
		if(!already_Exist){
			selectable_ToppingIDList.push_back(toppingID);
		}

	}

}


// SetMenuData 정의
SetMenuData::SetMenuData(const std::string& menuName, int price): MenuData(menuName, price){}

const std::vector<std::vector<int>>& SetMenuData::get_selectable_MainMenuID_OptionList() const noexcept{
	return selectable_MainMenuID_OptionList;
}

const std::vector<std::vector<MenuID>>& SetMenuData::get_selectable_OtherMenuID_OptionList() const noexcept{
	return selectable_OtherMenuID_OptionList;
}

const std::vector<MenuID>& SetMenuData::get_DefalutMenuID_OptionList() const noexcept{
	return defalutMenuID_OptionList;
}

// 세트 메뉴의 선택가능한 메인메뉴 옵션을 추가
void SetMenuData::add_Selectable_MainMenuID_Options(const std::vector<int>& selectable_MainMenuID_Option){
	bool is_Vaild_IDs{true};
	for(int i{0}; i < static_cast<int>(selectable_MainMenuID_Option.size()); ++i){
		// 유효한 값인지 검사
		if(0 > selectable_MainMenuID_Option[i] || selectable_MainMenuID_Option[i] >= static_cast<int>(mainMenu_DataList.size())){
			is_Vaild_IDs = false;
		}
	}
	if(is_Vaild_IDs){
		selectable_MainMenuID_OptionList.push_back(selectable_MainMenuID_Option);
	}
}

// 세트 메뉴의 선택가능한 기타메뉴 옵션을 추가
void SetMenuData::add_Selectable_OtherMenuID_Options(const std::vector<MenuID>& selectable_OtherMenuID_Option){
	MenuType menuType{selectable_OtherMenuID_Option[0].menuType};
	bool is_Vaild_IDs{true};
	int menu_DataList_Size;

	if(menuType == MenuType::SIDE){
		menu_DataList_Size = static_cast<int>(sideMenu_DataList.size());
	}
	else if(menuType == MenuType::TOPPING){
		menu_DataList_Size = static_cast<int>(toppingMenu_DataList.size());
	}
	else{
		is_Vaild_IDs = false;
	}

	for(int i{0}; i < static_cast<int>(selectable_OtherMenuID_Option.size()); ++i){
		// 유효한 값인지 검사
		if(0 > selectable_OtherMenuID_Option[i].id || selectable_OtherMenuID_Option[i].id >= menu_DataList_Size){
			is_Vaild_IDs = false;
		}
		// 다른 메뉴 종류가 존재하는 경우
		if(menuType != selectable_OtherMenuID_Option[i].menuType){
			is_Vaild_IDs = false;
		}
	}
	if(is_Vaild_IDs){
		selectable_OtherMenuID_OptionList.push_back(selectable_OtherMenuID_Option);
	}
}



// 세트 메뉴의 기본 옵션을 추가
void SetMenuData::add_DefaultMenuID_Option(const MenuID& defaultMenuID_Option){
	MenuType menuType{defaultMenuID_Option.menuType};
	bool is_Vaild_IDs{true};
	int menu_DataList_Size;

	if(menuType == MenuType::SIDE){
		menu_DataList_Size = static_cast<int>(sideMenu_DataList.size());
	}
	else if(menuType == MenuType::TOPPING){
		menu_DataList_Size = static_cast<int>(toppingMenu_DataList.size());
	}
	else{
		is_Vaild_IDs = false;
	}
	// 유효한 값인지 검사
	if(0 > defaultMenuID_Option.id || defaultMenuID_Option.id >= menu_DataList_Size){
		is_Vaild_IDs = false;
	}
	if(is_Vaild_IDs){
		defalutMenuID_OptionList.push_back(defaultMenuID_Option);
	}

}

// OtherMenuData 정의
OtherMenuData::OtherMenuData(const std::string& menuName, int price): MenuData(menuName, price){}



// 메뉴데이터를 만드는 함수 정의

void make_MenuData(){
	make_MainMenuData();
	make_SetMenuData();
}

void make_MainMenuData(){
	set_Seletable_SpicyLevels();
	set_Selectable_ToppingData();
}

void make_SetMenuData(){
	set_Selectable_Options();
	set_Defalut_Options();
}


// 각 메뉴에서 선택 가능한 매운맛의 단계를 설정함
void set_Seletable_SpicyLevels(){
	std::vector<SpicyLevel> tmp_spicyLevelList;
	for(int i{0}; i< static_cast<int>(mainMenu_DataList.size() - 5); ++i){ // 메뉴리스트의 뒤에 있는 5가지 닭발메뉴는 매운맛 선택이 불가능하므로 (메뉴리스트 사이즈 - 5)
		if(mainMenu_DataList[i].get_MenuName() == "2인 엽기떡볶이"){ // 초보맛 선택 불가
			tmp_spicyLevelList = {SpicyLevel::KIND, SpicyLevel::LESS_SPICY, SpicyLevel::ORIGINAL, SpicyLevel::VERY_SPICY};
		}
		else if(mainMenu_DataList[i].get_MenuName().substr(0,9) == "엽기 로제"){// 엽기 로제 메뉴는 착한맛과 오리지널만 선택 가능
			tmp_spicyLevelList = {SpicyLevel::KIND, SpicyLevel::ORIGINAL};
		}
		else{
			tmp_spicyLevelList = {SpicyLevel::KIND, SpicyLevel::BEGINNER, SpicyLevel::LESS_SPICY, SpicyLevel::ORIGINAL, SpicyLevel::VERY_SPICY};
		}
		for(int j{0}; j<static_cast<int>(tmp_spicyLevelList.size()); ++j){
			mainMenu_DataList[i].add_Seletable_SpicyLevels(tmp_spicyLevelList[j]);
		}
	}
}

// 각 메뉴에서 선택가능한 토핑들을 설정함
void set_Selectable_ToppingData(){
	std::vector<int> tmp_toppingNumList;

	for(int i{0}; i<static_cast<int>(mainMenu_DataList.size()); ++i){

		if(i<8){
			if(mainMenu_DataList[i].get_MenuName() == "엽기 닭볶음탕"){
				tmp_toppingNumList = {0,1,2,3,4,5,6,7,8};
			}
			else{
				tmp_toppingNumList = {0,1,2,3,4,5,6,7,8,9,10};
			}
		}
		else{
			if(mainMenu_DataList[i].get_MenuName() == "엽기 국물닭발"){
				tmp_toppingNumList = {0,1,2,3,4,9};
			}
			else{
				tmp_toppingNumList = {0,1,2,3,4};
			}
		}
		for(int j{0}; j < static_cast<int>(tmp_toppingNumList.size()); ++j){
			mainMenu_DataList[i].add_Selectable_ToppingID(tmp_toppingNumList[j]);
		}
	}
}

// 각 세트메뉴에서 선택가능한 옵션들을 설정함
void set_Selectable_Options(){

	// 엽기 떡볶이, 엽기 오뎅, 엽기 반반 중 택1
	std::vector<int> option1 = {0, 1, 2};

	// 엽기 닭발 메뉴 중 택1
	std::vector<int> option2 = {8, 9, 10, 11, 12};

	// 계란(2개), 메추리알(5) 중 택1
	std::vector<MenuID> option3 = { {MenuType::TOPPING, 3}, {MenuType::TOPPING, 4}};

	for(int i{0}; i<static_cast<int>(setMenu_DataList.size()); ++i){
		switch (i){

		// A ~ C set
		case 0: case 1: case 2:
			// 주먹김밥
			setMenu_DataList[i].add_Selectable_MainMenuID_Options(option1);
			setMenu_DataList[i].add_Selectable_OtherMenuID_Options(option3);
			break;

			// Family_Set
		case 3:
			setMenu_DataList[i].add_Selectable_MainMenuID_Options(option1);
			setMenu_DataList[i].add_Selectable_MainMenuID_Options(option2);
			break;


			// 엽기닭발 세트
		case 4:
			setMenu_DataList[i].add_Selectable_MainMenuID_Options(option2);
			break;

		}
	}
}

// 각 세트메뉴에서 기본 제공 옵션들을 설정함
void set_Defalut_Options(){

	for(int i{0}; i<static_cast<int>(setMenu_DataList.size()); ++i){
		switch (i){

		// A set
		case 0:
			// 주먹김밥
			setMenu_DataList[i].add_DefaultMenuID_Option({MenuType::SIDE, 0});
			break;

			// B set
		case 1:
			// 주먹김밥, 모둠튀김
			setMenu_DataList[i].add_DefaultMenuID_Option({MenuType::SIDE, 0});
			setMenu_DataList[i].add_DefaultMenuID_Option({MenuType::SIDE, 7});
			break;

			// C set
		case 2:
			// 주먹김밥, 모둠튀김, 당면
			setMenu_DataList[i].add_DefaultMenuID_Option({MenuType::SIDE, 0});
			setMenu_DataList[i].add_DefaultMenuID_Option({MenuType::SIDE, 7});
			setMenu_DataList[i].add_DefaultMenuID_Option({MenuType::TOPPING, 8});
			break;

			// Family_Set, 엽기닭발 세트
		case 3: case 4:
			// 주먹김밥
			setMenu_DataList[i].add_DefaultMenuID_Option({MenuType::SIDE, 0});
			break;

		}
	}
}






