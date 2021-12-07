#include "camera.hpp"

#include <glm/gtc/matrix_transform.hpp>

#include "pacman.hpp"

void Camera::computeProjectionMatrix(int width, int height) {
  m_projMatrix = glm::mat4(1.0f);
  const auto aspect{static_cast<float>(width) / static_cast<float>(height)};
  m_projMatrix = glm::perspective(glm::radians(70.0f), aspect, 0.1f, 10.0f);
}

void Camera::computeViewMatrix() {
  m_viewMatrix = glm::lookAt(m_eye, m_at, m_up);
}

void Camera::update(float deltaTime, glm::vec3 posicao, float rotacao) {
  olharPara(posicao);
}

glm::vec3 Camera::getDirection() { return glm::normalize(m_at - m_eye); }

void Camera::initialize(glm::vec3 posicao) { olharPara(posicao); }

void Camera::olharPara(glm::vec3 ponto) {
  m_at = ponto;
  m_eye = ponto - glm::vec3(m_distance);

  computeViewMatrix();
}