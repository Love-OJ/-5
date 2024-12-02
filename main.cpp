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

// �ĸ�������ƶ����������ң�
int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, -1, 1};

bool is_valid(int x, int y, int n, const vector<vector<char>>& grid) {
    return x >= 0 && x < n && y >= 0 && y < n && grid[x][y] != 'X';
}

// BFS����Ӷ���ֵ굽����������·��
void bfs(int n, const vector<Store>& stores, vector<vector<int>>& dist, const vector<vector<char>>& grid) {
    queue<pair<int, int>> q;

    // ��ʼ���������飬����λ�ö���ΪINF
    for (int i = 0; i < n; ++i) {
        fill(dist[i].begin(), dist[i].end(), INT_MAX);
    }

    // �����зֵ������в����ó�ʼ����Ϊ0
    for (const auto& store : stores) {
        q.push({store.x, store.y});
        dist[store.x][store.y] = 0;
    }

    // BFS�������·��
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

    // ����ֵ�λ��
    for (int i = 0; i < m; ++i) {
        cin >> stores[i].x >> stores[i].y;
        stores[i].x--; stores[i].y--;  // ������ת��Ϊ��0��ʼ
    }

    // ����ͻ�λ�ú�������
    for (int i = 0; i < k; ++i) {
        cin >> customers[i].x >> customers[i].y >> customers[i].c;
        customers[i].x--; customers[i].y--;  // ������ת��Ϊ��0��ʼ
    }

    // �����ϰ���λ��
    vector<vector<char>> grid(n, vector<char>(n, '.'));
    for (int i = 0; i < d; ++i) {
        cin >> obstacles[i].first >> obstacles[i].second;
        obstacles[i].first--; obstacles[i].second--;  // ������ת��Ϊ��0��ʼ
        grid[obstacles[i].first][obstacles[i].second] = 'X';  // ����ϰ���
    }

    // ����ÿ���ֵ굽ÿ��������·��
    vector<vector<int>> dist(n, vector<int>(n, INT_MAX));
    bfs(n, stores, dist, grid);

    // ���������ͳɱ�
    int total_cost = 0;
    for (const auto& customer : customers) {
        int min_dist = INT_MAX;

        // ���㵱ǰ�ͻ���ÿ���ֵ����̾���
        if (dist[customer.x][customer.y] != INT_MAX) {
            min_dist = dist[customer.x][customer.y];  // ���㵽�ֵ�����·��
        }

        // �ܳɱ�������С���ͳɱ� * ������
        total_cost += min_dist * customer.c;
    }

    cout << total_cost << endl;
    return 0;
}
