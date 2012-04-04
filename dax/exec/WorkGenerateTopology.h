//=============================================================================
//
//  Copyright (c) Kitware, Inc.
//  All rights reserved.
//  See LICENSE.txt for details.
//
//  This software is distributed WITHOUT ANY WARRANTY; without even
//  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
//  PURPOSE.  See the above copyright notice for more information.
//
//  Copyright 2012 Sandia Corporation.
//  Under the terms of Contract DE-AC04-94AL85000 with Sandia Corporation,
//  the U.S. Government retains certain rights in this software.
//
//=============================================================================

#ifndef __dax_exec_WorkGenerateTopology_h
#define __dax_exec_WorkGenerateTopology_h

#include <dax/Types.h>
#include <dax/exec/Cell.h>
#include <dax/exec/Field.h>
#include <dax/exec/WorkMapCell.h>

#include <dax/internal/GridTopologys.h>
#include <dax/exec/internal/ErrorHandler.h>
#include <dax/exec/internal/FieldAccess.h>

namespace dax {
namespace exec {

///----------------------------------------------------------------------------
/// Worklet that determines how many new cells should be generated
/// from it with the same topology.
/// This worklet is based on the WorkMapCell type so you have access to
/// "CellArray" information i.e. information about what points form a cell.
/// There are different versions for different cell types, which might have
/// different constructors because they identify topology differently.

template<class ICT, class OCT> class WorkGenerateTopology
{
public:
  typedef ICT InputCellType;
  typedef OCT OutputCellType;

  typedef typename InputCellType::TopologyType TopologyType;
  typedef typename InputCellType::PointIds InputPointIds;
  typedef typename OutputCellType::PointIds OutputPointIds;

private:
  InputCellType InputCell;
  dax::Id OutputIndex;
  dax::exec::Field<dax::Id> OutputTopology;
  dax::exec::internal::ErrorHandler ErrorHandler;
public:

  DAX_EXEC_EXPORT WorkGenerateTopology(
    const TopologyType &gridStructure,
    const dax::exec::Field<dax::Id> &outTopology,
    const dax::exec::internal::ErrorHandler &errorHandler)
    : InputCell(gridStructure, 0),
      OutputIndex(0),
      OutputTopology(outTopology),
      ErrorHandler(errorHandler)
    { }

  /// Get the topology of the input cell
  DAX_EXEC_EXPORT InputPointIds GetInputTopology() const
  {
    return this->InputCell.GetPointIndices();
  }

  /// Set the topology of one of the output cells
  DAX_EXEC_EXPORT void SetOutputTopology(const OutputPointIds &topology)
  {
    dax::exec::internal::fieldAccessNormalSet(this->OutputTopology,
                                              this->OutputIndex*OutputCellType::NUM_POINTS, //needs to be the index into the topology array
                                              topology);
  }

  DAX_EXEC_EXPORT void SetCellIndex(dax::Id cellIndex)
  {
    this->InputCell.SetIndex(cellIndex);
  }

  DAX_EXEC_EXPORT void SetOutputCellIndex(dax::Id cellIndex)
  {
  this->OutputIndex = cellIndex;
  }

  DAX_EXEC_EXPORT dax::Id GetOutputCellIndex()
  {
  return this->OutputIndex;
  }

  DAX_EXEC_EXPORT void RaiseError(const char* message)
  {
    this->ErrorHandler.RaiseError(message);
  }  
};


}
}

#endif //__dax_exec_WorkGenerateTopology_h