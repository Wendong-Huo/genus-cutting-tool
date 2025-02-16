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
//  Implements the baseclass for IOManager importer modules
//
//=============================================================================


#ifndef __BASEIMPORTER_HH__
#define __BASEIMPORTER_HH__


//=== INCLUDES ================================================================


// STL
#include <vector>

// OpenMesh
#include <OpenMesh/Core/System/config.h>
#include <OpenMesh/Core/Geometry/VectorT.hh>
#include <OpenMesh/Core/Mesh/BaseKernel.hh>


//== NAMESPACES ===============================================================


namespace OpenMesh {
namespace IO {


//=== IMPLEMENTATION ==========================================================


/**  Base class for importer modules. Importer modules provide an
 *   interface between the loader modules and the target data
 *   structure. This is basically a wrapper providing virtual versions
 *   for the required mesh functions.
 */
class OPENMESHDLLEXPORT BaseImporter
{
public:

  // base class needs virtual destructor
  virtual ~BaseImporter() {}


  // add a vertex with coordinate \c _point
  virtual VertexHandle add_vertex(const Vec3f& _point) = 0;

  // add a vertex without coordinate. Use set_point to set the position deferred
  virtual VertexHandle add_vertex() = 0;

  // add a face with indices _indices refering to vertices
  typedef std::vector<VertexHandle> VHandles;
  virtual FaceHandle add_face(const VHandles& _indices) = 0;

  // add texture coordinates per face, _vh references the first texcoord
  virtual void add_face_texcoords( FaceHandle _fh, VertexHandle _vh, const std::vector<Vec2f>& _face_texcoords) = 0;

  // Set the texture index for a face
  virtual void set_face_texindex( FaceHandle _fh, int _texId ) = 0;

  // Set coordinate of the given vertex. Use this function, if you created a vertex without coordinate
  virtual void set_point(VertexHandle _vh, const Vec3f& _point) = 0;

  // set vertex normal
  virtual void set_normal(VertexHandle _vh, const Vec3f& _normal) = 0;

  // set vertex color
  virtual void set_color(VertexHandle _vh, const Vec3uc& _color) = 0;

  // set vertex color
  virtual void set_color(VertexHandle _vh, const Vec4uc& _color) = 0;

  // set vertex color
  virtual void set_color(VertexHandle _vh, const Vec3f& _color) = 0;

  // set vertex color
  virtual void set_color(VertexHandle _vh, const Vec4f& _color) = 0;

  // set vertex texture coordinate
  virtual void set_texcoord(VertexHandle _vh, const Vec2f& _texcoord) = 0;

  // set vertex texture coordinate
  virtual void set_texcoord(HalfedgeHandle _heh, const Vec2f& _texcoord) = 0;

  // set edge color
  virtual void set_color(EdgeHandle _eh, const Vec3uc& _color) = 0;

  // set edge color
  virtual void set_color(EdgeHandle _eh, const Vec4uc& _color) = 0;

  // set edge color
  virtual void set_color(EdgeHandle _eh, const Vec3f& _color) = 0;

  // set edge color
  virtual void set_color(EdgeHandle _eh, const Vec4f& _color) = 0;

  // set face normal
  virtual void set_normal(FaceHandle _fh, const Vec3f& _normal) = 0;

  // set face color
  virtual void set_color(FaceHandle _fh, const Vec3uc& _color) = 0;

  // set face color
  virtual void set_color(FaceHandle _fh, const Vec4uc& _color) = 0;

  // set face color
  virtual void set_color(FaceHandle _fh, const Vec3f& _color) = 0;

  // set face color
  virtual void set_color(FaceHandle _fh, const Vec4f& _color) = 0;

  // Store a property in the mesh mapping from an int to a texture file
  // Use set_face_texindex to set the index for each face
  virtual void add_texture_information( int _id , std::string _name ) = 0;

  // get reference to base kernel
  virtual BaseKernel* kernel() { return 0; }

  virtual bool is_triangle_mesh()     const { return false; }

  // reserve mem for elements
  virtual void reserve( unsigned int /* nV */,
		                  unsigned int /* nE */,
		                  unsigned int /* nF */) {}

  // query number of faces, vertices, normals, texcoords
  virtual size_t n_vertices()   const = 0;
  virtual size_t n_faces()      const = 0;
  virtual size_t n_edges()      const = 0;


  // pre-processing
  virtual void prepare()  {}

  // post-processing
  virtual void finish()  {}
};


//=============================================================================
} // namespace IO
} // namespace OpenMesh
//=============================================================================
#endif
//=============================================================================
