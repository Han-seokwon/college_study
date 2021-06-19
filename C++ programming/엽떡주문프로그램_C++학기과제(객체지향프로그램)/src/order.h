//============================================================================
// Name        : 2020180117한석원_C++학기과제4.cpp
// Author      : 2020180117 한석원
// Version     :
// Copyright   : Your copyright notice
// Description : 주문 프로그램에서 사용할 클래스, 함수 등을 선언한 헤더파일입니다.
//============================================================================

#ifndef ORDER_H_
#define ORDER_H_

#include <iostream>
#include <limits>
#include <vector>
#include <string>
#include <cstdlib>
#include <stdexcept>
#include <stack>

// 매운맛 단계에 대한 열거형
enum class SpicyLevel{
	NONE,
	KIND,
	BEGINNER ,
	LESS_SPICY,
	ORIGINAL,
	VERY_SPICY
};

// 메뉴종류
enum class MenuType{
	NONE,
	MAIN,
	SET,
	SIDE,
	TOPPING
};

// 주문과정에서 사용자 편의를 위해 추가한 기능에 대한 열거형
enum class OrderProcessCommand{
	GO_BACK = 101, // 이전 단계로 돌아감
	CANCEl = 102, // 선택한 것을 취소
	END = 103, // 현재 단계를 종료
	CONTINUE = 104 // 다음 단계로 이동
};


// 주문 과정의 각 단계를 나타내는 열거형 -> 뒤로가기 기능에서 사용
enum class OrderProcess{
	NONE,
	MENUTYPE_SELECT,
	MENU_SELECT, // 세트메뉴, 사이드 메뉴 선택과정도 포함
	SPICY_SELECT,
	TOPPING_SELECT,
	OPTION_SELECT,
};



// 메뉴의 데이터를 유지할 클래스
class MenuData{
private:
	std::string menuName;
	int price;
public:
	explicit MenuData(const std::string& menuName, int price);
	virtual ~MenuData() = default;

	int get_Price() const noexcept;
	const std::string& get_MenuName() const noexcept;

};

// 기타(토핑, 사이드) 메뉴의 데이터를 유지할 클래스
class OtherMenuData: public MenuData{
public:
	explicit OtherMenuData(const std::string& menuName, int price);
	virtual ~OtherMenuData() = default;
};


// 메인 메뉴의 데이터를 유지할 클래스
class MainMenuData: public MenuData{
private:
	std::vector<SpicyLevel> selectable_SpicyLevelList;
	std::vector<int> selectable_ToppingIDList;

public:
	explicit MainMenuData(const std::string& menuName, int price);
	virtual ~MainMenuData() = default;

	const std::vector<SpicyLevel>& get_selectable_SpicyLevelList() const noexcept;
	const std::vector<int>& get_selectable_ToppingIDList() const noexcept;

	// 선택가능한 매운맛 단계를 추가함
	void add_Seletable_SpicyLevels(SpicyLevel spicy);

	// 선택가능한 토핑을 추가
	void add_Selectable_ToppingID(int toppingID);

};

// 메뉴 종류와 id를 유지할 구조체(사이드, 토핑 메뉴를 구분할 때만 사용)
struct MenuID{
	MenuType menuType;
	int id;
};

// 세트메뉴의 데이터를 유지할 클래스
class SetMenuData: public MenuData{

private:
	std::vector<std::vector<int>> selectable_MainMenuID_OptionList; // 세트메뉴에서 선택가능한 메인메뉴 옵션
	std::vector<std::vector<MenuID>> selectable_OtherMenuID_OptionList; // 세트메뉴에서 선택가능한 기타메뉴(토핑, 사이드) 옵션
	std::vector<MenuID> defalutMenuID_OptionList; // 세트메뉴에서 기본으로 제공하는 옵션(기본 제공 옵션은 모두 토핑 or 사이드)

public:
	explicit SetMenuData(const std::string& menuName, int price);
	virtual ~SetMenuData() = default;

	const std::vector<std::vector<int>>& get_selectable_MainMenuID_OptionList() const noexcept;
	const std::vector<std::vector<MenuID>>& get_selectable_OtherMenuID_OptionList() const noexcept;
	const std::vector<MenuID>& get_DefalutMenuID_OptionList() const noexcept;

	// 세트 메뉴의 선택가능한 메인메뉴 옵션을 추가
	void add_Selectable_MainMenuID_Options(const std::vector<int>& selectable_MainMenuID_Option);

	// 세트 메뉴의 선택가능한 기타 메뉴 옵션을 추가
	void add_Selectable_OtherMenuID_Options(const std::vector<MenuID>& selectable_OtherMenuID_Option);

	// 세트 메뉴의 기본 옵션을 추가
	void add_DefaultMenuID_Option(const MenuID& defaultMenuID_Option);
};



// 메인 메뉴 주문에 대한 정보를 저장하는 클래스
class MainMenu_OrderData{
private:
	int ordered_MainMenuID{-1}; // 주문된 메뉴
	int ordered_Price{0}; // 주문된 메뉴가격 + a
	SpicyLevel ordered_SpicyLevel{SpicyLevel::NONE};
	std::vector<int> ordered_ToppingIDList;

public:
	MainMenu_OrderData() = default;
	virtual ~MainMenu_OrderData() = default;

	int get_ordered_MainMenuID() const noexcept;
	int get_Ordered_Price() const noexcept;
	SpicyLevel get_Ordered_SpicyLevel() const noexcept;
	const std::vector<int>& get_ordered_ToppingIDList() const noexcept;

	// 메인메뉴의 인덱스를 받아 주문된 메뉴와 가격을 설정
	void set_ordered_MainMenuID_Price(int ordered_MenuID);

	void set_SpicyLevel(int ordered_SpicyNum);
	// 사용자가 주문한 토핑을 추가
	void add_Ordered_ToppingID(int ordered_toppingNum);
	// 주문된 토핑들을 모두 삭제함(뒤로가기할 때 사용)
	void clear_Ordered_ToppingIDList();

};


// 하나의 세트메뉴 주문에 대한 정보를 저장하는 클래스
class SetMenu_OrderData{
private:
	int ordered_SetMenuID{-1}; // 주문된 메뉴
	int ordered_Price{0}; // 주문된 메뉴가격 + a
	std::vector<int> ordered_MainMenu_OptionIDList;
	std::vector<MainMenu_OrderData> ordered_MainMenu_OptionList; // 선택가능한 옵션 중에 사용자가 주문한 메인메뉴, 메인메뉴 옵션은 매운맛, 토핑 선택이 필요해 따로 유지
	std::vector<MenuID> ordered_OtherMenu_OptionList; // 선택가능한 옵션 중에 사용자가 주문한 기타 메뉴(토핑, 사이드 메뉴)

public:
	explicit SetMenu_OrderData() = default;
	virtual ~SetMenu_OrderData() = default;

	int get_ordered_SetMenuID() const noexcept;
	int get_Ordered_Price() const noexcept;

	const std::vector<int>& get_ordered_MainMenu_OptionIDList() const noexcept;
	const std::vector<MainMenu_OrderData>& get_Ordered_MainMenu_OptionList() const noexcept;
	const std::vector<MenuID>& get_Ordered_OtherMenu_OptionList() const noexcept;

	void set_ordered_SetMenuID_Price(int ordered_MenuID);
	// 사용자가 메인메뉴 옵션 중에 특정 번호를 입력하면 그에 맞는 메인메뉴의 id를 ordered_MainMenu_OptionIDList에 추가
	void add_Ordered_MainMenu_OptionIDList(int ordered_mainMenu_OptionNum);
	void add_Ordered_MainMenu_Options(const MainMenu_OrderData& ordered_mainMenu_Options);
	void add_Ordered_OtherMenu_Options(int ordered_other_OptionNum);

	// 주문된 옵션들을 모두 삭제함(뒤로가기할 때 사용)
	void clear_all_OptionList();

	// 주문된 메인 메뉴 옵션들 중 가장 뒤의 원소를 삭제하고 반환(뒤로가기할 때 사용)
	MainMenu_OrderData pop_ordered_MainMenu_OptionList();


};


// 전체 주문내역을 저장하는 클래스(장바구니)
class OrderList{

private:
	int total_Ordered_Price{0}; // 주문내역 총 가격
	std::vector<MainMenu_OrderData> ordered_MainMenuList; // 주문된 메인메뉴의 리스트
	std::vector<SetMenu_OrderData> ordered_SetMenuList; // 주문된 세트메뉴의 리스트
	std::vector<int> ordered_SideMenuIDList; // 주문된 사이드메뉴의 리스트

public:

	int get_total_Ordered_Price() const noexcept;

	const std::vector<MainMenu_OrderData>& get_Ordered_MainMenuList() const noexcept;

	const std::vector<SetMenu_OrderData>& get_Ordered_SetMenuList() const noexcept;

	const std::vector<int>& get_Ordered_SideMenuIDList() const noexcept;

	// 주문된 메인 메뉴를 주문내역에 추가함
	void add_Ordered_MainMenu(const MainMenu_OrderData& ordered_Menu);

	// 주문된 세트메뉴를 주문내역에 추가함
	void add_Ordered_SetMenu(const SetMenu_OrderData& ordered_SetMenu);

	// 주문된 사이드메뉴를 주문내역에 추가함
	void add_Ordered_SideMenuID(int ordered_SideMenuID);

	// 사용자가 취소한 메뉴를 주문내역에서 삭제함
	void cancel_Ordered_Menu(MenuType menutype, int menu_num);
};


// 주문 프로세스 스택 클래스
// 뒤로가기 기능에서 사용
class OrderProcess_Stack{
private:
	std::stack<OrderProcess> orderStack;
public:
	// 주문 프로세스 스택의 가장 위의 요소 반환
	OrderProcess get_Top_orderStack() const noexcept;

	// 주문 프로세스 스택의 가장 위의 요소를 스택에서 빼내고 반환
	OrderProcess pop_orderStack();

	// 주문 프로세스 스택을 비움
	void clear_orderStack();

	// 인자로 들어온 요소를 스택에 push
	void push_orderStack(OrderProcess current_OrderProcess);

};




// <메뉴 데이터 구성>

void make_MenuData();

void make_MainMenuData();

void make_SetMenuData();

void make_SideMenuData();

void make_ToppingMenuData();

void set_Selectable_ToppingData();

// 각 메뉴에서 선택 가능한 매운맛의 단계를 설정함
void set_Seletable_SpicyLevels();

// 각 메뉴에서 선택가능한 토핑들을 설정함
void set_Selectable_ToppingData();

// 각 세트메뉴에서 선택가능한 옵션들을 설정함
void set_Selectable_Options();

// 각 세트메뉴에서 기본 제공 옵션들을 설정함
void set_Defalut_Options();


// <주문과정 처리>

// 현재 주문과정을 실행해도 되는지 여부를 확인
bool check_OrderProcess(OrderProcess current_OrderProcess);

// 현재 과정이 정상적으로 종료되었는지 확인
void check_OrderProcess_WellEnded(OrderProcess current_OrderProcess);

// 주문확정 단계에서 "뒤로가기"로 메인메뉴 옵션 선택단계로 왔는지 확인
void check_MainMenu_Option_Run_From_GO_BACK(int& MainMenu_OptionCnt, MainMenu_OrderData MainMenu_Order, SetMenu_OrderData& SetMenu_order);

// 메인메뉴 옵션 선택단계에서 토핑 선택이 정상적으로 종료되었는지 확인
void check_MainMenu_Option_Topping_WellEnded(int& MainMenu_OptionCnt, MainMenu_OrderData MainMenu_Order, SetMenu_OrderData& SetMenu_order);


// <선택>

void select_StartProgram();

// 메뉴 선택과정(메뉴 종류 -> 메뉴선택 -> 주문추가 확인)
void select_Menu_Process(OrderList& orderList);

// 메뉴 종류 선택
void select_MenuType(MenuType& selected_menuType);

// 메인 메뉴 선택 과정(메인메뉴 선택 -> 매운맛 선택 -> 토핑 선택 -> 주문 확인)
void select_MainMenuProcess(OrderList& orderList);

void select_MainMenu(MainMenu_OrderData& MainMenu_order);

void select_ToppingMenu(MainMenu_OrderData& MainMenu_order);

void select_SpicyLevel(MainMenu_OrderData& MainMenu_order);

void select_Menu(MenuType selected_menuType, OrderList& orderList);

// 현재까지 주문한 메인 메뉴 데이터를 주문내역에 추가할지 선택
void select_Confirm_MainMenu(MainMenu_OrderData& MainMenu_order);

// 세트메뉴 선택과정(세트 메뉴 선택 -> 옵션 선택 -> 주문 확인)
void select_SetMenuProcess(OrderList& orderList);

void select_SetMenu(SetMenu_OrderData& SetMenu_OrderData);

void select_Selectable_Options(SetMenu_OrderData& SetMenu_order);

// 세트메뉴의 메인메뉴 옵션 선택과정(매운맛 선택 -> 토핑 선택)
void select_MainMenu_OptionProcess(SetMenu_OrderData& SetMenu_order);

// 현재까지 주문한 세트 메뉴 데이터를 주문내역에 추가할지 선택
void select_Confirm_SetMenu(SetMenu_OrderData& SetMenu_order);

void select_SideMenu(OrderList& orderList);

// 주문 종료, 주문 계속, 주문 취소 중에 선택
void select_Order_End_Continue_Cancel(OrderList& orderList);

// 취소할 주문(메인, 세트, 사이드 중에)을 선택
void select_Menu_To_Cancel(OrderList& orderList);



// <입력>

// 사용자로부터 메뉴종류를 입력
void input_MenuType(int& selected_MenuTypeNum);

// 사용자로부터 메인메뉴를 입력
void input_MainMenu(int& selected_MainMenuNum);

// 사용자로부터 매운맛을 입력
void input_SpicyLevel(int& selected_SpicyLevelNum, MainMenu_OrderData& MainMenu_order);

// 사용자로부터 토핑을 입력
void input_ToppingMenu(std::vector<int>& selected_ToppingNums, MainMenu_OrderData& MainMenu_order);

// 주문 확인 단계에서 사용자로부터 선택지(뒤로가기 or 주문확정)를 입력
void input_Confirm_Order(int &selected_confirm_orderNum);

// 사용자로부터 세트메뉴를 입력
void input_SetMenu(int& selected_SetMenuNum);

// 사용자로부터 선택가능한 옵션 메뉴를 입력
void input_Selectable_Options(std::vector<int>& selected_OptionNums);

// 사용자로부터 사이드 메뉴를 입력
void input_SideMenu(int& sideMenu_Cnt, std::vector<int>& selected_SideMenuNums);

// 사용자로부터 주문 종료, 주문 계속, 주문 취소 중에 입력
void input_Order_End_Continue_Cancel(int& select_Num);


// < 주문데이터에 추가 >

// 사용자가 선택한 메인 메뉴를 주문데이터에 추가
void put_MainMenu_To_OrderData(int selected_MainMenuNum, MainMenu_OrderData& MainMenu_order);

// 사용자가 입력한 매운맛을 주문데이터에 추가
void put_SpicyLevel_To_OrderData(int selected_SpicyLevelNum, MainMenu_OrderData& MainMenu_order);

// 사용자가 선택한 토핑을 주문데이터에 추가
void put_ToppingMenu_To_OrderData(std::vector<int> selected_ToppingNums, MainMenu_OrderData& MainMenu_order);

// 사용자가 선택한 세트메뉴를 주문데이터에 추가
void put_SetMenu_To_OrderData(int selected_SetMenuNum, SetMenu_OrderData& SetMenu_OrderData);

// 사용자로부터 입력받은 옵션 번호들을 메인메뉴 옵션과, 기타메뉴 옵션으로 분리하여 주문데이터에 추가
void put_MainMenu_OtherMenu_Option(std::vector<int>& selected_OptionNums, SetMenu_OrderData& SetMenu_order);

// 사용자가 선택한 사이드 메뉴들을 주문데이터에 추가
void put_SideMenu_To_OrderData(int sideMenu_Cnt, std::vector<int> selected_SideMenuNums, OrderList& orderList);


// <출력>

// 해당 메뉴를 이름+가격으로 문자열 반환
std::string string_Menu_Name_Price(const MenuData& menu);

void print_StartProgram();

void print_MenuType();

void print_MainMenu();

void print_Selectable_ToppingMenu(const MainMenuData& mainMenu);

void print_Selectable_SpicyLevel(const MainMenuData& mainMenu);

// 메인메뉴 주문 확인 출력
void print_Confirm_MainMenu(const MainMenu_OrderData& MainMenu_order);

// 주문된 메인메뉴 출력
void print_Ordered_MainMenu(const MainMenu_OrderData& MainMenu_order, bool isOptionPrint = false);

// 주문내역의 메인메뉴에서 추가된 토핑들을 출력
void print_Ordered_Toppings(const std::vector<int>& ordered_ToppingIDList);


void print_SetMenu();

// 해당 세트메뉴의 선택가능한 옵션을 출력
void print_Selectable_Options(const SetMenuData& setMenu);

// 세트메뉴 주문 확인 출력
void print_Confirm_SetMenu(const SetMenu_OrderData& SetMenu_order);

// 주문된 세트메뉴를 출력(주문 확인 과정에서 사용)
void print_Ordered_SetMenu(const SetMenu_OrderData& Ordered_setMenu);

// 주문내역의 세트메뉴에서 기타 메뉴 옵션 or 기본 옵션을 출력
void print_Ordered_OtherMenu_Options(const MenuID& ordered_Option);

void print_SideMenu();

// 주문 확인 선택지를 출력
void print_Confirm_OrderedMenu();

// 주문내역 출력
void print_OrderList(const OrderList& orderList, bool isOrderEnd = false);

// 주문내역에서 주문된 메인메뉴들을 출력
void print_Ordered_MainMenuList(const std::vector<MainMenu_OrderData>& mainMenu_orderList);

// 주문내역에서 주문된 세트메뉴들을 출력
void print_Ordered_SetMenuList(const std::vector<SetMenu_OrderData>& setMenu_orderList);

// 주문내역에서 주문된 사이드메뉴들을 출력
void print_Ordered_SideMenuList(const std::vector<int>& sideMenu_orderList);


// <기타>
template <typename T>
void input_error_catch(T error){
	std::cin.clear();
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	std::cout<< "\n" << error.what() << "\n";
}




#endif /* ORDER_H_ */
