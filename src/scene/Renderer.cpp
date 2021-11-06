#pragma once

#include "scene.hpp"

void Renderer::clear() {
	glFlush();
	glClearColor(0.75f, 0.75f, 0.75f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::prepare() {
    const auto config = Configuration::getInstance();
    this->aspect = config->getViewport()->width / config->getViewport()->height;
    this->projection = glm::perspective(glm::radians(45.f), aspect, 1.f, 1000.f);
}

void Renderer::render(Entity* entity, Camera* camera, LightConfiguration* ligth) {
    const auto view = camera->getView();
    const auto model = *entity->getModel();
    const auto color = *entity->getColor();

    glBindVertexArray(entity->getVAO());
    glBindBuffer(GL_ARRAY_BUFFER, entity->getPositionVBO());
    glBufferData(GL_ARRAY_BUFFER, entity->getVertices()->size() * sizeof(vec3), entity->getVertices()->data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, entity->getNormalVBO());
    glBufferData(GL_ARRAY_BUFFER, entity->getNormals()->size() * sizeof(vec3), entity->getNormals()->data(), GL_STATIC_DRAW);

    glUseProgram(entity->getShader());
    glUniformMatrix4fv(glGetUniformLocation(entity->getShader(), "model"), 1, GL_FALSE, value_ptr(model));
    glUniformMatrix4fv(glGetUniformLocation(entity->getShader(), "view"), 1, GL_FALSE, value_ptr(view));
    glUniformMatrix4fv(glGetUniformLocation(entity->getShader(), "projection"), 1, GL_FALSE, value_ptr(this->projection));
    glUniform4f(glGetUniformLocation(entity->getShader(), "objectColor"), color.r, color.g, color.b, color.a);
    glUniform4f(glGetUniformLocation(entity->getShader(), "lightPosition"), 
        ligth->lightPosition.x, 
        ligth->lightPosition.y, 
        ligth->lightPosition.z, 
        ligth->lightPosition.w);
    glUniform1f(glGetUniformLocation(entity->getShader(), "ambientLightStrength"), ligth->ambientLightStrength);
    glUniform1f(glGetUniformLocation(entity->getShader(), "diffuseLightStrength"), ligth->diffuseLightStrength);

    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, entity->getPositionVBO());
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, entity->getNormalVBO());
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

    glDrawArrays(GL_TRIANGLES, 0, entity->getVertices()->size());
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
}

