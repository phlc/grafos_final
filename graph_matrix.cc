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
    copy - Cria uma cópia do grafo
    @return Graph*
    */
    Graph* copy(){
        Graph* cp = new Graph(this->n_vertices);

        for(int i=0; i<n_vertices; i++){
            for(int j=0; j<n_vertices; j++){
                cp->matrix[i][j] = this->matrix[i][j];
            }
        }

        return cp;
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
    Queue Class - Subclasse de fila para Breadth Search First
    */
    class Queue{
        int first; //primeiro da fila
        int last; //ultima posicao da fila (vazio)
        int size; //tamanho da fila
        int* arr; //fila

    public:
        //constructor
        Queue(int s){
            first = 0;
            last = 0;
            size = s;
            arr = new int[size]; 
        }

        //destructor
        ~Queue(){
            delete arr;
        }

        /*
        enqueue - enfileira um elemento na fila
        @param int n elemento
        @return int 0 fail | 1 success
        */
        int enqueue(int n){
            if (first != last - size +1){
                arr[last]=n;
                last++;
                return 1;
            }
            return 0;
        }

        /*
        dequeue - desenfileira um elemento da fila
        @return int n elemento | -1 fila vazia
        */
        int dequeue(){
            if(first!=last){
                return arr[first++];
            }
            return -1;
        }

        /*
        isEmpty - verifica se a fila está vazia
        @bool true vazia | false !vazia
        */
        bool isEmpty(){
            return first==last;
        }
    };

public:
    /*
    breadthSearch - Realiza uma busca em largura
    @param int v1 inicial, int v2 objetivo
    @return int* arranjo de ascendentes | arranjo[v2] = -1 fail | NULL erro
    */
    int* breadthSearch(int v1, int v2){
        //declarações
        int* parents = NULL;
        Queue fila = Queue(n_vertices);

        //teste validade parametros
        if (0<=v1 && v1<n_vertices && 0<=v2 && v2<n_vertices){
            //inicializar parents e visited para controle de visitados
            parents = new int[n_vertices];
            int visited[n_vertices];
            for (int i=0; i<n_vertices; i++){
                visited[i] = parents[i] = -1;
            }

            //enfileirar vértice inicial 
            fila.enqueue(v1);

            //vértice inicial pai dele mesmo
            parents[v1]=v1;

            //buscar
            while(!fila.isEmpty() && visited[v2]!=1){
                int v = fila.dequeue();
                visited[v] = 1; //marcar como visitado

                //inserir na listas vértices adjacentes não visitados
                for(int i=v+1; i%n_vertices!=v; i++){
                    if(matrix[v][i%n_vertices]!=0 && visited[i%n_vertices]!=1){
                        parents[i%n_vertices]=v;
                        visited[i%n_vertices] = 1;
                        fila.enqueue(i%n_vertices);
                    }
                }
            }
        }
        return parents;
    }

    /*
    minCapacity - Dado um caminho, encontra a menor capacidade
    @param int* parents - arranjo de ancestralidade, int s - source, int t - sink
    @return int - menor capacidade
    */
    int minCapacity(int* parents, int s, int t){
        int v1 = parents[t];
        int v2 = t;
        int capacity = matrix[v1][v2];

        while (v1 != s){
            v2 = v1;
            v1 = parents[v2];
            if (capacity > matrix[v1][v2]){
                capacity = matrix[v1][v2];
            }
        }

        return capacity;
    }

    /*
    subtractFlow - Subtrai um fluxo de um caminho
    @param int* parents = arranjo de ancestralidade, int s- source, int t - sink, int flow
    */
    void subtractFlow(int* parents, int s, int t, int flow){
        int v1 = parents[t];
        int v2 = t;

        //subtrair fluxo
        matrix[v1][v2] = matrix[v1][v2] - flow;
        matrix[v2][v1] = matrix[v2][v1] + flow;

        //repetir pelo caminho
        while (v1 != s){
            v2 = v1;
            v1 = parents[v2];
            matrix[v1][v2] = matrix[v1][v2] - flow;
            matrix[v2][v1] = matrix[v2][v1] + flow;
        }

    }


    /*
    maxFlow - Calcula o corte mínimo do grafo
    @param int s - source, int t - sink
    @return Graph* com o fluxo maximo nas arestas
    */
    Graph* maxFlow(int s, int t){
        //criar cópia
        Graph* max = this->copy();

        //busca por largura
        int* parents = max->breadthSearch(s, t);

        //repetir enquanto houver caminho s->t
        while (parents[t]!=-1){
            //achar menor capacidade do caminho
            int flow = max->minCapacity(parents, s, t);

            //subtrair fluxo
            max->subtractFlow(parents, s, t, flow);

            //nova busca
            parents =  max->breadthSearch(s, t);

        }

        return max;
    }

    
};

// para teste
int main(){
    Graph test = Graph(6);
    test.setEdge(0, 1, 16);
    test.setEdge(0, 3, 13);
    test.setEdge(1, 2, 12);
    test.setEdge(1, 3, 10);
    test.setEdge(2, 3, 9);
    test.setEdge(2, 5, 20);
    test.setEdge(3, 1, 4);
    test.setEdge(3, 4, 14);
    test.setEdge(4, 2, 7);
    test.setEdge(4, 5, 4);
    
    test.print();

    Graph* corte = test.maxFlow(0, 5);

    cout << endl;

    corte->print();

    int* parents = corte->breadthSearch(0, 5);

    cout << endl;
    for(int i=0; i<6; i++){
        cout << parents[i] << " ";
    }
    cout << endl;
}