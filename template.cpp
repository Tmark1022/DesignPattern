/*
	模板方法模式
	定义一些类似于钩子hook的空函数，等待到了子类在具体实现。
*/
#include<iostream>
using namespace std;

class TestPaper{
public:
	void question(){
		cout << "你是高比拜仁？" << endl;
		cout << answer() << endl;
	}

	virtual char answer(){
		return '#';
	}
};

class TestPaperA : public TestPaper{
	virtual char answer(){
		return 'y';
	}
};

int main(int argc, char * argv[]){
	TestPaper * obj = new TestPaperA();
	obj->question();
	return 0;
}