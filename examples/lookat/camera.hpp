#ifndef CAMERA_HPP_
#define CAMERA_HPP_

#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>

#include "gamedata.hpp"
class OpenGLWindow;
class Dinossauro;

class Camera {
 public:
  void computeViewMatrix();
  void computeProjectionMatrix(int width, int height);
  void initialize();

  void changeDistanceFromPlayer(float mouseWhell);
  void calculatePitch(float mouse);
  void calculateAngleAroundPlayer(float mouse);

 private:
  friend OpenGLWindow;
  friend Dinossauro;

  glm::mat4 m_viewMatrix;
  glm::mat4 m_projMatrix;

  glm::vec3 m_posicao{0, 5, 0};

  float m_pitch{10};
  float m_yaw{0};
  float m_roll{0};
  float m_distanceFromPlayer{10};
  float m_angleAroundPlayer{0};

  void update(glm::vec3 targetPosition, glm::vec3 pacmanRotation);
  void updatePosition(glm::vec3 targetPosition, glm::vec3 pacmanRotation);
};

#endif