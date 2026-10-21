#!/usr/bin/env python3
# ==============================================================
# SPDX-License-Identifier: Apache-2.0
# Copyright (c) 2022-2026 Jeff Nye, uarchlabs.com
# SPDX-FileCopyrightText: 2022-2026 Jeff Nye <jeff@uarchlabs.com>
# ==============================================================

for i in range(0,32):
  upper = str((i+1)*8-1)
  lower = str(i*8)
  print('ram[a][%3s:%3s] <= write & be[%s] ? wd : ram[a][%3s:%3s];' % \
      (upper,str(i*8),str(i),upper,str(i*8)))
