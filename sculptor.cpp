#include "sculptor.h"
#include "sculptor.h"
#include<iostream>
#include <fstream>
#include <vector>

Sculptor::Sculptor(int _nx, int _ny, int _nz) {
    if (_nx <= 0 || _ny <= 0 || _nz <= 0) {
        std::cerr << "Erro: dimensões inválidas para Sculptor!" << std::endl;
        exit(1);
    }

    nx = _nx;//planos
    ny = _ny;//linha
    nz = _nz;//coluna

    // alocação da memoria para matriz 3d em um unico bloco
    v = new Voxel**[nx];
    for (int i = 0; i < nx; i++) {
        v[i] = new Voxel*[ny];
        for (int j = 0; j < ny; j++) {
            v[i][j] = new Voxel[nz];
            for (int k = 0; k < nz; k++) {
                // Inicializando todos os voxel em "off" e com valores setados em zero
                v[i][j][k].show = false;
                v[i][j][k].r = v[i][j][k].g = v[i][j][k].b = 0.0f;
                v[i][j][k].a = 0.0f;
            }
        }
    }
}


Sculptor::~Sculptor()
{
    std::cout << "Programa encerrado\n";
    delete[] v[0][0]; // Libera os voxels (planos)
    delete[] v[0];    // Libera as colunas (segundo nível)
    delete[] v;       // Libera as linhas (primeiro nível)
}

void Sculptor::Imprime_Planos() {
    // Itera sobre todos os planos
    for (int i = 0; i < nx; i++) {
        std::cout << "Plano " << i << ":\n";
        // Itera sobre as linhas (ny)
        for (int j = 0; j < ny; j++) {
            // Itera sobre as colunas (nz)
            for (int k = 0; k < nz; k++) {
                // Verifica se o voxel está ativo
                if (v[i][j][k].show) {
                    std::cout << "1 "; // Voxel ativo
                } else {
                    std::cout << "0 "; // Voxel inativo
                }
            }
            std::cout << "\n"; // Nova linha para cada linha da matriz
        }
    }
}

void Sculptor::putVoxel(int x, int y, int z) {
    // Verifica se as coordenadas estão dentro dos limites da matriz
    if (x >= 0 && x < nx && y >= 0 && y < ny && z >= 0 && z < nz) {
        v[x][y][z].show = true;  // Marca o voxel como "ativo"
    } else {
        std::cerr << "Erro: coordenadas fora dos limites da matriz!" << std::endl;
    }
}

void Sculptor::cutVoxel(int x, int y, int z) {
    // Verifica se as coordenadas estão dentro dos limites da matriz
    if (x >= 0 && x < nx && y >= 0 && y < ny && z >= 0 && z < nz) {
        v[x][y][z].show = false;  // Marca o voxel como inativo
    } else {
        std::cerr << "Erro: coordenadas fora dos limites da matriz!" << std::endl;
    }
}

void Sculptor::setColor(float r, float g, float b, float alpha) {
    // Define a cor atual de desenho
    this->r = r;        // Componente de cor vermelha (0.0 a 1.0/0 a 255)
    this->g = g;        // Componente de cor verde (0.0 a 1.0/0 a 255)
    this->b = b;        // Componente de cor azul (0.0 a 1.0/0 a 255)
    this->a = alpha;    // Componente de opacidade (0.0 a 1.0/0 a 255)
}

void Sculptor::putBox(int x0, int x1, int y0, int y1, int z0, int z1) {
    // Garantir que os limites fornecidos estejam dentro das dimensões da matriz
    // std::max(x, y) retorna o maior valor entre x e y
    // std::min(x, y) retorna o menor valor entre x e y
    x0 = std::max(0, x0);       // Garante que x0 não seja menor que 0
    x1 = std::min(nx - 1, x1);  // Garante que x1 não ultrapasse nx-1
    y0 = std::max(0, y0);       // Garante que y0 não seja menor que 0
    y1 = std::min(ny - 1, y1);  // Garante que y1 não ultrapasse ny-1
    z0 = std::max(0, z0);       // Garante que z0 não seja menor que 0
    z1 = std::min(nz - 1, z1);  // Garante que z1 não ultrapasse nz-1

    // Percorrer todos os índices no intervalo ajustado
    for (int x = x0; x <= x1; ++x) { // Para cada coordenada x no intervalo [x0, x1]
        for (int y = y0; y <= y1; ++y) { // Para cada coordenada y no intervalo [y0, y1]
            for (int z = z0; z <= z1; ++z) { // Para cada coordenada z no intervalo [z0, z1]
                // Referência ao voxel atual para evitar múltiplos acessos à matriz
                Voxel &voxel = v[x][y][z];

                // Ativar o voxel: marca que ele está "ligado"
                voxel.show = true;

                // Define a cor do voxel usando os valores atuais de cor da classe
                voxel.r = r;  // Cor vermelha
                voxel.g = g;  // Cor verde
                voxel.b = b;  // Cor azul

                // Define a transparência do voxel usando o valor atual de alfa
                voxel.a = a;  // Transparência (opacidade)
            }
        }
    }
}


void Sculptor::cutBox(int x0, int x1, int y0, int y1, int z0, int z1) {
    // Garantir que os limites fornecidos estejam dentro das dimensões da matriz
    // std::max(x, y) retorna o maior valor entre x e y
    // std::min(x, y) retorna o menor valor entre x e y
    x0 = std::max(0, x0);       // Garante que x0 não seja menor que 0
    x1 = std::min(nx - 1, x1);  // Garante que x1 não ultrapasse nx-1
    y0 = std::max(0, y0);       // Garante que y0 não seja menor que 0
    y1 = std::min(ny - 1, y1);  // Garante que y1 não ultrapasse ny-1
    z0 = std::max(0, z0);       // Garante que z0 não seja menor que 0
    z1 = std::min(nz - 1, z1);  // Garante que z1 não ultrapasse nz-1

    // Percorrer todos os índices no intervalo ajustado
    for (int x = x0; x <= x1; ++x) { // Para cada coordenada x no intervalo [x0, x1]
        for (int y = y0; y <= y1; ++y) { // Para cada coordenada y no intervalo [y0, y1]
            for (int z = z0; z <= z1; ++z) { // Para cada coordenada z no intervalo [z0, z1]
                // Referência ao voxel atual para evitar múltiplos acessos à matriz
                Voxel &voxel = v[x][y][z];

                // Ativar o voxel: marca que ele está "ligado"
                voxel.show = false;

                // Define a cor do voxel usando os valores atuais de cor da classe
                voxel.r = r;  // Cor vermelha
                voxel.g = g;  // Cor verde
                voxel.b = b;  // Cor azul

                // Define a transparência do voxel usando o valor atual de alfa
                voxel.a = a;  // Transparência (opacidade)
            }
        }
    }
}


void Sculptor::putSphere(int xcenter, int ycenter, int zcenter, int radius) {
    // Verifica se o raio é válido
    if (radius <= 0) {
        std::cerr << "Erro: O raio negativo!" << std::endl;
        return;
    }
    for (int x = 0; x < nx; x++) {
        for (int y = 0; y < ny; y++) {
            for (int z = 0; z < nz; z++) {
                // Verifica a equação da esfera
                if ((x - xcenter) * (x - xcenter) +
                        (y - ycenter) * (y - ycenter) +
                        (z - zcenter) * (z - zcenter) <= radius * radius) {
                    // Ativa o voxel
                    v[x][y][z].show = true;

                    // Define a cor do voxel
                    v[x][y][z].r = r;
                    v[x][y][z].g = g;
                    v[x][y][z].b = b;
                    v[x][y][z].a = a;
                }
            }
        }
    }
}

void Sculptor::cutSphere(int xcenter, int ycenter, int zcenter, int radius) {
    // Verifica se o raio é válido
    if (radius <= 0) {
        std::cerr << "Erro: O raio negativo!" << std::endl;
        return;
    }
    for (int x = 0; x < nx; x++) {
        for (int y = 0; y < ny; y++) {
            for (int z = 0; z < nz; z++) {
                // Verifica a equação da esfera
                if ((x - xcenter) * (x - xcenter) +
                        (y - ycenter) * (y - ycenter) +
                        (z - zcenter) * (z - zcenter) <= radius * radius) {
                    // Ativa o voxel
                    v[x][y][z].show = false;

                    // Define a cor do voxel
                    v[x][y][z].r = r;
                    v[x][y][z].g = g;
                    v[x][y][z].b = b;
                    v[x][y][z].a = a;
                }
            }
        }
    }
}


void Sculptor::putEllipsoid(int xcenter, int ycenter, int zcenter, int rx, int ry, int rz) {
    // Verifica se os raios são válidos
    if (rx <= 0 || ry <= 0 || rz <= 0) {
        std::cerr << "Erro: Um dos raios está negativo!" << std::endl;
        return;
    }

    // Percorre todos os voxels dentro dos limites da matriz
    for (int x = 0; x < nx; x++) {
        for (int y = 0; y < ny; y++) {
            for (int z = 0; z < nz; z++) {
                // Calcula a equação normalizada do elipsóide
                float eq = ((float)(x - xcenter) * (x - xcenter)) / (rx * rx) +
                           ((float)(y - ycenter) * (y - ycenter)) / (ry * ry) +
                           ((float)(z - zcenter) * (z - zcenter)) / (rz * rz);

                // Se a equação for menor ou igual a 1, o voxel pertence ao elipsóide
                if (eq <= 1.0f) {
                    v[x][y][z].show = true; // Ativa o voxel

                    // Define a cor e a transparência do voxel
                    v[x][y][z].r = r;
                    v[x][y][z].g = g;
                    v[x][y][z].b = b;
                    v[x][y][z].a = a;
                }
            }
        }
    }
}

void Sculptor::cutEllipsoid(int xcenter, int ycenter, int zcenter, int rx, int ry, int rz) {
    // Verifica se os raios são válidos
    if (rx <= 0 || ry <= 0 || rz <= 0) {
        std::cerr << "Erro: Um dos raios está negativo!" << std::endl;
        return;
    }

    // Percorre todos os voxels dentro dos limites da matriz
    for (int x = 0; x < nx; x++) {
        for (int y = 0; y < ny; y++) {
            for (int z = 0; z < nz; z++) {
                // Calcula a equação normalizada do elipsóide
                float eq = ((float)(x - xcenter) * (x - xcenter)) / (rx * rx) +
                           ((float)(y - ycenter) * (y - ycenter)) / (ry * ry) +
                           ((float)(z - zcenter) * (z - zcenter)) / (rz * rz);

                // Se a equação for menor ou igual a 1, o voxel pertence ao elipsóide
                if (eq <= 1.0f) {
                    v[x][y][z].show = false; // Ativa o voxel

                    // Define a cor e a transparência do voxel
                    v[x][y][z].r = r;
                    v[x][y][z].g = g;
                    v[x][y][z].b = b;
                    v[x][y][z].a = a;
                }
            }
        }
    }
}


void Sculptor::writeOFF(const std::string &nomeArquivo) {
    std::ofstream fout;
    fout.open(nomeArquivo);

     if (!fout.is_open()) {
        std::cerr << "Erro ao abrir o arquivo!" << std::endl;
        return;
    }

    // Contagem dos voxels ativos
    int nVoxels = 0;
    for (int x = 0; x < nx; x++) {
        for (int y = 0; y < ny; y++) {
            for (int z = 0; z < nz; z++) {
                if (v[x][y][z].show) {
                    nVoxels++;
                }
            }
        }
    }

    if (nVoxels == 0) {
        std::cerr << "Nenhum voxel ativo para salvar." << std::endl;
        fout.close();
        return;
    }

    // Escreve o cabeçalho OFF
    fout << "OFF\n";
    fout << nVoxels * 8 << " " << nVoxels * 6 << " 0\n";

    // Lista de vértices
    int voxelIndex = 0; // Índice único para cada voxel ativo
    for (int x = 0; x < nx; x++) {
        for (int y = 0; y < ny; y++) {
            for (int z = 0; z < nz; z++) {
                if (v[x][y][z].show) {
                    fout << x - 0.5 << " " << y - 0.5 << " " << z - 0.5 << "\n"; // Vértice 0
                    fout << x - 0.5 << " " << y - 0.5 << " " << z + 0.5 << "\n"; // Vértice 1
                    fout << x - 0.5 << " " << y + 0.5 << " " << z - 0.5 << "\n"; // Vértice 2
                    fout << x - 0.5 << " " << y + 0.5 << " " << z + 0.5 << "\n"; // Vértice 3
                    fout << x + 0.5 << " " << y - 0.5 << " " << z - 0.5 << "\n"; // Vértice 4
                    fout << x + 0.5 << " " << y - 0.5 << " " << z + 0.5 << "\n"; // Vértice 5
                    fout << x + 0.5 << " " << y + 0.5 << " " << z - 0.5 << "\n"; // Vértice 6
                    fout << x + 0.5 << " " << y + 0.5 << " " << z + 0.5 << "\n"; // Vértice 7
                }
            }
        }
    }

    // Define as faces para cada voxel ativo
    voxelIndex = 0;
    for (int x = 0; x < nx; x++) {
        for (int y = 0; y < ny; y++) {
            for (int z = 0; z < nz; z++) {
                if (v[x][y][z].show) {
                    int base = voxelIndex * 8;
                    fout << "4 " << base + 0 << " " << base + 1 << " " << base + 3 << " " << base + 2 << " " << v[x][y][z].r << " " << v[x][y][z].g << " " << v[x][y][z].b << " " << v[x][y][z].a << "\n" ; // Face -xy
                    fout << "4 " << base + 4 << " " << base + 5 << " " << base + 7 << " " << base + 6 << " " << v[x][y][z].r << " " << v[x][y][z].g << " " << v[x][y][z].b << " " << v[x][y][z].a << "\n"; // Face +xy
                    fout << "4 " << base + 0 << " " << base + 1 << " " << base + 5 << " " << base + 4 << " " << v[x][y][z].r << " " << v[x][y][z].g << " " << v[x][y][z].b << " " << v[x][y][z].a << "\n"; // Face -xz
                    fout << "4 " << base + 2 << " " << base + 3 << " " << base + 7 << " " << base + 6 << " " << v[x][y][z].r << " " << v[x][y][z].g << " " << v[x][y][z].b << " " << v[x][y][z].a << "\n"; // Face +xz
                    fout << "4 " << base + 0 << " " << base + 2 << " " << base + 6 << " " << base + 4 << " " << v[x][y][z].r << " " << v[x][y][z].g << " " << v[x][y][z].b << " " << v[x][y][z].a << "\n"; // Face -yz
                    fout << "4 " << base + 1 << " " << base + 3 << " " << base + 7 << " " << base + 5 << " " << v[x][y][z].r << " " << v[x][y][z].g << " " << v[x][y][z].b << " " << v[x][y][z].a << "\n"; // Face +yz
                    voxelIndex++;
                }
            }
        }
    }

    fout.close();
    std::cout << "Arquivo " << nomeArquivo << " gravado com sucesso no formato OFF.\n";
}



