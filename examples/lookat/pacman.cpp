#include "pacman.hpp"

#include <fmt/core.h>
#include <imgui.h>
#include <tiny_obj_loader.h>

#include <cppitertools/itertools.hpp>
#include <glm/gtx/fast_trigonometry.hpp>
#include <glm/gtx/hash.hpp>
#include <unordered_map>

void Pacman::initializeGL(std::string assetsPath, GLuint program) {
  m_model.loadDiffuseTexture(assetsPath + "maps/pacman.png");
  m_model.loadFromFile(assetsPath + "cube.obj");
  m_model.setupVAO(program);

  auto model = glm::mat4{1};
  m_posicao_atual = m_posicao_inicial;
  m_modelMatrix = glm::translate(model, m_posicao_inicial);
}

void Pacman::paintGL(GLint viewMatrixLoc, GLint projMatrixLoc,
                     GLint modelMatrixLoc, GLint colorLoc) {
  // abcg::glBindVertexArray(m_VAO);

  // // matriz do modelo
  // abcg::glUniformMatrix4fv(modelMatrixLoc, 1, GL_FALSE,
  // &m_modelMatrix[0][0]);

  // // cor do coelho
  // abcg::glUniform4f(colorLoc, 1.0f, 1.0f, 1.0f, 1.0f);

  // abcg::glDrawElements(GL_TRIANGLES, m_indices.size(), GL_UNSIGNED_INT,
  //                      nullptr);

  // abcg::glBindVertexArray(0);
}

void Pacman::update(float deltaTime) {
  auto model = glm::mat4{1};
  // m_posicao_atual = m_posicao_atual + m_direcao * m_velocidade * deltaTime;
  m_modelMatrix = glm::translate(model, m_posicao_atual);
  m_modelMatrix = glm::scale(m_modelMatrix, m_escala_inicial);

  // m_angulo += m_sentidoRotacao * 300 * deltaTime;
  // m_modelMatrix = glm::rotate(m_modelMatrix, glm::radians(m_angulo),
  //                             glm::vec3(0.0f, 1.0f, 0.0f));
}

void Pacman::terminateGL() {
  // abcg::glDeleteBuffers(1, &m_VBO);
  // abcg::glDeleteBuffers(1, &m_EBO);
  // abcg::glDeleteVertexArrays(1, &m_VAO);
}

Pacman::~Pacman() {}