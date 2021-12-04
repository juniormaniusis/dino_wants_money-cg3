#include "parede.hpp"

#include <fmt/core.h>
#include <imgui.h>
#include <tiny_obj_loader.h>

#include <cppitertools/itertools.hpp>
#include <glm/gtc/matrix_inverse.hpp>
#include <glm/gtx/fast_trigonometry.hpp>
#include <glm/gtx/hash.hpp>
#include <unordered_map>

void Parede::initializeGL(GLuint program, std::string assetsPath,
                          glm::vec3 posInicial, glm::vec3 posFinal) {
  m_posicaoFinal = posFinal;
  m_posicaoInicial = posInicial;
  m_model.loadDiffuseTexture(assetsPath + "maps/parede.png");
  m_model.loadFromFile(assetsPath + "cube.obj");
  m_model.setupVAO(program);
  float comprimento = glm::length(posFinal - posInicial);
  m_modelMatrix = glm::scale(m_modelMatrix, glm::vec3(0.1, 3, comprimento));
}

void Parede::paintGL(GLuint program, glm::mat4 cameraViewMatrix) {
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

void Parede::update(float deltaTime) {}

void Parede::terminateGL() {}

Parede::~Parede() {}