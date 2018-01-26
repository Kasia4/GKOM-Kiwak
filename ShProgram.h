#pragma once
class ShProgram
{
private:
	GLuint program_id;
public:
	ShProgram(const GLchar* vertexPath, const GLchar* fragmentPath);

	void Use() const;

	GLuint getProgramID() const
	{
		return program_id;
	}
	~ShProgram();
};

