// Copyright 2016 The Fuchsia Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "apps/ledger/src/callback/cancellable.h"

namespace callback {

Cancellable::Cancellable() {}

Cancellable::~Cancellable() {}

AutoCancel::AutoCancel(ftl::RefPtr<Cancellable> cancellable)
    : cancellable_(cancellable) {
  if (cancellable_) {
    cancellable_->SetOnDone([this] { OnDone(); });
  }
}

AutoCancel::~AutoCancel() {
  if (cancellable_)
    cancellable_->Cancel();
}

void AutoCancel::Reset(ftl::RefPtr<Cancellable> cancellable) {
  if (cancellable == cancellable_)
    return;
  if (cancellable_)
    cancellable_->Cancel();
  cancellable_ = cancellable;
  if (cancellable_)
    cancellable_->SetOnDone([this] { OnDone(); });
}

void AutoCancel::set_on_empty(ftl::Closure callback) {
  FTL_DCHECK(!on_empty_);
  on_empty_ = callback;
  if (cancellable_->IsDone()) {
    OnDone();
  }
}

void AutoCancel::OnDone() {
  if (on_empty_) {
    on_empty_();
  }
}
}  // namespace callback
