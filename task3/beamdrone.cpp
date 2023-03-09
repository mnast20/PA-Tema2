#include <bits/stdc++.h>
using namespace std;

// maximum number of nodes
#define NMAX 1005

// value greater than any graph distance
#define INF (1 << 30)

struct MatrixPosition {
    int x;
    int y;
    int distance;
    int value;
};

class Task3 {
 public:
    void solve() {
        read_input();
        print_output(get_result());
    }

 private:
    int n, m;
    pair<int, int> source;
    pair<int, int> destination;
    MatrixPosition route_matrix[NMAX][NMAX];

    /**
     * Function reading and processing the provided input
    **/
    void read_input() {
        ifstream fin("./beamdrone.in");
        int xi, yi, xf, yf;
        fin >> n >> m;
        fin >> xi >> yi >> xf >> yf;

        // create source
        source.first = xi;
        source.second = yi;

        // create destination
        destination.first = xf;
        destination.second = yf;

        char x;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                fin >> x;

                // create the matrix position
                MatrixPosition pos;
                pos.x = i;
                pos.y = j;
                pos.distance = INF;

                // the source has the distance 0
                if (i == xi && j == yi) {
                    pos.distance = 0;
                }

                if (x == '.') {
                    pos.value = 1;
                    route_matrix[i][j] = pos;
                } else if (x == 'W') {
                    pos.value = 0;
                    route_matrix[i][j] = pos;
                }
            }
        }

        fin.close();
    }

    /**
     * Function checking if the given position falls within the matrix limits
     * @param x row
     * @param y column
     * @param n number of rows
     * @param m number of columns
     * */
    bool check_boundary(int x, int y, int n, int m) {
        // check if next row is out of bounds
        if (x < 0 || x >= n) {
            return false;
        }

        // check if next column is out of bounds
        if (y < 0 || y >= m) {
            return false;
        }

        return true;
    }

    /**
     * Function inserting a pair of next position and new direction in queue
     * if valid
     * @param n number of rows
     * @param m number of columns
     * @param queue {position, direction} pair queue
     * @param x_next next row position
     * @param y_next next column position
     * @param current current position in matrix
     * @param cost direction cost
     * @param direction current direction
     * @param route_matrix adjacency matrix
     * */
    void go_dir(int n, int m, queue<pair<MatrixPosition, int>> &queue,
                int x_next, int y_next, MatrixPosition current, int cost,
                int direction, MatrixPosition route_matrix[NMAX][NMAX]) {
        // check validity
        if (!check_boundary(x_next, y_next, n, m) ||
            route_matrix[x_next][y_next].value == 0) {
            return;
        }

        // compare distances
        if (current.distance + cost <= route_matrix[x_next][y_next].distance) {
            // update distance
            route_matrix[x_next][y_next].distance = current.distance + cost;

            // insert pair in queue
            pair<MatrixPosition, int> p;
            p.first = route_matrix[x_next][y_next];
            p.second = direction;
            queue.push(p);
        }
    }

    /**
     * Function using the BFS algorithm in order to calculate the shortest path
     * @param source source position
     * @param destination destination position
     * @param n number of rows
     * @param m number of columns
     * @param route_matrix adjacency matrix
     * */
    int BFS(pair<int, int> source, pair<int, int> destination, int n, int m,
                        MatrixPosition route_matrix[NMAX][NMAX]) {
        // create a queue that will contain pairs made up of the matrix
        // position and previous direction
        queue<pair<MatrixPosition, int>> queue;
        pair<MatrixPosition, int> p;

        // put the source position and the initial direcion inside the queue
        p.first = route_matrix[source.first][source.second];
        p.second = -1;
        queue.push(p);

        while (!queue.empty()) {
            // get the top queue pair
            MatrixPosition pos = queue.front().first;
            int previous_pos = queue.front().second;
            queue.pop();

            int x = pos.x;
            int y = pos.y;

            // travel to all directions using costs that are based on the
            // previous direction
            switch (previous_pos) {
                case 1: {
                    // previous position was up
                    go_dir(n, m, queue, x - 1, y, pos, 0, 1, route_matrix);
                    go_dir(n, m, queue, x + 1, y, pos, 2, 2, route_matrix);
                    go_dir(n, m, queue, x, y - 1, pos, 1, 3, route_matrix);
                    go_dir(n, m, queue, x, y + 1, pos, 1, 4, route_matrix);
                    break;
                } case 2: {
                    // previous position was down
                    go_dir(n, m, queue, x - 1, y, pos, 2, 1, route_matrix);
                    go_dir(n, m, queue, x + 1, y, pos, 0, 2, route_matrix);
                    go_dir(n, m, queue, x, y - 1, pos, 1, 3, route_matrix);
                    go_dir(n, m, queue, x, y + 1, pos, 1, 4, route_matrix);
                    break;
                } case 3: {
                    // previous position was left
                    go_dir(n, m, queue, x - 1, y, pos, 1, 1, route_matrix);
                    go_dir(n, m, queue, x + 1, y, pos, 1, 2, route_matrix);
                    go_dir(n, m, queue, x, y - 1, pos, 0, 3, route_matrix);
                    go_dir(n, m, queue, x, y + 1, pos, 2, 4, route_matrix);
                    break;
                } case 4: {
                    // previous position was right
                    go_dir(n, m, queue, x - 1, y, pos, 1, 1, route_matrix);
                    go_dir(n, m, queue, x + 1, y, pos, 1, 2, route_matrix);
                    go_dir(n, m, queue, x, y - 1, pos, 2, 3, route_matrix);
                    go_dir(n, m, queue, x, y + 1, pos, 0, 4, route_matrix);
                    break;
                } default: {
                    // source case
                    go_dir(n, m, queue, x - 1, y, pos, 0, 1, route_matrix);
                    go_dir(n, m, queue, x + 1, y, pos, 0, 2, route_matrix);
                    go_dir(n, m, queue, x, y - 1, pos, 0, 3, route_matrix);
                    go_dir(n, m, queue, x, y + 1, pos, 0, 4, route_matrix);
                    break;
                }
            }
        }

        // return the minimum cost to the destination
        return route_matrix[destination.first][destination.second].distance;
    }

    /**
     * Function returning the shortest path cost
     * */
    long long int get_result() {
        return BFS(source, destination, n, m, route_matrix);
    }

    /**
     * Function displaying the calculated shortest path length
     * @param result shortest path length
    **/
    void print_output(long long int result) {
        ofstream fout("./beamdrone.out");
        fout << result;
        fout.close();
    }
};

int main() {
    auto* task = new (nothrow) Task3();

    if (!task) {
        return -1;
    }

    task->solve();
    delete task;

    return 0;
}
