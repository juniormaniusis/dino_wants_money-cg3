#include "camera.hpp"

#include <glm/gtc/matrix_transform.hpp>

#include "pacman.hpp"

void Camera::computeProjectionMatrix(int width, int height) {
  float FOV = 70;
  float NEAR_PLANE = 0.1f;
  float FAR_PLANE = 1000;
  m_projMatrix = glm::mat4(1.0f);
  const auto aspect{static_cast<float>(width) / static_cast<float>(height)};
  m_projMatrix =
      glm::perspective(glm::radians(FOV), aspect, NEAR_PLANE, FAR_PLANE);
}

void Camera::computeViewMatrix() {
  // m_viewMatrix = glm::lookAt(m_eye, m_at, m_up);
  auto viewMatrix = glm::mat4{1};
  viewMatrix =
      glm::rotate(viewMatrix, glm::radians(m_pitch), glm ::vec3(1, 0, 0));
  viewMatrix =
      glm::rotate(viewMatrix, glm::radians(m_yaw), glm ::vec3(0, 1, 0));

  viewMatrix = glm::translate(viewMatrix, -m_posicao);

  m_viewMatrix = viewMatrix;
}

void Camera::update(glm::vec3 pacmanPosition, glm::vec3 pacmanRotation) {
  updatePosition(pacmanPosition, pacmanRotation);

  computeViewMatrix();
}

void Camera::updatePosition(glm::vec3 pacmanPosition,
                            glm::vec3 pacmanRotation) {
  float xDistance = m_distanceFromPlayer * glm::cos(glm::radians(m_pitch));
  float yDistance = m_distanceFromPlayer * glm::sin(glm::radians(m_pitch));

  float theta = pacmanRotation.y + m_angleAroundPlayer;

  float offsetX = static_cast<float>(xDistance * glm::sin(glm::radians(theta)));
  float offsetZ = static_cast<float>(xDistance * glm::cos(glm::radians(theta)));

  m_posicao.x = pacmanPosition.x - offsetX;
  m_posicao.z = pacmanPosition.z - offsetZ;
  m_posicao.y = pacmanPosition.y + yDistance;

  m_yaw = 180 - (pacmanRotation.y + m_angleAroundPlayer);
}

void Camera::initialize() {}

void Camera::changeDistanceFromPlayer(float mouseWheel) {
  m_distanceFromPlayer += mouseWheel * 0.2f;
  if (m_distanceFromPlayer < 3.0f) {
    m_distanceFromPlayer = 3.0f;
    return;
  }
  if (m_distanceFromPlayer > 15.0f) {
    m_distanceFromPlayer = 15.0f;
    return;
  }
}

void Camera::calculatePitch(float mouse) {
  float delta = mouse * 35.0f;
  m_pitch += delta;
  if (m_pitch < 10) {
    m_pitch = 10;
    return;
  }
  if (m_pitch > 95) {
    m_pitch = 95;
    return;
  }
}

void Camera::calculateAngleAroundPlayer(float mouse) {
  float delta = mouse * 35.0f;
  m_angleAroundPlayer -= delta;
}