/*
Pucminas - Ciência da Computação - Coração Eucarístico
Grafos - Manhã
Tárcila Fernanda Resende da Silva
Larissa Domingues Gomes
Pedro Henrique Lima Carvalho

Trabalho Final
*/


/*
Main - Cria uma arquivo .pgm que mostra o limite entre figura e fundo do arquivo .pgm de entrada
*/


//Dependencies
#include <iostream>
#include "converter.cc"

//Namespade
using namespace std;

int main(){
    //armazenar dados do cabeçalho do arquivo
    int data[3];

    //criar grafo a partir do arquivo
    Graph* grafo = Converter::buildGraph("ex4.pgm", 324, 1, data);

    //obter grafo de corte (arestas c-f, f)
    Graph* corte = grafo->maxFlow(0, grafo->nVertices()-1);

    //alterar grafo de valor dos vertices de grafo de corte para gerar .pgm
    for(int i=0; i<corte->nVertices(); i++){
        corte->setVertex(i, data[2]);
    }
    
    for(int i=0; i<corte->nVertices(); i++){
        for(int j=0; j<corte->nVertices(); j++){
            if(i!=j){
                if(grafo->getEdge(i,j)!=corte->getEdge(i,j)){
                    if(corte->getEdge(i,j)==0){
                        corte->setVertex(i, 0);
                        corte->setVertex(i, 0);
                    }
                }
            }
        }
    }

    //criar .pgm resposta
    Converter::drawLimits(corte, data, "saidaex4.pgm");

}