/* Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
   file Copyright.txt or https://cmake.org/licensing for details.  */
#pragma once

#include <string>

#include <cm/optional>

#include "cmGccDepfileReaderTypes.h"

/*
 * Read dependencies file and append prefix to all relative paths
 */
cm::optional<cmGccDepfileContent> cmReadGccDepfile(
  const char* filePath, const std::string& prefix = {});
