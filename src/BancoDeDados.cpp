#include "BancoDeDados.hpp"

BancoDeDados::BancoDeDados() {}

BancoDeDados::BancoDeDados(const std::string& banco) {
    int rc = sqlite3_open(banco.c_str(), &db);
    if (rc) {
        std::cerr << "Erro ao abrir banco de dados: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_close(db);
        db = nullptr;
    } else {
        std::cout << "Banco de dados aberto!" << std::endl;
    }
}

BancoDeDados::~BancoDeDados() {
    if (db) {
        sqlite3_close(db);
    }
}

void BancoDeDados::verificarErros(int rc) {
    if (rc != SQLITE_OK) {
        std::cerr << "Erro: " << sqlite3_errmsg(db) << std::endl;
    }
}

void BancoDeDados::CriarTabela() {
    const char* sql = "CREATE TABLE IF NOT EXISTS livros ("
                      "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                      "titulo TEXT NOT NULL, "
                      "conteudo TEXT NOT NULL);";
    char* MensagemErro = nullptr;
    int rc = sqlite3_exec(db, sql, nullptr, nullptr, &MensagemErro);
    if (rc != SQLITE_OK) {
        std::cerr << "Erro ao criar tabela: " << MensagemErro << std::endl;
        sqlite3_free(MensagemErro);
    } else {
        std::cout << "Tabela de livros criada com sucesso!" << std::endl;
    }
}

bool BancoDeDados::inserirLivro(const std::string& titulo, const std::string& conteudo) {
    std::string sql = "INSERT INTO livros (titulo, conteudo) VALUES (?, ?);";
    sqlite3_stmt* stmt;

    int rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);
    if (rc != SQLITE_OK) {
        std::cerr << "Erro ao preparar SQL: " << sqlite3_errmsg(db) << std::endl;
        return false;
    }

    sqlite3_bind_text(stmt, 1, titulo.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, conteudo.c_str(), -1, SQLITE_STATIC);

    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        std::cerr << "Erro ao inserir livro: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_finalize(stmt);
        return false;
    }

    sqlite3_finalize(stmt);
    return true;
}

bool BancoDeDados::verificarLivroExistente(const std::string& titulo) {
    std::string sql = "SELECT COUNT(*) FROM livros WHERE titulo = ?;";
    sqlite3_stmt* stmt;
    int count = 0;

    int rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);
    if (rc != SQLITE_OK) {
        std::cerr << "Erro ao preparar SQL: " << sqlite3_errmsg(db) << std::endl;
        return false;
    }

    sqlite3_bind_text(stmt, 1, titulo.c_str(), -1, SQLITE_STATIC);

    if (sqlite3_step(stmt) == SQLITE_ROW) {
        count = sqlite3_column_int(stmt, 0);
    }

    sqlite3_finalize(stmt);

    return count > 0;
}


std::string BancoDeDados::buscarLivro(const std::string& titulo) {
    std::string sql = "SELECT conteudo FROM livros WHERE titulo = ?;";
    sqlite3_stmt* stmt;
    std::string conteudoLivro;

    int rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);
    if (rc != SQLITE_OK) {
        std::cerr << "Erro ao preparar SQL: " << sqlite3_errmsg(db) << std::endl;
        return "";
    }

    sqlite3_bind_text(stmt, 1, titulo.c_str(), -1, SQLITE_STATIC);

    if (sqlite3_step(stmt) == SQLITE_ROW) {
        const unsigned char* conteudo = sqlite3_column_text(stmt, 0);
        conteudoLivro = reinterpret_cast<const char*>(conteudo);
    }

    sqlite3_finalize(stmt);
    return conteudoLivro;
}

std::vector<std::string> BancoDeDados::listarLivros() {
    std::vector<std::string> titulos;
    sqlite3_stmt* stmt;
    const char* sql = "SELECT titulo FROM livros";

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) == SQLITE_OK) {
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            const char* titulo = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
            if (titulo) {
                titulos.emplace_back(titulo);
            }
        }
    } else {
        std::cerr << "Erro ao listar livros: " << sqlite3_errmsg(db) << std::endl;
    }

    sqlite3_finalize(stmt);
    return titulos;
}

void BancoDeDados::FecharBanco() {
    sqlite3_close(db);
}


