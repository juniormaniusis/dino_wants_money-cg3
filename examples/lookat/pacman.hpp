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

 private:
  GLuint m_VAO{};
  GLuint m_VBO{};
  GLuint m_EBO{};

  GLint m_modelMatrixLoc{};
  GLint m_colorLoc{};

  std::vector<Vertex> m_vertices;
  std::vector<GLuint> m_indices;

  void loadModelFromFile(std::string_view path);
};

#endif