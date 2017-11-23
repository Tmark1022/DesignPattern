/*
	适配器模式：将一个类的接口转换成客户想要的另一个接口模式（双方在短时间都不可能修改自身的东西，这时适配器模式就很重要了）
*/
#include<iostream>
#include<string>
using namespace std;

// 抽象运动员类
class player{
public:
	player(string name) :player_name(name){}
	virtual void defence() = 0;
	virtual void Attack() = 0;
public:
	string player_name;

};

// 美国本土运动员类
class AmericanPlayer : public player{
public:
	AmericanPlayer(string name) : player(name){}
	virtual void defence(){
		cout << "hey " << this->player_name << ", go to defend" << endl;
	}
	virtual void Attack(){
		cout << "hey " << this->player_name << ", go to attack" << endl;
	}
};

// 中国运动员类
class YunDongYuan{
public:
	YunDongYuan(string name) : ming_zi(name){}
	void FangShou(){
		cout << "喂 " << this->ming_zi << ", 快去防守" << endl;
	}
	void JinGong(){
		cout << "喂 " << this->ming_zi << ", 快去进攻" << endl;
	}

public:
	string ming_zi;
};

// 一个适配器类，专门适配中国运动员
class AdapterPlayer : public player{
public:
	AdapterPlayer(string name): player(name){
		china_player = new YunDongYuan(name);
	}

	virtual void defence(){
		china_player->FangShou();
	}
	virtual void Attack(){
		china_player->JinGong();
	}

private:
	YunDongYuan * china_player;
};


// main
int main(int argc, char *argv[]){
	player * kobe = new AmericanPlayer("kone bryant");
	player * yao = new AdapterPlayer("姚明");

	kobe->defence();
	kobe->Attack();

	yao->defence();
	yao->Attack();


	return 0;
}