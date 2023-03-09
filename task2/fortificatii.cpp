#include <bits/stdc++.h>
using namespace std;

// maximum number of nodes
#define NMAX 100005

// value greater than any graph distance
#define INF (1UL << 50)

class Task2 {
 public:
    void solve() {
        read_input();
        print_output(get_result());
    }

 private:
    long long int n, m, k, b;
    vector<pair<long long int, long long int>> adj[NMAX];
    set<long long int> barbaric;
    int yes_barbaric[NMAX] = {0};

    /**
     * Function reading and processing the provided input
    **/
    void read_input() {
        ifstream fin("./fortificatii.in");
        fin >> n >> m >> k;
        fin >> b;

        long long int br;

        for (int i = 0; i < b; ++i) {
            fin >> br;
            barbaric.insert(br);
             // mark barbaric
            yes_barbaric[br] = 1;
        }

        for (int i = 1, x, y, w; i <= m; i++) {
            int barbaric_x = 0;
            int barbaric_y = 0;
            fin >> x >> y >> w;

            // add node and cost to adjacency matrix
            adj[x].push_back({y, w});
            adj[y].push_back({x, w});
        }

        fin.close();
    }

    /**
     * Function comparing the distances of two nodes
     * */
    static bool compareDistances(pair<long long int, long long int> P1,
                                pair<long long int, long long int> P2) {
        return P1.second > P2.second;
    }

    /**
     * Function using Dijkstra's Algorithm in order to return a distance list
     * from source up to nodes adjacent to the barbarics
     * @param source source node
     * @param n number of nodes
     * @param adj adjacency matrix
     * */
    vector<long long int> Dijskstra(long long int source, long long int n,
                            vector<pair<long long int, long long int>> adj[]) {
        vector<long long int> d(n + 1);

        for (int i = 1; i <= n; i++) {
            d[i] = INF;
        }

        priority_queue<pair<long long int, long long int>,
        std::vector<pair<long long int, long long int>>,
        std::function<bool(pair<long long int, long long int>,
        pair<long long int, long long int>)>> pq(compareDistances);

        d[source] = 0;

        // insert a {node, distance} pair inside the priority queue
        pair<long long int, long long int> p_source(source, d[source]);
        pq.push(p_source);

        while (!pq.empty()) {
            // get top element
            long long int node = pq.top().first;
            pq.pop();

            vector<pair<long long int, long long int>> neighbours = adj[node];

            // iterate through adjacent nodes
            for (int i = 0; i < neighbours.size(); i++) {
                long long int neighbour = neighbours[i].first;
                long long int cost = neighbours[i].second;

                // ignore barbarics
                if (!yes_barbaric[neighbour]) {
                    // compare distances
                    if (d[node] +  cost < d[neighbour]) {
                        // update distance
                        d[neighbour] = d[node] + cost;

                        // insert a new pair in the priority queue
                        pair<long long int, long long int> p_neigh;
                        p_neigh.first = neighbour;
                        p_neigh.second = d[neighbour];
                        pq.push(p_neigh);
                    }
                }
            }
        }

        return d;
    }

    /**
     * 
     * @param distances_barbarics
     * @param limit proposed limit
     * @param k number of forts to build
     * */
    int check_limit_bounds(vector<long long int> &distances_barbarics,
                long long int limit, long long int k) {
        long long int sum = 0;

        // iterate through distance vector
        for (int i = 0; i < distances_barbarics.size(); i++) {
            // check if distance exceeds limit
            if (distances_barbarics[i] < limit) {
                // sum up the difference between limit and current distance
                sum += limit - distances_barbarics[i];

                // check if sum exceeds the number of forts
                if (sum > k) {
                    return 0;
                }
            }
        }

        return 1;
    }

    /**
     * Function conducting a binary search for the minimum time out of the
     * maximized distances
     * @param distances_barbarics vector containing all distances to barbarics
     * @param k number of forts to build
     * */
    long long int binarySearch(vector<long long int> &distances_barbarics,
                                long long int k) {
        long long int result = 0;
        long long int left = 0;
        long long int right = INF;

        while (left <= right) {
            long long int middle = (left + right) / 2;

            if (!check_limit_bounds(distances_barbarics, middle, k)) {
                // go left
                right = middle - 1;
            } else {
                // go right
                left = middle + 1;
                result = middle;
            }
        }

        return result;
    }

    /**
     * Function returning the resulted minimum time
    **/
    long long int get_result() {
        // get distances to nodes
        vector<long long int> distances = Dijskstra(1, n, adj);
        vector<long long int> distances_barbarics;

        set<long long int>::iterator it;

        // iterate through barbarics and put all distances in a vector
        for (it = barbaric.begin(); it != barbaric.end(); it++) {
            // iterate throuh barbarics' edges
            for (int j = 0; j < adj[*it].size(); j++) {
                // skip edges containing barbarics
                if (yes_barbaric[adj[*it][j].first]) {
                    continue;
                }

                if (distances[adj[*it][j].first] != INF) {
                    // calculate distance based on adjacent edge's distance
                    long long int dist = adj[*it][j].second +
                                                distances[adj[*it][j].first];

                    // insert distance in vector
                    distances_barbarics.push_back(dist);
                }
            }
        }

        return binarySearch(distances_barbarics, k);
    }

    /**
     * Function displaying the resulted minimum time
     * @param result minimum time
    **/
    void print_output(long long int result) {
        ofstream fout("./fortificatii.out");
        fout << result;
        fout.close();
    }
};

int main() {
    auto* task = new (nothrow) Task2();

    if (!task) {
        return -1;
    }

    task->solve();
    delete task;

    return 0;
}
