#include <bits/stdc++.h>

using namespace std;

void leituraGrafo(vector<vector<double>> &, int);
void escritaGrafo(vector<vector<double>> &);
void BellmanFord(vector<vector<double>>&, int);
void INITIALIZE_SINGLE_SOURCE(vector<double>&, vector<int>&, int);
void RELAX(int, int, vector<double>&, vector<int>&, const vector<vector<double>>&);

int main(){
    int n, m;
    cin >> n >> m;
    vector<vector<double>> Grafo;
    Grafo.assign(n, vector<double>(n, 0));
    leituraGrafo(Grafo, m);
    escritaGrafo(Grafo);
    cout << "Total Vértices: " << n << endl;
    cout << "Total Arestas: " << m << endl;
    BellmanFord(Grafo, 0);
    return 0;
}

void leituraGrafo(vector<vector<double>> &G, int m){
    int a, b;
    double c;
    while (m--){
        cin >> a >> b >> c;
        G[a][b] = c;
    }
}

void escritaGrafo(vector<vector<double>> &G){
    int n = G.size();
    cout << "Matriz de Adjacência:" << endl;
    cout << "   ";
    for (int u = 0; u < n; u++){
        cout << u << " ";
    }
    cout << endl;
    for (int u = 0; u < n; u++){
        cout << u << ": ";
        for (int v = 0; v < n; v++){
            cout << G[u][v] << " ";
        }
        cout << endl;
    }
}

void INITIALIZE_SINGLE_SOURCE(vector<double> &d, vector<int> &pi, int s){
    int n = d.size();
    for (int v = 0; v < n; v++){
        d[v] = numeric_limits<double>::infinity();
        pi[v] = -1;
    }
    d[s] = 0;
}

void RELAX(int u, int v, vector<double> &d, vector<int> &pi, const vector<vector<double>> &G){
    if (d[v] > d[u] + G[u][v] && G[u][v] != 0){
        d[v] = d[u] + G[u][v];
        pi[v] = u;
    }
}

void BellmanFord(vector<vector<double>> &G, int s){
    int n = G.size();
    vector<double> d(n);
    vector<int> pi(n);
    INITIALIZE_SINGLE_SOURCE(d, pi, s);
    
    for (int i = 1; i < n; i++){
        for (int u = 0; u < n; u++){
            for (int v = 0; v < n; v++){
                if (G[u][v] != 0){
                    RELAX(u, v, d, pi, G);
                }
            }
        }
    }
    
    for (int u = 0; u < n; u++){
        for (int v = 0; v < n; v++){
            if (G[u][v] != 0 && d[v] > d[u] + G[u][v]){
                cout << "O grafo contém um ciclo de peso negativo." << endl;
                return;
            }
        }
    }
    
    cout << "Distâncias mínimas a partir do vértice " << s << ":" << endl;
    for (int i = 0; i < n; i++){
        cout << "Vértice " << i << ": " << d[i] << endl;
    }
}