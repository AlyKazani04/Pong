# Contributing to Pong

Thank you for your interest in contributing to **Pong**!  
This project is written in **C** and uses the **raylib** library. Contributions are welcome, but please follow the guidelines below to keep the workflow clean and consistent.

---

## Repository Rules

- The `main` branch is **protected**
- **All changes must go through Pull Requests**
- Every PR requires **at least 1 review**
- I, (**Aly Kazani**) am the **only maintainer** and reviewer
- Direct pushes to `main` are not allowed

---

## Branch Naming Convention

Please create a new branch from `main` using one of the following formats:

- `bugfix/<short-description>`
- `feature/<short-description>`
- `docs/<short-description>`

Examples:
- `bugfix/ball-collision`
- `feature/ai-opponent`
- `docs/update-readme`

Use clear, concise names written in lowercase and separated by hyphens if needed.

---

## Development Setup

- **Language:** C  
- **Compiler:** GCC  
- **Graphics Library:** raylib  
- **Platform:** Windows (current development environment)

The project is developed using **VS Code**, and the following flags are used to build the executable (`pong.exe`) via `tasks.json`:

```bash
-g
${file}
-o ${fileDirname}\pong.exe
-lraylib
-lopengl32
-lgdi32
-lwinmm
```

## Make sure:
- raylib is properly installed and linked
- You are using GCC, not MSVC or Clang
- Your changes compile without errors or warnings

---

## Coding Guidelines

- Keep the code simple and readable
- Follow existing code style and formatting
- Avoid introducing unnecessary abstractions
- Comment logic that is non-trivial or game-specific
- Do not introduce unused variables or dead code

---

## Commit Messages

Write clear and meaningful commit messages. Examples:
- Fix paddle collision logic
- Add basic CPU opponent
- Update build instructions

Avoid vague messages like fix, update, or changes.

---

## Pull Request Guidelines

When opening a PR:

1. Clearly describe what you changed and why
2. Reference related issues if applicable
3. Ensure the project builds and runs correctly
4. Keep PRs focused - one feature or fix per PR is preferred

The PR will be reviewed by the me before merging.

---

## Issues
- Use issues to report bugs or suggest features
- Provide clear reproduction steps for bugs
- Include screenshots or logs if relevant

---

By contributing, you agree to follow these guidelines and help keep the project maintainable and easy to understand.

Thank you for contributing!