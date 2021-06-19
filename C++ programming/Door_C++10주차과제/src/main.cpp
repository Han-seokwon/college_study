//============================================================================
// Name        : main.cpp
// Description : 11장 연습문제 3의 door관련 클래스를 실행하는 소스파일
//============================================================================


#include <iostream>
#include "door.h"


int main() {
	// 잠금장치가 없는 문
	Door* no_lockDoor{new NoLockDoor};

	std::cout << no_lockDoor->getDoorState() << '\n';

//	no_lockDoor->closeDoor(); // 문이 이미 닫혀있는데, 닫으려고 한 경우

	no_lockDoor->openDoor();
	std::cout << no_lockDoor->getDoorState() << '\n';

//	no_lockDoor->openDoor(); // 문이 이미 열려있는데, 열려고 한 경우

	no_lockDoor->closeDoor();
	std::cout << no_lockDoor->getDoorState() << '\n';

	delete no_lockDoor;

	// 잠금장치가 있는 문
	Door* lockDoor{new LockDoor};

	std::cout << lockDoor->getDoorState() << '\n';

	lockDoor->openDoor();
	std::cout << lockDoor->getDoorState() << '\n';

	lockDoor->closeDoor();
	std::cout << lockDoor->getDoorState() << '\n';

	// 문 잠금 설정
	LockDoor* lockDoor_casted{dynamic_cast<LockDoor*>(lockDoor)};

	lockDoor_casted->lockDoor();
	std::cout << lockDoor->getDoorState() << '\n';

	lockDoor_casted->unlockDoor();
	std::cout << lockDoor->getDoorState() << '\n';

	delete lockDoor;

	return 0;
}








