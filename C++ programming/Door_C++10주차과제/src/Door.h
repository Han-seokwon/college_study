//============================================================================
// Name        : Door.h
// Description : 11장 연습문제 3의 door관련 클래스를 선언한 헤더파일

// (클래스 설명)
// 잠금장치가 있는 문과 없는 문 모두 열고 닫기를 할 수 있으므로 부모클래스인 Door에 openDoor(), closeDoor()을 정의

// 잠금장치의 유무에 따라 문을 여는 과정은 다를 수 있므로 Door에서 openDoor()은 순수가상함수로 정의해  NoLockDoor와 LockDoor에서 재정의
// (LockDoor의 경우 잠금을 해제하고 문을 열어야 함)

// 문을 닫는 과정은 잠금장치의 유무와 상관없이 같으므로 Door에서 closeDoor()는 일반메소드로 정의

// LockDoor의 경우 잠금, 잠금 해제의 기능이 추가적으로 필요하므로 해당클래스 내부에 lockDoor(), unlockDoor()을 정의 (수동 잠금이라고 가정)
//============================================================================

#ifndef DOOR_H_
#define DOOR_H_
#include <string>


// 모든 문 클래스
class Door{
protected:
	bool isOpened{false}; // 문이 열려있는지 여부를 나타냄, 모든 문은 닫힌 상태로 시작
public:
	Door() = default;
	virtual ~Door() = default;

	virtual void openDoor() = 0; // 문을 열음
	void closeDoor(); // 문을 닫음
	virtual const std::string getDoorState() const = 0;

};

// 잠금장치가 없는 문 클래스
class NoLockDoor: public Door{
public:
	NoLockDoor() = default;
	~NoLockDoor() = default;

	virtual void openDoor() override;
	virtual const std::string getDoorState() const override;
};

// 잠금장치가 있는 문 클래스
class LockDoor: public Door{
private:
	bool isLocked{false}; // 문이 잠겨있는지 여부를 나타냄, , 모든 문은 잠금이 해제 상태로 시작
public:
	LockDoor() = default;
	~LockDoor() = default;

	virtual void openDoor() override;
	virtual const std::string getDoorState() const override;

	void lockDoor(); // 잠금 기능
	void unlockDoor(); // 잠금 해제 기능

};



#endif /* DOOR_H_ */

