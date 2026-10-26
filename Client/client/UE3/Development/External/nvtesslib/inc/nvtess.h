
#ifndef NVTESS_H
#define NVTESS_H

// NVCHANGE_BEGIN_JC
#include "nvmesh.h"
// NVCHANGE_END_JC

namespace nv {
    enum DestBufferMode
    {
        /** 
        This buffer contains dominant Edge and Corner Information for each vertex,
        suitable for performing crack-free displacement mapping on top of flat tessellation.
        */
        DBM_DominantEdgeAndCorner = 0,

        /** 
        This buffer contains indices needed to use with PN-AEN, but does not contain
        information to support crack-free displacement mapping.
        */
        DBM_PnAenOnly = 1,

        /**
        This buffer contains PN-AEN information along with dominant corner information. This
        information is sufficient to perform crack-free displacement mapping
        */
        DBM_PnAenDominantCorner = 2,

        /**
        This buffer contains PN-AEN information along with dominant corner and edge information.
        Although dominant edges can be inferred from PN-AEN information alone (making this mode 
        somewhat bloated compared to DBM_PnAenDominantCorner), it does remove the need for some
        computation in the Hull Shader.
        */
        DBM_PnAenDominantEdgeAndCorner = 3,

        DestBufferMode_MAX
    };

    enum IndexBufferType
    {
        IBT_U16,  // 16-bit indices
        IBT_U32,  // 32-bit indices

        IndexBufferType_MAX
    };

    struct Vector3
    {
        float x, y, z;

        inline bool operator==(const Vector3& rhs) const { return x == rhs.x && y == rhs.y && z == rhs.z; }
        inline bool operator<(const Vector3& rhs) const { return  x < rhs.x || y < rhs.y || z < rhs.z; }
    };

	struct Vector2
    {
        float x, y;

        inline bool operator==(const Vector2& rhs) const { return x == rhs.x && y == rhs.y; }
		inline bool operator<(const Vector2& rhs) const { return x < rhs.x || (x == rhs.x && y < rhs.y); }
    };

    struct Vertex
    {
        nv::Vector3 pos;
		nv::Vector2 uv;

        inline bool operator==(const Vertex& rhs) const { return pos == rhs.pos; }
        inline bool operator<(const Vertex& rhs) const { return pos < rhs.pos; }
    };

    /**
    This is a simple wrapper class around an index buffer. The index buffer must contain triangle lists,
    strips are not currently supported. This class will be used to pass index buffers into the library 
    as well as be used for the mechanism to return the created indices back to the application.

    The IndexBuffer class can either own the specified void* pointer (it will be freed by calling delete),
    or the application can indicate that it will retain ownership.
    */
    class IndexBuffer
    {
    private:
        void* mBufferContents;
        IndexBufferType mIbType;
        unsigned int mLength;
        bool mBufferOwner;

    public:
        IndexBuffer(void* bufferContents, IndexBufferType ibtype, unsigned int length, bool bufferOwner);
        ~IndexBuffer();

        inline IndexBufferType getType() const { return mIbType; }
        inline unsigned int getLength() const { return mLength; }
        unsigned int operator[](unsigned int index) const; 
    };

    class RenderBuffer
    {
    protected:
        IndexBuffer* mIb;

    public:
        inline virtual ~RenderBuffer() { delete mIb; }

        /** Return the vertex information at the specified index. */
        virtual nv::Vertex getVertex(unsigned int index) const = 0;

        const IndexBuffer* getIb() const { return mIb; }
    };

// NVCHANGE_BEGIN_JC
    #ifndef SAFE_DELETE
    #define SAFE_DELETE(p)       { if (p) { delete (p);     (p)=0; } }
    #endif
    #ifndef SAFE_DELETE_ARRAY
    #define SAFE_DELETE_ARRAY(p) { if (p) { delete[] (p);   (p)=0; } }
    #endif

    template <class T>
    class GenericBuffer
    {
        private:
        void* mBufferContents;
        int mElementCount;
        bool mBufferOwner;

    public:
        GenericBuffer(void* bufferContents, int elementCount, bool bufferOwner) :
            mBufferContents(bufferContents),
            mElementCount(elementCount),
            mBufferOwner(bufferOwner)
        { }
        ~GenericBuffer()
        { 
            if (mBufferOwner)
            {
                SAFE_DELETE_ARRAY(mBufferContents);
            }

            mBufferContents = 0;
        }

        inline unsigned int getElementSize() const { return sizeof(T); }
        inline unsigned int getElementCount() const { return mElementCount; }
        void* GetData() const { return mBufferContents; }
    };

    typedef GenericBuffer<float2>   BarycentricsBuffer;
    typedef GenericBuffer<int>      ExpansionsBuffer;
    typedef GenericBuffer<float3>   NormalsBuffer;
    typedef GenericBuffer<float3>   CoordinatesBuffer;

    enum TessellationAttributes
    {
        TA_Barycentrics     =   0x1,
        TA_SmoothNormals    =   0x2,
        TA_Coordinates      =   0x4,
    };

    struct TessellationBuffers
    {
        IndexBuffer*            mIndices;
        BarycentricsBuffer*     mBarycentrics;
        ExpansionsBuffer*       mPatchExpansions;
        NormalsBuffer*          mSmoothNormals;
        CoordinatesBuffer*      mCoordinates;

        int                     mDicingTargetMapWidth;
        int                     mDicingTargetMapHeight;
        int                     mDicingTexelsPerEdge;

        TessellationBuffers() :
            mIndices(0),
            mBarycentrics(0),
            mPatchExpansions(0),
            mSmoothNormals(0),
            mCoordinates(0),
            mDicingTargetMapWidth(0),
            mDicingTargetMapHeight(0),
            mDicingTexelsPerEdge(0)
        { }

        void Release()
        {
            SAFE_DELETE(mIndices);
            SAFE_DELETE(mBarycentrics);
            SAFE_DELETE(mPatchExpansions);
            SAFE_DELETE(mSmoothNormals);
            SAFE_DELETE(mCoordinates);
        }
    };
// NVCHANGE_END_JC

    namespace tess {    
        inline unsigned int getIndicesPerPatch(DestBufferMode destBufferMode)
        {
            switch (destBufferMode) {
                case DBM_DominantEdgeAndCorner:			return 12;
                case DBM_PnAenOnly:						return 9;
                case DBM_PnAenDominantCorner:			return 12;
                case DBM_PnAenDominantEdgeAndCorner:	return 18;
                default: // todo: Error
                    break;
            }

            return 3;
        }

        /** 
        Returns an index buffer suitable for the technique specified by destBufferMode. 

        Ownership of the return buffer belongs to the application and will need to be freed using
        delete.
        @destBufferMode - One of the modes specified in DestBufferMode.
        @completeBuffer - Whether the buffer returned should have all indices. If true, all 
        */
        IndexBuffer* buildTessellationBuffer(const RenderBuffer* inputBuffer, DestBufferMode destBufferMode, bool completeBuffer);

// NVCHANGE_BEGIN_JC
        void buildAdditionalTessellationBuffers(const RenderBuffer* inputBuffer, DestBufferMode destBufferMode, bool completeBuffer, unsigned int attributes, TessellationBuffers& buffers, bool crackFree = true, bool assignOpenEdges = true);
// NVCHANGE_END_JC
    };
};

#endif /* NVTESS_H */
