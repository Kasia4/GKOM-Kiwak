#pragma once
class ShProgram
{
public:
	ShProgram(const GLchar* vertexPath, const GLchar* fragmentPath);
	~ShProgram();

	void Use() const;

	GLuint getProgramID() const
	{
		return program_id;
	}
private:
	GLuint program_id;
};

