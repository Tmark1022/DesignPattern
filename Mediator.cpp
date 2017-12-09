/*
	中介者模式：用一个中介对象来封装一系列对象的交互。
			   中介者对象使得各个对象不需要显式地进行相互引用，从而降低其耦合度。


*/
#include<iostream>
#include<string>
using namespace std;

class AbstractMediator;


// 抽象Colleague
class AbstractColleague{
public:
	AbstractColleague(string _name, AbstractMediator * _med){
		this->name = _name;
		this->med = _med;
	}

	virtual void send_message(string msg) = 0;
	virtual void get_message(string msg) = 0;

	string get_name(){
		return name;
	}

protected:
	string name;
	AbstractMediator * med;
};


// 抽象Mediator
class AbstractMediator{
public:
	AbstractMediator(string _name){
		this->name = _name;
		this->colleague_a = this->colleague_b = nullptr;
	}

	virtual void transmit_messages(string msg, AbstractColleague * sneder) = 0;

	void set_seller(AbstractColleague * obj){
		this->colleague_a = obj;
	}

	void set_buyer(AbstractColleague * obj){
		this->colleague_b = obj;
	}


protected:
	string name;
	AbstractColleague * colleague_a, *colleague_b;

};


// 具体colleague类
// 出售房子类
class seller : public AbstractColleague{
public:
	seller(string _name, AbstractMediator * _med) : AbstractColleague(_name, _med){}

	virtual void send_message(string msg){
		cout << "seller类， 我是" << this->name << ", 我向房屋中介传递了一条消息:" << msg << endl;
		this->med->transmit_messages(msg, this);
	}

	virtual void get_message(string msg){
		cout << "seller类， 我是" << this->name << ", 我从房屋中介接收到了一条消息:" << msg << endl;
	}
};

class Buyer : public AbstractColleague{
public:
	Buyer(string _name, AbstractMediator * _med) : AbstractColleague(_name, _med){}

	virtual void send_message(string msg){
		cout << "Buyer类， 我是" << this->name << ", 我向房屋中介传递了一条消息:" << msg << endl;
		this->med->transmit_messages(msg, this);
	}

	virtual void get_message(string msg){
		cout << "Buyer类， 我是" << this->name << ", 我从房屋中介接收到了一条消息:" << msg << endl;
	}
};


// 房屋中介类
class HouseMediater : public AbstractMediator{
public:
	HouseMediater(string _name) :AbstractMediator(_name){}

	virtual void transmit_messages(string msg, AbstractColleague * sender){
		if (sender == this->colleague_a){
			this->colleague_b->get_message(sender->get_name() + "说，" + msg);
		}
		else if (sender == this->colleague_b){
			this->colleague_a->get_message(sender->get_name() + "说，" + msg);
		}
		else
			cout << "你还没在中介者中绑定关联呢" << endl; 
	}
};

// main 
int main(int argc, char * argv[]){
	// 初始化对象
	AbstractMediator *med = new HouseMediater("开口笑中介");
	AbstractColleague * seller1 = new seller("李先生", med);
	AbstractColleague * buyer1 = new Buyer("麦女士", med);
	AbstractColleague * buyer2 = new Buyer("test先生", med);

	// 中介绑定关联
	med->set_seller(seller1);
	med->set_buyer(buyer1);

	// run
	buyer1->send_message("这房子多少钱?");
	cout << "---------------------------分割线---------------------------------" << endl;
	seller1->send_message("100W左右吧，我们聊聊。");
	cout << "---------------------------分割线---------------------------------" << endl;
	buyer2->send_message("test");

	return 0;
}
