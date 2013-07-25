// Copyright 2012 Google Inc. All Rights Reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef SYZYGY_PE_UNITTEST_UTIL_H_
#define SYZYGY_PE_UNITTEST_UTIL_H_

#include <windows.h>

#include "base/file_util.h"
#include "base/files/file_path.h"
#include "gtest/gtest.h"
#include "syzygy/common/unittest_util.h"

namespace testing {

// Name of the test DLL and PDB. These exist in the output directory, and again
// in the test_data directory.
extern const wchar_t kTestDllName[];
extern const wchar_t kTestDllPdbName[];

// Name of the test DLL object file, relative to the output directory,
// built as a side effect of the compilation of the test DLL.
extern const wchar_t kTestDllObjName[];

// Name of the various test DLLs generated by the test_data project.
// These are placed in $(OutputDir)\test_data, so use
// GetExeTestDataRelativePath to build paths to them.
extern const wchar_t kAsanInstrumentedTestDllName[];
extern const wchar_t kAsanInstrumentedTestDllPdbName[];
extern const wchar_t kBBEntryInstrumentedTestDllName[];
extern const wchar_t kBBEntryInstrumentedTestDllPdbName[];
extern const wchar_t kCallTraceInstrumentedTestDllName[];
extern const wchar_t kCallTraceInstrumentedTestDllPdbName[];
extern const wchar_t kCoverageInstrumentedTestDllName[];
extern const wchar_t kCoverageInstrumentedTestDllPdbName[];
extern const wchar_t kProfileInstrumentedTestDllName[];
extern const wchar_t kProfileInstrumentedTestDllPdbName[];
extern const wchar_t kRandomizedTestDllName[];
extern const wchar_t kRandomizedTestDllPdbName[];

// Name of the various trace files. These are also relative to the test data
// directory.
extern const wchar_t *kBBEntryTraceFiles[4];
extern const wchar_t *kBranchTraceFiles[4];
extern const wchar_t *kCallTraceTraceFiles[4];
extern const wchar_t *kCoverageTraceFiles[4];
extern const wchar_t *kProfileTraceFiles[4];

// This class wraps an HMODULE and ensures that ::FreeLibrary is called when it
// goes out of scope.
class ScopedHMODULE {
 public:
  ScopedHMODULE();
  explicit ScopedHMODULE(HMODULE v);
  ~ScopedHMODULE();

  void Reset(HMODULE v);
  void Release();

  operator HMODULE() const {
    return value_;
  }

 private:
  HMODULE value_;
};

class PELibUnitTest : public testing::ApplicationTestBase {
 public:
  // Performs a series of assertions on the test DLL's integrity.
  static void CheckTestDll(const base::FilePath& path);

  // Loads the test DLL and returns its module handle.
  static void LoadTestDll(const base::FilePath& path, ScopedHMODULE* module);
};

}  // namespace testing

#endif  // SYZYGY_PE_UNITTEST_UTIL_H_
