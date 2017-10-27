/*
	构造者模式
	构造者模式，将一个复杂对象的构建与其表示分离，那么可以使得同一个构造过程可以构建不同的表示（形状）。
	构造者模式与模板方法模式很相似。
	模板方法是在超类中定义了算法框架，而细节的实现留在了子类中进行完善。
	构造者模式着重于有相同的构建顺序但对象的构建却很复杂，使用指挥类来实现了复杂的对象构建过程。
*/
#include<iostream>
#include<cstdlib>
#include<vector>
#include<string>

using namespace std;

// 具体需要组装的产品类
class Product{
public:
	Product(){
		vec_p = new vector<string>();
	}

	~Product(){
		delete vec_p;
	}

	void show(){
		for (auto iter = vec_p->cbegin(); iter != vec_p->cend(); ++iter){
			cout << *iter << " ";
		}
		cout << endl;
	}

	void add_part(string temp){
		vec_p->push_back(temp);
	}

protected:
	vector<string> * vec_p;
};

// 抽象Builder类，定义了必须需要在子类进行重载的函数
// 这里就抽象成手机与手机操作系统的组装
class Builder{
public:
	Builder(){
		product_obj = new Product();
	}

	~Builder(){
		delete product_obj;
	}


	// 组装手机
	virtual void build_phone(){
		abort();
	}

	// 组装操作系统 
	virtual void build_system(){
		abort();
	}

	Product * get_product(){
		return product_obj;
	}

protected:
	Product * product_obj;
};

// 具体的builder方法类A
class ConcreteBuilderA : public Builder{
public:
	// 组装手机
	virtual void build_phone(){
		product_obj->add_part("苹果手机");
	}

	// 组装操作系统 
	virtual void build_system(){
		product_obj->add_part("IOS操作系统");
	}
};

// 具体的builder方法类B
class ConcreteBuilderB : public Builder{
public:
	// 组装手机
	virtual void build_phone(){
		product_obj->add_part("华为手机");
	}

	// 组装操作系统 
	virtual void build_system(){
		product_obj->add_part("安卓操作系统");
	}
};

// 指挥类，定义了复杂对象的具体构造过程
class Director{
public:
	static void create(Builder * p){
		p->build_phone();
		p->build_system();
	}
};


// main
int main(int argc, char *argv[]){
	Product * ptemp;
	ConcreteBuilderA * obj_a = new ConcreteBuilderA();
	Director::create(obj_a);
	ptemp = obj_a->get_product();
	ptemp->show();
	
	cout << "--------------分割线-----------------" << endl;

	ConcreteBuilderB * obj_b = new ConcreteBuilderB();
	Director::create(obj_b);
	ptemp = obj_b->get_product();
	ptemp->show();

	return 0;
}