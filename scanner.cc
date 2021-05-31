/*
Pucminas - Ciência da Computação - Coração Eucarístico
Grafos - Manhã
Tárcila Fernanda Resende da Silva
Larissa Domingues Gomes
Pedro Henrique Lima Carvalho

Trabalho Final
*/


/*
Scanner - Class para leitura do arquivo .pgm e contrução do grafo
*/


//Dependencies
#include <iostream>
#include <fstream>
#include "graph_matrix.cc"

//Namespade
using namespace std;


class Scanner{

private:
    /*
    Constructor not allowed - Static Class
    */
    Scanner(){}

public:    
    //Methods
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
    Scanner::buildGraph("small.pgm")->print();
   // Scanner::buildGraph("basic.pgm")->print();
}