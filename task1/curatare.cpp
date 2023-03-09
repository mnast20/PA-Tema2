#include <bits/stdc++.h>
using namespace std;

// maximum number of nodes
#define NMAX 1500

// value greater than any graph distance
#define INF (1 << 30)


class Task1 {
 public:
    void solve() {
        read_input();
        print_output(get_value());
    }

 private:
    int n, m;
    int row[4] = {-1, 0, 0, 1};
    int col[4] = {0, -1, 1, 0};
    pair<int, int> dirty_spots[NMAX], robots[NMAX];
    int nrDirtySpots = 0, nrRobots = 0;
    char matrix[NMAX][NMAX];
    int graph_distances[NMAX][NMAX];
    vector<int> robots_permutations[NMAX];
    int resultedTime = INF;
    int distances[NMAX][NMAX];

    /**
     * Function reading and processing the provided input
    **/
    void read_input() {
        ifstream fin("./curatare.in");
        fin >> n >> m;

        char x;

        // read positions array
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                fin >> x;

                matrix[i][j] = x;

                if (x == 'S') {
                    // dirty spot
                    dirty_spots[nrDirtySpots] = {i, j};
                    nrDirtySpots++;
                } else if (x == 'R') {
                    // robot
                    robots[nrRobots] = {i, j};
                    nrRobots++;
                }
            }
        }

        fin.close();
    }

    /**
     * Function checking if the next position is valid
     * @param next_x next row
     * @param next_y next column
     * @param n number of rows
     * @param m number of columns
     * */
    bool check_valid(int next_x, int next_y, int n, int m,
                    int distances[NMAX][NMAX]) {
        // check if next row is out of bounds
        if (next_x < 0 || next_x >= n) {
            return false;
        }

        // check if next column is out of bounds
        if (next_y < 0 || next_y >= m) {
            return false;
        }

        // check if position is unavailable
        if (matrix[next_x][next_y] == 'X') {
            return false;
        }

        // check if the next position is visited
        if (distances[next_x][next_y] != INF) {
            return false;
        }

        return true;
    }

    /**
     * @param sizeVect vector size
     * @param vect current vector (either robot vector or dirty spots vector)
     * @param graph_distances matrix containing distances from robots and
     * dirty spots to dirty spots
     * @param starting_index  starting index in the graph_distances matrix
     * (0 for robots vector, nrRobots for dirty spots vector)
     * */
    void LeeAlgorithm(int sizeVect, pair<int, int> vect[],
                    int graph_distances[NMAX][NMAX], int starting_index) {
        // int distances[NMAX][NMAX];

        // iterate through vector
        for (int i = 0; i < sizeVect; i++) {
            // initialize distance matrix
            for (int j = 0; j < n; j++) {
                for (int k = 0; k < m; k++) {
                    distances[j][k] = INF;
                }
            }

            // distance to current source is 0
            distances[vect[i].first][vect[i].second] = 0;

            // put the source  in queue
            queue<pair<int, int>> q;
            q.push(vect[i]);

            while (!q.empty()) {
                // get top element and remove it
                pair<int, int> p_top = q.front();
                q.pop();

                int x = p_top.first;
                int y = p_top.second;

                for (int l = 0; l < 4; l++) {
                    // check if going in a certain direction is possible
                    if (check_valid(x + row[l], y + col[l], n, m, distances)) {
                        // update distance
                        distances[x + row[l]][y + col[l]] = distances[x][y] + 1;
                        // put next position in queue
                        q.push({x + row[l], y + col[l]});
                    }
                }
            }

            // add distances to all dirty spots to the vector element's row
            for (int j = 0; j < nrDirtySpots; j++) {
                graph_distances[starting_index][j] =
                        distances[dirty_spots[j].first][dirty_spots[j].second];
            }

            starting_index++;
        }
    }

    /**
     * Function calculating the best time for all robots based on permutations
     * @param nrRobots number of robots
     * @param graph_distances matrix containing distances from robots and
     * dirty spots to dirty spots
     * */
    void get_permutation_time(int nrRobots, int graph_distances[NMAX][NMAX]) {
        int bestMaxTime = 0;

        // iterate through robots
        for (int i = 0; i < nrRobots; i++) {
            // ignore robots that don't contain a list of indexes
            if (robots_permutations[i].size() == 0) {
                continue;
            }

            // extract the list of indexes
            vector<int> current_permutation = robots_permutations[i];
            int bestTime = INF;

            while (1) {
                // current time is equal to the distance between robot and the
                // dirty spot with the first index in the list of indexes
                int currentTime = graph_distances[i][current_permutation[0]];

                // iterate through the list of indexes
                for (int j = 1; j < current_permutation.size(); j++) {
                    // sum up the distances between the previous and
                    // the current dirty spots
                    currentTime +=
                        graph_distances[current_permutation[j - 1] + nrRobots]
                                        [current_permutation[j]];
                }

                // get the minimum permutation time
                if (currentTime < bestTime) {
                    bestTime = currentTime;
                }

                // get next permutation
                if (!next_permutation(current_permutation.begin(),
                                        current_permutation.end())) {
                    break;
                }
            }

            // get the maximum time out of all robots
            if (bestTime > bestMaxTime) {
                bestMaxTime = bestTime;
            }
        }

        // get the minimum time overall
        if (bestMaxTime < resultedTime) {
            resultedTime = bestMaxTime;
        }
    }

    /**
     * Backtracking function generating all subsets of dirty spots indexes
     * @param x current index
     * @param nrRobots number of robots
     * @param graph_distances matrix containing distances from robots and
     * dirty spots to dirty spots
     * */
    void backtracking(int x, int nrRobots, int graph_distances[NMAX][NMAX]) {
        if (x == nrDirtySpots) {
            // get best time from current matrix
            get_permutation_time(nrRobots, graph_distances);
            return;
        }

        for (int i = 0; i < nrRobots; i++) {
            // insert current index
            robots_permutations[i].push_back(x);
            backtracking(x + 1, nrRobots, graph_distances);
            // extract current index
            robots_permutations[i].pop_back();
        }
    }


    /**
     * Function returning the the minimum best calculated time
    **/
    int get_value() {
        // get distances from robots to dirty spots
        LeeAlgorithm(nrRobots, robots, graph_distances, 0);
        // get distances from dirty spots to dirty spots
        LeeAlgorithm(nrDirtySpots, dirty_spots, graph_distances, nrRobots);

        backtracking(0, nrRobots, graph_distances);

        return resultedTime;
    }

    /**
     * Function displaying the minimum best calculated time
    **/
    void print_output(int result) {
        ofstream fout("./curatare.out");

        fout << result;

        fout.close();
    }
};

int main() {
    auto* task = new (nothrow) Task1();

    if (!task) {
        return -1;
    }

    task->solve();
    delete task;

    return 0;
}
