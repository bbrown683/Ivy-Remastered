/*
MIT License

Copyright (c) 2017 Ben Brown

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include "Model.h"

bool Ivy::Graphics::Model::Load(std::string filePath) {
    Assimp::Importer importer;

    const aiScene* scene = importer.ReadFile(filePath, aiProcess_CalcTangentSpace |
        aiProcess_Triangulate |
        aiProcess_JoinIdenticalVertices |
        aiProcess_GenUVCoords |
        aiProcess_GenNormals);

    if (!scene || scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
        std::cout << "Assimp: Error - " << importer.GetErrorString() << std::endl;
        return false;
    }

    for (unsigned int i = 0; i < scene->mNumMeshes; i++) {
        aiMesh* mesh = scene->mMeshes[i];

        // Components of a mesh.
        std::vector<Vertex> vertices;
        std::vector<GLushort> indices;
        std::vector<Texture> textures;

        // Grab the vertex position and colors for the mesh.
        for (unsigned int j = 0; j < mesh->mNumVertices; j++) {
            Vertex vertex;

            if (mesh->HasPositions()) {
                aiVector3D position = mesh->mVertices[j];
                vertex.m_Position = glm::vec3(position.x, position.y, position.z);
            }
            else
                vertex.m_Position = glm::vec3();
            
            if (mesh->HasTextureCoords(0)) {
                aiVector3D texCoord0 = mesh->mTextureCoords[0][j];
                vertex.m_TexCoord0 = glm::vec2(texCoord0.x, texCoord0.y);
            }
            else
                vertex.m_TexCoord0 = glm::vec2();

            if (mesh->HasNormals()) {
                aiVector3D normal = mesh->mNormals[j];
                vertex.m_Normal = glm::vec3(normal.x, normal.y, normal.z);
            }
            else
                vertex.m_Normal = glm::vec3();


            if (mesh->HasVertexColors(0)) {
                aiColor4D color0 = mesh->mColors[0][j];
                vertex.m_Color0 = glm::vec4(color0.r, color0.g, color0.b, color0.a);
            }
            else
                vertex.m_Color0 = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);

            vertices.push_back(vertex);
        }

        if (mesh->HasFaces()) {
            // Grab the indices for the mesh.
            for (unsigned int j = 0; j < mesh->mNumFaces; j++) {
                aiFace face = mesh->mFaces[j];

                for (unsigned int k = 0; k < face.mNumIndices; k++)
                    indices.push_back(face.mIndices[k]);
            }
        }

        // Check to see if mesh has a texture.
        if (mesh->mMaterialIndex >= 0) {
            aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

            // Iterate though each texture type if they exist.
            for (unsigned int j = 0; j < material->GetTextureCount(aiTextureType_DIFFUSE); j++) {
                // Get the texture for the material.
                aiString string;
                material->GetTexture(aiTextureType_DIFFUSE, j, &string);
                textures.push_back(Texture(string.C_Str(), GL_RGBA));
            }     
        } 
        m_Meshes.push_back(TestMesh(m_Program, vertices, indices, textures));
    }

    // Create our meshes.
    for (unsigned int i = 0; i < m_Meshes.size(); i++)
        m_Meshes[i].Create();

    return true;
}

void Ivy::Graphics::Model::Draw(void) {
    for (unsigned int i = 0; i < m_Meshes.size(); i++)
        m_Meshes[i].Draw();
}

void Ivy::Graphics::Model::SetPosition(glm::vec3 position) {
    m_Position += position;
    for (unsigned int i = 0; i < m_Meshes.size(); i++)
        m_Meshes[i].SetPosition(m_Position);
}

void Ivy::Graphics::Model::SetRotation(glm::vec3 rotation) {
    m_Rotation += rotation;
    for (unsigned int i = 0; i < m_Meshes.size(); i++)
        m_Meshes[i].SetRotation(m_Rotation);
}

void Ivy::Graphics::Model::SetScale(glm::vec3 scale) {
    m_Scale += scale;
    for (unsigned int i = 0; i < m_Meshes.size(); i++)
        m_Meshes[i].SetScale(m_Scale);
}
