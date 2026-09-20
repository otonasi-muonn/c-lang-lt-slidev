# Presentation Design Brief

## Event

15-minute online session in a developer community.

The deck is presented through Discord screen sharing and later published as an interactive Slidev site.

## Audience

Primarily:

- university students
- young software engineers
- people who may use C occasionally or rarely

Assume no USB knowledge, no WASM knowledge, no ABI or FFI knowledge, and that
TypeScript may also be unfamiliar. Treat the room as intelligent non-specialists,
not as beginners.

## Communication goal

The audience should leave thinking:

"C is not only an old language you learn in class."

"I have some idea what 'close to the low level' actually means."

"Using C does not have to mean writing a whole application in C."

"I should not automatically remove C from consideration when choosing technology."

## Core story

The talk is built in this order, and the order is the argument:

1. Open on the speaker's own position: AI changed what it costs to write code,
   so choosing is the interesting part now. Stated as an opinion, not a fact.
2. What C actually is — a system implementation language for early Unix — before
   any reputation about it ("old", "dangerous", "embedded") is allowed in.
3. TypeScript introduced in one sheet, as the modern high-level choice the
   speaker would also make for a hackathon web app.
4. Why the speaker likes C: the machine's own concerns surface in your code.
5. The smallest possible demonstration: `uint32_t x = 0x12345678` observed byte
   by byte on a real machine, then named little-endian.
6. USB as a *revision exercise*, not new material: apply what was just learned to
   two real bytes and get a real vendor name out. 50 seconds.
7. TypeScript can read the same bytes. Say so first, explicitly.
8. What being close costs: padding, lifetime, and the memory-safety record.
9. Turn the question: when would I actually put C back on the list?
10. Split "using C" into two different decisions — reusing existing C, and
    writing a new small core — and keep them apart for the rest of the talk.
11. A toy `double_it()` compiled to WASM, to build one mental model only.
12. The same mechanism with the USB parser inside it.
13. SQLite as the real case, with its browser build drawn accurately.
14. Native interop shown as a *separate* mechanism from WASM.
15. Only at the end: name what was seen — 見える / 持っていける / つながる.
16. Concede where other languages win, then land on the one ask.

Do not hand the audience the three-word taxonomy at the start. It is the payoff,
not the roadmap.

The main deck is 23 slides / 38 presentation states, paced for roughly 14 minutes
plus operating and speaking margin. Enumeration, complete field listings,
`sizeof` comparisons, integer conversions, and C++ compatibility stay in the
appendix.

## Claims that must stay accurate

- USB is one case study, not the subject. The 18-byte sequence is an illustrative
  fixture built to the Device Descriptor format with real VID/PID values, not a
  captured device dump.
- The TypeScript comparison demonstrates abstraction level, never capability or
  speed.
- Byte order is a property of the environment the program ran in, not something
  the C language decides.
- Padding and `sizeof` are ABI-dependent. No "C always pads".
- SQLite's four reasons are SQLite's own reasons, not evidence that C beats every
  language.
- The browser SQLite build is `sqlite3.c` + `sqlite3-wasm.c` through Emscripten,
  with a JavaScript glue layer. Not "C alone in the browser".
- Web (WASM) and native (Python/C API, Node-API, `extern "C"`) are different
  mechanisms. Never collapsed into "it's all the C ABI".
- Memory unsafety is presented as a serious, current risk, with Rust named as a
  reasonable answer for new systems code.

## Desired personality

Technical. Curious. Playful where useful. Opinionated but not evangelical.

It should feel like an engineer showing something they genuinely enjoy, in their
own speaking voice.

It should not feel:

- corporate
- sales-oriented
- like a generic AI deck
- like a SaaS dashboard
- like a beginner programming lecture

Speaker notes are not a script. Each one carries what the frame is for, the bridge
to the next frame, and the technical caveats that must not be said wrong.

## Visual material

Prefer using:

- actual hexadecimal bytes
- real command output and real compiler warnings
- memory layout
- C source
- arrows showing data movement
- wire format vs object representation
- the two live WASM demos

The actual technical objects form the identity of the deck.

## Visual restraint

Use a restrained palette. Colour carries three meanings only: the value under
discussion, a multi-byte field, and an error.

Two marks recur and mean one thing each: a left hairline means the text was taken
from somewhere real, and a vertical rule means two things are separate mechanisms.

Do not assign a different accent color to every concept. Avoid repeated rounded
cards. Avoid UI-looking layouts unless the slide actually represents an
interactive interface.

## Most important slides

Spend the most design effort on:

1. The observed bytes of `0x12345678`, with the real run behind them.
2. The 18 bytes narrowing to `6D 04` and resolving to Logitech.
3. Lifetime as a visual sequence, with the real compiler warning.
4. The toy C/WASM demo: one number in, one number out, then the call path.
5. The SQLite browser stack and the Web/Native split beside it.
6. The naming slide, where the three words finally arrive.
7. The final technology-selection ask.

Other slides should support these rather than compete with them.
