#include <iostream>
#include "sculptor.h"
#include "elemento.h"
#include "funcao.h"





int main() {



    double xx, yx, zx;//plano xy
    double xy, yy, zy;//plano xz
    double xz, yz, zz;//plano yz
    double sx, sy, sz;//coordenadas do construtor sculptor

    Elemento elementos;
    std::string nome; // Nome do elemento químico

    // Cadastrar alguns elementos
    elementos.cadastrarAtomo();


    // Listar os elementos cadastrados
    elementos.listarAtomos();

    std::cout << "Digite o nome do elemento: ";
    std::getline(std::cin, nome);


    // Chama o método para procurar o elemento e retornar o raio
    double raio = elementos.selecionarElementoPorNome(nome);
    if (raio ==-1){
        return 1;
    }
    // Chama o método para procurar a valencia do elemento e retorna-la
    double valencia = elementos.retornarValencia(nome);

    // Se o raio retornado for válido (diferente de -1), exibe o raio
    if (raio != -1) {// define o tamanho da matriz usando como base o reio do elemento
        sx = raio + 300;
        sy = raio + 300;
        sz = raio + 300;
    }

    double raioCirculo = raio + 30 ;        // Raio dos aneis orbitais de valencoia com base no raio do atomo
    double raioEsfera = raio;               // Raio da nucleo do atomo conforme o raio do atomo
    double teta = 45.0*(M_PI/180);          // Ângulo em radianos (posição inicial no anel de valencia)
    double teta1 = 135.0*(M_PI/180);        // Ângulo com defasagem em radianos (posição inicial no anel de valencia)
    double teta2 = 225.0*(M_PI/180);         // Ângulo com defasagem em radianos (posição inicial no anel de valencia)

    // Cria uma matriz 3D de tamanho variavel conforme o raio do atomo
    Sculptor s(sx, sy, sz);

    //cento do nucleo do atomo

    double cx,cy,cz;
    cx = sx/2;
    cy = sy/2;
    cz = sz/2;


    // Define a cor dos arcos orbitais
    s.setColor(254,254, 254, 1.0);
    //cria a casca esferica do atomo
    s.putSphere(cx, cy, cz, raioCirculo); // Desenha uma esfera de no centro da matriz
    s.cutSphere(cx, cy, cz, raioCirculo - 2); // Recorta uma esfera menor centrada na origem para diminuir a densidade do nucleo

    //cria os aneis orbitais conforme o numero de valencia
    CriarRaiosOrbitas(s,cx,cy,cz,valencia);//Corta a esfera anteior formando os aneis orbitais nos planos x,y,z

    //cria uma casca oca o atomo central com raio proporcional
    s.setColor(255, 201, 0, 1.0);//define a cor do nucleo do atomo
    int Re = raio/1;//tornar o reio inteiro
    s.putSphere(cx, cy, cz, Re); // Desenha uma esfera com o raio do elemento centrada na origem
    s.cutSphere(cx, cy, cz, Re-2); // corta uma esfera com o raio do elemento centrada na origem

    //O codigo abaixo cria as esfeeras que representao os eletrons e posiciona no arco orbital conforme o plano e de acordo com a camada de valencia
    if (valencia >=1){
        std::string plano = "yz";
        calcularCentroEsfera(raioCirculo, raioEsfera, teta, plano, cx, cy, cz, xx, yx, zx);

        s.setColor(20, 255, 0, 1.0);
        s.putSphere(xx, yx, zx, 10); // Desenha uma esfera de raio 5 que pertence ao circulo

        if (valencia >=4){
            std::string plano = "yz";
            double teta4 = 225.0*(M_PI/180);
            calcularCentroEsfera(raioCirculo, raioEsfera, teta4, plano, cx, cy, cz, xx, yx, zx);

            s.setColor(45, 230, 30, 1.0);
            s.putSphere(xx, yx, zx, 10); // Desenha uma esfera de raio 5 que pertence ao circulo
        }

        if (valencia >=2){
            std::string plano1 = "xz";
            calcularCentroEsfera(raioCirculo, raioEsfera, teta1, plano1, cx, cy, cz, xy, yy, zy);


            s.setColor(30, 155, 205, 1.0);
            s.putSphere(xy, yy, zy, 10); // Desenha uma esfera de raio 5 que pertence ao circulo

            if (valencia >=5){
                double teta5 = 315.0*(M_PI/180);
                calcularCentroEsfera(raioCirculo, raioEsfera, teta5, plano1, cx, cy, cz, xy, yy, zy);

                s.setColor(200, 25, 30, 1.0);
                s.putSphere(xy, yy, zy, 10); // Desenha uma esfera de raio 5 que pertence ao circulo
            }
            if (valencia >=3){
                std::string plano2 = "xy";
                calcularCentroEsfera(raioCirculo, raioEsfera, teta2, plano2, cx, cy, cz, xz, yz, zz);

                s.setColor(255, 0, 230, 1.0);
                s.putSphere(xz, yz, zz, 10); // Desenha uma esfera de raio 10 que pertence ao circulo

                if (valencia >=6){
                    double teta6 = 60.0*(M_PI/180);
                    calcularCentroEsfera(raioCirculo, raioEsfera, teta6, plano2, cx, cy, cz, xz, yz, zz);

                    s.setColor(55, 155, 20, 1.0);
                    s.putSphere(xz, yz, zz, 10); // Desenha uma esfera de raio 5 que pertence ao circulo

                    if (valencia >=7){
                        double teta6 = 135.0*(M_PI/180);
                        calcularCentroEsfera(raioCirculo, raioEsfera, teta6, plano2, cx, cy, cz, xz, yz, zz);

                        s.setColor(15, 137, 150, 1.0);
                        s.putSphere(xz, yz, zz, 10); // Desenha uma esfera de raio 5 que pertence ao circulo
                    }
                }
            }
        }

    }

    s.writeOFF(nome + ".off");//gera o arquivo .OFF

    return 0;
}

