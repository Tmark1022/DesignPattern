/*
	备忘录模式：在不破坏一个封装性的前提下，捕获一个对象的内部状态，并且在该对象之外保存这个状态，以后就可将对象恢复到之前保存的状态。
	
	将备份与恢复的逻辑封装起来,不暴露在客户端中（部分备份的什么内容只能在GameMemento设置）
*/
#include<iostream>
#include<string>
#include<vector>
using namespace std;

// 游戏存档类
class GameMemento{
public:
	GameMemento(string _map_name, int _hp, int _money){
		this->map_name = _map_name;
		this->hp = _hp;
		this->money = _money;
	}
	
	string get_map_name(){
		return this->map_name;
	}

	int get_hp(){
		return this->hp;
	}

	int get_money(){
		return this->money;
	}

private:
	string map_name;
	int hp;
	int money;
};

// 游戏类
class Game{
public:
	Game(){
		this->map_name = "default";
		this->hp = 100;
		this->money = 1000;
	}

	void show(){
		cout << "地图: " << this->map_name << endl;
		cout << "hp: " << this->hp << endl;
		cout << "money: " << this->money << endl;
	}


	void fight(){
		this->map_name = "Boss";
		this->hp = 0;
		this->money = 2000;
	}

	// 封装创建存档
	GameMemento * create_memento(){
		GameMemento * memento_obj = new GameMemento(this->map_name, this->hp, this->money);
		return memento_obj;
	}

	// 封装恢复存档
	bool set_memento(GameMemento * memento_obj)
	{
		if (nullptr == memento_obj)
			return false;
		this->map_name = memento_obj->get_map_name();
		this->hp = memento_obj->get_hp();
		this->money = memento_obj->get_money();
	}

private:
	string map_name;
	int hp;
	int money;
};

// 存档管理类
class MementoCaretaker{
public:
#define SUCCESS true
#define FAILED false
public:
	~MementoCaretaker(){
		for (auto iter : memento_list)
		{
			delete iter;
			iter = nullptr;
		}
		memento_list.clear();
	}

	bool add_memento(GameMemento * memento_pointer){
		if (nullptr == memento_pointer)
			return FAILED;

		memento_list.push_back(memento_pointer);
		return SUCCESS;
	}

	GameMemento * get_memento(int index){
		return memento_list[index];
	}

private:
	vector<GameMemento * > memento_list;
};


// main 
int main(int argc, char *argcv[])
{
	// game 对象
	Game * game_obj = new Game();
	game_obj->show();

	cout << "----------------------分割线------------------------" << endl;

	// MementoCaretaker 对像
	MementoCaretaker * caretaker_obj = new MementoCaretaker();

	// 创建第一个存档（战斗前）
	caretaker_obj->add_memento(game_obj->create_memento());

	// 战斗
	game_obj->fight();
	game_obj->show();
	cout << "----------------------分割线------------------------" << endl;

	// 创建第二个存档（战斗后）
	caretaker_obj->add_memento(game_obj->create_memento());

	// 恢复战斗前的存档
	game_obj->set_memento(caretaker_obj->get_memento(0));
	game_obj->show();
	cout << "----------------------分割线------------------------" << endl;

	// 恢复战斗后的存档
	game_obj->set_memento(caretaker_obj->get_memento(1));
	game_obj->show();
	cout << "----------------------分割线------------------------" << endl;

	return 0;
}