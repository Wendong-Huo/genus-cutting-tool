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

#ifndef OPENMESH_HANDLES_HH
#define OPENMESH_HANDLES_HH


//== INCLUDES =================================================================

#include <OpenMesh/Core/System/config.h>
#include <iostream>


//== NAMESPACES ===============================================================

namespace OpenMesh {

//== CLASS DEFINITION =========================================================


/// Base class for all handle types
class BaseHandle
{ 
public:
  
  explicit BaseHandle(int _idx=-1) : idx_(_idx) {}

  /// Get the underlying index of this handle
  int idx() const { return idx_; }

  /// The handle is valid iff the index is not equal to -1.
  bool is_valid() const { return idx_ != -1; }

  /// reset handle to be invalid
  void reset() { idx_=-1; }
  /// reset handle to be invalid
  void invalidate() { idx_ = -1; }

  bool operator==(const BaseHandle& _rhs) const { 
    return (this->idx_ == _rhs.idx_); 
  }

  bool operator!=(const BaseHandle& _rhs) const { 
    return (this->idx_ != _rhs.idx_); 
  }

  bool operator<(const BaseHandle& _rhs) const { 
    return (this->idx_ < _rhs.idx_); 
  }


  // this is to be used only by the iterators
  void __increment() { ++idx_; }
  void __decrement() { --idx_; }


private:

  int idx_; 
};


//-----------------------------------------------------------------------------

/// Write handle \c _hnd to stream \c _os
inline std::ostream& operator<<(std::ostream& _os, const BaseHandle& _hnd) 
{
  return (_os << _hnd.idx());
}


//-----------------------------------------------------------------------------


/// Handle for a vertex entity
struct VertexHandle : public BaseHandle
{
  explicit VertexHandle(int _idx=-1) : BaseHandle(_idx) {}
};


/// Handle for a halfedge entity
struct HalfedgeHandle : public BaseHandle
{
  explicit HalfedgeHandle(int _idx=-1) : BaseHandle(_idx) {}
};


/// Handle for a edge entity
struct EdgeHandle : public BaseHandle
{
  explicit EdgeHandle(int _idx=-1) : BaseHandle(_idx) {}
};


/// Handle for a face entity
struct FaceHandle : public BaseHandle
{
  explicit FaceHandle(int _idx=-1) : BaseHandle(_idx) {}
};


//=============================================================================
} // namespace OpenMesh
//=============================================================================
#endif // OPENMESH_HANDLES_HH
//=============================================================================
