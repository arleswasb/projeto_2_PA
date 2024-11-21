#include "elemento.h"



void Elemento::cadastrarAtomo() {
    tabela.emplace_back(298.0, 1, "Cesio"); // Adiciona o átomo ao vetor
    tabela.emplace_back(243.0, 1, "Potassio"); // Adiciona o átomo ao vetor
    tabela.emplace_back(145.0, 2, "Magnesio"); // Adiciona o átomo ao vetor
    tabela.emplace_back(31.0, 2, "Helio"); // Adiciona o átomo ao vetor
    tabela.emplace_back(112.0, 2, "Berilio"); // Adiciona o átomo ao vetor
    tabela.emplace_back(87.0, 3, "Boro"); // Adiciona o átomo ao vetor
    tabela.emplace_back(136.0, 3, "Galio"); // Adiciona o átomo ao vetor
    tabela.emplace_back(118.0, 3, "Aluminio"); // Adiciona o átomo ao vetor
    tabela.emplace_back(111.0, 4, "Silicio"); // Adiciona o átomo ao vetor
    tabela.emplace_back(154.0, 4, "Chumbo"); // Adiciona o átomo ao vetor
    tabela.emplace_back(98.0, 5, "Fosforo"); // Adiciona o átomo ao vetor
    tabela.emplace_back(133.0, 5, "Antimonio"); // Adiciona o átomo ao vetor
    tabela.emplace_back(48.0, 6, "Oxigenio"); // Adiciona o átomo ao vetor
    tabela.emplace_back(135.0, 6, "Polonio"); // Adiciona o átomo ao vetor
    tabela.emplace_back(42.0, 7, "Fluor"); // Adiciona o átomo ao vetor
    tabela.emplace_back(79.0, 7, "Cloro"); // Adiciona o átomo ao vetor

}

void Elemento::listarAtomos() const {
    if (tabela.empty()) {
        std::cout << "Nenhum elemento foi cadastrado." << std::endl;
        return;
    }

    for (const auto& atomo : tabela) {
        std::cout << "elemento: " << atomo.nome << "-> " << "raio Atomico: " << atomo.raio << " pm" << "-> " << "Valencia: " << atomo.valencia << std::endl;
        std::cout << "-----------------------------" << std::endl;
    }
}
double Elemento::selecionarElementoPorNome(const std::string &nome) const {
    // Percorre o vetor de elementos
    for (const auto &atomo : tabela) {
        // Verifica se o nome do átomo corresponde ao nome fornecido
        if (atomo.nome == nome) {
            return atomo.raio; // Retorna o raio atômico
        }
    }

    // Se não encontrar o elemento, retorna -1 (ou outro valor indicativo de erro)
    std::cout << "Elemento com o nome nao encontrado." << std::endl;
    return -1; // Indica que o elemento não foi encontrado
}

double Elemento::retornarValencia(const std::string &nome) const {
    // Percorre o vetor de elementos
    for (const auto &atomo : tabela) {
        // Verifica se o nome do átomo corresponde ao nome fornecido
        if (atomo.nome == nome) {
            return atomo.valencia; // Retorna o raio atômico
        }
    }

    // Se não encontrar o elemento, retorna -1 (ou outro valor indicativo de erro)
    std::cout << "Elemento com o nome '" << nome << "' não encontrado." << std::endl;
    return -1; // Indica que o elemento não foi encontrado
}
