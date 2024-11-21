#ifndef ELEMENTO_H
#define ELEMENTO_H
#include <iostream>
#include <vector>
#include <string>

// Classe Elemento com definição de Átomo e funcionalidade de cadastro
class Elemento {
public:
    // Definição da struct Atomo
    struct Atomo {
        double raio;      // Raio atômico em picômetros
        int valencia;     // Número de elétrons na camada de valência
        std::string nome; // Nome do elemento químico

        // Construtor para inicializar a struct
        Atomo(double r, int v, std::string n) : raio(r), valencia(v), nome(n) {}
    };

private:
    // Vetor para armazenar os átomos cadastrados
    std::vector<Atomo> tabela;

public:
    // Construtor padrão
    Elemento() = default;

    // Método para cadastrar um novo átomo
    void cadastrarAtomo();

    // Método para listar todos os átomos cadastrados
    void listarAtomos() const;

    double selecionarElementoPorNome(const std::string &nome) const;
    double retornarValencia(const std::string &nome) const;
};

#endif // ELEMENTO_H
