---
name: presentation-qa
description: Visually and functionally review the rendered Slidev deck. Use after meaningful presentation changes and before declaring the talk ready.
---

# Presentation QA

Never approve this deck from slides.md or CSS alone.

The rendered presentation is the product.

## Required loop

1. Start or build Slidev.
2. Open it with Chromium.
3. Use a 1280x720 viewport.
4. Capture every slide.
5. Review the complete sequence visually.
6. Test the WASM demo.
7. Fix concrete problems.
8. Render again.
9. Stop when meaningful problems are resolved.

## Review every slide for

- immediate focal point
- readable typography
- screen-share readability
- overflow or clipping
- awkward line breaks
- excessive density
- weak hierarchy
- unnecessary borders/cards/colors
- repeated compositions
- generic AI-generated aesthetics
- unnatural Japanese
- inconsistent alignment
- misleading technical visuals

## Review the deck as a sequence

Check:
- visual rhythm
- pacing
- whether consecutive slides feel identical
- whether USB -> C -> WASM -> technology selection remains coherent
- whether viewers know where to look without reading everything

## Adversarial design questions

For every slide ask:

- Is this actually designed, or merely styled?
- Could the same layout appear in an unrelated AI-generated deck?
- Is the border/card/color communicating information?
- Would removing decoration improve this?
- Is the actual technical object more interesting than the UI around it?
- Would this survive Discord video compression?

## Demo QA

Test:
- normal WASM path
- loading behavior
- fallback behavior
- malformed input
- big-endian demonstration
- state labels

The UI must truthfully say whether WASM or JavaScript is executing.

## Final approval

Do not say the deck is ready unless actual rendered slides were inspected.