//
//  main.cpp
//  MoneyMatters
//
//  Created by Stefán Hafsteinsson on 17/12/14.
//  Copyright (c) 2014 Stefán Hafsteinsson. All rights reserved.
//

#include <algorithm>
#include <bitset>
#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <utility>
#include <vector>

using namespace std;

struct union_find
{
    vector<int> parent;
    vector<int> owe;
    vector<int> sumParent;
    union_find(int n)
    {
        parent = vector<int>(n);
        owe = vector<int>(n, 0);
        sumParent = vector<int>(n, 0);
        for (int i = 0; i < n; i++)
        {
            parent[i] = i;
        }
    }
    int find(int x)
    {
        if (parent[x] == x)
        {
            return x;
        } else
        {
            parent[x] = find(parent[x]);
            return parent[x];
        }
    }
    bool connected(int x, int y)
    {
        return find(x) == find(y);
    }
    void unite(int x, int y)
    {
        if(!connected(x, y))
        {
            updateSum(x, y);
        }
        parent[find(x)] = find(y);
    }
    void updateSum(int x, int y)
    {
        sumParent[find(y)] += sumParent[find(x)];
    }
};

int main(int argc, const char * argv[]) {
    
    int n, m, o, x, y;
    
    scanf("%d%d", &n, &m);
    
    union_find uf(n);
    
    for(int i = 0; i < n; i++)
    {
        scanf("%d", &o);
        
        uf.owe[i] = o;
        uf.sumParent[i] = o;
    }
    
    for(int i = 0; i < m; i++)
    {
        scanf("%d%d", &x, &y);
        
        uf.unite(x, y);
    }
    
    for(int i = 0; i < n; i++)
    {
        if(uf.sumParent[uf.find(i)] != 0)
        {
            cout << "IMPOSSIBLE" << endl;
            return 0;
        }
    }
    
    cout << "POSSIBLE" << endl;
    return 0;
}
