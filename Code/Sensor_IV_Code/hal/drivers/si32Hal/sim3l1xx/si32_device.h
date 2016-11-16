
//------------------------------------------------------------------------------
// Copyright (c) 2012 by Silicon Laboratories. 
// All rights reserved. This program and the accompanying materials
// are made available under the terms of the Silicon Laboratories End User 
// License Agreement which accompanies this distribution, and is available at
// http://developer.silabs.com/legal/version/v10/License_Agreement_v10.htm
// Original content and implementation provided by Silicon Laboratories.
//------------------------------------------------------------------------------

// This redirector file is used to include the appropriate device header file.
// Each si32Hal/{sim3xxxx} device folder has a version of this redirector file.
// Because all the redirector files have the same name, the device header file
// that is included will be selected by the include path to the device folder.

#include "sim3l1xx.h"

#define SI32_MCU_SIM3L1XX

//-eof-------------------------------------------------------------------------
