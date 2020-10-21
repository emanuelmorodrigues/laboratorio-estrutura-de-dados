#include "linked_set.hpp"
#include <limits>

// Construir lista vazia, mas com capacidade máxima informada.
linked_set::linked_set() {
    this->primeiro = nullptr;
    this->tamanho = 0;
}

// --- Métodos de "Coleção" ---


// Inserir "elemento" na coleção.
// Retornar indicativo de sucesso da inserção.
// NOTE Deve aumentar a capacidade caso necessário.
// NOTE Observe que aumentar em apenas uma unidade não nos alivia da pressão que tínhamos antes...
bool linked_set::inserir(int elemento) {
    if(pertence(elemento)) return false;
    if(this->primeiro == nullptr){
        no_encadeado* no = new no_encadeado(elemento);
        this->primeiro = no;
        this->tamanho++;
        return true;
    } else {
        no_encadeado* no = this->primeiro;
        while (no->proximo != nullptr){
            no = no->proximo;
        }
        no->proximo = new no_encadeado(elemento);
        this->tamanho++;
        return true;
    }
    return false;
}

// Remover "elemento" da coleção.
// Retornar indicativo de sucesso da remoção.
// NOTE Necessário preservar a ordem relativa dos que restarem.
bool linked_set::remover(int elemento) {
    if(!pertence(elemento)){
        return false;
    } 
    no_encadeado* no = obter_no_anterior_a(elemento);
    if(no == nullptr){
        if(this->primeiro != nullptr){
            no_encadeado* no_del = this->primeiro;
            this->primeiro = no_del->proximo;
            tamanho--;
            return true;
        } else {
            return false;
        }
    } else {
        no_encadeado* no_del = no->proximo;
        no->proximo = no_del->proximo;
        tamanho--;
        return true;
    }
}

// Determinar se "elemento" é um dos elementos ainda na coleção.
bool linked_set::pertence(int elemento) const {
    if(tamanho == 0) return false;
    no_encadeado* no = this->primeiro;
    while(no != nullptr){
        if(no->valor == elemento){
            return true;
        }
        no = no->proximo;
    }
    return false;
}


// --- Métodos de "Conjunto" ---

// Tornar o próprio conjunto (`this`) o resultado de sua união com o outro informado.
void linked_set::uniao_com(linked_set const &conjunto) {
    no_encadeado* no = conjunto.primeiro;
    while(no != nullptr){
        if(!pertence(no->valor)) inserir(no->valor);
        no = no->proximo;
    }
}

// Tornar o próprio conjunto (`this`) o resultado de sua intersecção com o outro informado.
void linked_set::intersecao_com(linked_set const &conjunto) {
    no_encadeado* no = this->primeiro;
    while(no != nullptr){
        if(!conjunto.pertence(no->valor)) remover(no->valor);
        no = no->proximo;
    }
}

// Testar se este conjunto (`this`) está contido no outro informado.
bool linked_set::esta_contido_em(linked_set const &conjunto) const {
    unsigned int tam_alvo = obter_tamanho();
    unsigned int count = 0;

    no_encadeado* no = this->primeiro;

    for(unsigned int i = 0; i < tam_alvo; i++){
        if(conjunto.pertence(no->valor)) count ++;
        no = no->proximo;
    }
    if(count == tam_alvo) return true;
    else return false;
}

// --- Métodos Auxiliares ---

// Construtor de um nó, onde a informação do próximo, no momento construção, é opcional
linked_set::no_encadeado::no_encadeado(int valor, no_encadeado* proximo) {
    this->valor = valor;
    this->proximo = proximo;
}

// Desejamos obter o próprio nó que esteja no índice informado.
// Deve retornar `nullptr` quando tal nó não existe.
// Auxilia processos que dependem de encontrar nós baseado em um índice.
linked_set::no_encadeado* linked_set::obter_no_em(unsigned int indice) const {
    no_encadeado* no = this->primeiro;
    if(no != nullptr){
        for(unsigned int i = 0; i < indice; i++){
        no = no->proximo;
        }
        return no;
    } else {
        return nullptr;
    }
}

// Desejamos obter o próprio nó que veja **antes** de algum com o valor informado.
// (ou seja, `anterior.proximo.valor == valor`)
// Auxilia processos que dependem de encontrar nós baseado em um valor.
// Deve retornar `nullptr` quando tal nó não existe.
linked_set::no_encadeado* linked_set::obter_no_anterior_a(int valor) const {
    if(this->primeiro->valor == valor){
        return nullptr;
    } 
    no_encadeado* no = this->primeiro;
    while(no->proximo != nullptr){
        if(no->proximo->valor == valor){
            return no;
        }
        no = no->proximo;
    }
    return nullptr;
}
