# Dhanvantari: AYUSH case-taking in C

A Data Structures project in C. A circular queue, binary search tree, linked list, hash table and stack drive a patient intake, case-taking, term-mapping and claim-sheet workflow. The web UI calls the same C code compiled to WebAssembly.

## Run in the terminal
    make cli && ./dhanvantari

## Run the website locally
    make wasm && make serve      # needs Emscripten; open http://localhost:8000

## Deploy (GitHub Pages)
1. Push to a GitHub repo on the `main` branch.
2. Repo Settings > Pages > Source: **GitHub Actions**.
3. The workflow in `.github/workflows/deploy.yml` builds the WebAssembly and publishes the site.

## Files
- `include/ayush.h` structures and API, `src/data.c` sample terminology dataset, `src/engine.c` all data-structure logic, `src/main.c` terminal menu, `web/` site.

The dataset is a sample. Swap in the official NAMASTE / ICD-11 TM2 codes before real use.
