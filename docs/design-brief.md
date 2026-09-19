# Presentation Design Brief

## Event

15-minute online session in a developer community.

The deck is presented through Discord screen sharing and later published as an interactive Slidev site.

## Audience

Primarily:
- university students
- young software engineers
- people who may use C occasionally or rarely

Do not assume deep USB knowledge.

## Communication goal

The audience should leave thinking:

"C is more interesting than I expected."

and:

"I should not automatically remove C from consideration when choosing technology."

## Core story

見える → 持っていける → つながる → when C is worth considering

Open from the speaker's usual choice: TypeScript for a hackathon.
Use bytes, object layout, and lifetime to make representation visible;
run the small C parser as WASM in a browser; show bindings to existing C libraries.
AI changes the cost of writing code, but not the meaning of memory or the choice of runtime and interfaces.

The main deck has 13 slides, paced for 13:30 plus 1:30 of operating and speaking margin.
Enumeration, complete field listings, size comparisons, integer conversions,
and C++ compatibility stay in the appendix.

USB is one case study, not the subject or roadmap. The 18-byte sequence is an
illustrative fixture with real VID/PID values, not a captured device dump.
The TypeScript comparison demonstrates abstraction level, not capability or speed.

## Desired personality

Technical.
Curious.
Playful where useful.
Opinionated but not evangelical.

It should feel like an engineer showing something they genuinely enjoy.

It should not feel:
- corporate
- sales-oriented
- like a generic AI deck
- like a SaaS dashboard
- like a beginner programming lecture

## Visual material

Prefer using:
- actual hexadecimal bytes
- memory layout
- C source
- arrows showing data movement
- wire format vs object representation
- the live WASM demo

The actual technical objects should form the identity of the deck.

## Visual restraint

Use a restrained palette.

Do not assign a different accent color to every concept.

Avoid repeated rounded cards.

Avoid UI-looking layouts unless the slide actually represents an interactive interface.

## Most important slides

Spend the most design effort on:

1. The raw 18-byte USB descriptor.
2. The transition from bytes to C interpretation.
3. Lifetime as a visual sequence and its connection to the AI title.
4. The C/WASM live demo: normal run first, optional details collapsed.
5. Bindings / C ABI / existing libraries, with runtime limitations explicit.
6. The final technology-selection takeaway, recalling all three themes.

Other slides should support these rather than compete with them.
