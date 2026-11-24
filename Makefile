SRC = src/data.c src/engine.c
EXP = _api_register,_api_next,_api_suggest,_api_finalize,_api_undo,_api_care,_api_patient,_api_bill,_api_state
cli:
	gcc -Wall -Wextra -O2 -Iinclude $(SRC) src/main.c -o dhanvantari
wasm:
	emcc -O2 -Iinclude $(SRC) -o web/ayush.js -sEXPORTED_FUNCTIONS=$(EXP) -sEXPORTED_RUNTIME_METHODS=ccall
serve:
	cd web && python3 -m http.server 8000
