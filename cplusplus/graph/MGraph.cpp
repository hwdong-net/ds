//https://gist.github.com/arrayed/4121223743f60e2105cde3b83f26590a
#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <iomanip>
using namespace std;

template<typename VT, typename Einfo=double>
class MGraph {
	vector<VT> vertices;
	vector< vector<Einfo> > edges; //�ڽӾ��� edges[i]�Ƕ���v��Ӧ��һ��, 
								  // edges[i][j]��ʾ����i,j���ϵ���Ϣ��Ȩ
	vector<bool> marks;
	unsigned int en_{ 0 };
	bool undirected{ true };
	Einfo invalid_edge_info;
public:
	MGraph(bool undirected = true)
		:undirected{ undirected } {}; //�յ�ͼ
	void add_vertex(const VT& v) {
		vertices.push_back(v);
	}
	VT operator[](int i)const { return vertices[i]; }
	VT& operator[](int i) { return vertices[i]; }

	void add_edge(const int i, const int j, const Einfo& edge_info) {
		if (edges.size() < vertices.size())
			throw "Ӧ���������ڽӾ���\n";
		edges[i][j] = edge_info;		en_++;
		if (undirected) {
			edges[j][i] = edge_info;		en_++;
		}
	}
	void clear_edges(const Einfo& invalid_info) {
		if (edges.size() != vertices.size()) {
			const int vn = vertices.size();
			edges.resize(vn, vector<Einfo>(vn, invalid_info));//edges[i][j] = invalid_info
		}
		invalid_edge_info = invalid_info;
	}

	void set_edge(const int i, const int j, const Einfo& info) {
		edges[i][j] = info;
	}

	int vn()const { return vertices.size(); }
	int en()const { return en_; }


	void print_matrix() {
		for (auto& row : edges) {
			for (auto& col : row)
				std::cout << setw(6) << col << " ";
			std::cout << std::endl;
		}
	}
	void print() {
		std::cout << "������Ϣ��\n";
		for (auto& v : vertices)
			std::cout << v << "\n";
		std::cout << "�ڽӾ���\n";
		print_matrix();
	}
	unsigned int index_is(const VT & vertex) {
		for (unsigned int i = 0; i < vertices.size(); i++) {
			if (vertices[i] == vertex)
				return i;
		}
		return -1;
	}


	void clear_marks() {
		if (marks.size() != vertices.size())
			marks.resize(vertices.size(), false);
		//for (auto &mark: marks)	mark = false;
		for (unsigned int i = 0; i < marks.size(); i++)
			marks[i] = false;
	}

	void mark_vertex(unsigned int v, bool mark = true) { marks[v] = mark; }
	bool is_marked(unsigned int v) { return marks[v]; }


	void DFS(unsigned int v, void (*visit_vertex)(const VT & vertex)) {
		if (v < 0 || v >= vertices.size()) return;
		marks[v] = true;
		visit_vertex(vertices[v]);

		for (unsigned int w = 0; w < vertices.size(); w++) {
			if (edges[v][w] != invalid_edge_info) {  //(v,w)��һ���߻�
				if (marks[w] == false)
					DFS(w, visit_vertex);
			}
		}
	}
	void DFS(void(*visit_vertex)(const VT & vertex)) {
		clear_marks();
		for (int v = 0; v != vertices.size(); v++)
			if (!marks[v])
				DFS_(v, visit_vertex);
	}

	void DFS_(unsigned int v, void(*visit_vertex)(const VT & vertex)) {
		if (v < 0 || v >= vertices.size()) return;
		stack<int> S;
		S.push(v);		marks[v] = true; //��ջ�����
		//visit_vertex(vertices[v]);
		while (!S.empty()) {
			auto v = S.top(); S.pop(); //��ջ
			visit_vertex(vertices[v]); //������
			// ��v��ÿ���ڽӵ� w
			for (unsigned int w = 0; w < vertices.size(); w++) {
				if (edges[v][w] != invalid_edge_info) {  //(v,w)��һ���߻�
					if (marks[w] == false) { //δ���ʹ�
						S.push(w);		marks[w] = true; //��ջ�����
					}
				}
			}
		}
	}

	void BFS(unsigned int v, void(*visit_vertex)(const VT & vertex)) {
		if (v < 0 || v >= vertices.size()) return;
		marks[v] = true;
		queue <unsigned int> que;
		que.push(v);

		while (!que.empty()) {
			auto v = que.front();
			que.pop();
			visit_vertex(vertices[v]);

			for (unsigned int w = 0; w < vertices.size(); w++) {
				if (edges[v][w] != invalid_edge_info) {  //(v,w)��һ���߻�
					if (marks[w] == false) {
						marks[w] = true;
						que.push(w);
					}
				}
			}
		}
	}
	void BFS(void(*visit_vertex)(const VT & vertex)) {
		clear_marks();
		for (int v = 0; v != vertices.size(); v++)
			if (!marks[v])
				BFS(v, visit_vertex);
	}


	void DFS_ConnectedComponents(unsigned int v, vector<int> & vertex_labels, const int label) {
		if (v < 0 || v >= vertices.size()) return;
		marks[v] = true;
		//visit_vertex(vertices[v]);
		vertex_labels[v] = label;

		for (unsigned int w = 0; w < vertices.size(); w++) {
			if (edges[v][w] != invalid_edge_info) {  //(v,w)��һ���߻�
				if (marks[w] == false)
					DFS_ConnectedComponents(w, vertex_labels, label);
			}
		}
	}

	auto DFS_ConnectedComponents() {
		int lebel = 0;
		vector<int> vertex_labels(vertices.size(), lebel);
		clear_marks();
		for (int v = 0; v != vertices.size(); v++)
			if (!marks[v]) {
				DFS_ConnectedComponents(v, vertex_labels, lebel);
				lebel++; //��һ����ͨ�����ı��
			}
		if (undirected) {
			return creat_ConnectedComponent_Graph(vertex_labels);
		}
		else return creat_directed_ConnectedComponent_Graph(vertex_labels);
	}

	auto creat_ConnectedComponent_Graph(vector<int> & vertex_labels) {
		vector<MGraph<VT, Einfo>> ConnectedComponent_Graphs;

		int min_label = 100000, max_label = -100000;
		for (int v = 0; v != vertex_labels.size(); v++) {
			if (vertex_labels[v] < min_label)
				min_label = vertex_labels[v];
			if (vertex_labels[v] > max_label)
				max_label = vertex_labels[v];
		}

		vector<int> vertex_indices(vertex_labels.size());
		for (int label = min_label; label <= max_label; label++) {
			MGraph<VT, Einfo> G;
			int vertex_index = 0;
			for (int v = 0; v != vertex_labels.size(); v++)
				if (vertex_labels[v] == label) {
					G.add_vertex(vertices[v]);
					vertex_indices[v] = vertex_index++;
				}

			G.clear_edges(invalid_edge_info);
			for (int v = 0; v != vertex_labels.size(); v++)
				if (vertex_labels[v] == label) {
					for (int w = v + 1; w != vertex_labels.size(); w++)
						if (edges[v][w] != invalid_edge_info && vertex_labels[w] == label) {
							auto v_index = vertex_indices[v];
							auto w_index = vertex_indices[w];
							G.add_edge(v_index, w_index, edges[v][w]);
						}
				}
			ConnectedComponent_Graphs.push_back(G);
		}
		return ConnectedComponent_Graphs;
	}
	auto creat_directed_ConnectedComponent_Graph(vector<int> & vertex_labels) {
		vector<MGraph<VT, Einfo>> ConnectedComponent_Graphs;
		return ConnectedComponent_Graphs;
	}

	template<typename VT, typename WT>
	friend void kruskal(const MGraph<VT, WT> & G);

#if 0
	template<typename VT, typename WT = double >
	friend void criticalPath(const MGraph<VT, WT> & G);
#endif

	template<typename VT, typename WT>
	friend auto floyd(const MGraph<VT, WT>& G);
};


using VT = char;
using ET = double;
inline void visit(const char &vertex) {
	std::cout << vertex << " ";
}



int main_M() {
	MGraph<VT,ET> G(false);  //����ͼ
	G.add_vertex('A');
	G.add_vertex('B');
	G.add_vertex('C');
	G.add_vertex('D');
	G.clear_edges(-1000);
	G.add_edge(0, 1, 6.5);
	G.add_edge(0, 2, 9.3);
	G.add_edge(2, 3, 1.4);
	G.add_edge(3, 0, 3.7);
	G.print();
	std::cout << std::endl;

	G[0] = 'X';
	G.set_edge(0, 1, 65.99);
	G.print();


#if 1
	std::cout <<"\n----����G2----"<< std::endl;
	MGraph<VT, ET> G2;   //����ͼ
	G2.add_vertex('A');
	G2.add_vertex('B');
	G2.add_vertex('C');
	G2.add_vertex('D');
	G2.add_vertex('E');
	G2.clear_edges(-1000);
	G2.add_edge(0, 1, 12);     //V1V2ȨֵΪ12
	G2.add_edge(0, 3, 14);    //V1V4ȨֵΪ14
	G2.add_edge(1, 2, 23);    //V2V3ȨֵΪ23
	G2.add_edge(1, 4, 325);    //V2V5ȨֵΪ25
	G2.add_edge(2, 3, 34);    //V3V4ȨֵΪ34
	G2.add_edge(2, 4, 35);    //V3V5ȨֵΪ35
	G2.print();
	std::cout << std::endl;


	std::cout << "DFS������\n";
	//G2.clear_marks();	 
	//G2.DFS(1, visit); std::cout << std::endl;
	G2.DFS(visit); std::cout << std::endl;
	std::cout << "BFS������\n";
	G2.BFS(visit); std::cout << std::endl;
#endif


#if 1
	std::cout << "\n----����G3----" << std::endl;
	MGraph<VT, ET> G3;   //����ͼ
	G3.add_vertex('A');
	G3.add_vertex('B');
	G3.add_vertex('C');
	G3.add_vertex('D');
	G3.add_vertex('E');
	G3.clear_edges(-1000);
	G3.add_edge(0, 1, 12);     //V1V2ȨֵΪ12
	G3.add_edge(1, 2, 23);     //V2V3ȨֵΪ23
	G3.add_edge(2, 0, 31);    //V3V1ȨֵΪ31
	G3.add_edge(3, 4, 45);    //V4V4ȨֵΪ45
	
	G3.print();
	std::cout << std::endl;

	vector<MGraph<char, double>> ConnectedComponent_Graphs;
	ConnectedComponent_Graphs = G3.DFS_ConnectedComponents();
	std::cout << "\n------ͼ����ͨ����-------\n";
	for (auto &G : ConnectedComponent_Graphs) {
		std::cout << "��ͨ������\n";
		G.print();
		std::cout << std::endl;
	}
#endif
	return 0;
}


#include "DisjointSet.h"
//#define DisjointSet

#ifndef DisjointSet
int find(int *parent,int i){
	while (parent[i] != i)
		i = parent[i];
	return i;
}
void union1(int *parent, int i, int j){
	int a = find(parent,i);
	int b = find(parent,j);
	parent[a] = b;
}
#endif

template<typename VT, typename WT>
void kruskal(const MGraph<VT, WT> &G) {
	const int n = G.vertices.size();
	const WT infinity = 1000000;
	int mincost = 0; // Cost of min MST. 

	// ��ʼ��disjoint sets. 
	int *parent = new int[n];
	for (int i = 0; i < n; i++)
		parent[i] = i;

	// Include minimum weight edges one by one 
	int edge_count = 0;
	while (edge_count < n - 1) {
		WT min = infinity; int  v{-1}, w{-1};
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				if (find(parent,i) != find(parent,j) &&G.edges[i][j] < min) {
					min = G.edges[i][j];
					v = i;
					w = j;
				}
			}
		}
		if (v == -1 || w == -1) break;
		union1(parent,v, w);
		std::cout << "Edge " << edge_count++ << ": "
			<< v<<","<< w<<","<<min << endl;		
		mincost += min;
	}
	if(edge_count==n-1)
		std::cout<<"\n ��С����= %d \n"<<mincost<<std::endl;
	else
		std::cout << "\n ��С��������������С����" << std::endl;

	delete[] parent;
}
void kruskal() {
	MGraph<char, double> G;
	G.add_vertex('A');
	G.add_vertex('B');
	G.add_vertex('C');
	G.add_vertex('D');
	G.add_vertex('E');
	G.add_vertex('F');
	const double infinity = 1000000;
	G.clear_edges(infinity);
	G.add_edge(0, 1, 6);  //AB:6
	G.add_edge(0, 2, 1);  //AC:1
	G.add_edge(0, 3, 5);  //AD:5
	G.add_edge(1, 2, 5);  //BC:5
	G.add_edge(1, 4, 3);  //BE:3
	G.add_edge(2, 3, 5);  //CD:5
	G.add_edge(2, 4, 5);  //CE:6
	G.add_edge(2, 5, 4);  //CF:4
	G.add_edge(3, 5, 2);  //DF:4
	G.add_edge(4, 5, 6);  //EF:6
	G.print();
	std::cout << std::endl;
	kruskal(G);
}

#if 0
template<typename VT, typename WT >
void criticalPath(const MGraph<VT, WT> &G) {
	//---���������������ve----
	vector<WT> ve(n, 0);
	stack<int> top_list;

	const int n = G.vertices.size();
	//����ÿ����������
	vector<int> indegree(n, 0);
	for (int i = 0; i < n;i++) {
		for (int j = 0; j < n; j++) {
			if (G.edges[i][j] != invalid_edge_info)
				indegree[j]++;
		}		
	}
	stack<int> S;
	for (int i = 0; i < n; ++i)
		if (indegree[i] == 0)
			S.push(i);         // ���������Ϊ0�Ķ�����ջ

	int count = 0;             // ��������¼��ǰ�Ѿ�����Ķ����� 
	while (!S.empty()) {
		int v = S.top(); S.pop();      // �ӳ�ջһ������

		top_list.push(v); // ����ö���
		++count;
		// ������vָ��Ķ������ȼ�1��������ȼ�Ϊ0�Ķ�����ջ

		for (int j = 0; j < n; j++) {
			if (G.edges[v][j] != invalid_edge_info) {
				indegree[j]--;
				if (indegree[p->v] == 0)
					S.push(p->v);      // �����Ϊ0������ջ
			}
		}		
	}
	if (count < n)		return false;           // ����ͼ���л�·

	//---���������������vl----

	return true;            // ��������ɹ�

}
void criticalPath() {
}

#endif

template<typename VT, typename WT>
auto floyd(const MGraph<VT, WT>& G) {
	vector< vector<WT> > D;
	vector< vector<unsigned int> > P;
	const int vn = G.vertices.size();
	double INF = std::numeric_limits<double>::infinity();
	D.resize(vn, vector<double>(vn, INF));
	P.resize(vn, vector<unsigned int>(vn, 0));
	for (auto u = 0; u < vn; u++) {
		for (auto v = 0; v < vn; v++) {
			if (G.edges[u][v] != G.invalid_edge_info) {
				D[u][v] = G.edges[u][v];
				P[u][v] = u;
			}
		}
	}


	for (auto k = 0; k < vn; k++) {
		for (auto u = 0; u < vn; u++) {
			for (auto v = 0; v < vn; v++) {
				if (u==v||D[u][k] == INF || D[k][v] == INF)
					continue;
				if (D[u][k] + D[k][v] < D[u][v]) {
					D[u][v] = D[u][k] + D[k][v];
					P[u][v] = P[k][v];
				}
			}
		}
	}

	cout << "��ӡ��������Ե���̾��룺" << endl;
	for (auto u = 0; u < vn; u++) {
		for (auto v = 0; v < vn; v++) {
			if (D[u][v] == INF) cout<<setw(5)<<" ";
			else cout << setw(5) << D[u][v];
		}
		cout << "\n";
	}
	cout << "\n";
	cout << "��ӡ��������Ե����·����" << endl;
	for (auto u = 0; u < vn; u++) {
		for (auto v = u + 1; v < vn; v++) {
			if (D[u][v] == INF) continue;
			vector<unsigned int> path;
			path.push_back(v);
			auto v_pre = P[u][v];
			while (v_pre != u) {
				path.push_back(v_pre);
				v_pre = P[u][v_pre];
			}
			cout << "path from " << u << "to" << v << "is: " << u;
			while (!path.empty()) {
				auto w = path.back(); path.pop_back();
				cout << " " << w;
			}
			cout << "\n";
		}
	}
}

void test_floyd() {
	MGraph<char, double> G;
	G.add_vertex('A');
	G.add_vertex('B');
	G.add_vertex('C');
	G.add_vertex('D');
	G.add_vertex('E');
	G.add_vertex('F');
	G.add_vertex('G');
	const double infinity = 1000000;
	G.clear_edges(infinity);
	G.add_edge(0, 1, 12);  //AB:6
	G.add_edge(0, 5, 16);  //AC:1
	G.add_edge(0, 6, 14);  //AD:5
	G.add_edge(1, 2, 10);  //BC:5
	G.add_edge(1, 5, 7);  //BE:3
	G.add_edge(2, 3, 3);  //CD:5
	G.add_edge(2, 4, 5);  //CE:6
	G.add_edge(2, 5, 6);  //CF:4
	G.add_edge(3, 4, 4);  //DF:4
	G.add_edge(4, 5, 2);  //DF:4
	G.add_edge(4, 6, 8);  //EF:6
	G.add_edge(5, 6, 9);  //EF:6

	G.print();
	std::cout << std::endl;
	floyd(G);
}
int main() {
	//extern int main_M();	return main_M();
	//extern int main_A();	return main_A();
	//extern void prim();   prim();
	//extern void kruskal(); kruskal();
	//extern void  topological_sort() ;  topological_sort();
	//extern void  criticalPath();  criticalPath();
	extern void test_floyd(); test_floyd();
	//extern void test_dijkstra();  test_dijkstra();
	
}