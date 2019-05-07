//
// Created by DarkWayC0de_pc on 17/11/2018.
//

#include <fstream>
#include <iostream>
#include <iterator>
#include "DFA.h"
namespace CyA{
    DFA::DFA() {

    }
    DFA::~DFA() {

    }
    void DFA::cargar(char *nombrefichero) {
        if(!DFA_.empty()){
            DFA_.clear();
            nestados_=0;
            arranque_=0;
        }
        build(nombrefichero);  //rev
    }
    void DFA::build(char *nombrefichero){
        std::ifstream archivo;
        archivo.open(nombrefichero);
        if(!archivo.fail()){
          std::cout<<"Apertura de archivo correcta";
           archivo>>nestados_;
           archivo>>arranque_;
           for (int i = 0; i < nestados_; ++i) {
              Estado aux;
              archivo>>aux.estado_>>aux.aceptacion_>>aux.transiciones_;
              for (int j = 0; j <aux.transiciones_; ++j) {
                  std::pair<char, unsigned> auxp;
                  archivo>>auxp.first>>auxp.second;
                  aux.transicion_.push_back(auxp);
              }
              DFA_.insert(aux);
           }
           analizar(archivo);

           archivo.close();
        }else{
            std::cout<<"Error en la apertura del archivo apertura";
        }
    }
    void DFA::analizar(std::ifstream &a) {
        bool erro=false;
        for (std::set<Estado>::iterator i= DFA_.begin();i!=DFA_.end();i++) {
            for (int j = 0; j <i->transiciones_ ; ++j) {
                for (int k = 0; k <i->transiciones_ ; ++k) {
                    if(j!=k&&(i->transicion_[j].first==i->transicion_[k].first)){
                        if(i->transicion_[j].second!=i->transicion_[k].second) {
                            erro = true;
                        }
                    }
                }
            }
        }
        if(nestados_!=DFA_.size()){
            erro=true;
        }
        if(erro){
            std::cout << "\nError definicion de automata";

            DFA_.clear();
        } else{
            std::cout <<"\nCarga correcta";
        }
    }
    bool DFA::vasio() {
        return DFA_.empty();
    }
    std::ostream& DFA::write(std::ostream &os) {
        os<<"DFA\n"
            <<nestados_<<"\n"
            <<arranque_<<"\n";
        for(std::set<Estado>::iterator i=DFA_.begin();i!=DFA_.end();i++){
            os<<i->estado_<<" "<<i->aceptacion_<<" "<<i->transiciones_<<" ";
            for (int j = 0; j <i->transiciones_ ; ++j) {
                os<<i->transicion_[j].first<<" "<<i->transicion_[j].second<<" ";
            }
            os<<"\n";
        }


    }
    void DFA::muerte() {
        int muerto;
        bool vivo=true;
        std::cout<<"Estados de muerte: ";
        for(std::set<Estado>::iterator i=DFA_.begin();i!=DFA_.end();i++){
            muerto=0;
            for (int j = 0; j <i->transiciones_ ; ++j) {
                if(i->transicion_[j].second==i->estado_){
                    muerto++;
                }
            }
            if(muerto==(i->transiciones_)){
                vivo=false;
                std::cout<<"\nEl estado "<<i->estado_<<" es un estado de muerte porque todas sun transiciones apuntan a si mismo como vemos aqui: ";
                for (int j = 0; j <i->transiciones_ ; ++j) {
                    std::cout<<i->transicion_[j].first<<" "<<i->transicion_[j].second<<" ";
                }
                std::cout<<"";
            }
        }
        if(vivo){
            std::cout<<"\nEste DFA no tiene estados de muerte";
        }
    }
    void DFA::cadena() {
        char cadena[100];
        bool aceptado=true;
        unsigned a;
        std::cout<<"Introduce la cadena a Analizar: ";
        std::cin>>cadena;
        a=siguiente(arranque_,cadena[0],aceptado);
        std::cout<<"Cadena de entrada:"<<cadena
            <<"\nEstado actual\tEntrada\t\tSiguiente estado\n"
            <<arranque_<<"\t\t"<<cadena[0]<<"\t\t"<<a<<"\n";

        for (int i = 1; cadena[i]!='\0'&&aceptado; ++i) {
            std::cout<<a<<"\t\t"<<cadena[i]<<"\t\t"<<siguiente(a,cadena[i], aceptado)<<"\n";
            a=siguiente(a,cadena[i], aceptado);
        }

        if (aceptado&&aceptacion(a)){
            std::cout<<"Cadena de entrada ACEPTADA";
        } else{
            std::cout<<"Cadena de entrada No ACEPTADA";
        }
    }
    unsigned DFA::siguiente(unsigned origen, char entrada, bool &aceptado) {
        for(std::set<Estado>::iterator i=DFA_.begin();i!=DFA_.end();i++){
            if(i->estado_==origen){
                for (int j = 0; j <i->transiciones_ ; ++j) {
                    if(i->transicion_[j].first==entrada){
                        return i->transicion_[j].second;
                    }
                }
            }
        }
        aceptado=false;
        return origen;
    }
    bool DFA::aceptacion(unsigned a) {
        for(std::set<Estado>::iterator i=DFA_.begin();i!=DFA_.end();i++){
            if(i->estado_==a){
                return i->aceptacion_;
            }
        }
        return false;
    }
}

