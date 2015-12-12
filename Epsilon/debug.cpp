#include "database.h"
#include "debug.h"
#include "recorder.h"

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

void test_History()
{
	using std::cout;
	using std::endl;


	std::shared_ptr<Library> pdb = std::make_shared<Library>("0.csv");
	History his(pdb);

	pdb->add(Item(10, "5", 1, 1, 1));
	pdb->add(Item(9, "4", 1, 1, 1));
	cout << "add item complete" << endl;
	his.log("add 10,1,1,1,5");
	cout << "log complete" << endl;
	his.show();
	pdb->print();
	cout << "going to undo" << endl;
	his.undo();
	cout << "undo complete" << endl;
	pdb->print();
}

void test_Record()
{
	using std::cout;
	using std::endl;

	std::shared_ptr<Library> pdb = std::make_shared<Library>("0.csv");

	pdb->move(10, 1);
	pdb->add(Item(10, "5", 1, 1, 1));
	pdb->add(Item(9, "4", 1, 1, 1));
	//cout << "add item complete" << endl;
	pdb->print();
	
	//Record re0("add 10,1,1,1,5", pdb);
	//cout << "init record(add) complete" << endl;
	//re0.refrain(pdb);
	//cout << "refrain complete" << endl;
	Record re1("move 3 10", pdb);
	cout << "init record(move) complete" << endl;
	pdb->move(10, 3);
	cout << "move item complete" << endl;
	pdb->print();
	re1.refrain(pdb);
	cout << "refrain complete" << endl;
	pdb->print();
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
