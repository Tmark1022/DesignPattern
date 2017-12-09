/*
	职责链模式：使得多个对象都有机会处理一个请求，将多个对象排列成一条链，沿着这条链传递该请求，知道有一个对象处理该请求为止。
				从而避免请求的发送者和处理者之间发生耦合。
				这样可以使得客户端不知道请求到底是哪一个对象处理了请求，这样子系统就可以在不影响客户端的前提下动态地重新组织和分配责任。

	My comprehension : 职责连模式主要就是封装了请求判断与传递的过程，使用条件判断会使得天剑判断语句很庞大，很容易出现问题（这与状态模式很相似，都是拆分条件判断语句）。
						职责链模式将条件语句拆分为链表一样，先将链表结构组织好，然后请求就沿着这个链表结构传递，知道某个节点对象处理了这个请求。
*/
#include<iostream>
using namespace std;

#define Request int

// 抽象Handler类，后继的handler对象在这里封装处理
class AbstractHandler{
public:
	AbstractHandler(){
		succeeder = nullptr;
	}

	void set_succeeder(AbstractHandler * obj){
		this->succeeder = obj;
	}

	virtual void handle_request(Request req) = 0;

protected:
	AbstractHandler * succeeder;
};


class  ConcreteHandlerA : public AbstractHandler{
public:
	ConcreteHandlerA() : AbstractHandler(){}

	virtual void handle_request(Request req){
		if (req <= 10){
			cout << "ConcreteHandlerA 处理了请求(" << req << ")" << endl;
		}
		else if (this->succeeder != nullptr){
			this->succeeder->handle_request(req);
		}
		else
			cout << "已到链尾啦，但是没人能处理到该请求(" << req << ")" << endl;
	}
};

class  ConcreteHandlerB : public AbstractHandler{
public:
	ConcreteHandlerB() : AbstractHandler(){}

	virtual void handle_request(Request req){
		if (req <= 20){
			cout << "ConcreteHandlerB 处理了请求(" << req << ")" << endl;
		}
		else if (this->succeeder != nullptr){
			this->succeeder->handle_request(req);
		}
		else
			cout << "已到链尾啦，但是没人能处理到该请求(" << req << ")" << endl;
	}
};

class  ConcreteHandlerC : public AbstractHandler{
public:
	ConcreteHandlerC() : AbstractHandler(){}

	virtual void handle_request(Request req){
		if (req <= 100){
			cout << "ConcreteHandlerC 处理了请求(" << req << ")" << endl;
		}
		else if (this->succeeder != nullptr){
			this->succeeder->handle_request(req);
		}
		else
			cout << "已到链尾啦，但是没人能处理到该请求(" << req << ")" << endl;
	}
};

// main
int main(int argc, char * argv[]){
	// 初始化需要的对象
	AbstractHandler * handlera = new ConcreteHandlerA();
	AbstractHandler * handlerb = new ConcreteHandlerB();
	AbstractHandler * handlerc = new ConcreteHandlerC();

	// 设置职责链结构
	handlera->set_succeeder(handlerb);
	handlerb->set_succeeder(handlerc);

	// 测试1
	cout << "test1 : ";
	handlera->handle_request(1);

	// 测试2
	cout << "test2 : ";
	handlera->handle_request(20);

	// 测试3
	cout << "test3 : ";
	handlera->handle_request(99);

	// 测试4
	cout << "test4 : ";
	handlera->handle_request(199);

	return 0;
}