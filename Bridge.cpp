/*
	桥接模式：使抽象部分和实现部分分离开来，使得能够独立的变化。（合成/聚合复用原则）
	抽象与实现分离并不是指抽象类与派生类分开，抽象指的是抽象类与派生类，而实现指的是用来实现抽象类与派生类的功能类对象。
*/

#include<iostream>
using namespace std;


// 实现
class AbstractImplement{
public:
	virtual void do_result() = 0;
};

class ConcreteImplementA : public AbstractImplement{
public:
	virtual void do_result(){
		cout << "ConcreteImplementA" << endl;
	}
};

class ConcreteImplementB : public AbstractImplement{
public:
	virtual void do_result(){
		cout << "ConcreteImplementB" << endl;
	}
};

// 抽象
class AbstractObject{
public:
	AbstractObject(){
		implement_obj = nullptr;
	}

	void set_implement(AbstractImplement * temp){
		implement_obj = temp;
	}

	virtual void do_result() = 0;

protected:
	AbstractImplement * implement_obj;
};

class ConcreteObject : public AbstractObject{
public:
	ConcreteObject() :AbstractObject(){}

	virtual void do_result(){
		this->implement_obj->do_result();
	}
};




// main
int main(int argc, char *argv[]){
	AbstractObject * obj = new ConcreteObject();
	AbstractImplement * implementa = new ConcreteImplementA();
	AbstractImplement * implementb = new ConcreteImplementB();

	obj->set_implement(implementa);
	obj->do_result();

	cout << "------------------------分割线-----------------------" << endl;

	obj->set_implement(implementb);
	obj->do_result();

	return 0;
}

