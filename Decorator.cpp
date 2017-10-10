/*
	装饰者模式
*/

#include<iostream>

// 抽象基类（不能实例化）
class Component{
public:
	virtual void operation() = 0;
};

// ConcreteComponent
class ConcreteComponent : public Component{
public:
	virtual void operation(){
		std::cout << "我是具体操作" << std::endl;
	}
};

// 抽象装饰类
class Decorator :public Component{
public:
	void set_component(Component * temp){
		this->component = temp;
	}

protected:
	Component * component = NULL;
};

// 具体装饰类A
class ConcreteDecoratorA :public Decorator{
public:
	void add_behavior_before_operation(){
		std::cout << "我是具体装饰类A（ConcreteDecoratorA）-->before" << std::endl;
	}

	void add_behavior_after_operation(){
		std::cout << "我是具体装饰类A（ConcreteDecoratorA）-->after" << std::endl;
	}

	virtual void operation(){
		this->add_behavior_before_operation();
		this->component->operation();
		this->add_behavior_after_operation();
	}
};

// 具体装饰类B
class ConcreteDecoratorB :public Decorator{
public:
	void add_behavior_before_operation(){
		std::cout << "我是具体装饰类B（ConcreteDecoratorA）-->before" << std::endl;
	}

	void add_behavior_after_operation(){
		std::cout << "我是具体装饰类B（ConcreteDecoratorA）-->after" << std::endl;
	}

	virtual void operation(){
		this->add_behavior_before_operation();
		this->component->operation();
		this->add_behavior_after_operation();
	}
};

// main
int main(int argc, char *argv[]){
	ConcreteComponent *pcc = new ConcreteComponent();
	ConcreteDecoratorA *pcda = new ConcreteDecoratorA();
	ConcreteDecoratorB *pcdb = new ConcreteDecoratorB();

	// 装饰顺序
	pcda->set_component(pcc);
	pcdb->set_component(pcda);

	// do
	pcdb->operation();

	return 0;
}