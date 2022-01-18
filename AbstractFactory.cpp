/*
	抽象工厂模式：提供一个创建一些列相关类对象的接口（工厂方法就是创建一种类对象，就不是一系列）
	优点：适合产品线更换的需求
	缺点：当需求是增加产品线中的新的产品类，那么就需要修改全部抽象工厂类
*/
#include<iostream>
using namespace std;



/*
	每一代产品有手机和手表两种， 创建抽象工厂，用于实例化每一代产品里的所有产品
   */

// 产品 : 手机
class AbstractProductPhone{
public:
	virtual void show() = 0;
	void call() {cout << "我能打电话" << endl;} 
};

class ConcreteProductPhone1 : public AbstractProductPhone{
public:
	virtual void show(){
		cout << "1代手机" << endl;
	}
};

class ConcreteProductPhone2 : public AbstractProductPhone{
public:
	virtual void show(){
		cout << "2代手机" << endl;
	}
};

// 产品 : 手表 
class AbstractProductWatch{
public:
	virtual void show() = 0;
	void time() {cout << "我能看时间" << endl;}
};

class ConcreteProductWatch1 : public AbstractProductWatch{
public:
	virtual void show(){
		cout << "1代手表" << endl;
	}
};

class ConcreteProductWatch2 : public AbstractProductWatch{
public:
	virtual void show(){
		cout << "2代手表" << endl;
	}
};


// 抽象工厂类
class AbstarctFactory{
public:
	virtual AbstractProductPhone* CreateProductPhone() = 0;
	virtual AbstractProductWatch* CreateProductWatch() = 0;
};



// 第一代产品系列工厂
class FactoryGeneration1 : public AbstarctFactory{
public:
	virtual AbstractProductPhone* CreateProductPhone(){
		return new ConcreteProductPhone1();
	}

	virtual AbstractProductWatch* CreateProductWatch(){
		return new ConcreteProductWatch1();
	}
};

// 第二代产品系列工厂
class FactoryGeneration2 : public AbstarctFactory{
public:
	virtual AbstractProductPhone* CreateProductPhone(){
		return new ConcreteProductPhone2();
	}

	virtual AbstractProductWatch* CreateProductWatch(){
		return new ConcreteProductWatch2();
	}
};

// main 
int main(int argc, char * argv[]){

	// 创建抽象工厂对象（当更换产品线时，只需要更改这个就可以了）
	// AbstarctFactory * factory = new FactoryGeneration1();
	AbstarctFactory * factory = new FactoryGeneration2();

	// 创建具体的产品对象
	AbstractProductPhone * product_phone = factory->CreateProductPhone();
	AbstractProductWatch * product_watch = factory->CreateProductWatch();

	// 输出
	product_phone->show();
	product_phone->call();
	product_watch->show();
	product_watch->time();

	return 0;
}
