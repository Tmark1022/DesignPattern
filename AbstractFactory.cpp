/*
	抽象工厂模式：提供一个创建一些列相关类对象的接口（工厂方法就是创建一种类对象，就不是一系列）
	优点：适合产品线更换的需求
	缺点：当需求是增加产品线中的新的产品类，那么就需要修改全部抽象工厂类
*/
#include<iostream>
using namespace std;

class AbstractProduct{
public:
	virtual void show() = 0;
};


// 产品线1
class AbstractProductLine1 :public AbstractProduct{
public:
	virtual void show() = 0;
};

class ConcreteProductLine1A : public AbstractProductLine1{
public:
	virtual void show(){
		cout << "line 1, ConcreteProductA" << endl;
	}
};

class ConcreteProductLine1B : public AbstractProductLine1{
public:
	virtual void show(){
		cout << "line 1, ConcreteProductB" << endl;
	}
};


// 产品线2
class AbstractProductLine2 :public AbstractProduct{
public:
	virtual void show() = 0;
};

class ConcreteProductLine2A : public AbstractProductLine2{
public:
	virtual void show(){
		cout << "line 2, ConcreteProductA" << endl;
	}
};

class ConcreteProductLine2B : public AbstractProductLine2{
public:
	virtual void show(){
		cout << "line 2, ConcreteProductB" << endl;
	}
};

// 抽象工厂类
class AbstarctFactory{
public:
	virtual AbstractProduct* CreateProductA() = 0;
	virtual AbstractProduct* CreateProductB() = 0;
};

// 产品线1的工厂
class Line1Factory : public AbstarctFactory{
public:
	virtual AbstractProduct* CreateProductA(){
		return new ConcreteProductLine1A();
	}

	virtual AbstractProduct* CreateProductB(){
		return new ConcreteProductLine1B();
	}
};

// 产品线2的工厂
class Line2Factory : public AbstarctFactory{
public:
	virtual AbstractProduct* CreateProductA(){
		return new ConcreteProductLine2A();
	}

	virtual AbstractProduct* CreateProductB(){
		return new ConcreteProductLine2B();
	}
};

// main 
int main(int argc, char * argv[]){

	// 创建抽象工厂对象（当更换产品线时，只需要更改这个就可以了）
	// AbstarctFactory * factory = new Line1Factory();
	AbstarctFactory * factory = new Line2Factory();

	// 创建具体的产品对象
	AbstractProduct * product_a = factory->CreateProductA();
	AbstractProduct * product_b = factory->CreateProductB();

	// 输出
	product_a->show();
	product_b->show();

	return 0;
}