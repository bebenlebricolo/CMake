#include <algorithm>
#include <string>
#include <vector>

#include <gtest/gtest.h>
#include "AS7DeviceResolver.h"

namespace cmAtmelStudioToolsTests
{

TEST(DeviceNamingConventionTest, test_Atmega_names)
{
  const std::vector<std::pair<std::string, std::string>> data =
  {
    {"atmega328p"       ,"ATmega328P"},
    {"atmega328pb"      ,"ATmega328PB"},
    {"atmega64a"        ,"ATmega64A"},
    {"atmega256rfr2"    ,"ATmega256RFR2"},
    {"atmega64hve2"    ,"ATmega64HVE2"}
  };

  for (auto& elem : data)
  {
    std::string convert = AS7DeviceResolver::apply_naming_convention(AS7DeviceResolver::Core::ATmega, elem.first);
    EXPECT_EQ(convert, elem.second);
  }
}

TEST(DeviceNamingConventionTest, test_Attiny_names)
{
  const std::vector<std::pair<std::string, std::string>> data =
  {
    {"attiny416auto"    ,"ATtiny416auto"},
    {"attiny85"         ,"ATtiny85"},
    {"attiny104"        ,"ATtiny104"},
    {"attiny3214"    ,"ATtiny3214"},
  };

  for (auto& elem : data)
  {
    std::string convert = AS7DeviceResolver::apply_naming_convention(AS7DeviceResolver::Core::ATtiny, elem.first);
    EXPECT_EQ(convert, elem.second);
  }
}

TEST(DeviceNamingConventionTest, test_Atautomotive_names)
{
  const std::vector<std::pair<std::string, std::string>> data =
  {
    {"ata6617c" ,"ATA6617C"},
    {"ata8510"  ,"ATA8510"},
    {"ata6617c" ,"ATA6617C"},
    {"ata5831"  ,"ATA5831"},
  };

  for (auto& elem : data)
  {
    std::string convert = AS7DeviceResolver::apply_naming_convention(AS7DeviceResolver::Core::ATautomotive, elem.first);
    EXPECT_EQ(convert, elem.second);
  }
}

// Note, not all ATA devices have their own -mmcu option (none that I could find in package.content though)
// So this test only checks naming convention applied to real cases of Atautomotive devices with their real -mmcu option
TEST(DeviceNamingConventionTest, test_Atxmega_names)
{
  const std::vector<std::pair<std::string, std::string>> data =
  {
    {"atxmega128a1u" ,"ATxmega128A1U"},
    {"atxmega256a3bu"  ,"ATxmega256A3BU"},
    {"atxmega32a4u" ,"ATxmega32A4U"},
    {"atxmega64a1"  ,"ATxmega64A1"},
  };

  for (auto& elem : data)
  {
    std::string convert = AS7DeviceResolver::apply_naming_convention(AS7DeviceResolver::Core::ATxmega, elem.first);
    EXPECT_EQ(convert, elem.second);
  }
}

// Note, for AT32UC devices, there is no "-mmcu option", so the test below extrapolates Atmel's naming convention
TEST(DeviceNamingConventionTest, test_At32UC_names)
{
  const std::vector<std::pair<std::string, std::string>> data =
  {
    {"at32uc3a3256s" ,"AT32UC3A3256S"},
    {"at32uc3a464"  ,"AT32UC3A464"},
    {"at32uc3a4256s" ,"AT32UC3A4256S"},
    {"at32uc3a4128s"  ,"AT32UC3A4128S"},
  };

  for (auto& elem : data)
  {
    std::string convert = AS7DeviceResolver::apply_naming_convention(AS7DeviceResolver::Core::UC, elem.first);
    EXPECT_EQ(convert, elem.second);
  }
}

TEST(DeviceNamingConventionTest, test_AT32UC_names_from_defines)
{
  const std::vector<std::pair<std::string, std::string>> data = {
    { "__AVR32_UC3A3256S__" , "AT32UC3A3256S" },
    { "__AT32UC3A3256S__"   , "AT32UC3A3256S" },
    { "__AVR32_UC3A464__"   , "AT32UC3A464" },
    { "__AT32UC3A464__"     , "AT32UC3A464" },
  };

  for (auto& elem : data) {
    std::string convert = AS7DeviceResolver::resolve_from_defines(elem.first);
    EXPECT_EQ(convert, elem.second);
  }
}

TEST(DeviceNamingConventionTest, test_SAM_names_from_defines)
{
  const std::vector<std::pair<std::string, std::string>> data =
  {
    {"__SAM3A4C__"  ,"ATSAM3A4C"},
    {"__SAM3N1A__"  ,"ATSAM3N1A"},
  };

  for (auto& elem : data)
  {
    std::string convert = AS7DeviceResolver::resolve_from_defines(elem.first);
    EXPECT_EQ(convert, elem.second);
  }
}

TEST(DeviceNamingConventionTest, test_mmcu_option_parsing)
{
  const std::vector<std::pair<std::string, std::string>> data = {
    { "-mmcu=atmega328p", "ATmega328P" },
    { "atmega328pb", "ATmega328PB" },
    { "-mmcu=attiny85", "ATtiny85" },
    { "atxmega256a3bu", "ATxmega256A3BU" },
    { "ata6617c", "ATA6617C" }
  };

  for (auto& elem : data) {
    std::string convert = AS7DeviceResolver::resolve_from_mmcu(elem.first);
    EXPECT_EQ(convert, elem.second);
  }
}

TEST(DeviceNamingConventionTest, test_definition_collection_resolving)
{
  std::vector<std::string> data = {
    "__FirstTest__",
    "VERBOSE=1",
    "NDEBUG",
    "__AVR_ATmega32YOP__=128", // should be discarded
    "__AVR_ATmega328PB__",
    "UNIT_TESTING=1"
  };

  std::string resolved = AS7DeviceResolver::resolve_from_defines(data);
  ASSERT_EQ(resolved, "ATmega328PB");
}

}

int main(int argc, char** argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}