#include<vector>
#include<iostream>
using namespace std;
template<typename TVertex, typename TEdge>
class Graph
{
 private:
	struct destination {
		int id;
		TVertex des;
		TEdge edge;
	};
	struct Vertex{
		int id;
		TVertex source;
		vector<destination> dest;
	};
	vector<Vertex> table;
public:
	Graph()
	{

	}
	int ret_index(TVertex f_ver)
	{
		for (int i = 0; i < table.size(); i++)
		{
			if (table[i].source == f_ver) return table[i].id;
		}
		return -1;
	}
	void addVertex(TVertex tmp_source)
	{
		Vertex struct_to_add;
		struct_to_add.id = table.size();
		struct_to_add.source = tmp_source;
		table.push_back(struct_to_add);
	}
	void addEdge(TVertex source, TVertex des, TEdge ed)
	{
			int tmp_id=ret_index(source);
			int temp_id = ret_index(des);
			destination temp;
			temp.des = des;
			temp.edge = ed;
			temp.id = temp_id;
			table[tmp_id].dest.push_back(temp);
	}
	void delVertex(TVertex sourc) 
	{
		int ind = ret_index(sourc);
		for(int i = 0 ;i < ind;i++)
		{
			for (int j = 0; j < table[i].dest.size(); j++)
			{
				if (table[i].dest[j].des == sourc)
				{
					for (int k = j; k < table[i].dest.size() - 1; k++)
					{
						table[i].dest[k].des = table[i].dest[k + 1].des;
					}
					table[i].dest.pop_back();
				}
			}
		}
		for (int i = ind+1; i < table.size(); i++)
		{
			for (int j = 0; j < table[i].dest.size(); j++)
			{
				if (table[i].dest[j].des == sourc)
				{
					for (int k = j; k < table[i].dest.size() - 1; k++)
					{
						table[i].dest[k].des = table[i].dest[k + 1].des;
					}
					table[i].dest.pop_back();
				}
			}
		}
		for (int i = ind; i < table.size()-1; i++)
		{
			table[i] = table[i + 1];
		}
		table.pop_back();
	}
	void delEdge(TVertex source, TVertex des)
	{
		int ind_s = ret_index(source);
		int ind_d = ret_index(des);
		for (int i = 0; i < table[ind_s].dest.size()-1; i++)
		{
			if (table[ind_s].dest[i+1].id == ind_d)
			{
				for (int j = i; j < i < table[ind_s].dest.size() - 1; j++)
				{
					table[ind_s].dest[i] = table[ind_s].dest[i + 1];
				}
				table[ind_s].dest.pop_back();
			}
		}
	}
	void print()
	{
		for (int i = 0; i < table.size(); i++)
		{
			cout << table[i].source << ":  {";
			for (int j=0;j<table[i].dest.size();j++)
			{
				cout << table[i].dest[j].des<<"("<< table[i].dest[j].edge <<")";

			}
			cout << "}" << endl;
		}
	}
};
int main()
{
	Graph<int, int> A;
	A.addVertex(1);
	A.addVertex(2);
	//A.print();
	A.addEdge(1, 2, 3);
	//A.delEdge(1, 2);
	//A.delVertex(1);
	A.print();
	return 0;
}