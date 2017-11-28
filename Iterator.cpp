/*
	迭代器模式：提供一种方法来顺序的遍历聚合对象（vector）里边的各个元素。
	
	当需求需要遍历聚合对象内的各个元素（不管遍历的顺序（多种）），这时候就可以使用迭代器模式了。
*/
#include<iostream>
using namespace std;

// 抽象迭代器类（定义顺序遍历的方式）
class AbstractIterator{
public:
	// 第一个元素
	virtual void first() = 0;
	// 下一个元素
	virtual void next() = 0;
	// 是否结尾
	virtual bool end() = 0;
	// 当前的元素
	virtual int current_item() = 0;
};


// 聚合对象抽象类
class AbstractContainer{
public:
	AbstractContainer(){
		count = 0;
		max = 1024;
	}

	// 创建迭代器的虚函数，有多种迭代器形式就在这里写多少种
	virtual AbstractIterator * create_iterator() = 0;
	virtual AbstractIterator * create_iterator_desc() = 0;

	// 获得元素
	int get(int index){
		if (index >= this->count){
			cout << "out of range" << endl;
			return -1;
		}

		return this->array[index];
	}

	// 添加元素
	void add(int value){
		this->array[this->count] = value;
		this->count += 1;
	}

	// 获得当前元素个数
	int get_count()
	{
		return this->count;
	}

protected:
	int array[1024];
	int count;
	int max;
};





// 顺序访问迭代器类
class Iterator : public AbstractIterator{
public:
	Iterator(AbstractContainer * pointer){
		this->container = pointer;
		this->now_cnt = -1;
	}

	// 第一个元素
	virtual void first(){
		this->now_cnt = 0;	
	}
	// 下一个元素
	virtual void next(){
		this->now_cnt += 1;
	}
	// 是否结尾
	virtual bool end(){
		return this->now_cnt >= this->container->get_count() ? true : false;
	}
	// 当前的元素
	virtual int current_item(){
		if (this->end())
			return -1;
		return this->container->get(this->now_cnt);
	}

protected:
	AbstractContainer * container;
	int now_cnt;
};




// 倒序访问迭代器类
class IteratorDesc : public AbstractIterator{
public:
	IteratorDesc(AbstractContainer * pointer){
		this->container = pointer;
		this->now_cnt = -1;
	}

	// 第一个元素
	virtual void first(){
		this->now_cnt = this->container->get_count() - 1;
	}
	// 下一个元素
	virtual void next(){
		this->now_cnt -= 1;
	}
	// 是否结尾
	virtual bool end(){
		return this->now_cnt < 0 ? true : false;
	}
	// 当前的元素
	virtual int current_item(){
		if (this->end())
			return -1;
		return this->container->get(this->now_cnt);
	}

protected:
	AbstractContainer * container;
	int now_cnt;
};


class ConcreteContainer :public AbstractContainer{
public:
	ConcreteContainer() :AbstractContainer(){

	}

	// 创建迭代器的虚函数，有多种迭代器形式就在这里写多少种
	virtual AbstractIterator * create_iterator(){
		return new Iterator(this);
	}

	virtual AbstractIterator * create_iterator_desc(){
		return new IteratorDesc(this);
	}

};


// main
int main(int argc, char *argv[]){
	ConcreteContainer * container = new ConcreteContainer();

	for (int a = 1; a <= 10; ++a)
		container->add(a);

	// 顺序遍历
	AbstractIterator * iter1 = container->create_iterator(); 
	iter1->first(); 
	while (!iter1->end()){
		cout << iter1->current_item() << endl;
		iter1->next();
	}

	cout << "-------------------------分割线---------------------------" << endl;

	AbstractIterator * iter2 = container->create_iterator_desc();
	iter2->first();
	while (!iter2->end()){
		cout << iter2->current_item() << endl;
		iter2->next();
	}

	return 0;
}


