#include <bits/stdc++.h>
using namespace std;

// maximum number of nodes
#define NMAX 10005

class Task {
 public:
    void solve() {
        read_input();
        print_output(get_result());
    }

 private:
    int n, m, a;
    int matrix[NMAX][NMAX];
    unordered_set<int> adj[NMAX];

    /**
     * Function reading and processing the provided input
    **/
    void read_input() {
        ifstream fin("./curse.in");

        fin >> n >> m >> a;
        int x;
        vector<int> previous(n);

        for (int i = 0; i < a; i++) {
            int equal = 1;
            for (int j = 0; j < n; j++) {
                fin >> x;

                // compare the previous line with the current one
                if (i != 0) {
                    if (equal == 1 && previous[j] != x) {
                        // add to the previous node's adjacent list
                        adj[previous[j]].insert(x);
                        equal = 0;
                    }
                }

                // update the previous line
                previous[j] = x;
            }
        }

        fin.close();
    }

    /**
     * Function applying the DFS Algorithm an inserting nodes in the
     * topologically sorted array based on the order of appearancces
     * @param sort_index current index in sorted vector based on priority
     * @param node current node
     * @param adj adjacency matrix
     * */
    void dfs_sort(int &sort_index, int node, vector<int> &visited,
                vector<int> &sorted, unordered_set<int> adj[NMAX]) {
        // mark current node as visited
        visited[node] = 1;

        unordered_set<int>::iterator it;

        // iterate through adjacent nodes to the current one
        for (it = adj[node].begin(); it != adj[node].end(); it++) {
            if (!visited[*it]) {
                dfs_sort(sort_index, *it, visited, sorted, adj);
            }
        }

        // insert node in priority list
        sorted[sort_index] = node;

        // decrease the current sorting ndex
        sort_index--;
    }

    /**
     * Function using the Topological Sorting Algorithm in order to sort the
     * nodes based on priority
     * @param n number of nodes
     * @param adj adjacency matrix
     * */
    vector<int> topo_sort(int n, unordered_set<int> adj[NMAX]) {
        vector<int> visited;
        vector<int> sorted;

        // fill the visited and sorted vectors with default values
        visited.push_back(0);
        for (int i = 0; i < n; i++) {
            visited.push_back(0);
            sorted.push_back(-1);
        }

        // starting sorting index
        int index = n - 1;

        for (int i = 1; i <= n; i++) {
            if (!visited[i]) {
                // apply DFS if node was not previouslt visited
                dfs_sort(index, i, visited, sorted, adj);
            }
        }

        return sorted;
    }

    /**
     * Function returning the topologically sorted graph nodes
     * */
    vector<int> get_result() {
        return topo_sort(m, adj);
    }

    /**
     * Function displaying the sorted graph nodes
     * @param priorities vector of sorted nodes
    **/
    void print_output(vector<int> priorities) {
        ofstream fout("./curse.out");

        for (int i = 0; i < m; i++) {
            fout << priorities[i] << ' ';
        }

        fout.close();
    }
};

int main() {
    auto* task = new (nothrow) Task();

    if (!task) {
        return -1;
    }

    task->solve();
    delete task;

    return 0;
}
