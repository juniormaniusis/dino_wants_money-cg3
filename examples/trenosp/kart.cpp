#include "kart.hpp"
#include <cppitertools/itertools.hpp>
#include <glm/gtx/fast_trigonometry.hpp>
#include <glm/gtx/hash.hpp>
#include <unordered_map>

//atualiza a position do treno e limita seus movimentos dedntro da wall
void Kart::moveKart(float speed,float side){
    if(speed>0){
        if(side!=0){
            m_angle+=(side*30);
        }
        m_position += glm::vec3(speed*glm::cos(glm::radians(m_angle)),0.0f,-speed*glm::sin(glm::radians(m_angle)));
    }
    if(speed<0){
        if(side!=0){
            m_angle-=(side*30);
        }
        m_position += glm::vec3(speed*glm::cos(glm::radians(m_angle)),0.0f,-speed*glm::sin(glm::radians(m_angle)));
    }
    float factor{0.2f*(1.0f-(static_cast<float>(glm::abs(glm::cos(glm::radians(m_angle)-asin((glm::normalize(m_position)).x) ) ) ) ) ) };
    float distance{glm::distance(m_position,glm::vec3(0.0f))};
    if(distance < (3.15f+factor)){
        m_position = (3.17f+factor)*glm::normalize(m_position);
    }
    if(distance > (4.65f-factor)){
        m_position = (4.62f-factor)*glm::normalize(m_position);
    }
    glm::mat4 model{1.0f};
    model = glm::translate(model, m_position);
    model = glm::rotate(model, glm::radians(m_angle), glm::vec3(0, 1, 0));
    model = glm::scale(model, glm::vec3(0.2f));
    m_modelMatrix = model;
}   