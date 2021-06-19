//============================================================================
// Name        : Door.cpp
// Description : 11장 연습문제 3의 door 클래스를 정의한 소스파일
//============================================================================

#include <iostream>
#include "door.h"

// 모든 문 클래스
void Door::closeDoor(){
	if(isOpened){
		isOpened = false;
	}
	else{
		throw std::logic_error{"문이 이미 닫혀있습니다."};
	}
}

// 잠금장치가 없는 문 클래스
void NoLockDoor::openDoor(){
	if(isOpened){
		throw std::logic_error{"문이 이미 열려있습니다.\n"};
	}
	else{
		isOpened = true;
	}
}

const std::string NoLockDoor::getDoorState() const{
	if(isOpened){
		return "문이 열려 있습니다.";
	}
	else{
		return "문이 닫혀 있습니다.";
	}
}

// 잠금장치가 있는 문 클래스
void LockDoor::openDoor(){
	if(isOpened){
		throw std::logic_error{"문이 이미 열려있습니다.\n"};
	}
	else{ // 문이 닫혀있는 경우

		if(isLocked){
			throw std::logic_error{"문이 잠겨져 있습니다.\n"};
		}
		else{
			isOpened = true;
		}
	}
}

const std::string LockDoor::getDoorState() const{
	if(isOpened){
		return "문이 열려 있습니다.";
	}
	else{// 문이 닫혀있는 경우
		if(isLocked){
			return "문이 닫혀있고, 잠겨있습니다.";
		}
		else{
			return "문이 닫혀있고, 잠겨있지 않습니다.";
		}
	}
}

void LockDoor::lockDoor(){
	if(isOpened){
		throw std::logic_error{"문이 열려있어 잠금을 걸 수 없습니다.\n"};
	}
	else{// 문이 닫혀있는 경우
		if(isLocked){
			throw std::logic_error{"문이 이미 잠겨있습니다.\n"};
		}
		else{
			isLocked = true;
		}
	}

}

void LockDoor::unlockDoor(){
	if(isLocked){
		isLocked = false;
	}
	else{
		throw std::logic_error{"문이 잠겨있지 않습니다.\n"};
	}

}


