#ifndef NVMESH_H
#define NVMESH_H

#include <vector>

template <class T>
struct myvect2
{
    T& operator [] (int i)
    { return vector[i]; }
    const T& operator[](int i) const
    { return vector[i]; }
    inline myvect2()
    { }
    inline myvect2(T _x, T _y)
    { vector[0] = _x; vector[1] = _y; }
    inline bool operator == (const myvect2<T> &v) const
    { return vector[0] == v[0] && vector[1] == v[1]; }
    inline bool operator != (const myvect2<T> &v) const
    { return vector[0] != v[0] || vector[1] != v[1]; }
    inline myvect2 operator * (const double s) const
    { return myvect2((T)(vector[0] * s), (T)(vector[1] * s)); }
    inline myvect2 operator + (const myvect2 &v) const
    { return myvect2((T)(vector[0] + v[0]), (T)(vector[1] + v[1])); }
    inline myvect2 operator - (const myvect2 &v) const
    { return myvect2((T)(vector[0] - v[0]), (T)(vector[1] - v[1])); }
    inline myvect2<T> &operator +=(const myvect2<T> &v)
    {
        vector[0] += (T)v[0]; vector[1] += (T)v[1];
        return *this;
    }

    T vector[2];
};

typedef myvect2<float> float2;
typedef myvect2<int> int2;

template <class T>
struct myvect3
{
    T& operator [] (int i)
    { return vector[i]; }
    const T& operator[](int i) const
    { return vector[i]; }
    inline myvect3()
    { }
    inline myvect3(T _x, T _y, T _z)
    { vector[0] = _x; vector[1] = _y; vector[2] = _z; }
    inline bool operator == (const myvect3<T> &v) const
    { return vector[0] == v[0] && vector[1] == v[1] && vector[2] == v[2]; }
    inline bool operator != (const myvect3<T> &v) const
    { return vector[0] != v[0] || vector[1] != v[1] || || vector[2] != v[2]; }
    inline myvect3 operator * (const double s) const
    { return myvect3((T)(vector[0] * s), (T)(vector[1] * s), (T)(vector[2] * s)); }
    inline myvect3 operator + (const myvect3 &v) const
    { return myvect3((T)(vector[0] + v[0]), (T)(vector[1] + v[1]), (T)(vector[2] + v[2])); }
    inline myvect3 operator - (const myvect3 &v) const
    { return myvect3((T)(vector[0] - v[0]), (T)(vector[1] - v[1]), (T)(vector[2] - v[2])); }
    inline myvect3<T> &operator +=(const myvect3<T> &v)
    {
        vector[0] += (T)v[0]; vector[1] += (T)v[1]; vector[2] += (T)v[2];
        return *this;
    }
    inline void operator /= (const double s)
    {
        vector[0] /= (T)s; vector[1] /= (T)s; vector[2] /= (T)s;
        return;
    }

    T vector[3];
};

typedef myvect3<float> float3;

template <class T>
inline double dot(const myvect2<T> &v1, const myvect2<T> &v2)
{
    return v1[0] * v2[0] + v1[1] * v2[1];
}

template <class T>
inline double dot(const myvect3<T> &v1, const myvect3<T> &v2)
{
    return v1[0] * v2[0] + v1[1] * v2[1] + v1[2] * v2[2];
}

template <class T>
inline myvect3<T> normalize(const myvect3<T> &_v)
{
    myvect3<T> v = _v;
    double lensqr = dot(v, v);
    if (lensqr > 0) {
        v /= sqrt(lensqr);
    }
    return v;
}

template <class T>
inline myvect3<T> cross(const myvect3<T> &a, const myvect3<T> &b)
{
    return myvect3<T>(a[1] * b[2] - a[2] * b[1], a[2] * b[0] - a[0] * b[2], a[0] * b[1] - a[1] * b[0]);
}

struct Adjacency
{
    inline Adjacency(std::vector<unsigned int>& indices, std::vector<float3>& positions) :
        m_Indices(indices),
        m_Positions(positions),
        m_PackedVerticesNum(0)
    { }

    std::vector<unsigned int>&  m_Indices;
    std::vector<float3>&        m_Positions;

    std::vector<unsigned int>   m_AdjIndices;
    std::vector<int>            m_FacesPerVertex;
    std::vector<int>            m_FacesCollected;
    std::vector<unsigned int>   m_AdjacencyFaces;
    std::vector<unsigned int>   m_PackedIndices;
    std::vector<unsigned int>   m_VertsRecode;

    unsigned int                m_PackedVerticesNum;

    void GenerateAdjacencyInfo();
    unsigned int GeneratePackedPosIndices();
};

#endif // NVMESH_H