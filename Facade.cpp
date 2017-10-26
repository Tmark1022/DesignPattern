/*
	外观模式（facade）,又称为门面模式；为一组子系统创建高层的接口，用于统一管理子系统的接口，降低耦合度。
	外观模式充分地体现了依赖倒转原则和迪米特法则
	依赖倒转原则：面向接口编程，外观模式封装了高层接口，客户端就只需对接口进行编程，不需知道以及操作底层复杂的子系统。
	迪米特法则：最少知道原则，高层模块（facade）隔离了两个不直接联系相关的模块。
*/
#include<iostream>
using namespace std;

/*
	具体功能类
*/
class ConcreteMethodA{
public:
	void func(){
		cout << "i am ConcreteMethodA" << endl;
	}
};

class ConcreteMethodB{
public:
	void func(){
		cout << "i am ConcreteMethodB" << endl;
	}
};

class ConcreteMethodC{
public:
	void func(){
		cout << "i am ConcreteMethodC" << endl;
	}
};

/*
外观类
*/
class Facade{
public:
	Facade(){
		p_a = new ConcreteMethodA();
		p_b = new ConcreteMethodB();
		p_c = new ConcreteMethodC();
	}

	void method_a(){
		p_a->func();
		p_c->func();
	}

	void method_b(){
		p_a->func();
		p_b->func();
	}

	void method_c(){
		p_b->func();
		p_c->func();
	}

protected:
	ConcreteMethodA * p_a;
	ConcreteMethodB * p_b;
	ConcreteMethodC * p_c;
};

// main
int main(int argc, char *argv[]){
	Facade * obj = new Facade();
	obj->method_a();
	cout << "--------------------" << endl;
	obj->method_b();
	cout << "--------------------" << endl;
	obj->method_c();
	return 0;
}