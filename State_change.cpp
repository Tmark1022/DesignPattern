/*************************************************************************
 @ Author	: tmark
 @ Created Time	: Wed 19 Jan 2022 03:23:26 PM CST
 @ File Name	: State_change.cpp
 @ Description	: 状态模式实现状态变化 
 ************************************************************************/
#include <iostream>
#include <typeinfo>
#include <vector>
#include <string>
#include <algorithm>
#include <climits>
#include <deque>
#include <unordered_map>
#include <unordered_set>

using namespace std;

/*
	有如下状态转换图
		1001
		  |
		1002
		  |				
		/	\	(根据flag变量，决定状态变化分支)
	  1003 1004
	    \   /
		  |
		1005
		  | 
		1006(end)
   */

/***************************************************
* forward declaration 
***************************************************/
class AbstractContex;

/***************************************************
* abstract base class 
***************************************************/
// 状态基类
class AbstractState {
	public:
		const int state;
		AbstractState(int state):state(state) {}
		virtual void TryChangeState(AbstractContex *) = 0;
		virtual ~AbstractState() {}
};

// 上下文基类(需要进行状态切换)
class AbstractContex {
	public:
		int time_state;
		int flag;
		AbstractState * now_state; 	
		AbstractContex(int time_state, AbstractState * now_state, int flag) : time_state(time_state), now_state(now_state), flag(flag) {}
		void SetTimeState(int time_state) { this->time_state = time_state;}	
		void SetFlag(int flag) { this->flag = flag;}	
		void SetState(AbstractState * state) { 
			if (this->now_state) {
				delete this->now_state;
			}
			this->now_state = state;
		}	
		virtual void TryChangeState() {this->now_state->TryChangeState(this);}
};

/***************************************************
* state 
***************************************************/
class State1006 : public AbstractState {
	public:
		State1006():AbstractState(1006) {}
		void TryChangeState(AbstractContex * contex) override {
			if (contex->time_state == state) { cout << "..保持(当前)状态 : " << state << endl;} 
			else {
				cout << "没有下个状态啦。。。" << endl;
			}

		}
};

class State1005 : public AbstractState {
	public:
		State1005():AbstractState(1005) {}
		void TryChangeState(AbstractContex * contex) override {
			if (contex->time_state == state) { cout << "..保持(当前)状态 : " << state << endl; } 
			else {
				AbstractState *next_state = new State1006();
				cout << "切换状态 : " << state << " -> " << next_state->state << endl;	
				contex->SetState(next_state);
				contex->TryChangeState();
			}
		}
};

class State1004 : public AbstractState {
	public:
		State1004():AbstractState(1004) {}
		void TryChangeState(AbstractContex * contex) override {
			if (contex->time_state == state) { cout << "..保持(当前)状态 : " << state << endl; } 
			else {
				AbstractState *next_state = new State1005();
				cout << "切换状态 : " << state << " -> " << next_state->state << endl;	
				contex->SetState(next_state);
				contex->TryChangeState();
			}
		}
};

class State1003 : public AbstractState {
	public:
		State1003():AbstractState(1003) {}
		void TryChangeState(AbstractContex * contex) override {
			if (contex->time_state == state) { cout << "..保持(当前)状态 : " << state << endl; } 
			else {
				AbstractState *next_state = new State1005();
				cout << "切换状态 : " << state << " -> " << next_state->state << endl;	
				contex->SetState(next_state);
				contex->TryChangeState();
			}
		}
};

class State1002 : public AbstractState {
	public:
		State1002():AbstractState(1002) {}
		void TryChangeState(AbstractContex * contex) override {
			if (contex->time_state == state) { cout << "..保持(当前)状态 : " << state << endl; } 
			else {
				AbstractState *next_state = nullptr; 
				if (contex->flag) next_state = new State1004();
				else next_state = new State1003();
				cout << "切换状态 : " << state << " -> " << next_state->state << endl;	
				contex->SetState(next_state);
				contex->TryChangeState();
			}
		}
};

class State1001 : public AbstractState {
	public:
		State1001():AbstractState(1001) {}
		void TryChangeState(AbstractContex * contex) override {
			if (contex->time_state == state) { cout << "..保持(当前)状态 : " << state << endl; } 
			else {
				AbstractState *next_state = new State1002();
				cout << "切换状态 : " << state << " -> " << next_state->state << endl;	
				contex->SetState(next_state);
				contex->TryChangeState();
			}
		}
};

/***************************************************
* context
***************************************************/
class ConcreteContex  : public AbstractContex {
	public:
		ConcreteContex(int time_state, AbstractState * now_state, int flag) : AbstractContex(time_state, now_state, flag) {}
};

/***************************************************
* init static variables
***************************************************/

int main(int argc, char *argv[]) {
	/*
	// AbstractContex *contex = new ConcreteContex(1001, new State1001(), 0);
	AbstractContex *contex = new ConcreteContex(1001, new State1001(), 1);
	contex->TryChangeState();

	contex->SetTimeState(1002);
	contex->TryChangeState();

	contex->SetTimeState(1005);
	contex->TryChangeState();

	contex->SetTimeState(1006);
	contex->TryChangeState();
	contex->TryChangeState();
	*/

	AbstractContex *contex = new ConcreteContex(1001, new State1001(), 1);
	contex->TryChangeState();
	contex->SetTimeState(1006);
	contex->TryChangeState();

	return 0;
}
