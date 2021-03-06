// Copyright 2016 The Fuchsia Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "apps/ledger/src/callback/destruction_sentinel.h"

namespace callback {

DestructionSentinel::DestructionSentinel() : is_destructed_ptr_(nullptr) {}

DestructionSentinel::~DestructionSentinel() {
  if (is_destructed_ptr_)
    *is_destructed_ptr_ = true;
}

}  // namespace callback
