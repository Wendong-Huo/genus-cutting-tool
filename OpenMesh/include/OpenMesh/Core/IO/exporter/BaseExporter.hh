/* ========================================================================= *
 *                                                                           *
 *                               OpenMesh                                    *
 *           Copyright (c) 2001-2015, RWTH-Aachen University                 *
 *           Department of Computer Graphics and Multimedia                  *
 *                          All rights reserved.                             *
 *                            www.openmesh.org                               *
 *                                                                           *
 *---------------------------------------------------------------------------*
 * This file is part of OpenMesh.                                            *
 *---------------------------------------------------------------------------*
 *                                                                           *
 * Redistribution and use in source and binary forms, with or without        *
 * modification, are permitted provided that the following conditions        *
 * are met:                                                                  *
 *                                                                           *
 * 1. Redistributions of source code must retain the above copyright notice, *
 *    this list of conditions and the following disclaimer.                  *
 *                                                                           *
 * 2. Redistributions in binary form must reproduce the above copyright      *
 *    notice, this list of conditions and the following disclaimer in the    *
 *    documentation and/or other materials provided with the distribution.   *
 *                                                                           *
 * 3. Neither the name of the copyright holder nor the names of its          *
 *    contributors may be used to endorse or promote products derived from   *
 *    this software without specific prior written permission.               *
 *                                                                           *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS       *
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED *
 * TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A           *
 * PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER *
 * OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,  *
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,       *
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR        *
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF    *
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING      *
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS        *
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.              *
 *                                                                           *
 * ========================================================================= */

/*===========================================================================*\
 *                                                                           *
 *   $Revision: 1258 $                                                         *
 *   $Date: 2015-04-28 22:07:46 +0900 (Tue, 28 Apr 2015) $                   *
 *                                                                           *
\*===========================================================================*/


//=============================================================================
//
//  Implements the baseclass for MeshWriter exporter modules
//
//=============================================================================


#ifndef __BASEEXPORTER_HH__
#define __BASEEXPORTER_HH__


//=== INCLUDES ================================================================


// STL
#include <vector>

// OpenMesh
#include <OpenMesh/Core/System/config.h>
#include <OpenMesh/Core/Geometry/VectorT.hh>
#include <OpenMesh/Core/Mesh/BaseKernel.hh>


//=== NAMESPACES ==============================================================


namespace OpenMesh {
namespace IO {


//=== EXPORTER ================================================================


/**
   Base class for exporter modules.
   The exporter modules provide an interface between the writer modules and
   the target data structure.
*/

class OPENMESHDLLEXPORT BaseExporter
{
public:

  virtual ~BaseExporter() { }


  // get vertex data
  virtual Vec3f  point(VertexHandle _vh)    const = 0;
  virtual Vec3f  normal(VertexHandle _vh)   const = 0;
  virtual Vec3uc color(VertexHandle _vh)    const = 0;
  virtual Vec4uc colorA(VertexHandle _vh)   const = 0;
  virtual Vec3ui colori(VertexHandle _vh)    const = 0;
  virtual Vec4ui colorAi(VertexHandle _vh)   const = 0;
  virtual Vec3f colorf(VertexHandle _vh)    const = 0;
  virtual Vec4f colorAf(VertexHandle _vh)   const = 0;
  virtual Vec2f  texcoord(VertexHandle _vh) const = 0;


  // get face data
  virtual unsigned int
  get_vhandles(FaceHandle _fh,
	       std::vector<VertexHandle>& _vhandles) const=0;
  virtual Vec3f  normal(FaceHandle _fh)      const = 0;
  virtual Vec3uc color (FaceHandle _fh)      const = 0;
  virtual Vec4uc colorA(FaceHandle _fh)      const = 0;
  virtual Vec3ui colori(FaceHandle _fh)    const = 0;
  virtual Vec4ui colorAi(FaceHandle _fh)   const = 0;
  virtual Vec3f colorf(FaceHandle _fh)    const = 0;
  virtual Vec4f colorAf(FaceHandle _fh)   const = 0;

  // get edge data
  virtual Vec3uc color(EdgeHandle _eh)    const = 0;
  virtual Vec4uc colorA(EdgeHandle _eh)   const = 0;
  virtual Vec3ui colori(EdgeHandle _eh)    const = 0;
  virtual Vec4ui colorAi(EdgeHandle _eh)   const = 0;
  virtual Vec3f colorf(EdgeHandle _eh)    const = 0;
  virtual Vec4f colorAf(EdgeHandle _eh)   const = 0;

  // get reference to base kernel
  virtual const BaseKernel* kernel() { return 0; }


  // query number of faces, vertices, normals, texcoords
  virtual size_t n_vertices()   const = 0;
  virtual size_t n_faces()      const = 0;
  virtual size_t n_edges()      const = 0;


  // property information
  virtual bool is_triangle_mesh()     const { return false; }
  virtual bool has_vertex_normals()   const { return false; }
  virtual bool has_vertex_colors()    const { return false; }
  virtual bool has_vertex_texcoords() const { return false; }
  virtual bool has_edge_colors()      const { return false; }
  virtual bool has_face_normals()     const { return false; }
  virtual bool has_face_colors()      const { return false; }
};


//=============================================================================
} // namespace IO
} // namespace OpenMesh
//=============================================================================
#endif
//=============================================================================
