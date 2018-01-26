#include "FileModel.h"

using namespace std;



FileModel::FileModel(const GLchar * modelPath, const glm::vec3& v)
	:Model(v)
	,modelPath(modelPath)
{
	generate();
}

FileModel::~FileModel()
{
	
}

void FileModel::generate()
{
	ifstream model_file;
	model_file.open(modelPath);
	if (!model_file.is_open())
	{
		cout << "Model loading failed. File opening error." << endl;
		return;
	}
	GLuint v_count, v_readed = 0;
	model_file >> v_count;
	
	glm::vec3* vec_pos = new glm::vec3[v_count];
	glm::vec3* vec_norm = new glm::vec3[v_count];
	glm::vec2* vec_tex = new glm::vec2[v_count];

	for (GLuint i = 0; i < v_count && !model_file.eof(); ++i, v_readed+=6)
	{
		model_file >> vec_pos[i].x;
		model_file >> vec_pos[i].y;
		model_file >> vec_pos[i].z;
		model_file >> vec_norm[i].x;
		model_file >> vec_norm[i].y;
		model_file >> vec_norm[i].z;
	}
	if (v_readed != v_count * VERTEX_SIZE)
	{
		delete[] vec_pos;
		delete[] vec_norm;
		delete[] vec_tex;
		cout << "Model loading failed. Wrong file structure." << endl;
		return;
	}

	GLuint i_count, i_readed = 0;
	model_file >> i_count;
	glm::uvec3* vec_idx = new glm::uvec3[i_count];
	
	for (GLuint i = 0; i < i_count*INDEX_SIZE; ++i, ++i_readed)
	{
		model_file >> vec_idx[i].x;
		model_file >> vec_idx[i].y;
		model_file >> vec_idx[i].z;

	}
	if (i_readed != i_count*INDEX_SIZE)
	{
		delete[] vec_pos;
		delete[] vec_norm;
		delete[] vec_tex;
		delete[] vec_idx;
		cout << "Model loading failed. Wrong file structure." << endl;
		return;
	}
	setVertices(v_count);
	setIndices(i_count);
	for (GLuint i = 0; i < v_count; ++i)
	{
		setVertex(i, vec_pos[i], vec_norm[i], vec_tex[i]);
	}
	for (GLuint i = 0; i < i_count; ++i)
	{
		setIndex(i, vec_idx[i]);
	}
	setBuffers();
}
