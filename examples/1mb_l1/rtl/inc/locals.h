// ==============================================================
// SPDX-License-Identifier: Apache-2.0
// Copyright (c) 2022-2026 Jeff Nye, uarchlabs.com
// SPDX-FileCopyrightText: 2022-2026 Jeff Nye <jeff@uarchlabs.com>
// ==============================================================
// vi:syntax=verilog
`ifndef LOAD_LOCALS

`define LOAD_LOCALS 1

localparam DOP_BE  = 4'hF;

localparam integer DOP_WR  = 0;
localparam integer DOP_RD  = 1;
localparam integer DOP_DBG = 2;
localparam integer DOP_INV = 3;  //Gang invalidate
`endif
