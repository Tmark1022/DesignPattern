/*
	命令模式：将一个请求封装成一个对象，从而使你可用不同的请求对客户进行参数化；
			  对请求排队或记录请求日志，以及支持可撤销的操作。
*/
#include<iostream>
#include<vector>
using namespace std;

// reciver,命令接受者类
class AbsractReciever{
public:
	virtual void action() = 0;
};

class ConcreteRecieverA : public AbsractReciever{
public:
	virtual void action(){
		cout << "A接受者行为" << endl;
	}
};

class ConcreteRecieverB : public AbsractReciever{
public:
	virtual void action(){
		cout << "B接受者行为" << endl;
	}
};


// 命令对象类
class AbstractCommand{
public:
	AbstractCommand(AbsractReciever * temp){
		reciever = temp;
	}

	virtual void ExecuteCommand() = 0;
protected:
	AbsractReciever * reciever;
};

class ConcreteCommandA : public AbstractCommand{
public:
	ConcreteCommandA(AbsractReciever * temp) :AbstractCommand(temp){}

	virtual void ExecuteCommand(){
		cout << "执行命令A : " << endl;
		this->reciever->action();
	}
};

class ConcreteCommandB : public AbstractCommand{
public:
	ConcreteCommandB(AbsractReciever * temp) :AbstractCommand(temp){}

	virtual void ExecuteCommand(){
		cout << "执行命令B : " << endl;
		this->reciever->action();
	}
};

// 命令执行者/收集者类
class Invoke{
public:
	void add_command(AbstractCommand*temp){
		this->vec.push_back(temp);
	}

	void notify(){
		for (auto command : this->vec){
			command->ExecuteCommand();
		}
	}

protected:
	vector<AbstractCommand*> vec;
};


// main
int main(int argc, char * argv[]){
	// 命令调用对象
	Invoke * invoke = new Invoke();
	// 命令接受者对象
	AbsractReciever * reciever_a = new ConcreteRecieverA();
	AbsractReciever * reciever_b = new ConcreteRecieverB();
	// 命令对象
	AbstractCommand * command_a = new ConcreteCommandA(reciever_a);
	AbstractCommand * command_b = new ConcreteCommandB(reciever_b);

	// 命令调用对象收集命令
	invoke->add_command(command_a);
	invoke->add_command(command_b);
	
	//通知接受者
	invoke->notify();

	return 0;
}
