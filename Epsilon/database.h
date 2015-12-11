#ifndef DATABASE_H_
#define DATABASE_H_

#include <iostream>
#include <string>
#include <map>
#include <memory>

class translate
{
public:
	const int type(const std::string &orig);
	const std::string type(const int orig);
	const int status(const std::string &orig);
	const std::string status(const int orig);
	const int location(const std::string &orig);
	const std::string location(const int orig);
};

class Item
{
public:
	Item(int id = 0,
		std::string info = std::string("Null"),
		int what = 0,
		int how = 0,
		int where = 0)
		:identify(id), information(info), type(what), status(how), location(where) {}
	Item(const Item &orig) = default;

	void show(std::ostream &os = std::cout) const;
	const int id() const
	{
		return identify;
	}
	const std::string info() const
	{
		return information;
	}
	const std::string what() const;
	const std::string how() const;
	const std::string where() const;
	const std::string print() const;

	bool operator==(const Item &rhs);

	bool edit(const std::string &info);
	bool slip(int how);
	bool move(int where);

	
private:
	int identify;
	std::string information;
	int type;
	int status;
	int location;
};

class Library
{
public:
	Library(std::string db_filename = std::string("db.csv")) :filename(db_filename)
	{ 
		load(filename);
	}
	~Library();

	void load(std::string src_filename);
	void save(std::string trg_filename);

	bool add(const Item &orig);
	bool del(int id);

	bool edit(int id, const std::string &info);
	bool slip(int id, int how);
	bool move(int id, int where);

	const std::shared_ptr<Item> search(int id);

	const std::string &file() const
	{
		return filename;
	}
	const std::string &file(std::string &name)
	{
		return filename=name;//not check for equality.
	}

	void print(std::string command, std::string val, std::ostream &os = std::cout);
	void print(std::ostream &os = std::cout);

private:
	std::map<int, std::shared_ptr<Item>> data;//data in id order
	std::multimap<std::string, std::shared_ptr<Item>> index_addr;//index in address order
	std::multimap<std::string, std::shared_ptr<Item>> index_type;//index in type order

	std::string filename;
};

std::ostream &operator<<(std::ostream &os, const Item &orig);
#endif