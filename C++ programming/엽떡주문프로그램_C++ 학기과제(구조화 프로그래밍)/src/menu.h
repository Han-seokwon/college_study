//============================================================================
// Name        : menu.h
// Description : 동대문엽기떡볶이 학기과제 menu.h 헤더파일입니다.
//============================================================================

#ifndef MENU_H_
#define MENU_H_
#include <vector>
#include <string>
#include <cstdlib>
#include <vector>
#include <iostream>


// 프로그램에서 각 단계들이 종료되고 어떤 명령을 실행하지에 대한 열거형
enum ProgramCommand{
	GO_BACK =0,
	CONTINUE,
	END,
	CANCEL
};


// 주문 프로그램에서 각 선택단계들에 대한 열거형
enum OrderProcess{
	NA=0,
	MENULIST_SELECT,
	MENU_SELECT,
	OPTION_SELECT,
	SPICY_SELECT,
	TOPPING_SELECT,
	ORDER_CONTINUE_SELECT
};



// 매운맛 단계에 대한 열거형
enum SpicyLevel{
	NONE=0,
	KIND,
	BEGINNER,
	LESS_SPICY,
	ORIGINAL,
	VERY_SPICY
};


// 메뉴 종류를 고를 때 사용할 열거형
enum MenuListOptions{
	YUPPGY_MENU = 0,
	CHICKEN_FEET_MENU,
	SIDE_MENU,
	TOPPING,
	SET_MENU
};

// 세트 메뉴를 고를 때 사용할 열거형
enum SetMenuOptions{
	A_Set =0,
	B_Set,
	C_Set,
	Family_Set,
	Yuppgy_Chicken_Feet_Set
};


// 각 메뉴들에 대한 데이터를 담는 구조체
struct MenuData{
	std::string menuName;
	int price;
	std::vector<SpicyLevel> selectableSpicyLevelVector; // 선택가능한 매운맛
	std::vector<MenuData*> selectableToppingVector; // 선택가능한 토핑들
};


//  각 세트메뉴에 대한 데이터를 담는 구조체
struct SetMenuData{
	std::string setMenuName;
	int setPrice;
	std::vector<std::vector<MenuData>> menuOptionsVector; // 세트메뉴의 옵션(선택이 가능한 조합)메뉴들
	std::vector<MenuData*> menuDefalutVector; // 세트메뉴에서 기본적으로 제공되는 메뉴들
};


// 사용자가 주문과정에서 선택한 일반메뉴(세트메뉴 제외) 대한 데이터를 담는 구조체
struct OrderMenuData{
	int orderedPrice;
	MenuData* orderedMenuData{nullptr}; // 주문된 메뉴의 정보
	std::vector<MenuData*> orderedToppingsVector; // 추가된 토핑들
	SpicyLevel orderedSpicy{NONE}; // 선택된 매운맛 단계
};


// 사용자가 주문과정에서 선택한 세트메뉴에 대한 데이터를 담는 구조체
struct OrderSetMenuData{
	int orderedSetMenuPrice;
	SetMenuData* orderedSetMenuData{nullptr}; // 주문된 세트메뉴의 정보
	std::vector<OrderMenuData> selectedOptions; // 세트메뉴의 선택가능한 옵션에 대한 주문데이터
};


// 주문된 메뉴에 대한 데이터를 담는 구조체
struct OrderedData{
	bool isSetMenu{false}; // 세트메뉴인지 여부를 구분
	OrderMenuData orderedMenu; // 주문된 일반메뉴
	OrderSetMenuData orderedSetMenu; // 주문된 세트메뉴
};


// 주문된 모든 메뉴에 대한 데이터를 담는 구조체(주문내역)
struct TotalOrderHistory{
	int totalPrice;
	std::vector<OrderedData> orderedDataVector; // 주문된 각 메뉴들의 데이터
};



// 1. <main.cpp>


// <--상호작용 함수-->


// 사용자에게 시작메뉴를 선택하면 그에 맞는 정수형을 반환함
int selectStartProgram();


// 사용자가 잘못된 입력을 했을 때 경고문을 출력함
void printInputError();


// 2. <Make_Menu.cpp>


// <--내부논리 처리함수-->


// 일반메뉴(세트메뉴를 제외)의 데이터를 하나의 2차원 벡터(AllMenuData)에 담음
void makeMenu(std::vector<std::vector<MenuData>>& AllMenuData);


// 메뉴데이터에 선택가능한 매운맛 단계들을 추가함
void putSelectableSpicyLevel(std::vector<MenuData>& MenuListData);


// 메뉴데이터에 선택가능한 토핑들의 데이터를 추가함
void putSelectableToppings(std::vector<std::vector<MenuData>>& AllMenuData);


// 세트메뉴의 데이터들을 하나의 1차원 벡터(AllsetMenuData)에 담음
void makeSetMenu(std::vector<std::vector<MenuData>>& AllMenuData, std::vector<SetMenuData>& AllsetMenuData);


// 세트메뉴에 해당하는 옵션들을 세트 메뉴 데이터에 추가함
void putSetMenuOption(std::vector<std::vector<MenuData>>& AllMenuData, SetMenuData& setMenuData, SetMenuOptions setMenu);


// 세트메뉴에 해당하는 기본 메뉴들을 세트 메뉴 데이터에 추가함
void putSetMenuDefalut(std::vector<std::vector<MenuData>>& AllMenuData, SetMenuData& setMenuData, SetMenuOptions setMenu);



// 3. <Order_Process.cpp>


// <--내부논리 처리함수-->


// 주문 프로그램(메뉴종류 선택 -> 메뉴 선택 -> 주문내역 출력)을 실행
ProgramCommand startOrderProcess(std::vector<std::vector<MenuData>>& AllMenuData, std::vector<SetMenuData>& AllSetMenuData);


// 선택한 메뉴종류의 int 타입을 그에 맞는 MenuListOptions 열거형으로 변환해주는 함수
MenuListOptions changeType_To_MenuListOptions(int selectedMenuList);


// 선택한 메뉴의 총가격(메뉴의 가격 + 추가한 토핑 가격)을 계산하여 총가격을 정수형으로 반환
int calculateOrderPrice(OrderedData& order);


// 주문내역의 각 주문에 대한 가격을 계산하여 총가격을 정수형으로 반환
int calculateTotalPrice(TotalOrderHistory& orderHistory);


// 사용자가 취소하려고 하는 주문을 주문내역에서 삭제함
void cancelOrderProcess(TotalOrderHistory& orderHistory);


// <--상호작용 함수-->

// 사용자가 메뉴종류를 선택하면 그에 맞는 정수형을 반환
int selectMenuList();


// 현재까지의 주문내역(주문된 메뉴들 + 총가격)을 출력함
void printOrderList(TotalOrderHistory& orderHistory);


// 해당 메뉴의 이름과 가격을 하나의 문자열로 만들어 반환함
std::string makeString_SelectedMenu(MenuData& selectedMenu, bool isSelectOptionProcess=false);

// 메뉴 선택이 끝나고 사용자에게 주문을 계속할지를 물어보고 그에 맞는 ProgramCommand를 반환함
ProgramCommand selectMenuProcessOption(TotalOrderHistory& orderHistory);


// 사용자가 추가로 메뉴를 선택한다고 했을 때, 안내문구를 출력함
void printContinueOrderProcess();


// 사용자에게 주문내역중에 취소하고 싶은 메뉴를 선택하게하고 그에 맞는 정수형을 반환함
int selectMenu_To_Cancel(TotalOrderHistory& orderHistory);


// 사용자가 주문을 종료한다고 했을 때, 최종주문내역을 출력함
void printEndOrderProcess(TotalOrderHistory& orderHistory);


// 4. <Select_Menu.cpp>


// <--내부논리 처리함수-->


// 메뉴 선택과정(메뉴 선택-> 매운맛 선택 -> 토핑 추가)를 실행, 세트메뉴 옵션을 선택할 때도 사용됨
ProgramCommand selectMenuProcess(OrderMenuData& orderMenuData, std::vector<MenuData>& selectedMenuListData, bool isSelectOptionProcess=false);


// 세트 메뉴 선택 과정(세트 메뉴선택 -> 옵션 선택)을 실행
ProgramCommand selectSetMenuProcess(OrderSetMenuData& orderSetMenu, std::vector<SetMenuData>& AllSetMenuData);


//  종료된 단계의 정보를 저장하는 스택에서 이전에 실행한 단계를 찾아서 반환함
OrderProcess lastProcess(std::vector<OrderProcess>& finishedProcessStack);


// <--상호작용 함수-->


// 메뉴종류에 맞는 메뉴들 중에서 사용자가 선택한 메뉴에 맞는 정수형을 반환
int selectMenu(std::vector<MenuData>& selectedMenuList, bool isSelectOptionProcess);


// 최종적으로 메뉴를 주문데이터에 추가할 것인지를 물어보고 그에 맞는 ProgramCommand을 반환함
ProgramCommand selectPutMenu_Or_GoBack();


// 사용자가 선택한 세트메뉴에 맞는 정수형을 반환
int selectSetMenu(std::vector<SetMenuData>& AllSetMenuData);




// 5. <Select_Spicy_Topping.cpp>


// <--내부논리 처리함수-->


// 토핑추가단계의 진행(새로운 토핑을 추가, 추가한 토핑을 취소, 토핑 추가 단계 종료)을 결정하고, 결정된 기능을 수행함
ProgramCommand selectToppingProcess(MenuData& selectedMenu, std::vector<MenuData*>& orderedToppingsVector);


// 사용자가 선택한 토핑을 주문데이터에서 삭제함
void cancelToppingProcess(MenuData& selectedMenu, std::vector<MenuData*>& orderedToppingsVector);

// <--상호작용 함수-->


// 사용자가 선택한 매운맛단계에 맞는 SpicyLevel 열거형을 반환
SpicyLevel selectSpicyLevel(MenuData& selectedMenu);


// 사용자가 (이전 단계로 돌아가기, 토핑 추가, 추가한 토핑 취소, 토핑 추가종료) 중에서 선택하게하고 그에 맞는 ProgramCommand 열거형을 반환
ProgramCommand selectToppingProcessOption(std::vector<MenuData*>& orderedToppingsVector);


// 사용자가 선택한 메뉴에 추가할 수 있는 토핑을 고르면 그에 맞는 정수형을 반환
int selectTopping(MenuData& selectedMenu);


// 사용자에게 현재 메뉴에 추가된 토핑들과 앞으로 추가할 수 있는 토핑의 개수를 보여줌
void printAddedToppings(MenuData& selectedMenu, std::vector<MenuData*>& orderedToppingsVector);


// 사용자에게 취소할 토핑을 선택하게하고 그에 맞는 정수형을 반환
int selectTopping_To_Cancel(MenuData& selectedMenu, std::vector<MenuData*>& orderedToppingsVector);


#endif /* MENU_H_ */






