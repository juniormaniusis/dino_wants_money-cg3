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

void Camera::dolly(float speed) {
  // Compute forward vector (view direction)
  const glm::vec3 forward{glm::normalize(m_at - m_eye)};

  // Move eye and center forward (speed > 0) or backward (speed < 0)
  m_eye += forward * speed;
  m_at += forward * speed;

  computeViewMatrix();
}

void Camera::truck(float speed) {
  // Compute forward vector (view direction)
  const glm::vec3 forward{glm::normalize(m_at - m_eye)};
  // Compute vector to the left
  const glm::vec3 left{glm::cross(m_up, forward)};

  // Move eye and center to the left (speed < 0) or to the right (speed > 0)
  m_at -= left * speed;
  m_eye -= left * speed;

  computeViewMatrix();
}

void Camera::pan(float speed) {
  glm::mat4 transform{glm::mat4(1.0f)};

  // Rotate camera around its local y axis
  transform = glm::translate(transform, m_eye);
  transform = glm::rotate(transform, -speed, m_up);
  transform = glm::translate(transform, -m_eye);

  m_at = transform * glm::vec4(m_at, 1.0f);

  computeViewMatrix();
}

void Camera::imprime(glm::mat4 mat) {
  for (int i = 0; i < 4; i++) {
    printf("(%f, %f, %f, %f)\n", mat[i][0], mat[i][1], mat[i][2], mat[i][3]);
  }
}

void Camera::rotacaoFixa(float velocidade, glm::vec3 posicao) {
  if (velocidade != 0) {
    glm::mat4 transform{glm::mat4(1.0f)};

    // Rotate camera around its local y axis
    transform = glm::translate(transform, m_eye);
    transform = glm::rotate(transform, -velocidade, m_up);
    transform = glm::translate(transform, -m_eye);

    m_distance = transform * glm::vec4(m_distance, 1.0f);
    m_distance.y = -1.2f;
    // m_distance *= distancia;

    m_at = posicao;
    m_eye = posicao - glm::vec3(m_distance);

    computeViewMatrix();
  }
}

void Camera::update(float deltaTime, glm::vec3 posicao, float rotacao) {
  if (m_cameraMode == CameraMode::Fixa) {
    // rotacaoFixa(rotacao * deltaTime, posicao);
    olharPara(posicao);
  } else if (m_cameraMode == CameraMode::Livre) {
    dolly(m_dollySpeed * deltaTime);
    truck(m_truckSpeed * deltaTime);
    pan(m_panSpeed * deltaTime);
  }
}

glm::vec3 Camera::getDirection() { return glm::normalize(m_at - m_eye); }

void Camera::initialize(glm::vec3 posicao) { olharPara(posicao); }

void Camera::olharPara(glm::vec3 ponto) {
  m_at = ponto;
  m_eye = ponto - glm::vec3(m_distance);

  computeViewMatrix();
}