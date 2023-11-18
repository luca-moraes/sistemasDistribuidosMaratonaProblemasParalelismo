#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long   ll;

const int N = 1022;

const ll mod = 1e9 + 7;

class matrix{
    public:
    int n;
    ll mat[N][N];
    ll aux[N][N];

    void change_n(int n){
        this->n = n;
    }

    matrix(int n){
        this->n = n;
    }

    void init_base(){
        for(int i = 0 ; i < n ; i++){
            for(int j = 0 ; j < n ; j++){
                mat[i][j] = 0LL;
            }
        }
    }

    void init_ident(){
        for(int i = 0 ; i < n ; i++){
            for(int j = 0 ; j < n ; j++){
                mat[i][j] = (i == j);
            }
        }
    }

    matrix(){

    }
    
    void multiply(matrix *rhs){
        for(int i = 0 ; i < n ; i++){
            for(int j = 0 ; j < n ; j++){
                this->aux[i][j] = 0LL;
                
                for(int k = 0 ; k < n ; k++){
                    this->aux[i][j] += this->mat[i][k] * rhs->mat[k][j];
                    this->aux[i][j] %= mod;
                }
            }
        }
        
        for(int i = 0 ; i < n ; i++){
            for(int j = 0 ; j < n ; j++){
                this->mat[i][j] = this->aux[i][j];
            }
        }
    }

    void multiply(matrix &rhs){
        for(int i = 0 ; i < n ; i++){
            for(int j = 0 ; j < n ; j++){
                this->aux[i][j] = 0LL;
                
                for(int k = 0 ; k < n ; k++){
                    this->aux[i][j] += this->mat[i][k] * rhs.mat[k][j];
                    this->aux[i][j] %= mod;
                }
            }
        }
        
        for(int i = 0 ; i < n ; i++){
            for(int j = 0 ; j < n ; j++){
                this->mat[i][j] = this->aux[i][j];
            }
        }
    }

    void pow(ll p, matrix &ident){
        // cout << "cheguei aqui!" << endl;
        auto &r = ident;
        auto d = this;
        // int cnt = 0;

        while(p){
            if(p & 1LL){
                r.multiply(d);
            }

            // cout << "step " << ++cnt << endl;

            d->multiply(d);
            p >>= 1LL;
        }

        // r.print();
    }

    //pass one line of matrix in the vector, put the base value too, |clause| = n + 1
    //line is 0 index based
    void add_clause(int lin, matrix &base, vector< ll > clause){
        // assert(clause.size() == (long unsigned int) n + 1);
        // assert(0 <= lin && lin < n);

        for(int i = 0 ; i < n ; i++){
            this->mat[lin][i] = clause[i];
        }

        base.mat[lin][0] = clause[n];
    }

    void print_line(int line){
        for(int i = 0 ; i < n ; i++){
            printf("%lld ", this->mat[i][line]);
        }
        
        printf("\n");
    }
    
    void print(){
        cout << "sz = " << this->n << endl;

        for(int i = 0 ; i < n ; i++){
            for(int j = 0 ; j < n ; j++){
                cout << this->mat[i][j] << " ";
            }
            
            cout << endl;
        }
    }
    
    matrix get_answer_matrix(int e, matrix &ident, matrix &base){
        this->pow(e, ident);

        // ident.print();

        ident.multiply(base);

        // ident.print();
        
        return ident;
    }
    
    void set_base_case(int line, matrix &base, ll val){
        base.mat[line][0] = val;
    }
    
    ll get_answer(int line){
        return this->mat[line][0];
    }
};

matrix ans(N), base(N), ident(N);

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n, k;
    
    cin >> n >> k;

    ans.change_n(n);
    base.change_n(n);
    ident.change_n(n);

    ident.init_ident();
    base.init_base();

    vector< ll > P;
    vector< ll > A;

    for(int i = 0 ; i < n ; i++){
        ll ai;

        cin >> ai;

        A.push_back(ai);
    }

    for(int i = 0 ; i < n ; i++){
        ll pi;

        cin >> pi;

        P.push_back(pi);
    }

    // reverse(P.begin(), P.end());

    P.push_back(A[n - 1]);

    ans.add_clause(0, base, P);

    for(int i = 1 ; i < n ; i++){
        vector< ll > clausei;

        for(int j = 0 ; j < n ; j++){
            if(j == i - 1){
                clausei.push_back(1);
            }else{
                clausei.push_back(0);
            }
        }

        clausei.push_back(A[n - i - 1]);

        ans.add_clause(i, base, clausei);
    }

    // ans.print();

    // base.print();

    cout << ans.get_answer_matrix(k - n, ident, base).get_answer(0) << "\n";

    return 0;
}