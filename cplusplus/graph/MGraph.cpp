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
	vector< vector<Einfo> > edges; //邻接矩阵 edges[i]是顶点v对应的一行, 
								  // edges[i][j]表示顶点i,j边上的信息如权
	vector<bool> marks;
	unsigned int en_{ 0 };
	bool undirected{ true };
	Einfo invalid_edge_info;
public:
	MGraph(bool undirected = true)
		:undirected{ undirected } {}; //空的图
	void add_vertex(const VT& v) {
		vertices.push_back(v);
	}
	VT operator[](int i)const { return vertices[i]; }
	VT& operator[](int i) { return vertices[i]; }

	void add_edge(const int i, const int j, const Einfo& edge_info) {
		if (edges.size() < vertices.size())
			throw "应该先生成邻接矩阵！\n";
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
		std::cout << "顶点信息：\n";
		for (auto& v : vertices)
			std::cout << v << "\n";
		std::cout << "邻接矩阵：\n";
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
			if (edges[v][w] != invalid_edge_info) {  //(v,w)是一个边或弧
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
		S.push(v);		marks[v] = true; //入栈做标记
		//visit_vertex(vertices[v]);
		while (!S.empty()) {
			auto v = S.top(); S.pop(); //出栈
			visit_vertex(vertices[v]); //访问它
			// 对v的每个邻接点 w
			for (unsigned int w = 0; w < vertices.size(); w++) {
				if (edges[v][w] != invalid_edge_info) {  //(v,w)是一个边或弧
					if (marks[w] == false) { //未访问过
						S.push(w);		marks[w] = true; //入栈做标记
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
				if (edges[v][w] != invalid_edge_info) {  //(v,w)是一个边或弧
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
			if (edges[v][w] != invalid_edge_info) {  //(v,w)是一个边或弧
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
				lebel++; //下一个连通分量的标记
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
	MGraph<VT,ET> G(false);  //有向图
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
	std::cout <<"\n----创建G2----"<< std::endl;
	MGraph<VT, ET> G2;   //无向图
	G2.add_vertex('A');
	G2.add_vertex('B');
	G2.add_vertex('C');
	G2.add_vertex('D');
	G2.add_vertex('E');
	G2.clear_edges(-1000);
	G2.add_edge(0, 1, 12);     //V1V2权值为12
	G2.add_edge(0, 3, 14);    //V1V4权值为14
	G2.add_edge(1, 2, 23);    //V2V3权值为23
	G2.add_edge(1, 4, 325);    //V2V5权值为25
	G2.add_edge(2, 3, 34);    //V3V4权值为34
	G2.add_edge(2, 4, 35);    //V3V5权值为35
	G2.print();
	std::cout << std::endl;


	std::cout << "DFS遍历：\n";
	//G2.clear_marks();	 
	//G2.DFS(1, visit); std::cout << std::endl;
	G2.DFS(visit); std::cout << std::endl;
	std::cout << "BFS遍历：\n";
	G2.BFS(visit); std::cout << std::endl;
#endif


#if 1
	std::cout << "\n----创建G3----" << std::endl;
	MGraph<VT, ET> G3;   //无向图
	G3.add_vertex('A');
	G3.add_vertex('B');
	G3.add_vertex('C');
	G3.add_vertex('D');
	G3.add_vertex('E');
	G3.clear_edges(-1000);
	G3.add_edge(0, 1, 12);     //V1V2权值为12
	G3.add_edge(1, 2, 23);     //V2V3权值为23
	G3.add_edge(2, 0, 31);    //V3V1权值为31
	G3.add_edge(3, 4, 45);    //V4V4权值为45
	
	G3.print();
	std::cout << std::endl;

	vector<MGraph<char, double>> ConnectedComponent_Graphs;
	ConnectedComponent_Graphs = G3.DFS_ConnectedComponents();
	std::cout << "\n------图的连通分量-------\n";
	for (auto &G : ConnectedComponent_Graphs) {
		std::cout << "连通分量：\n";
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

	// 初始化disjoint sets. 
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
		std::cout<<"\n 最小代价= %d \n"<<mincost<<std::endl;
	else
		std::cout << "\n 最小生成树不存在最小代价" << std::endl;

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
	//---正向拓扑排序计算ve----
	vector<WT> ve(n, 0);
	stack<int> top_list;

	const int n = G.vertices.size();
	//计算每个顶点的入度
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
			S.push(i);         // 将所有入度为0的顶点入栈

	int count = 0;             // 计数，记录当前已经输出的顶点数 
	while (!S.empty()) {
		int v = S.top(); S.pop();      // 从出栈一个顶点

		top_list.push(v); // 输出该顶点
		++count;
		// 将所有v指向的顶点的入度减1，并将入度减为0的顶点入栈

		for (int j = 0; j < n; j++) {
			if (G.edges[v][j] != invalid_edge_info) {
				indegree[j]--;
				if (indegree[p->v] == 0)
					S.push(p->v);      // 若入度为0，则入栈
			}
		}		
	}
	if (count < n)		return false;           // 有向图中有回路

	//---正向拓扑排序计算vl----

	return true;            // 拓扑排序成功

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

	cout << "打印各个顶点对的最短距离：" << endl;
	for (auto u = 0; u < vn; u++) {
		for (auto v = 0; v < vn; v++) {
			if (D[u][v] == INF) cout<<setw(5)<<" ";
			else cout << setw(5) << D[u][v];
		}
		cout << "\n";
	}
	cout << "\n";
	cout << "打印各个顶点对的最短路径：" << endl;
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