/*
Pucminas - Ciência da Computação - Coração Eucarístico
Grafos - Manhã
Tárcila Fernanda Resende da Silva
Larissa Domingues Gomes
Pedro Henrique Lima Carvalho

Trabalho Final
*/


/*
Converter - Class para leitura do arquivo .pgm e contrução do grafo e vice-versa
Cada pixel do arquivo é representado por um vértice, lido da esqueda para direita, de cima para baixo
Peso do vértice é o valor do pixel
Haverá uma arestas entre dois pixels se forem vizinhos diretos (diagonal não é vizinho)
Peso da aresta é dado pela fórmula: p = (valor_máximo_escala)+1 - |peso_v1 - peso_v2|
Dessa forma, o fluxo será maior para tonalidade proximas e menor para tonalidades diferentes.
*/


//Dependencies
#include <iostream>
#include <fstream>
#include "graph_matrix.cc"

//Namespade
using namespace std;


class Converter{

private:
    /*
    Constructor not allowed - Static Class
    */
    Converter(){}

    /*
    calcFlow - Calcula o fluxo de uma aresta
    @param int max, int p1, int p2
    @return int flow
    */
    static int calcFlow (int max, int p1, int p2){
        int abs = p1 - p2;
        if(abs < 0)
            abs *= -1;
        return ((max+1) - abs);
    }

public:    
    /*
    buildGraph - Constroi um grafo a partir de um arquivo .pgm
    @param String nome do arquivo
    @return Graph*
    */
    static Graph* buildGraph(string nome){
        //declarações
        fstream arquivo;
        Graph* grafo = NULL;    
        int width, height, max; //largura, altura e valor máximo de cinza do arquivo    
        char buffer[50];

        //abrir arquivo
        arquivo.open(nome, ios::in);
        if(arquivo.is_open()){
            //ler primeira linha
            arquivo.getline(buffer, 50);

            //ler cabeçalho
            arquivo >> width;
            arquivo >> height;
            arquivo >> max;

            //total de pixels
            int total = width*height;
            //criar grafo
            grafo = new Graph(total+2); // todos os pixels + uma Sorce (vértice 0) e um Sink (vértice lagura*altura+1)
            
            //preencher os vértices com os valores de cada pixel
            for (int pixel=1; pixel<=total; pixel++){
                int value;
                arquivo >> value;
                grafo->setVertex(pixel, value);
            }

            //preencher as arestas 
            for(int i=1; i<=total; i++){
                //com vizinho de acima
                if ((i-width)>0){
                    grafo->setEdge(i, (i-width), calcFlow(max, grafo->getVertex(i), grafo->getVertex(i-width)));
                }
                //com vizinho de baixo
                if(i+width<=total){
                    grafo->setEdge(i, (i+width), calcFlow(max, grafo->getVertex(i), grafo->getVertex(i+width)));
                }
                //com vizinho da esquerta
                if(i%width!=1){
                    grafo->setEdge(i, i-1, calcFlow(max, grafo->getVertex(i), grafo->getVertex(i-1)));
                }
                //com vizinho da direita
                if(i%width!=0){
                    grafo->setEdge(i, i+1, calcFlow(max, grafo->getVertex(i), grafo->getVertex(i+1)));
                }

            }
        }


        //fechar arquivo 
        arquivo.close();

        //retorno
        return grafo;
    }

    /*
    drawLimits - desenha a linha divisória entre objeto e fundo
    @param Graph* representativo da figura, int width, int height, String nome do arquivo
    @return int 1 sucess || 0 fail
    */
    static int drawLimits (Graph* grafo, int width, int height, string nome){
        int control = 0;
        return control;
    }
};

//para testes
int main(){
    Converter::buildGraph("small.pgm")->print();
   // Converter::buildGraph("basic.pgm")->print();
}