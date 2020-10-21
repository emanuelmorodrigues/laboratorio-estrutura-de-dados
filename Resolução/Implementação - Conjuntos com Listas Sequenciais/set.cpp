#include "set.hpp"
#include <iostream>
#include <limits>
using namespace std;
// Construir lista vazia, mas com capacidade máxima informada.
set::set(unsigned int capacidade) {
    vetor = new int[capacidade];
    this->tamanho = 0;
    this->capacidade = capacidade;
}

// --- Métodos de "Coleção" ---


// Inserir "elemento" na coleção.
// Retornar indicativo de sucesso da inserção.
// NOTE Deve aumentar a capacidade caso necessário.
// NOTE Observe que aumentar em apenas uma unidade não nos alivia da pressão que tínhamos antes...
bool set::inserir(int elemento) {
    if(pertence(elemento)) return false;
    if(tamanho < capacidade) {
        vetor[this->tamanho] = elemento;
        this->tamanho++;
        return true;
    } else {
            vetor[this->tamanho] = elemento;
            capacidade *= (capacidade + 1);
            vetor = (int*) realloc (vetor, (capacidade) * sizeof(int));
            this->tamanho++;
            return true;
    }
    return false;
}

// Remover "elemento" da coleção.
// Retornar indicativo de sucesso da remoção.
// NOTE Necessário preservar a ordem relativa dos que restarem.
bool set::remover(int elemento) {
    for(unsigned int i = 0; i < this->tamanho; i++){
        if(vetor[i] == elemento){
             for(unsigned int j = i+1; j < this->tamanho; j++) {
                vetor[j-1] = vetor[j];
            }
            this->tamanho--;
            return true;
        }
    }
    return false;
}

// Determinar se "elemento" é um dos elementos ainda na coleção.
bool set::pertence(int elemento) const {
    for(unsigned int i = 0; i < this->tamanho; i++){
        if(vetor[i] == elemento){
            return true;
        }
    }
    return false;
}


// --- Métodos de "Conjunto" ---

// Tornar o próprio conjunto (`this`) o resultado de sua união com o outro informado.
void set::uniao_com(set const &conjunto) {
    unsigned int tamanho_conjunto = conjunto.obter_tamanho();
    for(unsigned int i = 0; i < tamanho_conjunto; i++ ){
        if(!pertence(conjunto.vetor[i])) inserir(conjunto.vetor[i]);
    }
}

// Tornar o próprio conjunto (`this`) o resultado de sua intersecção com o outro informado.
void set::intersecao_com(set const &conjunto) {
    for(unsigned int i = 0; i < this->tamanho; i++){
        if(!conjunto.pertence(vetor[i])){
            remover(vetor[i]);
            i--;
        } 
    }
}

// Testar se este conjunto (`this`) está contido no outro informado.
bool set::esta_contido_em(set const &conjunto) const {
    unsigned int tamanho_conjunto = conjunto.obter_tamanho();
    unsigned int count = 0;
    if(obter_tamanho() > tamanho_conjunto) return false;
    else {
        for(unsigned int i = 0; i < tamanho_conjunto; i++ ){
            if(pertence(conjunto.vetor[i])) count++;
        }
        if(count == this->tamanho) return true;
        else return false;
    }
}