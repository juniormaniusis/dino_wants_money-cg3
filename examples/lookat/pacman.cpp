#include "pacman.hpp"

#include <fmt/core.h>
#include <imgui.h>
#include <tiny_obj_loader.h>

#include <cppitertools/itertools.hpp>
#include <glm/gtc/matrix_inverse.hpp>
#include <glm/gtx/fast_trigonometry.hpp>
#include <glm/gtx/hash.hpp>
#include <unordered_map>

void Pacman::initializeGL(std::string assetsPath, GLuint program) {
  m_model.loadDiffuseTexture(assetsPath + "maps/dog.jpg");
  m_model.loadFromFile(assetsPath + "dog.obj");
  m_model.setupVAO(program);

  auto model = glm::mat4{1};
  m_posicao_atual = m_posicao_inicial;
  m_modelMatrix = glm::translate(model, m_posicao_inicial);
  m_modelMatrix = glm::rotate(model, glm::radians(90.0f), glm::vec3(1, 0, 0));
}

void Pacman::paintGL(GLuint program, glm::mat4 cameraViewMatrix) {
  GLint modelMatrixLoc{glGetUniformLocation(program, "modelMatrix")};
  GLint normalMatrixLoc{glGetUniformLocation(program, "normalMatrix")};
  GLint shininessLoc{glGetUniformLocation(program, "shininess")};
  GLint KaLoc{glGetUniformLocation(program, "Ka")};
  GLint KdLoc{glGetUniformLocation(program, "Kd")};
  GLint KsLoc{glGetUniformLocation(program, "Ks")};
  GLint mappingModeLoc{glGetUniformLocation(program, "mappingMode")};
  glUniformMatrix4fv(modelMatrixLoc, 1, GL_FALSE, &m_modelMatrix[0][0]);

  auto modelViewMatrix{glm::mat4(cameraViewMatrix * m_modelMatrix)};
  glm::mat3 normalMatrix{glm::inverseTranspose(modelViewMatrix)};
  glUniformMatrix3fv(normalMatrixLoc, 1, GL_FALSE, &normalMatrix[0][0]);

  glUniform1f(shininessLoc, m_model.m_shininess);
  glUniform4fv(KaLoc, 1, &m_model.m_Ka.x);
  glUniform4fv(KdLoc, 1, &m_model.m_Kd.x);
  glUniform4fv(KsLoc, 1, &m_model.m_Ks.x);

  glUniform1i(mappingModeLoc, 1);
  m_model.render();
}

void Pacman::update(float deltaTime) {
  auto model = glm::mat4{1};
  m_posicao_atual = m_posicao_atual + m_direcao * m_velocidade * deltaTime;
  m_modelMatrix = glm::translate(model, m_posicao_atual);
  m_modelMatrix = glm::scale(m_modelMatrix, m_escala_inicial);
  m_modelMatrix = glm::rotate(m_modelMatrix, glm::radians(-90.0f), glm::vec3(1, 0, 0));
  m_modelMatrix = glm::rotate(m_modelMatrix, glm::radians(-90.0f), glm::vec3(0, 0, 1));
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