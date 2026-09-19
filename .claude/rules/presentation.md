# Presentation project rules

This repository's primary product is a 15-minute online technical presentation.

For presentation-related work:

- Visual design is a first-class requirement.
- Do not default to generic AI-generated frontend patterns.
- Do not judge presentation quality from source code alone.
- Render and visually inspect the deck after meaningful design changes.
- Optimize for Discord screen sharing at 1280x720.
- Prefer the technical material itself over decorative UI.
- Preserve technical correctness during redesign.
- Do not declare the deck finished without rendered-output QA.
- Claude owns the overall visual direction.
- Parallel agents may review or investigate, but must not independently redesign different slides into conflicting visual systems.
- Do not push, create PRs, or merge without explicit user approval.

## Required workflow for presentation changes

Before modifying slides.md, style.css, or presentation components:

1. Read `docs/design-brief.md`.
2. Use the `frontend-design` and `technical-lt-design` skills.
3. Inspect the current rendered deck before redesigning it.

After meaningful visual changes:

1. Use `webapp-testing` and `presentation-qa`.
2. Render every slide at 1280x720.
3. Inspect the screenshots visually, not only the DOM or source.
4. Fix concrete visual problems found in the screenshots.
5. Repeat until another pass finds no meaningful visual defect.

Never declare the presentation complete based only on successful build output.