#ifndef PACMAN_HPP_
#define PACMAN_HPP_

#include <vector>

#include "abcg.hpp"

struct Vertex {
  glm::vec3 position;

  bool operator==(const Vertex& other) const {
    return position == other.position;
  }
};

class Pacman {
 public:
  void initializeGL(std::string assetsPath, GLuint program);
  void paintGL(GLint viewMatrixLoc, GLint projMatrixLoc, GLint modelMatrixLoc,
               GLint colorLoc);
  void terminateGL();
  void update(float deltaTime);

 private:
  GLuint m_VAO{};
  GLuint m_VBO{};
  GLuint m_EBO{};

  GLint m_modelMatrixLoc{};
  glm::mat4 m_modelMatrix{1.0f};

  GLint m_colorLoc{};

  std::vector<Vertex> m_vertices;
  std::vector<GLuint> m_indices;

  glm::vec3 m_posicao_inicial{glm::vec3(0, 0, 0)};
  glm::vec3 m_escala_inicial{glm::vec3(.5f)};

  // posicionamento no espaço
  float m_tamanho{1.0f};
  float m_velocidade{1.0f};
  glm::vec3 m_direcao{glm::vec3(0, 0, 0)};

  void loadModelFromFile(std::string_view path);
  void computarMatrixModeloInicial();
};

#endif