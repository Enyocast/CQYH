#include "nvmesh.h"
#include "tsort.hpp"

unsigned int Adjacency::GeneratePackedPosIndices()
{
    static float3 *s_pVertices;
    struct SortedVertex
    {
        inline bool operator <(const SortedVertex &v) const
        {
            float3 &vertex0 = s_pVertices[index];
            float3 &vertex1 = s_pVertices[v.index];

            for (int i=0; i<3; ++i)
            {
                if (vertex0[i] < vertex1[i])
                    return true;
                if (vertex1[i] < vertex0[i])
                    return false;
            }
            return false;
        }
        int index;
    };

    unsigned int verticesNum = (unsigned int)m_Positions.size();
    unsigned int indicesNum = (unsigned int)m_Indices.size();

    std::vector<unsigned int> iSortedVerts;
    iSortedVerts.resize(verticesNum);
    for (unsigned int i=0; i < verticesNum; ++i)
    {
        iSortedVerts[i] = i;
    }

    s_pVertices = &m_Positions[0];
    TSort<SortedVertex>::QSort((SortedVertex*)&iSortedVerts[0], verticesNum);

    m_VertsRecode.resize(verticesNum);
    for (unsigned int i = 0; i < verticesNum; ++i)
    {
        m_VertsRecode[i] = i;
    }

    m_PackedVerticesNum = 1;
    m_PackedIndices.clear();
    m_PackedIndices.push_back(iSortedVerts[0]);
    for (unsigned int i=1; i<verticesNum; ++i)
    {
        if (m_Positions[iSortedVerts[i - 1]] == m_Positions[iSortedVerts[i]])
        {
            m_VertsRecode[iSortedVerts[i]] = m_VertsRecode[iSortedVerts[i - 1]];
        }
        else
        {
            ++m_PackedVerticesNum;
            m_PackedIndices.push_back(iSortedVerts[i]);
        }
    }
    iSortedVerts.clear();

    m_AdjIndices.resize(indicesNum);
    for (unsigned int i=0; i < indicesNum; ++i)
    {
        m_AdjIndices[i] = m_VertsRecode[m_Indices[i]];
    }

    return m_PackedVerticesNum;
}

void Adjacency::GenerateAdjacencyInfo()
{
    unsigned int verticesNum = (unsigned int)m_Positions.size();
    unsigned int indicesNum = (unsigned int)m_Indices.size();

    m_FacesPerVertex.resize(verticesNum, 0);
    for (unsigned int i=0; i<indicesNum; ++i)
    {
        ++m_FacesPerVertex[m_AdjIndices[i]];
    }

    // Calculate prefix sum for the number of faces per vertex
    for (unsigned int i=0; i<verticesNum - 1; ++i)
    {
        m_FacesPerVertex[i+1] += m_FacesPerVertex[i];
    }

    // Collect all face indices per vertex
    m_FacesCollected.resize(verticesNum, 0);
    m_AdjacencyFaces.resize(m_FacesPerVertex[verticesNum-1]);

    // Build list of faces for each vertex
    for (unsigned int i=0; i<indicesNum; ++i)
    {
        unsigned int index = m_AdjIndices[i];
        m_FacesCollected[index]++;
        m_AdjacencyFaces[m_FacesPerVertex[index] - m_FacesCollected[index]] = i;
    }
}