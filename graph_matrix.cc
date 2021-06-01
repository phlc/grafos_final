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

    //Construtor grafo vazio - não permitido
    Graph(){}

public:
    /*
    Constructors
    */
    //Construtor
    Graph(int size){
        init(size);
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
    getVertex - informa o valor de um vértice
    @param int vértice
    @return int valor
    */
    int getVertex(int v){
        return matrix[v][v];
    }

    /*
    getEdge - informa o valor de uma aresta
    @param int v1, int v2
    @return int valor
    */
    int getEdge(int v1, int v2){
        return matrix[v1][v2];
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
            n = w;
            matrix[v1][v2]=w;
        }
        return n;
    }



private:
    /*
    Line Class - Subclasse de fila para Breadth Search First
    */
    
    
};