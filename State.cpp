/*
	状态模式：消除庞大的条件判断分支语句。
	状态模式将各种状态的操作逻辑和下一个状态的转移逻辑都分布到state的子类中，来减少相互间的依赖。
*/
#include<iostream>
using namespace std;



// First method, 传统的状态判断逻辑，状态判断方法庞大，难以维护（修改摸一个状态或者插入新的状态的时候，违背开闭原则，难以维护，维护容易造成错误）
class Work{
public:
	static int now_time;
	void write_programe();
};

// 有多个状态的时候，条件分支过于庞大（当然这里只有几行，假设庞大），难以维护
void Work::write_programe(){
	if (Work::now_time < 12)
		cout << "早上敲码，神清气爽" << endl;
	else if (Work::now_time < 17)
		cout << "下午敲码，有点小困" << endl;
	else if (Work::now_time < 21)
		cout << "晚上加班敲码，受不了" << endl;
	else if (Work::now_time < 24)
		cout << "通宵敲码，坟草丈许高" << endl;
	else
		cout << "兄弟别闹，时间超过24小时啦" << endl;
}

// （类静态成员变量必须初始化）， 初始化静态成员变量(准确来说应该是定义变量，分配内存)
int Work::now_time = 0;



// 类声明
class Context;
class MorningState;
class AfternoonState;
class NightState;
class MidNightState;
class ErrorState;


// second method, 使用状态模式，分解庞大的条件分支
// 抽象状态类
class State{
public:
	virtual void write_programe(Context * context_obj) = 0;
};

// 早上敲码状态类
class MorningState : public State{
public:
	virtual void write_programe(Context * context_obj);
};

// 上下文类
class Context{
public:
	Context(){
		this->current_state = new MorningState();
	}
	void set_now_time(int time){
		context_now_time = time;
	}
	int get_now_time(){
		return context_now_time;
	}

	void write_programe(){
		if (this->current_state == nullptr)
			return;

		this->current_state->write_programe(this);
	}

public:
	State * current_state;
	static int context_now_time;
};



// 下午敲码状态类
class AfternoonState : public State{
public:
	virtual void write_programe(Context * context_obj);
};

// 晚上敲码状态类
class NightState : public State{
public:
	virtual void write_programe(Context * context_obj);
};

// 通宵敲码状态类
class MidNightState : public State{
public:
	virtual void write_programe(Context * context_obj);
};

// 错误状态类
class ErrorState : public State{
public:
	virtual void write_programe(Context * context_obj){
		if (context_obj->get_now_time() > 24)
			cout << "兄弟别闹，时间超过24小时啦" << endl;
	}
};


void MorningState::write_programe(Context * context_obj){
	if (context_obj->get_now_time() < 12)
		cout << "早上敲码，神清气爽" << endl;
	else{
		// 下一个状态
		context_obj->current_state = new AfternoonState();
		context_obj->write_programe();
	}
}

void AfternoonState::write_programe(Context * context_obj){
	if (context_obj->get_now_time() < 17)
		cout << "下午敲码，有点小困" << endl;
	else{
		// 下一个状态
		context_obj->current_state = new NightState();
		context_obj->write_programe();
	}
}

void NightState::write_programe(Context * context_obj){
	if (context_obj->get_now_time() < 21)
		cout << "晚上加班敲码，受不了" << endl;
	else{
		// 下一个状态
		context_obj->current_state = new MidNightState();
		context_obj->write_programe();
	}
}


void MidNightState::write_programe(Context * context_obj){
	if (context_obj->get_now_time() <= 24)
		cout << "通宵敲码，坟草丈许高" << endl;
	else{
		// 下一个状态
		context_obj->current_state = new ErrorState();
		context_obj->write_programe();
	}
}
















int Context::context_now_time = 0;




// main
int main(int argc, char * argv[])
{
	// test First method
	Work * work_obj = new Work();
	Work::now_time = 8;
	work_obj->write_programe();
	Work::now_time = 14;
	work_obj->write_programe();
	Work::now_time = 20;
	work_obj->write_programe();
	Work::now_time = 23;
	work_obj->write_programe();
	Work::now_time = 25;
	work_obj->write_programe();
	
	cout << "------------------------分割线----------------------" << endl;

	// test Second method, state module
	Context * context_obj = new Context();
	context_obj->set_now_time(8);
	context_obj->write_programe();
	context_obj->set_now_time(14);
	context_obj->write_programe();
	context_obj->set_now_time(20);
	context_obj->write_programe();
	context_obj->set_now_time(23);
	context_obj->write_programe();
	context_obj->set_now_time(25);
	context_obj->write_programe();

	return 0;
}





