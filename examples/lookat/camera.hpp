#ifndef CAMERA_HPP_
#define CAMERA_HPP_

#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>

#include "gamedata.hpp"
class OpenGLWindow;
class Pacman;

class Camera {
 public:
  void computeViewMatrix();
  void olharPara(glm::vec3 ponto);
  void computeProjectionMatrix(int width, int height);

  void dolly(float speed);
  void truck(float speed);
  void pan(float speed);

 private:
  friend OpenGLWindow;
  friend Pacman;
  glm::vec3 m_eye{glm::vec3(0.0f, 0.5f, 2.5f)};  // Camera position

  glm::vec3 m_distance{glm::vec3(-2.85, -2.85, 0)};  // distancia do objeto

  glm::vec3 m_at{glm::vec3(0.0f, 0.5f, 0.0f)};  // Look-at point
  glm::vec3 m_up{glm::vec3(0.0f, 1.0f, 0.0f)};  // "up" direction

  // Matrix to change from world space to camera soace
  glm::mat4 m_viewMatrix;

  // Matrix to change from camera space to clip space
  glm::mat4 m_projMatrix;

  CameraMode m_cameraMode;
  float m_dollySpeed{0.0f};
  float m_truckSpeed{0.0f};
  float m_panSpeed{0.0f};

  void update(float deltaTime, Pacman pacman);
};

#endif