/*
	单列模式：使得一个类只有一个对象。
	
	解决多线程时候的单例模式：加锁
	避免每一次都加锁：双重锁定
*/
#include<iostream>
using namespace std;

class Singleton{
public:
	static Singleton * get_instance(){
		// 最普通的方式，没有解决多线程
		if (instance == nullptr){
			return new Singleton();
		}
		return instance;
	}

private:
	// 将构造函数设置为私有，设置一个public的 接口来控制只能初始化一次
	Singleton(){
		instance = this;
		cout << "调用Singleton的构造函数" << endl;
	}
	static Singleton * instance;
};

// 初始化类静态成员函数
Singleton * Singleton::instance = nullptr;

// main
int main(int ragc, char *argv[]){
	Singleton * temp = Singleton::get_instance();
	cout << "对象1内存地址：" << temp << endl;

	cout << "----------------------分割线-----------------------" <<endl;

	Singleton * temp2 = Singleton::get_instance();
	cout << "对象2内存地址：" << temp << endl;

	return 0;
}