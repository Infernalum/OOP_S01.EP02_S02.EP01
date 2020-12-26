#include "pch.h"
#include "D:\������� ����\C++\���\Operation ~Data Deleted~\Level Editor\BattleFieldClass\pch.h"

using namespace XCom;

TEST(Constructors, EmptyConstructor) {
	Creature* player = new Operative("�������");
	ASSERT_EQ("�������", dynamic_cast<Operative*>(player)->get_callname());
	ASSERT_EQ(-1, player->get_ID());
	ASSERT_EQ(1, player->get_sight());
	ASSERT_EQ(1, player->get_HP());
	ASSERT_EQ(1, player->get_maxHP());
	ASSERT_EQ(1, player->get_TP());
	ASSERT_EQ(1, player->get_maxTP());
	
}


TEST(Constructors, CopyConstructors) {
	Operative player1("�������");
	Operative player2(player1);
	ASSERT_EQ("�������", player2.get_callname());
	ASSERT_EQ(-1, player2.get_ID());
	ASSERT_EQ(1, player2.get_sight());	
	ASSERT_EQ(1, player2.get_HP());
	ASSERT_EQ(1, player2.get_TP());
	ASSERT_EQ(1, player2.get_maxTP());

}


TEST(Consructors, MoveConstructors) {
	Operative player(Operative("�����������"));
	ASSERT_EQ("�����������", player.get_callname());
	ASSERT_EQ(-1, player.get_ID());
	ASSERT_EQ(1, player.get_sight());
	ASSERT_EQ(1, player.get_HP());
	ASSERT_EQ(1, player.get_maxHP());
	ASSERT_EQ(1, player.get_TP());
	ASSERT_EQ(1, player.get_maxTP());

}

TEST(Methods, Callname) {
	Creature* player = new Operative("�������");
	dynamic_cast<Operative*>(player)->set_callname("������ �������");
	ASSERT_EQ("������ �������", dynamic_cast<Operative*>(player)->get_callname());
}


TEST(Methods, spriteID) {
	Creature* player1 = new Operative("�������");
	ASSERT_EQ(-1, dynamic_cast<Operative*>(player1)->get_ID());
}

TEST(Methods, Change_Weapon) {
	Operative* player1 = new Operative("�������");
	Weapon* rifle = new Weapon("������");
	player1->change_weapon(rifle);
	ASSERT_EQ(rifle, player1->get_hand());
	Weapon* rifle2 = new Weapon("������ �� �������");
	Weapon* res = nullptr;
	res = player1->change_weapon(rifle2);
	ASSERT_EQ(rifle2, player1->get_hand());
	ASSERT_EQ(res, rifle);
}

TEST(Methods, Add_Item) {
	Operative* player1 = new Operative("�������");
	Item* firstaidkit = new FirstAidKit;
	Item* weapon = new Weapon;
	Item* ammobox = new AmmoBox;
	player1->add_item(firstaidkit).add_item(ammobox).add_item(weapon);
	ASSERT_EQ(3, player1->size());
	std::ofstream file("Add_Item.txt"), table("table.txt"), config("config.txt");
	file << *player1;
	player1->save(config);
	player1->show_table(table);
}

TEST(Methods, Clone) {
	Operative* player1 = new Operative("�������");
	Operative* clone = player1->clone();
	ASSERT_EQ("�������", clone->get_callname());
	ASSERT_EQ(-1, clone->get_ID());
	ASSERT_EQ(1, clone->get_sight());
	ASSERT_EQ(1, clone->get_HP());
	ASSERT_EQ(1, clone->get_maxHP());
	ASSERT_EQ(1, clone->get_TP());
	ASSERT_EQ(1, clone->get_maxTP());
}


TEST(Methods, Load) {
	Operative* player1 = new Operative;
	std::ifstream config("config.txt");
	player1->load(config);
	player1->get_callname();
}
