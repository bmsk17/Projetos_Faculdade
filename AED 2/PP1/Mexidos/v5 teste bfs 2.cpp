#include <iostream>
#include <limits>
enum Cores {BRANCO,CINZA,PRETO};
int TEMPO;

using namespace std;

template<class T>
class No{                      //Noz�o da massa!

private:

    T item;
    No<T>* prox;

public:

    No(){
        prox = NULL;
    }
    No(T item){
    this->item = item;
    this->prox = NULL;
    }

    void setItem(T item);
    void setProx(No<T>* prox);
    T getItem();
    No<T>* getProx();
};

template<class T>
void No<T>::setItem(T item) {
    this->item = item;
}

template<class T>
void No<T>::setProx(No* prox) {
    this->prox = prox;
}

template<class T>
T No<T>::getItem() {
    return item;
}

template<class T>
No<T>* No<T>::getProx() {
     return prox;
}

//----------------------------FIM N� ------------------------------------------------

template<class T>
class Lista{                        //Lista din�mica basicona
private:

    No<T>* prim;
    No<T>* ult;
    int TAM;

public:

    Lista (){
    prim = new No<T>;
    prim->setProx(NULL);
    ult = prim;
    }

    ~Lista(){}
    No<T>* getPrim();
    int busca(int i);
    void insere(T item);
    void remove(T item);
    void print();
    int getTAM();
};

template <class T>
int Lista<T>::getTAM(){
    return TAM;
}

template<class T>
No<T>* Lista<T>::getPrim(){
    return prim;
}

template<class T>
int Lista<T>::busca(int i){

    No<T> *p = getPrim()->getProx();

    int cont = 1;
    int achou;

    while(p != NULL){
      if(cont == i){
         achou = p->getItem();
      }
      cont++;
      p = p->getProx();
    }

    return achou;
}

template<class T>
void Lista<T>::insere(T item){
    ult->setProx(new No<T>);
    ult = ult->getProx();
    ult->setProx(NULL);
    ult->setItem(item);
    TAM++;
}

template<class T>
void Lista<T>::print(){
    No<T>* p = prim->getProx();
    while(p != NULL){
        cout << p->getItem() << " ";
        p = p->getProx();
    }
    cout << endl;
}

//--------------------------------FIM LISTA-------------------------------
template<class T>
class Fila{                     //Fila usada na fun��o de busca em largura!
private:

    No<T>* frente;
    No<T>* tras;


public:

    Fila(){
    frente = new No<T>;
    frente->setProx(NULL);
    tras = frente;
    }

    T getFrente();
    bool vazia();
    void enfileira(T item);
    void desenfileira(T item);
    void print();
};

template<class T>
bool Fila<T>::vazia(){
    return tras == frente;
}

template<class T>
T Fila<T>::getFrente(){
    return frente->getProx()->getItem();
}

template<class T>
void Fila<T>::enfileira(T item){
    tras->setProx(new No<T>);
    tras = tras->getProx();
    tras->setItem(item);
    tras->setProx(NULL);
}

template<class T>
void Fila<T>::desenfileira(T item){
    No<T>* aux = frente;
    frente = frente->getProx();
    item = frente->getItem();
    delete aux;
}

template<class T>
void Fila<T>::print(){
    frente = frente->getProx();
    while(frente != NULL){
        cout << frente->getItem() << "\n";
        frente = frente->getProx();
    }
}

//----------------------------------------FIM FILA---------------------------------

template<class T>
class Aresta{
private:

    T vertice1;
    T vertice2;
    float peso ;

public:
    Aresta(){}
    Aresta(T vertice1,T vertice2,float peso){
        this->vertice1= vertice1;
        this->vertice2= vertice2;
        this->peso= peso;
    }
    T getVertice1();
    T getVertice2();
    float getPeso();
};
template<class T>
T Aresta<T>::getVertice1() {
     return vertice1;
}

template<class T>
T Aresta<T>::getVertice2() {
     return vertice2;
}

template<class T>
float Aresta<T>::getPeso() {
     return peso;
}

//--------------------------------INICIO GRAFO----------------------------

template<class T>
class Grafo{
private:

    Lista<T> *adj;     //Lista de adjac�ncia pra guardar os adjacentes de cada vertice
    int ordem = 0;          //Ordem = quantidade de vertices do grafo.
    int tamanho;


public:

    Grafo(T ordem){
     inicializar(ordem);    //Construtor que recebe a ordem do grafo!
    }
    void inicializar(T ordem);
    void insereAresta(T vert1, T vert2);
    void print();
    int getOrdem();
    Lista<T>* getAdj();
    T BFS(T iniVert, T fimVert);//busca em largura
    int verificaAresta (T vert1, T vert2); //BUSCA ARESTA NO GRAFO (listas de adj)
    int verificaVertice (T vert);
    void solucao(T antecessor,T vinicial,T vfinal,Grafo<T> g,Lista<T> *salvar,int volta);
    void retorna(T antecessor,T vinicial,T vfinal,Grafo<T> g,Lista<T> *salvar,int volta);
};

template <class T>
Lista<T>* Grafo<T>::getAdj(){
   return adj;
}

template <class T>
int Grafo<T>::getOrdem(){
    return ordem;
}

template<class T>
void Grafo<T>::inicializar(T ordem){
    this->ordem = ordem;
    adj = new Lista<T>[ordem + 1];
}

template <class T>
int Grafo<T>::verificaAresta(T vert1,T vert2){

    Lista<T> *aux = adj;
    int i = ordem;
    int cont=0;

    for (int j = 1;j<=i;j++){
        if(j==vert1){
                No<T> *z = aux[j].getPrim()->getProx();
                cont=0;
                while(z!=NULL){
                    if(z->getItem()==vert2){
                        cont++;
                    }
                    z= z->getProx();
                }
        }
    }


  if (cont > 0){
    return 0;
  }
  else{
    return 1;
  }

}

template <class T>
int Grafo<T>::verificaVertice(T vert){

    Lista<T> *aux = adj;
    int i = ordem;
    T cont=0,vetorligado;

    for (int j = 1;j<=i;j++){
        No<T> *z = aux[j].getPrim()->getProx();
        cont=0;
        while(z!=NULL){
            if(z->getItem()==vert){
                cont++;
                vetorligado=z->getItem();
            }
            z= z->getProx();
        }
    }
    if (cont > 0){
        return 0;
    }
    else{
        return 1;
    }
}

template<class T>                             //Insere arestas
void Grafo<T>::insereAresta(T vert1, T vert2){
    adj[vert1].insere(vert2);
    adj[vert2].insere(vert1);
    tamanho++;
}

template<class T>
T Grafo<T>::BFS (T iniVert, T fimVert){      //Busca em largura, que ir� pegar o menor caminho entre dois vertices
    Grafo<T> arvore(ordem);
    T vertice = iniVert;
    bool encontrou = false;
    int cor[ordem + 1];
    int distancia[ordem + 1];
    T predecessor[ordem + 1];

    for(int i = 0; i < ordem + 1; i++){     //Deixar todos com cor branca, distancia infinita e antecessor -1
        cor[i] = BRANCO;
        distancia[i] = numeric_limits<int>::max();  //INFINITO!
        predecessor[i] = -1;
    }

    cor[vertice] = CINZA;
    distancia[vertice] = -1;
    predecessor[vertice] = -1;

    Fila<T> fila;
    fila.enfileira(vertice);

    while(!fila.vazia()){
        vertice = fila.getFrente();

        fila.desenfileira(vertice);
        No<T>* posicao = adj[vertice].getPrim()->getProx();    //Pega o primeiro valor da lista

        while(posicao != NULL){     //percorre a lista
            if(cor[posicao->getItem()] == BRANCO){     //Se o elemento da lista n foi visto
                cor[posicao->getItem()] = CINZA;       //Troca o valor pra visto
                distancia[posicao->getItem()] = distancia[vertice] + 1;    //Pega a distancia e incrementa 1
                predecessor[posicao->getItem()] = vertice;
                fila.enfileira(posicao->getItem());
                cout<<"Esta no Vertice : "<<vertice<< " Enfileirou : "<<posicao->getItem()<<endl;
                int j= vertice;
                arvore.insereAresta(vertice,posicao->getItem());
            }
            posicao = posicao->getProx();   //Ir� pegar o proximo elemento da lista
        }
        cout<<endl;
        cor[vertice] = PRETO; //saindo do loop v�rtice vira preto pois ja foi visitado
    }

    T verticeAux = iniVert;
    int coraux[ordem + 1];
    int distanciaAux[ordem + 1];
    T predecessorAux[ordem + 1];

    for(int i = 0; i < ordem + 1; i++){     //Deixar todos com cor branca, distancia infinita e antecessor -1
        coraux[i] = BRANCO;
        distanciaAux[i] = numeric_limits<int>::max();  //INFINITO!
        predecessorAux[i] = -1;
    }

    arvore.print();
    Lista<T> save;
    solucao(0,iniVert,fimVert,arvore,&save,0);
    save.print();

}

template<class T>
void Grafo<T>::solucao(T antecessor,T vinicial,T vfinal,Grafo<T> g,Lista<T> *salvar,int volta){
    Lista<T> *aux = g.getAdj();
    No<T>* posicao = aux[vinicial].getPrim()->getProx();
    cout<<"----------------------------------"<<endl;
    while(posicao!=NULL){
        if(posicao->getItem()==vfinal){
            salvar->insere(antecessor);
            volta=1;
        }

        if(volta==1){
                cout<<endl<<"INSERIU -------------------"<<endl;
                cout<<"antecessor = "<<antecessor<<endl;
                cout<<"vinicial = "<<vinicial<<endl;
                cout<<"Posicao = "<<posicao->getItem()<<endl;
                cout<<"vfinal = "<<vfinal<<endl;
            if(antecessor==posicao->getItem()){
                salvar->insere(antecessor);
                solucao(posicao->getItem(),vfinal,vinicial,g,salvar,volta);
            }
        }

        if(volta==0){
            if(antecessor!=posicao->getItem()){
                cout<<"antecessor = "<<antecessor<<endl;
                cout<<"vinicial = "<<vinicial<<endl;
                cout<<"Posicao = "<<posicao->getItem()<<endl;
                cout<<"vfinal = "<<vfinal<<endl;
                solucao(vinicial,posicao->getItem(),vfinal,g,salvar,volta);
            }
        }


        posicao=posicao->getProx();

    }


}


template<class T>
void Grafo<T>::print(){
    for(int i = 1;i < ordem+1;i++){
        cout << "v[" << i << "] = ";
        adj[i].print();
    }
}
//-------------------------------------FIM GRAFO --------------------

//--------------------------------INICIO DFS----------------------------

template <class T>
class DFS {
private:
  int *pred;
  Grafo<T> *grafocriado;
  Cores *cor;
  int *d;
  int *f;
  void dfs(Grafo<T> &);
  void dfsVisita(Grafo<T> &,int);
public:
  DFS(){ }
  void inicia(Grafo<T> &);
  int *getPred();
  Cores *getCor();
  int *getF();
  int *getD();
  Grafo<T>* getGrafoCriado();
};

template <class T>
Grafo<T>* DFS<T>::getGrafoCriado(){
  return grafocriado;
}

template <class T>
void DFS<T>::inicia(Grafo<T> &g){
  dfs(g);
}

template <class T>
int * DFS<T>::getPred(){
  return pred;
}

template <class T>
Cores * DFS<T>::getCor(){
  return cor;
}
template <class T>
int* DFS<T>::getF(){
  return f;
}

template <class T>
int* DFS<T>::getD(){
  return d;
}


template <class T>
void DFS<T>::dfsVisita(Grafo<T> &g, int u){
  TEMPO = TEMPO +1;
  d[u] = TEMPO;
  cor[u] = CINZA;
  Lista<int> adj = g.getAdj()[u];
  int i = 1;
  while(i <= adj.getTAM()){
        int v = adj.busca(i);
        if(cor[v] == BRANCO){
            pred[v] = u;
            dfsVisita(g,v);
            grafocriado->insereAresta(u,v);
        }
        i++;
    }
  cor[u] = PRETO;
  TEMPO = TEMPO + 1;
  f[u] = TEMPO;
}

template <class T>
void DFS<T>::dfs(Grafo<T> &g){
    const int N = g.getOrdem();
    pred = new int[N];
    cor = new Cores[N];
    d = new int[N];
    f = new int[N];
    grafocriado = new Grafo<T>(N);

    for(int u=1;u<=N;u++){
      cor[u] = BRANCO;
      pred[u] = -1;
    }
    TEMPO = 0;
    for(int u=1;u<=N;u++){
      if(cor[u] == BRANCO){
         dfsVisita(g,u);
      }
    }
}


template<class T>
class SistemaPlanetario{
private:

    Grafo<T> *grafo;
    Lista<Aresta<int> > arestas;
    float tamanho;
    int ordem;

public:
    SistemaPlanetario(){}
    SistemaPlanetario(T ordem){
        this->grafo= new Grafo<int>(ordem) ;
        this->tamanho=0;
        this->ordem=ordem;
    }
    void insereAresta(int vert1, int vert2,float peso);
    void print();
    T BFS(T iniVert, T fimVert,Lista<T> listaExecao);
    float getTamanho();
    float soma();
    Grafo<T>* getGrafo();


};

template <class T>
Grafo<T>* SistemaPlanetario<T>::getGrafo(){
    return grafo;
}

template <class T>
float SistemaPlanetario<T>::getTamanho(){
    return tamanho;
}
template<class T>                             //Insere arestas
void SistemaPlanetario<T>::insereAresta(int vert1, int vert2,float peso){
    grafo->insereAresta(vert1,vert2);
    Aresta<T> x(vert1,vert2,peso);
    Aresta<T> y(vert2,vert1,peso);
    arestas.insere(x);

}
template<class T>                             //Insere arestas
void SistemaPlanetario<T>::print(){
    grafo->print();
}
template<class T>                             //Insere arestas
T SistemaPlanetario<T>::BFS(T iniVert, T fimVert,Lista<T> listaExecao){
    grafo->BFS(iniVert,fimVert,listaExecao);
}

template <class T>
float SistemaPlanetario<T>::soma(){
    DFS<int> dfs;
    int i=0;

    Grafo<int> grafoAux(ordem);
    No<Aresta<T> >* p = arestas.getPrim()->getProx();
    while(p != NULL){
        grafoAux.insereAresta(p->getItem().getVertice1(),p->getItem().getVertice2());
        p = p->getProx();
    }

    dfs.inicia(grafoAux);

    No<Aresta<T> >* s = arestas.getPrim()->getProx();
    dfs.getGrafoCriado()->print();
    /*while(s != NULL){
        cout<<s->getItem().getVertice1()<< " "<<s->getItem().getVertice2()<< " "<<endl;
        s = s->getProx();
    }*/
    while(s != NULL){
        i = dfs.getGrafoCriado()->verificaAresta(s->getItem().getVertice1(),s->getItem().getVertice2());
        if(i==0){
            cout<<endl<<"Vertice  : "<<s->getItem().getVertice1()<<" para "<<s->getItem().getVertice2()<<endl;
            tamanho = tamanho + s->getItem().getPeso();
        }
        s = s->getProx();
    }

}

//--------------------------------FIM DFS----------------------------


int main()
{
 Grafo<int> g(18);
    g.insereAresta(1, 3);
    g.insereAresta(1, 9);
    g.insereAresta(1, 15);
    g.insereAresta(1, 16);
    g.insereAresta(1, 17);
    g.insereAresta(2, 4);
    g.insereAresta(2, 5);
    g.insereAresta(2, 11);
    g.insereAresta(2, 12);
    g.insereAresta(2, 18);
    g.insereAresta(3, 8);
    g.insereAresta(3, 9);
    g.insereAresta(3, 14);
    g.insereAresta(4, 5);
    g.insereAresta(4, 6);
    g.insereAresta(4, 7);
    g.insereAresta(4, 9);
    g.insereAresta(4, 15);
    g.insereAresta(5, 7);
    g.insereAresta(5, 12);
    g.insereAresta(5, 14);
    g.insereAresta(5, 15);
    g.insereAresta(6, 7);
    g.insereAresta(6, 9);
    g.insereAresta(7, 12);
    g.insereAresta(7, 13);
    g.insereAresta(7, 15);
    g.insereAresta(7, 17);
    g.insereAresta(8, 11);
    g.insereAresta(8, 12);
    g.insereAresta(8, 14);
    g.insereAresta(9, 10);
    g.insereAresta(9, 11);
    g.insereAresta(9, 12);
    g.insereAresta(9, 14);
    g.insereAresta(9, 13);
    g.insereAresta(10, 14);
    g.insereAresta(10, 15);
    g.insereAresta(11, 12);
    g.insereAresta(11, 13);
    g.insereAresta(11, 16);
    g.insereAresta(11, 18);

    g.print();
    Lista<int> LS;
    LS.insere(1);

    int i =g.BFS(1,5);



    return 0;
}




























