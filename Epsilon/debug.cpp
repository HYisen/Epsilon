#include "database.h"
#include "debug.h"

#include <sstream>
#include <random>
#include <ctime>


void debug()
{
	using std::cout;
	using std::endl;

	cout << "Debug Mode" << endl;


	//test_Item();

	test_Library();

	cout << "Debug Finished" << endl;

	system("pause");
}

void test_Library()
{
	using std::cout;
	using std::endl;


	Library db;

	//db.load();

	cout << "Library Tests" << endl;

	cout << "1st Print" << endl;

	db.print(cout);

	for (int k = 0; k != 10; ++k)
	{
		Item one = ramdom_creat(k);
		cout << "key=" << one.id() << endl;
		db.add(one);
	}

	cout << "2nd Print" << endl;
	db.print();

	db.search(2)->show();

	for (int k = 2; k != 15; ++k)
	{
		//auto trg = db.search(k);
		//trg->show();
		db.del(k);
	}

	cout << "3rd Print" << endl;
	db.print();

	//db.add(one);


	//db.save();
}

void test_Item()
{
	using std::cout;
	using std::endl;

	Item one;

	one.show();
	one.edit("Elephant");
	one.slip(2);
	one.move(1);
	cout << one;
	cout << one.print() << endl;

}

Item ramdom_creat(int id)
{
	static std::default_random_engine e(static_cast<unsigned>(std::time(0)));
	static std::uniform_int_distribution<int> what(1, 5);
	static std::uniform_int_distribution<int> how(1, 3);
	static std::uniform_int_distribution<int> where(1, 4);

	std::ostringstream os;

	os << "No." << id;

	//std::cout << "creating " << id << std::endl;

	return Item(id, os.str(), what(e), how(e), where(e));
}
