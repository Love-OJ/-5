#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

struct Customer {
    int x, y, c;
};

struct Store {
    int x, y;
};

// 四个方向的移动（上下左右）
int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, -1, 1};

bool is_valid(int x, int y, int n, const vector<vector<char>>& grid) {
    return x >= 0 && x < n && y >= 0 && y < n && grid[x][y] != 'X';
}

// BFS计算从多个分店到各个点的最短路径
void bfs(int n, const vector<Store>& stores, vector<vector<int>>& dist, const vector<vector<char>>& grid) {
    queue<pair<int, int>> q;

    // 初始化距离数组，所有位置都设为INF
    for (int i = 0; i < n; ++i) {
        fill(dist[i].begin(), dist[i].end(), INT_MAX);
    }

    // 将所有分店加入队列并设置初始距离为0
    for (const auto& store : stores) {
        q.push({store.x, store.y});
        dist[store.x][store.y] = 0;
    }

    // BFS搜索最短路径
    while (!q.empty()) {
        auto [x, y] = q.front();
        q.pop();
        for (int i = 0; i < 4; ++i) {
            int nx = x + dx[i], ny = y + dy[i];
            if (is_valid(nx, ny, n, grid) && dist[nx][ny] == INT_MAX) {
                dist[nx][ny] = dist[x][y] + 1;
                q.push({nx, ny});
            }
        }
    }
}

int main() {
    int n, m, k, d;
    cin >> n >> m >> k >> d;

    vector<Store> stores(m);
    vector<Customer> customers(k);
    vector<pair<int, int>> obstacles(d);

    // 输入分店位置
    for (int i = 0; i < m; ++i) {
        cin >> stores[i].x >> stores[i].y;
        stores[i].x--; stores[i].y--;  // 将坐标转换为从0开始
    }

    // 输入客户位置和需求量
    for (int i = 0; i < k; ++i) {
        cin >> customers[i].x >> customers[i].y >> customers[i].c;
        customers[i].x--; customers[i].y--;  // 将坐标转换为从0开始
    }

    // 输入障碍物位置
    vector<vector<char>> grid(n, vector<char>(n, '.'));
    for (int i = 0; i < d; ++i) {
        cin >> obstacles[i].first >> obstacles[i].second;
        obstacles[i].first--; obstacles[i].second--;  // 将坐标转换为从0开始
        grid[obstacles[i].first][obstacles[i].second] = 'X';  // 标记障碍物
    }

    // 计算每个分店到每个点的最短路径
    vector<vector<int>> dist(n, vector<int>(n, INT_MAX));
    bfs(n, stores, dist, grid);

    // 计算总配送成本
    int total_cost = 0;
    for (const auto& customer : customers) {
        int min_dist = INT_MAX;

        // 计算当前客户到每个分店的最短距离
        if (dist[customer.x][customer.y] != INT_MAX) {
            min_dist = dist[customer.x][customer.y];  // 计算到分店的最短路径
        }

        // 总成本加上最小配送成本 * 需求量
        total_cost += min_dist * customer.c;
    }

    cout << total_cost << endl;
    return 0;
}
