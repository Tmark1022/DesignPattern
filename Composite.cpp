/*
	组合模式：将对象组合成树形结构以表示‘部分-整体’的层次结构。
	组合模式使得用户对单个对象和组合对象的使用具有一致性。

	典型例子：文件结构
	在查看文件的时候，是能够查看到文件夹与具体文件的，但是他们的表示确实不同（例如文件夹双击还能再进入，而文件却是不能），
	如果将他们区别对待，那么客户端想要显示一个对象的时候就在写相应的判断逻辑区分这个对象是文件夹还是文件，然后才能却别的来显示。
	而使用组合模式，却是能将单个对象和组合对象相同对待起来（毕竟只是查看文件，文件夹和文件可以等同对待起来）
	组合模式通过使得文件类（叶子leaf）和文件夹类（树枝部分composite）继承相同的抽象基类，在基类里边统一了接口来使得单个对象和组合对象能够一致对待。
*/
#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
using namespace std;

// 抽象组件基类
class Component{
public:
	Component(string _name) :name(_name){}
	virtual void add(Component * ) = 0;
	virtual void remove(Component *) = 0;
	virtual void show(int depth = 1) = 0;

protected:
	string name;
};

// 文件类（叶子类）
class File :public Component{
public:
	File(string _name) :Component(_name){}
	virtual void add(Component * obj){
		abort();
	}
	virtual void remove(Component * obj){
		abort();
	}
	virtual void show(int depth = 1){
		for (int i = 1; i <= depth; ++i)
			cout << "-";
		cout << this->name << endl;
	}
};

// 文件夹类（树枝类）
class Folder :public Component{
public:
	Folder(string _name) :Component(_name){}
	~Folder(){
		for (auto pointer : vec){
			delete pointer;
			pointer = nullptr;
		}

		this->vec.clear();
	}

	virtual void add(Component * obj){
		if (nullptr == obj)
			return;
		this->vec.push_back(obj);
	}

	virtual void remove(Component * obj){
		auto iter = find(this->vec.begin(), this->vec.end(), obj);
		if (iter == this->vec.end())
			return;

		this->vec.erase(iter);
	}

	virtual void show(int depth = 1){
		// 输出自身
		for (int i = 1; i <= depth; ++i)
			cout << "-";
		cout << this->name << endl;

		// 输出其组成部分
		for (auto obj : this->vec)
			obj->show(depth + 2);
	}

protected:
	vector<Component*> vec;
};




// main
int main(int argc, char *argv[]){
	Component * root = new Folder("root");
	Component * dir1 = new Folder("dir1");
	Component * dir2 = new Folder("dir2");

	Component *file1 = new File("file1");
	Component *file2 = new File("file2");
	Component *file3 = new File("file3");
	Component *file4 = new File("file4");

	dir1->add(file2);

	dir2->add(file3);
	dir2->add(file4);

	root->add(dir1);
	root->add(dir2);
	root->add(file1);
	root->remove(file1);

	root->show(1);
	cout << "-----------------分割线--------------------" << endl;
	dir1->show(1);
	cout << "-----------------分割线--------------------" << endl;
	dir2->show(1);
	cout << "-----------------分割线--------------------" << endl;
	file1->show(1);
	cout << "-----------------分割线--------------------" << endl;





	return 0;
}



