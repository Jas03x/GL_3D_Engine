#include "PointLightRenderer.h"

_PointLightRenderer PointLightRenderer;

void _PointLightRenderer::initalize(const DSFramebuffer& fbo)
{
	ShaderSource source = ShaderSource(INT_SHDR("point_light.vert"), INT_SHDR("point_light.frag"));
	this->source(source);
	this->bindAttributeLocation(0, "vertex");
	this->link(source);
	this->mvp_matrix = this->getUniform("mvp_matrix");
	this->light_color = this->getUniform("light_color");
	this->diffuse_texture = this->getUniform("diffuse_texture");
	this->normal_texture = this->getUniform("normal_texture");
	this->depth_texture = this->getUniform("depth_texture");
	this->light_position = this->getUniform("light_position");
	this->inv_proj_matrix = this->getUniform("inv_proj_matrix");
	this->screen_size = this->getUniform("screen_size");

	this->framebuffer = &fbo;
}

void _PointLightRenderer::render(const PointLight& light)
{
	this->bind();
    // VAO should already be bound
	//PointLight::_bindVAO();

	this->framebuffer->bindTexture(this->diffuse_texture, DSFramebuffer::DIFFUSE_TEXTURE, 0);
	this->framebuffer->bindTexture(this->normal_texture, DSFramebuffer::NORMAL_TEXTURE, 1);
	this->framebuffer->bindTexture(this->depth_texture, DSFramebuffer::DEPTH_TEXTURE, 2);
	
	glm::mat4 inverse_projection = glm::inverse(Camera::getProjectionMatrix());
    glm::mat4 mvp = Camera::getMatrix() * glm::translate(light.position) * glm::scale(light.size);
	glm::vec3 light_pos_eyespace = glm::vec3(Camera::getViewMatrix() * glm::vec4(light.position, 1));
    
	glUniformMatrix4fv(this->mvp_matrix, 1, GL_FALSE, &mvp[0][0]);
	glUniformMatrix4fv(this->inv_proj_matrix, 1, GL_FALSE, &inverse_projection[0][0]);
	
	glUniform2f(this->screen_size, (float) this->framebuffer->getDimensions().x, (float) this->framebuffer->getDimensions().y);
	glUniform3fv(this->light_color, 1, &light.color[0]);
	glUniform3fv(this->light_position, 1, &light_pos_eyespace[0]);

	glDrawArrays(GL_TRIANGLES, 0, PointLight::_getArrayVertexCount());
	glBindVertexArray(0);
}

void _PointLightRenderer::destroy()
{
	Shader::destroy();
}
