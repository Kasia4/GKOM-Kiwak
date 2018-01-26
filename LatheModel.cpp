#include "LatheModel.h"

LatheModel::LatheModel(const GLuint seg, const std::vector<glm::vec2>& line, const glm::vec3& v)
	:Model(v)
	,segments(seg)
	,side_line(line)
{
	generate();
}

LatheModel::~LatheModel()
{
}

void LatheModel::generate()
{
	GLuint& sh_v = segments;
	const GLuint& li_s = side_line.size();
	GLuint v_count = 2 * (sh_v + 1)*(li_s - 1) + 2 * sh_v + 2;
	GLuint i_count = 2 * (sh_v+1)*(li_s - 1) + 2 * sh_v + 2*sh_v + 2;
	setVertices(v_count);
	setIndices(i_count);
	GLfloat step_angle = 2 * M_PI / sh_v;
	GLfloat curr_h = 0.0f;

	for (GLuint i = 0; i < li_s-1; ++i)
	{
		glm::vec2& curr_l = side_line[i];
		glm::vec2& curr_l_n = side_line[i + 1];
		glm::vec3 level_cent(0.0f, curr_l.y, 0.0f);
		GLfloat level_r = curr_l.x;
		GLfloat level_r_n = curr_l_n.x;
		GLfloat side_h = glm::length(curr_l - curr_l_n);
		GLfloat side_l = 2 * level_r*level_r - 2 * level_r*cos(step_angle);

		for (GLuint j = 0; j < sh_v; ++j)
		{
			glm::vec3 curr = cylindrical(level_r, curr_l.y, j*step_angle);
			glm::vec3 curr_n = cylindrical(level_r_n, curr_l_n.y, j*step_angle);
			glm::vec3 v_osc = cylindrical(1.0f, 0.0f, j*step_angle + M_PI / 2);
			glm::vec3 curr_d = curr_n - curr;
			glm::vec3 norm = normal(curr_d, v_osc);
			setVertex(2 * (sh_v + 1)*i + 2 * j, curr, norm, glm::vec2(j*side_l, curr_h));
			setVertex(2 * (sh_v + 1)*i + 2 * j + 1, curr_n, norm, glm::vec2(j*side_l, curr_h + side_h));
			setIndex(2 * (sh_v + 1)*i + 2 * j, glm::uvec3(2 * (sh_v + 1)*i + 2 * j, 2 * (sh_v + 1)*i + 2 * (j + 1), 2 * (sh_v + 1)*i + 2 * j + 1));
			setIndex(2 * (sh_v + 1)*i + 2 * j + 1, glm::uvec3(2 * (sh_v + 1)*i + 2 * (j + 1), 2 * (sh_v + 1)*i + 2 * j + 1, 2 * (sh_v + 1)*i + 2 * (j + 1) + 1));
		}

		glm::vec3 curr_d(curr_l_n.x - curr_l.x, curr_l_n.y - curr_l.y, 0.0f); 
		glm::vec3 norm = normal(curr_d, glm::vec3(0.0f, 0.0f, 1.0f));
		setVertex(2 * (sh_v + 1)*i + 2 * sh_v, cylindrical(level_r, curr_l.y , 0.0f), norm, glm::vec2(sh_v*side_l, curr_h));
		setVertex(2 * (sh_v + 1)*i + 2 * sh_v + 1, cylindrical(level_r_n, curr_l_n.y, 0.0f), norm, glm::vec2(sh_v*side_l, curr_h + side_h));
		curr_h += side_h;
	}

	for (GLuint j = 0; j < sh_v; ++j)
	{
		glm::vec3 curr = cylindrical(side_line[0].x, side_line[0].y, j*step_angle);
		glm::vec3 curr2 = cylindrical(side_line[side_line.size() - 1].x, side_line[side_line.size() - 1].y, j*step_angle);
		setVertex(2 * (sh_v + 1)*(li_s - 1) + 2 * j, curr, down, glm::vec2(curr.x, curr.z));
		setVertex(2 * (sh_v + 1)*(li_s - 1) + 2 * j + 1, curr2, up, glm::vec2(curr2.x, curr2.z));
		setIndex(2 * (sh_v + 1)*(li_s - 1) + 2 * sh_v + 2 * j, glm::uvec3(2 * (sh_v + 1)*(li_s - 1) + 2 * j, 2 * (sh_v + 1)*(li_s - 1) + 2 * ((j + 1) % sh_v), 2 * (sh_v + 1)*(li_s - 1) + 2 * sh_v));
		setIndex(2 * (sh_v + 1)*(li_s - 1) + 2 * sh_v + 2 * j + 1, glm::uvec3(2 * (sh_v + 1)*(li_s - 1) + 2 * j + 1, 2 * (sh_v + 1)*(li_s - 1) + 2 * ((j + 1) % sh_v) + 1, 2 * (sh_v + 1)*(li_s - 1) + 2 * sh_v + 1));
	}

	setVertex(2 * (sh_v + 1)*(li_s - 1) + 2 * sh_v, glm::vec3(0.0f, side_line[0].y, 0.0f), down, glm::vec2());
	setVertex(2 * (sh_v + 1)*(li_s - 1) + 2 * sh_v + 1, glm::vec3(0.0f, side_line[side_line.size() - 1].y, 0.0f), up, glm::vec2());

	setBuffers();
}
