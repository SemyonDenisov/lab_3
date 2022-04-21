#include<vector>
#include<iostream>
using namespace std;
template<typename TVertex, typename TEdge>
class Graph
{
 private:
	 struct sv {//for deep search 
		 int color = 0;
		 TVertex prev;
		 int t_open = 0;
		 int t_close = 0;
	 };
	struct destination {
		int id;
		TVertex des;
		TEdge edge;
	};
	struct Vertex{
		int id;
		TVertex source;
		vector<destination> dest;
		sv inf;
	};
	vector<Vertex> table;
public:
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
			table[i].id--;
		}
		table.pop_back();
	}
	void delEdge(TVertex source, TVertex des)
	{
		int ind_s = ret_index(source);
		int ind_d = ret_index(des);
		for (int i = 0; i < table[ind_s].dest.size(); i++)
		{
			if (table[ind_s].dest[i].id == ind_d)
			{
				for (int j = i; j < table[ind_s].dest.size() - 1; j++)
				{
					table[ind_s].dest[i] = table[ind_s].dest[i + 1];
					table[ind_s].dest[i].id--;
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
	void deep_search()
	{
		int t = 0;
		deep(table[0],t);
		for (int i = 0; i < table.size(); i++)
		{
			if (table[i].inf.color == 0)
			{
				deep(table[i], t);
			}
		}
	}
	void deep(Vertex s,int &t)
	{
		table[s.id].inf.color = 1;
		table[s.id].inf.t_open = t;
		t++;
		for (int j = 0; j < table[s.id].dest.size(); j++)
		{
			if (table[table[s.id].dest[j].id].inf.color == 0)
			{
				table[table[s.id].dest[j].id].inf.prev = table[s.id].source;
				deep(table[table[s.id].dest[j].id], t);
			}
		}
		table[s.id].inf.color = 2;
		table[s.id].inf.t_close = t;
		cout << table[s.id].source << endl;
		t++;
	}
	void bellman_ford(TVertex source ,TVertex dest)
	{

		TEdge d[4];
		for (int i = 0; i < table.size(); i++)
		{
			d[i] = 1000000000;
		}
		d[ret_index(source)] = 0;
		vector<vector<TVertex>> ways(table.size());
		/*for (int i = 0; i < table.size(); i++)
		{
			ways[i].push_back(source);
		}*/
		for (int i = 0; i < table.size(); i++)
		{
			for (int j = 0; j < table[i].dest.size(); j++)
			{
				if (d[i] + table[i].dest[j].edge < d[table[i].dest[j].id])
				{
					d[table[i].dest[j].id] = d[i] + table[i].dest[j].edge;
					//if (table[i].dest[j].id == ret_index(dest) )
					{
						ways[table[i].dest[j].id] = ways[i];
						ways[table[i].dest[j].id].push_back(table[i].id + 1);
					
					}
				}
			}
		}
		for (int i = 0; i < table.size(); i++)
		{
			ways[i].push_back(table[i].id+1);
		}
		for (int i = 0; i < table.size(); i++)
		{
			for (int j = 0; j < ways[i].size(); j++)
			{
				cout << ways[i][j] ;
			}
			cout<< endl;
		}
		cout << endl;
		for (int i = 0;  i < ret_index(source); i++) if (d[i] == 1000000000)
			cout << endl << source << "->" << i + 1 << "=" << "Not";
		else cout << endl << source << "->" << i + 1 << "=" << d[i];
		for (int i = ret_index(source)+1; i < table.size(); i++) if (d[i] == 1000000000)
			cout << endl << source << "->" << i + 1 << "=" << "Not";
		else cout << endl << source << "->" << i + 1 << "=" << d[i];
	}
};
int main()
{
	Graph<int, int> A;
	A.addVertex(1);
	A.addVertex(2);
	A.addVertex(3);
	A.addVertex(4);
	//A.print();
	A.addEdge(1, 2, 3);
	A.delEdge(1, 2);
	//A.delVertex(1);
	A.print();
	A.addEdge(2, 1, 8);
	A.addEdge(1, 2, 3);
	A.addEdge(2, 4, 7);
	A.addEdge(3, 1, 2);
	A.addEdge(4, 3, 9);
	A.print();
	A.deep_search();
	A.bellman_ford(1,3);
	return 0;
}