/*
 * SceneShader.h
 *
 *  Created on: Nov 17, 2015
 *      Author: acarocha
 */

#ifndef SCENESHADER_H_
#define SCENESHADER_H_

#include "Shader.h"
#include <vector>

#define GLM_FORCE_RADIANS

#include "TriMesh.h"
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "texture.h"
#include "lodepng.h"

class SceneShader : public Shader
{
public:

	SceneShader();
	~SceneShader();

    void startup (std::string model, std::string texture);
	void shutdown ();
	void render();

	void renderPlane();
	void renderMesh();
	void renderLight();

	void setAspectRatio( float ratio );
	void setZTranslation(float z);
	void setRotationX( float x );
	void setRotationY( float y );

	void updateLightPositionX( float x );
	void updateLightPositionY( float y );
	void updateLightPositionZ( float z );

    float r = 0.4;
    void updateTexture( std::string texture_name );
    void updateModel( std::string model_name );
    void createVertexBuffer( std::string model_name, std::string texture_name );
	
private:

	/*methods*/

    void readMesh( std::string filename );


	/*variables*/
	GLuint _programLight;
	GLuint _programPlane;
	GLuint _programMesh;

	GLuint _planeVertexArray;
	GLuint _planeVertexBuffer;

	GLuint _meshVertexArray;
	GLuint _meshVertexBuffer;
	GLuint _meshNormalBuffer;
	GLuint _meshIndicesBuffer;

	GLint _mvUniform, _projUniform;

	/* Matrices */
	glm::mat4 _modelview;
	glm::mat4 _projection;

	float _zTranslation;
	float _xRot;
	float _yRot;
	float _aspectRatio;

    /* Textures */
    GLuint _texture2Did;
    Texture _texture;

	/*vertices*/	
	std::vector<unsigned char> _image;
	unsigned int _imageWidth;
    unsigned int _imageHeight;

	trimesh::TriMesh* _mesh;
	std::vector<unsigned int> _triangleIndices;

	glm::vec3 lightPosition;

};

#endif /* SCENESHADER_H_ */
