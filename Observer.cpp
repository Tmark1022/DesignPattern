/*
	观察者模式：实现一对多的依赖关系， 是得多个观察者对象依赖某一主体对象；当主题对象的状态发生改变的时候，
				主题对象就会一一的通知它的观察者，使得观察者能够自动地改变自己的状态。

	观察者模式用于要实现当一个对象发生改变需要同时更新多个对象的系统，
	观察者模式贯彻了依赖倒转的原则，使得具体的主题对象类不依赖于具体的观察者类，而是依赖于抽象的观察者类（收集订阅它的观察者对象可能会千其百怪，完全没关系， 但都用update来更新状态）
	同时使得具观察类对象不依赖于具体的主题对象类，而是依赖于抽象的主题对象类（使得主题对象类发生改变的时候，不需要修改任何与其相关的观察者类，开闭原则）
 */

/*
	这里，我们用微信用户订阅微信公众号来说明观察者模式
*/

#include<iostream>
#include<vector>
#include<string>
using namespace std;

// 类的声明
class AbstractOfficalAccount;
class AbstractWeiXin;

// 抽象观察者类（抽象微信类）
class AbstractWeiXin{
public:
	AbstractWeiXin(string name_temp){
		name = name_temp;
	}

	string get_name(){
		return name;
	}

	virtual void update(AbstractOfficalAccount * oa){
		cout << "NULL" << endl;
	}

protected:
	string name;
};


// 抽象主题对象类(抽象微信公众号类)
class AbstractOfficalAccount{
#define RES_SUCCESS 1
#define RES_FAILED	0
public:
	typedef int RESTYPE;

	AbstractOfficalAccount(string name_temp){
		name = name_temp;
		p_vec = new vector<AbstractWeiXin*>();
	}

	~AbstractOfficalAccount(){
		/*
		释放vector容器不能释放对应的观察者
		for (auto iter = p_vec->begin(); iter != p_vec->end(); ++iter){
			if (*iter != NULL){
				delete  *iter;
				*iter = NULL;
			}	
		}
		*/
		this->p_vec->clear();
		delete p_vec;
	}

	RESTYPE attach(AbstractWeiXin * temp){
		if (temp == NULL)
			return RES_FAILED;
		// 判断是否已经订阅了
		auto iter = find(this->p_vec->begin(), this->p_vec->end(), temp);
		if (iter == this->p_vec->end()){
			this->p_vec->push_back(temp);
			return RES_SUCCESS;
		}
		else{
			cout << temp->get_name() << "已经订阅了公众号（" << this->get_name() << ")，不能重复关注。" << endl;
			return RES_FAILED;
		}
	}

	RESTYPE detach(AbstractWeiXin * temp){
		if (temp == NULL)
			return RES_FAILED;
		// 判断是否已经订阅了
		auto iter = find(this->p_vec->begin(), this->p_vec->end(), temp);
		
		if (iter == this->p_vec->end()){
			cout << temp->get_name() << "没有订阅公众号（" << this->get_name() << ")， 不能取消关注。" << endl;
			return RES_FAILED;
		}
		else{
			this->p_vec->erase(iter);
			return RES_SUCCESS;
		}
	}

	string get_name(){
		return name;
	}

	void notify(){
		for (auto iter = this->p_vec->begin(); iter != this->p_vec->end(); ++iter){
			(*iter)->update(this);
		}
	}

protected:
	string name;
	vector<AbstractWeiXin*> * p_vec;
};

// 具体的公众号类A
class ConcreteOfficalAccountA : public AbstractOfficalAccount{
public:
	ConcreteOfficalAccountA(string name_temp) : AbstractOfficalAccount(name_temp){}
};

// 具体的公众号类B
class ConcreteOfficalAccountB : public AbstractOfficalAccount{
public:
	ConcreteOfficalAccountB(string name_temp) : AbstractOfficalAccount(name_temp){}
};

// 具体观察者类A
class WeiXinA : public AbstractWeiXin
{
public:
	WeiXinA(string name_temp) : AbstractWeiXin(name_temp){}
	virtual void update(AbstractOfficalAccount * oa){
		cout << "type WeiXinA, " << "微信公众号（" << oa->get_name() << "）发布了新的文章，" << this->name << "已经收到推送通知了" << endl;
	} 
};

// 具体观察者类A
class WeiXinB : public AbstractWeiXin
{
public:
	WeiXinB(string name_temp) : AbstractWeiXin(name_temp){}
	virtual void update(AbstractOfficalAccount * oa){
		cout << "type WeiXinB, " << "微信公众号（" << oa->get_name() << "）发布了新的文章，" << this->name << "已经收到推送通知了" << endl;
	}
};

// main
int main(int argc, char * argv[]){
	// 创建公众号类
	AbstractOfficalAccount * oaA = new ConcreteOfficalAccountA("广州本地宝");
	AbstractOfficalAccount * oaB = new ConcreteOfficalAccountB("深圳通");

	// 创建微信类
	AbstractWeiXin * wxA = new WeiXinA("用户A");
	AbstractWeiXin * wxB = new WeiXinB("用户B");

	// 订阅关注操作
	oaA->attach(wxA);
	oaA->attach(wxB);
	oaB->attach(wxA);
	oaB->attach(wxB);
	oaB->detach(wxA);

	// 发布更新
	oaA->notify();
	cout << "--------------------分割线----------------------" << endl;
	oaB->notify();

	return 0;
}



