#include <iostream>
#include <string>
#include <fstream>
#include <vector>
using namespace std;

ifstream in ("Tema2.in");
ofstream out ("Tema2.out");

class Gramatica{
    string stari;
    string alfabet;
    vector < vector < pair < int, char > > > tranzitii;
    vector <int> stari_finale;
public:
    Gramatica(): stari(""), alfabet(""), tranzitii(), stari_finale() {}
    Gramatica( string s, string a, vector <vector < pair <int, char> > > t, vector <int> f ):
    stari(std::move(s)), alfabet(std::move(a)), tranzitii(std::move(t)), stari_finale(std::move(f)){}
    friend ostream & operator<< (ostream &ostr, const Gramatica &A);
    friend istream & operator>> ( istream &istr, Gramatica &A);
    vector < vector <pair <int, char > > > getTranzitii () const {
        return this->tranzitii;
    }
    string getStari() const {
        return this->stari;
    }
    string getAlfabet() const {
        return this->alfabet;
    }
    vector <int> getStariFinale() const {
        return this->stari_finale;
    }
};

ostream& operator<< (ostream & afis, const Gramatica &A) {
    string s = A.getStari();
    afis << "N = {";
    for ( unsigned int i = 0; i < s.length() - 1; i++){
        afis << s[i] <<", ";
    }
    afis << s[s.length() - 1] << "}\nΣ = {";
    s = A.getAlfabet();
    for( unsigned int i = 0; i < s.length() - 1; i++ ){
        afis << s[i] << ", ";
    }
    afis << s[s.length() - 1] << "}\n";
    s = A.getStari();
    vector < vector <pair <int, char> > > v = A.getTranzitii();
    int i = 0;
    for ( auto y : v){
        for ( auto x : y)
            if ( x.first != -1 )
                afis << s[i] << " - " << x.second << s[x.first] << endl;
            else
                afis << s[i] << " - " << x.second << endl;
        i++;
    }
    afis << "*\n";
    return afis;
}

istream& operator>> (istream& in, Gramatica& A) {
    string aux;
    getline(in, aux);
    for( unsigned int i = 0; i < aux.length(); i++){
        if( aux[i+1] == ',' || aux[i+1] == '}'){
            A.stari.push_back(aux[i]);
        }
    }
    for( size_t i = 0; i < A.stari.length(); i++){
        vector < pair < int, char > >  v;
        A.tranzitii.emplace_back(v);
    }
    getline(in, aux);
    for( unsigned int i = 0; i < aux.length(); i++){
        if( aux[i+1] == ',' || aux[i+1] == '}'){
            A.alfabet.push_back( aux[i] );
        }
    }
    getline(in, aux);
    while( aux != "*"){
        int i = A.stari.find(aux[0]);
        if( aux.length() == 6){
            int j = A.stari.find(aux[5]);
            pair <int, char> k = make_pair(j, aux[4]);
            A.tranzitii[i].push_back(k);
        } else{
            A.tranzitii[i].emplace_back(make_pair(-1, aux[4]));
            if( aux[4] == '#')
                A.stari_finale.push_back(i);
        }
        getline(in, aux);
    }
    return in;
}

bool Apartine ( const Gramatica & A , string cuv, unsigned int c){
    vector < vector < pair < int, char > > > v = A.getTranzitii();
    string s = A.getStari();
    if ( cuv.empty() ) {
       vector<int>  f = A.getStariFinale();
       for ( auto i : f ){
           if( i == c ){
               return true;
           }
       }
       return false;
    }
    for ( auto p : v[c] ){
        if ( cuv[0] == p.second )
        {
            string cont = cuv;
            cont.erase(0, 1);
            if ( Apartine ( A, cont, p.first) )
                return true;
        }
    }
}

void Raspuns( ostream & out, const Gramatica &A, string &cuv ){
    bool ok = Apartine(A, cuv, 0);
    if ( ok )
        out << "w = " << cuv << " ∈ L(G)\n";
    else
        out << "w = " << cuv << " ∉ L(G)\n";
}

int main() {
    Gramatica A;
    in >> A ;
    out << A;
    string cuv = "-";
    while ( !cuv.empty() )
    {
        cout << "w =";
        getline ( cin, cuv);
        //cuv.erase(0, 4);
        Raspuns( out, A, cuv );
    }
    return 0;
}