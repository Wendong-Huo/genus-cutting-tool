#pragma once
#include <OpenMesh/Core/Mesh/TriMesh_ArrayKernelT.hh>


struct MyTraits : public OpenMesh::DefaultTraits
{
  typedef OpenMesh::Vec3d Point; // use double-values points
  VertexAttributes(OpenMesh::Attributes::Status);
  FaceAttributes(OpenMesh::Attributes::Status);
  EdgeAttributes(OpenMesh::Attributes::Status);
};



typedef OpenMesh::TriMesh_ArrayKernelT<MyTraits>  OmMesh;

