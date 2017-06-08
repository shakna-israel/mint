# mint

**min**imal **int**eger language.

---

This is a reference implementation for a small estoric programming language, that is intentionally *not* Turing complete. Programs written in it will always terminate. (Barring any bugs in implementation).

---

# Building

Check the Releases page, there might be a pre-built download.

---

Have g++ in your PATH, as well as UPX.

Then run:

```
./build.sh release
```

The release binary can be found at build/mint.

It is statically linked.

---

# Usage

You can both pipe programs to the mint interpreter, and supply them as arguments.

Piped data is appended *after* data supplied as an argument.

```
echo "---%" | mint ++++
> 1
```

See [Specification](Specification.md) for expected behaviours.

---

# License

Any and all C++ files are covered by [CLICENSE.md](CLICENSE.md).

Any and all other files are covered by [DLICENSE](DLICENSE).
