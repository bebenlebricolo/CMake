#pragma once

#include <memory>
#include <string>
#include <unordered_set>
#include <vector>

#include "cmAvrGccCompilerOption.h"

namespace compiler {

struct LinkerOption : public CompilerOption
{
  /**
     * @brief determines whether the given token is part of the static map of available optimizations flags or not
     * @param[in]   _token : string representation of current flag being parsed
     * @return true : token exist in collection ; false : token is not part of the collection, thus it is not part of the available set of optimizations.
    */
  static bool can_create(const std::string& _token);

  LinkerOption();
  LinkerOption(const std::string& _token);

  /**
   * @brief Splits concatenated options as sometimes, linker parameters are given using the "Wl," prefix, which supports concatenated
   * options such as "Wl,--gc-sections,--relax".
   *
   * @param     _token : raw input token as parsed from command line input
   * @return    a vector of simple tokens, as if they were provided as standalone ones like this :
   *                [0] "-Wl,--gc-sections"
   *                [1] "-Wl,--relax"
   */
  static std::vector<std::string> split_concatenated_options(const std::string& _token);

  /**
   * @brief Checks if input token matches internal representation of the linker flag.
   * For instance, if underlying flag is "Wl,--gc-sections", input token should be compared with :
   *    --gc-sections       => Which is the native way for ld to consume flags
   *    Wl,--gc-sections    => Which is the way GCC consumes flag to be passed to the linker
   * @param input_token
   * @return
   */
  virtual bool contains(const std::string& input_token) const override;

};

}
