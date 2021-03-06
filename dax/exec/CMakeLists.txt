##=============================================================================
##
##  Copyright (c) Kitware, Inc.
##  All rights reserved.
##  See LICENSE.txt for details.
##
##  This software is distributed WITHOUT ANY WARRANTY; without even
##  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
##  PURPOSE.  See the above copyright notice for more information.
##
##  Copyright 2012 Sandia Corporation.
##  Under the terms of Contract DE-AC04-94AL85000 with Sandia Corporation,
##  the U.S. Government retains certain rights in this software.
##
##=============================================================================

set(headers
  Assert.h
  CellField.h
  CellVertices.h
  Derivative.h
  ExecutionObjectBase.h
  Interpolate.h
  InterpolatedCellPoints.h
  KeyGroup.h
  ParametricCoordinates.h
  WorkletInterpolatedCell.h
  WorkletGenerateKeysValues.h
  WorkletGenerateTopology.h
  WorkletInterpolatedCell.h
  WorkletMapCell.h
  WorkletMapField.h
  WorkletReduceKeysValues.h

  ${Dax_BINARY_DIR}/dax/exec/VectorOperations.h
)

dax_declare_headers(${headers})

#-----------------------------------------------------------------------------
set(DAX_VECTOR_OPERATIONS_NAMESPACE "dax::exec")
set(DAX_VECTOR_OPERATIONS_NAMESPACE_NAME "dax_exec")
set(DAX_VECTOR_OPERATIONS_NAMESPACE_START "namespace dax { namespace exec {")
set(DAX_VECTOR_OPERATIONS_NAMESPACE_END   "} }")
set(DAX_VECTOR_OPERATIONS_EXPORT "DAX_EXEC_EXPORT")
configure_file(
  ${Dax_SOURCE_DIR}/dax/internal/VectorOperations.h.in
  ${Dax_BINARY_DIR}/dax/exec/VectorOperations.h
  @ONLY
  )

#-----------------------------------------------------------------------------
add_subdirectory(arg)
add_subdirectory(internal)

add_subdirectory(testing)
