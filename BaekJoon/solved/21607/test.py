#!/usr/bin/python3
# Code by CHATGPT, Failed..

MOD = 100003

def f(x):
    return (2 * x * x - 1) % MOD

def g(x):
    return (4 * x * x * x - 3 * x) % MOD

class SegmentTree:
    def __init__(self, data):
        self.n = len(data)
        self.tree = [0] * (4 * self.n)
        self.lazy_f = [False] * (4 * self.n)
        self.lazy_g = [False] * (4 * self.n)
        self.build(0, 0, self.n - 1, data)
        
    def build(self, node, start, end, data):
        if start == end:
            self.tree[node] = data[start]
        else:
            mid = (start + end) // 2
            self.build(2 * node + 1, start, mid, data)
            self.build(2 * node + 2, mid + 1, end, data)
            self.tree[node] = (self.tree[2 * node + 1] + self.tree[2 * node + 2]) % MOD
    
    def apply_lazy(self, node, start, end):
        if self.lazy_f[node]:
            self.tree[node] = f(self.tree[node])
            if start != end:
                self.lazy_f[2 * node + 1] = True
                self.lazy_f[2 * node + 2] = True
            self.lazy_f[node] = False
        
        if self.lazy_g[node]:
            self.tree[node] = g(self.tree[node])
            if start != end:
                self.lazy_g[2 * node + 1] = True
                self.lazy_g[2 * node + 2] = True
            self.lazy_g[node] = False

    def update_range(self, l, r, func_type):
        self._update_range(0, 0, self.n - 1, l, r, func_type)
        
    def _update_range(self, node, start, end, l, r, func_type):
        self.apply_lazy(node, start, end)
        
        if start > end or start > r or end < l:
            return
        
        if start >= l and end <= r:
            if func_type == 'f':
                self.tree[node] = f(self.tree[node])
                if start != end:
                    self.lazy_f[2 * node + 1] = True
                    self.lazy_f[2 * node + 2] = True
            elif func_type == 'g':
                self.tree[node] = g(self.tree[node])
                if start != end:
                    self.lazy_g[2 * node + 1] = True
                    self.lazy_g[2 * node + 2] = True
            return
        
        mid = (start + end) // 2
        self._update_range(2 * node + 1, start, mid, l, r, func_type)
        self._update_range(2 * node + 2, mid + 1, end, l, r, func_type)
        self.tree[node] = (self.tree[2 * node + 1] + self.tree[2 * node + 2]) % MOD
    
    def query(self, idx):
        return self._query(0, 0, self.n - 1, idx)
    
    def _query(self, node, start, end, idx):
        self.apply_lazy(node, start, end)
        if start == end:
            return self.tree[node]
        mid = (start + end) // 2
        if idx <= mid:
            return self._query(2 * node + 1, start, mid, idx)
        else:
            return self._query(2 * node + 2, mid + 1, end, idx)

# 입력 처리 및 쿼리 실행
if __name__ == "__main__":
    import sys
    input = sys.stdin.read
    data = input().split()
    
    n = int(data[0])
    q = int(data[1])
    
    A = list(map(int, data[2:n+2]))
    queries = data[n+2:]
    
    seg_tree = SegmentTree(A)
    
    index = 0
    result = []
    while index < len(queries):
        query_type = int(queries[index])
        if query_type == 1:
            l = int(queries[index + 1]) - 1
            r = int(queries[index + 2]) - 1
            seg_tree.update_range(l, r, 'f')
            index += 3
        elif query_type == 2:
            l = int(queries[index + 1]) - 1
            r = int(queries[index + 2]) - 1
            seg_tree.update_range(l, r, 'g')
            index += 3
        elif query_type == 3:
            x = int(queries[index + 1]) - 1
            result.append(seg_tree.query(x))
            index += 2
    
    for res in result:
        print(res)
