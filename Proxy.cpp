/*
	代理模式
*/
#include<iostream>
using namespace std;

// 抽象实体类
class Subject{
public:
	virtual void operation() = 0;			// 定义暴露的接口
};

// 真实实体类
class RealSubject : public Subject{
public:
	virtual void operation(){
		cout << "真实的操作在这里。" << endl;
	}
};

RealSubject global_realsubject;		// 全局真实实体对象

// proxy 代理类
class Proxy : public Subject{
public:
	Proxy(){
		this->temp = &global_realsubject;
	}
	virtual void operation(){
		// handle something before do real operation
		// ......
		this->temp->operation();
	}

protected:
	RealSubject * temp;				// 对真实实体的一个引用
};

int main(int argc, char * argv[]){
	Proxy * obj = new Proxy();
	obj->operation();

	delete obj;
	return 0;
}
