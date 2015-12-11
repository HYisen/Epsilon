#include <sstream>
#include <iomanip>
#include <fstream>

#include "database.h"

translate tran;

void Item::show(std::ostream &os) const
{
	using std::endl;

	//os << "id(" << identify << ")\t info(" << information << ")\nwhat(" << status << ")\thow(" << status << ")\twhere(" << location << ")" << endl;

	os << "id(" << id() << ")\t info(" << info()
		<< ")\nwhat(" << type << what() << ")\thow(" << status << how() << ")\twhere(" << location << where() << ")" << endl;
}

std::ostream &operator<<(std::ostream &os, const Item &orig)
{
	orig.show(os);
	return os;
} 

inline const std::string Item::what() const
{
	return tran.type(type);
}

inline const std::string Item::how() const
{
	return tran.status(status);
}

inline const std::string Item::where() const
{
	return tran.location(location);
}

const std::string Item::print() const
{
	using std::setw;

	std::ostringstream os;

	os << setw(5) << id() << setw(12) << what() << setw(12) << how() << setw(12) << where() << setw(16) << info();

	return os.str();
}

inline bool Item::operator==(const Item & rhs)
{
	return (this->identify == rhs.identify) && 
		(this->information == rhs.information) &&
		(this->type == rhs.type) && (this->status == rhs.status) &&
		(this->location == rhs.location);
}

bool Item::edit(const std::string &info)
{
	information = info;

	return true;
}

bool Item::slip(int how)
{
	status = how;

	return true;
}

bool Item::move(int where)
{
	location = where;

	return true;
}

Library::~Library()
{
	save(filename);
}

void Library::load(std::string trg_filename)
{
	using std::getline;
	using std::string;

	std::ifstream file(trg_filename);

	std::string line;

	while (getline(file, line))
	{
		for (auto &ch : line)
		{
			if (ch == ',')
			{
				ch = '\n';
			}
		}

		std::istringstream in(line);

		int identify;
		string type, status, location, information;

		in >> identify;
		in >> type;
		in >> status;
		in >> location;
		in >> information;

		//std::cout << identify << "," << type << "," << status << "," << location << "," << information << std::endl;

		add(Item(identify, information, tran.type(type), tran.status(status), tran.location(location)));
	}

	std::cout << "LOAD from " << filename << std::endl;
}

void Library::save(std::string src_filename)
{
	std::ofstream file(src_filename);

	for (auto one : data)
	{
		file << one.second->id() << "," <<
			one.second->what() << "," <<
			one.second->how() << "," <<
			one.second->where() << "," <<
			one.second->info() << std::endl;
	}

	std::cout << "SAVE to " << src_filename << std::endl;
}

bool Library::add(const Item & orig)
{
	//std::cout << (data.find(orig.id()) != data.cend()) << "adding ID= " << orig.id() << std::endl;

	auto ptr = std::make_shared<Item>(orig);

	if (data.find(orig.id()) != data.cend())
	{
		std::cout << "same ID existed." << std::endl;
		return false;
	}

	data.insert(std::make_pair(ptr->id(), ptr));
	index_addr.insert(std::make_pair(ptr->where(), ptr));
	index_type.insert(std::make_pair(ptr->what(), ptr));

	return true;
}

bool Library::del(int id)
{
	if (data.find(id) == data.cend())
	{
		std::cout <<data.count(id)<< "No such ID(" <<id<<")"<< std::endl;
		return false;
	}


	for (auto ita = index_addr.lower_bound(data[id]->where()); ita != index_addr.upper_bound(data[id]->where()); ++ita)
	{
		if (ita->second == data[id])
		{
			index_addr.erase(ita);
			break;
		}
	}
	
	for (auto ita = index_type.lower_bound(data[id]->what()); ita != index_type.upper_bound(data[id]->what()); ++ita)
	{
		if (ita->second == data[id])
		{
			index_type.erase(ita);
			break;
		}
	}

	data.erase(id);

	return true;
}

bool Library::edit(int id, const std::string &info)
{
	return search(id)->edit(info);
}

bool Library::slip(int id, int how)
{
	return search(id)->slip(how);
}

bool Library::move(int id, int where)
{
	return search(id)->move(where);
}

const std::shared_ptr<Item> Library::search(int id)
{
	return data.find(id)->second;
}




void Library::print(std::string command, std::string val, std::ostream & os)
{
	using std::string;
	using std::endl;

	if (command == string("addr"))
	{
		for (auto it = index_addr.lower_bound(val); it != index_addr.upper_bound(val);++it)
		{
			os << it->second->print() << endl;
		}
	}
	else if (command == string("type"))
	{
		for (auto it = index_type.lower_bound(val); it != index_type.upper_bound(val); ++it)
		{
			os << it->second->print() << endl;
		}
	}

	os << "Print finished." << endl;
}

void Library::print(std::ostream &os)
{
	for (auto one : data)
	{
		os << one.second->print() << std::endl;
	}

	os << "Print finished." << std::endl;
}

const int translate::type(const std::string & orig)
{
	if (orig == "undefined")
	{
		return 0;
	}
	else if (orig == "shirts")
	{
		return 1;
	}
	else if (orig == "T_shirts")
	{
		return 2;
	}
	else if (orig == "pants")
	{
		return 3;
	}
	else if (orig == "briefs")
	{
		return 4;
	}
	else if (orig == "socks")
	{
		return 5;
	}
	else
	{
		return -1;
	}
}

const std::string translate::type(const int orig)
{
	std::string str;

	switch (orig)
	{
	case 0:
		str = "undefined";
		break;
	case 1:
		str = "shirts";
		break;
	case 2:
		str = "T_shirts";
		break;
	case 3:
		str = "pants";
		break;
	case 4:
		str = "briefs";
		break;
	case 5:
		str = "socks";
		break;
	default:
		str = "error";
	}

	return str;
}

const int translate::status(const std::string & orig)
{
	if (orig == "undefined")
	{
		return 0;
	}
	else if (orig == "brand_new")
	{
		return 1;
	}
	else if (orig == "normal")
	{
		return 2;
	}
	else if (orig == "worned")
	{
		return 3;
	}
	else
	{
		return -1;
	}
}

const std::string translate::status(const int orig)
{
	std::string str;

	switch (orig)
	{
	case 0:
		str = "undefined";
		break;
	case 1:
		str = "brand_new";
		break;
	case 2:
		str = "normal";
		break;
	case 3:
		str = "worned";
		break;
	default:
		str = "error";
	}

	return str;
}

const int translate::location(const std::string & orig)
{
	if (orig == "undefined")
	{
		return 0;
	}
	else if (orig == "A")
	{
		return 1;
	}
	else if (orig == "B")
	{
		return 2;
	}
	else if (orig == "C")
	{
		return 3;
	}
	else if (orig == "D")
	{
		return 4;
	}
	else
	{
		return -1;
	}
}

const std::string translate::location(const int orig)
{
	std::string str;

	switch (orig)
	{
	case 0:
		str = "undefined";
		break;
	case 1:
		str = "A";
		break;
	case 2:
		str = "B";
		break;
	case 3:
		str = "C";
		break;
	case 4:
		str = "D";
		break;
	default:
		str = "error";
	}

	return str;
}
