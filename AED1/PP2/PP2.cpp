#include <iostream>

using namespace std;

class Chave{

private:

    string key;

public:

    Chave (){}
    Chave (string key){
      this->key = key;
    }

    void Imprime();
    string getKey();
    void setKey(string chave);
};

string Chave::getKey(){
   return this->key;
}

void Chave::setKey(string chave) {
        this->key = chave;
    }

void Chave::Imprime(){
  cout <<key <<" ";
}
//-------------------------------------------------------------------------------------------------
template <class T>
class No {

private:

    No<T>* esq,*dir;
    T item;
    int alt;

public:

        No<T>(T item){
            this->item = item;
            this->esq = NULL;
            this->dir = NULL;
            this->alt = 0;
        }

         void setAlt(int alt);
         int getAlt ();
         No<T>* getEsq();
         No<T>* getDir();
         T getChave();
         void setChave(T item);
         void setEsq(No<T>* item);
         void setDir(No<T>* item);


};

template <class T>
void No<T>::setAlt(int alt){
   this->alt = alt;
}

template <class T>
int No<T>::getAlt(){
   return this->alt;
}

template <class T>
 No<T>* No<T>::getEsq(){
    return this->esq;
}

template <class T>
T No<T>::getChave(){
  return this->item;
}

template <class T>
void No<T>::setChave(T item){
  this->item = item;
}

template <class T>
 No<T>* No<T>::getDir(){
    return this->dir;
}

template <class T>
 void No<T>::setEsq(No<T>* no){
    this->esq = no;
}

template <class T>
 void No<T>::setDir(No<T>* no){
    this->dir = no;
}


//-------------------------------------------------------------------------------------------------

template <class T>
class AVL{

private:

    No<T>* raiz;

public:

    AVL (){
      raiz = NULL;
    }

    No<T>* getRaiz();
    No<T>* BuscaMenor(No<T>* no);
    No<T>* BuscaMaior(No<T>* no);
    int Maior(int x,int y);
    int Altura(No<T>* no);
    void Insere(T item);
    No<T>* Insere(T item, No<T>* no);
    No<T>* Remove(T item, No<T>* no);
    void Remove(T item);
    No<T>* RSD (No<T>* no);
    No<T>* RSE (No<T>* no);
    No<T>* RDE(No<T>* no);
    No<T>* RDD(No<T>* no);
    void ImprimePreOrdem (No<T>* Raiz);
    void ImprimeOrdem (No<T>* Raiz);
    void ImprimePosOrdem (No<T>* Raiz);
    No<T>* Busca (No<T>* Raiz, T item);
    void ImprimeNo(No<T>* no);


};

template <class T>
No<T>* AVL<T>::getRaiz(){
   return this->raiz;
}

template <class T>
No<T>* AVL<T>::BuscaMenor(No<T>* no){

        if(no == NULL){
            return NULL;
        }
        else if(no->getEsq() == NULL){
            return no;
         }
        else{
            return BuscaMenor(no->getEsq());
        }
}

template <class T>
No<T>* AVL<T>::BuscaMaior(No<T>* no){

        if(no == NULL){
            return NULL;
        }
        else if(no->getDir() == NULL){
            return no;
        }
        else{
            return BuscaMaior(no->getDir());
        }
}

template <class T>
int AVL<T>::Maior(int x,int y){

   if (x > y){
    return x;
   }
   else {
    return y;
   }
}

template <class T>
int AVL<T>::Altura(No<T>* no){

   if (no == NULL){
     return -1;
   }
   else{
     return no->getAlt();
   }
}

template <class T>
void AVL<T>::Insere(T item){

    raiz = Insere(item, raiz);
}

template <class T>
No<T>* AVL<T>::Insere(T item, No<T>* no){

      if(no == NULL){
            no = new No<T>(item);

        }
        else if(item.getKey() < no->getChave().getKey()){

            no->setEsq(Insere(item, no->getEsq()));

           if(Altura(no->getEsq()) - Altura(no->getDir()) == 2){
                if(item.getKey() < no->getEsq()->getChave().getKey()){
                    no = RSD(no);
                }
                else{
                    no = RDD(no);
                }
            }
        }

        else if(item.getKey() > no->getChave().getKey()){

            no->setDir(Insere(item, no->getDir()));

            if(Altura(no->getDir()) - Altura(no->getEsq()) == 2){
                if(item.getKey() > no->getDir()->getChave().getKey()){
                    no = RSE(no);
                }
                else{
                    no = RDE(no);
                }
            }
        }

        no->setAlt(Maior(Altura(no->getEsq()), Altura(no->getDir()))+1);
        return no;
}

template <class T>
void AVL<T>::Remove(T item){

   raiz = Remove(item, raiz);
}

template <class T>
No<T>* AVL<T>::Remove(T item, No<T>* no){

        No<T>* aux;


        if(no == NULL){
            return NULL;
        }


        else if(item.getKey() < no->getChave().getKey()){
            no->setEsq(Remove(item, no->getEsq()));
        }
        else if(item.getKey() > no->getChave().getKey()){
            no->setDir(Remove(item, no->getDir()));
        }


        else if(no->getEsq() != NULL && no->getDir() != NULL){

            aux = BuscaMenor(no->getDir());
            no->setChave(aux->getChave());
            no->setDir(Remove(no->getChave(), no->getDir()));
        }

        else{
            aux = no;
            if(no->getEsq() == NULL)
               no = no->getDir();
            else if(no->getDir() == NULL)
                no = no->getEsq();
            delete aux;
        }

        if(no == NULL){
            return no;
        }

        no->setAlt(Maior(Altura(no->getEsq()), Altura(no->getDir()))+1);


        if(Altura(no->getEsq()) - Altura(no->getDir()) == 2){

            if(Altura(no->getEsq()->getEsq()) - Altura(no->getEsq()->getDir()) == 1){
                  return RSE(no);
            }

            else{
                return RDE(no);
            }
        }


        else if(Altura(no->getDir()) - Altura(no->getEsq()) == 2){

            if(Altura(no->getDir()->getDir()) - Altura(no->getDir()->getEsq()) == 1){
                return RSD(no);

            }
            else{
                return RDD(no);
            }
        }

        return no;
}

template <class T>
No<T>* AVL<T>::RSD(No<T>* no){

        No<T>* aux = no->getEsq();
        no->setEsq(aux->getDir());
        aux->setDir(no);
        no->setAlt(Maior(Altura(no->getEsq()), Altura(no->getDir()))+1);
        aux->setAlt(Maior(Altura(aux->getEsq()), no->getAlt())+1);
        return aux;
}

template <class T>
No<T>* AVL<T>::RSE(No<T>* no){

        No<T>* aux = no->getDir();
        no->setDir(aux->getEsq());
        aux->setEsq(no);
        no->setAlt(Maior(Altura(no->getEsq()), Altura(no->getDir()))+1);
        aux->setAlt(Maior(Altura(aux->getDir()), no->getAlt())+1);
        return aux;
}

template <class T>
No<T>* AVL<T>::RDE(No<T>* no){

        no->setDir(RSD(no->getDir()));
        return RSE(no);

}

template <class T>
No<T>* AVL<T>::RDD(No<T>* no){

        no->setEsq(RSE(no->getEsq()));
        return RSD(no);

}

template <class T>
void AVL<T>::ImprimePreOrdem(No<T>* Raiz){

    if (Raiz != NULL){

        Raiz->getChave().Imprime();
        ImprimePreOrdem(Raiz->getEsq());
        ImprimePreOrdem(Raiz->getDir());

    }
}

template <class T>
void AVL<T>::ImprimeOrdem(No<T>* Raiz){

    if (Raiz != NULL){

        ImprimeOrdem(Raiz->getEsq());
        Raiz->getChave().Imprime();
        ImprimeOrdem(Raiz->getDir());

    }
}

template <class T>
void AVL<T>::ImprimePosOrdem(No<T>* Raiz){

    if (Raiz != NULL){

        ImprimePosOrdem(Raiz->getEsq());
        ImprimePosOrdem(Raiz->getDir());
        Raiz->getChave().Imprime();

    }
}

template <class T>
No<T>* AVL<T>::Busca(No<T>* Raiz, T item){

    if (Raiz == NULL || Raiz->getChave().getKey() == item.getKey()){
       return Raiz;
    }

    if (Raiz->getChave().getKey() > item.getKey()){
       return Busca (Raiz->getEsq(), item);
    }
    else if (Raiz->getChave().getKey() < item.getKey()){
       return Busca (Raiz->getDir(), item);
    }
    else{
        return NULL;
    }

}
template <class T>
void AVL<T>::ImprimeNo(No<T>* no){

  if (no == NULL){
    cout <<"ITEM N ENCONTRADO";
  }
  else{
   no->getChave().Imprime();
  }
}

//----------------------------------------------------------------------------------------

template<typename TIPO>
class TabelaHash {
private:
    int TAM;
    AVL<TIPO> *thash;
public:
TabelaHash(int tam){
       this->TAM = MaiorPrimo(tam/4);
       thash = new AVL<TIPO>[TAM];
       cout <<"TAMANHO ATUAL DA TAB = "<<TAM;
    }
  void InsereHash(TIPO item);
  int FuncaoHash(string Chave);
  void ImprimeHash(int Pos);
  int Fatorar(long long int Base, int Expoente);
  AVL<TIPO>* getNo();
  int MaiorPrimo (int x);
  int getTAM();
};

template <typename TIPO>
int TabelaHash<TIPO>::getTAM(){
   return this->TAM;
}

template <typename TIPO>
int TabelaHash<TIPO>::MaiorPrimo (int x){

   int i,cont=0;
   int aux = x;
   for (i=1;i<=aux;i++){
         if (aux%i==0){
            cont++;
         }
 }
     if (cont==2){
        return aux;
      }
      else if(aux==1 || aux==0){
        return -1;
      }
      else {
         return MaiorPrimo(aux-1);
      }
}

template <typename TIPO>
AVL<TIPO>* TabelaHash<TIPO>::getNo(){
   return thash;
}

template <typename TIPO>
int TabelaHash<TIPO>::FuncaoHash(string Chave){
   unsigned long long int Soma = 0;
   int p;
   p = Chave.length();
   p--;
for (unsigned int i=0; i<Chave.length(); ++i){
    Soma = Soma+ (((unsigned char)Chave[i]) * Fatorar(1000000000+7,p));
    Soma = Soma%TAM;
    p--;
}
return Soma%TAM;
}

template <typename TIPO>
int TabelaHash<TIPO>::Fatorar(long long int Base, int Expoente){
  long long int Total = 1,i = 1;
   while (i<=Expoente){
    Total = Total * Base;
    Total = Total %TAM;
    i++;
   }
  return Total;
}

template <typename TIPO>
void TabelaHash<TIPO>::InsereHash(TIPO item){
    int aux;
    string Chave;

    Chave = item.getNome();
    aux = FuncaoHash(Chave);
    thash[aux].Insere(item);
}

template <typename TIPO>
void TabelaHash<TIPO>::ImprimeHash(int Pos){

  thash[Pos].ImprimePreOrdem(thash[Pos].getRaiz());
}
//-------------------------------------------------------------------------------------------------

class VarKinojo {
private:
    string key;
    TabelaHash<Chave> *tab;
public:
    VarKinojo(string key,int tamanho){
        this->key=key;
        this->tab= new TabelaHash<Chave>(tamanho) ;
    }
    string getKey();
    void setKey(string chave);

};

string VarKinojo::getKey(){
   return this->key;
}
void VarKinojo::setKey(string chave) {
        this->key = chave;
    }

//----------------------------------------------------------------------------------------

class Alfabeto {
private:
    TabelaHash<VarKinojo> tab;
public:

};

int main(){


}
