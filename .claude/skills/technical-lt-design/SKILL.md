---
name: technical-lt-design
description: Design guidance specific to this 15-minute online C-language Slidev talk. Use whenever changing slide structure, visual hierarchy, layouts, code presentation, diagrams, or presentation styling.
---

# Technical LT Design

This is a 15-minute online technical talk shown over Discord screen sharing.

Audience:
- university students
- software engineers roughly up to their late 20s
- mixed familiarity with C, USB, WASM, and low-level programming

Goals:
1. Make C feel genuinely interesting.
2. Make the audience consider C as a realistic future technology choice.

## Presentation constraints

Design primarily for 1280x720.

A slide's primary point should be understandable in about 2 seconds.

Prefer:
- one dominant idea per slide
- large typography
- strong left alignment for explanatory slides
- actual bytes, code, memory layouts, protocol diagrams, and runtime behavior as visual material
- deliberate changes of composition between slides
- details moved to speaker notes or appendix

Avoid:
- dashboard layouts
- repeated rounded-card grids
- every concept inside a box
- tiny annotations
- decorative gradients
- generic developer-conference aesthetics
- identical compositions on consecutive slides

## Visual identity

Derive the visual language from this specific subject:

- raw bytes
- hexadecimal data
- memory
- wire formats
- USB descriptors
- C source
- boundaries between systems
- WebAssembly

Do not decorate the slides with generic technology imagery.

The technical object itself should usually be the visual.

## Rhythm

The deck should intentionally alternate between forms such as:

- statement
- raw bytes
- code
- diagram
- live demo
- conclusion

Do not make every slide equally dense.

## Technical integrity

Never simplify a technical statement into something false for visual convenience.

If information is too dense, move details to notes or appendix instead of shrinking them.

## Success criterion

The result should clearly look designed for this exact C / USB / WASM talk.

It must not resemble:
- a SaaS landing page
- an AI-generated dashboard
- a generic Tailwind component showcase
- a reusable conference template