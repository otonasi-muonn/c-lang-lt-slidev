---
name: ruthless-slide-editor
description: Aggressively reduce slide content to the minimum needed for audience understanding. Use when slides are dense, over-explained, technically complete but hard to follow, or when deciding what belongs in the main deck versus speaker notes or appendix.
---

# Ruthless Slide Editor

A technically correct slide can still be a bad presentation slide.

The main deck does not need to preserve every true fact.

It needs to preserve the audience's understanding.

## Primary rule

One slide should usually perform one cognitive move.

Examples:
- ask one question
- reveal one fact
- explain one transformation
- show one contradiction
- make one decision
- land one conclusion

If a slide performs three or four moves, split, simplify, or remove material.

## Deletion hierarchy

When a slide is too dense, remove in this order:

1. repeated wording
2. caveats that can move to notes
3. terminology not needed yet
4. implementation details
5. secondary examples
6. full tables when one row proves the point
7. complete code when 3 lines are enough
8. complete protocol sequences when one interaction is enough

Preserve only what is required for the current point.

## Main deck vs notes vs appendix

Use the main deck for:
- ideas the audience must understand during the talk
- the key example
- the key transformation
- the key conclusion

Use speaker notes for:
- exact caveats
- alternative wording
- background context
- details the speaker may mention verbally

Use appendix for:
- full tables
- exact protocol sequences
- secondary edge cases
- detailed language-lawyer material
- material useful for Q&A but not required for the story

## Do not protect content because it is correct

"Technically correct" is not a reason to keep something visible.

Ask instead:

"If I remove this from the slide, does the audience lose the current idea?"

If no, remove it.

## Prefer representative evidence

One strong example is often better than a complete list.

For example:
- one multibyte field can explain little-endian
- one padding mismatch can explain why sizeof is unsafe for wire length
- one dangling pointer can explain lifetime risk
- one real WASM round-trip can explain portability

Do not prove the same point four times unless comparison itself is the point.

## Avoid simultaneous reading and listening

If the audience must read a dense table while the speaker explains another idea, the slide has failed.

Favor:
- one highlighted row
- one code fragment
- one visual relationship
- one sentence

## Simplicity test

For every slide ask:

- What is the one thing I want remembered?
- What can disappear without harming that?
- What belongs in notes instead?
- What belongs in appendix?
- Can the point be shown with fewer words?
- Can one example replace a list?
- Can one visual replace a paragraph?

Keep cutting until further removal would damage the intended idea.

## Final criterion

The slide should feel almost too simple when read silently.

That is often correct.

The speaker supplies the missing connective tissue.