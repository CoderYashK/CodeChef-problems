/*
(Challenge) Connecting computers Problem Code: POINTCN
All submissions for this problem are available.

Chef has decided to start a new software company, the company's building has N offices numbered from 0 to N-1 and there's a computer in each office.

All offices' computers should be connected within a single network, so it's required to buy some ethernet cables and hubs. a cable connecting i-th office with j-th office has cost Ci,j also if the i-th office is connected with j other offices then it's required to buy a hub with capacity j and this will cost Hi,j, note that even if the hub with higher capacity is cheaper than the hub with capacity j the company will still buy the hub with capacity j. Each office should have exactly one hub.

Find a way for building the network so that all offices are connected to each other directly or indirectly while minimizing the total cost, it's not allowed to connect same pair of offices with more than one cable and it's not allowed to connect an office with itself.

Your solution is not required to find the most optimal solution. However, the less cost your solution will provide the more points you will get.
Input

Since the input is large you will not be given it directly. Instead, you will be given some parameters and the generator used to generate the input.

The first line contains a single integer T denoting the number of test-cases

The first line of each test-case contains the integers N, Cmax, Hmax

The following 2*N lines, each contain two integers Seedi,1, Seedi,2 the seeds required for generating the input.

Using one of the generators, C++ generator, java generator, python 2 generator you will get C and H arrays.
Output

For each test-case output N lines, each line contains a string of N characters. if you want to connect i-th office and j-th office with a cable then i-th character of j-th line and j-th character of i-th line both should be '1' otherwise they should be '0'. Note that i-th character of i-th line should always be '0' because you can't connect an office with itself.

Note that cables information is enough to uniquely determine what hub should be bought for each office.
Constraints

    T = 5
    N = 1000
    0 ≤ Ci,j ≤ 1,000,000
    0 ≤ Hi,j ≤ 1,000,000
    Ci,j = Cj,i
    Ci,i = 0
    0 < Seedi,1, Seedi,2 < 1018

Test Generation

There will be 10 test-files.

The cost of a cable is chosen uniformly at random between 0 and Cmax and the cost of a hub is chosen uniformly at random between 0 and Hmax.

In each of the 10 test-files there are 5 test-cases, the values of Cmax and Hmax are:

    First test-case: Cmax = 40,000 and Hmax = 1,000,000
    Second test-case: Cmax = 100,000 and Hmax = 1,000,000
    Third test-case: Cmax = 200,000 and Hmax = 1,000,000
    Fourth test-case: Cmax = 500,000 and Hmax = 1,000,000
    Fifth test-case: Cmax = 1,000,000 and Hmax = 1,000,000

All seeds in input are randomly generated.

Scoring

You will receive a WA if you didn't follow output format or there is a pair of offices which are not connected.

Your score in a single test-case is equal to the cost of the network outputed in that test-case, your overall score is the sum of scores of all test-cases in all test-files.

During contest you will be able to get your score on first 2 test-files. After contest there will be rejudge on full tests set.

Example

Input:
1
4 10 20
123456789012 4567890123456
11111111111111 2222222222222
101010101010 2323232323232
112358132134 1928374655647
999999555555 5555559999999
234123124155 1241352352345
234213515123 1231245551223
523432523332 1234124515123

Output:
0111
1000
1000
1000

 
Explanation

Example case 1. note that the example doesn't follow constraints on T and N and also seeds are set by hand in this sample.

In this example we have the array C:

0 0 7 6
0 0 2 7
7 2 0 7
6 7 7 0

and the array H

9 10 2 0
7 9 0 7
9 3 15 18
10 3 20 5

In the output, first office is connected all other offices and that will make the cost of the network equal to S = 0 + 7 + 6 + 0 + 9 + 3 + 3 = 28, so the score on this test-case is 28. 
*/

#include<bits/stdc++.h>
using namespace std;
 
#ifdef ONLINE_JUDGE
    const int T = 5, N = 1000, MX = 1000+24;
#else
    const int T = 5, N = 1000, MX = 1000+24;
#endif
 
typedef pair<int, int> pii;
const clock_t ddl = clock() + CLOCKS_PER_SEC * 4.7;
 
 
class task_t {
    int Cmax, Hmax;
    int C[MX][MX], H[MX][MX];
    int nearest[MX][MX];
    array<bitset<N>, N> res, ans;
    int greedy_link(int deg[]);
    int score;
    double best_k;
public:
    int test_case_id_guess, best_score;
    void read();
    void show();
    void fixed_degree(double k);
} task[T];
 
 
mt19937 g19937;
int test_case_id; //0..4
 
void read_info();
 
int main() {
    read_info();
    for (int i = 0; i < T; ++i) {
        task[i].fixed_degree(1);
        task[i].fixed_degree(2);
        task[i].fixed_degree(1.5);
        task[i].fixed_degree(0.5);
        task[i].fixed_degree(2.5);
    }
    for (int i = 0; clock() < ddl; i = (i + 1) % T) {
        static uniform_real_distribution<double> dis(1.2, 1.7);
        task[i].fixed_degree(dis(g19937));
    }
    for (int i = 0; i < T; ++i) task[i].show();
}
 
namespace disjoint {
    int out[MX], fa[MX];
    int component_cnt, leaf_cnt, out_sum;
    int find_root(int x) {
        return fa[x] == x ? x : fa[x] = find_root(fa[x]);
    }
    void init(int oo[] = fa) {
        component_cnt = N;
        for (int i = 0; i < N; ++i) {
            fa[i] = i;
            out_sum += out[i] = oo[i];
        }
    }
    bool can_merge(int x, int y) {
        if (component_cnt == 1) return true;
        const int a = find_root(x), b = find_root(y);
        if (component_cnt > 2 && out[a] == 1 && out[b] == 1) return false;
        return a != b || (out[a] > 2 && out_sum >= component_cnt * 2);
    }
    bool merge(int x, int y) {
        if (component_cnt > 1) {
            int a = find_root(x), b = find_root(y);
            out_sum -= 2;
            if (a != b) {
                if(out[b] > out[a]) swap(a, b);
                --component_cnt;
                out[fa[b] = a] += out[b];
            }
            out[a] -= 2;
        }
    }
};
 
 
const int
    Cmax[] = {40000, 100000, 200000, 500000, 1000000},
    Hmax = 1e6;
uint64_t s[2];
 
 
#ifndef ONLINE_JUDGE
    mt19937 data_gen;
    void set_seed() {
        static uniform_int_distribution<uint64_t> dis(1, exa::num- 1);
        s[0] = dis(data_gen);
        s[1] = dis(data_gen);
    }
#else
    void set_seed() {
        scanf("%llu %llu", &s[0], &s[1]);
    }
#endif
 
void read_info() {
#   ifndef ONLINE_JUDGE
        int seed;
        scanf("%d%d", &test_case_id, &seed);
        printf("Seed = %d\n", seed);
        data_gen.seed(seed);
        g19937.seed(data_gen());
        //g19937.seed(random_device()());
#   else
        scanf("%*d"/*, &T*/);
        g19937.seed(random_device()());
#   endif
    for (int i = 0; i < T; ++i) task[i].read();
}
 
 
uint64_t xorshift128plus() {
    uint64_t x = s[0];
    const uint64_t y = s[1];
    x ^= x << 23;
    s[1] = x ^ y ^ (x >> 17) ^ (y >> 26);
    return s[0] = y;
}
 
void task_t::read() {
#   ifndef ONLINE_JUDGE
        Cmax = ::Cmax[test_case_id < 5 ? test_case_id : (this - task) * 5 / T];
        Hmax = ::Hmax;
#   else
        scanf("%*d%d%d", /*&N,*/ &Cmax, &Hmax);
#   endif
    test_case_id_guess = lower_bound(::Cmax, ::Cmax+5, Cmax) - ::Cmax;
    best_score = numeric_limits<int>::max();
    for (int i = 0; i < N; i++) {
        C[i][i] = 0;
        set_seed();
        for (int j = i + 1; j < N; j++)
            C[i][j] = C[j][i] = xorshift128plus() % (Cmax + 1);
    }
 
    for (int i = 0; i < N; i++) {
        set_seed();
        for (int j = 0; j < N; j++)
            H[i][j] = xorshift128plus() % (Hmax + 1);
        H[i][0] = Hmax * 5;
    }
    
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) nearest[i][j] = j;
        swap(nearest[i][0], nearest[i][i]);
        sort(nearest[i] + 1, nearest[i] + N, [key = C[i]] (int j, int k) {
            return key[j] < key[k];
        });
    }
}
 
void task_t::show() {
#   ifdef ONLINE_JUDGE
        for (int i = 0; i < N; ++i) { 
            string tmp = ans[i].to_string();
            reverse(tmp.begin(), tmp.end());
            puts(tmp.c_str());
        }
#   else
        disjoint::init();
        int score = 0;
        for (int i = 0; i < N; ++i) {
            assert(!ans[i][i]);
            score += H[i][ans[i].count()];
            for(int j = i + 1; j < N; ++j) {
                assert(ans[i][j] == ans[j][i]);
                if(ans[i][j]) { disjoint::merge(i, j); score += C[i][j];}
            }
        }
        printf("ts%d @ k = %f: %d\n", 1+test_case_id_guess, best_k, score);
        assert(disjoint::component_cnt == 1);
        assert(score == best_score);
#   endif
}
 
class parity_min {
public:
    static int sum, parity, choose[MX];
    static int alternate, alternate_id, alternate_v;
    static void init() {
        alternate = numeric_limits<int>::max();
        sum = parity = 0;
    }
    static void commit() {
        if (parity) {
            parity = 0;
            sum += alternate;
            choose[alternate_id] = alternate_v;
        }
    }
    int mi[2], op[2], id;
    parity_min(int id) : id(id) {
        mi[0] = mi[1] = numeric_limits<int>::max();
    }
    void send(int k, int v) {
        if(v < mi[k & 1]) { mi[k & 1] = v; op[k & 1] = k;}
    }
    int max() { return std::max(mi[0], mi[1]); }
    int min() { return std::min(mi[0], mi[1]); }
    ~parity_min() {
        const int p = mi[0] > mi[1], tmp = mi[!p] - mi[p];
        sum += mi[p];
        parity ^= p;
        choose[id] = op[p];
        if (tmp < alternate) {
            alternate = tmp;
            alternate_id = id;
            alternate_v = op[!p];
        }
    }
};
int parity_min::alternate, parity_min::alternate_id, parity_min::alternate_v,
    parity_min::sum, parity_min::parity, parity_min::choose[MX];
 
namespace balance_counter {
    int maxv;
    int pos[MX], val[MX];
    vector<int> vi[MX];
    void clear() { for ( ;maxv >= 0; ) vi[maxv--].clear(); maxv = 0;}
    void decreace(int x) {
        auto &v1 = vi[val[x]]; 
        pos[v1.back()] = pos[x];
        v1[pos[x]] = v1.back();
        v1.pop_back();
        auto &v0 = vi[--val[x]];
        pos[x] = v0.size();
        v0.push_back(x);
        for ( ;vi[maxv].empty(); --maxv);
    }
    int get_max() { return vi[maxv][g19937() % vi[maxv].size()];}
    void push(int k, int v) {
        if(v > maxv) maxv = v;
        pos[k] = vi[val[k] = v].size();
        vi[v].push_back(k);
    }
};
 
void task_t::fixed_degree(double k = 1) {
    parity_min::init();
    for (int i = 0, s = 0; i < N; ++i) {
        parity_min pm(i);
        for (int j = 1; j < N && pm.max() > s; ++j) {
            s += C[i][nearest[i][j]];
            pm.send(j, s + H[i][j] * k);
        }
    }
    parity_min::commit();
    score = greedy_link(parity_min::choose);
    if(score < best_score) {
#       ifndef ONLINE_JUDGE
            printf("%f@ k = %f: t%d : %d -> %d\n",
                double(ddl - clock()) / CLOCKS_PER_SEC,
                this-task, k, best_score, score);
#       endif
        best_score = score;
        best_k = k;
        ans.swap(res);
    }
}
 
// copied from http://uoj.ac/submission/188569
#define _rep(_1, _2, _3, _4, name, ...) name
#define rep2(i, n) rep3(i, 0, n)
#define rep3(i, a, b) rep4(i, a, b, 1)
#define rep4(i, a, b, c) for (int i = int(a); i < int(b); i += int(c))
#define rep(...) _rep(__VA_ARGS__, rep4, rep3, rep2, _)(__VA_ARGS__)
 
using i8 = signed char;
using i16 = signed short;
using i64 = long long;
using u8 = unsigned char;
using u32 = unsigned;
using u64 = unsigned long long;
using f80 = long double;
 
template <typename WeightType>
class MaximumWeightedMatching {
  /*
  Maximum Weighted Matching in General Graphs
  - O(n^3) time
  - O(n + m) space
  Note: each vertex is 1-indexed.
  */
public:
  using weight_t = WeightType;
  using weight_sum_t = i64;
  struct Edge { 
    bool operator < (const Edge& rhs) const {
      return (from < rhs.from) || (from == rhs.from && to < rhs.to);
    }
    int from, to; weight_t weight; 
  };
 
private:
  enum TreeLabelNumber { INNER = -1, UNUSED = 0, OUTER = 1 };
  enum LabelNumber { SEPARATED = -2, DEFAULT = -1 };
  enum EdgeNumber { UNDEFINED = 1 << 30 };
 
  static constexpr weight_t INF = weight_t(1) << (sizeof(weight_t) * 8 - 2);
 
  struct Node { int next, from, to; };
  struct Label { int from, to; };
 
  class Queue {
  public:
    Queue() {}
    Queue(int N) : que(N), qh(0), qt(0) {}
    void clear() { qh = qt = 0; }
    int* data() { return que.data(); }
    bool empty() const { return qh == qt; }
    int dequeue() { return que[qh++]; }
    void enqueue(int u) { que[qt++] = u; }
    int operator [] (int i) const { return que[i]; }
    int size() const { return qt; }
 
    vector<int> que;
    int qh, qt;
  };
 
public:
  MaximumWeightedMatching(int N, const vector<Edge>& raw_edges) 
      : N(N), B((N - 1) / 2), size(N + B + 1) {
 
    offsets.assign(N + 2, 0);
    for (auto& e : raw_edges) {
      offsets[e.from + 1]++;
      offsets[e.to + 1]++;
    }
    rep(i, 1, N + 1) offsets[i] += offsets[i - 1];
    edges.resize(raw_edges.size() * 2);
    rep(i, raw_edges.size()) {
      auto& e = raw_edges[i];
      edges[offsets[e.from]++] = {e.from, e.to, 2 * e.weight};
      edges[offsets[e.to]++] = {e.to, e.from, 2 * e.weight};
    }
    rep(i, N + 1) offsets[N + 1 - i] = offsets[N - i];
    offsets[0] = 0;
  }
 
  pair<weight_sum_t, vector<int>> maximum_weighted_matching() {
    initialize();
    set_potential();
    rep(u, 1, N + 1) if (!mate[u]) {
      for (int s = 0; !augmented(u, s); s = adjust_dual_solutions());
      fix_blossom_bases();
      clear_label();
    }
    weight_sum_t ret = 0;
    rep(u, 1, N + 1) if (mate[u] > u) {
      weight_t max_w = 0;
      rep(eid, offsets[u], offsets[u + 1]) if (edges[eid].to == mate[u]) {
        max_w = max(max_w, edges[eid].weight);
      }
      ret += max_w;
    }
    return { ret >> 1, mate };
  }
  
private:
  inline int encode(int e) const {
    return e + size + 1; // should be >= 3
  }
 
  inline weight_t reduced_cost(int u, int v, const Edge& e) const {
    return potential[u] + potential[v] - e.weight;
  }
 
  inline weight_t reduced_cost(int eid) const {
    return reduced_cost(edges[eid].from, edges[eid].to, edges[eid]);
  }
 
  void rematch(int v, int w) {
    auto t = mate[v]; mate[v] = w;
    if (mate[t] != v) return;
    if (label[v].to == 0) {
      mate[t] = label[v].from;
      rematch(mate[t], t);
    } else {
      int x = label[v].from, y = label[v].to;
      rematch(x, y); rematch(y, x);
    }
  }
 
  Label search_blossom_edge(int bid) const {
    int b = base[bid], bv = b;
    for (; node[bv].next != b; bv = node[node[bv].next].next);
    return {node[bv].from, node[bv].to};
  }
 
  void label_blossom(int bid, int m, Label l) {
    label[bid] = {l.from, (l.to == surface[l.to]) ? 0 : l.to};
    if (bid <= N) return;
    int b = base[bid]; label_blossom(b, mate[bid] = m, l);
    l = search_blossom_edge(bid);
    for (int bv = b, bw; node[bv].next != b; bv = node[bw].next) {
      label_blossom(bw = node[bv].next, 0, l);
      label_blossom(node[bw].next, node[bw].from, {node[bv].from, node[bv].to});
    }
  }
 
  int find_mate(int bid) {
    return bid <= N ? mate[bid] : mate[bid] = find_mate(base[bid]);
  }
 
  void push_inner_blossom_rec(int bid, bool push=true) {
    tree_label[bid] = (bid <= N) ? INNER : UNUSED;
    if (bid > N) {
      int v = base[bid], u = v;
      do { push_inner_blossom_rec(v, push); } while ( (v = node[v].next) != u);
    } else if (push) inner_vertices[inner_vertices_size++] = bid;
  }
 
  void push_inner_blossom(int bid) {
    if (tree_label[bid] != UNUSED) return;
    bool push = label[bid].from != SEPARATED;
    if (bid > N) {
      if (push) inner_blossoms[inner_blossom_size++] = bid; 
      push_inner_blossom_rec(bid, push);
    } else if (push) inner_vertices[inner_vertices_size++] = bid;
    tree_label[bid] = INNER;
  }
 
  void push_outer_blossom_rec(int bid) {
    tree_label[bid] = (bid <= N) ? OUTER : UNUSED;
    if (bid > N) {
      int v = base[bid], u = v;
      do { push_outer_blossom_rec(v); } while ( (v = node[v].next) != u );
    } else outer_vertices.enqueue(bid);
  }
 
  void push_outer_blossom(int bid, bool push) {
    push_outer_blossom_rec(bid);
    if (bid <= N) return;
    if (push) outer_blossoms[outer_blossom_size++] = bid, tree_label[bid] = OUTER;
    else tree_label[bid] = UNUSED;
  }
 
  inline void merge_edge(int x, int bx, int eid) {
    auto& e = edges[eid];
    int y = e.to, by = surface[y];
    if (tree_label[by] != OUTER || bx == by) return;
    auto r_cost = reduced_cost(x, y, e);
    if (r_cost < best_cost[by].first) {
      if (best_cost[by].first == INF) merged_edges[merged_edge_size++] = by;
      best_cost[by] = {r_cost, eid};
    }
  }
 
  inline void merge_vertex(int x, int bx) {
    rep(eid, offsets[x], offsets[x + 1]) merge_edge(x, bx, eid);
    best_edge[x] = UNDEFINED;
  }
 
  void clear_best_edges(int b) {
    if (b > N) {
      int v = b = base[b];
      do { clear_best_edges(v); } while ( (v = node[v].next) != b );
    } else best_edge[b] = UNDEFINED;
  }
 
  void merge_outer(int b, int bid) {
    if (b > N) {
      for (int eid = be_head[b]; eid >= 0; eid = be_next[eid]) {
        merge_edge(edges[eid].from, bid, eid);
      }
      be_head[b] = -1;
      clear_best_edges(b);
    } else merge_vertex(b, bid);
  }
 
  void merge_inner(int b, int bid) {
    if (b > N) {
      int v = b = base[b];
      do { merge_inner(v, bid); } while ((v = node[v].next) != b);
    } else merge_vertex(b, bid);
  }
 
  void build_linked_list(int bid) {
    if (bid <= N) return;
    int last = -1;
    for (; merged_edge_size > 0; ) {
      int by = merged_edges[--merged_edge_size], eid = best_cost[by].second;
      int x = edges[eid].from, y = edges[eid].to;
      be_next[eid] = last;
      if (tree_label[y] == OUTER) update_best_edge(y, by, best_cost[by].first, eid);
      if (best_edge[x] == UNDEFINED || best_cost[by].first < reduced_cost(best_edge[x])) {
        best_edge[x] = eid;
      }
      best_cost[by] = {INF, UNDEFINED};
      last = eid;
    }
    be_head[bid] = last;
  }
 
  void merge_best_edges(int bid, int inner_count) {
    rep(i, inner_count) {
      int bv = outer_blossoms[outer_blossom_size + i];
      if (bv >= 0) merge_outer(bv, bid), merge_inner(node[bv].next, bid);
      else merge_inner(~bv, bid), merge_outer(node[~bv].next, bid);
    }
    merge_outer(base[bid], bid);
    build_linked_list(bid);
  }
 
  void contract(int x, int y, int eid) {
    int s = surface[x], t = surface[y];
    if (s == t) return;
    auto h = label[surface[mate[s]]].from = label[surface[mate[t]]].from = -encode(eid);
 
    int lca = -1;
    for (; ; label[surface[mate[s]]].from = h) {
      if (mate[t] != 0) swap(s, t);
      s = lca = surface[label[s].from];
      if (label[surface[mate[s]]].from == h) break;
    }
 
    int inner_count = 0;
    for (int dir = 0; dir < 2; ++dir) {
      int v = (dir == 0) ? x : y;
      while (1) {
        int bv = surface[v], mv = mate[bv], bmv = surface[mv];
        if (bv == lca) break;
        label[mv] = label[bmv] = {x, y};
        auto n = node[bmv];
        if (!dir) {
          node[bv] = {bmv, mate[mv], mv};
          node[bmv].next = surface[n.to];
        } else {
          node[surface[n.to]] = {bmv, n.to, n.from};
          node[bmv] = {bv, mv, mate[mv]}; 
        }
        push_outer_blossom(bmv, false);
        v = label[bv].from;
 
        // Caution: used as temporary array
        outer_blossoms[outer_blossom_size + (inner_count++)] = !dir ? bv : ~bmv;
      }
    }
    node[surface[y]] = {surface[x], y, x};
 
    int bid = next_bid.back(); next_bid.pop_back();
    base[bid] = lca, label[bid].from = label[lca].from, mate[bid] = mate[lca];
 
    tree_label[bid] = OUTER;
    set_surface(bid, bid);
    merge_best_edges(bid, inner_count);
 
    outer_blossoms[outer_blossom_size++] = bid;
  }
 
  inline void update_best_edge(int y, int by, weight_t r_cost, int eid) {
    if (tree_label[by] != OUTER && best_edge[y] == UNDEFINED) {
      neighbors[neighbor_size++] = y;
    }
    if (best_edge[y] == UNDEFINED || r_cost < reduced_cost(best_edge[y])) {
      best_edge[y] = eid;
    }
  }
 
  void build_edge_list(int b) {
    if (b <= N) return;
    merge_inner(b, b);
    build_linked_list(b);
  }
 
  bool augmented(int root, int s) {
    if (s == 0) {
      int br = surface[root];
      push_outer_blossom(br, true);
      label_blossom(br, 0, {0, 0});
      build_edge_list(br);
    } 
    for (; !outer_vertices.empty() || s > 0; s = 0) {
      auto x = (s > 0) ? s : outer_vertices.dequeue();
      if (potential[x] == 0) {
        if (root != x) rematch(x, 0);
        return true;
      }
      rep(eid, offsets[x], offsets[x + 1]) {
        int bx = surface[x], y = edges[eid].to, by = surface[y];
        if (bx == by) continue;
        auto r_cost = reduced_cost(x, y, edges[eid]);
        if (r_cost > 0 || tree_label[by] != OUTER) {
          update_best_edge(y, by, r_cost, eid);
          if (r_cost > 0) continue;
        }
        if (label[by].from >= 0) {
          contract(x, y, eid);
          continue;
        } 
        if (tree_label[by] == UNUSED) {
          push_inner_blossom(by);
          if (by != y) label_blossom(by, find_mate(by), {DEFAULT, 0});
        }
        int z = mate[by];
        if (z == 0 && by != surface[root]) {
          rematch(x, y); rematch(y, x);
          return true;
        }
        int bz = surface[z];
        if (label[bz].from < 0) {
          node[by] = {-1, y, x};
          push_outer_blossom(bz, true);
          label_blossom(bz, mate[z], {x, y});
          build_edge_list(bz);
        }
      }
    }
    return false;
  }
 
  void set_surface(int b, int bid) {
    for (int v = base[b]; surface[v] != bid; v = node[v].next) {
      if (v > N) tree_label[v] = UNUSED, set_surface(v, bid);
      surface[v] = bid;
    }
  }
  
  void reset_surface(int b, int bid) {
    surface[b] = bid;
    if (b <= N) return;
    for (b = base[b]; surface[b] != bid; b = node[b].next) reset_surface(b, bid);
  }
 
  void separate_blossom(int bid, bool push_blossom=true) {
    tree_label[bid] = UNUSED, label[bid].from = SEPARATED;
    if (bid <= N) return;
    if (push_blossom) inner_blossoms[inner_blossom_size++] = bid;
    for (int b = base[bid]; label[b].from != SEPARATED; b = node[b].next) {
      separate_blossom(b, false);
    }
  }
 
  void reverse_blossom(int b) {
    int v = b, fr = node[b].from, to = node[b].to;
    for (int nv = node[v].next; nv != b; ) {
      int nnext = node[nv].next, nfr = node[nv].from, nto = node[nv].to;
      node[nv].next = v, node[nv].from = to, node[nv].to = fr;
      fr = nfr, to = nto, v = nv, nv = nnext;
    }
    node[b].next = v, node[b].from = to, node[b].to = fr;
  }
 
  void expand_blossom(int bid) {
    next_bid.push_back(bid); tree_label[bid] = UNUSED;
    for (int b = base[bid]; surface[b] == bid; b = node[b].next) reset_surface(b, b);
    int old_base = base[bid], target = surface[node[bid].from]; 
    if (mate[node[target].from] == node[target].to) reverse_blossom(old_base);
    for (int b = target; node[b].next != old_base; ) {
      separate_blossom(b = node[b].next); separate_blossom(b = node[b].next);
    }
    node[target] = node[bid];
    for (int b = old_base; ; b = node[b].next) {
      label[b].from = DEFAULT, tree_label[b] = INNER; 
      if (b > N) inner_blossoms[inner_blossom_size++] = b;
      int m = find_mate(b), bm = surface[m];
      if (b != old_base) mate[bm] = mate[m];
      label[m] = label[bm] = {node[b].to, node[b].from};
      if (b == target) break;
      push_outer_blossom(b = node[b].next, true);
      build_edge_list(b);
    }
    base[bid] = bid, surface[bid] = bid;
  }
 
  void update_potential(int* vs, int s, weight_t delta, int label) {
    rep(i, s) {
      int x = vs[i];
      if (tree_label[x] != label) continue;
      potential[x] += delta;
    }
  }
 
  int adjust_dual_solutions() {
    pair<weight_t, int> delta1(INF, 0), delta2(INF, 0), delta3(INF, 0), delta4(INF, 0);
    rep(i, outer_vertices.size()) {
      int y = outer_vertices[i], eid = best_edge[y];
      delta1 = min(delta1, {potential[y], y});
      if (eid != UNDEFINED) {
        delta3 = min(delta3, {reduced_cost(eid) >> 1, y});
      }
    }
    rep(i, neighbor_size) {
      int y = neighbors[i];
      if (tree_label[y] == UNUSED) {
        int eid = best_edge[y], x = edges[eid].from;
        delta2 = min(delta2, {reduced_cost(x, y, edges[eid]), x});
      }
    }
    rep(i, inner_blossom_size) if (tree_label[inner_blossoms[i]] == INNER) {
      int b = inner_blossoms[i];
      delta4 = min(delta4, {potential[b] >> 1, b});
    }
    auto delta = min(min(delta1, delta2), min(delta3, delta4));
    auto d = delta.first;
    update_potential(outer_vertices.data(), outer_vertices.size(), -1 * d, OUTER);
    update_potential(inner_vertices.data(), inner_vertices_size,    1 * d, INNER);
    update_potential(outer_blossoms.data(), outer_blossom_size,     2 * d, OUTER);
    update_potential(inner_blossoms.data(), inner_blossom_size,    -2 * d, INNER);
    if (delta4.first == d) {
      expand_blossom(delta4.second);
      return -1;
    } else {
      return delta.second;
    }
  }
 
  void fix_blossom_bases() {
    int remain = size - next_bid.size() - (N + 1);
    for (int bid = N + 1; bid < size && remain > 0; ++bid) if (base[bid] != bid) {
      int b = base[bid];
      for (int skipped = 0; skipped < 2;) {
        b = node[b].next;
        if (mate[node[b].from] == node[b].to) skipped = 0;
        else skipped++;
      }
      base[bid] = b;
      --remain;
    }
  }
 
  void free_edge_list(int x) {
    be_head[x] = -1;
  }
 
  void clear_vertices(int* vs, int size) {
    rep(i, size) {
      int v = vs[i]; 
      label[v] = {DEFAULT, 0}; tree_label[v] = UNUSED; best_edge[v] = UNDEFINED;
    }
  }
 
  void clear_label() {
    label[0] = {DEFAULT, 0};
    clear_vertices(outer_vertices.data(), outer_vertices.size()); outer_vertices.clear();
    clear_vertices(inner_vertices.data(), inner_vertices_size); inner_vertices_size = 0;
    clear_vertices(outer_blossoms.data(), outer_blossom_size);
    rep(i, outer_blossom_size) if (be_head[outer_blossoms[i]] >= 0) free_edge_list(outer_blossoms[i]);
    outer_blossom_size = 0;
    clear_vertices(inner_blossoms.data(), inner_blossom_size); inner_blossom_size = 0;
    rep(i, neighbor_size) best_edge[neighbors[i]] = UNDEFINED;
    neighbor_size = 0;
  }
 
  void set_potential() {
    potential.resize(size);
    rep(u, 1, N + 1) {
      weight_t max_w = 0;
      rep(eid, offsets[u], offsets[u + 1]) max_w = max(max_w, edges[eid].weight);
      potential[u] = max_w >> 1;
    }
  }
 
  void initialize() {
    mate.assign(size, 0);
    label.assign(size, {-1, 0});
 
    surface.resize(size); rep(i, size) surface[i] = i;
    base.resize(size); rep(i, size) base[i] = i;
    node.resize(size); rep(i, size) node[i] = {i, i, i};
 
    outer_vertices = Queue(N);
    inner_vertices.resize(N + 1); inner_vertices_size = 0;
    outer_blossoms.resize(B); outer_blossom_size = 0;
    inner_blossoms.resize(B); inner_blossom_size = 0;
 
    tree_label.assign(size, UNUSED);
 
    next_bid.resize(B);
    rep(i, B) next_bid[i] = size - 1 - i;
 
    merged_edges.resize(N + 1); merged_edge_size = 0;
    best_cost.assign(size, {INF, UNDEFINED});
 
    neighbors.resize(N + 1); neighbor_size = 0;
    best_edge.assign(size, UNDEFINED);
 
    be_head.assign(size, -1);
    be_next.resize(edges.size());
  }
 
private:
  int N, B, size;
  vector<Edge> edges;
  vector<int> offsets;
 
  vector<Label> label;
  vector<int> mate, surface, base;
  vector<Node> node;
  vector<weight_t> potential;
 
  vector<int> next_bid;
 
  vector<i8> tree_label;
 
  Queue outer_vertices;
  vector<int> inner_vertices; int inner_vertices_size;
  vector<int> outer_blossoms; int outer_blossom_size;
  vector<int> inner_blossoms; int inner_blossom_size;
 
  vector<int> merged_edges; int merged_edge_size;
  vector< pair<weight_t, int> > best_cost;
  vector<int> neighbors; int neighbor_size;
  vector<int> best_edge;
 
  vector<int> be_head, be_next;
};
 
 
int task_t::greedy_link(int deg[]) {
    balance_counter::clear();
    disjoint::init(deg);
    static int nearest_i[N];
    score = 0;
    for (int i = 0; i < N; ++i) {
        res[i].reset();
        nearest_i[i] = 1;
        score += H[i][deg[i]];
        balance_counter::push(i, deg[i]);
    }
    for( ;balance_counter::maxv >= 2; ) {
        const int u = balance_counter::get_max();
        int &j = nearest_i[u];
        int oj = j;
        for ( ;j < N; ++j) {
            const int v = nearest[u][j];
            if(!res[u][v] && balance_counter::val[v] > 0 && disjoint::can_merge(u, v))
                break;
        }
        if (j == N) return numeric_limits<int>::max();
        const int v = nearest[u][j++];
        balance_counter::decreace(u);
        balance_counter::decreace(v);
        res[u].set(v);
        res[v].set(u);
        score += C[u][v];
        disjoint::merge(u, v);
    }
    //if (disjoint::component_cnt != 1) return numeric_limits<int>::max();
    auto& v = balance_counter::vi[1];
    using MWM = MaximumWeightedMatching<int>;
    static vector<MWM::Edge> e;
    e.clear();
    e.reserve(v.size() * v.size() >> 1);
    for (int i = 0; i < v.size(); ++i)
        for (int j = i + 1; j < v.size(); ++j) if(!res[v[i]][v[j]])
            e.push_back({i + 1, j + 1, Cmax - C[v[i]][v[j]]});
    //printf("%d %d\n", v.size(), e.size());
    MWM gg(v.size(), e);
    auto resp = gg.maximum_weighted_matching();
    auto& mate = resp.second;
    for (int i = 1; i <= v.size(); ++i) {
        const int a = v[i - 1], b = v[mate[i]-1];
        if(a < b) {
            //printf("%d-%d ", a, b);
            assert(!res[a][b]);
            res[a].set(b);
            res[b].set(a);
            score += C[a][b];       
        }
    }
    //printf("\n%d %d\n", v.size(), mate.size());
    return score;
}