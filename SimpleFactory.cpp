/*
	简单工厂
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

// 简单工厂类
class SimpleFactory{
public:
	static ProductBase * create(char type){
		switch (type)
		{
		case 'A':return new ProductA(); break;
		case 'B':return new ProductB(); break;
		default:
			return NULL;
			break;
		}
	}
};


// main 
int main(int argc, char *argv[]){
	ProductBase * obja = SimpleFactory::create('A');
	obja->operation();
	ProductBase * objb = SimpleFactory::create('B');
	objb->operation();

	return 0;
}