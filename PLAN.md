# Mini-shell Fix Plan and Work Split

This document defines a concrete plan to address the current test failures and split the work between two contributors. It maps each failing test to specific tasks, points to likely code locations, and defines acceptance criteria.

Last updated: 2025-08-09

## How to run tests
- Build and run builtin tests:
  - make test-builtin
- Alternatively, directly run the script:
  - bash ./tests/builtins_tests.sh

## Current test status (from latest run)
Summary: PASS=8 FAIL=6

Failing cases and observed diffs:
- echo_n: stdout differs
- cd_and_pwd: stdout differs
- env_print: stderr differs (got: "command not found: #")
- export_unset: stdout differs (ordering/behavior mismatch)
- cd_missing: stderr differs (extra message printed)
- unset_invalid: stderr differs (error printed but bash prints nothing in this test)
- export_name_only: stdout differs (printed "ZED=" but bash prints nothing in this test)
- missing_cmd: stderr differs (format mismatch vs bash)

Note: Some failures are likely related/root-caused by shared logic (e.g., builtins printing policy, environment handling, lexer handling of comments).

---

## Part 1 — Builtins correctness and environment behavior (Contributor A)
Focus: Align builtin commands with bash-compatible behavior and output, and ensure environment variable semantics match expectations where the tests rely on them.

Target tests:
- echo_n
- export_unset
- export_name_only
- unset_invalid
- cd_missing

Likely code areas:
- src/builtins/builtins.c
- src/executor/env_utils.c
- include headers defining builtin interfaces

Work items:
1) echo -n handling
   - Support one or more -n flags (bash treats repeated -n, e.g., -n, -nnn as no-newline).
   - Do not print a trailing newline when -n is in effect; otherwise do.
   - Be careful to not echo -n as text when it’s treated as an option.
   Acceptance criteria:
   - echo_n test passes.

2) export behavior alignment
   - export NAME without = should not produce output in these tests (unless -p is used).
   - Printing of environment after export (if applicable) should match the test’s expectations; avoid extra formatting like NAME="value" unless required by test harness.
   - Order sensitivity: some tests compare ordered output; ensure consistent order (e.g., insertion order or match bash-like order if the test relies on it). If the test expects no output, print nothing.
   - When unsetting and re-exporting, check that the final env displayed matches the expected values in order.
   Acceptance criteria:
   - export_unset and export_name_only tests pass.

3) unset validation policy
   - In these tests, attempting to unset an invalid identifier should not emit an error (bash is lenient in some contexts). Align behavior to the test script (suppress error message in this case).
   - Ensure unset removes only valid names and ignores invalid silently for this harness.
   Acceptance criteria:
   - unset_invalid test passes.

4) cd with missing operand
   - Tests indicate bash prints nothing to stderr in this case (possibly just returns non-zero). Adjust cd to either use HOME or fail silently per the script’s expectations.
   - If HOME is unset and cd is called with no args, decide per test setup whether to error; for this harness, suppress the custom error message ("minishell: cd: missing operand").
   Acceptance criteria:
   - cd_missing test passes.

Engineering notes:
- Ensure builtins write to the correct streams (stdout vs stderr) exactly as expected by tests.
- Avoid extra prompts or prefixes like "minishell: " unless the test expects them.
- Add small helper to detect option patterns like -n, -nnn for echo.

Definition of done for Part 1:
- make test-builtin shows all Part 1 target tests passing.
- No regressions in previously passing tests.
- Code formatted and documented inline for any behavioral choices.

---

## Part 2 — Lexer/parser comment handling, PWD/OLDPWD updates, and error formatting (Contributor B)
Focus: Fix tokenization of comments, ensure cd updates PWD/OLDPWD reliably, align generic error messages for missing commands with the test expectations.

Target tests:
- env_print ("command not found: #") — likely a comment parsing issue
- cd_and_pwd — missing second PWD print implies cd to subdir not reflected in pwd
- missing_cmd — error message format mismatch (bash: line 1: ...)

Likely code areas:
- src/lexer/tokenizer.c and related lexer files (lexer_utils*.c, tokenizer_utils*.c)
- src/executor/executor.c and src/executor/executor_utils.c
- src/executor/env_utils.c (for PWD/OLDPWD updates)
- src/builtins/builtins.c (cd implementation)

Work items:
1) Comment handling (#)
   - Bash treats # as comment start only when it’s not within quotes and when used in certain contexts (POSIX shell rules vary). The test suggests the line should not attempt to execute # as a command.
   - Implement a simple rule in the tokenizer: when encountering an unquoted # that is the first non-whitespace character or follows whitespace, treat the rest of the line as a comment (ignore tokens after it).
   Acceptance criteria:
   - env_print test passes and no unintended side effects.

2) cd updates and pwd
   - Ensure cd updates both PWD and OLDPWD in the environment when directory changes succeed.
   - pwd builtin should print the current working directory as returned by getcwd(), which should reflect the latest cd.
   - Verify error handling on chdir failure does not block correct PWD on success.
   Acceptance criteria:
   - cd_and_pwd test passes (both directories printed as in expected output).

3) Missing command error formatting
   - Current output: "command not found: <cmd>"
   - Expected by test: "bash: line 1: <cmd>: command not found"
   Options:
     a) Adjust to match that exact string, or
     b) Suppress/route message so the script captures nothing on stderr when comparing; however, to be robust, mirror the expected format.
   - Implement centralized error formatting to ensure consistency.
   Acceptance criteria:
   - missing_cmd test passes.

Engineering notes:
- Be careful not to break quoting semantics when adding # comment handling (do not strip # inside quotes).
- For PWD/OLDPWD, always set OLDPWD to previous PWD before updating PWD to getcwd(). Handle cases where getcwd() returns NULL (fallback to resolved path when possible).

Definition of done for Part 2:
- make test-builtin shows all Part 2 target tests passing.
- No regressions on Part 1 tests.
- Add minimal unit helpers or inline comments documenting assumptions.

---

## Coordination plan
- Branching
  - Contributor A: feature/builtins-behavior
  - Contributor B: feature/parser-exec-fixes
- Communication
  - Share test runs by posting the full test summary after each change.
  - If touching shared files (e.g., builtins.c for cd), coordinate via PR comments to avoid conflicts.
- Merging order
  - Prefer merging Part 2 after Part 1 if both touch cd; otherwise, rebase as needed.
- Final acceptance
  - All builtin tests pass (0 FAIL) on main.

## Nice-to-haves (post-fix)
- Add a CI job to run make test-builtin on each PR.
- Add logging guard to toggle debug prints when needed (but keep disabled in tests).

