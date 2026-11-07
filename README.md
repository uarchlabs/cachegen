<!-- SPDX-License-Identifier: CC-BY-4.0                              -->
<!-- Copyright (c) 2023-2026 Jeff Nye, uarchlabs.com                 -->
<!-- SPDX-FileCopyrightText: 2023-2026 Jeff Nye <jeff@uarchlabs.com> -->

# cachegen

cachegen generates cache RTL from a configuration. Its command-line tool,
`cgen`, reads a JSON description of a cache hierarchy and emits the
SystemVerilog design, its testbenches and a Make build.

It is also an experiment in how to spend an LLM's context. Caches are
built from well-known organizations: tags, data arrays, valid bits,
replacement state, MSHRs, fill and victim buffers. Having an implementation
assistant write thousands of lines of cache RTL directly uses context in
proportion to the size of the design, and drift between artifacts that
must agree is the usual failure. The approach here is to specify the cache,
let a deterministic generator emit the bulk of it, and have the assistant
review and adapt the output. The generator contributes consistency; the
assistant contributes judgment.

The first configuration it targets is the cache hierarchy of
[Pacino](https://github.com/uarchlabs/pacino), an 8-issue out-of-order
RISC-V targeting RVA23S64.

## Status

```
  DONE         five-file input schema: system, topology, caches, ports, links
  DONE         Pacino worked example (testcases/pacino)
  DONE         cgen front half: load, resolve, check, derive
  DONE         cgen emitter: RTL, testbenches, Make build
  DONE         generation logs, including which configuration fields are used
  NOT STARTED  C++ functional model backend
  NOT STARTED  elaborated configuration output
  NOT STARTED  GUI
```

For the Pacino configuration, the emitted design lints clean, builds,
elaborates and passes its generated tests. `planning/PROJECT_STATUS.md` is
the current record, and `planning/arch/cgen_decisions.md` holds the design
decisions.

## Repository layout

```
  cli/                cgen source (C++), unit tests (googletest) and fixtures
  planning/schema/    JSON schemas for the five input files, with examples
  planning/arch/      cgen design decisions
  testcases/pacino/   the Pacino cache configuration
  examples/1mb_l1/    a hand-written reference cache (below)
  prompts/            IA task files
  session_handoffs/   PA session handoffs
  templates/          task file and report templates
  tools/              submodules: Verilator, googletest,
                      json-schema-validator, jnutils
```

## Building cgen

cgen needs a C++ compiler and Boost.ProgramOptions
(`-lboost_program_options`).

```
git clone --recurse-submodules https://github.com/uarchlabs/cachegen
cd cachegen/cli
make            # builds cgen and its unit tests
make test       # runs the unit tests
make run        # checks the Pacino configuration end to end
```

Usage:

```
cgen --cmd={check,emit} --config=<file> [options]
cgen --help
```

`check` loads, resolves and checks a configuration. `emit` also writes the
RTL, testbenches and build.

## Reference design: examples/1mb_l1

The repository started in 2023 as a hand-written cache: 1 MB, 4-way,
32-byte lines, tree PLRU, physical addressing, with a main memory block
behind it. It has directed tests for load and store hits, allocation on
clean and dirty misses, and LRU behavior; a C++ functional model with a
test-case generator; and Quartus files for a Cyclone V (DE0-Nano-SoC). It
was written for Icarus Verilog and GTKWave. `examples/1mb_l1/rtl/README.txt`
describes the RTL.

It is kept as a second data point for the generator: a cache organization
written by hand, against which generated output can be compared.

## Methodology

cachegen is developed with the same planning assistant (PA) and
implementation assistant (IA) flow as Pacino. Task files are in `prompts/`,
PA handoffs in `session_handoffs/`, and the conventions in
`planning/PROJECT_CORE.md`.

## License

Code and RTL are released under the Apache License 2.0 (see LICENSE).
Documentation is released under CC BY 4.0.

cachegen was relicensed from GPL-3.0 to Apache-2.0 on 2026-10-21.
Versions up to the tag `gpl-3.0-final` remain available under GPL-3.0.
