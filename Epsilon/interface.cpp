#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <iterator>
#include <memory>

#include "debug.h"
#include "recorder.h"

void surface()
{
	using std::string;
	using std::cin;
	using std::cout;
	using std::endl;
	using std::vector;
	using std::istringstream;
	using std::stoi;

	
	std::shared_ptr<Library> pdb = std::make_shared<Library>("test.csv");
	History his(pdb);
	
	

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
				pdb->print();
			}
			else if (limb.size() == 3)
			{
				pdb->print(limb[1], limb[2]);
			}
		}
		else if (limb[0] == "show")
		{
			his.show();
		}
		else if (limb[0] == "undo")
		{
			if (limb.size() == 1)
			{
				his.undo();
			}
			else if (limb.size() == 2)
			{
				his.undo(stoi(limb[1]));
			}
		}
		else if (limb[0] == "load")
		{
			if (limb.size() == 1)
			{
				limb.push_back(pdb->file());
			}
			else
			{
				pdb->file(limb[1]);
			}
			pdb->load(limb[1]);
		}
		else if (limb[0] == "save")
		{
			if (limb.size() == 1)
			{
				limb.push_back(pdb->file());
			}
			else
			{
				pdb->file(limb[1]);
			}
			pdb->save(limb[1]);
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
				his.log(input);
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
				pdb->add(one);
			}
			else if (*limb.cbegin() == "del")
			{
				his.log(input);
				int id;
				while (ins >> id)
				{
					pdb->del(id);
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

			his.log(input);
			if (*limb.cbegin() == "move")
			{
				for (auto id : trgs)
				{
					pdb->move(id, stoi(limb[1]));
				}
			}
			else if (*limb.cbegin() == "slip")
			{
				for (auto id : trgs)
				{
					pdb->slip(id, stoi(limb[1]));
				}
			}
			else if (*limb.cbegin() == "edit")
			{
				for (auto id : trgs)
				{
					pdb->edit(id, limb[1]);
				}
			}
		}
		
	}

	system("pause");
}

