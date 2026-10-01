# Spec: Factory Shape Creator

## Objective

Turn the current empty C++ program into an interactive terminal experience. On
startup, it displays the exact title `Welcome to the Factory.`, lets a user
choose a box or triangle, gathers the requested visual settings, simulates the
factory working, and shows a text preview of the requested creation.

### Success criteria

- The first visible program output contains `Welcome to the Factory.`.
- The user can choose either a box or a triangle.
- The program collects an outline color, fill color, and size for the chosen
  shape.
- The program displays the available color choices before prompting for either
  color.
- Invalid menu choices, unsupported colors, and invalid numeric sizes produce a helpful
  message and re-prompt without terminating the program.
- After valid customization, the program displays a creation message, waits
  three seconds, and shows a labeled textual preview plus the selected
  settings.

## Assumptions

- This is a terminal application: the repository has only `main.cpp` and a
  shell script that compiles it with `g++`; it has no GUI framework.
- A preview uses ANSI color escapes for its outline and fill cells, and also
  shows the selected color names as readable labels.
- Colors must be one of: black, red, green, yellow, blue, magenta, cyan,
  white, gray, purple, or orange.
- `size` is a positive whole number and controls the width/height of the ASCII
  art; it may not exceed 70 characters. Every outline is one cell wide.
- The factory delay is exactly three seconds.
- A single creation runs per program invocation; there is no restart menu or
  saved history.

## Tech Stack

- C++17 standard library (`iostream`, `string`, `thread`, `chrono`).
- No new packages or external dependencies.

## Commands

- Build and run interactively: `./test_runner.sh`
- Build with warnings: `g++ -std=c++17 -Wall -Wextra -pedantic main.cpp factory_creator.cpp -o app`
- Run the compiled program: `./app`
- Run tests after they are added: `g++ -std=c++17 -Wall -Wextra -pedantic tests/factory_creator_test.cpp factory_creator.cpp -o /tmp/factory_creator_test && /tmp/factory_creator_test`

## Project Structure

- `main.cpp` — program entry point and interactive input/output flow.
- `factory_creator.h` / `factory_creator.cpp` — shape model, validation, and
  preview-generation logic kept independent of terminal I/O.
- `tests/factory_creator_test.cpp` — unit tests for validation and generated
  previews.
- `specs/factory-creator.md` — this feature’s requirements and plan.

## Code Style

Use small named functions, `enum class` for the two allowed shape kinds, and
standard-library types. Keep terminal I/O in `main.cpp` so the logic is easy to
test.

```cpp
ShapeConfig config{ShapeKind::Box, "blue", "white", 4};
if (!isValid(config)) {
  return 1;
}
std::cout << makePreview(config);
```

## Testing Strategy

- Unit-test valid and invalid shape configurations, including unsupported
  colors and sizes greater than 70, plus the output structure and ANSI colors
  of both box and triangle previews.
- Compile the production program with warnings enabled.
- Manually exercise one box and one triangle flow, including a bad menu choice
  and a non-positive numeric value.
- Do not make tests depend on the real three-second delay; it belongs only to
  the interactive entry point.

## Boundaries

- Always: preserve the exact welcome title, validate all user input, run tests
  and a warning-enabled compile before handoff.
- Ask first: adding GUI libraries, changing the delay, accepting arbitrary
  fractional/negative dimensions, or adding repeat/save behavior.
- Never: add dependencies, alter unrelated files, commit generated `app`, or
  use terminal escape sequences as the only way to communicate selected color.

## Implementation Plan

### Task 1: Define the shape model and preview logic

**Acceptance:** A `ShapeConfig` represents either shape and produces readable
ASCII previews with colored outline and fill cells; invalid or unsupported
colors, non-positive sizes, and sizes above 70 are rejected.

**Verify:** Unit tests compile and pass.

### Task 2: Add the interactive factory flow

**Acceptance:** The program presents the title, selection prompts, customization
prompts, re-prompts invalid input, waits three seconds, and displays the
requested preview.

**Verify:** Warning-enabled compile and scripted/manual terminal checks for a
box and triangle.

### Checkpoint

- Unit tests pass.
- `g++ -std=c++17 -Wall -Wextra -pedantic main.cpp factory_creator.cpp -o app`
  succeeds.
- The full interactive flow matches all success criteria.

## Risks and Mitigations

| Risk | Mitigation |
| --- | --- |
| Console color support varies | Display color names in the preview rather than depending on ANSI escape codes. |
| Stream failures can trap input loops | Clear failed input and discard the invalid line before re-prompting. |
| Large values create unusable output | Reject sizes above the specified maximum of 70 characters. |

## Open Questions

None, provided the assumptions above are accepted.
