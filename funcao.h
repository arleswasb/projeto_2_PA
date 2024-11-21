#ifndef FUNCAO_H
#define FUNCAO_H
#include "sculptor.h"

// Função para calcular o centro da esfera no círculo no plano xy
void calcularCentroEsfera(double raioCirculo, double raioEsfera, double teta, const std::string& plano,double &cx, double &cy, double &cz, double &x, double &y, double &z) {
    // Coordenadas do centro do círculo

    // Calcular o centro com base no plano
    if (plano == "xy") {
        x = cx + raioCirculo * cos(teta);  // Coordenada x no círculo
        y = cy + raioCirculo * sin(teta);  // Coordenada y no círculo
        z = cz;              // Esfera acima do plano xy
        // z = cz - raioEsfera;           // Esfera abaixo do plano xy (descomente se necessário)
    }
    else if (plano == "xz") {
        x = cx + raioCirculo * cos(teta);  // Coordenada x no círculo
        z = cz + raioCirculo * sin(teta);  // Coordenada z no círculo
        y = cy;              // Esfera acima do plano xz
        // y = cy - raioEsfera;           // Esfera abaixo do plano xz (descomente se necessário)
    }
    else if (plano == "yz") {
        y = cy + raioCirculo * cos(teta);  // Coordenada y no círculo
        z = cz + raioCirculo * sin(teta);  // Coordenada z no círculo
        x = cx;              // Esfera acima do plano yz
        // x = cx - raioEsfera;           // Esfera abaixo do plano yz (descomente se necessário)
    }
    else {
        std::cerr << "Plano inválido! Use 'xy', 'xz' ou 'yz'." << std::endl;
    }
}

// Função para criar os raios orbitais
void CriarRaiosOrbitas(Sculptor &s,const double &cx,const double &cy,const double &cz,double &valencia) {
    // Realiza cortes em caixas para esculpir a forma de aneis

    int px=2,py=0,pz=0;//espessura da borda positiva de x,y,z
    int nx=1,ny=0,nz=0;//espessura da borda negativa de x,y,z

    if (valencia >= 2){
            py=2;
            ny=1;
        if (valencia >= 3){
                pz=2;
                nz=1;
            }
    }

    //quadrante 1 superior

    s.cutBox(0, cx-nx, 0, cy-ny, 0, cz-nz);
    s.cutBox(0, cx-nx, cy+py, 2*cy, 0, cz-nz);

    //quadrante 1 inferior

    s.cutBox(cx+px, 2*cx, cy+py, 2*cy, cz+pz, 2*cz);
    s.cutBox(cx+px, 2*cx, 0,cy, cz+pz, 2*cz);

    //quadrante 2 superior

    s.cutBox(0, cx-nx, 0, cy-ny, 0, cz-nz);
    s.cutBox(0, cx-nx, 0,cy-ny, cz+pz,2*cz);

    //quadrante 2 inferior

    s.cutBox(cx+px, 2*cx, cy+py, 2*cy, cz+pz, 2*cz);
    s.cutBox(cx+px, 2*cx, cy+py,2*cy, 0,cz-nz);

    //quadrante 3 superior

    s.cutBox(0, cx-nx, 0, cy-ny, 0, cz-nz);
    s.cutBox(cx+px, 2*cx, 0,cy-ny, 0, cz-nz);

    //quadrante 3 inferior

    s.cutBox(cx+px, 2*cx, cy+py, 2*cy, cz+pz, 2*cz);
    s.cutBox(0, cx, cy+py, 2*cy, cz+pz, 2*cz);
}



#endif // FUNCAO_H
