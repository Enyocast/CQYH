#include <stdio.h>
#include <string.h>
#include <math.h>

#include "RecastNavMesh.h"

#include "Recast.h"
#include "RecastLog.h"
#include "DetourCommon.h"
#include "DetourNavMesh.h"
#include "DetourNavMeshBuilder.h"

#pragma warning(disable:4244)

// recast related structures
rcConfig cfg;
rcHeightfield* solid = NULL;
rcCompactHeightfield* chf = NULL;
rcContourSet* cset = NULL;
rcPolyMesh* polyMesh = NULL;
rcPolyMeshDetail* detailMesh = NULL;
dtNavMesh* detourMesh = NULL;

// addtional data cache
rcConvexArea* areasExcluded = NULL;
int nareasExcluded = 0;
float* vertsSeeds = NULL;
int nvertsSeeds = 0;
float polySearch[3];
int polyMaxHeight;

void rcConvexArea::DeepCopy(const rcConvexArea& srcArea)
{
	nverts = srcArea.nverts;
	minh = srcArea.minh;
	maxh = srcArea.maxh;
	
	if (srcArea.nverts > 0)
	{
		verts = new float[3 * srcArea.nverts];
		memcpy(verts, srcArea.verts, sizeof(float) * 3 * nverts);
	}
	else
	{
		verts = NULL;
	}
}

rcConvexArea& rcConvexArea::operator=(const rcConvexArea& p)
{
	if (this != &p)
		DeepCopy(p);

	return *this;
}

void rcSetupGeneration(const float cellSize, const float cellHeight,
					   const float agentMinHeight, const float agentMaxHeight,
					   const float agentMaxSlope, const float agentMaxClimb)
{
	memset(&cfg, 0, sizeof(cfg));
	cfg.cs = cellSize;
	cfg.ch = cellHeight;
	cfg.walkableSlopeAngle = agentMaxSlope;
	cfg.walkableHeight = (int)ceilf(agentMinHeight / cellHeight);
	cfg.walkableClimb = (int)ceilf(agentMaxClimb / cellHeight);
	cfg.walkableRadius = 0;
	cfg.maxEdgeLen = (int)(1200.0f / cellSize);
	cfg.maxSimplificationError = 1.3f;
	// minRegionSize and mergeRegionSize are expressed in voxels
	cfg.minRegionSize = (int)rcSqr(0);
	cfg.mergeRegionSize = (int)rcSqr(20.0f);
	cfg.maxVertsPerPoly = (int)MAX_VERTS_PER_POLY;
	cfg.detailSampleDist = 600.0f;
	cfg.detailSampleMaxError = 1.0f;
	polyMaxHeight = (int)ceilf(agentMaxHeight / cellHeight);
}

bool rcBuildConvexArea(const float* verts, const int nverts, rcConvexArea& area)
{
	memset(&area, 0, sizeof(rcConvexArea));
	if (nverts == 0)
	{
		return false;
	}

	area.verts = new float[3 * nverts];
	if (area.verts == NULL)
	{
		return false;
	}

	area.nverts = nverts;
	area.minh = verts[2];
	area.maxh = verts[2];
	
	for (int i = 0; i < nverts; i++)
	{
		area.verts[i * 3 + 0] = -verts[i * 3 + 0];
		area.verts[i * 3 + 1] = 0.0f;
		area.verts[i * 3 + 2] = -verts[i * 3 + 1];

		if (area.minh > verts[i * 3 + 2]) area.minh = verts[i * 3 + 2];
		if (area.maxh < verts[i * 3 + 2]) area.maxh = verts[i * 3 + 2];
	}

	return true;
}

bool rcAddExcludedAreas(const rcConvexArea* areas, const int nareas)
{
	areasExcluded = new rcConvexArea[nareas];
	if (areasExcluded == NULL)
	{
		nareasExcluded = 0;
		return false;
	}

	nareasExcluded = nareas;
	for (int i = 0; i < nareas; i++)
	{
		areasExcluded[i] = areas[i];
	}

	return true;
}

bool rcAddWalkableSeeds(const float* verts, const int nverts, const float* polySearchExtent)
{
	vertsSeeds = new float[3 * nverts];
	if (vertsSeeds == NULL)
	{
		nvertsSeeds = 0;
		return false;
	}

	nvertsSeeds = nverts;
	for (int i = 0; i < nverts; i++)
	{
		vertsSeeds[i * 3 + 0] = -verts[i * 3 + 0];
		vertsSeeds[i * 3 + 1] =  verts[i * 3 + 2];
		vertsSeeds[i * 3 + 2] = -verts[i * 3 + 1];
	}

	polySearch[0] = polySearchExtent[0];
	polySearch[1] = polySearchExtent[2];
	polySearch[2] = polySearchExtent[1];
	return true;
}

void rcApplyHeightSpanFilter(rcHeightfield& solid, const rcFilterWalkableSpan FilterFunc, void* spanFilterContext)
{
	const int w = solid.width;
	const int h = solid.height;
	for (int y = 0; y < h; ++y)
	{
		for (int x = 0; x < w; ++x)
		{
			bool hasWalkableSpan = false;
			for (rcSpan* s = solid.spans[x + y*w]; s; s = s->next)
			{
				if ((s->flags & RC_WALKABLE) != 0)
				{
					hasWalkableSpan = true;
					break;
				}
			}

			if (hasWalkableSpan &&
				!FilterFunc(-(solid.bmin[0] + (x + 0.5f) * solid.cs), -(solid.bmin[2] + (y + 0.5f) * solid.cs), solid.bmin[1], solid.bmax[1], spanFilterContext))
			{
				for (rcSpan* s = solid.spans[x + y*w]; s; s = s->next)
				{
					s->flags &= ~RC_WALKABLE;
				}
			}
		}
	}
}

void rcFloodFillWalkableSeeds()
{
	dtQueryFilter dummyFilter;
	rcIntArray* openSet = new rcIntArray();

	for (int i = 0; i < nvertsSeeds; i++)
	{
		dtPolyRef polyRef = detourMesh->findNearestPoly(&vertsSeeds[i * 3], polySearch, &dummyFilter, NULL);
		if (polyRef > 0)
		{
			unsigned int PolyIdx, DummyInt;
			detourMesh->decodePolyId(polyRef, DummyInt, DummyInt, PolyIdx);
			openSet->push(PolyIdx);
		}
	}

	while (openSet->size() > 0)
	{
		rcIntArray* nextSet = new rcIntArray();

		for (int i = 0; i < openSet->size(); i++)
		{
			int OpenPoly = (*openSet)[i];
			polyMesh->flags[OpenPoly] = 0;

			const unsigned short* src = &polyMesh->polys[OpenPoly*polyMesh->nvp*2];
			for (int iv = 0; iv < polyMesh->nvp; iv++)
			{
				int neighbourPoly = src[iv + polyMesh->nvp];
				if (neighbourPoly != RC_MESH_NULL_IDX &&
					polyMesh->flags[neighbourPoly] != 0)
				{
					nextSet->push(neighbourPoly);
				}
			}			
		}

		delete openSet;
		openSet = nextSet;
	}

	delete openSet;
}

void rcFillHeightAreas(rcCompactHeightfield& chf, unsigned char maxHeight)
{
	for (int z = 0; z < chf.height; ++z)
	{
		for (int x = 0; x < chf.width; ++x)
		{
			const rcCompactCell& c = chf.cells[x+z*chf.width];
			for (int i = (int)c.index, ni = (int)(c.index+c.count); i < ni; ++i)
			{
				rcCompactSpan& s = chf.spans[i];
				chf.areas[i] = (s.h > maxHeight) ? maxHeight : s.h;
			}
		}
	}
}

bool rcGenerateInternal(const float* verts, const int nverts,
						const int* faces, const int nfaces,
						const rcFilterWalkableSpan spanFilter, void* spanFilterContext)
{
	// 
	// Step 1. Calculate bounds
	//

	rcCalcBounds(verts, nverts, cfg.bmin, cfg.bmax);

	// expand a bit to get generation as close to level edges as possible (important for connecting dynamic sections)
	cfg.bmax[0] += cfg.cs;
	cfg.bmax[2] += cfg.cs;

	rcCalcGridSize(cfg.bmin, cfg.bmax, cfg.cs, &cfg.width, &cfg.height);

	cfg.borderSize = 0;	
	cfg.tileSize = 0;

	//
	// Step 2. Rasterize input polygon soup.
	//

	// Allocate voxel heighfield where we rasterize our input data to.
	solid = new rcHeightfield;
	if (!solid ||
		!rcCreateHeightfield(*solid, cfg.width, cfg.height, cfg.bmin, cfg.bmax, cfg.cs, cfg.ch))
	{
		return false;
	}

	// Allocate array that can hold triangle flags.
	// If you have multiple meshes you need to process, allocate
	// and array which can hold the max number of triangles you need to process.
	unsigned char* triflags = new unsigned char[nfaces];
	if (!triflags)
	{
		return false;
	}

	// Find triangles which are walkable based on their slope and rasterize them.
	// If your input data is multiple meshes, you can transform them here, calculate
	// the flags for each of the meshes and rasterize them.
	memset(triflags, 0, nfaces*sizeof(unsigned char));
	rcMarkWalkableTriangles(cfg.walkableSlopeAngle, verts, nverts, faces, nfaces, triflags);
	rcRasterizeTriangles(verts, nverts, faces, triflags, nfaces, *solid, cfg.walkableClimb);

	delete [] triflags;
	triflags = 0;

	//
	// Step 3. Filter walkables surfaces.
	//

	// Geometry import have problems with clipping static meshes into defined bounds.
	// Reject voxels outside generation boundaries
	rcApplyHeightSpanFilter(*solid, spanFilter, spanFilterContext);

	// Once all geoemtry is rasterized, we do initial pass of filtering to
	// remove unwanted overhangs caused by the conservative rasterization
	// as well as filter spans where the character cannot possibly stand.
	rcFilterLowHangingWalkableObstacles(cfg.walkableClimb, *solid);
	rcFilterLedgeSpans(cfg.walkableHeight, cfg.walkableClimb, *solid);
	rcFilterWalkableLowHeightSpans(cfg.walkableHeight, *solid);

	//
	// Step 4. Partition walkable surface to simple regions.
	//

	// Compact the heightfield so that it is faster to handle from now on.
	// This will result more cache coherent data as well as the neighbours
	// between walkable cells will be calculated.
	chf = new rcCompactHeightfield;
	if (!chf ||
		!rcBuildCompactHeightfield(cfg.walkableHeight, cfg.walkableClimb, RC_WALKABLE, *solid, *chf))
	{
		return false;
	}

	// Encode available height in area code
	rcFillHeightAreas(*chf, polyMaxHeight);

	// (Optional) Mark areas.
	for (int i = 0; i < nareasExcluded; ++i)
		rcMarkConvexPolyArea(areasExcluded[i].verts, areasExcluded[i].nverts, areasExcluded[i].minh, areasExcluded[i].maxh, RC_NULL_AREA, *chf);

	// Prepare for region partitioning, by calculating distance field along the walkable surface.
	if (!rcBuildDistanceField(*chf))
	{
		return false;
	}

	// Partition the walkable surface into simple regions without holes.
	if (!rcBuildRegions(*chf, cfg.borderSize, cfg.minRegionSize, cfg.mergeRegionSize))
	{
		return false;
	}

	//
	// Step 5. Trace and simplify region contours.
	//

	// Create contours.
	cset = new rcContourSet;
	if (!cset||
		!rcBuildContours(*chf, cfg.maxSimplificationError, cfg.maxEdgeLen, *cset))
	{
		return false;
	}

	//
	// Step 6. Build polygons mesh from contours.
	//

	// Build polygon navmesh from the contours.
	polyMesh = new rcPolyMesh;
	if (!polyMesh ||
		!rcBuildPolyMesh(*cset, cfg.maxVertsPerPoly, *polyMesh))
	{
		return false;
	}

	//
	// (Optional) Step 7. Create detail mesh which allows to access approximate height on each polygon.
	//					  Required for detour mesh used only for finding nearby poly

	detailMesh = new rcPolyMeshDetail;
	if (!detailMesh ||
		!rcBuildPolyMeshDetail(*polyMesh, *chf, cfg.detailSampleDist, cfg.detailSampleMaxError, *detailMesh))
	{
		return false;
	}

	//
	// (Optional) Step 8. Create Detour data from Recast poly mesh.
	//

	// fill flags, or else detour won't be able to find polygons
	memset(polyMesh->flags, 0xff, sizeof(polyMesh->flags[0]) * polyMesh->npolys);

	dtNavMeshCreateParams params;
	memset(&params, 0, sizeof(params));
	params.verts = polyMesh->verts;
	params.vertCount = polyMesh->nverts;
	params.polys = polyMesh->polys;
	params.polyAreas = polyMesh->areas;
	params.polyFlags = polyMesh->flags;
	params.polyCount = polyMesh->npolys;
	params.nvp = polyMesh->nvp;
	params.detailMeshes = detailMesh->meshes;
	params.detailVerts = detailMesh->verts;
	params.detailVertsCount = detailMesh->nverts;
	params.detailTris = detailMesh->tris;
	params.detailTriCount = detailMesh->ntris;
	params.walkableHeight = (float)cfg.walkableHeight;
	params.walkableRadius = (float)cfg.walkableRadius;
	params.walkableClimb = (float)cfg.walkableClimb;
	rcVcopy(params.bmin, polyMesh->bmin);
	rcVcopy(params.bmax, polyMesh->bmax);
	params.cs = cfg.cs;
	params.ch = cfg.ch;

	unsigned char* navData = 0;
	int navDataSize = 0;

	if (!dtCreateNavMeshData(&params, &navData, &navDataSize))
	{
		return false;
	}

	detourMesh = new dtNavMesh;
	if (!detourMesh ||
		!detourMesh->init(navData, navDataSize, DT_TILE_FREE_DATA, 2048))
	{
		return false;
	}

	return true;
}

bool findLedgeOnTheSameLevel(int& px, int& pz, unsigned int py)
{
	bool bFound = false;
	int dpx[] = { 0, -1, 1, -1, 0, 1, -1, 0, 1 };
	int dpz[] = { 0, 0, 0, -1, -1, -1, 1, 1, 1 };

	// search in closest neighbourhood 3x3
	for (int i = 0; i < 9; i++)
	{
		if (px + dpx[i] >= solid->width || px + dpx[i] < 0 ||
			pz + dpz[i] >= solid->height || pz + dpz[i] < 0)
		{
			continue;
		}

		for (rcSpan* testSpan = solid->spans[px + dpx[i] + (pz + dpz[i]) * solid->width]; testSpan != NULL; testSpan = testSpan->next)
		{
			unsigned int bot = testSpan->smax;
			unsigned int top = (testSpan->next) ? testSpan->next->smin : 0xffff;
			if (bot <= py && top >= py)
			{
				if (testSpan->flags & RC_LEDGE)
				{
					px += dpx[i];
					pz += dpz[i];
					return true;
				}
			}
		}
	}

	return false;
}

bool rcSampleDropDownLink(const float* point, const float* direction, float& dropHeight)
{
	int px = point[0] / cfg.cs;
	int pz = point[2] / cfg.cs;
	unsigned int py = point[1] / cfg.ch;

	// adjust cell to nearby ledge
	if (!findLedgeOnTheSameLevel(px, pz, py))
		return false;

	// find walkable span below, offset in given direction
	px += direction[0] * 1;
	pz += direction[2] * 1;
	if (px >= solid->width || pz >= solid->height || px < 0 || pz < 0)
		return false;

	for (rcSpan* testSpan = solid->spans[px + pz * solid->width]; testSpan != NULL; testSpan = testSpan->next)
	{
		unsigned int bot = testSpan->smax;
		unsigned int top = (testSpan->next) ? testSpan->next->smin : 0xffff;
		if (bot <= py && top >= py + cfg.walkableHeight &&
			(testSpan->flags & RC_WALKABLE))
		{
			dropHeight = (py - bot) * cfg.ch;
			return true;
		}
	}

	return false;
}

void rcGatherDropDownLinks(float*& vertsDropDown, int& nvertsDropDown)
{
	// allocate memory for all possible dropdown places: edges without a neightbour in all walkable polys
	int nPossibleLinks = 0;
	for (int i = 0; i < polyMesh->npolys; i++)
	{
		if (polyMesh->flags[i] != 0)
			continue;
		
		const unsigned short* srcPoly = &polyMesh->polys[i*cfg.maxVertsPerPoly*2];
		for (int iv = 0; iv < cfg.maxVertsPerPoly; iv++)
		{
			if (srcPoly[iv + cfg.maxVertsPerPoly] == RC_MESH_NULL_IDX &&
				srcPoly[iv] != RC_MESH_NULL_IDX)
			{
				nPossibleLinks++;
			}
		}
	}

	vertsDropDown = new float[nPossibleLinks*4];
	nvertsDropDown = 0;

	// for every walkable polygon 
	for (int i = 0; i < polyMesh->npolys; i++)
	{
		if (polyMesh->flags[i] != 0)
			continue;

		const unsigned short* srcPoly = &polyMesh->polys[i*cfg.maxVertsPerPoly*2];

		// get center point (relative to bounds, no point in wasting time for adding offset to every coord)
		int nPolyVerts = 0;
		float centerPoint[3] = { 0 };
		for (int iv = 0; iv < cfg.maxVertsPerPoly; iv++)
		{
			if (srcPoly[iv] != RC_MESH_NULL_IDX)
			{
				float vertPos[3];
				vertPos[0] = polyMesh->verts[srcPoly[iv] * 3 + 0] * cfg.cs;
				vertPos[1] = polyMesh->verts[srcPoly[iv] * 3 + 1] * cfg.ch;
				vertPos[2] = polyMesh->verts[srcPoly[iv] * 3 + 2] * cfg.cs;
				rcVadd(centerPoint, centerPoint, vertPos);
				nPolyVerts++;
			}
		}
		centerPoint[0] *= 1.0f / nPolyVerts;
		centerPoint[1] *= 1.0f / nPolyVerts;
		centerPoint[2] *= 1.0f / nPolyVerts;

		// for every edge without neighbour
		for (int iv = 0; iv < cfg.maxVertsPerPoly; iv++)
		{
			if (srcPoly[iv + cfg.maxVertsPerPoly] == RC_MESH_NULL_IDX &&
				srcPoly[iv] != RC_MESH_NULL_IDX)
			{
				unsigned short v0 = srcPoly[iv];
				unsigned short v1 = (srcPoly[iv + 1] == RC_MESH_NULL_IDX) ? srcPoly[0] : srcPoly[iv + 1];
				if (v0 != v1)
				{
					float v0Pos[3], v1Pos[3], dv[3];
					v0Pos[0] = polyMesh->verts[v0 * 3 + 0] * cfg.cs;
					v0Pos[1] = polyMesh->verts[v0 * 3 + 1] * cfg.ch;
					v0Pos[2] = polyMesh->verts[v0 * 3 + 2] * cfg.cs;
					v1Pos[0] = polyMesh->verts[v1 * 3 + 0] * cfg.cs;
					v1Pos[1] = polyMesh->verts[v1 * 3 + 1] * cfg.ch;
					v1Pos[2] = polyMesh->verts[v1 * 3 + 2] * cfg.cs;
					rcVsub(dv, v1Pos, v0Pos);

					// calc dropdown direction
					float dropDir[3] = { 0 };
					if (abs(dv[0]) > abs(dv[2]))
					{
						dropDir[2]= (((v0Pos[2] + v1Pos[2]) * 0.5) > centerPoint[2]) ? 1 : -1;
					}
					else
					{
						dropDir[0]= (((v0Pos[0] + v1Pos[0]) * 0.5) > centerPoint[0]) ? 1 : -1;
					}

					// prepare samples
					float edgeLen = rcVdist(v0Pos, v1Pos);
					int nSamples = rcMin(2, 1 + (int)(edgeLen / (4 * cfg.cs)));
					
					float sPos[3];
					rcVcopy(sPos, v0Pos);

					// test samples
					bool bSamplePassed = false;
					float minDropHeight = 0;
					for (int is = 0; is < nSamples; is++)
					{
						float dropHeight = 0;
						
						bSamplePassed = rcSampleDropDownLink(sPos, dropDir, dropHeight);
						if (!bSamplePassed) break;

						if (is == 0 || minDropHeight > dropHeight)
							minDropHeight = dropHeight;

						rcVmad(sPos, sPos, dv, 1.0f / (nSamples - 1));						
					}

					// save drop down place, use UE3 coord system
					if (bSamplePassed)
					{
						float edgeMidPoint[3];
						rcVmad(edgeMidPoint, v0Pos, dv, 0.5f);
						rcVadd(edgeMidPoint, edgeMidPoint, cfg.bmin);
						rcVmad(edgeMidPoint, edgeMidPoint, dropDir, cfg.cs * 0.5f);
						
						vertsDropDown[nvertsDropDown * 4 + 0] = -edgeMidPoint[0];
						vertsDropDown[nvertsDropDown * 4 + 1] = -edgeMidPoint[2];
						vertsDropDown[nvertsDropDown * 4 + 2] =  edgeMidPoint[1];
						vertsDropDown[nvertsDropDown * 4 + 3] = minDropHeight;
						nvertsDropDown++;
					}
				}
			}
		}
	}
}

bool rcGenerateNavMesh(const float* verts, const int nverts,
					   const int* faces, const int nfaces,
					   const rcFilterWalkableSpan spanFilter, void* spanFilterContext,
					   float*& vertsNavMesh, int& nvertsNavMesh,
					   rcNavMeshPoly*& polysNavMesh, int& npolysNavMesh,
					   float*& vertsDropDown, int& nvertsDropDown)
{
	bool bRet = false;

	if (nverts > 0 &&
		rcGenerateInternal(verts, nverts, faces, nfaces, spanFilter, spanFilterContext))
	{
		// mark polys inaccessible from seeds
		rcFloodFillWalkableSeeds();

		// sample edges for drop down links
		rcGatherDropDownLinks(vertsDropDown, nvertsDropDown);

		// prepare verts in UE3 coords
		vertsNavMesh = new float[3 * polyMesh->nverts];
		nvertsNavMesh = polyMesh->nverts;
		for (int i = 0; i < nvertsNavMesh; i++)
		{
			vertsNavMesh[i * 3 + 0] = -(polyMesh->bmin[0] + polyMesh->verts[i * 3 + 0] * cfg.cs);
			vertsNavMesh[i * 3 + 1] = -(polyMesh->bmin[2] + polyMesh->verts[i * 3 + 2] * cfg.cs);
			vertsNavMesh[i * 3 + 2] =  (polyMesh->bmin[1] + polyMesh->verts[i * 3 + 1] * cfg.ch);
		}

		// prepare polys
		polysNavMesh = new rcNavMeshPoly[polyMesh->npolys];
		npolysNavMesh = 0;
		for (int i = 0; i < polyMesh->npolys; i++)
		{
			if (polyMesh->flags[i] != 0)
				continue;
			
			polysNavMesh[npolysNavMesh].height = cfg.ch * polyMesh->areas[i];
			polysNavMesh[npolysNavMesh].isBorderPoly = false;

			int numVerts = 0;
			const unsigned short* srcPoly = &polyMesh->polys[i*cfg.maxVertsPerPoly*2];
			for (int iv = 0; iv < cfg.maxVertsPerPoly; iv++)
			{
				if (srcPoly[iv] != RC_MESH_NULL_IDX) numVerts++;
				polysNavMesh[npolysNavMesh].verts[iv] = -1;
			}

			for (int iv = 0; iv < numVerts; iv++)
			{
				if (srcPoly[iv + cfg.maxVertsPerPoly] == RC_MESH_NULL_IDX)
				{
					polysNavMesh[npolysNavMesh].isBorderPoly = true;
				}

				polysNavMesh[npolysNavMesh].verts[numVerts - iv -1] = srcPoly[iv];
			}

			npolysNavMesh++;
		}

		bRet = true;
	}

	delete solid; solid = NULL;
	delete chf; chf = NULL;
	delete cset; cset = NULL;
	delete polyMesh; polyMesh = NULL;
	delete detailMesh; detailMesh = NULL;
	delete detourMesh; detourMesh = NULL;
	delete[] areasExcluded; areasExcluded = NULL;
	delete[] vertsSeeds; vertsSeeds = NULL;
	nareasExcluded = 0;
	nvertsSeeds = 0;

	return bRet;
}
