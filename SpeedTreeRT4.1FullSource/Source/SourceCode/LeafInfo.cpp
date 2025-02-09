///////////////////////////////////////////////////////////////////////  
//  LeafInfo.cpp
//
//  *** INTERACTIVE DATA VISUALIZATION (IDV) CONFIDENTIAL AND PROPRIETARY INFORMATION ***
//
//  This software is supplied under the terms of a license agreement or
//  nondisclosure agreement with Interactive Data Visualization, Inc. and
//  may not be copied, disclosed, or exploited except in accordance with 
//  the terms of that agreement.
//
//      Copyright (c) 2003-2007 IDV, Inc.
//      All rights reserved in all media.
//
//      IDV, Inc.
//      http://www.idvinc.com

#include "TreeEngine.h"


// constants
const int c_nNumCorners = 4;


///////////////////////////////////////////////////////////////////////  
//  SIdvLeafInfo::SIdvLeafInfo definition

SIdvLeafInfo::SIdvLeafInfo( ) :
    m_bDimming(true),
    m_fDimmingScalar(1.0f),
    m_eCollisionType(SIdvLeafInfo::TREE),
    m_fSpacingTolerance(0.5f),
    m_fPlacementDistance(0.0f),
    m_nPlacementLevel(0),
    m_fBlossomDistance(0.75f),
    m_fBlossomWeighting(0.8f),
    m_nBlossomLevel(1),
    m_nNumRockingGroups(3),
    m_nNumLeafLodLevels(4),
    m_nNumTextures(0),
    m_pLeafVertexes(NULL),
    m_pLeafTexCoords(NULL),
    m_pTimeOffsets(NULL),
    m_bSmoothingEnabled(false),
    m_fSmoothingAngle(30.0f),
    m_nDimmingDepth(1)
{
}


///////////////////////////////////////////////////////////////////////  
//  SIdvLeafInfo::~SIdvLeafInfo definition

SIdvLeafInfo::~SIdvLeafInfo( )
{
    st_delete_array<float>(m_pTimeOffsets, "~SIdvLeafInfo, m_pTimeOffsets");

    if (m_pLeafVertexes)
    {
        for (int i = 0; i < m_nNumLeafLodLevels; ++i)
            st_delete_array<float>(m_pLeafVertexes[i], "~SIdvLeafInfo, m_pLeafVertexes[i]");
        st_delete_array<float*>(m_pLeafVertexes, "~SIdvLeafInfo, m_pLeafVertexes");
    }

    st_delete_array<float>(m_pLeafTexCoords, "~SIdvLeafInfo, m_pLeafTexCoords");
}


///////////////////////////////////////////////////////////////////////  
//  SIdvLeafInfo::InitTables definition

void SIdvLeafInfo::InitTables(int nNumTextures)
{
    m_nNumTextures = nNumTextures;

    // initialize time offsets
    m_pTimeOffsets = st_new_array<float>(m_nNumRockingGroups, "SIdvLeafInfo::InitTables, m_pTimeOffsets");
    stRandom cDice;
    int i = 0; // declared outside of the for-scope for portability
    for (i = 0; i < m_nNumRockingGroups; ++i)
        m_pTimeOffsets[i] = cDice.GetUniform(0.0, 10000.0);

    m_pLeafTexCoords = st_new_array<float>(4 * 2 * 2 * nNumTextures, "SIdvLeafInfo::InitTables, m_pLeafTexCoords");
    float* pTexCoord = m_pLeafTexCoords;

    // initialize values to something reasonable
    const float c_fFlip = CSpeedTreeRT::GetTextureFlip( ) ? -1.0f : 1.0f;
    for (i = 0; i < 2 * nNumTextures; ++i)
    {
        *pTexCoord++ = 0.0f;
        *pTexCoord++ = c_fFlip;
        *pTexCoord++ = c_fFlip;
        *pTexCoord++ = c_fFlip;
        *pTexCoord++ = c_fFlip;
        *pTexCoord++ = 0.0f;
        *pTexCoord++ = 0.0f;
        *pTexCoord++ = 0.0f;
    }

    // allocate billboarded array, one for each LOD
    m_pLeafVertexes = st_new_array<float*>(m_nNumLeafLodLevels, "SIdvLeafInfo::InitTables, m_pLeafVertexes");

    // quantity of each LOD is determined by
    //     (number of textures) *
    //     (2, for the leaf textures that are vertically flipped) *
    //     (number of unique rocking groups) *
    //     (4, number of corners in one leaf) *
    //     (4, the x, y, z coordinate + one pad for efficient vertex shader use)
    int nTotalSize = (nNumTextures * 2) * m_nNumRockingGroups * (4 * 4);
    for (i = 0; i < m_nNumLeafLodLevels; ++i)
    {
        m_pLeafVertexes[i] = st_new_array<float>(nTotalSize, "SIdvLeafInfo::InitTables, m_pLeafVertexes[i]");
        for (int j = 0; j < nTotalSize; ++j)
            m_pLeafVertexes[i][j] = 0.0f;
    }
}


///////////////////////////////////////////////////////////////////////  
//  SIdvLeafInfo::Parse definition

void SIdvLeafInfo::Parse(CTreeFileAccess& cFile)
{
    int nToken = cFile.ParseToken( );
    do
    {
        switch (nToken)
        {
            case File_Leaf_Blossom_Distance:
                m_fBlossomDistance = cFile.ParseFloat( );
                break;
            case File_Leaf_Blossom_Level:
                m_nBlossomLevel = cFile.ParseInt( );
                m_nDimmingDepth = m_nBlossomLevel;
                break;
            case File_Leaf_Blossom_Weighting:
                m_fBlossomWeighting = cFile.ParseFloat( );
                break;
            case File_Leaf_ColorShift:
                (void) cFile.ParseBool( ); // color shift is no longer used
                break;
            case File_Leaf_ColorShiftScalar:
                (void) cFile.ParseFloat( ); // color shift scalar is no longer used
                break;
            case File_Leaf_Dimming:
                m_bDimming = cFile.ParseBool( );
                break;
            case File_Leaf_DimmingScalar:
                m_fDimmingScalar = cFile.ParseFloat( );
                break;
            case File_Leaf_LightScalar:
                (void) cFile.ParseFloat( ); // light scalar is no longer used
                break;
            case File_Leaf_Lit:
                (void) cFile.ParseBool( ); // leaf lit is no longer used
                break;
            case File_Leaf_SpacingTolerance:
                m_fSpacingTolerance = cFile.ParseFloat( );
                break;
            case File_Leaf_CollisionDetection:
                m_eCollisionType = static_cast<SIdvLeafInfo::ECollisionType>(cFile.ParseInt( ));
                break;
            case File_BeginSingleLeafInfo:
            {
                nToken = cFile.ParseToken( ); // File_LeafLevelCount
                int nCount = cFile.ParseInt( );
                m_vLeafTextures.clear( );
                m_vLeafTextures.resize(nCount);
                for (int i = 0; i < nCount; ++i)
                {
                    SIdvLeafTexture sLeaf;
                    nToken = cFile.ParseToken( ); // skip File_BeginLeafLevel
                    nToken = cFile.ParseToken( );
                    do
                    {
                        switch (nToken)
                        {
                            case File_Leaf_Blossom:
                                sLeaf.m_bBlossom = cFile.ParseBool( );
                                break;
                            case File_Leaf_Color:
                                sLeaf.m_cColor = cFile.ParseVector3( );
                                break;
                            case File_Leaf_ColorVariance:
                                sLeaf.m_fColorVariance = cFile.ParseFloat( );
                                break;
                            case File_Leaf_Filename:
                            {
                                cFile.ParseString(sLeaf.m_strFilename);
                                sLeaf.m_strFilename = IdvNoPath(sLeaf.m_strFilename);
                            }
                                break;
                            case File_Leaf_Origin:
                                sLeaf.m_cOrigin = cFile.ParseVector3( );
                                break;
                            case File_Leaf_Size:
                                sLeaf.m_cSize = cFile.ParseVector3( );
                                break;
                            case File_Leaf_SizeUsed:
                                sLeaf.m_cSizeUsed = cFile.ParseVector3( );
                                break;
                            case File_Leaf_Ratio:
                                static_cast<void>(cFile.ParseFloat( ));
                                break;
                            default:
                                throw(IdvFileError("malformed single leaf information"));
                                break;
                        }
                        nToken = cFile.ParseToken( );
                    } while (nToken != File_EndLeafLevel);

                    m_vLeafTextures[i] = sLeaf;
                }
                nToken = cFile.ParseToken( ); // File_EndLeafInfo
            }
                break;
            default:
                throw(IdvFileError("malformed general leaf information"));
        }
        nToken = cFile.ParseToken( );
    } while (nToken != File_EndGeneralLeafInfo);
}


///////////////////////////////////////////////////////////////////////  
//  SIdvLeafInfo::Save definition

void SIdvLeafInfo::Save(CTreeFileAccess& cFile) const
{
    cFile.SaveToken(File_BeginGeneralLeafInfo);

    cFile.SaveToken(File_Leaf_Blossom_Distance);
    cFile.SaveFloat(m_fBlossomDistance);

    cFile.SaveToken(File_Leaf_Blossom_Level);
    cFile.SaveInt(m_nBlossomLevel);

    cFile.SaveToken(File_Leaf_Blossom_Weighting);
    cFile.SaveFloat(m_fBlossomWeighting);

    cFile.SaveToken(File_Leaf_ColorShift);
    cFile.SaveBool(false); // color shift is no longer used

    cFile.SaveToken(File_Leaf_ColorShiftScalar);
    cFile.SaveFloat(-1.0f); // color shift scalar is no longer used

    cFile.SaveToken(File_Leaf_Dimming);
    cFile.SaveBool(m_bDimming);

    cFile.SaveToken(File_Leaf_DimmingScalar);
    cFile.SaveFloat(m_fDimmingScalar);

    cFile.SaveToken(File_Leaf_LightScalar);
    cFile.SaveFloat(-1.0f); // leaf light scalar is no longer used

    cFile.SaveToken(File_Leaf_Lit);
    cFile.SaveBool(false); // leaf lit is no longer used

    cFile.SaveToken(File_Leaf_SpacingTolerance);
    cFile.SaveFloat(m_fSpacingTolerance);

    cFile.SaveToken(File_Leaf_CollisionDetection);
    cFile.SaveInt(m_eCollisionType);

    // save the individual textures
    cFile.SaveToken(File_BeginSingleLeafInfo);

    cFile.SaveToken(File_LeafLevelCount);
    cFile.SaveInt(int(m_vLeafTextures.size( )));
    for (unsigned int i = 0; i < m_vLeafTextures.size( ); ++i)
    {
        const SIdvLeafTexture& sLeaf = m_vLeafTextures[i];

        cFile.SaveToken(File_BeginLeafLevel);

        cFile.SaveToken(File_Leaf_Blossom);
        cFile.SaveBool(sLeaf.m_bBlossom);

        cFile.SaveToken(File_Leaf_Color);
        cFile.SaveVector3(sLeaf.m_cColor);

        cFile.SaveToken(File_Leaf_ColorVariance);
        cFile.SaveFloat(sLeaf.m_fColorVariance);

        cFile.SaveToken(File_Leaf_Filename);
        cFile.SaveString(sLeaf.m_strFilename);

        cFile.SaveToken(File_Leaf_Origin);
        cFile.SaveVector3(sLeaf.m_cOrigin);

        cFile.SaveToken(File_Leaf_Size);
        cFile.SaveVector3(sLeaf.m_cSize);

        cFile.SaveToken(File_Leaf_SizeUsed);
        cFile.SaveVector3(sLeaf.m_cSizeUsed);

        float fRatio = 1.0f;
        if (sLeaf.m_cSize[0] > 0.0f)
            fRatio = sLeaf.m_cSize[1] / sLeaf.m_cSize[0];
        cFile.SaveToken(File_Leaf_Ratio);
        cFile.SaveFloat(fRatio);

        cFile.SaveToken(File_EndLeafLevel);
    }
    cFile.SaveToken(File_EndSingleLeafInfo);

    cFile.SaveToken(File_EndGeneralLeafInfo);
}
