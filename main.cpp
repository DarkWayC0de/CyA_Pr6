#include <iostream>
#include "DFA.h"


int main() {
	//system("clear");
    std::cout<<"Practica 6 de Computabilidad y Algoritmia";
    char opcion;
    CyA::DFA A;
    do{
        std::cout<< "\nc .-Cargar DFA"
                    "\nm .-Mostras DFA"
                    "\ni .-Identificar estados de muerte"
                    "\na .-Analizar cadena"
                    "\nq .-Finalizar programa"
                    "\nIntroduce la letra de la acion a ejecutar:";
        std::cin>>opcion;
      //  system("clear");
        switch (opcion){
            case 'c':
                char nombrefichero[50];

                std::cout<<"Introduzca el nombre del fichero:";
                std::cin>>nombrefichero;
                A.cargar(nombrefichero);
                break;
            case 'm':
                if(!A.vasio()) {
                    A.write(std::cout);
                }else{
                    std::cout<<"Tines que cargar primero el DFA";
                }
                break;
            case 'i':
                if(!A.vasio()) {
                    A.muerte();
                }else{
                    std::cout<<"Tines que cargar primero el DFA";
                }
                break;
            case 'a':
                if(!A.vasio()) {
                    A.cadena();
                }else{
                    std::cout<<"Tines que cargar primero el DFA";
                }
                break;
            case 'q':
                break;

            default:
                std::cout<<"\nEsa opcion no te la he ofrecido. Por favor introduce una opcion del listado";
        }

    }while(opcion!='q');






    return 0;
}
