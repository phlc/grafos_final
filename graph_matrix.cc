/*
Pucminas - Ciência da Computação - Coração Eucarístico
Grafos - Manhã
Tárcila Fernanda Resende da Silva
Larissa Domingues Gomes
Pedro Henrique Lima Carvalho

Trabalho Final
*/


/*
Graph Class - Classe de Implementação do Grafo
Grafo Simples, Direcionado.
Estrutura de dados: matriz n x n -> n = número de vértices.
Graph(x,x) = int -> Peso do Vértice.
Graph(x,y) = 0 -> aresta inexistente
Graph(x,y) > 0 -> Peso da Aresta
*/


//Dependencies
#include <iostream>

//Namespade
using namespace std;


class Graph{
private:
    int n_vertices;       // número de vértices 
    int** matrix;         // matriz representativa do grafo.

    /*
    init - Função de Inicialização do Objeto
    @param  size: número máximo de vértices
            simple: grafo simples ou multigrafo
            directed: grafo direcionado ou não-direcionado
    */
    void init(int size){
        n_vertices = size;

        //alocação de memória para a matriz
        matrix = new int*[n_vertices];
        for(int i=0; i<n_vertices; i++){
            matrix[i] =  new int[n_vertices];
        }

        //inicialização da matriz vazia
        for(int i=0; i<n_vertices; i++){
            for(int j=0; j<n_vertices; j++){
                matrix[i][j]=0;
            }
        }
    }
public:
    /*
    Constructors
    */
    //Construtor
    Graph(int size){
        init(size);
    }
    //Construtor grafo tamnho padrão 10
    Graph(){
        init(10);
    }

    //Destructor
    ~Graph(){
        for(int i=0; i<n_vertices; i++){
            delete matrix[i];
        }
        delete matrix;
    }
    
    //Methods
    /*
    print - mostra a matriz
    */
    void print(){
        cout << "   ||";
        for(int i=0; i<n_vertices-1; i++){
            printf("%2d |", i);
        }
        cout << (n_vertices-1) << endl;
        cout << "- - - -";
        for(int i=0; i<n_vertices-1; i++){
            cout << " - -";
        }
        cout << endl;
        for (int i=0; i<n_vertices; i++){
            printf("%2d ||", i);
            for(int j=0; j<n_vertices-1; j++){
                if(i==j)
                    printf("%2d*|", matrix[i][j]);
                else
                    printf("%2d |", matrix[i][j]);
            }
            cout << " ";
            cout << matrix[i][n_vertices-1];
            if(i==n_vertices-1)
                cout << "*" << endl;
            else
                cout << endl;
        }
    }

    /*
    nVertices - informa o número de vértices do grafo
    @return número de vértices
    */
    int nVertices(){
        return n_vertices;
    }


    /*
    setVertex - estabelece um peso para um vértice no grafo
    @param vértice, peso do vértice
    @return peso do vértice || -1 erro 
    */
    int setVertex(int v, int w){
        int n=-1;
        if(v>=0 || v<n_vertices){
            n = w;
            matrix[v][v] = w;
        }
        return n;
    }

    /*
    setEdge - acrescenta/remove/altera o peso de uma aresta 
    @param vértice origiem, vértice destino, peso
    @return peso da aresta || -1 erro
    */
    int setEdge(int v1, int v2, int w){
        int n = -1;
        
        //verificar valores validos
        if(v1>=0 && v1<n_vertices && v2>=0 && v2<n_vertices){
            matrix[v1][v2]=w;
        }
        return n;
    }



// --------------------------------------- Desafio Printing Cycles ------------------------------------------------
private:
    /*
    deepFirstSearch - Busca por um ou todos os vértices - Recusivo
    @param matriz de Adjacência, número de vértices, vértice de início, vértice procurado
    @return sinal de target encontrado
    */
    int deepFirstSearch(int** mAdj, int n_v, int v1, int v_target, int visited[], int* parents){
        //definições
        int signal = 0; //sinal de parada para v_target encontrado

        //caminhamento
        for (int i=1; i<n_v && signal==0; i++){
            int v2 = (v1+i)%n_v;
            if(mAdj[v1][v2]==1 && visited[v2]==0){
                visited[v2]=1;
                parents[v2]=v1;
                if(v2==v_target)
                    return 1;
                signal = deepFirstSearch(mAdj, n_v, v2, v_target, visited, parents);
            }
        }    
        return signal;
    }

    /*
    deepFirstSearch - Busca por um ou todos os vértices
    @param matriz de Adjacência, número de vértices, vértice de início, vértice procurado
    @return array de ancestralidade
    */
    int* deepFirstSearch (int** mAdj, int n_v, int v_init, int v_target){
        //definições
        int visited[n_v];
        int signal = 0; //sinal de parada para v_target encontrado
        int* parents = new int[n_v];
        
        //inicialização do arrranho de ancestralidade
        for(int i=0; i<n_v;i++){
            visited[i]=0;
            parents[i]=-1;
        }

        //vértice raiz
        parents[v_init] = v_init;
        visited[v_init] =  1;
        if(v_init == v_target) 
            signal = 1;
        
        //caminhamento
        for (int i=1; i<n_v && signal==0; i++){
            int v2 = (v_init+i)%n_v;
            if(mAdj[v_init][v2]==1 && visited[v2]==0){
                visited[v2]=1;
                parents[v2] = v_init;
                if(v2==v_target)
                    i=n_v;
                else
                   signal = deepFirstSearch(mAdj, n_v, v2, v_target, visited, parents);
            }
        }

        return parents;
    }

    /*
    deepFirstSearch - Overload - Passar por todo o grafo
    @param matriz de Adjacência, número de vértices, vértice de início.
    @return array de ancestralidade
    */
    int* deepFirstSearch (int** mAdj, int n_v, int v_init){
        return deepFirstSearch(mAdj, n_v, v_init, -1);
    }

public:
    /*
    deepFirstSearch - Overload - Chamada do Objeto
    @param vértice de início, vértice procurado.
    @return array de ancestralidade
    */
    int* deepFirstSearch (int v_init, int v_target){
        return deepFirstSearch(matrix, n_vertices, v_init, v_target);
    }

    /*
    deepFirstSearch - Overload - Chamada do Objeto - Passar por todo grafo
    @param vértice de início,.
    @return array de ancestralidade
    */
    int* deepFirstSearch (int v_init){
        return deepFirstSearch(matrix, n_vertices, v_init, -1);
    }
};

int main(){
    Graph grafo = Graph(10);
    grafo.print();
    cout << endl << endl;
    grafo.setVertex(5, 55);
    grafo.setVertex(9, 99);
    grafo.setEdge(5, 9, 59);
    grafo.setEdge(9, 5, 95);
    grafo.print();
}