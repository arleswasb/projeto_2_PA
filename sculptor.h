#ifndef SCULPTOR_H
#define SCULPTOR_H
#include <string>

class Sculptor
{
public:
    struct Voxel
    {
        float r,g,b; // Cores
        float a; // Transparencia
        bool show; // Mostrado ou nao
    };

private:
    Voxel ***v; // matriz 3D
    int nx, ny, nz; // Dimensões
    float r, g, b, a; // Current drawing color
public:
    // Construtor da classe
    Sculptor(int _nx, int _ny, int _nz);
    // Destrutor da classe
    ~Sculptor();
    //metodos da classe Esculptor

    void putVoxel(int x, int y, int z);//Ativa o voxel na posição (x,y,z) (fazendo show = true) e atribui ao mesmo a cor atual de desenho
    void setColor(float r, float g, float b, float alpha); //Define a cor atual de desenho.
    void cutVoxel(int x, int y, int z);//Desativa o voxel na posição (x,y,z) (fazendo show = false)
    void putBox(int x0, int x1, int y0, int y1, int z0, int z1);//Ativa todos os voxels no intervalo x∈[x0,x1],y∈[y0,y1], z∈[z0,z1] e atribui aos mesmos a cor atual de desenho
    void cutBox(int x0, int x1, int y0, int y1, int z0, int z1);//Desativa todos os voxels no intervalo x∈[x0,x1], y∈[y0,y1], z∈[z0,z1]
    void putSphere(int xcenter, int ycenter, int zcenter, int radius);//Ativa todos os voxels que satisfazem à equação da esfera e atribui aos mesmos a cor atual de desenho (r,g,b,a)
    void cutSphere(int xcenter, int ycenter, int zcenter, int radius);//Desativa todos os voxels que satisfazem à equação da esfera
    void putEllipsoid(int xcenter, int ycenter, int zcenter, int rx, int ry, int rz);//Ativa todos os voxels que satisfazem à equação do elipsóide e atribui aos mesmos a cor atual de desenho
    void cutEllipsoid(int xcenter, int ycenter, int zcenter, int rx, int ry, int rz);//Desativa todos os voxels que satisfazem à equação do elipsóide
    void writeOFF(const std::string &nomeArquivo);//grava a escultura no formato OFF no arquivo filename
};

#endif // SCULPTOR_H
