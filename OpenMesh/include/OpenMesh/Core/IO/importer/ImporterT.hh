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
//  Implements an importer module for arbitrary OpenMesh meshes
//
//=============================================================================


#ifndef __IMPORTERT_HH__
#define __IMPORTERT_HH__


//=== INCLUDES ================================================================


#include <OpenMesh/Core/IO/importer/BaseImporter.hh>
#include <OpenMesh/Core/Utils/vector_cast.hh>
#include <OpenMesh/Core/Utils/color_cast.hh>
#include <OpenMesh/Core/Mesh/Attributes.hh>
#include <OpenMesh/Core/System/omstream.hh>


//== NAMESPACES ===============================================================


namespace OpenMesh {
namespace IO {


//=== IMPLEMENTATION ==========================================================


/**
 *  This class template provides an importer module for OpenMesh meshes.
 */
template <class Mesh>
class ImporterT : public BaseImporter
{
public:

  typedef typename Mesh::Point       Point;
  typedef typename Mesh::Normal      Normal;
  typedef typename Mesh::Color       Color;
  typedef typename Mesh::TexCoord2D  TexCoord2D;
  typedef std::vector<VertexHandle>  VHandles;


  ImporterT(Mesh& _mesh) : mesh_(_mesh), halfedgeNormals_() {}


  virtual VertexHandle add_vertex(const Vec3f& _point)
  {
    return mesh_.add_vertex(vector_cast<Point>(_point));
  }

  virtual VertexHandle add_vertex()
  {
    return mesh_.new_vertex();
  }

  virtual FaceHandle add_face(const VHandles& _indices)
  {
    FaceHandle fh;

    if (_indices.size() > 2)
    {
      VHandles::const_iterator it, it2, end(_indices.end());


      // test for valid vertex indices
      for (it=_indices.begin(); it!=end; ++it)
        if (! mesh_.is_valid_handle(*it))
        {
          omerr() << "ImporterT: Face contains invalid vertex index\n";
          return fh;
        }


      // don't allow double vertices
      for (it=_indices.begin(); it!=end; ++it)
        for (it2=it+1; it2!=end; ++it2)
          if (*it == *it2)
          {
            omerr() << "ImporterT: Face has equal vertices\n";
            failed_faces_.push_back(_indices);
            return fh;
          }


      // try to add face
      fh = mesh_.add_face(_indices);
      if (!fh.is_valid())
      {
        failed_faces_.push_back(_indices);
        return fh;
      }

      //write the half edge normals
      if (mesh_.has_halfedge_normals())
      {
        //iterate over all incoming haldedges of the added face
        for (typename Mesh::FaceHalfedgeIter fh_iter = mesh_.fh_begin(fh);
            fh_iter != mesh_.fh_end(fh); ++fh_iter)
        {
          //and write the normals to it
          typename Mesh::HalfedgeHandle heh = *fh_iter;
          typename Mesh::VertexHandle vh = mesh_.to_vertex_handle(heh);
          typename std::map<VertexHandle,Normal>::iterator it_heNs = halfedgeNormals_.find(vh);
          if (it_heNs != halfedgeNormals_.end())
            mesh_.set_normal(heh,it_heNs->second);
        }
        halfedgeNormals_.clear();
      }
    }
    return fh;
  }

  // vertex attributes

  virtual void set_point(VertexHandle _vh, const Vec3f& _point)
  {
    mesh_.set_point(_vh,vector_cast<Point>(_point));
  }

  virtual void set_normal(VertexHandle _vh, const Vec3f& _normal)
  {
    if (mesh_.has_vertex_normals())
      mesh_.set_normal(_vh, vector_cast<Normal>(_normal));

    //saves normals for half edges.
    //they will be written, when the face is added
    if (mesh_.has_halfedge_normals())
      halfedgeNormals_[_vh] = vector_cast<Normal>(_normal);
  }

  virtual void set_color(VertexHandle _vh, const Vec4uc& _color)
  {
    if (mesh_.has_vertex_colors())
      mesh_.set_color(_vh, color_cast<Color>(_color));
  }

  virtual void set_color(VertexHandle _vh, const Vec3uc& _color)
  {
    if (mesh_.has_vertex_colors())
      mesh_.set_color(_vh, color_cast<Color>(_color));
  }

  virtual void set_color(VertexHandle _vh, const Vec4f& _color)
  {
    if (mesh_.has_vertex_colors())
      mesh_.set_color(_vh, color_cast<Color>(_color));
  }

  virtual void set_color(VertexHandle _vh, const Vec3f& _color)
  {
    if (mesh_.has_vertex_colors())
      mesh_.set_color(_vh, color_cast<Color>(_color));
  }

  virtual void set_texcoord(VertexHandle _vh, const Vec2f& _texcoord)
  {
    if (mesh_.has_vertex_texcoords2D())
      mesh_.set_texcoord2D(_vh, vector_cast<TexCoord2D>(_texcoord));
  }

  virtual void set_texcoord(HalfedgeHandle _heh, const Vec2f& _texcoord)
  {
    if (mesh_.has_halfedge_texcoords2D())
      mesh_.set_texcoord2D(_heh, vector_cast<TexCoord2D>(_texcoord));
  }

  // edge attributes

  virtual void set_color(EdgeHandle _eh, const Vec4uc& _color)
  {
      if (mesh_.has_edge_colors())
          mesh_.set_color(_eh, color_cast<Color>(_color));
  }

  virtual void set_color(EdgeHandle _eh, const Vec3uc& _color)
  {
      if (mesh_.has_edge_colors())
          mesh_.set_color(_eh, color_cast<Color>(_color));
  }

  virtual void set_color(EdgeHandle _eh, const Vec4f& _color)
  {
      if (mesh_.has_edge_colors())
          mesh_.set_color(_eh, color_cast<Color>(_color));
  }

  virtual void set_color(EdgeHandle _eh, const Vec3f& _color)
  {
      if (mesh_.has_edge_colors())
          mesh_.set_color(_eh, color_cast<Color>(_color));
  }

  // face attributes

  virtual void set_normal(FaceHandle _fh, const Vec3f& _normal)
  {
    if (mesh_.has_face_normals())
      mesh_.set_normal(_fh, vector_cast<Normal>(_normal));
  }

  virtual void set_color(FaceHandle _fh, const Vec3uc& _color)
  {
    if (mesh_.has_face_colors())
      mesh_.set_color(_fh, color_cast<Color>(_color));
  }

  virtual void set_color(FaceHandle _fh, const Vec4uc& _color)
  {
    if (mesh_.has_face_colors())
      mesh_.set_color(_fh, color_cast<Color>(_color));
  }

  virtual void set_color(FaceHandle _fh, const Vec3f& _color)
  {
    if (mesh_.has_face_colors())
      mesh_.set_color(_fh, color_cast<Color>(_color));
  }

  virtual void set_color(FaceHandle _fh, const Vec4f& _color)
  {
    if (mesh_.has_face_colors())
      mesh_.set_color(_fh, color_cast<Color>(_color));
  }

  virtual void add_face_texcoords( FaceHandle _fh, VertexHandle _vh, const std::vector<Vec2f>& _face_texcoords)
  {
    // get first halfedge handle
    HalfedgeHandle cur_heh   = mesh_.halfedge_handle(_fh);
    HalfedgeHandle end_heh   = mesh_.prev_halfedge_handle(cur_heh);

    // find start heh
    while( mesh_.to_vertex_handle(cur_heh) != _vh && cur_heh != end_heh )
      cur_heh = mesh_.next_halfedge_handle( cur_heh);

    for(unsigned int i=0; i<_face_texcoords.size(); ++i)
    {
      set_texcoord( cur_heh, _face_texcoords[i]);
      cur_heh = mesh_.next_halfedge_handle( cur_heh);
    }
  }

  virtual void set_face_texindex( FaceHandle _fh, int _texId ) {
    if ( mesh_.has_face_texture_index() ) {
      mesh_.set_texture_index(_fh , _texId);
    }
  }

  virtual void add_texture_information( int _id , std::string _name ) {
    OpenMesh::MPropHandleT< std::map< int, std::string > > property;

    if ( !mesh_.get_property_handle(property,"TextureMapping") ) {
      mesh_.add_property(property,"TextureMapping");
    }

    if ( mesh_.property(property).find( _id ) == mesh_.property(property).end() )
      mesh_.property(property)[_id] = _name;
  }

  // low-level access to mesh

  virtual BaseKernel* kernel() { return &mesh_; }

  bool is_triangle_mesh() const
  { return Mesh::is_triangles(); }

  void reserve(unsigned int nV, unsigned int nE, unsigned int nF)
  {
    mesh_.reserve(nV, nE, nF);
  }

  // query number of faces, vertices, normals, texcoords
  size_t n_vertices()  const { return mesh_.n_vertices(); }
  size_t n_faces()     const { return mesh_.n_faces(); }
  size_t n_edges()     const { return mesh_.n_edges(); }


  void prepare() { failed_faces_.clear(); }


  void finish()
  {
    if (!failed_faces_.empty())
    {
      omerr() << failed_faces_.size()
	    << " faces failed, adding them as isolated faces\n";

      for (unsigned int i=0; i<failed_faces_.size(); ++i)
      {
        VHandles&  vhandles = failed_faces_[i];

        // double vertices
        for (unsigned int j=0; j<vhandles.size(); ++j)
        {
          Point p = mesh_.point(vhandles[j]);
          vhandles[j] = mesh_.add_vertex(p);
          // DO STORE p, reference may not work since vertex array
          // may be relocated after adding a new vertex !

          // Mark vertices of failed face as non-manifold
          if (mesh_.has_vertex_status()) {
              mesh_.status(vhandles[j]).set_fixed_nonmanifold(true);
          }
        }

        // add face
        FaceHandle fh = mesh_.add_face(vhandles);

        // Mark failed face as non-manifold
        if (mesh_.has_face_status())
            mesh_.status(fh).set_fixed_nonmanifold(true);

        // Mark edges of failed face as non-two-manifold
        if (mesh_.has_edge_status()) {
            typename Mesh::FaceEdgeIter fe_it = mesh_.fe_iter(fh);
            for(; fe_it.is_valid(); ++fe_it) {
                mesh_.status(*fe_it).set_fixed_nonmanifold(true);
            }
        }
      }

      failed_faces_.clear();
    }
  }



private:

  Mesh& mesh_;
  std::vector<VHandles>  failed_faces_;
  // stores normals for halfedges of the next face
  std::map<VertexHandle,Normal> halfedgeNormals_;
};


//=============================================================================
} // namespace IO
} // namespace OpenMesh
//=============================================================================
#endif
//=============================================================================
