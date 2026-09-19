---
name: technical-storytelling
description: Explain difficult technical concepts through examples, analogy, progressive reveal, and concrete-to-abstract storytelling. Use when simplifying technical explanations for a mixed audience without losing correctness.
---

# Technical Storytelling

The audience should understand before they learn terminology.

## Default explanation order

Prefer:

1. concrete example
2. question or surprise
3. visual transformation
4. intuitive analogy
5. technical name
6. precise limitation or caveat

Do not begin with definitions unless the definition itself is the interesting part.

## Example before abstraction

Instead of:

"USB descriptors are data structures returned during enumeration."

Prefer:

"PC: Who are you?
Device: Here are 18 bytes."

Then show the actual bytes.

Only after the audience understands the interaction should terminology appear.

## Analogy rules

Analogies are temporary scaffolding.

A useful analogy:
- maps one difficult idea to one familiar idea
- helps predict what happens next
- is short
- is explicitly bounded when it stops being accurate

Do not stack multiple analogies onto the same concept.

Do not let the analogy replace the real technical object.

Always return from the analogy to the real bytes, code, memory, or behavior.

## Good progression

Use:

concrete
→ intuitive
→ technical
→ precise

Examples:

wire bytes
→ "number cards arriving in order"
→ little-endian
→ exact byte interpretation

stack buffer
→ "a hotel room that disappears after checkout"
→ object lifetime
→ returning a pointer to expired storage

padding
→ "the payload is 18 bytes, but the shelf may add gaps"
→ alignment/padding
→ sizeof is not a wire length

## Reveal structure

Good technical moments often have:

question
→ prediction
→ reveal
→ explanation
→ implication

Do not show the answer before the audience has a reason to care.

## Vocabulary discipline

Minimize new terms introduced on a single slide.

If a term is not needed to understand the current point, delay it.

Prefer plain language first.

Technical vocabulary is useful after the mental model exists.

## Speaker + slide relationship

The slide does not need to contain the whole explanation.

Slides should show:
- the thing
- the transformation
- the relationship
- the surprise

The speaker can supply:
- context
- caveats
- transitions
- detailed explanation

Do not force the audience to read the full argument while also listening.

## Emotional goal

For this talk, understanding alone is not enough.

The audience should experience small moments of:
- "oh"
- "that is what those bytes mean"
- "wait, C can do that?"
- "that is more interesting than I expected"

Preserve technical accuracy, but design the explanation for curiosity.

## Final check

For every difficult concept ask:

- Can I show an example before naming it?
- Can I remove one term?
- Can I replace one paragraph with a transformation?
- Does the audience know why they should care before I explain the mechanism?
- Is the analogy helping, or just sounding clever?