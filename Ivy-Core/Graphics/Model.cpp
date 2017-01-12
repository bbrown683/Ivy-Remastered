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
        aiMesh* aMesh = scene->mMeshes[i];

        // Components of a mesh.
        std::vector<Vertex> vertices;
        std::vector<GLushort> indices;

        // Grab the vertex position and colors for the mesh.
        for (unsigned int j = 0; j < aMesh->mNumVertices; j++) {
            Vertex vertex;

            if (aMesh->HasPositions()) {
                aiVector3D position = aMesh->mVertices[j];
                vertex.m_Position = glm::vec3(position.x, position.y, position.z);
            }
            else
                vertex.m_Position = glm::vec3();

            if (aMesh->HasTextureCoords(0)) {
                aiVector3D texCoord0 = aMesh->mTextureCoords[0][j];
                vertex.m_TexCoord0 = glm::vec2(texCoord0.x, texCoord0.y);
            }
            else
                vertex.m_TexCoord0 = glm::vec2();

            if (aMesh->HasNormals())
            {
                aiVector3D normal = aMesh->mNormals[j];
                vertex.m_Normal = glm::vec3(normal.x, normal.y, normal.z);
            }
            else
                vertex.m_Normal = glm::vec3();

            if (aMesh->HasVertexColors(0))
            {
                aiColor4D color0 = aMesh->mColors[0][j];
                vertex.m_Color0 = glm::vec4(color0.r, color0.g, color0.b, color0.a);
            }
            else
                vertex.m_Color0 = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);

            vertices.push_back(vertex);
        }

        if (aMesh->HasFaces())
        {
            // Grab the indices for the mesh.
            for (unsigned int j = 0; j < aMesh->mNumFaces; j++)
            {
                aiFace face = aMesh->mFaces[j];

                for (unsigned int k = 0; k < face.mNumIndices; k++)
                    indices.push_back(face.mIndices[k]);
            }
        }

        m_Meshes.push_back(Mesh(m_Program, vertices, indices));
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
