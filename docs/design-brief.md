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

USB
→ raw bytes
→ C exposes representation and boundaries
→ C compiled to WASM
→ browser
→ when C is worth considering

USB is an accessible example, not the actual subject of the talk.

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
3. The C/WASM live demo.
4. The final technology-selection takeaway.

Other slides should support these rather than compete with them.