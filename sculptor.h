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
    void putVoxel(int x, int y, int z);
    void setColor(float r, float g, float b, float alpha);
    void Imprime_Planos();
    void cutVoxel(int x, int y, int z);
    void putBox(int x0, int x1, int y0, int y1, int z0, int z1);
    void cutBox(int x0, int x1, int y0, int y1, int z0, int z1);
    void putSphere(int xcenter, int ycenter, int zcenter, int radius);
    void cutSphere(int xcenter, int ycenter, int zcenter, int radius);
    void putEllipsoid(int xcenter, int ycenter, int zcenter, int rx, int ry, int rz);
    void cutEllipsoid(int xcenter, int ycenter, int zcenter, int rx, int ry, int rz);
    void writeOFF(const std::string &nomeArquivo);
};

#endif // SCULPTOR_H
