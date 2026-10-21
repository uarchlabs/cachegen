// ==============================================================
// SPDX-License-Identifier: Apache-2.0
// Copyright (c) 2022-2026 Jeff Nye, uarchlabs.com
// SPDX-FileCopyrightText: 2022-2026 Jeff Nye <jeff@uarchlabs.com>
// ==============================================================
#include "gen.h"
#include <iostream>
using namespace std;

int main(int ac,char **av)
{
  CacheGen cg(ac,av);
  if(!cg.run()) return 1;
  return 0;
}
