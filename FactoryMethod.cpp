/*
工厂方法
*/
#include<iostream>
using namespace std;

// 产品基类
class ProductBase{
public:
	virtual void operation() = 0;
};

// 具体产品类A
class ProductA : public ProductBase{
public:
	virtual void operation(){
		cout << "i am product A" << endl;
	}
};

// 具体产品类B
class ProductB : public ProductBase{
public:
	virtual void operation(){
		cout << "i am product B" << endl;
	}
};

// 工厂基类
class FactoryBase{
public:
	virtual ProductBase * create() = 0;
};

// 具体工厂类A
class FactoryMethodA{
public:
	virtual ProductBase * create(){
		return new ProductA();
	}
};

// 具体工厂类B
class FactoryMethodB{
public:
	virtual ProductBase * create(){
		return new ProductB();
	}
};

// main 
int main(int argc, char *argv[]){
	FactoryMethodA * fma = new FactoryMethodA();
	FactoryMethodB * fmb = new FactoryMethodB();
	ProductBase * obja = fma->create();
	ProductBase * objb = fmb->create();
	obja->operation();
	objb->operation();
	return 0;
}