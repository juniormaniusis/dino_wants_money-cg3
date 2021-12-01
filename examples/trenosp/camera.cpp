#include "camera.hpp"
#include <glm/gtc/matrix_transform.hpp>

void Camera::computeProjectionMatrix(int width, int height) {
  m_projMatrix = glm::mat4(1.0f);
  auto aspect{static_cast<float>(width) / static_cast<float>(height)};
  m_projMatrix = glm::perspective(glm::radians(70.0f), aspect, 0.1f, 20.0f);
}

void Camera::computeViewMatrix() {
  m_viewMatrix = glm::lookAt(m_eye, m_at, m_up);
}

//movimento no eixo z da camera
void Camera::dolly(float speed) {
  // forward : vetor unitário em direção -z da camera
  glm::vec3 forward = glm::normalize(m_at - m_eye);

  // Move para frente e para trás
  m_eye += forward * speed;
  m_at += forward * speed;

  computeViewMatrix();
}

//movimento de truck (lateral)
void Camera::truck(float speed) {
  // Compute forward
  glm::vec3 forward = glm::normalize(m_at - m_eye);
  // produto vetorial para achar o vetor a esquerda
  glm::vec3 left = glm::cross(m_up, forward);

  // Move para os lados
  m_at -= left * speed;
  m_eye -= left * speed;

  computeViewMatrix();
}

//movimento de truck (vertical)
void Camera::truckVert(float speed) {
  // Compute forward 
  glm::vec3 forward = glm::normalize(m_at - m_eye);
  //produto vetorial para achar o vetor a esquerda
  glm::vec3 left = glm::cross(m_up, forward);
  //produto vetorial para achar o vetor que aponta na direção y da camera
  glm::vec3 up = glm::cross(left,forward);

  // Move para cima e para baixo 
  m_at -= up * speed;
  m_eye -= up * speed;

  computeViewMatrix();
}

//movimento de pan(lateral)
void Camera::pan(float speed) {
  glm::mat4 transform{glm::mat4(1.0f)};

  // Rotate camera around its local y axis
  transform = glm::translate(transform, m_eye);
  transform = glm::rotate(transform, -speed, m_up);
  transform = glm::translate(transform, -m_eye);

  m_at = transform * glm::vec4(m_at, 1.0f);

  computeViewMatrix();
}

float Camera::angleBetween(
 glm::vec3 a,
 glm::vec3 b,
 glm::vec3 origin
){
 glm::vec3 da=glm::normalize(a-origin);
 glm::vec3 db=glm::normalize(b-origin);
 return glm::acos(glm::dot(da, db));
}

//movimento de pan(vertical limitado a próximo de 180 graus)
void Camera::panVert(float speed) {
  glm::mat4 transform{glm::mat4(1.0f)};
  glm::vec3 forward = glm::normalize(m_at - m_eye);
  float angle = angleBetween(m_up,forward,glm::vec3(0.0f));
  if((angle < 0.5f && speed > 0.0f) ||(angle > 2.6f && speed < 0.0f)) {
    return;
  }
  glm::vec3 left = glm::normalize(glm::cross(m_up, forward));
  
  // Rotate camera around its local x axis
  transform = glm::translate(transform, m_eye);
  transform = glm::rotate(transform, -speed, left);
  transform = glm::translate(transform, -m_eye);

  m_at = transform * glm::vec4(m_at, 1.0f);

  computeViewMatrix();
}

//modo third person, centraliza a camera atrás do treno
void Camera::centerKart(glm::vec3 position,float angle){
  m_at = position;
  m_eye = position - glm::vec3(1.5f*glm::cos(glm::radians(angle)),-0.9f,-1.5f*glm::sin(glm::radians(angle)));

  computeViewMatrix();
}