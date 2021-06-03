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
    @param String nome do arquivo, int pixel referência p/ conectar source, int pixel referência p/ conectar sink
            int[3] para armazenar width, height e max
    @return Graph*
    */
    static Graph* buildGraph(string nome, int s, int t, int data[3]){
        //declarações
        fstream arquivo;
        Graph* grafo = NULL;    
        int width, height, max, total; //largura, altura e valor máximo de cinza do arquivo, total de pixels    
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

            //armazenar dados cabeçalho
            data[0] = width;
            data[1] = height;
            data[2] = max;

            //total de pixels
            total = width*height;
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

        //conectar source e sink a todos vértices com tonalidade igual a s e t respectivamente 
        int source = grafo->getVertex(s);
        int sink = grafo->getVertex(t);
        for(int i=1; i<total; i++){
            if(grafo->getVertex(i)==source){
                grafo->setEdge(0, i, max+1);
            }
            else if(grafo->getVertex(i)==sink){
                grafo->setEdge(i, total+1, max+1);
            }
        }
        //fechar arquivo 
        arquivo.close();

        //retorno
        return grafo;
    }

    /*
    drawLimits - desenha a linha divisória entre objeto e fundo
    @param Graph* representativo da figura, int[3] (width, height, max), String nome do arquivo
    @return int 1 sucess || 0 fail
    */
    static int drawLimits (Graph* grafo, int data[3], string nome){
        //declarações
        int control = 0;
        fstream arquivo;

        //abrir arquivo
        arquivo.open(nome, ios::out);
        if(arquivo.is_open()){
            arquivo << "P2" << endl;
            arquivo << data[0] << " " << data[1] << endl;
            arquivo << data[2] << endl;
            control++;
            for(int i=0; i<data[1]; i++){
                for(int j=0; j<data[0]; j++){
                    arquivo << grafo->getVertex(control) << " ";
                    control++;
                }
                arquivo << endl;
            }
        }
        return control;
    }
};


//para testes
int main(){
    int data[3];
    Graph* test = Converter::buildGraph("small.pgm", 13, 27, data);
   // Converter::buildGraph("basic.pgm")->print();
    Converter::drawLimits (test, data, "saida.pgm");

}