#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <iterator>

#include "debug.h"

void surface()
{
	using std::string;
	using std::cin;
	using std::cout;
	using std::endl;
	using std::vector;
	using std::istringstream;
	using std::stoi;

	//debug();

	Library db("test.csv");

	string input;
	while (std::getline(cin, input))
	{
		istringstream in(input);

		vector<string> limb;
		auto it=std::back_inserter(limb);

		string temp;
		while (in >> temp)
		{
			*it = temp;
		}

		if (*limb.cbegin() == "!q")
		{
			break;
		}
		else if (*limb.cbegin() == "print")
		{
			if (limb.size() == 1)
			{
				db.print();
			}
			else if (limb.size() == 3)
			{
				db.print(limb[1], limb[2]);
			}
		}
		else if (limb[0] == "load")
		{
			if (limb.size() == 1)
			{
				limb.push_back(db.file());
			}
			else
			{
				db.file(limb[1]);
			}
			db.load(limb[1]);
		}
		else if (limb[0] == "save")
		{
			if (limb.size() == 1)
			{
				limb.push_back(db.file());
			}
			else
			{
				db.file(limb[1]);
			}
			db.save(limb[1]);
		}
		else if (limb.size() == 2)
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
				int identify, type, status, location;
				string information;

				ins >> identify;
				ins >> type;
				ins >> status;
				ins >> location;
				ins >> information;

				//std::cout << identify << "," << type << "," << status << "," << location << "," << information << std::endl;

				Item one(identify, information, type, status, location);
				one.show();
				db.add(one);
			}
			else if (*limb.cbegin() == "del")
			{
				int id;
				while (ins >> id)
				{
					db.del(id);
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
					db.move(id, stoi(limb[1]));
				}
			}
			else if (*limb.cbegin() == "slip")
			{
				for (auto id : trgs)
				{
					db.slip(id, stoi(limb[1]));
				}
			}
			else if (*limb.cbegin() == "edit")
			{
				for (auto id : trgs)
				{
					db.edit(id, limb[1]);
				}
			}
		}
		
	}

	system("pause");
}

