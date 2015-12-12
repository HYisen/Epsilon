#include <iterator>
#include <vector>
#include <string>
#include <sstream>
#include <iomanip>

#include "recorder.h"
#include "database.h"

extern translate tran;

void Record::refrain(std::shared_ptr<Library> orig)
{
	using std::istringstream;
	using std::string;
	using std::vector;
	using std::stoi;

	istringstream in(command);

	vector<string> limb;
	auto it = std::back_inserter(limb);

	string temp;
	while (in >> temp)
	{
		*it = temp;
	}

	if (limb.size() == 2)
	{
		for (auto &ch : limb[1])
		{
			if (ch == ',')
			{
				ch = '\n';
			}
		}
		istringstream ins(limb[1]);
		if (*limb.cbegin() == "add")
		{
			orig->del(*(num.cbegin()));
		}
		else if (*limb.cbegin() == "del")
		{
			for (auto it : its)
			{
				orig->add(*it);
			}
		}
	}
	else if (limb.size() == 3)
	{
		/*
		vector<int> trgs;
		for (auto &ch : limb[2])
		{
			if (ch == ',')
			{
				ch = '\n';
			}
		}
		istringstream trg(limb[2]);
		int id;
		while (trg >> id)
		{
			trgs.push_back(id);
		}
		//no need to elucidate, as ID is already stored in num.
		*/
		if (*limb.cbegin() == "move")
		{
			auto ps = str.begin();
			for (auto id : num)
			{
				orig->move(id, tran.location(*ps));
				++ps;
			}
		}
		else if (*limb.cbegin() == "slip")
		{
			auto ps = str.begin();
			for (auto id : num)
			{
				orig->slip(id, tran.status(*ps));
				++ps;
			}
		}
		else if (*limb.cbegin() == "edit")
		{
			auto ps = str.begin();
			for (auto id : num)
			{
				orig->edit(id, *ps);
				++ps;
			}
		}
	}
}

void Record::vault(const std::string & command, std::shared_ptr<Library> orig)
{
	using std::istringstream;
	using std::string;
	using std::vector;

	istringstream in(command);

	vector<string> limb;
	auto it = std::back_inserter(limb);

	string temp;
	while (in >> temp)
	{
		*it = temp;
	}

	if (limb.size() == 2)
	{
		for (auto &ch : limb[1])
		{
			if (ch == ',')
			{
				ch = '\n';
			}
		}
		istringstream ins(limb[1]);
		if (*limb.cbegin() == "add")
		{
			int identify;
			string information;

			ins >> identify;

			num.push_back(identify);
		}
		else if (*limb.cbegin() == "del")
		{
			int id;
			while (ins >> id)
			{
				its.push_back(orig->search(id));
			}
		}
	}
	else if (limb.size() == 3)
	{
		vector<int> trgs;
		for (auto &ch : limb[2])
		{
			if (ch == ',')
			{
				ch = '\n';
			}
		}
		istringstream trg(limb[2]);
		int id;
		while (trg >> id)
		{
			trgs.push_back(id);
		}

		if (*limb.cbegin() == "move")
		{
			for (auto id : trgs)
			{
				num.push_back(id);
				str.push_back(orig->search(id)->where());
			}
		}
		else if (*limb.cbegin() == "slip")
		{
			for (auto id : trgs)
			{
				num.push_back(id);
				str.push_back(orig->search(id)->how());
			}
		}
		else if (*limb.cbegin() == "edit")
		{
			for (auto id : trgs)
			{
				num.push_back(id);
				str.push_back(orig->search(id)->info());
			}
		}
	}
}

void History::log(const std::string & command)
{
	records.emplace_back(command,orig);
}

void History::undo(int id)
{
	
	if (id == -1)//undo only one step
	{
		auto it = records.end() - 1;
		std::cout << "undo:\t" << it->order() << std::endl;
		it->refrain(orig);
		records.erase(it);
	}
	else if(id<records.size())
	{
		auto n = records.size() - id;
		while (n)
		{
			auto it = records.end() - 1;
			std::cout << "undo:\t" << it->order() << std::endl;
			it->refrain(orig);
			records.erase(it);
			--n;
		}
	}
}

void History::show(std::ostream &os)
{
	int n = -1;
	for (auto one : records)
	{
		os << std::setw(4) << ++n << ":" << one.order() << std::endl;
	}

	os << "history showed" << std::endl;
}
