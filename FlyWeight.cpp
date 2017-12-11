/*
	享元模式(FlyWeight):运用共享技术有效地支持大量细粒度的对象。
	总结来说就是享元模式使得共享使用相同的对象，避免创建大量新的相同作用的对象造成巨大资源浪费。
*/
#include<iostream>
#include<map>
#include<string>
#include<algorithm>
using namespace std;

// 抽象网网站类
class WebSite{
public:
	virtual void operation(string user_name) = 0;
};

// 博客网站类
class BlogWebSite : public WebSite{
public:
	virtual void operation(string user_name){
		cout << user_name << "的博客" << endl;
	}
};

// 产品展示网站类
class ProductionWebSite : public WebSite{
public:
	virtual void operation(string user_name){
		cout << user_name << "的产品展示网站" << endl;
	}
};


// 网站工厂
typedef map<string, WebSite*> WebSiteContainer;
class WebSiteFactory{
public:
	WebSiteFactory(){
		flyweights = new WebSiteContainer();
	}
	
	WebSite* get_website_obj(string type){
		WebSite* temp = nullptr;
		auto iter = flyweights->find(type);
		if (iter == flyweights->end()){
			if (type == "Blog"){
				(*flyweights)[string("Blog")] = temp = new BlogWebSite();
			}
			else if (type == "Production"){
				(*flyweights)[string("Production")] = temp = new ProductionWebSite();
			}
			else
				cout << "不存在的网站类型" << endl;
			return temp;
		}
		else{
			return iter->second;
		}
	}
	
protected:
	WebSiteContainer * flyweights;
};



// main
int main(int argc, char *argv[]){
	// 初始化工厂
	WebSiteFactory * factory = new WebSiteFactory();
	
	// 博客
	WebSite * blog1 = factory->get_website_obj("Blog");
	cout << "对象内存地址" << blog1 << endl;
	blog1->operation("小杨");

	WebSite * blog2 = factory->get_website_obj("Blog");
	cout << "对象内存地址" << blog2 << endl;
	blog1->operation("小明");

	WebSite * blog3 = factory->get_website_obj("Blog");
	cout << "对象内存地址" << blog3 << endl;
	blog1->operation("小红");

	cout << "---------------------分割线-----------------------" << endl;

	// 产品展示
	WebSite * pro1 = factory->get_website_obj("Production");
	cout << "对象内存地址" << pro1 << endl;
	pro1->operation("苹果公司");

	WebSite * pro2 = factory->get_website_obj("Production");
	cout << "对象内存地址" << pro2 << endl;
	pro2->operation("华为公司");

	WebSite * pro3 = factory->get_website_obj("Production");
	cout << "对象内存地址" << pro3 << endl;
	pro3->operation("小米公司");
	
	cout << "---------------------分割线-----------------------" << endl;

	// 不存在的类型
	WebSite * test = factory->get_website_obj("Test");
	cout << "对象内存地址" << test << endl;

	return 0;
}
