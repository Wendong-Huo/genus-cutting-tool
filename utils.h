#pragma once 
#include <Windows.h>
#include <string>
#include "VTK_Header.h"
#include "OpenMesh_Header.h"
#include <DirectXMath.h>
int GetFileName(std::string &filename,LPTSTR dialogTitle,const char* filter,bool save = false);
std::string GetFileExtension(const std::string& FileName);

void vtkPolydata2OpenMesh(vtkPolyData *polydata, OmMesh *mesh);
vtkIdType GetCellID(vtkPolyData *polydata, vtkIdType v1,vtkIdType v2,vtkIdType v3);
vtkIdType GetCellID(vtkPolyData *polydata, OmMesh &mesh , OmMesh::FaceHandle fh);
//bool	  isBoundaryEdge(vtkPolyData *polydata, vtkIdType v1,vtkIdType v2);
vtkSmartPointer<vtkIdList> GetConnectedVertices(vtkSmartPointer<vtkPolyData> mesh, vtkIdType vid);

void CutMesh(OmMesh &mesh, OmMesh::HalfedgeHandle &he0 ,OmMesh::HalfedgeHandle &he1,OmMesh::VertexHandle newVH);


float Cal3DTriangleArea(
    const DirectX::XMFLOAT3* pv0,
    const DirectX::XMFLOAT3* pv1,
    const DirectX::XMFLOAT3* pv2);

float CalFaceGeoL2SquraedStretch(
	const float f_area3d,
	const DirectX::XMFLOAT3 *pFace,
    const DirectX::XMFLOAT2& v0,
    const DirectX::XMFLOAT2& v1,
    const DirectX::XMFLOAT2& v2,
    float& f2D);