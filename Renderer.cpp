#include "Renderer.h"


Renderer::Renderer(ShProgram & shader)
	:shader(shader)
{
}

Renderer::~Renderer()
{
}


void Renderer::use(const GLuint& VAO, const glm::mat4& trans, const GLuint indices_count, const Material* mat)
{
	setObjectMaterial(mat);
	setObjectMatrix(trans);
	shader.Use();
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, indices_count, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
	glDisable(GL_TEXTURE_2D);
}

void Renderer::setObjectMatrix(const glm::mat4& mtx)
{
	GLuint transformLoc = glGetUniformLocation(shader.getProgramID(), "transform");
	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(mtx));
}

void Renderer::setViewMatrix(const glm::mat4& mtx)
{
	GLuint viewLoc = glGetUniformLocation(shader.getProgramID(), "view");
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(mtx));

}

void Renderer::setProjectionMatrix(const glm::mat4& mtx)
{
	GLuint projLoc = glGetUniformLocation(shader.getProgramID(), "projection");
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(mtx));
}



void Renderer::setObjectMaterial(const Material * material)
{
	GLuint programID = shader.getProgramID();
	if (material->getTexture()) {
		glEnable(GL_TEXTURE_2D);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, material->getTexture()->getId());
		glUniform1i(glGetUniformLocation(programID, "Texture0"), 0);
		glUniform1i(glGetUniformLocation(programID, "iftexture"), GL_TRUE);

		glm::vec2 tex_scale = material->getTextureScale();
		float tex_scale_a[2] = { tex_scale.x, tex_scale.y };
		glUniform2fv(glGetUniformLocation(programID, "textureScale"), 1, tex_scale_a);
	}
	else {
		glUniform1i(glGetUniformLocation(programID, "iftexture"), GL_FALSE);
	}

	glUniform1f(glGetUniformLocation(programID, "glossiness"), material->getGlossiness());
	glUniform1f(glGetUniformLocation(programID, "specularLevel"), material->getSpecularLevel());
	glUniform4fv(glGetUniformLocation(programID, "materialColor"),1,  glm::value_ptr(material->getColor()));
}


void Renderer::setLight(const Light& light)
{
	GLuint s_id = shader.getProgramID();
	glUniform1f(glGetUniformLocation(s_id, "lightPower"), light.getPower());
	glUniform3fv(glGetUniformLocation(s_id, "lightColor"), 1, glm::value_ptr(light.getColor()));
	glUniform3fv(glGetUniformLocation(s_id, "lightPosition"), 1, glm::value_ptr(light.getPosition()));
}

void Renderer::setEnvironment(const Environment & environment)
{
	GLuint s_id = shader.getProgramID();
	glUniform1f(glGetUniformLocation(s_id, "ambientLevel"), environment.getAmbientLight());
	glUniform3fv(glGetUniformLocation(s_id, "ambientColor"), 1, glm::value_ptr(environment.getAmbientColor()));
}
