/*=========================================================================

  This software is distributed WITHOUT ANY WARRANTY; without even
  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
  PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#include "daxImageData.h"

#include "CoreImageData.cl.h"

//-----------------------------------------------------------------------------
struct daxImageData::OpaqueDataType
{
  int Dimensions[3];
} __attribute__( (__packed__) );

//-----------------------------------------------------------------------------
daxImageData::daxImageData()
{
  this->NumberOfComponents = 1;
  this->Dimensions[0] = this->Dimensions[1] = this->Dimensions[2] = 0;
  this->Data = NULL;
  this->OpaqueDataPointer = new OpaqueDataType();
}

//-----------------------------------------------------------------------------
daxImageData::~daxImageData()
{
  delete [] this->Data;
  this->Data = NULL;
  delete this->OpaqueDataPointer;
  this->OpaqueDataPointer = NULL;
}

//-----------------------------------------------------------------------------
void* daxImageData::GetOpaqueDataPointer() const
{
  this->OpaqueDataPointer->Dimensions[0] = this->Dimensions[0];
  this->OpaqueDataPointer->Dimensions[1] = this->Dimensions[1];
  this->OpaqueDataPointer->Dimensions[1] = this->Dimensions[1];
  return this->OpaqueDataPointer;
}

//-----------------------------------------------------------------------------
size_t daxImageData::GetOpaqueDataSize() const
{
  return sizeof(daxImageData::OpaqueDataType);
}

//-----------------------------------------------------------------------------
void daxImageData::SetDimensions(int x, int y, int z)
{
  if (this->Dimensions[0] != x || this->Dimensions[1] != y ||
    this->Dimensions[2] != z)
    {
    delete []this->Data;
    this->Data = new float[x*y*z * this->NumberOfComponents];
    this->Dimensions[0] = x;
    this->Dimensions[1] = y;
    this->Dimensions[2] = z;
    }
}

//-----------------------------------------------------------------------------
void daxImageData::SetNumberOfComponents(int num)
{
  if (this->NumberOfComponents != num)
    {
    delete []this->Data;
    this->Data = new
      float[this->Dimensions[0]*this->Dimensions[1]*this->Dimensions[2]*num];
    this->NumberOfComponents = num;
    }
}

//-----------------------------------------------------------------------------
float* daxImageData::GetDataPointer(int x, int y, int z)
{
  int ijk[3] = { x, y, z};
  int dim[3] = { this->Dimensions[0], this->Dimensions[1], this->Dimensions[2]};
  return this->Data + ((ijk[2]*dim[1] + ijk[1])*dim[0] + ijk[0]);
}

//-----------------------------------------------------------------------------
const int* daxImageData::GetDimensions() const
{
  return this->Dimensions;
}


namespace daxImageDataInternals
{
  std::string GetOpenCLCode()
    {
    return daxHeaderString_CoreImageData;
    }
}